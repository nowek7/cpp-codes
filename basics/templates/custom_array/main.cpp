#include "custom_array.hpp"

#include <iterator>
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& container)
{
    // for (auto it = container.begin(); it != container.end() - 1; ++it)
    // {
    //     os << *it << " ";
    // }
    // os << *(container.end() - 1);

    std::copy(container.begin(), container.end() - 1, std::ostream_iterator<T>(os, " "));
    os << *(container.end() - 1);

    return os;
}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& container)
{
    for (auto it = container.begin(); it != container.end() - 1; ++it)
    {
        os << *it << " ";
    }
    os << *(container.end() - 1);

    // std::copy(container.begin(), container.end(), std::ostream_iterator<T>(os, " "));

    return os;
}

// template<class Container>
// std::ostream& operator<<(std::ostream& os, const Container container)
// {
//     for (auto it = container.begin(); it != container.end() - 1; ++it)
//     {
//         os << *it << std::endl;
//     }
//     os << *(container.end() - 1);
//     return os;
// }

int main()
{
    CustomArray<3, int, false> myArray;
    myArray[0] = 10;
    myArray[1] = 20;
    myArray[2] = 30;

    for (auto elem : myArray)
    {
        std::cout << elem << std::endl;
    }

    std::cout << std::endl;

    {
        for (auto it = myArray.begin(); it != myArray.end(); ++it)
        {
            std::cout << *it << std::endl;
        }
    }

    std::cout << std::endl;

    {
        std::cout << "MAX: " << myArray.max() << std::endl;
        std::cout << "MIN: " << myArray.min() << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "Template deduction for creating templated array" << std::endl;
        auto myExtArray = getArray<5, true>(10);
        for (const auto elem : myExtArray)
        {
            std::cout << elem << std::endl;
        }
    }

    std::cout << std::endl;

    {
        std::cout << "Template deduction for vector" << std::endl;
        std::vector<int> container(10);
        std::cout << container << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "Template deduction for array" << std::endl;
        std::array<int, 5> array = {10, 20, 30, 40, 50};
        std::cout << array << std::endl;
    }

    return 0;
}