#include "ConnectedClient.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

ConnectedClient::ConnectedClient(int aFd)
  :
  theFd(aFd)
  {}

void ConnectedClient::close()
  {
  ::close(theFd);
  }

bool ConnectedClient::isConnected() const
  {
  return theFd != -1;
  }

int ConnectedClient::getFd() const
  {
  return theFd;
  }