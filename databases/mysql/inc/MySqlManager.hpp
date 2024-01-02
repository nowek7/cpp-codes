#pragma once

#include "DbConfig.hpp"

#include <mysql/mysql.h>
#include <optional>

class MySqlManager: virtual public IDatabaseManager
{
public:
  static void freeResults(MYSQL_RES* aResults);

public:
  MySQLDb();
  ~MySQLDb();

  void close();
  void connect(const ReDatabaseConfig& aConfig);
  bool isConnected() const;
  void startTransaction();
  std::optional<MYSQL_RES*> query(std::string& aSql);
  void commit();
  void rollback();

  std::string getCurrentTimestamp();

private:
  MYSQL* theDb = nullptr;
};
