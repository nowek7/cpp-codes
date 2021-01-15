#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "TCPAddress.h"
#include "ConnectedClient.h"

#include <stdlib.h>

struct TCPServer
  {
  int theListeningSocket;
  struct TCPAddress *theAddress;
  struct ConnectedClient *theClients;
  int theNumConnectedClients;
  };

struct TCPServer* initTCPServer(struct TCPAddress *aTCPAddress)
  {
  struct TCPServer *server = NULL;
  server = (struct TCPServer*)malloc(sizeof(struct TCPServer));
  server->theListeningSocket = -1;
  server->theAddress = aTCPAddress;
  server->theClients = NULL;
  server->theNumConnectedClients = 0;

  return server;
  }

#endif