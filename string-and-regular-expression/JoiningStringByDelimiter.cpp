#include <array>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>

template<typename Iterator>
std::string joinStrings(Iterator aBegin, Iterator aEnd, const char *aDelimiter)
  {
  std::ostringstream osStream;
  std::copy(aBegin, aEnd - 1, std::ostream_iterator<std::string>(osStream, aDelimiter));
  osStream << *(aEnd - 1) << "\n";

  return osStream.str();
  }

template<typename C>
std::string joinStrings(const C &aContainer, const char *aSeparator)
  {
  if (aContainer.empty())
    return std::string{};

  return joinStrings(std::begin(aContainer), std::end(aContainer), aSeparator);
  }

int main()
  {
  using namespace std::string_literals;

    {
    std::vector<std::string> strings{"This", "is", "an", "example"};
    std::cout << joinStrings(strings, " ");
    }

    {
    std::vector<std::string> strings{"1", "2", "3", "4"};
    std::cout << joinStrings(strings, ", ");
    }

    {
    std::vector<std::string> strings{};
    std::cout << joinStrings(strings, " ");
    }

    {
    std::array<std::string, 4> strings{"I", "am", "Michal", "!"};
    std::cout << joinStrings(strings, " ");
    }

    {
    std::array<std::string, 5> strings{"Hello", "how", "are", "you", "?"};
    std::cout << joinStrings(strings, "-");
    }
  }