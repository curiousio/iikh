#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "DatabaseManager.h"
#include "Recipe.h"
#include "Similarity.h"

class RecipeDB {
 private:
  DatabaseManager dbm;

 public:
  // noArgsConstructor
  RecipeDB() : dbm("iikh.db") {
    // createTable
    dbm.executeQuery(
        "CREATE TABLE IF NOT EXISTS recipe (recipe_id INTEGER PRIMARY KEY "
        "AUTOINCREMENT, name TEXT, description TEXT, ingredient TEXT, recipe "
        "TEXT);");
  }

  void searchRecipe() {
    std::cout << "Select a Mode (1. Print All 2. Select): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();
    system("cls");
    switch (selectNum) {
      case 1:
        printAllRecipe();
        break;
      case 2:
        selectRecipe();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void printAllRecipe() {
    std::cout << "All Recipe" << std::endl;
    std::vector<Recipe> recipes;
    dbm.executeQuery("SELECT * FROM recipe;", &recipes, true);
    if (recipes.empty()) {
      std::cout << "No Recipe" << std::endl;
      return;
    }
    for (auto &recipe : recipes) {
      recipe.printNameAndDescription();
    }
    std::cout << "Do you want to see a specific recipe? [y/n]: ";
    char select;
    std::cin >> select;
    std::cin.ignore();
    if (select == 'y') {
      std::cout << "Input Recipe Name: ";
      std::string name;
      std::getline(std::cin, name);
      selectRecipe(name);
    }
  }

  void selectRecipe() {
    Recipe recipe;
    std::string name;
    std::cout << "Input Recipe Name: ";
    std::getline(std::cin, name);
    dbm.executeQuery(
        ("SELECT * FROM recipe WHERE name = '" + name + "';").c_str(), &recipe);
    if (recipe.printRecipe() == 1) {
        Similarity similarity(name);
        similarity.checkSimilarity(2);
    }
  }

  void selectRecipe(const std::string &name) {
    Recipe recipe;
    dbm.executeQuery(
        ("SELECT * FROM recipe WHERE name = '" + name + "';").c_str(), &recipe);
    recipe.printRecipe();
  }

  Recipe selectRecipe(const std::string &name, int) {
    Recipe recipe;
    dbm.executeQuery(
        ("SELECT * FROM recipe WHERE name = '" + name + "';").c_str(), &recipe);
    return recipe;
  }

  void addRecipe() {
    Recipe recipe;
    recipe.addRecipe();
    std::set<std::string> recipeNames = getRecipeNames();
    if (recipeNames.find(recipe.getMenuName()) != recipeNames.end()) {
      std::cout << "Already Exist" << std::endl;
      return;
    }
    dbm.executeQuery(
        ("INSERT INTO recipe (name, description, ingredient, recipe) VALUES "
         "('" +
         recipe.getMenuName() + "', '" + recipe.getMenuDescription() + "', '" +
         recipe.getMenuIngredient() + "', '" + recipe.getMenuRecipe() + "');")
            .c_str());
  }

  void deleteRecipe() {
    std::string menu_recipe;
    std::set<std::string> recipeNames = getRecipeNames();
    std::cout << "Input Target Recipe Name: ";
    std::getline(std::cin, menu_recipe);
    if (recipeNames.find(menu_recipe) == recipeNames.end()) {
      std::cout << "Wrong Input" << std::endl;
      Similarity similarity(menu_recipe);
      similarity.checkSimilarity(2);
      return;
    }
    dbm.executeQuery(
        ("DELETE FROM recipe WHERE name='" + menu_recipe + "';").c_str());
  }

  void updateRecipe() {
    std::string item, content, menu_recipe;
    std::set<std::string> recipeNames = getRecipeNames();
    std::cout << "Input Target Recipe Name: ";
    std::getline(std::cin, menu_recipe);
    if (recipeNames.find(menu_recipe) == recipeNames.end()) {
      std::cout << "Wrong Input" << std::endl;
      Similarity similarity(menu_recipe);
      similarity.checkSimilarity(2);
      return;
    }
    std::cout << "What would you like to change? (name, description, "
                 "ingredient, recipe): ";
    std::getline(std::cin, item);
    if (item != "name" && item != "description" && item != "ingredient" &&
        item != "recipe") {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    if (item == "recipe") {
      std::cout << "Input Recipe Method (To finish, just press Enter)"
                << std::endl;
      int index = 1;
      while (true) {
        std::cout << "Step " << index << ": ";
        std::string userInput;
        std::getline(std::cin, userInput);
        if (userInput.compare("") == 0) {
          break;
        }
        content += std::to_string(index++) + ". ";
        content += userInput;
        content += "\n";
      }
    } else {
      std::cout << "What would you like to change the " + item + " to?: ";
      std::getline(std::cin, content);
    }
    dbm.executeQuery(("UPDATE recipe SET " + item + " = '" + content +
                      "' WHERE name = '" + menu_recipe + "';")
                         .c_str());
  }

  std::set<std::string> getRecipeNames() {
    std::set<std::string> recipeNames;
    dbm.executeQuery("SELECT name FROM recipe;", &recipeNames, true);
    return recipeNames;
  }
};
