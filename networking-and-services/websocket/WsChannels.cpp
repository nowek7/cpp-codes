#include "WsChannels.hpp"

#include <algorithm>
#include <stdexcept>

void WsChannels::subscribe(const std::string_view &aChannel, WsClient &aWsClient)
  {
  auto it = theChannels.find(aChannel);
  if (it != theChannels.end())
    {
    bool success = false;
    auto &connectedsClients = it->second;
    for (size_t i = 0; i < connectedsClients.size() && !success; i++)
      {
      const auto &client = connectedsClients[i];
      const auto id = client.getId();
      const auto ws = client.getWs();
      if (id != aWsClient.getId())
        {
        if (ws == aWsClient.getWs())
          connectedsClients.erase(connectedsClients.begin() + i);

        connectedsClients.push_back(aWsClient);
        success = true;
        }
      else
        {
        // Replace WsClient
        std::swap(connectedsClients[i], aWsClient);
        success = true;
        }
      }
    }
  else
    {
    auto [it, inserted] = theChannels.insert({aChannel, {}});
    if (!inserted)
      throw std::logic_error("Can't insert channel");

    it->second.push_back(aWsClient);
    }
  }

void WsChannels::unsubscribe(const std::string_view &aChannel, WsClient &aWsClient)
  {
  auto it = theChannels.find(aChannel);
  if (it != theChannels.end())
    {
    if (!isEmpty(aChannel))
      {
      auto &connectedsClients = it->second;
      auto pos = std::find(connectedsClients.begin(), connectedsClients.end(), aWsClient);
      if (pos != connectedsClients.end())
        connectedsClients.erase(pos);

      if (isEmpty(aChannel))
        remove(aChannel);
      }
    else
      remove(aChannel);
    }
  }

std::optional<std::vector<WsClient>> WsChannels::getWsClients(const std::string_view &aChannel)
  {
  auto it = theChannels.find(aChannel);
  if (it != theChannels.end())
    return it->second;
  else
    return {};
  }

bool WsChannels::isEmpty(const std::string_view &aChannel)
  {
  const auto it = theChannels.find(aChannel);
  if (it != theChannels.end())
    {
    auto &websocketClients = it->second;
    if (websocketClients.empty())
      return true;
    else
      return false;
    }
  else
    return true;
  }

void WsChannels::remove(const std::string_view &aChannel)
  {
  auto it = theChannels.find(aChannel);
  if (it != theChannels.end())
    theChannels.erase(it);
  }

void WsChannels::remove(WsClient &aWsClient)
  {
  for (auto &[channel, connectedClients] : theChannels)
    {
    auto pos = std::find(connectedClients.begin(), connectedClients.end(), aWsClient);
    if (pos != connectedClients.end())
      {
      connectedClients.erase(pos);
      if (connectedClients.empty())
        theChannels.erase(channel);
      }
    }
  }

