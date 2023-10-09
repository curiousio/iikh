#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <string>

class Recipe {
 private:
  std::string menu_name;
  std::string menu_description;
  std::string menu_ingredient;
  std::string menu_recipe;

 public:
  //constructor
  Recipe() = default;

  //getter
  std::string getMenuName() { return menu_name; }
  std::string getMenuDescription() { return menu_description; }
  std::string getMenuIngredient() { return menu_ingredient; }
  std::string getMenuRecipe() { return menu_recipe; }

  //setter
  void setMenuName(const std::string &name) { menu_name = name; }
  void setMenuDescription(const std::string &description) { menu_description = description; }
  void setMenuIngredient(const std::string &ingredient) { menu_ingredient = ingredient; }
  void setMenuRecipe(const std::string &recipe) { menu_recipe = recipe; }

  //이부분만 따로 분리시켜 놓은 이유. 문제 2-4 해결.
  void addRecipe() {
    std::cout << "Input Recipe Name: ";
    std::getline(std::cin, menu_name);
    std::cout << "Input Recipe Description: ";
    std::getline(std::cin, menu_description);
    std::cout << "Input Recipe Ingredient: ";
    std::getline(std::cin, menu_ingredient);
    std::cout << "Input Recipe Recipe(Enter를 누르면 다음 입력으로 넘어가고, 마지막에 끝맺음은 온점 2개를 쓰시면 됩니다.\n"
                 "순서를 나타내는 숫자를 적을 필요는 없습니다.): ";
    std::vector<std::string> temps;
    int idx = 1;
    while (true) {
      std::string temp;
      std::getline(std::cin, temp);
      if (temp == "..") {
        break;
      }
      menu_recipe += std::to_string(idx++) + ". ";
      menu_recipe += temp;
      menu_recipe += "\n";
    }
  }

  void printNameAndDescription() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Name: " << menu_name << std::endl;
    std::cout << "Description: " << menu_description << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }

  void printRecipe() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Name: " << menu_name << std::endl;
    std::cout << "Description: " << menu_description << std::endl;
    std::cout << "Ingredient: " << menu_ingredient << std::endl;
    std::cout << "Recipe: " << std::endl;
    std::cout << menu_recipe << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }
};

