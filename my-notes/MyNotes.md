# C++17 Features

## Using structured bindings to handle multi-return values

Developers have to choose between returning multiple values through reference parameters to a function, defining a structure to contain the multiple values or returning a `std::pair` or `std::tuple`.

The first two use named variables that have the advantage that they clearly indicate the meaning of the return value,
but have the disadvantage that they have to be explicitly defined.

`std::pair` has its members called first and second, and `std::tuple` has unnamed members that can only
be retrieved with a function call, but can be copied to named variables using std::tie().
None of these solutions is ideal.

C++17 extends the semantic use of `std::tie()` into a first-class core language feature that
enables unpacking the values of a tuple to named variables. This feature is called structured
bindings.

To return multiple values from a function using a compiler that supports C++17 you should
do the following:

1. Use an `std::tuple` for the return type.

```cpp
std::tuple<int, std::string, double> find()
  {
  return std::make_tuple(1, "marius", 1234.5);
  }
```

2. Use structured bindings to unpack the values of the tuple into named objects.

```cpp
auto [id, name, score] = find();
```

3. Use decomposition declaration to bind the returned values to variables inside an if statement or switch statement.

```cpp
if (auto [id, name, score] = find(); score > 1000)
  {
  std::cout << name << std::endl;
  }
```

### How it works

Structured bindings are a language feature that works just like `std::tie()`, except that we
don't have to define named variables for each value that needs to be unpacked explicitly
with `std::tie()`. With structured bindings, we define all named variables in a single
definition using the auto specifier so that the compiler can infer the correct type for each
variable.

---

## Clip number

`std::clamp` is defined in `#include<algorithm>`

```cpp
template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi ); // (1)(since C++17)

template<class T, class Compare>
constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp ); // (2)(since C++17)

```

1) If `v` compares less than `lo`, returns `lo`; otherwise if `hi` compares less than `v`, returns `hi`; otherwise returns `v`. Uses `operator<` to compare the values.
2) Same as (1), but uses `comp` to compare the values.

The behavior is undefined if the value of `lo` is greater than `hi`.

```cpp
#include <algorithm>
#include <iostream>

int main()
  {
  auto value = 5;
  auto lowerBound = -10;
  auto upperBound = 10;

  std::cout << std::clamp(value, lowerBound, upperBound) << std::endl; // 5

  value = -15;
  std::cout << std::clamp(value, lowerBound, upperBound) << std::endl; // -10

  value = 15;
  std::cout << std::clamp(value, lowerBound, upperBound) << std::endl; // 10
  }

```

---

## Variadic templates

[Example 1](../language-features/UsageVariadicTemplatesOnContainer.cpp)
[Example 2](../language-features/CompareVariadicTemplate.cpp)

---