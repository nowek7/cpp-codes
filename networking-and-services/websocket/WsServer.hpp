#pragma once

#include "WsChannels.hpp"

class WsServer
  {
  const int NUM_PROTOCOLS = 3;

  public:
    typedef struct Session
      {
      void *theUserSpace;
      } theSession;

    inline static int theId{0};
    inline static int mainCallback(struct lws *aWs, enum lws_callback_reasons aReason, void *aUser, void *aRequest, size_t aSize);
    inline static int defaultCallback(struct lws *aWs, enum lws_callback_reasons aReason, void *aUser, void *aRequest, size_t aSize);

    WsServer();
    ~WsServer();

    void run();

    void createProtocols();

    void receive(lws *aWs, void *aData);
    void manageClient(lws *aRawWsClient, const nlohmann::json &aPayload);
    void subscribe(const WsClient &aWsClient, const nlohmann::json &aData);
    void unsubscribe(const WsClient &aWsClient, const nlohmann::json &aData);

    void sendToClients(const nlohmann::json &aPayload);
    void send(lws *aWs, const nlohmann::json &aPayload);

  private:
    const char *theInterface{nullptr};
    struct lws_context_creation_info theInfoContext{0};
    struct lws_context *theContext{nullptr};
    struct lws_protocols theProtocols[NUM_PROTOCOLS];
    const char *theCertPath{nullptr};
    const char *theKeyPath{nullptr};

    std::vector<WsClient> theWsClients;
    WsChannels theChannels;
  };
