#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

template<class Element>
using tString = std::basic_string<Element, std::char_traits<Element>, std::allocator<Element>>;

template<class Element>
using tStringStream = std::basic_stringstream<Element, std::char_traits<Element>, std::allocator<Element>>;

template<class Element>
tString<Element> capitalize(const tString<Element> &aText)
  {
  tStringStream<Element> capitalized;

  bool newWord = true;
  for (const auto &char_: aText)
    {
    newWord = newWord || std::ispunct(char_) || std::isspace(char_);
    if (std::isalpha(char_))
      {
      if (newWord)
        {
        capitalized << static_cast<Element>(std::toupper(char_));
        newWord = false;
        }
      else
        capitalized << static_cast<Element>(std::tolower(char_));
      }
    else
      capitalized << char_;
    }

  return capitalized.str();
  }

  int main()
    {
    auto printResult = [](std::string &aText, const std::string &aExpected)
      {
      std::cout << "Text -> " <<  aText << std::endl;
      std::cout << "Expected -> " << aExpected << std::endl;
      std::cout << "Capitalized -> " << capitalize(aText) << std::endl;
      };

      {
      std::string text = "THIS IS an ExamplE, should wORk!";
      std::string expected = "This Is An Example, Should Work!";

      printResult(text, expected);
      }

      {
      std::string text = "my name is Michal!";
      std::string expected = "My Name Is Michal!";

      printResult(text, expected);
      }
    }