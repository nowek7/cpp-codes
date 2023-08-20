#include "custom_string.hpp"

#include <iostream>

int main()
{
    String<char> name("Michal");
    name += '!';

    std::cout << name << std::endl;
    std::cout << std::boolalpha << (name == "Michal!") << std::endl;
    std::cout << std::boolalpha << (name == name) << std::endl;

    try
    {
        std::cout << name[-1] << std::endl;
    }
    catch (const std::out_of_range& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    std::cout << name[5] << std::endl;

    try
    {
        std::cout << name[15] << std::endl;
    }
    catch (const std::out_of_range& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}