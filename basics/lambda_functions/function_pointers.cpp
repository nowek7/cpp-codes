#include <cmath>
#include <iostream>

using namespace std;

typedef double (*SqrtFunc)(int, double);     // or alias using SqrtFunc = double(*)(int, double);
typedef double (*PowerFunc)(double, double); // using PowerFunc = double(*)(double, double);
typedef double (*Func)(int,
                       double,
                       double,
                       SqrtFunc,
                       PowerFunc); // using PowerFunc = double(*)(int, double, double,
                                   // double(*)(int, double), double(*)(double, double));

// Computes n-th root of x
double sqrtn(int n, double x)
{
  return exp(log(x) / n);
}

double power(double x, double y)
{
  return exp(log(x) * y);
}

template<typename F, typename G>
double function(int n, double y, double z, F f, G g)
{
  return (f(n, y) > z) ? g(z, y) : g(y, z);
}

int main()
{
  // double (*fp1)(int, double) = &sqrtn;
  // double (*fp2)(double, double) = &power;
  // double (*fp3)(int, double, double, double(*)(int, double),
  // double(*)(double, double)) = function<double(*)(int, double),
  // double(*)(double, double)>;

  SqrtFunc fp1 = &sqrtn;
  PowerFunc fp2 = &power;
  double (*fp3)(int, double, double, SqrtFunc, PowerFunc) = function<SqrtFunc, PowerFunc>;

  cout << fp3(2, 10, 3, fp1, fp2) << endl;
  cout << fp3(3, 10, 3, fp1, fp2) << endl;
  return 0;
}
