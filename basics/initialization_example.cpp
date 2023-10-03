#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

const char* varable = "sss";

int main()
{
  // Initialization

  {
    // Copy initialization
    int var_name = 5;
  }

  {
    // Value initializtion
    int var_name {5};
  }

  {
    // Direct initialization
    std::string var_name("name");
  }

  {
    // List initlization
    auto var_name = {1, 2, 3};
  }

  {
    // Aggregate initialization
    char vars[3] = {'a', 'b', 'c'};
  }

  {
    int var_name = 10;

    // Reference initialization
    int& even_number = var_name;
  }

  {
    struct simple_struct
    {
      int a;
    };

    simple_struct s {.a = 10};
  }

  {
    struct simple_struct
    {
      int a;
    };

    std::vector<simple_struct> entries = {{.a = 10}, {.a = 15}, {.a = 16}};

    // Before C++17
    for (const auto& entry: entries) {
      const auto& id = entry.a;
      std::cout << entry.a << std::endl;
    }

    // >= C++17
    for (const auto& [id]: entries) {
      std::cout << id << std::endl;
    }
  }

  return 0;
}