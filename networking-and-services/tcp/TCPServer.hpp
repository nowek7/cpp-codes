#pragma once

#include "TCPAddress.hpp"
#include "ConnectedClient.hpp"

#include <optional>
#include <vector>
#include <memory>

class TCPServer
  {
  public:
    TCPServer();
    ~TCPServer();

    bool isRunning() const;
    void handleAcceptingConnections(bool aExtraAccepting = false);

  private:
    int theListeningSocket = -1;
    ReTCPAddress theAddress;
    std::vector<ReConnectedClient> theClients;

    bool open();
    void close();
    void resetClients();
  };

#endif