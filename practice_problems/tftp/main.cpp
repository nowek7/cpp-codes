#include "tftp.hpp"

#include <iostream>
#include <unistd.h>

int main()
{
  std::cout << "Start program\n";

  TftpClient client("192.168.1.3", 69);
  const bool downloaded = client.startDownload("test.pdf", "./data/local_test.pdf");

  if (downloaded)
  {
    const char* args[] = {"/bin/chmod", "+x", "./data/local_test.pdf", NULL};
    const int res = execv(args[0], const_cast<char**>(args));
    if (res < 0)
    {
      // throw std::runtime_error("Failed to execute command!");
    }
  }

  // unlink("./data/local_test.pdf");

  std::cout << "End program\n";
  return 0;
}