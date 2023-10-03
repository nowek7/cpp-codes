#include "tftp.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>

int main()
{
  std::cout << "Start program\n";

  TftpClient client("192.168.1.4", 69);
  client.startDownload("temp.pdf", "./data/local_temp.pdf");

  std::this_thread::sleep_for(std::chrono::seconds(20));

  std::cout << "End program\n";
  return 0;
}