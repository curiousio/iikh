#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "DatabaseManager.h"
#include "Plan.h"
#include "sqlite/sqlite3.h"

class PlanDB {
 private:
  DatabaseManager dbm;
  RecipeDB recipe_db_;

 public:
  PlanDB() : dbm("iikh.db") {
    // createTable
    dbm.executeQuery(
        "CREATE TABLE IF NOT EXISTS plan (plan_id INTEGER PRIMARY KEY "
        "AUTOINCREMENT, name TEXT, date TEXT, breakfast TEXT, lunch TEXT, "
        "dinner text);");
  }

  void searchPlan() {
    std::cout << "Select a Mode (1. Print All Date Plan, 2. Print All Name "
                 "Plan 3. Select Date, 4. Select Name): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거.
    system("cls");
    switch (selectNum) {
      case 1:
        printAllPlanByDate();
        break;
      case 2:
        printAllPlanByName();
        break;
      case 3:
        selectPlanByDate();
        break;
      case 4:
        selectPlanByName();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void printAllPlanByDate() {
    std::cout << "All Plan" << std::endl;
    std::vector<Plan> plans;
    dbm.executeQuery("SELECT * FROM plan WHERE date IS NOT NULL;", &plans,
                     true);
    for (auto &plan : plans) {
      plan.printPlanDate();
    }
    std::cout << "Do you want to see a specific plan? [y/n]: ";
    char select;
    std::cin >> select;
    std::cin.ignore();
    if (select == 'y') {
      std::cout << "Input Plan Date: ";
      std::string plan;
      std::cin >> plan;
      std::cin.ignore();
      selectPlanByDate(plan);
    }
  }

  void printAllPlanByName() {
    std::cout << "All Plan" << std::endl;
    std::vector<Plan> plans;
    dbm.executeQuery("SELECT * FROM plan WHERE name IS NOT NULL;", &plans,
                     true);
    for (auto &plan : plans) {
      plan.printPlanName();
    }
    std::cout << "Do you want to see a specific plan? [y/n]: ";
    char select;
    std::cin >> select;
    std::cin.ignore();
    if (select == 'y') {
      std::cout << "Input Plan Name: ";
      std::string plan;
      std::cin >> plan;
      std::cin.ignore();
      selectPlanByName(plan);
    }
  }

  void selectPlanByName() {
    Plan plan;
    std::string name;
    std::cout << "Input Plan Name: ";
    std::getline(std::cin, name);
    dbm.executeQuery(
        ("SELECT * FROM plan WHERE name = '" + name + "';").c_str(), &plan);
    int selectNum = plan.printPlan();
    if (selectNum == 1) {
      std::string breakfast = plan.getBreakfast();
      recipe_db_.selectRecipe(breakfast);
    } else if (selectNum == 2) {
      std::string lunch = plan.getLunch();
      recipe_db_.selectRecipe(lunch);
    } else if (selectNum == 3) {
      std::string dinner = plan.getDinner();
      recipe_db_.selectRecipe(dinner);
    } else {
      return;
    }
  }

  void selectPlanByName(const std::string &name) {
    Plan plan;
    dbm.executeQuery(
        ("SELECT * FROM plan WHERE name = '" + name + "';").c_str(), &plan);
    int selectNum = plan.printPlan();
    if (selectNum == 1) {
      std::string breakfast = plan.getBreakfast();
      recipe_db_.selectRecipe(breakfast);
    } else if (selectNum == 2) {
      std::string lunch = plan.getLunch();
      recipe_db_.selectRecipe(lunch);
    } else if (selectNum == 3) {
      std::string dinner = plan.getDinner();
      recipe_db_.selectRecipe(dinner);
    } else {
      return;
    }
  }

  void selectPlanByDate() {
    Plan plan;
    std::string date;
    std::cout << "Input Plan Date: ";
    std::getline(std::cin, date);
    dbm.executeQuery(
        ("SELECT * FROM plan WHERE date = '" + date + "';").c_str(), &plan);
    int selectNum = plan.printPlan();
    if (selectNum == 1) {
      std::string breakfast = plan.getBreakfast();
      recipe_db_.selectRecipe(breakfast);
    } else if (selectNum == 2) {
      std::string lunch = plan.getLunch();
      recipe_db_.selectRecipe(lunch);
    } else if (selectNum == 3) {
      std::string dinner = plan.getDinner();
      recipe_db_.selectRecipe(dinner);
    } else {
      return;
    }
  }

  void selectPlanByDate(const std::string &date) {
    Plan plan;
    dbm.executeQuery(
        ("SELECT * FROM plan WHERE date = '" + date + "';").c_str(), &plan);
    int selectNum = plan.printPlan();
    if (selectNum == 1) {
      std::string breakfast = plan.getBreakfast();
      recipe_db_.selectRecipe(breakfast);
    } else if (selectNum == 2) {
      std::string lunch = plan.getLunch();
      recipe_db_.selectRecipe(lunch);
    } else if (selectNum == 3) {
      std::string dinner = plan.getDinner();
      recipe_db_.selectRecipe(dinner);
    } else {
      return;
    }
  }

  void addPlan() {
    std::cout << "Select a Mode (1. Add Date Plan, 2. Add Name Plan): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거.
    system("cls");
    switch (selectNum) {
      case 1:
        addDatePlan();
        break;
      case 2:
        addNamePlan();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void addNamePlan() {
    std::string planName;
    std::string planBreakfast;
    std::string planLunch;
    std::string planDinner;
    std::cout << "Input Plan Name: ";
    std::getline(std::cin, planName);

    std::cout << "Input breakfast: ";
    std::getline(std::cin, planBreakfast);
    std::cout << "Input lunch: ";
    std::getline(std::cin, planLunch);
    std::cout << "Input dinner: ";
    std::getline(std::cin, planDinner);
    // insert문, plan_id, date는 NULL로 세팅
    dbm.executeQuery(("INSERT INTO Plan VALUES(NULL, '" + planName +
                      "', NULL, '" + planBreakfast + "', '" + planLunch +
                      "', '" + planDinner + "');")
                         .c_str());
  }

  void addDatePlan() {
    std::string planDate;
    std::string planBreakfast;
    std::string planLunch;
    std::string planDinner;

    std::cout << "Input Date(YYYY-MM-DD): ";
    std::getline(std::cin, planDate);
    std::cout << "Input breakfast: ";
    std::getline(std::cin, planBreakfast);
    std::cout << "Input lunch: ";
    std::getline(std::cin, planLunch);
    std::cout << "Input dinner: ";
    std::getline(std::cin, planDinner);
    // insert문, plan_id, name은 NULL로 세팅
    dbm.executeQuery(("INSERT INTO Plan VALUES(NULL, NULL, '" + planDate +
                      "', '" + planBreakfast + "', '" + planLunch + "', '" +
                      planDinner + "');")
                         .c_str());
  }

  void deletePlan() {
    std::cout << "Select a Mode (1. Delete Date Plan, 2. Delete Name Plan): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거.
    system("cls");
    switch (selectNum) {
      case 1:
        deleteDatePlan();
        break;
      case 2:
        deleteNamePlan();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void deleteNamePlan() {
    std::string planName;
    std::cout << "Input Target Plan Name: ";
    std::getline(std::cin, planName);
    dbm.executeQuery(
        ("DELETE FROM plan WHERE name='" + planName + "';").c_str());
  }

  void deleteDatePlan() {
    std::string planDate;
    std::cout << "Input Target Plan Date: ";
    std::getline(std::cin, planDate);
    dbm.executeQuery(
        ("DELETE FROM plan WHERE date='" + planDate + "';").c_str());
  }

  void updatePlan() {
    std::cout << "Select a Mode (1. Update Date Plan, 2. Update Name Plan): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거.
    system("cls");
    switch (selectNum) {
      case 1:
        updateDatePlan();
        break;
      case 2:
        updateNamePlan();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void updateDatePlan() {
    std::string planDate;
    std::string item;
    std::string content;
    std::cout << "Input Target Plan Date: ";
    std::getline(std::cin, planDate);
    std::cout << "Which item do you want to update? (breakfast, "
                 "lunch, dinner): ";
    std::getline(std::cin, item);
    std::cout << "What would you like to change the " + item + " to?: ";
    std::getline(std::cin, content);
    dbm.executeQuery(("UPDATE plan SET " + item + "='" + content +
                      "' WHERE date= '" + planDate + "';")
                         .c_str());
  }

  void updateNamePlan() {
    std::string planName;
    std::string item;
    std::string content;
    std::cout << "Input Target Plan Name: ";
    std::getline(std::cin, planName);
    std::cout << "Which item do you want to update? (name, breakfast, "
                 "lunch, dinner): ";
    std::getline(std::cin, item);
    std::cout << "What would you like to change the " + item + " to?: ";
    std::getline(std::cin, content);
    dbm.executeQuery(("UPDATE plan SET " + item + "='" + content +
                      "' WHERE plan= '" + planName + "';")
                         .c_str());
  }
};
