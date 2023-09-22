#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

enum class FILE_STATUS
{
  DOWNLOADED = 0,
  NOT_DOWLOADED
};

enum class CHMOD : uint
{
  EXEC = 0
};

FILE_STATUS
check(const std::string& path)
{
  struct stat buffer;
  if (stat(path.c_str(), &buffer) != 0) {
    std::cout << "Failed to download file" << '\n';
    return FILE_STATUS::NOT_DOWLOADED;
  } else {
    if (buffer.st_size == 0) {
      std::cout << "Failed to download file!" << '\n';
      return FILE_STATUS::DOWNLOADED
    }
  }
}

void setPermission(const std::string& path, CHMOD mod)
{
  const char* args[] = {"/usr/bin/chmod", "+x", path.c_str(), nullptr};
  execv(args[0], const_cast<char**>(args));
}