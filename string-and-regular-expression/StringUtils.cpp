#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace string
  {
  template <class CharT>
  using tString = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  template <class CharT>
  using tStringStream = std::basic_stringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  namespace mutableString
    {
    template<typename CharT>
    inline void toUpper(tString<CharT> &aText)
      {
      std::transform(std::begin(aText), std::end(aText), std::begin(aText), toupper);
      }

    template<typename CharT>
    inline void toLower(tString<CharT> &aText)
      {
      std::transform(std::begin(aText), std::end(aText), std::begin(aText), tolower);
      }

    template<typename CharT>
    inline void reverse(tString<CharT> &aText)
      {
      std::reverse(std::begin(aText), std::end(aText));
      }

    template<typename CharT>
    inline void trim(tString<CharT> &aText)
      {
      auto first{ aText.find_first_not_of(' ') };
      auto last{ aText.find_last_not_of(' ') };
      aText = aText.substr(first, (last - first + 1));
      }

    template<typename CharT>
    inline void trimLeft(tString<CharT> &aText)
      {
      auto first{ aText.find_first_not_of(' ') };
      aText = aText.substr(first, aText.size() - first);
      }

    template<typename CharT>
    inline void trimRight(tString<CharT> &aText)
      {
      auto last{ aText.find_last_not_of(' ') };
      aText = aText.substr(0, last + 1);
      }
    } // namespace mutableString

  template<typename CharT>
  inline tString<CharT> toUpper(tString<CharT> aText)
    {
    std::transform(std::begin(aText), std::end(aText), std::begin(aText), toupper);
    return aText;
    }

  template<typename CharT>
  inline tString<CharT> toLower(tString<CharT> aText)
    {
    std::transform(std::begin(aText), std::end(aText), std::begin(aText), tolower);
    return aText;
    }

  template<typename CharT>
  inline tString<CharT> reverse(tString<CharT> aText)
    {
    std::reverse(std::begin(aText), std::end(aText));
    return aText;
    }

  template<typename CharT>
  inline tString<CharT> trim(const tString<CharT> &aText)
    {
    auto first{ aText.find_first_not_of(' ') };
    auto last{ aText.find_last_not_of(' ') };
    return aText.substr(first, (last - first + 1));
    }

  template<typename CharT>
  inline tString<CharT> trimLeft(const tString<CharT> &aText)
    {
    auto first{ aText.find_first_not_of(' ') };
    return aText.substr(first, aText.size() - first);
    }

  template<typename CharT>
  inline tString<CharT> trimRight(const tString<CharT> &aText)
    {
    auto last{ aText.find_last_not_of(' ') };
    return aText.substr(0, last + 1);
    }

  template<typename CharT>
  inline tString<CharT> trim(const tString<CharT> &aText, const tString<CharT> &aChars)
    {
    auto first{ aText.find_first_not_of(aChars) };
    auto last{ aText.find_last_not_of(aChars) };
    return aText.substr(first, (last - first + 1));
    }

  template<typename CharT>
  inline tString<CharT> trimLeft(const tString<CharT> &aText, const tString<CharT> &chars)
    {
    auto first{ aText.find_first_not_of(chars) };
    return aText.substr(first, aText.size() - first);
    }

  template<typename CharT>
  inline tString<CharT> trimRight(const tString<CharT> &aText, const tString<CharT> & aChars)
    {
    auto last{ aText.find_last_not_of(aChars) };
    return aText.substr(0, last + 1);
    }

  template<typename CharT>
  inline tString<CharT> remove(tString<CharT> aText, const CharT aChar)
    {
    auto start = std::remove_if(std::begin(aText), std::end(aText), [=](CharT const c) {return c == aChar; });
    aText.erase(start, std::end(aText));
    return aText;
    }

  template<typename CharT>
  inline std::vector<tString<CharT>> split(tString<CharT> aText, const CharT aDelimiter)
    {
    auto sStream = tStringStream<CharT>{aText};
    auto tokens = std::vector<tString<CharT>>{};
    auto token = tString<CharT>{};
    while (std::getline(sStream, token, aDelimiter))
      {
      if (!token.empty())
        tokens.push_back(token);
      }

    return tokens;
    }
  } // namespace string

int main()
  {
  using namespace std::string_literals;

  {
    auto str = "this is not UPPERCASE"s;
    std::cout << str << " -> " << string::toUpper(str) << std::endl;
  }

  {
    auto str = "THIS IS NOT lowercase"s;
    std::cout << str << " -> " << string::toLower(str) << std::endl;
  }

  {
    auto str = "cookbook"s;
    std::cout << str << " -> " << string::reverse(str) << std::endl;
  }

  {
    auto str{ "   this is an example   "s };
    std::cout << "Trim_" << str << " ->_" << string::trim(str) << "_" << std::endl;
    std::cout << "Trim left_" << str << " ->_" << string::trimLeft(str) << "_" << std::endl;
    std::cout << "Trim right_" << str << " ->_" << string::trimRight(str) << "_" << std::endl;
  }

  {
    auto chars{ " !%\n\r"s };
    auto str{ "!!  this % needs a lot\rof trimming  !\n"s };

    std::cout << "Trim_" << str << " ->_" << string::trim(str, chars) << "_" << std::endl;
    std::cout << "Trim left_" << str << " ->_" << string::trimLeft(str, chars) << "_" << std::endl;
    std::cout << "Trim right_" << str << " ->_" << string::trimRight(str, chars) << "_" << std::endl;
  }

  {
    auto str{ "must remove all * from aText**"s };
    std::cout << "Remove " << str << " ->_" << string::remove(str, '*') << std::endl;

    auto text{ "must remove all ! from aText!*"s };
    std::cout << "Remove " << text << " ->_" << string::remove(text, '!') << std::endl;
  }

  {
    auto text{ "this aText will be split   "s };
    auto tokens = string::split(text, ' ');
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it)
      std::cout << *it << std::endl;

    auto tokens2{ string::split(""s, ' ') };
    for (auto it = tokens2.cbegin(); it != tokens2.cend(); ++it)
      std::cout << *it << std::endl;
  }
}