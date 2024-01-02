#pragma once

#include <mutex>

class ProgressBar
{
public:
  ProgressBar(double aBarWidth, std::string aFill, std::string aRemainders = " ");

  void setProgress(double aValue);
  void setBarWidth(size_t aWidth);
  void fillBarProgressWith(const std::string& aChars);
  void fillBarRemainderWith(const std::string& aChars);
  void setStatusText(const std::string& aStatusText);

  void update(double aValue, std::ostream& aOstream = std::cout);
  void display(std::ostream& aOstream = std::cout);

private:
  std::mutex theMutex;
  double theProgress = 0;
  double theBarWidth = 60;
  std::string theFill = "#";
  std::string theRemainders = " ";
  std::string theStatusText = "";
};
