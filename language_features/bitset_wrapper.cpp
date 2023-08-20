#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

class BitsetWrapper
{
  std::vector<bool> theBits;

public:
  friend void print(const BitsetWrapper& aBitsetWrapper);

  BitsetWrapper() = default;
  BitsetWrapper(const std::vector<bool>& aBits): theBits(aBits)
  {
  }

  bool operator[](size_t aIdx)
  {
    if (aIdx >= theBits.size())
    {
      throw std::out_of_range("Index out of range!");
    }

    return theBits[aIdx];
  }

  inline bool any() const
  {
    for (const auto bit: theBits)
    {
      if (bit)
      {
        return true;
      }
    }

    return false;
  }

  inline bool all() const
  {
    for (const auto bit: theBits)
    {
      if (!bit)
      {
        return false;
      }
    }

    return true;
  }

  inline bool none() const
  {
    return !any();
  }

  inline size_t count() const
  {
    return std::count(theBits.cbegin(), theBits.cend(), true);
  }

  inline size_t size() const
  {
    return theBits.size();
  }

  inline BitsetWrapper& add(const bool aBit)
  {
    theBits.push_back(aBit);
    return *this;
  }

  inline BitsetWrapper& remove(const size_t aIdx)
  {
    if (aIdx >= theBits.size())
    {
      throw std::out_of_range("Index out of range!");
    }

    theBits.erase(theBits.begin() + aIdx);

    return *this;
  }

  inline BitsetWrapper& set(const bool aValue = true)
  {
    for (auto i = 0; i < theBits.size(); i++)
    {
      theBits[i] = aValue;
    }

    return *this;
  }

  inline BitsetWrapper& set(const size_t aIdx, const bool aValue)
  {
    if (aIdx >= theBits.size())
    {
      throw std::out_of_range("Index out of range!");
    }

    theBits[aIdx] = aValue;

    return *this;
  }

  inline BitsetWrapper& reset()
  {
    for (auto i = 0; i < theBits.size(); i++)
    {
      theBits[i] = false;
    }

    return *this;
  }

  inline BitsetWrapper& reset(size_t aIdx)
  {
    if (aIdx >= theBits.size())
    {
      throw std::out_of_range("Index out of range!");
    }

    theBits[aIdx] = false;

    return *this;
  }

  inline BitsetWrapper& flip()
  {
    theBits.flip();
    return *this;
  }

  inline std::vector<bool> data() const
  {
    return theBits;
  }
};

void print(const BitsetWrapper& aBitsetWrapper)
{
  auto& bits = aBitsetWrapper.theBits;
  const auto endIdx = bits.size() - 1;
  for (auto i = 0; i < endIdx; i++)
  {
    std::cout << bits[i] << ", ";
  }
  std::cout << bits[endIdx] << std::endl;
}

int main()
{
  BitsetWrapper bw;

  bw.add(true).add(true).add(false);
  print(bw);

  bw.add(false);
  print(bw);

  bw.add(true);
  print(bw);

  if (bw.any())
  {
    std::cout << "Has some 1s" << std::endl;
  }

  if (bw.all())
  {
    std::cout << "Has only 1s" << std::endl;
  }

  if (bw.none())
  {
    std::cout << "Has no 1s" << std::endl;
  }

  std::cout << "Has " << bw.count() << " 1s" << std::endl;

  bw.set(2, true);
  print(bw);

  bw.set();
  print(bw);

  bw.reset(0);
  print(bw);

  bw.reset();
  print(bw);

  bw.flip();
  print(bw);
}