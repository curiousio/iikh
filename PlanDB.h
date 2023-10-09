#pragma once

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
 public:
  PlanDB() : dbm("iikh.db") {
    // createTable
    dbm.executeQuery(
        "CREATE TABLE IF NOT EXISTS plan (plan_id INTEGER PRIMARY KEY "
        "AUTOINCREMENT, name TEXT, date TEXT, breakfast TEXT, lunch TEXT, "
        "dinner text);");
  }
  void searchPlan() {
    std::cout << "Select a Mode (1. Print All Date Plan, 2. Print ALl Name Plan 3. Select): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거.
    system("cls");
    switch (selectNum) {
      case 1: printAllPlanByDate();
        break;
      case 2: printAllPlanByName();
      case 3:selectPlan();
        break;
      default:std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void printAllPlanByDate() {
    std::cout << "All Plan" << std::endl;
    std::vector<Plan> plans;
    dbm.executeQuery("SELECT * FROM plan WHERE date IS NOT NULL;", &plans, true);
    for (auto &plan : plans) {
      plan.printPlanDate();
    }
  }

  void printAllPlanByName() {
    std::cout << "All Plan" << std::endl;
    std::vector<Plan> plans;
    dbm.executeQuery("SELECT * FROM plan WHERE name IS NOT NULL;", &plans, true);
    for (auto &plan : plans) {
      plan.printPlanName();
    }
  }

  void selectPlan() {
    Plan plan;
    std::string name;
    std::cout << "Input Plan Name: ";
    std::getline(std::cin, name);
    dbm.executeQuery(
        ("SELECT * FROM plan WHERE name = '" + name + "';").c_str(), &plan);
    plan.printPlan();
  }

  void addPlan() {
    std::string planName;
    std::string planDate;
    std::string planBreakfast;
    std::string planLunch;
    std::string planDinner;
    std::cout << "Input Plan Name: ";
    std::getline(std::cin, planName);
    std::cout << "Input Date(YYYYMMDD): ";
    std::getline(std::cin, planDate);
    std::cout << "Input breakfast: ";
    std::getline(std::cin, planBreakfast);
    std::cout << "Input lunch: ";
    std::getline(std::cin, planLunch);
    std::cout << "Input dinner: ";
    std::getline(std::cin, planDinner);
    // insert문, plan_id는 NULL로 세팅
    dbm.executeQuery(("INSERT INTO Plan VALUES(NULL, '" + planName + "', '" +
        planDate + "', '" + planBreakfast + "', '" + planLunch +
        "', '" + planDinner + "');")
                         .c_str());
  }

  void deletePlan() {
    std::string planName;
    std::cout << "Input Target Plan Name: ";
    std::getline(std::cin, planName);
    dbm.executeQuery(
        ("DELETE FROM plan WHERE planName='" + planName + "';").c_str());
  }

  void updatePlan() {
    std::string planName;
    std::string item;
    std::string content;
    std::cout << "Input Target Plan Name: ";
    std::getline(std::cin, planName);
    std::cout << "What item do you want to update? (name, date, breakfast, "
                 "lunch, dinner): ";
    std::getline(std::cin, item);
    std::cout << "What do you want to update it to?: ";
    std::getline(std::cin, content);
    dbm.executeQuery(("UPDATE plan SET " + item + "='" + content +
        "' WHERE plan= '" + planName + "';")
                         .c_str());
  }
};