#include <algorithm>
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
  auto sStream = tStringStream<Element> {aText};
  auto tokens = std::vector<tString<Element>> {};
  auto token = tString<Element> {};

  while (std::getline(sStream, token, aSeparator)) {
    if (!token.empty()) {
      tokens.push_back(token);
    }
  }

  return tokens;
}

template<typename Element>
inline std::vector<tString<Element>> split(tString<Element> aText, const tString<Element> aSeparators)
{
  auto tokens = std::vector<tString<Element>> {};

  size_t pos;
  size_t prevPos = 0;
  while ((pos = aText.find_first_of(aSeparators, prevPos)) != std::string::npos) {
    if (pos > prevPos) {
      tokens.push_back(aText.substr(prevPos, pos - prevPos));
    }

    prevPos = pos + 1;
  }

  // Add rest of text.
  if (prevPos < aText.length()) {
    tokens.push_back(aText.substr(prevPos, std::string::npos));
  }

  return tokens;
}

std::string LongestWord(const std::string& text)
{
  auto words = split(text, ' ');
  return *std::max_element(words.begin(), words.end(), [](std::string lhs, std::string rhs) {
    return lhs.size() < rhs.size();
  });
}

int main()
{
  std::cout << LongestWord("Keyboard mouse monitor dock station") << '\n';

  return 0;
}