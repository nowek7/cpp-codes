#include <iostream>
#include <optional>
#include <regex>
#include <string>

struct URI
  {
  std::string theProtocol;
  std::string theDomain;
  std::optional<int> thePort;
  std::optional<std::string> thePath;
  std::optional<std::string> theQuery;
  std::optional<std::string> theFragment;
  };

std::optional<URI> parseURI(std::string aURI)
  {
  std::regex rx(R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)");
  auto matches = std::smatch{};

  if (std::regex_match(aURI, matches, rx))
    {
    if (matches[1].matched == matches[2].matched)
      {
      URI url;
      url.theProtocol = matches[1].str();
      url.theDomain = matches[2].str();

      if (matches[4].matched)
        url.thePort = std::stoi(matches[4].str());

      if (matches[5].matched)
        url.thePath = matches[5];

      if (matches[7].matched)
        url.theQuery = matches[7];

      if (matches[9].matched)
          url.theFragment = matches[9];

      return url;
      }
    }

  return {};
  }

int main()
  {
  auto p1 = parse_uri("https://en.cppreference.com/w/cpp/utility/optional");

  auto p2 = parse_uri("https://bbc.com:80/en/index.html?lite=true#ui");
  }

