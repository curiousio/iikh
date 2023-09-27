#pragma once

#include <iostream>
#include <vector>
#include "sqlite/sqlite3.h"
#include "databaseManager.h"

class Recipe {
 private:
  DatabaseManager dbm;
  std::string menu_name;
  std::string menu_description;
  std::vector<std::string> menu_ingredient;
  std::string menu_recipe;
 public:
  //noArgsConstructor
  Recipe() : dbm("recipe.db") {
    //createTable
    dbm.executeQuery("CREATE TABLE IF NOT EXISTS recipe (name TEXT, description TEXT, ingredient TEXT, recipe TEXT);");
  }

  void searchRecipe() {
    std::cout << "Select a Mode(1. Print All 2. Select) : ";
    int selectNum;
    std::cin >> selectNum;
    system("cls");
    switch (selectNum) {
      case 1:printAllRecipe();
        break;
      case 2:selectRecipe();
        break;
      default:std::cout << "Wrong Input" << std::endl;
        break;
    }
  }
  void printAllRecipe() {
        std::cout << "All Recipe" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        dbm.executeQuery("SELECT * FROM recipe;");
        std::cout << "----------------------------------------" << std::endl;
  }

  void selectRecipe() {
    std::string name;
    std::cout << "Input Recipe Name : ";
    std::cin >> name;
    std::cout << "----------------------------------------" << std::endl;
    dbm.executeQuery(("SELECT * FROM recipe WHERE name = '" + name + "';").c_str());
    std::cout << "----------------------------------------" << std::endl;
  }

};