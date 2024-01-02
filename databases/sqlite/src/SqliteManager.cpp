#include "db_manager.hpp"

DbManager::DbManager(const std::string_view& dbName, const DbConfig& config): theConfig(config), theName(dbName)
{
  sqlite3* db = nullptr;
  const int res = sqlite3_open_v2(dbName.data(), &db, static_cast<int>(theConfig.flags), theConfig.zVfs);

  auto dbDeleter = [](sqlite3* db) {
    sqlite3_close_v2(db);
  };
  theDb = std::unique_ptr<sqlite3, std::function<void(sqlite3*)>>(db, dbDeleter);

  if (res != SQLITE_OK)
  {
    sqlite3_extended_errcode(theDb.get());
  }
}