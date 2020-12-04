#include "TCPServer.hpp"
#include "./../helpers/Socket.hpp"

#include <chrono>
#include <numeric>
#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std::chrono_literals;

TCPServer::TCPServer(const TCPAddress &aAddress)
  :
  theAddress(aAddress)
  {
  bool opened = open();
  if (!opened)
    throw std::runtime_error("Cannot open TCP server!");
  }

TCPServer::~TCPServer()
  {
  close();
  }

bool TCPServer::isRunning() const
  {
  return theListeningSocket != -1;
  }

void TCPServer::close()
  {
  ::close(theListeningSocket);
  }

void TCPServer::removeClients()
  {
  theClients.clear();
  }

bool TCPServer::open()
  {
  if (!theAddress.isSet())
    throw std::logic_error("Empty server address!");

  int sock = -1;
  sockaddr_in sockAddress{ 0 };
  int optval = 1;

  const char* host = theAddress.theHost.c_str();
  const uint16_t port = theAddress.thePort;

  sock = socket(AF_INET, SOCK_STREAM, 0);

  printf("Opening listening port at %s:%i \n", host, port);
  if (sock < 0)
    {
    printf("Can't create TCP socket\n");
    return false;
    }

  // Internet address family
  sockAddress.sin_family = AF_INET;

  // Local port
  sockAddress.sin_port = htons(port);

  if (theAddress.theHost.size() > 0)
    {
    if (inet_pton(sockAddress.sin_family, host, &(sockAddress.sin_addr)) == 0)
      sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    }
  else
    {
    // IP not provided
    sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    }

  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&optval), sizeof(optval)) != 0)
    {
    printf("Setsockopt - setting SO_REUSEADDR\n");
    ::close(sock);
    return false;
    }

  if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<char*>(&optval), sizeof(optval)) != 0)
    {
    printf("Setsockopt - setting SO_KEEPALIVE\n");
    ::close(sock);
    return false;
    }

  // Bind to the local address
  if (bind(sock, reinterpret_cast<struct sockaddr*>(&sockAddress), sizeof(sockAddress)) < 0)
    {
    printf("Can't bind the socket to the address\n");
    ::close(sock);
    return false;
    }

  // Mark the socket so it will listen for incoming connections
  if (listen(sock, SOMAXCONN) < 0)
    {
    printf("Can't listen\n");
    ::close(sock);
    return false;
    }

  theListeningSocket = sock;

  return true;
  }

void TCPServer::handleAcceptingConnections()
  {
  // Clear readset.
  fd_set rset{};
  FD_ZERO(&rset);

  int maxFd = theListeningSocket + 1;
  struct timeval timeToSelect {0, 500};

  auto until = std::chrono::high_resolution_clock::now() + 10s;
  while (std::chrono::high_resolution_clock::now() < until)
    {
    // Set listener in readset.
    FD_SET(theListeningSocket, &rset);

    const int readySocket = select(maxFd, &rset, NULL, NULL, &timeToSelect);
    if (readySocket <= 0)
      continue;

    if (FD_ISSET(theListeningSocket, &rset))
      {
      sockaddr_in sockAddress{};
      int length = sizeof(sockAddress);
      int fd = accept(theListeningSocket, reinterpret_cast<sockaddr*>(&sockAddress), reinterpret_cast<socklen_t*>(&length));
      if (fd == -1)
        continue;

      if (fd > maxFd)
        maxFd = fd;

      theClients.emplace_back(fd);
      }
    }
  }