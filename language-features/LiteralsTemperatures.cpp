#include <cmath>
#include <iostream>

#include <assert.h>

bool areEqual(const double &aNumber, const double &aOther, double const aEpsilon = 0.001)
  {
  return std::fabs(aNumber - aOther) < aEpsilon;
  }

namespace Temperature
  {
  enum class Scale
    {
    Kelvin = 0,
    Celsius,
    Fahrenheit,
    };

  template<Scale S>
  class Quantity
    {
    public:
      constexpr explicit Quantity(const double aAmount): theAmount(aAmount) {}
      explicit operator double() const { return theAmount; }

    private:
      const double theAmount;
    };

  template <Scale S>
  inline bool operator==(const Quantity<S> &aLeft, const Quantity<S> &aRight)
    {
    return areEqual(static_cast<double>(aLeft), static_cast<double>(aRight));
    }

  template <Scale S>
  inline bool operator!=(const Quantity<S> &aLeft, const Quantity<S> &aRight)
    {
    return !(aLeft == aRight);
    }

  template <Scale S>
  inline bool operator<(const Quantity<S> &aLeft, const Quantity<S> &aRight)
    {
    return static_cast<double>(aLeft) < static_cast<double>(aRight);
    }

  template <Scale S>
  inline bool operator>(const Quantity<S> &aLeft, const Quantity<S> &aRight)
    {
    return aRight < aLeft;
    }

  template <Scale S>
  inline bool operator<=(const Quantity<S> &aLeft, const Quantity<S> &aRight)
    {
    return !(aLeft > aRight);
    }

  template <Scale S>
  inline bool operator>=(const Quantity<S> &aLeft, const Quantity<S> &aRight)
    {
    return !(aLeft < aRight);
    }

  template <Scale S>
  constexpr Quantity<S> operator+(const Quantity<S> &aQuantity1, const Quantity<S> &aQuantity2)
    {
    return Quantity<S>(static_cast<double>(aQuantity1) + static_cast<double>(aQuantity2));
    }

  template <Scale S>
  constexpr Quantity<S> operator-(const Quantity<S> &aQuantity1, const Quantity<S> &aQuantity2)
    {
    return Quantity<S>(static_cast<double>(aQuantity1) - static_cast<double>(aQuantity2));
    }

  template<Scale S, Scale D>
  struct ConversionTraits
    {
    // Avoid unnecessary conversion.
    static double convert(const double aValue) = delete;
    };

  template <>
  struct ConversionTraits<Scale::Kelvin, Scale::Celsius>
    {
    static double convert(const double aValue)
      {
      return aValue - 273.15;
      }
    };

  template <>
  struct ConversionTraits<Scale::Kelvin, Scale::Fahrenheit>
    {
    static double convert(const double aValue)
      {
      return ((aValue * 9) / 5) - 459.67;
      }
    };

  template <>
  struct ConversionTraits<Scale::Celsius, Scale::Kelvin>
    {
    static double convert(const double aValue)
      {
      return aValue + 273.15;
      }
    };

  template <>
  struct ConversionTraits<Scale::Celsius, Scale::Fahrenheit>
    {
    static double convert(const double aValue)
      {
      return ((aValue * 9) / 5) + 32;
      }
    };

  template <>
  struct ConversionTraits<Scale::Fahrenheit, Scale::Celsius>
    {
    static double convert(const double aValue)
      {
      return ((aValue - 32) * 5) / 9;
      }
    };

  template <>
  struct ConversionTraits<Scale::Fahrenheit, Scale::Kelvin>
    {
    static double convert(const double aValue)
      {
      return ((aValue + 459.67) * 5) / 9;
      }
    };

  template <Scale D, Scale S>
  constexpr Quantity<D> temperatureCast(const Quantity<S> aTemperature)
    {
    return Quantity<D>(ConversionTraits<S, D>::convert(static_cast<double>(aTemperature)));
    }

  namespace TemperatureScale
    {
    constexpr Quantity<Scale::Celsius> operator"" _deg(const long double aAmount)
      {
      return Quantity<Scale::Celsius>{static_cast<double>(aAmount)};
      }

    constexpr Quantity<Scale::Fahrenheit> operator"" _f(const long double aAmount)
      {
      return Quantity<Scale::Fahrenheit>{static_cast<double>(aAmount)};
      }

    constexpr Quantity<Scale::Kelvin> operator"" _k(const long double aAmount)
      {
      return Quantity<Scale::Kelvin>{static_cast<double>(aAmount)};
      }
    } // namespace TemperatureScale
  } // namespace Temperature

int main()
  {
    using namespace Temperature;
    using namespace TemperatureScale;

    auto t1{36.5_deg};
    auto t2{79.0_f};
    auto t3{100.0_k};

    {
      auto tf = temperatureCast<Scale::Fahrenheit>(t1);
      auto tc = temperatureCast<Scale::Celsius>(tf);
      assert(t1 == tc);
    }

    {
      auto tk = temperatureCast<Scale::Kelvin>(t1);
      auto tc = temperatureCast<Scale::Celsius>(tk);
      assert(t1 == tc);
    }

    {
      auto tc = temperatureCast<Scale::Celsius>(t2);
      auto tf = temperatureCast<Scale::Fahrenheit>(tc);
      assert(t2 == tf);
    }

    {
      auto tk = temperatureCast<Scale::Kelvin>(t2);
      auto tf = temperatureCast<Scale::Fahrenheit>(tk);
      assert(t2 == tf);
    }

    {
      auto tc = temperatureCast<Scale::Celsius>(t3);
      auto tk = temperatureCast<Scale::Kelvin>(tc);
      assert(t3 == tk);
    }

    {
      auto tf = temperatureCast<Scale::Fahrenheit>(t3);
      auto tk = temperatureCast<Scale::Kelvin>(tf);
      assert(t3 == tk);
    }
  }
