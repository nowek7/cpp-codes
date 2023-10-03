#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <type_traits>
#include <vector>

void print(const std::vector<int>& v)
{
  if (!v.empty()) {
    for (int i = 0; i < v.size() - 1; ++i) {
      std::cout << v[i] << " ";
    }
    std::cout << *v.rbegin() << '\n';
  }
}

int main()
{
  std::vector<int> v = {256, 64, 16 * 3, 16 * 9, 16, 8 * 7, 9, 3, 1, 6, 2, 5};
  print(v);

  int center = 50;
  std::sort(v.begin(), v.end(), [&center](const auto& a, const auto& b) {
    return std::abs(a - center) < std::abs(b - center);
  }); // ( 1 )

  print(v);
  auto sharkovsky = [](auto a, auto b) {
    for (;;) {
      if (a == 1 && b == 1) {
        return false;
      }

      if (a == 1) {
        return true;
      }
      if (b == 1) {
        return false;
      }

      if (a % 2 != 0) {
        if (b % 2 != 0) {
          return a < b ? false : true;
        } else {
          return true;
        }
      } else {
        if (b % 2 != 0) {
          return true;
        }

        a /= 2;
        b /= 2;
      }
    }
  }; // ( 2 )

  assert(sharkovsky(1, 2));
  assert(sharkovsky(2, 4));
  assert(sharkovsky(64, 256));
  assert(sharkovsky(256, 256 * 3));
  assert(sharkovsky(256 * 9, 256 * 5));
  assert(sharkovsky(256 * 3, 64 * 9));
  assert(!sharkovsky(1, 1));
  assert(!sharkovsky(4, 2));
  assert(!sharkovsky(256, 64));
  assert(!sharkovsky(256 * 3, 256));
  assert(!sharkovsky(256 * 5, 256 * 9));
  assert(!sharkovsky(64 * 9, 256 * 3));

  // std::sort(v.begin(), v.end(), sharkovsky);
  // print(v);

  srand(time(NULL));
  int a = 0, b = 40;
  auto generator = [&a, &b]() {
    return a + std::rand() % b; // ( 3 )
  };

  std::generate(v.begin(), v.end(), generator);
  print(v);

  a = 100, b = 200;
  std::generate(v.begin(), v.end(), generator);
  print(v);

  a = -10;
  b = 10;
  auto evenGenerator = [&a, &b]() {
    return a + (std::rand() * 2) % b; // ( 4 )
  };

  std::generate(v.begin(), v.end(), evenGenerator);
  print(v);

  v.resize(20);
  a = 0;
  b = 100;
  std::generate(v.begin(), v.end(), evenGenerator);
  print(v);

  auto l1_norm = [](auto& container) {
    double l1_norm = 0;
    for (auto& elem: container) {
      l1_norm += std::abs(elem);
    }
    return l1_norm;
  }; // ( 5 )
  std::cout << l1_norm(v) << std::endl;

  std::vector<double> m = {1.4, 2.4, -2.4, -4.2, -43.3};
  std::cout << l1_norm(m) << std::endl;

  std::list<double> l(m.begin(), m.end());
  std::cout << l1_norm(l) << std::endl;

  double l1Norm = std::accumulate(m.begin(), m.end(), 0., [](auto prev, auto next) {
    return std::abs(prev) + std::abs(next);
  });
  std::cout << l1Norm << std::endl;

  auto wielomian = [](double* coefficients, const int& degree) {
    return [coefficients, &degree](const auto& value) {
      auto res = 0;
      for (int i = degree; i >= 0; i--) {
        res += coefficients[i] * std::pow(value, i);
      }

      return res;
    };
  }; // ( 6 )

  double table[] = {1, 2, 3, 4, 5};
  auto w1 = wielomian(table, 4);
  std::cout << w1(1.0) << " " << w1(0.0) << " " << w1(2.0) << std::endl;

  auto w2 = wielomian(table, 2);
  std::cout << w2(1.0) << " " << w2(0.0) << " " << w2(2.0) << std::endl;

  return 0;
}

/**
Expected output (or similar):
256 64 48 144 16 56 9 3 1 6 2 5
48 56 64 16 9 6 5 3 2 1 144 256
1 2 16 64 256 144 48 56 6 9 5 3
11 33 7 4 40 20 36 27 4 38 31 18
142 135 106 164 160 189 152 196 156 102 198 114
0 -2 -6 -8 -2 -10 -2 -4 -4 0 -8 0
-6 -2 -4 -8 8 -6 0 -4 8 -2 6 8 -8 -8 2 10 10 -6 6 2
114
53.7
53.7
15 1 129
6 1 17
*/
