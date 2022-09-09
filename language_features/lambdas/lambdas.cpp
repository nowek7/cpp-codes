#include <functional>
#include <iostream>

class Button
{
public:
  Button(std::function<void(void)> aClick):
    theOnClick{aClick}
  {
  }

  auto onClick() const
  {
    theOnClick();
  }

private:
  std::function<void(void)> theOnClick{};
};

auto makeButtons()
{
  auto beepBtn = Button(
    [beepCount = 0]() mutable
    {
      std::cout << "Beep: " << beepCount << "! " << std::endl;
      ++beepCount;
    });

  auto bopBtn = Button([]() { std::cout << "Bop. " << std::endl; });
  auto silentBtn = Button([]() {});

  return std::vector<Button>{beepBtn, bopBtn, silentBtn};
}

int main()
{
  auto buttons = makeButtons();
  for (const auto& btn: buttons)
  {
    btn.onClick();
  }

  buttons.front().onClick();

  return 0;
}
