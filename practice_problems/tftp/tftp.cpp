#include "tftp.hpp"

#include <chrono>
#include <exception>
#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

using namespace std::chrono_literals;

TftpClient::TftpClient(const std::string serverIp, const uint16_t port):
  theServerIp(serverIp),
  thePort(port)
{
}

bool TftpClient::startDownload(const std::string remotePath, const std::string destPath)
{
  std::thread worker(&TftpClient::downloadFile, this, remotePath, destPath);
  worker.join();

  {
    std::unique_lock<std::mutex> lock(theLockDownload);
    theDownloaded.wait_for(lock, 15s); // 12s ~ 30MB
  }

  struct stat buffer;
  bool downloaded = false;
  if (stat(destPath.c_str(), &buffer) == 0 && buffer.st_size > 0) {
    std::cout << "File exist!\n";
    downloaded = true;
  }

  if (downloaded) {
    std::cout << "File is downloaded \n";
  } else {
    std::cout << "File is not downloaded \n";
  }

  return downloaded;
}

void TftpClient::downloadFile(const std::string remotePath, const std::string destPath)
{
  try {
    std::unique_lock<std::mutex> lock(theLockStart);

    pid_t child = fork();
    if (child == 0) {
      const char* args[] = {
        "/usr/bin/tftp",
        "-m",
        "binary",
        theServerIp.c_str(),
        std::to_string(thePort).c_str(),
        "-c",
        "get",
        remotePath.c_str(),
        destPath.c_str(),
        nullptr
      };

      const int res = execv(args[0], const_cast<char**>(args));
      if (res < 0) {
        throw std::runtime_error("Failed to execute command!");
      }
      exit(0);
    }
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
}