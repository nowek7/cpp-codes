// Static polymorphism with CRTP

#include <iostream>
#include <vector>
#include <memory>

namespace CRTP_Demo_1
  {
  template <class T>
  class Base
    {
    public:
      void func() { static_cast<T*>(this)->func(); }
    };

  class Derived : public Base<Derived>
    {
    public:
      void func() { std::cout << "Derived::func" << std::endl; }
    };

  template <class T>
  void doSomething(Base<T> &aBase) { aBase.func(); }
  }

namespace CRTP_Demo_2
  {
  template <class T>
  class Control
    {
    public:
      void draw()
        {
        static_cast<T*>(this)->eraseBackground();
        static_cast<T*>(this)->paint();
        }
    };

  class Button : public Control<Button>
    {
    private:
      friend class Control<Button>;

    void eraseBackground() { std::cout << "Erasing button background..." << std::endl; }
    void paint() { std::cout << "Painting button..." << std::endl; }
    };

  class Checkbox : public Control<Checkbox>
    {
    public:
      void eraseBackground() { std::cout << "Erasing checkbox background..." << std::endl; }
      void paint() { std::cout << "Painting checkbox..." << std::endl; }
    };

  template <class T>
  void drawControl(Control<T> &aControl) { aControl.draw(); }

  template <class T>
  class FancyButton : public Control<FancyButton<T>>
    {
    public:
      void eraseBackground() { static_cast<T*>(this)->paintArea(); }
      void paint() { std::cout << "Painting button..." << std::endl; }
    };

  class TransparentButton : public FancyButton<TransparentButton>
    {
    public:
      void paintArea() { std::cout << "Painting transparent button background..." << std::endl; }
    };
  }

namespace CRTP_Demo_3
  {
  class ControlBase
    {
    public:
      virtual void draw() = 0;
      virtual ~ControlBase() {}
    };

  template <class T>
  class Control : public ControlBase
    {
    T* derived() { return static_cast<T*>(this); }

    public:
      virtual void draw() override
        {
        derived()->eraseBackground();
        derived()->paint();
        }
    };

  class Button : public Control<Button>
    {
    public:
      void eraseBackground() { std::cout << "Erasing button background..." << std::endl; }
      void paint() { std::cout << "Painting button..." << std::endl; }
    };

  class Checkbox : public Control<Checkbox>
    {
    public:
      void eraseBackground() { std::cout << "Erasing checkbox background..." << std::endl; }
      void paint() { std::cout << "Painting checkbox..." << std::endl; }
    };

  void drawControls(std::vector<std::shared_ptr<ControlBase>> &aControls)
    {
    for (auto &control : aControls)
      control->draw();
    }
  }

int main()
  {
    {
    using namespace CRTP_Demo_1;

    Derived derived;
    derived.func();

    doSomething(derived);
    }

    {
    using namespace CRTP_Demo_2;

    Button button;
    Checkbox checkbox;

    button.draw();
    drawControl(button);
    drawControl(checkbox);
    }

    {
    using namespace CRTP_Demo_2;

    TransparentButton button;
    button.draw();
    }

    {
    using namespace CRTP_Demo_3;

    std::vector<std::shared_ptr<ControlBase>> controls;
    controls.emplace_back(std::make_shared<Button>());
    controls.emplace_back(std::make_shared<Checkbox>());

    drawControls(controls);
    }
  }