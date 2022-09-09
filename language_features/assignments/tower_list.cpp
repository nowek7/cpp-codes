#include <cstdio>
#include <vector>

class TowerList
{
public:
  TowerList():
    theMaxHeightIdx{1},
    theTowerHeights{25.0f, 44.0f, 12.0f}
  {
  }

  auto getMaxTowerHeight() const
  {
    return theMaxHeightIdx >= 0 ? theTowerHeights[theMaxHeightIdx] : 0.0f;
  }

  TowerList(TowerList&& aTowerList) noexcept
  {
    printf("Move constructor\n");
    std::swap(theTowerHeights, aTowerList.theTowerHeights);
    std::swap(theMaxHeightIdx, aTowerList.theMaxHeightIdx);
  }

  auto& operator=(TowerList&& aTowerList) noexcept
  {
    printf("Move assignment\n");
    std::swap(theTowerHeights, aTowerList.theTowerHeights);
    std::swap(theMaxHeightIdx, aTowerList.theMaxHeightIdx);
    return *this;
  }

  std::vector<float> theTowerHeights{};
  int theMaxHeightIdx{-1};
};

int main()
{
  auto tower = TowerList{};

  // Move-constructor
  auto towerBridge = std::move(tower);

  // Move-assignment
  auto towerHeart = TowerList{};
  towerBridge = std::move(towerHeart);

  auto maxHeight = tower.getMaxTowerHeight();
}