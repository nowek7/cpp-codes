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

    void send();

    int getFd() const;

  private:
    int theFd;
    ReTCPAddress theAddress;
    ConnectionState theState = ConnectionState::CLOSED;

    TCPClient(const ReTCPClient&) = delete;
    TCPClient& operator=(const ReTCPClient&) = delete;

    void close();
    void reset();
    void reconnect();
  };