#include <cstdlib>
#include <iostream>
#include <string>

auto allocated = std::size_t {0};

// Overload operator new and delete to track allocations
auto operator new(size_t size) -> void*
{
  void* p = std::malloc(size);
  allocated += size;
  return p;
}

auto operator delete(void* p) noexcept -> void
{
  return std::free(p);
}

auto main() -> int
{
  allocated = 0;
  // auto s = std::string{""}; // Elaborate with different string sizes
  auto s = std::string {"12345678901234567890123"};
  std::cout << "stack space = " << sizeof(s) << ", heap space = " << allocated << ", capacity = " << s.capacity()
            << '\n';
}