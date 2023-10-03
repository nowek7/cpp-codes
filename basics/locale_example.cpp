#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
#include <vector>

int main()
{
  {
    auto loc_def = std::locale {};

#ifdef _WIN32
    auto loc_us = std::locale {"English_US.1252"};
#else
    auto loc_us = std::locale {"en_US.utf8"};
#endif

    auto loc1 = std::locale {loc_def, new std::collate<wchar_t>};
    auto loc2 = std::locale {loc_def, loc_us, std::locale::collate};
  }

  auto now = std::chrono::system_clock::now();
  auto stime = std::chrono::system_clock::to_time_t(now);
  auto ltime = std::localtime(&stime);

  std::vector<std::string> names {"John", "adele", "Vivind", "Francois", "Robert", "Uwe"};
  auto sortAndPrint = [](std::vector<std::string> v, const std::locale& loc) {
    std::sort(v.begin(), v.end(), loc);
    for (auto const& s: v) {
      std::cout << s << ' ';
    }
    std::cout << std::endl;
  };

  {
#ifdef _WIN32
    auto loc = std::locale("German_Germany.1252");
#else
    auto loc = std::locale("de_DE.utf8");
#endif

    std::cout.imbue(loc);
    std::cout << 1000.50 << std::endl;
    std::cout << std::showbase << std::put_money(1050) << std::endl;
    std::cout << std::put_time(ltime, "%c") << std::endl;

    sortAndPrint(names, loc);
  }

  {
    auto loc = std::locale("");
    std::cout.imbue(loc);

    std::cout << 1000.50 << std::endl;
    std::cout << std::showbase << std::put_money(1050) << std::endl;
    std::cout << std::put_time(ltime, "%c") << std::endl;

    sortAndPrint(names, loc);
  }

  {
#ifdef _WIN32
    std::locale::global(std::locale("Swedish_Sweden.1252"));
#else
    std::locale::global(std::locale("sv_SE.utf8"));
#endif

    auto loc = std::locale {};
    std::cout.imbue(loc);

    std::cout << 1000.50 << std::endl;
    std::cout << std::showbase << std::put_money(1050) << std::endl;
    std::cout << std::put_time(ltime, "%c") << std::endl;

    sortAndPrint(names, loc);
  }

  {
    auto loc = std::locale::classic();
    std::cout.imbue(loc);

    std::cout << 1000.50 << std::endl;
    std::cout << std::showbase << std::put_money(1050) << std::endl;
    std::cout << std::put_time(ltime, "%c") << std::endl;

    sortAndPrint(names, loc);
  }
}
