#pragma once

#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "DatabaseManager.h"
#include "Plan.h"
#include "RecipeDB.h"
#include "sqlite/sqlite3.h"

class PlanDB {
 private:
  DatabaseManager dbm;
  RecipeDB recipe_db_;
  std::set<std::string> RecipeName;

 public:
  PlanDB() : dbm("iikh.db") {
    // createTable
    dbm.executeQuery(
        "CREATE TABLE IF NOT EXISTS plan (plan_id INTEGER PRIMARY KEY "
        "AUTOINCREMENT, name TEXT, date TEXT, breakfast TEXT, lunch TEXT, "
        "dinner text);");
  }

  std::set<std::string> getNames() {
    std::set<std::string> temp;
    dbm.executeQuery("SELECT name FROM plan WHERE name IS NOT NULL;", &temp,
                     true);
    return temp;
  }

  std::set<std::string> getDates() {
    std::set<std::string> temp;
    dbm.executeQuery("SELECT date FROM plan WHERE date IS NOT NULL;", &temp,
                     true);
    return temp;
  }

  void searchPlan() {
    std::cout << "Select a Mode (1. Print All Date Plan, 2. Print All Name "
                 "Plan 3. Select Date, 4. Select Name): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거
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
    if (plans.empty()) {
      std::cout << "No Date Plan" << std::endl;
      return;
    }
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
      std::getline(std::cin, plan);
      selectPlanByDate(plan);
    }
  }

  void printAllPlanByName() {
    std::cout << "All Plan" << std::endl;
    std::vector<Plan> plans;
    dbm.executeQuery("SELECT * FROM plan WHERE name IS NOT NULL;", &plans,
                     true);
    if (plans.empty()) {
      std::cout << "No Name Plan" << std::endl;
      return;
    }
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
      std::getline(std::cin, plan);
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
    std::cout << "Select a Mode (1. Add Date Plan, 2. Add Name Plan, 3. Add "
                 "Date Plan Using Name Plan): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거
    system("cls");
    switch (selectNum) {
      case 1:
        addDatePlan();
        break;
      case 2:
        addNamePlan();
        break;
      case 3:
        addDatePlanUsingNamePlan();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void addDatePlanUsingNamePlan() {
    std::string planDate;
    std::string planName;
    std::set<std::string> Name = getNames();
    std::set<std::string> Date = getDates();
    Plan inputPlan;
    std::cout << "-------------NamePlan Lists-------------" << std::endl;
    for (auto &name : Name) {
      std::cout << "Plan Name : " << name << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Input Name: ";
    std::getline(std::cin, planName);
    if (Name.find(planName) == Name.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "Input Date (YYYY-MM-DD): ";
    std::getline(std::cin, planDate);
    if (Date.find(planDate) != Date.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    dbm.executeQuery(
        ("SELECT * FROM plan WHERE name = '" + planName + "';").c_str(),
        &inputPlan);
    // 날짜랑 inputPlan의 아침, 점심, 저녁만 들어가게.
    dbm.executeQuery(("INSERT INTO Plan VALUES(NULL, NULL, '" + planDate +
                      "', '" + inputPlan.getBreakfast() + "', '" +
                      inputPlan.getLunch() + "', '" + inputPlan.getDinner() +
                      "');")
                         .c_str());
  }

  void addNamePlan() {
    std::string planName;
    std::string planBreakfast;
    std::string planLunch;
    std::string planDinner;
    RecipeName = recipe_db_.getRecipeNames();
    std::cout << "Input Plan Name: ";
    std::getline(std::cin, planName);
    // 입력하고, Recipe 목록에 없을 때에는 return.
    std::cout << "Input breakfast: ";
    std::getline(std::cin, planBreakfast);
    if (std::find(RecipeName.begin(), RecipeName.end(), planBreakfast) ==
        RecipeName.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "Input lunch: ";
    std::getline(std::cin, planLunch);
    if (std::find(RecipeName.begin(), RecipeName.end(), planLunch) ==
        RecipeName.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "Input dinner: ";
    std::getline(std::cin, planDinner);
    if (std::find(RecipeName.begin(), RecipeName.end(), planDinner) ==
        RecipeName.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
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
    RecipeName = recipe_db_.getRecipeNames();
    std::cout << "Input Date (YYYY-MM-DD): ";
    std::getline(std::cin, planDate);
    std::cout << "Input breakfast: ";
    std::getline(std::cin, planBreakfast);
    if (std::find(RecipeName.begin(), RecipeName.end(), planBreakfast) ==
        RecipeName.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "Input lunch: ";
    std::getline(std::cin, planLunch);
    if (std::find(RecipeName.begin(), RecipeName.end(), planLunch) ==
        RecipeName.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "Input dinner: ";
    std::getline(std::cin, planDinner);
    if (std::find(RecipeName.begin(), RecipeName.end(), planDinner) ==
        RecipeName.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
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
    std::cin.ignore();  // 개행 문자 제거
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
    std::set<std::string> Name = getNames();
    std::cout << "Input Target Plan Name: ";
    std::getline(std::cin, planName);
    if (Name.find(planName) == Name.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    dbm.executeQuery(
        ("DELETE FROM plan WHERE name='" + planName + "';").c_str());
  }

  void deleteDatePlan() {
    std::string planDate;
    std::set<std::string> Date = getDates();
    std::cout << "Input Target Plan Date (YYYY-MM-DD): ";
    std::getline(std::cin, planDate);
    if (Date.find(planDate) == Date.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    dbm.executeQuery(
        ("DELETE FROM plan WHERE date='" + planDate + "';").c_str());
  }

  void updatePlan() {
    std::cout << "Select a Mode (1. Update Date Plan, 2. Update Name Plan): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거
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
    std::set<std::string> Date = getDates();
    std::cout << "Input Target Plan Date (YYYY-MM-DD): ";
    std::getline(std::cin, planDate);
    if (Date.find(planDate) == Date.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "Which item do you want to update? (date, breakfast, "
                 "lunch, dinner): ";
    std::getline(std::cin, item);
    if (item != "date" && item != "breakfast" && item != "lunch" &&
        item != "dinner") {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "What would you like to change the " + item + " to?: ";
    std::getline(std::cin, content);
    if (item == "date") {
      if (Date.find(content) != Date.end()) {
        std::cout << "Wrong Input" << std::endl;
        return;
      }
    }
    dbm.executeQuery(("UPDATE plan SET " + item + " = '" + content +
                      "' WHERE date = '" + planDate + "';")
                         .c_str());
  }

  void updateNamePlan() {
    std::string planName;
    std::string item;
    std::string content;
    std::set<std::string> Name = getNames();
    std::cout << "Input Target Plan Name: ";
    std::getline(std::cin, planName);
    if (Name.find(planName) == Name.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "Which item do you want to update? (name, breakfast, "
                 "lunch, dinner): ";
    std::getline(std::cin, item);
    if (item != "name" && item != "breakfast" && item != "lunch" &&
        item != "dinner") {
      std::cout << "Wrong Input" << std::endl;
      return;
    }
    std::cout << "What would you like to change the " + item + " to?: ";
    std::getline(std::cin, content);
    if (item == "name") {
      if (Name.find(content) != Name.end()) {
        std::cout << "Wrong Input" << std::endl;
        return;
      }
    }
    dbm.executeQuery(("UPDATE plan SET " + item + " = '" + content +
                      "' WHERE name = '" + planName + "';")
                         .c_str());
  }
};
