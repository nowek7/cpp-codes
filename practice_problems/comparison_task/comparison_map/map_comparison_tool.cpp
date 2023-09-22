#include "map_comparison_tool.hpp"

namespace MAP {
  void accessToElementContainer(std::map<int, int>& container, const int key)
  {
    if (container.at(key)) {
      // Do nothing.
    }
  }

  void modifyContainer(std::map<int, int>& container)
  {
    for (auto& [key, value]: container) {
      container[key] = container[key] + 1;
    }
  }
} // namespace MAP

namespace UNORDERED_MAP {
  void accessToElementContainer(std::unordered_map<int, int>& container, const int key)
  {
    if (container.at(key)) {
      // Do nothing.
    }
  }

  void modifyContainer(std::unordered_map<int, int>& container)
  {
    for (auto& [key, value]: container) {
      container[key] = container[key] + 100;
    }
  }
} // namespace UNORDERED_MAP