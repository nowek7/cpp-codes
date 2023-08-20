#pragma once

#include <vector>
#include <array>
#include <algorithm>

template<int N, typename T, bool Heap>
class CustomArray
{
public:
    CustomArray()
    {
        if (Heap)
        {
            mVector = std::vector<T>(N);
        }
    }

    T& operator[](const size_t& idx)
    {
        return *(begin() + idx);
    }

    T* begin()
    {
        return Heap ? &mVector[0] : &mArray[0];
    }

    T* end()
    {
        return Heap ? &mVector[mVector.size()] : &mArray[mArray.size()];
    }

    T max()
    {
        return *std::max_element(begin(), end());
    }

    T min()
    {
        return *std::min_element(begin(), end());
    }

private:
    std::array<T, N> mArray;
    std::vector<T> mVector;
};

template<int N, bool Heap, typename T>
auto getArray(const T defaultValue)
{
    CustomArray<N, T, Heap> array;
    for (int i = 0; i < N; ++i)
    {
        array[i] = defaultValue;
    }
    return array;
}

template<typename T, int N = 10, bool Heap = false>
auto getArray(const T defaultValue)
{
    return CustomArray<N, T, Heap>();
}