#pragma once

#include <iostream>
#include <set>

#include "Plan.h"
#include "Recipe.h"
#include "sqlite/sqlite3.h"

class DatabaseManager {
 public:
  int rc;  // SQLite3 return code

  DatabaseManager(const char *dbName) {
    rc = sqlite3_open(dbName, &db);

    if (rc) {
      std::cerr << "Can't Open Database: " << sqlite3_errmsg(db) << std::endl;
    }
  }

  ~DatabaseManager() { sqlite3_close(db); }

  void executeQuery(const char *query) {
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, query, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
      std::cerr << "Error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

  // Recipe & Plan
  void executeQuery(const char *query, void *data) {
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, query, getterCallback, data, &errMsg);

    if (rc != SQLITE_OK) {
      std::cerr << "Error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

  // vector
  void executeQuery(const char *query, void *data, int) {
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, query, vectorCallback, data, &errMsg);

    if (rc != SQLITE_OK) {
      std::cerr << "Error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

 private:
  sqlite3 *db;

  // argc 5: Recipe, 6: Plan
  static int getterCallback(void *data, int argc, char **argv,
                            char **azColName) {
    // RecipeDB
    if (argc == 5) {
      Recipe *recipe = static_cast<Recipe *>(data);

      recipe->setMenuName(argv[1] ? argv[1] : "NULL");
      recipe->setMenuDescription(argv[2] ? argv[2] : "NULL");
      recipe->setMenuIngredient(argv[3] ? argv[3] : "NULL");
      recipe->setMenuRecipe(argv[4] ? argv[4] : "NULL");
    }

    // PlanDB
    if (argc == 6) {
      Plan *plan = static_cast<Plan *>(data);

      plan->setName(argv[1] ? argv[1] : "NULL");
      plan->setDate(argv[2] ? argv[2] : "NULL");
      plan->setBreakfast(argv[3] ? argv[3] : "NULL");
      plan->setLunch(argv[4] ? argv[4] : "NULL");
      plan->setDinner(argv[5] ? argv[5] : "NULL");
    }

    return 0;
  }

  // vector
  static int vectorCallback(void *data, int argc, char **argv,
                            char **azColName) {
    // RecipeDB
    if (argc == 5) {
      std::vector<Recipe> *recipe = static_cast<std::vector<Recipe> *>(data);
      Recipe temp;

      temp.setMenuName(argv[1] ? argv[1] : "NULL");
      temp.setMenuDescription(argv[2] ? argv[2] : "NULL");
      temp.setMenuIngredient(argv[3] ? argv[3] : "NULL");
      temp.setMenuRecipe(argv[4] ? argv[4] : "NULL");
      recipe->push_back(temp);
    }

    // Name & Ingredient of RecipeDB, Name & Date of PlanDB
    if (argc == 1) {
      std::set<std::string> *name = static_cast<std::set<std::string> *>(data);

      name->insert(argv[0] ? argv[0] : "NULL");
    }

    // PlanDB
    if (argc == 6) {
      std::vector<Plan> *plan = static_cast<std::vector<Plan> *>(data);
      Plan temp;

      temp.setName(argv[1] ? argv[1] : "NULL");
      temp.setDate(argv[2] ? argv[2] : "NULL");
      temp.setBreakfast(argv[3] ? argv[3] : "NULL");
      temp.setLunch(argv[4] ? argv[4] : "NULL");
      temp.setDinner(argv[5] ? argv[5] : "NULL");
      plan->push_back(temp);
    }

    return 0;
  }
};
