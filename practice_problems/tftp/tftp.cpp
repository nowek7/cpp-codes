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

void TftpClient::startDownload(const std::string remotePath, const std::string destPath)
{
  std::thread worker(&TftpClient::downloadFile, this, remotePath, destPath);
  worker.detach();
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

      execv(args[0], const_cast<char**>(args));
      exit(0);
    } else {
      waitpid(child, nullptr, 0);

      struct stat buffer;
      if (stat(destPath.c_str(), &buffer) == 0) {
        std::cout << "Downloaded : " << buffer.st_size << "bytes \n" << std::endl;

        const char* args[] = {"/bin/chmod", "+x", "./data/local_temp.pdf", nullptr};
        execv(args[0], const_cast<char**>(args));
      } else {
        std::cout << "File not downloaded !\n";
      }
    }
  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
}