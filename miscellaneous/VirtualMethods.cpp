#include <iostream>
#include <memory>

// class Number
//   {
//   auto operator+(int aLeft, int aRight) -> void { std::cout << aLeft + aRight << std::endl; }
//   auto operator+(double aLeft, double aRight) -> void { std::cout << aLeft + aRight << std::endl; }
//   auto operator+(std::string aLeft, std::string aRight) -> void { std::cout << aLeft + aRight << std::endl; }
//   }

// Operator overloading
namespace Core
  {
  auto isEqual(int aLeft, int aRight) -> bool { return aLeft == aRight; }
  auto isEqual(double aLeft, double aRight) -> bool { return aLeft == aRight; }
  auto isEqual(std::string aLeft, std::string aRight) -> bool { return aLeft.compare(aRight) == 0; }
  };

// Runtime
struct AnimalBase
  {
  virtual ~AnimalBase() {};
  virtual auto speak() const -> void {}
  };

struct Bear: public AnimalBase
  {
  auto roar() const { std::cout << "ROAR" << std::endl; }
  auto speak() const -> void { roar(); }
  };

struct Duck: public AnimalBase
  {
  auto quack() const { std::cout << "QUACK" << std::endl; }
  auto speak() const -> void { quack(); }
  };

auto speak(const AnimalBase *aAnimal) -> void
  {
  aAnimal->speak();
  }

int main()
  {
  auto a{10}, b{10};
  auto first{"ROAR"}, second{"MEOW"};
  auto pi{3.141592}, euler{ 2.7182818};

  std::cout << a << " == " << b << " -> " << std::boolalpha << Core::isEqual(a, b) << std::endl;
  std::cout << first << " == " << second << " -> " << std::boolalpha << Core::isEqual(first, second) << std::endl;
  std::cout << euler << " == " << pi << " -> " << std::boolalpha << Core::isEqual(euler, pi) << std::endl;

  std::cout << "--------------------------" << std::endl;

  AnimalBase *animal;
  Bear bear;
  animal = &bear;

  animal->speak();

  // animal->roar(); // Error!

  Duck *duck = new Duck();

  // speak(bear);
  speak(duck);
  return 0;
  }