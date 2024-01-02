#pragma once

#include <string>

class IDatabaseManager
{
public:
  IDatabaseManager() = delete;
  IDatabaseManager(const IDatabaseManager&) = delete;
  IDatabaseManager& operator=(const IDatabaseManager&) = delete;
  ~IDatabaseManager() = default;

  virtual void startTransaction() = 0;
  virtual void commit() = 0;
  virtual void rollback() = 0;

  virtual bool isEmpty() = 0;
  virtual bool isConnected() = 0;
  virtual std::string getCurrentTimestamp() = 0;
};