#include <filesystem>
#include <iostream>

void simpleVisitDirectory(const std::filesystem::path &aDirectory)
  {
  // Iterate only the content of a directory without recursively visiting its subdirectories
  if (std::filesystem::exists(aDirectory))
    {
    for (const auto &entry : std::filesystem::directory_iterator(aDirectory))
      {
      auto filename = entry.path().filename();
      if (std::filesystem::is_directory(entry.status()))
        std::cout << "[+]" << filename << std::endl;
      else if (std::filesystem::is_symlink(entry.status()))
        std::cout << "[>]" << filename << std::endl;
      else if (std::filesystem::is_regular_file(entry.status()))
        std::cout << " " << filename << std::endl;
      else
        std::cout << "[?]" << filename << std::endl;
      }
    }
  }

void visitDirectory(const std::filesystem::path &aDirectory, const bool aRecursive = false, const unsigned int level = 0)
  {
  // Iterate all the content of a directory, including its subdirectories, in a
  // structured manner, such as traversing a tree.
  if (std::filesystem::exists(aDirectory) && std::filesystem::is_directory(aDirectory))
    {
    const auto lead = std::string(level * 3, ' ');
    for (const auto &entry : std::filesystem::directory_iterator(aDirectory))
      {
      auto filename = entry.path().filename();
      if (std::filesystem::is_directory(entry.status()))
        {
        std::cout << lead << "[+]" << filename << std::endl;
        if (aRecursive)
          visitDirectory(entry, aRecursive, level + 1);
        }
      else if (std::filesystem::is_symlink(entry.status()))
        std::cout << lead << "[>]" << filename << std::endl;
      else if (std::filesystem::is_regular_file(entry.status()))
        std::cout << lead << " " << filename << std::endl;
      else
        std::cout << lead << "[?]" << filename << std::endl;
      }
    }
  }

void visitDirectoryRecursively(const std::filesystem::path &aDirectory)
  {
  // Iterate all the content of a directory, including its subdirectories, use
  // recursive_directory_iterator when the order of processing the entries
  // does not matter:
  if (std::filesystem::exists(aDirectory) && std::filesystem::is_directory(aDirectory))
    {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(aDirectory))
      {
      auto filename = entry.path().filename();
      if (std::filesystem::is_directory(entry.status()))
        std::cout << "[+]" << filename << std::endl;
      else if (std::filesystem::is_symlink(entry.status()))
        std::cout << "[>]" << filename << std::endl;
      else if (std::filesystem::is_regular_file(entry.status()))
        std::cout << " " << filename << std::endl;
      else
        std::cout << "[?]" << filename << std::endl;
      }
    }
  }

int main ()
  {
  auto path = std::filesystem::path{"/home/mnowak/projects/cpp-codes/miscellaneous"};
  // simpleVisitDirectory(path);
  // visitDirectory(path, true);
  visitDirectoryRecursively(path);
  }