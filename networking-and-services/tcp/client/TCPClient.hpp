#pragma once

#include "TCPAddress.hpp"

class TCPClient
  {
  public:
    enum class ConnectionState
      {
      NO_CHANGE,
      CLOSED,
      ESTABLISHED
      };

  public:
    TCPClient();
    ~TCPClient();

    bool connect();
    bool isConnected() const { return theFd != -1; };
    ConnectionState updateState();

    void write();
    void read();

    int getFd() const;

  private:
    int theFd;
    TCPAddress theAddress;
    ConnectionState theState = ConnectionState::CLOSED;

    TCPClient(const TCPClient&) = delete;
    TCPClient& operator=(const TCPClient&) = delete;

    void close();
    void reset();
    void reconnect();
  };