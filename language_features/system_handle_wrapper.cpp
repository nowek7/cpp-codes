#ifdef _WIN32
  #include <windows.h>
#else
typedef void* HANDLE;

  #define DWORD unsigned long

  #ifdef _LP64
    #define LONG_PTR long long
    #define ULONG_PTR unsigned long long
  #else
    #define LONG_PTR long
    #define ULONG_PTR unsigned long
  #endif

  #define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

struct SECURITY_ATTRIBUTES
{
  DWORD nLength;
  void* lpSecurityDescriptor;
  int bInheritHandle;
};

struct OVERLAPPED
{
  ULONG_PTR Internal;
  ULONG_PTR InternalHigh;
  union
  {
    struct
    {
      DWORD Offset;
      DWORD OffsetHigh;
    } DUMMYSTRUCTNAME;

    void* Pointer;
  } DUMMYUNIONNAME;

  HANDLE hEvent;
};

int CloseHandle(HANDLE hObject)
{
  return 0;
}

HANDLE CreateFile(const char*, DWORD, DWORD, SECURITY_ATTRIBUTES*, DWORD, DWORD, HANDLE)
{
  return INVALID_HANDLE_VALUE;
}

int ReadFile(HANDLE, void*, DWORD, DWORD*, OVERLAPPED*)
{
  return 0;
}

  #define GENERIC_READ 0x80000000L
  #define GENERIC_WRITE 0x40000000L
  #define CREATE_NEW 1
  #define CREATE_ALWAYS 2
  #define OPEN_EXISTING 3
  #define OPEN_ALWAYS 4
  #define TRUNCATE_EXISTING 5
  #define FILE_SHARE_READ 1
  #define FILE_ATTRIBUTE_NORMAL 0x00000080
#endif

#include <algorithm>
#include <stdexcept>
#include <vector>

template<typename Traits>
class UniqueHandle
{
  using pointer = typename Traits::pointer;

  pointer theValue;

public:
  UniqueHandle(const UniqueHandle&) = delete;
  UniqueHandle& operator=(const UniqueHandle&) = delete;

  explicit UniqueHandle(pointer aValue = Traits::invalid()) noexcept:
    theValue{aValue}
  {
  }

  UniqueHandle(UniqueHandle&& aOther) noexcept:
    theValue{aOther.release()}
  {
  }

  ~UniqueHandle() noexcept
  {
    Traits::close(theValue);
  }

  UniqueHandle& operator=(UniqueHandle&& aOther) noexcept
  {
    if (this != &aOther)
    {
      reset(aOther.release());
    }

    return *this;
  }

  explicit operator bool() const noexcept
  {
    return theValue != Traits::invalid();
  }

  pointer get() const noexcept
  {
    return theValue;
  }

  pointer release() noexcept
  {
    auto value = theValue;
    theValue = Traits::invalid();
    return value;
  }

  bool reset(pointer value = Traits::invalid()) noexcept
  {
    if (theValue != value)
    {
      Traits::close(theValue);
      theValue = value;
    }

    return static_cast<bool>(*this);
  }

  void swap(UniqueHandle<Traits>& other) noexcept
  {
    std::swap(theValue, other.theValue);
  }
};

template<typename Traits>
void swap(UniqueHandle<Traits>& aLeft, UniqueHandle<Traits>& aRight) noexcept
{
  aLeft.swap(aRight);
}

template<typename Traits>
bool operator==(const UniqueHandle<Traits>& aLeft, const UniqueHandle<Traits>& aRight) noexcept
{
  return aLeft.get() == aRight.get();
}

template<typename Traits>
bool operator!=(const UniqueHandle<Traits>& aLeft, const UniqueHandle<Traits>& aRight) noexcept
{
  return aLeft.get() != aRight.get();
}

struct NullHandleTraits
{
  using pointer = HANDLE;

  static pointer invalid() noexcept
  {
    return nullptr;
  }

  static void close(pointer aValue) noexcept
  {
    CloseHandle(aValue);
  }
};

struct InvalidHandleTraits
{
  using pointer = HANDLE;

  static pointer invalid() noexcept
  {
    return INVALID_HANDLE_VALUE;
  }

  static void close(pointer value) noexcept
  {
    CloseHandle(value);
  }
};

using nullHandle = UniqueHandle<NullHandleTraits>;
using invalidHandle = UniqueHandle<InvalidHandleTraits>;

void functionThatThrows()
{
  throw std::runtime_error("An error has occurred!");
}

void badHandleExample()
{
  bool condition1 = false;
  bool condition2 = true;
  HANDLE handle =
    CreateFile("sample.txt", GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

  if (handle == INVALID_HANDLE_VALUE)
  {
    return;
  }

  if (condition1)
  {
    CloseHandle(handle);
    return;
  }

  std::vector<char> buffer(1024);
  unsigned long bytesRead = 0;
  ReadFile(handle, buffer.data(), buffer.size(), &bytesRead, nullptr);

  if (condition2)
  {
    // oops, forgot to close handle
    return;
  }

  // Throws exception; the next line will not execute
  functionThatThrows();

  CloseHandle(handle);
}

void goodHandleExample()
{
  bool condition1 = false;
  bool condition2 = true;

  invalidHandle handle{
    CreateFile("sample.txt", GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr)};

  if (!handle)
  {
    return;
  }

  if (condition1)
  {
    return;
  }

  std::vector<char> buffer(1024);
  unsigned long bytesRead = 0;
  ReadFile(handle.get(), buffer.data(), buffer.size(), &bytesRead, nullptr);

  if (condition2)
  {
    return;
  }

  functionThatThrows();
}

int main()
{
  try
  {
    badHandleExample();
  }
  catch (...)
  {
  }

  try
  {
    goodHandleExample();
  }
  catch (...)
  {
  }

  return 0;
}
