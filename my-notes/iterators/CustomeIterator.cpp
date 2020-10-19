#include <iostream>
#include <stdexcept>

// TODO: Compile!

// My custom array/container.
template<typename T, const size_t Size>
class my_array
  {
  private:
    T theData[Size] = {};
    size_t theSize = 0;

  public:
    T const& getAt(const size_t aIndex) const
      {
      if (aIndex < theSize)
        return theData[aIndex];

      return std::out_of_range("Index is out of range!");
      }

    void setAt(const size_t aIndex, const T &aValue)
      {
      if (aIndex < theSize)
        theData[aIndex] = aValue;

      return std::out_of_range("Index is out of range!");
      }

    size_t getSize() const { return theSize; }
  };

// My custom iterator class.
template<typename T, typename C, const size_t Size>
class my_iterator
  {
  private:
    size_t theIndex;
    C &theContainer;

  public:
    my_iterator(C &aContainer, const size_t aIndex)
      :
      theIndex(aIndex),
      theContainer(aContainer)
      {}

    bool operator!=(const my_iterator &aOther) const
      {
      return theIndex != theOther.getIndex();
      }

    T const& operator*() const { return theContainer.getAt(theIndex); }

    my_iterator const& operator++() const
      {
      ++theIndex;
      return *this;
      }

    size_t getIndex() const { return theIndex; }
  };


  // Aliases.
  template<typename T, const size_t Size>
  using my_custom_iterator = my_iterator<T, my_array<T, Size>, Size>;

  template<typename T, const size_t Size>
  using my_custom_const_iterator = my_iterator<T, my_array<T, Size> const, Size>;


  // Implement begin() and end() functions corresponding to begin and end iterator iterators (overloads).count()

  template<typename T, const size_t Size>
  inline my_custom_iterator<T, Size> begin(my_array<T, Size> &aContainer)
    {
    return my_custom_iterator<T, Size>(aContainer, 0);
    }

  template<typename T, const size_t Size>
  inline my_custom_iterator<T, Size> end(my_array<T, Size> &aContainer)
    {
    return my_custom_iterator<T, Size>(aContainer, aContainer.getSize());
    }

  // const
  template<typename T, const size_t Size>
  inline my_custom_iterator<T, Size> begin(const my_array<T, Size> &aContainer)
    {
    return my_custom_const_iterator<T, Size>(container, 0);
    }

  template<typename T, const size_t Size>
  inline my_custom_iterator<T, Size> end(const my_array<T, Size> &aContainer)
    {
    return my_custom_const_iterator<T, Size>(aContainer, aContainer.getSize());
    }

template <typename T, const size_t Size>
void print_my_array(const my_array<T, Size> &aContainer)
  {
  for (auto &&elem : aContainer)
    std::cout << elem << std::endl;
  }

auto main() -> int
  {
  my_array<int, 10> container;
  for (auto i = 0; i < 10;)
    container.set(i, i);

  for (auto &&elem : container)
    std::cout << elem << std::endl;

  return 0;
  }