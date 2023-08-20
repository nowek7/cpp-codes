#include <iostream>
#include <string>
#include <regex>

int main()
{
    const std::string uri = "";
    std::regex rx{R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\s]+)?(\?(&?[^&]*=\w+)+)(#?(\w+))?$)"};

    auto matches = std::smatch{};

    if (std::regex_match(uri, matches, rx))
    {
        for (const auto& match : matches)
        {
            std::cout << match.str() << std::endl;
        }
    }

    return 0;
}