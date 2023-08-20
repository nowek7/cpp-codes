
#include <algorithm>
#include <array>
#include <random>
#include <iostream>
#include <numeric>

namespace
{
    constexpr int SIZE = 100;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uid(1, 10000);

    std::array<int, SIZE> container;

    for (auto& element: container)
    {
        element = uid(gen);
    }

    for (auto& element: container)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    int min = container[0];
    for (const auto& element: container)
    {
        if (min > element)
        {
            min = element;
        }
    }

    std::cout << "Max -> " << min << std::endl;
    std::cout << "Min -> " << *std::max_element(container.begin(), container.end()) << std::endl;

    return 0;
}