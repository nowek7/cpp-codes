#include <iostream>
#include <numbers>

inline float square(float aNumber)
{
    return aNumber * aNumber;
}

inline float area(float aRadius)
{
    return std::numbers::pi * square(aRadius);
}

int main()
{
    std::cout << __cplusplus << '\n';

    for (float radius = 1.0f; radius < 3.0f; radius += 0.1f) {
        std::cout << "Area disc for radius " << radius << " is equal- " << area(radius) << '\n';
    }
}
