#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Recipe {
 private:
  std::string menuName;
  std::string menuDescription;
  std::string menuIngredient;
  std::string menuRecipe;

 public:
  // constructor
  Recipe() = default;

  // getter
  std::string getMenuName() { return menuName; }
  std::string getMenuDescription() { return menuDescription; }
  std::string getMenuIngredient() { return menuIngredient; }
  std::string getMenuRecipe() { return menuRecipe; }

  // setter
  void setMenuName(const std::string &name) { menuName = name; }
  void setMenuDescription(const std::string &description) {
    menuDescription = description;
  }
  void setMenuIngredient(const std::string &ingredient) {
    menuIngredient = ingredient;
  }
  void setMenuRecipe(const std::string &recipe) { menuRecipe = recipe; }

  // 이 부분만 따로 분리시켜 놓은 이유. 문제 2-4 해결.
  void addRecipe() {
    std::cout << "Input Recipe Name: ";
    std::getline(std::cin, menuName);
    std::cout << "Input Recipe Description: ";
    std::getline(std::cin, menuDescription);
    std::cout << "Input Recipe Ingredient: ";
    std::getline(std::cin, menuIngredient);
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
      menuRecipe += std::to_string(index++) + ". ";
      menuRecipe += userInput;
      menuRecipe += "\n";
    }
  }

  void printNameAndDescription() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Name: " << menuName << std::endl;
    std::cout << "Description: " << menuDescription << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }

  void printRecipe() {
    if(menuName.empty()) {
      std::cout << "No Recipe" << std::endl;
      return;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Name: " << menuName << std::endl;
    std::cout << "Description: " << menuDescription << std::endl;
    std::cout << "Ingredient: " << menuIngredient << std::endl;
    std::cout << "Recipe: " << std::endl;
    std::cout << menuRecipe;  // Already contains newline
    std::cout << "----------------------------------------" << std::endl;
  }
};
