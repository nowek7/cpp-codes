#pragma once

#include <functional>
#include <memory>
#include <sqlite3.h>
#include <string_view>

enum class DbFlags
{
  READONLY = SQLITE_OPEN_READONLY,
  READWRITE = SQLITE_OPEN_READWRITE,
  CREATE = SQLITE_OPEN_CREATE
};

inline DbFlags operator|(const DbFlags& lhs, const DbFlags& rhs)
{
  return static_cast<DbFlags>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

enum class DbEncoding
{
  ANY = SQLITE_ANY,
  UTF8 = SQLITE_UTF8,
  UTF16 = SQLITE_UTF16
};

struct DbConfig
{
  DbFlags flags = DbFlags::READWRITE | DbFlags::CREATE;
  const char* zVfs = nullptr;
  DbEncoding encoding = DbEncoding::ANY;
};

typedef std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> statement;

class DbManager
{
public:
  DbManager(const std::string_view& dbName, const DbConfig& config = {});
  ~DbManager() = default;

  DbManager(const DbManager&) = delete;
  DbManager& operator=(const DbManager&) = delete;

  bool isConnected() const;
  void startTransaction();
  void commit() const;
  void rollback() const;
  int query();

private:
  std::unique_ptr<sqlite3, std::function<void(sqlite3*)>> theDb;
  DbConfig theConfig;
  const std::string theName;
};