#include <map>
#include <unordered_map>

namespace MAP {
  void accessToElementContainer(std::map<int, int>& container, const int key);
  void modifyContainer(std::map<int, int>& container);
} // namespace MAP

namespace UNORDERED_MAP {
  void accessToElementContainer(std::unordered_map<int, int>& container, const int key);
  void modifyContainer(std::unordered_map<int, int>& container);
} // namespace UNORDERED_MAP
