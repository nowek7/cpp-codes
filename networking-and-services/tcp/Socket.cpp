#include "Socket.hpp"

#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>

bool Socket::setNonblocking(int fd)
  {
  long flags = fcntl(fd, F_GETFL);;
  if (flags == -1)
    {
    printf("Can't get open flags fd=%d\n", fd);
    return false;
    }

  if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
    printf("Can't set open flags fd=%d\n", fd);
    return false;
    }

  return true;
  }

int Socket::send(int aFd, const char *aBuffer, int aBufferSize)
  {
  return ::send(aFd, aBuffer, aBufferSize, 0);
  }

int Socket::receive(int aFd, char *aBuffer, int aBufferSize)
  {
  int bytesRecv = ::recv(aFd, aBuffer, aBufferSize, 0);
  if (bytesRecv < 0)
    {
    if (errno != EWOULDBLOCK)
      return -1;
    else
      return 0;
    }
  else if (bytesRecv == 0)
    return -1;

  return bytesRecv;
  }
