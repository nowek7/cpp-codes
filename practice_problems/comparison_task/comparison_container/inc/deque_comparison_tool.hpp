#pragma once

#include "comparison_tool.hpp"

#include <deque>

class DequeComparisonTool: public ComparisonTool
{
public:
  DequeComparisonTool();

  void generateSummary(std::ofstream& oFile) final;

protected:
  std::pair<int, int> beginElementsActionSummary() final;
  std::pair<int, int> middleElementsActionSummary() final;
  std::pair<int, int> endElementsActionSummary() final;
  void modifyContainer() final;
  void modifyParityIndex() final;

private:
  std::deque<int> mContainer;
};
