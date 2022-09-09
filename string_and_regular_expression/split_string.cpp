#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

template<class Element>
using tString = std::basic_string<Element, std::char_traits<Element>, std::allocator<Element>>;

template<class Element>
using tStringStream = std::basic_stringstream<Element, std::char_traits<Element>, std::allocator<Element>>;

template<typename Element>
inline std::vector<tString<Element>> split(tString<Element> aText, const Element aSeparator)
{
  auto sStream = tStringStream<Element>{aText};
  auto tokens = std::vector<tString<Element>>{};
  auto token = tString<Element>{};

  while (std::getline(sStream, token, aSeparator))
  {
    if (!token.empty())
    {
      tokens.push_back(token);
    }
  }

  return tokens;
}

template<typename Element>
inline std::vector<tString<Element>> split(tString<Element> aText, const tString<Element> aSeparators)
{
  auto tokens = std::vector<tString<Element>>{};

  size_t pos;
  size_t prevPos = 0;
  while ((pos = aText.find_first_of(aSeparators, prevPos)) != std::string::npos)
  {
    if (pos > prevPos)
    {
      tokens.push_back(aText.substr(prevPos, pos - prevPos));
    }

    prevPos = pos + 1;
  }

  // Add rest of text.
  if (prevPos < aText.length())
  {
    tokens.push_back(aText.substr(prevPos, std::string::npos));
  }

  return tokens;
}

int main()
{
  auto printResult = [](std::vector<std::string>& aText, const std::vector<std::string>& aResult)
  {
    std::copy(aText.begin(), aText.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "-------------------" << std::endl;
    std::copy(aResult.begin(), aResult.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
  };

  {
    std::string text = "this is an example";
    auto result = split(text, ' ');
    std::vector<std::string> expected{"This", "is", "an", "example"};
  }

  {
    std::string text = "My.!-name?-is.-Michal";
    auto result = split(text, std::string(".?!-"));
    std::vector<std::string> expected{"My", "name", "is", "Michal"};
  }
}