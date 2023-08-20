#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template<class T, size_t R, size_t C>
class Array2D
{
private:
  typedef T valueType;
  typedef valueType* iterator;
  typedef valueType const* const_iterator;

  std::vector<T> theContainer;

public:
  Array2D(): theContainer(R * C)
  {
  }

  explicit Array2D(std::initializer_list<T> aSequence): theContainer(aSequence)
  {
  }

  constexpr T* data() noexcept
  {
    return theContainer.data();
  }

  constexpr T const* data() const noexcept
  {
    return theContainer.data();
  }

  constexpr T& at(size_t aRowIdx, size_t aColIdx)
  {
    return theContainer.at(aRowIdx * C + aColIdx);
  }

  constexpr T const& at(size_t aRowIdx, size_t aColIdx) const
  {
    return theContainer.at(aRowIdx * C + aColIdx);
  }

  constexpr T& operator()(size_t aRowIdx, size_t aColIdx)
  {
    return theContainer[aRowIdx * C + aColIdx];
  }

  constexpr T const& operator()(size_t aRowIdx, size_t aColIdx) const
  {
    return theContainer[aRowIdx * C + aColIdx];
  }

  constexpr bool empty() const noexcept
  {
    return R == 0 || C == 0;
  }

  constexpr size_t size(int aRank) const
  {
    if (aRank == 1)
    {
      return R;
    }
    else if (aRank == 2)
    {
      return C;
    }

    throw std::out_of_range("Rank is out of range!");
  }

  std::vector<T> getContainer() const
  {
    return theContainer;
  }

  void fill(T aValue)
  {
    std::fill(std::begin(theContainer), std::end(theContainer), aValue);
  }

  void swap(Array2D& aOther) noexcept
  {
    auto otherContainer = aOther.getContainer();
    theContainer.swap(otherContainer);
  }

  // Difference between theContainer.data() -> pointer vs theContainer.begin() -> iterator
  // Exactly the same in theContainer.data() + theContainer.size() -> pointer vs theContainer.end() -> iterator
  const_iterator begin() const
  {
    return theContainer.data();
  }

  const_iterator end() const
  {
    return theContainer.data() + theContainer.size();
  }

  iterator begin()
  {
    return theContainer.data();
  }

  iterator end()
  {
    return theContainer.data() + theContainer.size();
  }
};

template<class T, size_t R, size_t C>
void printArray2D(Array2D<T, R, C> const& aContainer)
{
  for (int i = 0; i < R; ++i)
  {
    for (int j = 0; j < C; ++j)
    {
      std::cout << aContainer.at(i, j) << ' ';
    }
    std::cout << std::endl;
  }
}

int main()
{
  {
    std::cout << "Test fill" << std::endl;

    Array2D<int, 2, 3> container;
    container.fill(1);

    printArray2D(container);
  }

  {
    std::cout << "Test operator()" << std::endl;
    Array2D<int, 2, 3> container;

    for (size_t i = 0; i < container.size(1); ++i)
    {
      for (size_t j = 0; j < container.size(2); ++j)
        container(i, j) = 1 + i * 3 + j;
    }

    printArray2D(container);
  }

  {
    std::cout << "Test move semantics" << std::endl;

    Array2D<int, 2, 3> container{10, 20, 30, 40, 50, 60};
    printArray2D(container);

    Array2D<int, 2, 3> container2(std::move(container));
    printArray2D(container2);
  }

  {
    std::cout << "Test swap" << std::endl;

    Array2D<int, 2, 3> container1{1, 2, 3, 4, 5, 6};
    Array2D<int, 2, 3> container2{10, 20, 30, 40, 50, 60};

    printArray2D(container1);
    printArray2D(container2);

    std::cout << "SWAP" << std::endl;
    container1.swap(container2);

    printArray2D(container1);
    printArray2D(container2);
  }

  {
    std::cout << "Test capacity" << std::endl;

    Array2D<int, 2, 3> const container{1, 2, 3, 4, 5, 6};

    for (size_t i = 0; i < container.size(1); ++i)
    {
      for (size_t j = 0; j < container.size(2); ++j)
        std::cout << container(i, j) << ' ';

      std::cout << std::endl;
    }
  }

  {
    std::cout << "Test iterators" << std::endl;

    Array2D<int, 2, 3> const container{1, 2, 3, 4, 5, 6};
    for (auto const elem: container)
      std::cout << elem << ' ';
    std::cout << std::endl;

    std::copy(std::begin(container), std::end(container), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
}
