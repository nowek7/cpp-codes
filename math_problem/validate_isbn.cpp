#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>

int main()
{
  auto validateISBN = [](const std::string aISBN)
  {
    auto size = aISBN.size();
    if (size != 10)
    {
      throw new std::logic_error("Invalid ISBN size!");
    }

    int checksum = 0;
    for (int i = 1; i < 10; i++)
    {
      if (aISBN.at(i - 1) >= '0' && aISBN.at(i - 1) <= '9')
      {
        checksum += i * (static_cast<int>(aISBN.at(i - 1)) - 48);
      }
    }

    checksum %= 11;
    return (checksum == (static_cast<int>(aISBN.at(9)) - 48)) ? "correct!" : "incorrect";
  };

  auto validateISBN_2v = [](std::string aISBN)
  {
    auto valid = false;

    auto limit = 10;
    if ((aISBN.size() == limit) && std::count_if(aISBN.begin(), aISBN.end(), isdigit) == limit)
    {
      auto filter = [&limit](int aTotal, char aSign)
      {
        return aTotal + (limit--) * (aSign - '0');
      };

      const auto checksum = std::accumulate(aISBN.begin(), aISBN.end(), 0, filter);
      valid = !(checksum % 11);
    }

    return valid;
  };

  const std::string ISBN{"0306406152"};
  std::cout << "ISBN: " << ISBN << " is " << std::boolalpha << validateISBN_2v(ISBN) << std::endl;
}