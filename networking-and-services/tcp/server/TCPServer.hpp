#pragma once

#include "./../helpers/TCPAddress.hpp"
#include "./../helpers/ConnectedClient.hpp"

#include <optional>
#include <vector>
#include <memory>

class TCPServer
  {
  public:
    TCPServer(const TCPAddress &aAddress);
    ~TCPServer();

    bool isRunning() const;
    void handleAcceptingConnections();
    void handle();

  private:
    int theListeningSocket = -1;
    TCPAddress theAddress;
    std::vector<ConnectedClient> theClients;

    bool open();
    void close();
    void removeClient(const int &aClientIdx);
    void removeClient(const ConnectedClient &aClient);
    void removeClients();
  };