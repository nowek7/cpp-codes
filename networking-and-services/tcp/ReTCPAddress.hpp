#pragma once

#include <string>

struct TCPAddress
  {
  std::string theHost;
  uint16_t thePort{ 0 };

  bool isSet() const
    {
    return theHost.size() > 0 && thePort > 0;
    }
  };

