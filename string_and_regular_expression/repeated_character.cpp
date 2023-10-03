// Type your code here, or load an example.
#include <array>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

constexpr int ASCII_CODE_A = 97;
constexpr int ALPHABET_SIZE = 26;

char repeatedCharacter(std::string sequence)
{
  std::array<int, ALPHABET_SIZE> occurences = {0};
  for (char letter: sequence) {
    const int idx = static_cast<int>(letter) - ASCII_CODE_A;
    if (++occurences[idx] == 2) {
      return letter;
    }
  }

  return 's';
}

int main()
{
  {
    std::string text = "abcdd";
    std::cout << repeatedCharacter(text) << '\n';
  }

  {
    std::string text = "abcdbd";
    std::cout << repeatedCharacter(text) << '\n';
  }

  {
    std::string text = "abcddbd";
    std::cout << repeatedCharacter(text) << '\n';
  }

  return 0;
}