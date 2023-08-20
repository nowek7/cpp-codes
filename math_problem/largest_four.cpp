#include <algorithm>
#include <vector>

#include <assert.h>

#include <iostream>

int sumFirstFourNumber(const std::vector<int>& array) 
{
    int sum = 0;
    for (auto i = 0; i < std::min(static_cast<int>(array.size()), 4); ++i) {
        sum += array[i];
    }
    return sum;
}

int largestFour(std::vector<int>& array)
{   
    if (array.size() > 4) {
        std::sort(array.begin(), array.end(), std::greater<int>());
    }
    return sumFirstFourNumber(array);
}

int main()
{
    std::vector<int> array = {4, 5, -2, 3, 1, 2, 6, 6};

    std::cout << largestFour(array) << '\n';
    assert(21 == largestFour(array));

    return 0;
}