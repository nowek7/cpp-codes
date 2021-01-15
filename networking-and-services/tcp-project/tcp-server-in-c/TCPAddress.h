#ifndef TCP_ADDRESS_H
#define TCP_ADDRESS_H

#include <stdint.h>
#include <stdlib.h>

struct TCPAddress
  {
  const char *theHost;
  uint16_t thePort;
  };

struct TCPAddress* initTCPAddress(const char *aHost, const int aPort)
  {
  struct TCPAddress *address = NULL;
  address = (struct TCPAddress*)malloc(sizeof(struct TCPAddress));

  address->theHost = aHost;
  address->thePort = aPort;
  return address;
  }

#endif