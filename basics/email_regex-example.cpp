#include <iostream>
#include <iomanip>
#include <string>
#include <regex>

using namespace std::string_literals;

template <typename CharT>
using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

template <typename CharT>
bool isValidFormat(tstring<CharT> const & pattern, tstring<CharT> const & text)
  {
  auto rx = std::basic_regex<CharT>{ pattern, std::regex_constants::icase };
  return std::regex_match(text, rx);
  }

bool isValidEmailFormat(std::string const & email)
  {
  auto rx = std::regex{ R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s, std::regex_constants::icase };
  return std::regex_match(email, rx);
  }

bool isValidEmailFormatW(std::wstring const & text)
  {
  return isValidFormat(LR"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s, text);
  }

std::tuple<bool, std::string, std::string, std::string> isValidEmailFormatWithResult(std::string const & email)
  {
  auto rx = std::regex{ R"(^([A-Z0-9._%+-]+)@([A-Z0-9.-]+)\.([A-Z]{2,})$)"s, std::regex_constants::icase };
  auto result = std::smatch{};
  auto success = std::regex_match(email, result, rx);

  return std::make_tuple(
    success,
    success ? result[1].str() : ""s,
    success ? result[2].str() : ""s,
    success ? result[3].str() : ""s);
   }

int main()
  {
  auto ltest = [](std::string const & email)
    {
    std::cout << std::setw(30) << std::left
      << email << " : "
      << (isValidEmailFormat(email) ? "valid" : "invalid")
    << std::endl;
    };

  auto ltest2 = [](auto const & email)
    {
    std::wcout << std::setw(30) << std::left
      << email << L" : "
      << (isValidEmailFormatW(email) ? L"valid" : L"invalid")
    << std::endl;
    };

  auto ltest3 = [](std::string const & email)
    {
    auto valid{ false };
    auto localpart = std::string{};
    auto hostname = std::string{};
    auto dnsLabel = std::string{};

    std::tie(valid, localpart, hostname, dnsLabel) = isValidEmailFormatWithResult(email);

    std::cout << std::setw(30) << std::left
      << email << " : "
      << std::setw(10) << (valid ? "valid" : "invalid")
      << std::endl << "   local = " << localpart << "; domain=" << hostname << "; dns = " << dnsLabel
      << std::endl;
    };

  ltest("michal@DOMAIL.CO.PL"s);
  ltest("michal@DOMAIL.INFO"s);
  ltest("M.I.C.H_A.L@DOMAIN.INFO"s);
  ltest("ROOT@LOCALHOST"s);

  ltest2(L"michael.DOE@DOMAIN.COM"s);
  ltest2(L"michaelDOE@DOMAIL.CO.UK"s);
  ltest2(L"michaelDOE@DOMAIL.INFO"s);
  ltest2(L"J.O.H.N_D.O.E@DOMAIN.INFO"s);
  ltest2(L"ROOT@LOCALHOST"s);
  ltest2(L"joe.doe@domain.com"s);

  ltest3("JOE.doe@DOMAIN.COM"s);
  ltest3("ROOT@LOCALHOST"s);
  }