#include <iostream>
#include <string>
#include <set>

int main()
  {
  auto orderOfAppearanceLetter = [](std::string aString)
    {
    std::string output = "";
    auto size = aString.size();
    if (size > 0)
      {
      output += aString.at(0);
      std::set<char> setString = {aString.at(0)};
      for (auto i = 1; i < size; ++i)
        {
        if (setString.find(aString.at(i)) == setString.end())
          {
          setString.insert(aString.at(i));
          output += aString.at(i);
          }
        }
      }

    return output;
    };

  std::cout << orderOfAppearanceLetter("ABCDABCDABCD") << std::endl;
  std::cout << orderOfAppearanceLetter("AAABBBCCCDDD") << std::endl;
  std::cout << orderOfAppearanceLetter("ACBBBAACCDDD") << std::endl;
  }