#include <cassert>
#include <iostream>
#include <vector>

bool isPalindrome(std::vector<std::string> arr, int start, int end)
{
  for (auto i = start, j = end; i < j; ++i, --j) {
    if (arr[i] != arr[j]) {
      return false;
    }
  }
  return true;
}

bool SymmetricTree(std::vector<std::string> strArr)
{
  if (strArr.size() % 2 == 0) {
    return false;
  }

  for (int start = 0, end = 0; end < strArr.size(); start = end + 1, end = start * 2) {
    if (!isPalindrome(strArr, start, end)) {
      return false;
    }
    start = end + 1;
    end = start * 2;
  }

  return true;
}

int main()
{
  {
    std::vector<std::string> strArr = {"4", "3", "4"};
    assert(SymmetricTree(strArr) == false);
  }

  {
    std::vector<std::string> strArr = {"10", "2", "2", "#", "1", "1", "#"};
    assert(SymmetricTree(strArr) == true);
  }

  return 0;
}
