#include <filesystem>
#include <iostream>

std::string getDirectoryEntryPattern(const std::filesystem::directory_entry& entry)
{
  if (std::filesystem::is_directory(entry.status()))
  {
    return "[+]";
  }
  else if (std::filesystem::is_symlink(entry.status()))
  {
    return "[>]";
  }
  else if (std::filesystem::is_regular_file(entry.status()))
  {
    return " ";
  }
  else
  {
    return "[?]";
  }
}

void simpleVisitDirectory(const std::filesystem::path& directory)
{
  // Iterate only the content of a directory without recursively visiting its
  // subdirectories
  if (std::filesystem::exists(directory))
  {
    for (const auto& entry: std::filesystem::directory_iterator(directory))
    {
      const auto filename = entry.path().filename();
      const auto pattern = getDirectoryEntryPattern(entry);
      std::cout << pattern << filename << std::endl;
    }
  }
}

void visitDirectory(const std::filesystem::path& directory,
                    bool aRecursive = false,
                    unsigned int level = 0)
{
  // Iterate all the content of a directory, including its subdirectories, in a
  // structured manner, such as traversing a tree.
  if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
  {
    const auto lead = std::string(level * 3, ' ');
    for (const auto& entry: std::filesystem::directory_iterator(directory))
    {
      auto filename = entry.path().filename();
      const auto pattern = getDirectoryEntryPattern(entry);

      std::cout << pattern << filename << std::endl;
      if (std::filesystem::is_directory(entry.status()) &&
          aRecursive)
      {
        visitDirectory(entry, aRecursive, level + 1);
      }
    }
  }
}

void visitDirectoryRecursively(const std::filesystem::path& directory)
{
  // Iterate all the content of a directory, including its subdirectories, use
  // recursive_directory_iterator when the order of processing the entries
  // does not matter:
  if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
  {
    for (const auto& entry: std::filesystem::recursive_directory_iterator(directory))
    {
      auto filename = entry.path().filename();
      const auto pattern = getDirectoryEntryPattern(entry);
      std::cout << pattern << filename << std::endl;
    }
  }
}

int main()
{
  auto path = std::filesystem::path{"/home/mnowak/Desktop"};
  // simpleVisitDirectory(path);
  // visitDirectory(path, true);
  visitDirectoryRecursively(path);
}