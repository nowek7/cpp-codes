#include <algorithm>
#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <stdexcept>

#include <cassert>

using namespace std::string_literals;

struct Task
  {
  int priority;
  std::string name;
  };

struct Tag
  {
  int id;
  std::string name;

  Tag(int const id = 0, std::string const & name = ""s)
    :
    id(id),
    name(name)
    {}
  };

template <typename Type, const size_t SIZE>
class dummyArray
  {
  Type data[SIZE] = {};

  public:
    Type& operator[](const size_t index)
      {
      if (index < SIZE)
        return data[index];
      throw std::out_of_range("Index out of range");
      }

    const Type& operator[](const size_t index) const
      {
      if (index < SIZE)
        return data[index];
      throw std::out_of_range("Index out of range");
      }

    size_t size() const { return SIZE; }

    template <typename T, const size_t Size>
    class dummyArrayIterator
      {
      public:
        typedef dummyArrayIterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::random_access_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;

      private:
        pointer ptr = nullptr;
        size_t index = 0;

        bool compatible(const self_type &other) const
          {
          return ptr == other.ptr;
          }

      public:
        dummyArrayIterator() = default;
        explicit dummyArrayIterator(pointer ptr, const size_t index)
          :
          ptr(ptr),
          index(index)
          {}


        // --- common to all iterators ---
        // copy-constructible, copy-assignable and destructible
        dummyArrayIterator(const dummyArrayIterator&) = default;
        dummyArrayIterator& operator=(const dummyArrayIterator &) = default;
        ~dummyArrayIterator() = default;

        // Can be prefix- and postfix- incremented
        self_type& operator++()
          {
          if (index >= Size)
            throw std::out_of_range("Iterator cannot be incremented past the end of range.");
          ++index;
          return *this;
          }

        self_type operator++(int)
          {
          self_type tmp = *this;
          ++*this;
          return tmp;
          }

        bool operator==(const self_type &other) const
          {
          assert(compatible(other));
          return index == other.index;
          }

        bool operator!=(const self_type &other) const
          {
          return !(*this == other);
          }

        // Can be dereferenced as an rvalue
        reference operator*() const
          {
          if (ptr == nullptr)
            throw std::bad_function_call();
          return *(ptr + index);
          }

        reference operator-> () const
          {
          if (ptr == nullptr)
            throw std::bad_function_call();
          return *(ptr + index);
          }

        // multi-pass: neither dereferencing nor incrementing affects dereferenceability
        // --- forward iterator ---

        // --- bidirectional iterator ---
        // can be decremented
        self_type& operator--()
          {
          if (index <= 0)
              throw std::out_of_range("Iterator cannot be decremented past the end of range.");
          --index;
          return *this;
          }

        self_type operator--(int)
          {
          self_type tmp = *this;
          --*this;
          return tmp;
          }

        // --- bidirectional iterator ---

        // --- random access iterator ---
        // supports arithmetic operators + and -
        self_type operator+(difference_type offset) const
          {
          self_type tmp = *this;
          return tmp += offset;
          }

        self_type operator-(difference_type offset) const
          {
          self_type tmp = *this;
          return tmp -= offset;
          }

        difference_type operator-(self_type const & other) const
          {
          assert(compatible(other));
          return (index - other.index);
          }

        // supports inequality comparisons (<, >, <= and >=) between iterators
        bool operator<(const self_type &other) const
          {
          assert(compatible(other));
          return index < other.index;
          }

        bool operator>(const self_type &other) const
          {
          return other < *this;
          }

        bool operator<=(const self_type &other) const
          {
          return !(other < *this);
          }

        bool operator>=(const self_type &other) const
          {
          return !(*this < other);
          }

        // Supports compound assignment operations += and -=
        self_type& operator+=(const difference_type offset)
          {
          if (index + offset < 0 || index + offset > Size)
            throw std::out_of_range("Iterator cannot be incremented past the end of range.");

          index += offset;
          return *this;
          }

        self_type& operator-=(const difference_type offset)
          {
          return *this += -offset;
          }

        // Supports offset dereference operator ([])
        value_type& operator[](const difference_type offset)
          {
          return (*(*this + offset));
          }

        value_type const & operator[](const difference_type offset) const
          {
          return (*(*this + offset));
          }
         // --- random access iterator ---
      };

      typedef dummyArrayIterator<Type, SIZE>        iterator;
      typedef dummyArrayIterator<Type const, SIZE>  constant_iterator;

  public:
    iterator begin()
      {
      return iterator(data, 0);
      }

    iterator end()
      {
      return iterator(data, SIZE);
      }

    constant_iterator begin() const
      {
      return constant_iterator(data, 0);
      }

    constant_iterator end() const
      {
      return constant_iterator(data, SIZE);
      }
  };

int main()
  {
    {
      dummyArray<int, 5> array1;
      array1[0] = 1;
      array1[1] = 2;
      array1[2] = 3;
      array1[3] = 4;
      array1[4] = 5;

      dummyArray<int, 5> array2;
      dummyArray<int, 5>::iterator i1 = array1.begin();
      dummyArray<int, 5>::iterator i2 = array1.begin();
      dummyArray<int, 5>::iterator i3 = array1.begin();
      dummyArray<int, 5>::iterator i4 = array1.end();

      dummyArray<int, 5>::iterator y1 = array2.begin();

      // Copy-constructible, copy-assignable and destructible
      auto ci1(i1);
      ci1 = i3;

      // Incrementable
      ++ci1;
      ci1++;

      // Equality/inequality comparison
      auto e1 = i1 == i2;
      auto e2 = i1 == i3;
      //auto e3 = i1 == y1;

      // Dereferenced as rvalue
      if (*i1 > 0) {}

      // Dereferenced as lvalue
      *i1 = 11;
      *i1++ = 111;

      // Default constructible
      dummyArray<int, 5>::iterator i0;
      dummyArray<int, 5>::iterator();

      // Multi-pass
        {
          i2 = i1;
          *i1++;
          *i2;
        }

      // Decrementable
      --i4;
      i4--;
      *i4--;

      // Arithmetic increment and decrement
      auto x1 = i1 + 2;
      //auto x2 = 1 + i1;
      auto x3 = i4 - 1;
      auto d = x1 - x3;

      // Logical comparison
      auto ls = i1 < i4;
      auto gt = i1 > i4;
      auto le = i1 <= i4;
      auto ge = i1 >= i4;

      // Compound assignment
      i1 += 2;
      i1 += -2;
      i1 -= -2;
      i1 -= 2;

      // Offset dereference operator
      auto e = i1[2];
    }

    {
      dummyArray<int, 5> array;
      array[0] = 10;
      array[1] = 20;
      array[2] = 30;
      array[3] = 40;
      array[4] = 50;

      std::transform(array.begin(), array.end(), array.begin(),
                     [](int const e) { return e * 2; });

      for (auto &&entry : array)
        std::cout << entry << std::endl;
    }

    {
      dummyArray<int, 5> array;
      array[0] = 10;
      array[1] = 20;
      array[2] = 30;
      array[3] = 40;
      array[4] = 50;

      for (auto &&entry : array)
        std::cout << entry << std::endl;

      auto lp = [](dummyArray<int, 5> const & container)
        {
        for (const auto &entry : container)
          std::cout << entry << std::endl;
        };

      lp(array);
    }

    {
      dummyArray<Task, 5> tasks;
      tasks[0] = Task{ 10, "Task 1" };
      tasks[1] = Task{ 20, "Task 2" };
      tasks[2] = Task{ 30, "Task 3" };
      tasks[3] = Task{ 40, "Task 4" };
      tasks[4] = Task{ 50, "Task 5" };

      for (auto &&task : tasks)
        std::cout << task.priority << " " << task.name << std::endl;

      auto task0 = &tasks[0];
      std::cout << task0->priority << " " << task0->name << std::endl;
    }

    {
      dummyArray<std::unique_ptr<Tag>, 5> a;
      a[0] = std::make_unique<Tag>(1, "Tag 1");
      a[1] = std::make_unique<Tag>(2, "Tag 2");
      a[2] = std::make_unique<Tag>(3, "Tag 3");
      a[3] = std::make_unique<Tag>(4, "Tag 4");
      a[4] = std::make_unique<Tag>(5, "Tag 5");

      for (auto it = a.begin(); it != a.end(); ++it)
        std::cout << it->id << " " << it->name << std::endl;

      auto p0 = a[0].get();
      std::cout << p0->id << " " << p0->name << std::endl;
    }

    {
      dummyArray<int, 5> array;
      array[0] = 10;
      array[1] = 20;
      array[2] = 30;
      array[3] = 40;
      array[4] = 50;

      auto print = [](const dummyArray<int, 5>  &array)
        {
        for (size_t i = 0; i < array.size(); ++i)
          std::cout << array[i] << std::endl;
        };

      print(array);
    }
  }
