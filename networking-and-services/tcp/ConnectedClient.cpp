#include "ConnectedClient.hpp"

ReConnectedClient::ReConnectedClient(int aFd)
  :
  theFd(aFd)
  {}

void ReConnectedClient::close()
  {
  ::close(theFd)
  }

bool ReConnectedClient::isConnected() const
  {
  return theFd != -1;
  }

int ReConnectedClient::getFd() const
  {
  return theFd;
  }