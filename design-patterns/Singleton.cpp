#include <iostream>
#include <assert.h>

class Singleton
  {
  private:
    Singleton() {}
  public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& instance()
      {
      static Singleton single;
      return single;
      }

    void demo() { std::cout << "Demo using classic singleton" << std::endl; }
  };

template <class T>
class SingletonBase
  {
  protected:
    SingletonBase() {}
  public:
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

    static T& instance()
      {
      static T single;
      return single;
      }
  };

class Single : public SingletonBase<Single>
  {
  Single() {}
  friend class SingletonBase<Single>;

  public:
    void demo() { std::cout << "Demo using CRTP singleton" << std::endl; }
  };

int main()
  {
    {
    auto &single = Singleton::instance();
    single.demo();

    auto &sec = Singleton::instance();
    assert(&sec == &single);
    }

    {
    auto &single = Single::instance();
    single.demo();

    auto &sec = Single::instance();
    assert(&sec == &single);
    }
  }