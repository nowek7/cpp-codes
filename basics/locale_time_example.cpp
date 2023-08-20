#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

void writeTime()
  {
  auto now = std::chrono::system_clock::now();
  auto stime = std::chrono::system_clock::to_time_t(now);
  auto ltime = std::localtime(&stime);

  #ifdef _WIN32
    auto locUK = std::locale{ "English_UK.1252" };
  #else
    auto locUK = std::locale{ "en_GB.utf8" };
  #endif

  std::cout.imbue(locUK);

  std::cout << std::put_time(ltime, "%c") << std::endl;
  std::cout << std::put_time(ltime, "%Y-%m-%d") << std::endl;
  std::cout << std::put_time(ltime, "%F") << std::endl;
  std::cout << std::put_time(ltime, "%T") << std::endl;
  std::cout << std::put_time(ltime, "%F %T") << std::endl;
  std::cout << std::put_time(ltime, "%FT%T%z") << std::endl;
  std::cout << std::put_time(ltime, "%V") << std::endl;
  std::cout << std::put_time(ltime, "%Y-W%V") << std::endl;
  std::cout << std::put_time(ltime, "%Y-W%V-%u") << std::endl;
  std::cout << std::put_time(ltime, "%Y-%j") << std::endl;

  std::cout.imbue(std::locale::classic());
  }

void readTime()
  {
    {
      std::istringstream stext("2016-12-04T05:26:47+0900");

      auto time = std::tm{};
      stext >> std::get_time(&time, "%Y-%m-%dT%H:%M:%S");
      if (stext.fail())
        std::cout << "Parsing failed" << std::endl;
      else
        std::cout << std::put_time(&time, "%c") << std::endl;
    }

    {
      std::istringstream stext("Sun 04 Dec 2016 05:35:30 JST");

      #ifdef _WIN32
        auto locUK = std::locale{ "English_UK.1252" };
      #else
        auto locUK = std::locale{ "en_GB.utf8" };
      #endif

      stext.imbue(locUK);
      auto time = std::tm{};

      stext >> std::get_time(&time, "%c");
      if (stext.fail())
        std::cout << "Parsing failed" << std::endl;
      else
        std::cout << std::put_time(&time, "%c") << std::endl;
    }
  }

int main()
  {
  writeTime();
  readTime();
  }
