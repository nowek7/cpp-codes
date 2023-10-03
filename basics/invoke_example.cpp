#include <assert.h>
#include <functional>
#include <iostream>
#include <tuple>

int add(int a, int b)
{
  return a + b;
}

struct foo
{
  int x = 0;

  void incrementBy(int n)
  {
    x += n;
  }
};

namespace details {
  template<class F, class T, std::size_t... I>
  auto apply(F&& f, T&& t, std::index_sequence<I...>)
  {
    return std::invoke(std::forward<F>(f), std::get<I>(std::forward<T>(t))...);
  }
} // namespace details

template<class F, class T>
auto apply(F&& f, T&& t)
{
  return details::apply(std::forward<F>(f),
                        std::forward<T>(t),
                        std::make_index_sequence<std::tuple_size<std::decay_t<T>>::value> {});
}

int main()
{
  {
    auto a1 = add(1, 2);
    assert(a1 == 3);

    int (*fadd)(const int, const int) = &add;
    auto a2 = fadd(1, 2);
    assert(a2 == 3);

    auto fadd2 = &add;
    auto a3 = fadd2(1, 2);
    assert(a3 == 3);
  }

  {
    foo f;
    f.incrementBy(3);
    auto x1 = f.x;
    assert(x1 == 3);

    void (foo::*finc)(const int) = &foo::incrementBy;
    (f.*finc)(3);
    auto x2 = f.x;
    assert(x2 == 6);

    auto finc2 = &foo::incrementBy;
    (f.*finc2)(3);
    auto x3 = f.x;
    assert(x3 == 9);
  }

  {
    auto a1 = std::invoke(add, 1, 2);
    assert(a1 == 3);
    auto a2 = std::invoke(&add, 1, 2);
    assert(a2 == 3);

    int (*fadd)(const int, const int) = &add;

    auto a3 = std::invoke(fadd, 1, 2);
    assert(a3 == 3);
  }

  {
    foo f;
    auto x1 = std::invoke(&foo::x, f);
    assert(x1 == 0);

    std::invoke(&foo::incrementBy, f, 10);
    auto x2 = std::invoke(&foo::x, f);
    assert(x2 == 10);

    auto x3 = std::invoke(std::plus<>(), std::invoke(&foo::x, f), 3);
    assert(x3 == 13);

    auto x4 = std::invoke(&foo::x, f);
    assert(x4 == 10);
  }

  {
    auto l = [](auto a, auto b) {
      return a + b;
    };

    auto a = std::invoke(l, 1, 2);
    assert(a == 3);
  }

  {
    auto a = apply(add, std::make_tuple(1, 2));
  }
}