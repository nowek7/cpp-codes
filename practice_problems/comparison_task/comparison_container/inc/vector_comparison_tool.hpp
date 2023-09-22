#pragma once

#include "comparison_tool.hpp"

#include <vector>

class VectorComparisonTool: public ComparisonTool
{
public:
  VectorComparisonTool();
  void generateSummary(std::ofstream& oFile) final;

protected:
  std::pair<int, int> beginElementsActionSummary() final;
  std::pair<int, int> middleElementsActionSummary() final;
  std::pair<int, int> endElementsActionSummary() final;
  void modifyContainer() final;
  void modifyParityIndex() final;

private:
  std::vector<int> mContainer;
};
