#pragma once

#include <array>
#include <fstream>
#include <random>

const std::array<int, 11> SIZES = {1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};

class ComparisonTool
{
public:
  ComparisonTool():
    mSize(0),
    mGenerator(mRandomDevice()),
    mUid(0, 100) {};

  ~ComparisonTool() = default;

  virtual void generateSummary(std::ofstream& oFile) = 0;

protected:
  std::size_t mSize;
  std::random_device mRandomDevice;
  std::mt19937 mGenerator;
  std::uniform_int_distribution<> mUid;

  virtual std::pair<int, int> beginElementsActionSummary() = 0;
  virtual std::pair<int, int> middleElementsActionSummary() = 0;
  virtual std::pair<int, int> endElementsActionSummary() = 0;
  virtual void modifyContainer() = 0;
  virtual void modifyParityIndex() = 0;
};
