#include "TCPServer.h"

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

// #define MULTITHREAD

bool openServer(struct TCPServer *aServer)
  {
  if (aServer)
    {
    struct TCPAddress *address = aServer->theAddress;
    if (!(address->thePort > 0 && address->theHost))
      perror("Empty server address!");

    int sock = -1;
    struct sockaddr_in sockAddress;
    memset(&sockAddress, 0, sizeof(struct sockaddr_in));
    int optval = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    printf("Opening listening port at %s:%i \n", address->theHost, address->thePort);
    if (sock < 0)
      {
      printf("Can't create TCP socket\n");
      return false;
      }

    // Internet address family
    sockAddress.sin_family = AF_INET;

    // Local port
    sockAddress.sin_port = htons(address->thePort);

    if (address->theHost > 0)
      {
      if (inet_pton(sockAddress.sin_family, address->theHost, &(sockAddress.sin_addr)) == 0)
        sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
      }
    else
      {
      // IP not provided
      sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
      }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval)) != 0)
      {
      printf("Setsockopt - setting SO_REUSEADDR\n");
      close(sock);
      return false;
      }

    if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&optval, sizeof(optval)) != 0)
      {
      printf("Setsockopt - setting SO_KEEPALIVE\n");
      close(sock);
      return false;
      }

    // Bind to the local address
    if (bind(sock, (struct sockaddr*)&sockAddress, sizeof(sockAddress)) < 0)
      {
      printf("Can't bind the socket to the address\n");
      close(sock);
      return false;
      }

    // Mark the socket so it will listen for incoming connections
    if (listen(sock, SOMAXCONN) < 0)
      {
      printf("Can't listen\n");
      close(sock);
      return false;
      }

    aServer->theListeningSocket = sock;

    return true;
    }
  else
    return false;
  }

void removeClients(struct TCPServer *aServer)
  {
  if (aServer)
    {
    free(aServer->theClients);
    aServer->theNumConnectedClients = 0;
    }
  }

void closeServer(struct TCPServer *aServer)
  {
  if (aServer)
    {
    removeClients(aServer);
    close(aServer->theListeningSocket);
    }
  }

bool isRunning(const struct TCPServer *aServer)
  {
  return aServer ? aServer->theListeningSocket != -1 : false;
  }

void acceptClient(struct TCPServer *aServer, int aFd)
  {
  if (!aServer)
    return;

  // Set non blocking socket.
  long flags = fcntl(aFd, F_GETFL);;
  if (flags == -1)
    {
    close(aFd);
    printf("Can't get open flags fd=%d\n", aFd);
    return;
    }

  if (fcntl(aFd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
    close(aFd);
    printf("Can't set open flags fd=%d\n", aFd);
    return;
    }

  int connected = aServer->theNumConnectedClients;
  if (connected != 0)
    {
    struct ConnectedClient *clients = NULL;
    clients = (struct ConnectedClient*)malloc(sizeof(struct ConnectedClient) * (connected + 1));
    memcpy(clients, aServer->theClients, connected);
    removeClients(aServer);

    clients[aServer->theNumConnectedClients].theFd = aFd;
    aServer->theClients = clients;
    }
  else
    {
    aServer->theClients = NULL;
    aServer->theClients = (struct ConnectedClient*)malloc(sizeof(struct ConnectedClient) * 1);
    aServer->theClients[0].theFd = aFd;
    }

  ++(aServer->theNumConnectedClients);
  printf("\t\t Accepted new connection %d\n", aServer->theClients[0].theFd);
  printf("\t\t Connected %d\n", aServer->theNumConnectedClients);
  }

void handleAcceptingConnections(struct TCPServer *aServer)
  {
  printf("\t Handling new connections\n");

  // Clear readset.
  fd_set rset;
  memset(&rset, 0, sizeof(fd_set));

  FD_ZERO(&rset);

  int maxFd = aServer->theListeningSocket + 1;
  struct timeval timeToSelect;
  timeToSelect.tv_sec = 0;
  timeToSelect.tv_usec = 500;

  clock_t start = clock();
  while (clock() < start + 2000)
    {
    // Set listener in readset.
    FD_SET(aServer->theListeningSocket, &rset);

    int readySocket = select(maxFd, &rset, NULL, NULL, &timeToSelect);
    // if (readySocket <= 0)
    //   continue;

    if (FD_ISSET(aServer->theListeningSocket, &rset))
      {
      struct sockaddr_in sockAddress;
      memset(&sockAddress, 0, sizeof(struct sockaddr_in));

      int length = sizeof(sockAddress);
      int fd = accept(aServer->theListeningSocket, (struct sockaddr*)&sockAddress, (socklen_t*)&length);
      if (fd == -1)
        continue;

      if (fd > maxFd)
        maxFd = fd;

      acceptClient(aServer, fd);
      }
    }
  }

void handle(struct TCPServer *aServer)
  {
  printf("Handle\n");

  const int numClients = aServer->theNumConnectedClients;
  for (int i = 0; i < numClients; ++i)
    {
    int sizeBuffer = 0;
    int readBytes = read(aServer->theClients[i].theFd, (char*)&sizeBuffer, sizeof(sizeBuffer));
    // printf("Read %d", readBytes);
    // if (readBytes < 0)
    //   {
    //   // printf("Could not read size of msg from socket\n");
    //   close(aServer->theClients[i].theFd);
    //   aServer->theClients[i].theFd = -1;
    //   continue;
    //   }

    char *buffer = (char*)malloc(sizeBuffer * sizeof(char));
    readBytes = read(aServer->theClients[i].theFd, buffer, sizeBuffer);
    // if (readBytes < 0)
    //   {
    //   // printf("Could not read msg from socket\n");
    //   close(aServer->theClients[i].theFd);
    //   aServer->theClients[i].theFd = -1;
    //   continue;
    //   }

    sleep(10);
    printf("Received: %s \n", buffer);
    }
  }

void updateClients(struct TCPServer *aServer)
  {
  int numConnected = 0;
  const int numClients = aServer->theNumConnectedClients;
  for (int i = 0; i < numClients; ++i)
    {
    if (aServer->theClients[i].theFd != -1)
      numConnected++;
    }

  struct ConnectedClient *clients = NULL;
  if (numClients != numConnected)
    {
    clients = (struct ConnectedClient*)malloc(sizeof(struct ConnectedClient) * numConnected);
    for (int i = 0; i < numClients; ++i)
      {
      if (aServer->theClients[i].theFd != -1)
        clients[i] = aServer->theClients[i];
      }

    free(aServer->theClients);
    aServer->theClients = clients;
    aServer->theNumConnectedClients = numConnected;
    }
  }

int main(int argc, char *argv[])
  {
  struct TCPAddress *tcpAddress = initTCPAddress("localhost", 3000);
  struct TCPServer *tcpServer = initTCPServer(tcpAddress);

  bool isOpen = openServer(tcpServer);
  if (!isOpen)
    {
    perror("Can't open TCP server!\n");
    exit(-1);
    }

  while (true)
    {
    handleAcceptingConnections(tcpServer);

    #ifdef MULTITHREAD
      pthread_t thread;

      result = pthread_create(&thread, NULL, handle, tcpServer);
      if (result < 0)
        {
        perror("Could not create thread");
        exit(-1);
        }
      pthread_detach(thread);
    #else
      handle(tcpServer);
    #endif

    // updateClients(tcpServer);
    }

  closeServer(tcpServer);
  free(tcpServer->theAddress);
  free(tcpServer);
  }