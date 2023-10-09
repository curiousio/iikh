#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "DatabaseManager.h"
#include "Recipe.h"
#include "sqlite/sqlite3.h"

class RecipeDB {
 private:
  DatabaseManager dbm;

 public:
  // noArgsConstructor
  RecipeDB() : dbm("iikh.db") {
    // createTable
    dbm.executeQuery(
        "CREATE TABLE IF NOT EXISTS recipe (recipe_id INTEGER PRIMARY KEY "
        "AUTO INCREMENT, name TEXT, description TEXT, ingredient TEXT, recipe "
        "TEXT);");
  }

  void searchRecipe() {
    std::cout << "Select a Mode (1. Print All 2. Select): ";
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
    std::vector<Recipe> recipes;
    dbm.executeQuery("SELECT * FROM recipe;", &recipes, true);
    for (auto &recipe : recipes) {
      recipe.printNameAndDescription();
    }
  }

  void selectRecipe() {
    Recipe recipe;
    std::string name;
    std::cout << "Input Recipe Name: ";
    std::getline(std::cin, name);
    dbm.executeQuery(
        ("SELECT * FROM recipe WHERE name = '" + name + "';").c_str(), &recipe);
    ;
  }

  void addRecipe() {
    Recipe recipe;
    recipe.addRecipe();
    dbm.executeQuery(
        ("INSERT INTO recipe (name, description, ingredient, recipe) VALUES "
         "('" +
            recipe.getMenuName() + "', '" + recipe.getMenuDescription() + "', '" +
            recipe.getMenuIngredient() + "', '" + recipe.getMenuRecipe() + "');")
            .c_str());
  }


  void deleteRecipe() {
    std::string menu_recipe;
    std::cout << "Input Target Recipe Name : ";
    std::getline(std::cin, menu_recipe);
    dbm.executeQuery(
        ("DELETE FROM recipe WHERE recipe='" + menu_recipe + "';").c_str());
  }


  void updateRecipe() {
    std::string item, content, menu_recipe;
    std::cout << "Input Target Recipe Name : ";
    std::getline(std::cin, menu_recipe);
    std::cout << "What item do you want to update?(name, description, "
                 "ingredient, recipe) : ";
    std::getline(std::cin, item);
    std::cout << "What do you want to update it to?: ";
    std::getline(std::cin, content);
    dbm.executeQuery(("UPDATE recipe SET " + item + "='" + content +
        "' WHERE recipe=" + menu_recipe)
                         .c_str());
  }
};