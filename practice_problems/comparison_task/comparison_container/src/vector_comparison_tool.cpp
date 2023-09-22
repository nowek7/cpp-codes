#include "vector_comparison_tool.hpp"

#include "utils.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>

VectorComparisonTool::VectorComparisonTool():
  ComparisonTool()
{
}

void VectorComparisonTool::generateSummary(std::ofstream& oFile)
{
  for (const auto size: SIZES) {
    mSize = size;

    const auto [beginAddTime, beginRmTime] = beginElementsActionSummary();
    const auto [middleAddTime, middleRmTime] = middleElementsActionSummary();
    const auto [endAddTime, endRmTime] = endElementsActionSummary();

    std::generate(mContainer.begin(), mContainer.end(), [this]() {
      return mUid(mGenerator);
    });
    auto modifyTime = performanceTimer<>::duration(&VectorComparisonTool::modifyParityIndex, this);
    auto modifyParityTime = performanceTimer<>::duration(&VectorComparisonTool::modifyParityIndex, this);

    try {
      std::ostringstream oss;
      oss << size << ",";
      oss << beginAddTime << "," << middleAddTime << "," << endAddTime << ",";
      oss << beginRmTime << "," << middleRmTime << "," << endRmTime << ",";
      oss << modifyTime.count() << "," << modifyParityTime.count() << "\n";

      const std::string line = oss.str();
      oFile.write(line.c_str(), line.size());
    } catch (const std::ios_base::failure& ex) {
      std::cout << "Failed to write data to file! - " << ex.what() << "\n";
    }
  }
}

std::pair<int, int> VectorComparisonTool::beginElementsActionSummary()
{
  auto addElementAtBegin = [this]() {
    while (mContainer.size() != mSize) {
      mContainer.insert(std::begin(mContainer), mUid(mGenerator));
    }
  };

  const auto addTime = performanceTimer<>::duration(addElementAtBegin);

  auto removeElementAtBegin = [this]() {
    while (!mContainer.empty()) {
      mContainer.erase(std::begin(mContainer));
    }
  };
  const auto rmTime = performanceTimer<>::duration(removeElementAtBegin);

  return std::make_pair(rmTime.count(), addTime.count());
}

std::pair<int, int> VectorComparisonTool::middleElementsActionSummary()
{
  auto middleIdx = [this]() {
    const int middleIdx = mContainer.size() / 2;
    return std::begin(mContainer) + middleIdx;
  };

  auto addElementAtMiddle = [this, &middleIdx]() {
    for (auto it = middleIdx(); mContainer.size() != mSize; it = middleIdx()) {
      mContainer.insert(it, mUid(mGenerator));
    }
  };
  const auto addTime = performanceTimer<>::duration(addElementAtMiddle);

  auto removeElementAtMiddle = [this, &middleIdx]() {
    while (!mContainer.empty()) {
      mContainer.erase(middleIdx());
    }
  };
  const auto rmTime = performanceTimer<>::duration(removeElementAtMiddle);

  return std::make_pair(rmTime.count(), addTime.count());
}

std::pair<int, int> VectorComparisonTool::endElementsActionSummary()
{
  auto addElementAtEnd = [this]() {
    while (mContainer.size() != mSize) {
      mContainer.push_back(mUid(mGenerator));
    }
  };
  const auto addTime = performanceTimer<>::duration(addElementAtEnd);

  auto removeElementAtEnd = [this]() {
    while (mContainer.size() != 0) {
      mContainer.pop_back();
    }
  };
  const auto rmTime = performanceTimer<>::duration(removeElementAtEnd);

  return std::make_pair(addTime.count(), rmTime.count());
}

void VectorComparisonTool::modifyContainer()
{
  auto pred = [](int& elem) {
    elem += 1;
  };
  std::for_each(mContainer.begin(), mContainer.end(), pred);
}

void VectorComparisonTool::modifyParityIndex()
{
  for (std::size_t i = 0; i < mContainer.size(); i += 2) {
    mContainer[i] += 1;
  }
}