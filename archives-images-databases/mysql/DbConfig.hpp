#pragma once

#include <string>

struct DbConfig
  {
  std::string theHost;
  std::string theUser;
  std::string thePassword;
  std::string theDatabase;
  int thePort;

  bool isSet() const
    {
    return theHost.size() > 0 &&
           theUser.size() > 0 &&
           thePassword.size() > 0 &&
           thePort > 0;
    }
  };