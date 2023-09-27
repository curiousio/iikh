#pragma once

#include <iostream>
#include "sqlite/sqlite3.h"

class DatabaseManager {
 public:
  int rc; // SQLite3 리턴 코드

  DatabaseManager(const char* dbName) {
    rc = sqlite3_open(dbName, &db);
    if (rc) {
      std::cerr << "Can't Open Database : " << sqlite3_errmsg(db) << std::endl;
    }
  }

  ~DatabaseManager() {
    sqlite3_close(db);
  }

  void executeQuery(const char* query) {
    char* errMsg = nullptr;
    rc = sqlite3_exec(db, query, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "Error : " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

 private:
  sqlite3* db;

  static int callback(void* data, int argc, char** argv, char** azColName) {
    std::cout << "----------------------------------------" << std::endl;
    for (int i = 0; i < argc; i++) {
      std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    return 0;
  }
};
