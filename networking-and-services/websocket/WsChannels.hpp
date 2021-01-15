#pragma once

#include "WsClient.hpp"

#include <map>
#include <optional>
#include <string_view>
#include <vector>

class WsChannels
  {
  private:
    typedef std::map<std::string_view, std::vector<WsClient>> Channels;

  public:
    WsChannels() = default;
    ~WsChannels() = default;

    void subscribe(const std::string_view &aChannel, WsClient &aWsClient);
    void unsubscribe(const std::string_view &aChannel, WsClient &aWsClient);
    std::optional<std::vector<WsClient>> getWsClients(const std::string_view &aChannel);

  private:
    Channels theChannels;

    bool isEmpty(const std::string_view &aChannel);
    void remove(const std::string_view &aChannel);
    void remove(WsClient &aWsClient);
  };