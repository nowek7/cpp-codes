#pragma once

#include <condition_variable>
#include <mutex>

class TftpClient
{
public:
  TftpClient(const std::string serverIp, const uint16_t port = 69);
  TftpClient(const TftpClient&) = delete;
  TftpClient(const TftpClient&&) = delete;
  ~TftpClient() = default;

  TftpClient& operator=(const TftpClient&) = delete;

  void startDownload(const std::string remotePath, const std::string destPath);

private:
  std::string theServerIp;
  uint16_t thePort;

  std::mutex theLockStart;
  std::mutex theLockDownload;
  std::condition_variable theDownloaded;

  void downloadFile(const std::string remotePath, const std::string destPath);
};