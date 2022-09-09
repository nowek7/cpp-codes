#include <filesystem>
#include <functional>
#include <iostream>

namespace fs = std::filesystem;

std::vector<fs::path> findFiles(const fs::path& directory, std::function<bool(const fs::path&)> filter)
{
  auto result = std::vector<fs::path>{};
  if (fs::exists(directory))
  {
    for (const auto& entry:
         fs::recursive_directory_iterator(directory, fs::directory_options::follow_directory_symlink))
    {
      if (fs::is_regular_file(entry) && filter(entry))
      {
        result.push_back(entry);
      }
    }
  }

  return result;
}

int main()
{
  // Find files containing prefix 'file_'
  {
    auto results = findFiles(fs::current_path() / "test",
                             [](fs::path const& p)
                             {
                               auto filename = p.wstring();
                               return filename.find(L"file_") != std::wstring::npos;
                             });

    for (const auto& path: results)
    {
      std::cout << path << std::endl;
    }
  }

  // Find files with extension '.cpp'
  {
    auto results =
      findFiles(fs::current_path() / "test", [](const fs::path& path) { return path.extension() == L".dat"; });

    for (const auto& path: results)
    {
      std::cout << path << std::endl;
    }
  }
}