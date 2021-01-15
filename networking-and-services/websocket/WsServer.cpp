#include "WsServer.hpp"

#include <libwebsockets.h>

WsServer::WsServer()
  {
  createProtocols();

  // Fill zeros to lws_context_creation_info.
  // memset(&theInfoContext, 0, sizeof(theInfoContext));
  theInfoContext.port = WS_PORT;
  theInfoContext.iface = theInterface;
  theInfoContext.protocols = theProtocols;
  theInfoContext.ssl_cert_filepath = theCertPath;
  theInfoContext.ssl_private_key_filepath = theKeyPath;
  theInfoContext.gid = -1;
  theInfoContext.uid = -1;
  theInfoContext.options = 0;

  // Initialize parameters to context.
  theContext = lws_create_context(&theInfoContext);
  if (!theContext)
    throw std::runtime_error("Can't create lws context\n");
  }

WsServer::~WsServer()
  {
  lws_context_destroy(theContext);

  delete theInterface;
  delete theCertPath;
  delete theKeyPath;
  }

void WsServer::run()
  {
  try
    {
    for (;;)
      lws_service(theContext, 1000);
    }
  catch (const std::exception &ex)
    {
    throw ex;
    }
  }

void WsServer::createProtocols()
  {
  theProtocols[0] =
    {
    "default_callback",
    defaultCallback,
    sizeof(Session),
    0,
    0,
    this
    };

  theProtocols[1] =
    {
    "main_callback",
    mainCallback,
    sizeof(Session),
    1024,
    0,
    this
    };

  theProtocols[2] =
    {
    NULL,
    NULL,
    0,
    0,
    0,
    this
    };
  }

int WsServer::defaultCallback(struct lws *aWebSocket, enum lws_callback_reasons aReason, void *aUser, void *aRequest, size_t aSize)
  {
  return 0;
  }

int WsServer::mainCallback(struct lws *aWs, enum lws_callback_reasons aReason, void *aUser, void *aRequest, size_t aSize)
  {
  // WsServer instance.
  const lws_protocols *protocol = lws_get_protocol(aWs);
  WsServer *me = reinterpret_cast<WsServer*>(protocol->user);

  // Data will be different for every connected peer
  Session *data = reinterpret_cast<Session*>(aUser);

  // User data be same for every connected peer
  void *userdata = lws_context_user(lws_get_context(aWs));

  switch (aReason)
    {
    case LWS_CALLBACK_PROTOCOL_INIT:
      {
      break;
      }

    case LWS_CALLBACK_ESTABLISHED:
      {
      printf("New connection\n");
      nlohmann::json payload =
        {
          {"channel", "system"},
          {"connectionId", WsServer::theId++}
        };

      me->send(aWs, payload);
      break;
      }

    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
      {
      printf("Websocket error!\n");
      break;
      }

    case LWS_CALLBACK_CLOSED:
      {
      printf("WsServer was closed\n");
      break;
      }

    case LWS_CALLBACK_RECEIVE:
      {
      me->receive(aWs, aRequest);
      break;
      }

    // case LWS_CALLBACK_SERVER_WRITEABLE:
    //   {
    //   break;
    //   }

    case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
      {
      break;
      }

    case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
      {
      printf("\n");
      break;
      }

    default:
      break;
    }

  return 0;
  }

void WsServer::receive(lws *aWs, void *aData)
  {
  auto payload = nlohmann::json::parse(reinterpret_cast<char*>(aData));
  if (!payload.is_null() && !payload.empty())
    manageClient(aWs, payload);
  }

void WsServer::sendToClients(const nlohmann::json &aPayload)
  {
  std::string_view channel = aPayload["channel"].get<std::string_view>();
  auto connectedWsClients = theChannels.getWsClients(channel);
  if (connectedWsClients)
    {
    const int id = aPayload["connectionId"];
    for (const auto &wsClient : connectedWsClients.value())
      {
      if (wsClient.getId() != id)
        send(wsClient.getWs(), aPayload);
      }
    }
  }

void WsServer::manageClient(lws *aRawWsClient, const nlohmann::json &aPayload)
  {
  const auto &wsClient = std::find_if(theWsClients.begin(), theWsClients.end(),
                                      [&aRawWsClient](const auto &aWs)
                                        {
                                        return aRawWsClient == aWs.getWs();
                                        });
  if (wsClient != theWsClients.end())
    {
    if (!aPayload.is_null() && !aPayload.empty())
      {
      if (!aPayload["subscribe"].is_null())
        subscribe(*wsClient, aPayload);

      if (!aPayload["unsubscribe"].is_null())
        unsubscribe(*wsClient, aPayload);
      }
    }
  else
    printf("Something wrong. Unknown WsClient");
  }

void WsServer::subscribe(const WsClient &aWsClient, const nlohmann::json &aData)
  {
  if (aData["subscribe"].is_array())
    {
    for (const auto &value : aData["subscribe"].get<std::vector<std::string_view>>())
      theChannels.subscribe(value, const_cast<WsClient &>(aWsClient));
    }
  else if (aData["subscribe"].is_string())
    theChannels.subscribe(aData["subscribe"].get<std::string_view>(), const_cast<WsClient &>(aWsClient));
  }

void WsServer::unsubscribe(const WsClient &aWsClient, const nlohmann::json &aData)
  {
  if (aData["unsubscribe"].is_array())
    {
    for (const auto &value : aData["unsubscribe"].get<std::vector<std::string_view>>())
      theChannels.unsubscribe(value, const_cast<WsClient &>(aWsClient));
    }
  else if (aData["unsubscribe"].is_string())
    theChannels.unsubscribe(aData["unsubscribe"].get<std::string_view>(), const_cast<WsClient &>(aWsClient));
  }

void WsServer::send(lws *aWs, const nlohmann::json &aPayload)
  {
  std::string_view data = aPayload.dump();
  unsigned char *buffer = new unsigned char[sizeof(char) * (LWS_SEND_BUFFER_PRE_PADDING + data.size() + LWS_SEND_BUFFER_POST_PADDING)];
  std::memcpy(buffer + LWS_SEND_BUFFER_PRE_PADDING, data.data(), data.size());

  // char *buffer = (unsigned char *)malloc(sizeof(char) * (LWS_SEND_BUFFER_PRE_PADDING + theLengthMessage + LWS_SEND_BUFFER_POST_PADDING));
  // memcpy(theData + LWS_SEND_BUFFER_PRE_PADDING, msg.c_str(), theLengthMessage);

  int length = 0;
  int bytesSent = lws_write(aWs, buffer + LWS_SEND_BUFFER_PRE_PADDING, length, LWS_WRITE_TEXT);
  if (bytesSent < static_cast<int>(data.size()))
    printf("Incomplete sending json!\n");

  if (bytesSent < 0)
    printf("WebSocket may be closed!\n");

  delete[] buffer;
  }
