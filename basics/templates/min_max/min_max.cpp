#include <iostream>

template<typename T, typename T1, typename T2, typename T3>
T minmax(const T1 a, const T2 b, const T3 c)
{
    const T casted_a = static_cast<T>(a);
    const T casted_b = static_cast<T>(b);
    const T casted_c = static_cast<T>(c);

    if (casted_a > casted_b)
    {
        return (casted_a > casted_c) ? casted_a : casted_c;
    }
    else
    {
        return (casted_b > casted_c) ? casted_b : casted_c;
    }
}

int main()
{
    std::cout<< minmax<int, int, float, double>(100, 1000, 15.0) << std::endl;
    return 0;
}