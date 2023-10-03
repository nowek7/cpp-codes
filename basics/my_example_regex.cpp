#include <iostream>
#include <regex>
#include <string>

int main()
{
  const std::string uri = "https://bbc.com:80/en/index.html?lite=true?sasaas=asasa?michal=nowak#Sasasasas";
  std::regex rx {R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?(&?[^&]*=\w+)+)(#?(\w+))?$)"};
  auto matches = std::smatch {};

  if (std::regex_match(uri, matches, rx)) {
    for (int i = 0; i < matches.size(); ++i) {
      std::cout << i << " | " << matches[i].str() << std::endl;
    }

    const auto queries = matches[7].str();
    size_t pos = 0;
    size_t end = queries.find('?', pos);
    while (end != std::string::npos) {
      const std::string query = queries.substr(pos, end);
      std::cout << query << std::endl;
      pos = end + 1;
      end = queries.find('?', pos);
    }
  }

  return 0;
}