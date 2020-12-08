#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

enum class ProcessStatus
  {
  Suspended,
  Running
  };

enum class Platform
  {
  p32bit,
  p64bit
  };

struct ProcessInfo
  {
  int theId;
  std::string theName;
  ProcessStatus theStatus;
  std::string theAccount;
  size_t theMemory;
  Platform thePlatform;
  };

void printProcesses(std::vector<ProcessInfo> aProcesses)
  {
  auto statusToString = [](const ProcessStatus &status)
    {
    return status == ProcessStatus::Suspended ? "suspended" : "running";
    };

  auto platformToString = [](const Platform &aPlatform)
    {
    return aPlatform == Platform::p32bit ? "32-bit" : "64-bit";
    };

  auto comp = [](const ProcessInfo &p1, const ProcessInfo &p2)
              {
              return p1.theName < p2.theName;
              };
  std::sort(std::begin(aProcesses), std::end(aProcesses), comp);
  for (auto const &process : aProcesses)
    {
    std::cout << std::left<< std::setw(25) << std::setfill(' ') << process.theName;
    std::cout << std::left << std::setw(8) << std::setfill(' ') << process.theId;
    std::cout << std::left << std::setw(12) << std::setfill(' ') << statusToString(process.theStatus);
    std::cout << std::left << std::setw(15) << std::setfill(' ') << process.theAccount;
    std::cout << std::right << std::setw(10) << std::setfill(' ') << static_cast<int>(process.theMemory / 1024);
    std::cout << std::left << ' ' << platformToString(process.thePlatform);

    std::cout << std::endl;
   }
}

int main()
  {
  using namespace std::string_literals;

  std::vector<ProcessInfo> processes
    {
      { 512, "cmd.exe"s, ProcessStatus::Running, "SYSTEM"s, 148293, Platform::p64bit },
      { 1044, "chrome.exe"s, ProcessStatus::Running, "marius.bancila"s, 25180454, Platform::p32bit },
      { 7108, "explorer.exe"s, ProcessStatus::Running, "marius.bancila"s, 2952943, Platform::p64bit },
      { 10100, "chrome.exe"s, ProcessStatus::Running, "marius.bancila"s, 227756123, Platform::p32bit },
      { 22456, "skype.exe"s, ProcessStatus::Suspended, "marius.bancila"s, 16870123, Platform::p64bit },
    };

  printProcesses(processes);
  }
