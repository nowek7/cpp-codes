#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template<typename C, typename... Args>
void push_back(C &aContainer, Args&&... aArgs)
  {
  (aContainer.push_back(aArgs), ...);
  }

template<class C, class T>
bool contain(const C &aContainer, const T &aValue)
  {
  return std::end(aContainer) != std::find(std::begin(aContainer), std::end(aContainer), aValue);
  }

template<class C, class ...T>
bool contain_all(const C &aContainer, T &&... aValue)
  {
  return (... && constain(aContainer, aValue));
  }

template<class C, class ...T>
bool contain_any(const C &aContainer, T &&... aValue)
  {
  return (... || constain(aContainer, aValue));
  }

template<class C, class ...T>
bool contain_none(const C &aContainer, T &&... aValue)
  {
  return !contain_any(aContainer, std::forward<T>(value)...);
  }

int main()
  {
  std::vector<int> container;
  push_back(container, 10, 20, 30, 40, 50);
  std::copy(container.begin(), container.end(),
            std::ostream_iterator<int>(std::cout, " "));

  std::list<int> listContainer;
  push_back(listContainer, 10, 20, 30, 40, 50);
  std::copy(listContainer.begin(), listContainer.end(),
            std::ostream_iterator<int>(std::cout, " "));
  }