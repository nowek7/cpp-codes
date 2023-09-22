#include "map_comparison_tool.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <unordered_map>

namespace {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> uid(0, 100);
} // namespace

std::map<int, int> generateMapContainer(const int& size)
{
  std::map<int, int> container;
  for (int i = 0; i < size; ++i) {
    container.insert({i, uid(generator)});
  }
  return container;
}

std::unordered_map<int, int> generateUnorderedMapContainer(const int& size)
{
  std::unordered_map<int, int> container;
  for (int i = 0; i < size; ++i) {
    container.insert({i, uid(generator)});
  }
  return container;
}

int main()
{
  const std::string header = "elements,access,modify\n";

  {
    std::ofstream oFile("map.csv");
    if (oFile) {
      std::ostringstream oss;
      oss << header;
      for (auto size: {100, 1000, 10000, 100000, 500000}) {
        auto map = generateMapContainer(size);

        auto accessFun = [&]() {
          MAP::accessToElementContainer(map, size / 2);
        };
        auto accessTime = performanceTimer<>::duration(accessFun);

        auto modifyFun = [&]() {
          MAP::modifyContainer(map);
        };
        auto modifyTime = performanceTimer<>::duration(modifyFun);

        oss << size << "," << accessTime.count() << "," << modifyTime.count() << "\n";
      }
      const auto content = oss.str();
      oFile.write(content.c_str(), content.size());
    }
  }

  {
    std::ofstream oFile("unordered_map.csv");
    if (oFile) {
      std::ostringstream oss;
      oss << header;
      for (auto size: {100, 1000, 10000, 100000, 500000}) {
        auto unorderedMap = generateUnorderedMapContainer(size);
        auto accessFun = [&]() {
          UNORDERED_MAP::accessToElementContainer(unorderedMap, size / 2);
        };
        auto accessTime = performanceTimer<>::duration(accessFun);

        auto modifyFun = [&]() {
          UNORDERED_MAP::modifyContainer(unorderedMap);
        };
        auto modifyTime = performanceTimer<>::duration(modifyFun);

        oss << size << "," << accessTime.count() << "," << modifyTime.count() << "\n";
      }

      const auto content = oss.str();
      oFile.write(content.c_str(), content.size());
    }
  }

  return 0;
}
