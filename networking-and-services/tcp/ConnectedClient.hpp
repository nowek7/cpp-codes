#pragma once

class ConnectedClient
  {
  public:
    ConnectedClient(int aFd);
    ~ConnectedClient() = default;

    void close();
    bool isConnected() const;
    int getFd() const;

  private:
    int theFd = -1;
  };

