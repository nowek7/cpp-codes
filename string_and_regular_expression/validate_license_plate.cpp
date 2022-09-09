#include <iostream>
#include <regex>
#include <string_view>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string_view, std::string> regexPlates
{
  {"PL", R"(([A-Z]{2,3})\s([A-Z0-9]{4,5}))"},
  {"US", R"([A-Z]{3}-[A-Z]{2} \d{3,4})"}
};

bool validateLicensePlateFormat(std::string_view aPlate)
{
  std::regex rx(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
  return std::regex_match(aPlate.data(), rx);
}

std::vector<std::string> extractLicensePlateNumbers(const std::string& aString)
{
  std::regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})");
  std::smatch match;
  std::vector<std::string> results{};

  for (auto iter = std::sregex_iterator(aString.cbegin(), aString.cend(), rx);
       iter != std::sregex_iterator();
       ++iter)
  {
    if ((*iter)[1].matched)
    {
      results.push_back(iter->str());
    }
  }

  return results;
}

int main()
{
  std::cout << "Correct plate -> ABC-DE 123" << validateLicensePlateFormat("ABC-DE 123") << std::endl;
  std::cout << "Correct plate -> ABC-DE 1234" << validateLicensePlateFormat("ABC-DE 1234") << std::endl;
  std::cout << "Incorrect plate -> ABC-DE 12345" << !validateLicensePlateFormat("ABC-DE 12345") << std::endl;
  std::cout << "Incorrect plate -> abc-de 1234" << !validateLicensePlateFormat("abc-de 1234") << std::endl;

  // TODO: Check error!
  std::vector<std::string> expected{"AAA-AA 123", "ABC-DE 1234", "XYZ-WW 0001"};
  std::string text("AAA-AA 123qwe-ty 1234  ABC-DE 123456..XYZ-WW 0001");
  auto result = extractLicensePlateNumbers(text);
  if (result.size() == expected.size())
  {
    std::cout << "Text \t Result \t Expected" << std::endl;
    for (auto i = 0; i < result.size(); ++i)
    {
      std::cout << text[i] << " \t " << result[i] << " \t " << expected[i] << std::endl;
    }
  }
}