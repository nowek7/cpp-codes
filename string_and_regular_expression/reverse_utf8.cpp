#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

void reverseUtf8(std::string& original)
{
  int eos = original.length();
  while (eos > 0) {
    char c = original.front();
    int characterBytes;
    switch ((c & 0xF0) >> 4) {
      case 0xC:
      case 0xD: /* U+000080-U+0007FF: two bytes. */
        characterBytes = 2;
        break;
      case 0xE: /* U+000800-U+00FFFF: three bytes. */
        characterBytes = 3;
        break;
      case 0xF: /* U+010000-U+10FFFF: four bytes. */
        characterBytes = 4;
        break;
      default:
        characterBytes = 1;
        break;
    }

    for (int i = 0; i < characterBytes; i++) {
      original.insert(eos + i, 1, original[i]);
    }
    original.erase(0, characterBytes);
    eos -= characterBytes;
  }
}

void utf8Reverse(char* str)
{
  char* end = (str + strlen(str));
  for (char* start = str; start < end; ++start) {
    char c = *start;
    *start = *--end;
    *end = c;
  }

  for (char* start = end = str; char c = *end++;) {
    if ((c & 0x80) == 0) {
      // ASCII char
      start = end;
    } else if ((c & 0xc0) == 0xc0) {
      char* tmp = end;
      switch (end - start) {
        case 4: {
          c = *start;
          *start++ = *--end;
          *end = c;
        }
        case 3:
        case 2: {
          c = *start;
          *start++ = *--end;
          *end = c;
        }
      }
      end = start = tmp;
    }
  }
}

int main()
{
  std::string s = "żółty";
  utf8Reverse(s.data());
  std::cout << s << '\n';
  reverseUtf8(s);
  std::cout << s << '\n';

  return 0;
}