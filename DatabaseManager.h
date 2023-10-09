#pragma once

#include <iostream>
#include <set>

#include "sqlite/sqlite3.h"

class DatabaseManager {
 public:
  int rc;  // SQLite3 리턴 코드

  DatabaseManager(const char *dbName) {
    rc = sqlite3_open(dbName, &db);
    if (rc) {
      std::cerr << "Can't Open Database: " << sqlite3_errmsg(db) << std::endl;
    }
  }

  ~DatabaseManager() { sqlite3_close(db); }

  // 출력용
  void executeQuery(const char *query) {
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, query, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "Error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

  // Meal Class Type으로 받아올 때는 이걸 사용
  void executeQuery(const char *query, void *data) {
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, query, getterCallback, data, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "Error : " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

 private:
  sqlite3 *db;

  // 출력용, Recipe_id, Plan_id는 제외
  static int callback(void *data, int argc, char **argv, char **azColName) {
    std::cout << "----------------------------------------" << std::endl;
    for (int i = 1; i < argc; i++) {
      std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL")
                << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    return 0;
  }

  // set 타입으로 가져오는 용도, select name일 경우에.
  static int getterCallback(void *data, int argc, char **argv,
                            char **azColName) {
    std::set<std::string> *temp = (std::set<std::string> *)data;
    temp->insert(argv[1]);
    return 0;
  }
};
