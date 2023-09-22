#include "deque_comparison_tool.hpp"
#include "list_comparison_tool.hpp"
#include "vector_comparison_tool.hpp"

#include <array>
#include <sstream>
#include <string>

namespace {
  constexpr int NUM_COLUMNS = 9;
  const std::array<std::string, NUM_COLUMNS> HEADER = {"count_elements",
                                                       "add_at_begin",
                                                       "add_at_middle",
                                                       "add_at_end",
                                                       "remove_at_begin",
                                                       "remove_at_middle",
                                                       "remove_at_end",
                                                       "modify_all_index",
                                                       "modify_parity_idx"};

  std::string csvHeader()
  {
    std::ostringstream header;
    for (int i = 0; i < NUM_COLUMNS - 1; ++i) {
      header << HEADER[i] << ",";
    }
    header << *(HEADER.end() - 1) << "\n";
    return header.str();
  }
} // namespace

int main()
{
  // std::vector
  {
    VectorComparisonTool tool;
    const std::string csvFile = "vector.csv";
    std::ofstream oFile(csvFile.c_str());
    if (oFile) {
      const std::string header = csvHeader();
      oFile.write(header.c_str(), header.size());
      tool.generateSummary(oFile);

      oFile.close();
    }
  }

  // std::list
  {
    ListComparisonTool tool;
    const std::string csvFile = "list.csv";
    std::ofstream oFile(csvFile.c_str());
    if (oFile) {
      const std::string header = csvHeader();
      oFile.write(header.c_str(), header.size());
      tool.generateSummary(oFile);

      oFile.close();
    }
  }

  // std::deque
  {
    DequeComparisonTool tool;
    const std::string csvFile = "deque.csv";
    std::ofstream oFile(csvFile.c_str());
    if (oFile) {
      const std::string header = csvHeader();
      oFile.write(header.c_str(), header.size());
      tool.generateSummary(oFile);

      oFile.close();
    }
  }

  return 0;
}