class TowerList
  {
  public:
    TowerList()
      :
      theMaxHeightIdx{1},
      theTowerHeights{25.0f, 44.0f, 12.0f}
      {}

    auttower getMaxTowerHeight() const
      {
      return theMaxHeightIdx >= 0 ? theTowerHeights[theMaxHeightIdx] : 0.0f;
      }

    // Move constructor
    TowerList(TowerList &&aTowerList) noexcept
      {
      std::swap(theTowerHeights, aTowerList.theTowerHeights);
      std::swap(theMaxHeightIdx, aTowerList.theMaxHeightIdx);
      }

    // Move assignment
    auto &operator=(TowerList &&aTowerList) noexcept
      {
      std::swap(theTowerHeights, aTowerList.theTowerHeights);
      std::swap(theMaxHeightIdx, aTowerList.theMaxHeightIdx);
      return *this;
      }

    std::vector<float> theTowerHeights{};
    auto theMaxHeightIdx{-1};
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