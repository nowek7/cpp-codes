#pragma once

#include <cmath>
#include <initializer_list>
#include <numeric>
#include <vector>
#include <stdexcept>

class Vector
  {
  public:
    static double dot(const Vector &aLeft, const Vector &aRight);

  public:
    Vector() = default;
    Vector(std::initializer_list<double> aValues);
    Vector(std::vector<double> aValues);
    Vector(const Vector &aOther);
    Vector(Vector &&aOther) = delete;

    ~Vector() = default;

    Vector &operator=(const Vector &aOther);
    Vector &operator=(Vector &&aOther) = delete;

    Vector operator+(const Vector &aOther);
    Vector &operator+=(const Vector &aOther);

    Vector operator-(const Vector &aOther);
    Vector &operator-=(const Vector &aOther);

    template<typename T>
    Vector operator*(const T aScalar);
    
    template<typename T>
    Vector &operator*=(const T aScalar);

    template<typename T>
    Vector operator/(const T aScalar);

    template<typename T>
    Vector &operator/=(const T aScalar);

    bool operator==(const Vector &aOther);
    bool operator!=(const Vector &aOther);

    std::vector<double> getCoordinates() const;
    size_t getDimension() const;
    double getLength() const;

  private:
    std::vector<double> theCoordinates = {};
    double theLength = 0;

    void computeLength();
  };

Vector::Vector(std::initializer_list<double> aValues)
  {
  theCoordinates.insert(theCoordinates.end(), aValues.begin(), aValues.end());
  computeLength();
  }

inline Vector::Vector(std::vector<double> aValues)
  {
  theCoordinates.insert(theCoordinates.end(), aValues.begin(), aValues.end());
  computeLength();
  }

Vector::Vector(const Vector &aOther)
  {
  theCoordinates.clear();
  auto otherCoordinates = aOther.getCoordinates();
 
  std::copy(otherCoordinates.begin(), otherCoordinates.end(), std::back_inserter(theCoordinates));
  theLength = aOther.getLength();
  }

Vector &Vector::operator=(const Vector &aOther)
  {
  auto otherCoordinates = aOther.getCoordinates();
  
  theCoordinates.clear();
  std::copy(otherCoordinates.begin(), otherCoordinates.end(), std::back_inserter(theCoordinates));
  theLength = aOther.getLength();

  return *this;
  }

inline Vector Vector::operator+(const Vector &aOther)
  {
  auto otherCoordinates = aOther.getCoordinates();
  if (theCoordinates.size() != otherCoordinates.size())
    throw std::logic_error("Vectors do not have the same size!");

  std::vector<double> vec;
  for (auto i = 0; i < theCoordinates.size(); i++)
    vec.push_back(theCoordinates[i] + otherCoordinates[i]);
  
  return Vector(vec);
  }

Vector &Vector::operator+=(const Vector &aOther)
  {
  auto otherCoordinates = aOther.getCoordinates();
  if (theCoordinates.size() != otherCoordinates.size())
    throw std::logic_error("Vectors do not have the same size!");

  for (auto i = 0; i < theCoordinates.size(); i++)
    theCoordinates[i] += otherCoordinates[i];

  theLength += aOther.getLength();

  return *this;
  }

Vector Vector::operator-(const Vector &aOther)
  {
  auto otherCoordinates = aOther.getCoordinates();
  if (theCoordinates.size() != otherCoordinates.size())
    throw std::logic_error("Vectors do not have the same size!");

  std::vector<double> vec;
  for (auto i = 0; i < theCoordinates.size(); i++)
    vec.push_back(std::move(theCoordinates[i] - otherCoordinates[i]));

  return Vector(vec);
  }

Vector &Vector::operator-=(const Vector &aOther)
  {
  auto otherCoordinates = aOther.getCoordinates();
  if (theCoordinates.size() != otherCoordinates.size())
    throw std::logic_error("Vectors do not have the same size!");

  for (auto i = 0; i < theCoordinates.size(); i++)
    theCoordinates[i] -= otherCoordinates[i];

  theLength -= aOther.getLength();

  return *this;
  }

double Vector::dot(const Vector &aLeft, const Vector &aRight)
  {
  auto leftCoordinates = aLeft.getCoordinates();
  auto rightCoordinates = aRight.getCoordinates();
  if (leftCoordinates.size() != rightCoordinates.size())
    throw std::logic_error("Vectors do not have the same size!");

  auto dot = double{0};
  for (auto i = 0; i < leftCoordinates.size(); i++)
    dot += leftCoordinates[i] * rightCoordinates[i];

  return dot;
  }

template<typename T>
Vector Vector::operator*(const T aScalar)
  {
  auto coordinates = theCoordinates;
  for (auto i = 0; i < coordinates.size(); i++)
    coordinates[i] *= aScalar;

  return Vector(coordinates);
  }

template<typename T>
Vector &Vector::operator*=(const T aScalar)
  {
  for (auto i = 0; i < theCoordinates.size(); i++)
    theCoordinates[i] *= aScalar;

  computeLength();

  return *this;
  }

template<typename T>
Vector Vector::operator/(const T aScalar)
  {
  if (aScalar == 0)
    throw std::logic_error("Cannot divide by zero!");

  auto coordinates = theCoordinates;
  for (auto i = 0; i < coordinates.size(); i++)
    coordinates[i] /= aScalar;

  return Vector(coordinates);
  }

template<typename T>
Vector &Vector::operator/=(const T aScalar)
  {
  if (aScalar == 0)
    throw std::logic_error("Cannot divide by zero!");

  for (auto i = 0; i < theCoordinates.size(); i++)
    theCoordinates[i] /= aScalar;

  computeLength();
  
  return *this;
  }

inline bool Vector::operator==(const Vector &aOther)
  {
  auto otherCoordinates = aOther.getCoordinates();
  if (theCoordinates.size() != otherCoordinates.size())
    return false;

  for (auto i = 0; i < theCoordinates.size(); i++)
    {
    if (theCoordinates[i] != otherCoordinates[i])
      return false;
    }

  return true;
  }

inline bool Vector::operator!=(const Vector &aOther)
  {
  auto otherCoordinates = aOther.getCoordinates();
  if (theCoordinates.size() == otherCoordinates.size())
    {
    for (auto i = 0; i < theCoordinates.size(); i++)
      {
      if (theCoordinates[i] != otherCoordinates[i])
        return true;
      }

    return false;
    }

  return true;
  }

inline std::vector<double> Vector::getCoordinates() const
  {
  return theCoordinates;
  }

inline size_t Vector::getDimension() const
  {
  return theCoordinates.size();
  }

inline double Vector::getLength() const
  {
  return theLength;
  }

inline void Vector::computeLength()
  {
  auto sum = double{0};
  for (auto i = 0; i < theCoordinates.size(); i++)
    sum += theCoordinates[i] * theCoordinates[i];

  theLength = std::sqrt(sum);
  }
