#pragma once

#include <iostream>

struct foo
  {
  foo()
    {
    std::cout << "default constructor" << std::endl;
    }

  foo(const std::string &aText)
    {
    std::cout << "constructor '" << aText << "'" << std::endl;
    }

  foo(const foo &other)
    {
    std::cout << "copy constructor" << std::endl;
    }

  foo(foo&& other)
    {
    std::cout << "move constructor" << std::endl;
    };

  foo& operator=(const foo &other)
    {
    std::cout << "assignment" << std::endl;
    return *this;
    }

  foo& operator=(foo&& other)
    {
    std::cout << "move assignment" << std::endl;
    return *this;
    }

  ~foo()
    {
    std::cout << "destructor" << std::endl;
    }
  };
