#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <cmath>
// #include "progress_bar.hpp"
// #include "termcolor.hpp"

class ProgressBar
  {
  public:
    ProgressBar(double aBarWidth, std::string aFill, std::string aRemainders = " ");
    void setProgress(double aValue);
    void setBarWidth(size_t aWidth);
    void fillBarProgressWith(const std::string &aChars);
    void fillBarRemainderWith(const std::string &aChars);
    void setStatusText(const std::string &aStatusText);

    void update(double aValue, std::ostream &aOstream = std::cout);
    void display(std::ostream &aOstream = std::cout);

  private:
    std::mutex theMutex;
    double theProgress = 0;
    double theBarWidth  = 60;
    std::string theFill = "#";
    std::string theRemainders = " ";
    std::string theStatusText = "";
  };

ProgressBar::ProgressBar(double aBarWidth, std::string aFill, std::string aRemainders)
  :
  theBarWidth(aBarWidth),
  theFill(aFill),
  theRemainders(aRemainders)
  {}

void ProgressBar::setProgress(double aValue)
  {
  std::unique_lock lock {theMutex};
  theProgress = aValue;
  };

void ProgressBar::setBarWidth(size_t aWidth)
  {
  std::unique_lock lock {theMutex};
  theBarWidth = aWidth;
  }

void ProgressBar::fillBarProgressWith(const std::string &aChars)
  {
  std::unique_lock lock {theMutex};
  theFill = aChars;
  }

void ProgressBar::fillBarRemainderWith(const std::string &aChars)
  {
  std::unique_lock lock {theMutex};
  theRemainders = aChars;
  }

void ProgressBar::setStatusText(const std::string &aChars)
  {
  std::unique_lock lock {theMutex};
  theStatusText = aChars;
  }

void ProgressBar::update(double aValue, std::ostream &aOstream)
  {
  if (aValue <= 100)
    {
    setProgress(aValue);
    display(aOstream);
    }
  }

void ProgressBar::display(std::ostream &aOstream)
  {
  std::unique_lock lock {theMutex};

  //  Move cursor to the first position on the same line and flush.
  aOstream << '\r' << std::flush;

  //  Start bar.
  aOstream << "[";
  const auto completed = static_cast<size_t>(theProgress * static_cast<double>(theBarWidth) / 100);
  for (auto i = 0; i < theBarWidth; i++)
    {
    if (i <= completed)
      aOstream << theFill;
    else
      aOstream << theRemainders;
    }

  //  End bar.
  aOstream << "]";
  aOstream << std::min(static_cast<size_t>(theProgress), static_cast<size_t>(100)) << "%";
  aOstream << " " << theStatusText;
  }

int main()
  {
  // std::cout << termcolor::bold << termcolor::yellow;
  ProgressBar bar{50, "#", " "};

  for (auto i = 1; i <= 100; i++)
    {
    bar.update(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }

  // std::cout << termcolor::reset;
  }