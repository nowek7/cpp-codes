#include <iostream>
#include <regex>
#include <string>
#include <string_view>

std::string convertDateString(std::string_view aText)
  {
  auto rx = std::regex{R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))" };

  return std::regex_replace(aText.data(), rx, R"($5-$3-$1)");
  }

int main()
  {
  std::cout << "Today: is 30.07.2020" << std::endl;
  std::cout << convertDateString("Today: is 30.07.2020") << std::endl;
  }