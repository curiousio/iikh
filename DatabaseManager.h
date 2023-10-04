#pragma once

#include <iostream>
#include "sqlite/sqlite3.h"

//Meal쪽 없어서 일단 임시로 만들어놓은 클래스. 생기면 삭제후 수정 부탁.
class Meal {
 public:
  std::string menu_name;
  std::string menu_description;
  std::string menu_ingredient;
  std::string menu_recipe;

  void setData(const std::string &col1, const std::string &col2, const std::string &col3, const std::string &col4) {
    menu_name = col1;
    menu_description = col2;
    menu_ingredient = col3;
    menu_recipe = col4;
  }
};

class DatabaseManager {
 public:
  int rc; // SQLite3 리턴 코드

  DatabaseManager(const char *dbName) {
    rc = sqlite3_open(dbName, &db);
    if (rc) {
      std::cerr << "Can't Open Database : " << sqlite3_errmsg(db) << std::endl;
    }
  }

  ~DatabaseManager() {
    sqlite3_close(db);
  }

  //출력용
  void executeQuery(const char *query) {
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, query, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "Error : " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

  //Meal Class Type으로 받아올때는 이걸 사용
  void executeQuery(const char *query, Meal *data) {
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, query, getterCallback, data, &errMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "Error : " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

 private:
  sqlite3 *db;

  //출력용, Recipe_id, Plan_id는 제외
  static int callback(void *data, int argc, char **argv, char **azColName) {
    std::cout << "----------------------------------------" << std::endl;
    for (int i = 1; i < argc; i++) {
      std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    return 0;
  }

  //Meal 타입으로 가져오는용도, Recipe_id는 제외.
  static int getterCallback(void *data, int argc, char **argv, char **azColName) {
    if (argc == 5) {
      Meal *dataStorage = static_cast<Meal *>(data);
      dataStorage->setData(argv[1] ? argv[1] : "NULL",
                           argv[2] ? argv[2] : "NULL",
                           argv[3] ? argv[3] : "NULL",
                           argv[4] ? argv[4] : "NULL");
    }
    return 0;
  }

};
