#include <iostream>
#include <memory>

class Base
{
public:
  int baseClassPublicValue {10};

  void baseClassFunction()
  {
    std::cout << "Base class function." << std::endl;
  }

  virtual void virtualBaseClassFunction()
  {
    std::cout << "Base class virtual function." << std::endl;
  }

private:
  int baseClassPrivateValue {20};

protected:
  int baseClassProtectedValue {30};
};

class Child: public Base
{
public:
  int childClassPublicValue {10};

  void childClassFunction()
  {
    std::cout << "Child class function." << std::endl;
  }

  void virtualBaseClassFunction()
  {
    std::cout << "Child class virtual function." << std::endl;
  }

private:
  int childClassPrivateValue {20};
};

class OtherBaseClass
{
public:
  /* pure virtual function that makes OtherBaseClass abstract */
  virtual void pureVirtualOtherBaseClassFunction() = 0;
};

class OtherChildClass: public OtherBaseClass
{
public:
  /* define this function is mandatory as it is pure virtual into the base */
  void pureVirtualOtherBaseClassFunction()
  {
    std::cout << "Other base class pure virtual function definition." << std::endl;
  }
};

int main()
{
  /* Create a Base pointer to a Child object */
  std::unique_ptr<Base> basePointer = std::make_unique<Child>();

  /* Base members are accessible (as long as their visibility allows it) */
  std::cout << basePointer->baseClassPublicValue << std::endl;

  /* Base protected and private members are not accessible */
  // std::cout << basePointer->baseClassPrivateValue << std::endl;
  // std::cout << basePointer->baseClassProtectedValue << std::endl;

  /* Child public members are not accessible */
  // std::cout << basePointer->childClassPublicValue << std::endl;

  /* Base class functions can be called */
  basePointer->baseClassFunction();

  /* child class functions cannot be called */
  // basePointer->childClassFunction();

  /* base class virtual functions are replaced by their child counterpart */
  basePointer->virtualBaseClassFunction();

  /* it is not possible to create objects of an abstract class */
  // OtherBaseClass object;

  /* it is possible to create abstract base class pointer to child class object */
  std::unique_ptr<OtherBaseClass> otherBasePointer = std::make_unique<OtherChildClass>();
  otherBasePointer->pureVirtualOtherBaseClassFunction();
}
