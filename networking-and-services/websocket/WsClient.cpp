#include "WsClient.hpp"

WsClient::WsClient(int aId, lws *aWs)
  :
  theId(aId),
  theWs(aWs)
  {}

WsClient::WsClient(const WsClient &aWsClient)
  {
  theId = aWsClient.getId();
  theWs = aWsClient.getWs();
  }

WsClient::WsClient(WsClient &&aWsClient)
  {
  theId = std::move(aWsClient.getId());
  theWs = std::move(aWsClient.getWs());
  }

WsClient::~WsClient()
  {}

WsClient &WsClient::operator=(WsClient &&aWsClient)
  {
  if (this != &aWsClient)
    {
    theId = std::move(aWsClient.getId());
    theWs = std::move(aWsClient.getWs());
    }

  return *this;
  }

bool WsClient::operator==(const WsClient &aWsClient)
  {
  return theId == aWsClient.getId();
  }

bool WsClient::operator!=(const WsClient &aWsClient)
  {
  return !(*this == aWsClient);
  }

struct lws* WsClient::getWs() const
  {
  return theWs;
  }

int WsClient::getId() const
  {
  return theId;
  }

