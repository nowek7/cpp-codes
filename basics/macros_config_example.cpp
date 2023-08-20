#include <iostream>
#include <iomanip>
#include <ostream>
#include <string>

struct Config
  {
  std::string theCompiler;
  std::string theCompilerVersion;
  std::string theArchitecture;
  std::string theConfiguration;

  Config()
    {
    setCompiler();
    setCompilerVersion();
    setArchitecture();
    setConfiguration();
    }

  friend std::ostream& operator<<(std::ostream &os, const Config &aConfig)
    {
    os << std::setw(18) << std::left << "Compiler: " << std::right << aConfig.theCompiler << std::endl;
    os << std::setw(18) << std::left << "Compiler version: " << std::right << aConfig.theCompilerVersion << std::endl;
    os << std::setw(18) << std::left << "Architecture: " << std::right << aConfig.theArchitecture << std::endl;
    os << std::setw(18) << std::left << "Configuration: " << std::right << aConfig.theConfiguration << std::endl;

    return os;
    }

  private:
    void setCompiler()
      {
      #if defined _MSC_VER
        theCompiler =  "Visual C++";
      #elif defined __clang__
        theCompiler =  "Clang";
      #elif defined __GNUG__
        theCompiler =  "GCC";
      #else
        theCompiler =  "Unknown compiler";
      #endif
      }

    void setCompilerVersion()
      {
      #if defined _MSC_VER
        #if (_MSC_VER >= 1900)
          theCompilerVersion = "Visual C++ 2015 or newer";
        #else
         theCompilerVersion = "Visual C++ " + std::string(_MSC_FULL_VER);
        #endif
      #elif defined __clang__
        #if (__clang_major__ == 3) && (__clang_minor__ >= 9)
          theCompilerVersion = "Clang 3.9 or newer";
        #else
          theCompilerVersion = "Clang " + std::string(__clang_version__);
        #endif
      #elif defined __GNUG__
        #if __GNUC__ >= 5 && __GNUC_MINOR__ > 0
          theCompilerVersion = "GCC 5.0 or newer";
        #else
          theCompilerVersion = "GCC " + std::string(__VERSION__);
        #endif
      #else
        throw "Unknown compiler";
      #endif
      }

    void setArchitecture()
      {
      #if defined _MSC_VER
        #if defined _M_X64
         theArchitecture = "AMD64";
        #elif defined _M_IX86
          theArchitecture = "INTEL x86";
        #elif defined _M_ARM
          theArchitecture = "ARM";
        #else
          theArchitecture = "Unknown";
        #endif
      #elif defined __clang__ || __GNUG__
        #if defined __amd64__
          theArchitecture = "AMD64";
        #elif defined __i386__
          theArchitecture = "INTEL x86";
        #elif defined __arm__
          theArchitecture = "ARM";
        #else
          theArchitecture = "Unknown";
        #endif
      #else
        throw "Unknown compiler";
      #endif
      }

    void setConfiguration()
      {
      #ifdef _DEBUG
        theConfiguration = "Debug";
      #else
        theConfiguration = "Release";
      #endif
      }
  };

int main()
  {
  Config config;
  std::cout << config;
  }