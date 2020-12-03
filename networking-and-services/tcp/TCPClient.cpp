#include "TCPClient.hpp"

#include <stdexcept>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>

TCPClient::TCPClient()
  {
  reset();

  theAddress.theHost = "localhost";
  theAddress.thePort = "3000";
  }

TCPClient::~TCPClient()
  {
  close();
  }

void TCPClient::close()
  {
  if (theFd != -1)
    ::close(theFd);
  }

void TCPClient::reset()
  {
  theFd = -1;
  }

bool TCPClient::connect()
  {
  close();

  if (!theAddress.isSet())
    {
    printf("Server address does not set\n");
    return false;
    }

  int sock = -1;
  struct addrinfo hints { 0 };
  struct addrinfo* server;
  auto port = theAddress.thePort;

  sock = static_cast<int>(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
  if (sock < 0)
    {
    printf("Create TCP socket failed\n");
    return false;
    }

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  int result = getaddrinfo(theAddress.theHost.c_str(), std::to_string(port).c_str(), &hints, &server);
  if (result != 0)
    {
    ::closesocket(sock);
    freeaddrinfo(server);
    }

  result = ::connect(sock, server->ai_addr, static_cast<int>(server->ai_addrlen));
  freeaddrinfo(server);
  if (result < 0)
    {
    if (errno == EINPROGRESS)
      return true;
    else
      return false;
    }

  int optval = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<char*>(&optval), sizeof(optval)) == -1)
    {
    printf("setsockopt - SO_KEEPALIVE\n");
    return false;
    }

  theFd = sock;
  theState = ConnectionState::ESTABLISHED;

  return true;
  }

TCPClient::ConnectionState TCPClient::updateState()
  {
  struct pollfd fds[] = { {theFd, POLLOUT} };

  int res = poll(fds, 1, 0);
  if (res != 0 && res != 1)
    {
    short events = fds[0].revents;
    if (events & POLLOUT)
      {
      int error = 0;
      socklen_t len = 4;

      if (getsockopt(fds[0].fd, SOL_SOCKET, SO_ERROR,
          reinterpret_cast<char *>(&error), &len) != 0)
        {
        close();
        return ConnectionState::CLOSED;
        }

      // Connected
      if (error == 0)
        {
        theState = ConnectionState::ESTABLISHED;
        return UpdateState::eEstablished;
        }
      else if (error != EINPROGRESS)
        {
        close();
        return ConnectionState::CLOSED;
        }
      }
    else if (events & (POLLHUP | POLLERR))
      {
      // Hangup or error
      printf("Hangup or error\n");
      close();
      return ConnectionState::CLOSED;
      }
    else if (events & POLLNVAL)
      {
      printf("Invalid\n");
      close();
      return ConnectionState::CLOSED;
      }
    else if (events & POLLIN)
      {
      printf("Something to read from server\n");
      // Something logic to read data from server.

      theState = ConnectionState::ESTABLISHED;
      return ConnectionState::ESTABLISHED
      }
    }

  return ConnectionState::NO_CHANGE;
  }

void TCPClient::reconnect()
  {
  if (theFd == -1)
    {
    printf("Trying to reconnect...\r");
    connect();
    }
  }

int TCPClient::getFd() const
  {
  return theFd;
  }

void TCPClient::write()
  {
  std::string payload = "TODO";
  const int result = ReSocket::send(theFd, payload.c_str(), static_cast<int>(rawPayload.size()));
  if (result < 0)
    close();
  }