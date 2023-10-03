#include <iostream>

enum class BOOLEAN
{
  FALSE = 0,
  TRUE = 1
};

template<class T>
class Value
{
public:
  Value() = default;

  explicit Value(T val):
    m_value(val)
  {
  }

  bool operator==(const Value& source)
  {
    return this->m_value == source.m_value;
  }

  operator T()
  {
    return m_value;
  }

private:
  T m_value {BOOLEAN::FALSE};
};

int main()
{
  {
    Value<BOOLEAN> tmp {BOOLEAN::TRUE};
    std::cout << (tmp == BOOLEAN::TRUE ? "TRUE" : "FALSE") << '\n';
  }

  {
    Value<BOOLEAN> tmp;
    std::cout << (tmp == BOOLEAN::TRUE ? "TRUE" : "FALSE") << '\n';
  }

  return 0;
}