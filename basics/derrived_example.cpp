
int main()
{
  {
    class Base
    {
    public:
      virtual void foo(const int a)
      {
      }
    };

    class Derived: public Base
    {
    public:
      virtual void foo(const int a)
      {
      }
    };
  }

  {
    class Base
    {
      virtual void foo() = 0;

      virtual void bar()
      {
      }

      virtual void foobar() = 0;
    };

    class Derived1: public Base
    {
      virtual void foo() override = 0;

      virtual void bar() override
      {
      }

      virtual void foobar() override
      {
      }
    };

    class Derived2: public Derived1
    {
      virtual void foo() override
      {
      }
    };
  }

  {
    class Base
    {
    public:
      virtual void foo()
      {
      }

      virtual void bar()
      {
      }
    };

    class Derived1: public Base
    {
    public:
      virtual void foo() override
      {
      }

      // virtual void bar(char const c) override {} // error, no Base::bar(char const)
    };

    class Derived2: public Derived1
    {
      virtual void foo() final
      {
      }
    };

    class Derived3: public Derived2
    {
      // virtual void foo() override {} // error
    };

    class Derived4 final: public Derived1
    {
      virtual void foo() override
      {
      }
    };

    // class Derived5 : public Derived4 // error
    //   {
    //   };
  }

  {
    class foo
    {
      int final = 0;

      void override()
      {
      }
    };
  }
}