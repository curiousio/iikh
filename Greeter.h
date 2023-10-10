#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DatabaseManager.h"
#include "PlanDB.h"
#include "RecipeDB.h"
#include "sqlite/sqlite3.h"

class Greeter {
 private:
  std::vector<std::string> menu;
  RecipeDB recipeDB;
  PlanDB planDB;

 public:
  Greeter() {
    menu.push_back("SEARCH RECIPE");  // 1
    menu.push_back("ADD RECIPE");     // 2
    menu.push_back("DELETE RECIPE");  // 3
    menu.push_back("UPDATE RECIPE");  // 4
    menu.push_back("SEARCH PLAN");    // 5
    menu.push_back("ADD PLAN");       // 6
    menu.push_back("DELETE PLAN");    // 7
    menu.push_back("UPDATE PLAN");    // 8
    menu.push_back("QUIT");           // 9
  }

  void printAndSelectMenu() {
    int selectNum;
    for (int i = 0; i < menu.size(); i++) {
      std::cout << i + 1 << ". " << menu[i] << std::endl;
    }
    std::cout << "Select Menu: ";
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거
    system("cls");
    std::cout << "Selected Menu: " << menu[selectNum - 1] << std::endl;

    switch (selectNum) {
      case 1:
        recipeDB.searchRecipe();
        break;
      case 2:
        recipeDB.addRecipe();
        break;
      case 3:
        recipeDB.deleteRecipe();
        break;
      case 4:
        recipeDB.updateRecipe();
        break;
      case 5:
        planDB.searchPlan();
        break;
      case 6:
        planDB.addPlan();
        break;
      case 7:
        planDB.deletePlan();
        break;
      case 8:
        planDB.updatePlan();
        break;
      case 9:
        quit();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  static void quit() {
    std::cout << "Bye" << std::endl;
    exit(0);
  }
};
