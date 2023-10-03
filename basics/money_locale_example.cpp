#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std::string_literals;

void testMoney()
{
  std::vector<std::string> locale_names {""s,
#ifdef _WIN32
    "English_US.1252"s,
    "English_UK.1252"s,
    "Japanese_Japan.932"s,
    "French_France.1252"s,
    "German_Germany.1252"s,
    "Romanian_Romania.1250"s
#else
    "en_US.utf8"s,
    "en_GB.utf8"s,
    "ja_JP.utf8"s,
    "fr_FR.utf8"s,
    "de_DE.utf8"s,
    "ro_RO.utf8"s
#endif
  };

  long double mon = 12345.67;

  std::cout << std::showbase << std::put_money(mon) << " or " << std::put_money(mon, true) << std::endl;

  for (const auto& locale: locale_names) {
    std::cout.imbue(std::locale(locale));
    std::cout << std::showbase << locale << ": " << std::put_money(mon) << " or " << std::put_money(mon, true)
              << std::endl;
  }

  std::cout.imbue(std::locale::classic());
  std::vector<std::string> texts {"$123.46"s, "123.46 USD"s, "USD 123.46"s, "123.46"s};

  for (const auto& text: texts) {
    std::cout << std::endl << "parsing " << std::quoted(text) << std::endl;
    for (const auto& locale: locale_names) {
      std::istringstream stext(text);
      long double value;

      stext.imbue(std::locale(locale));
      stext >> std::get_money(value);

      std::cout << locale << ": ";
      if (stext) {
        std::cout << value << std::endl;
      } else {
        std::cout << "failed" << std::endl;
      }
    }
  }
}

void writeMoney()
{
#ifdef _WIN32
  auto locUK = std::locale {"English_UK.1252"};
#else
  auto locUK = std::locale {"en_GB.utf8"};
#endif

  long double mon = 12345.67;

  std::cout.imbue(locUK);

  std::cout << std::put_money(mon) << std::endl;
  std::cout << std::showbase << std::put_money(mon) << std::endl;
  std::cout << std::showbase << std::put_money(mon, true) << std::endl;

  std::string smon = "12345.67";

  std::cout << std::put_money(smon) << std::endl;
  std::cout << std::showbase << std::put_money(smon) << std::endl;
  std::cout << std::showbase << std::put_money(smon, true) << std::endl;

  std::cout.imbue(std::locale::classic());
}

void readMoney()
{
  {
    auto text = "$123.45 123.45 USD"s;
    std::istringstream stext(text);

#ifdef _WIN32
    auto loc_us = std::locale {"English_US.1252"};
#else
    auto loc_us = std::locale {"en_US.utf8"};
#endif

    stext.imbue(loc_us);

    long double v1;
    std::string v2;

    stext >> std::get_money(v1) >> std::get_money(v2);
    // v1 = 12345, v2 = "12345"

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;

    stext.seekg(0, std::ios::beg);
    stext >> std::get_money(v1, true) >> std::get_money(v2, true);
    // v1 = 0, v2 = "12345"

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
  }
}

int main()
{
  testMoney();

  writeMoney();
  readMoney();
}