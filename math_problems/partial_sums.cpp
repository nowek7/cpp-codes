#include <iostream>
#include <vector>

std::vector<int> getPartialSumFromSequence(const std::vector<int>& sequence)
{
  const auto size = sequence.size();
  std::vector<int> partialSums(size + 1);
  for (auto i = 0; i < size; ++i) {
    partialSums[i + 1] = partialSums[i] + sequence[i];
  }

  return partialSums;
}

int main()
{
  std::vector<int> sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (auto sum: getPartialSumFromSequence(sequence)) {
    std::cout << sum << '\n';
  }

  return 0;
}