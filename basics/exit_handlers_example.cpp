#include <cstdlib>
#include <iostream>

void exitHandler_1()
{
  std::cout << "Exit handler 1" << std::endl;
}

void exitHandler_2()
{
  std::cout << "Exit handler 2" << std::endl;
}

void quickExitHandler_1()
{
  std::cout << "Quick exit handler 1" << std::endl;
}

void quickExitHandler_2()
{
  std::cout << "Quick exit handler 2" << std::endl;
}

struct static_foo
{
  ~static_foo()
  {
    std::cout << "Static foo destroyed!" << std::endl;
  }

  static static_foo* instance()
  {
    static static_foo obj;
    return &obj;
  }
};

int main()
{
  {
    std::atexit(exitHandler_1);
    static_foo::instance();
    std::atexit(exitHandler_2);
    std::atexit([]() {
      std::cout << "Exit handler 3" << std::endl;
    });

    // std::exit(42);    // exit handlers are invoked
    // std::terminate(); // exit handlers are not invoked
  }

  {
    std::at_quick_exit(quickExitHandler_1);
    std::at_quick_exit(quickExitHandler_2);
    std::at_quick_exit([]() {
      std::cout << "Quick exit handler 3" << std::endl;
    });

    // std::quick_exit(42); // exit handlers are invoked
    // std::terminate();    // exit handlers are not invoked
  }
}