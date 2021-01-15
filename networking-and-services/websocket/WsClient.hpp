#pragma once

#include <memory>
#include <libwebsockets.h>

class WsClient
  {
  public:
    WsClient(int aId, lws *aWs);
    WsClient(const WsClient &aWsClient);
    WsClient(WsClient &&aWsClient);
    ~WsClient();

    WsClient &operator=(WsClient &&aWsClient);
    bool operator==(const WsClient &aWsClient);
    bool operator!=(const WsClient &aWsClient);

    lws* getWs() const;
    int getId() const;

  private:
    WsClient() = delete;

    int theId;
    lws *theWs;
  };