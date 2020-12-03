#pragma once

class Socket
  {
  public:
    static bool setNonblocking(int aFd);
    static int send(int aFd, const char *aBuffer, int aBufferSize);
    static int receive(int aFd, char *aBuffer, int aBufferSize);
  };