#pragma once

#include "comparison_tool.hpp"

#include <list>

class ListComparisonTool: public ComparisonTool
{
public:
  ListComparisonTool();

  void generateSummary(std::ofstream& oFile) final;

protected:
  std::pair<int, int> beginElementsActionSummary() final;
  std::pair<int, int> middleElementsActionSummary() final;
  std::pair<int, int> endElementsActionSummary() final;
  void modifyContainer() final;
  void modifyParityIndex() final;

private:
  std::list<int> mContainer;
};