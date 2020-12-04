#include "MySQLDb.hpp"

#include <stdexcept>

void MySQLDb::freeResults(MYSQL_RES *aResults)
  {
  mysql_free_result(aResults);
  }

MySQLDb::MySQLDb(const ReMySQLDbConfig &aConfig)
  {
  theDb = mysql_init(theDb);
  if (!theDb)
    throw std::logic_error("Can't init mysql object");
  }

MySQLDb::~MySQLDb()
  {
  close();
  }

void MySQLDb::close()
  {
  if (theDb)
    mysql_close(theDb);
  }

void MySQLDb::connect(const ReDatabaseConfig &aConfig)
  {
  if (!aConfig.isSet())
    throw std::logic_error("Empty database config\n");

  const std::string &host = aConfig.theHost;
  const std::string &user = aConfig.theUser;
  const std::string &password = aConfig.thePassword;
  const std::string &database = aConfig.theDatabase;
  const int &port = aConfig.thePort;
  theDb = mysql_real_connect(theDb,
                             host.c_str(), user.c_str(), password.c_str(), database.c_str(), port,
                             NULL, CLIENT_MULTI_STATEMENTS);
  if (!theDb)
    throw std::logic_error("Can't connect to database\n");
  }

bool MySQLDb::isConnected() const
  {
  return theDb != nullptr;
  }

void MySQLDb::startTransaction()
  {
  const int result = mysql_query(theDb, "start transaction;");
  if (result != 0)
    throw std::logic_error("Can't start transaction\n");
  }

std::optional<MYSQL_RES*> MySQLDb::query(std::string &aSql)
  {
  const int success = mysql_real_query(theDb, aSql.c_str(), static_cast<unsigned long>(aSql.length()));
  if (success == 0)
    {
    if (mysql_field_count(theDb) == 0)
      return {};

    return mysql_store_result(theDb);
    }
  else
    throw std::logic_error(mysql_error(theDb));
  }

void MySQLDb::commit()
  {
  const int result = mysql_commit(theDb);
  if (result != 0)
    throw std::logic_error("Can't commit transaction\n");
  }

void MySQLDb::rollback()
  {
  const int result = mysql_rollback(theDb)
  if (result != 0)
    throw std::logic_error("Can't rollback transaction\n");
  }

std::string MySQLDb::getCurrentTimestamp()
  {
  std::string sql = "select current_timestamp();";
  auto result = query(sql);
  auto value = mysql_fetch_row(*result);

  return std::string(value[0]);
  }
