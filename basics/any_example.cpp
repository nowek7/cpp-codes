#include <any>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std::string_literals;

void log(const std::any &aValue)
  {
  if (aValue.has_value())
    {
    auto const &tv = aValue.type();
    if (tv == typeid(int))
      std::cout << std::any_cast<int>(aValue) << std::endl;
    else if (tv == typeid(std::string))
      std::cout << std::any_cast<std::string>(aValue) << std::endl;
    else if (tv == typeid(std::chrono::time_point<std::chrono::system_clock>))
      {
      auto t = std::any_cast<std::chrono::time_point<std::chrono::system_clock>>(aValue);
      auto now = std::chrono::system_clock::to_time_t(t);
      std::cout << std::put_time(std::localtime(&now), "%F %T") << std::endl;
      }
    else
      std::cout << "Unexpected value type" << std::endl;
    }
  else
    std::cout << "(Empty)" << std::endl;
  }

inline bool isInteger(const std::any &aValue)
  {
  return aValue.type() == typeid(int);
  }

int main()
  {
    {
      std::any value(42);  // integer     12
      value = 42.0;        // double      12.0
      value = "42"s;       // std::string "12"
    }

    {
    std::cout << "=================2=================" << std::endl;
    auto lambda_test = [](const std::any &anyValue)
      {
      if (anyValue.has_value())
        std::cout << "has value" << std::endl;
      else
        std::cout << "no value" << std::endl;
      };

      std::any value;
      lambda_test(value);   // no value

      value = 42;
      lambda_test(value);   // has value

      value.reset();
      lambda_test(value);   // no value
    }

    {
      std::cout << "=================3=================" << std::endl;
      std::any value = 42.0;
      try
        {
        auto d = std::any_cast<double>(value);
        std::cout << d << std::endl;
        }
      catch (const std::bad_any_cast  &ex)
        {
        std::cout << ex.what() << std::endl;
        }

      try
        {
        auto pd = std::any_cast<double>(&value);
        std::cout << *pd << std::endl;
        }
      catch (const std::bad_any_cast &ex)
        {
        std::cout << ex.what() << std::endl;
        }

      try
        {
        auto i = std::any_cast<int>(value);
        std::cout << i << std::endl;
        }
      catch (const std::bad_any_cast &ex)
        {
        std::cout << ex.what() << std::endl;
        }


      value = "sample"s;
      try
        {
        auto s = std::any_cast<std::string>(value);
        std::cout << s << std::endl;
        }
      catch (const std::bad_any_cast &ex)
        {
        std::cout << ex.what() << std::endl;
        }

      value = std::vector<int>{ 1, 1, 2, 3, 5, 8 };
      try
        {
        auto values = std::any_cast<std::vector<int>>(value);
        for (auto &entry : values)
          std::cout << entry << std::endl;
        }
      catch (const std::bad_any_cast &ex)
        {
        std::cout << ex.what() << std::endl;
        }
    }

    {
      std::cout << "=================4=================" << std::endl;
      log(std::any{}); // (empty)
      log(12); // 12
      log("12"s); // 12
      log(12.0); // unexpected value type
      log(std::chrono::system_clock::now());  // 2016-10-30 22:42:57
    }

    {
      std::cout << "=================5=================" << std::endl;
      std::vector<std::any> values;
      values.push_back(std::any{});
      values.push_back(12);
      values.push_back("12"s);
      values.push_back(12.0);
      values.push_back(std::chrono::system_clock::now());

      for (const auto &entry : values)
        log(entry);
    }

    {
      std::cout << "=================6=================" << std::endl;
      struct foo
        {
        foo() = default;
        foo(const foo&) = delete;
        };

      foo f;
      // std::any value = f; // error
    }
  }