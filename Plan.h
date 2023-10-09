#pragma once

#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "DatabaseManager.h"
#include "sqlite/sqlite3.h"

class Meal {
 private:
  DatabaseManager dbm;
  std::set<std::string> recipeName;

 public:
  // NoArgsConstructor
  Meal() : dbm("recipe.db") {
    // set 타입으로 RecipeDB에 있는 Name만 가져옴.
    dbm.executeQuery("SELECT name FROM recipe;", &recipeName);
  }

  void printMeal() {
    for (auto &temp : recipeName) {
      std::cout << "-" << temp << std::endl;
    }
    std::cout << std::endl;
  }

  void addMeal(std::string &m) {
    if (searchMeal(m) == "NULL") {
      recipeName.insert(m);
    }
  }

  std::string searchMeal(std::string &target) {
    auto it = recipeName.find(target);
    if (it == recipeName.end()) return "NULL";
    return *it;
  }

  void deleteMeal(std::string &target) { recipeName.erase(target); }
};

class Date {
 private:
  int year, month, day;

 public:
  Date(int y, int m, int d) : year(y), month(m), day(d){};
  Date(std::string &d) {
    year = std::stoi(std::string(d).substr(0, 4));
    month = std::stoi(std::string(d).substr(4, 2));
    day = std::stoi(std::string(d).substr(6, 2));
  };

  int getYear() { return year; }
  int getMonth() { return month; }
  int getDay() { return day; }
};

class Plan {
 private:
  std::string planName;
  Date date;
  Meal Breakfast, Lunch, Dinner;
  DatabaseManager dbm;

 public:
  Plan(std::string &n, Date d, std::vector<Meal> m)
      : planName(n), date(d), Breakfast(m[0]), Lunch(m[1]), Dinner(m[2]){};
  Plan() : dbm("plan.db") {
    // createTable
    dbm.executeQuery(
        "CREATE TABLE IF NOT EXISTS plan (plan_id INTEGER PRIMARY KEY "
        "AUTOINCREMENT, name TEXT, date TEXT, breakfast TEXT, lunch TEXT, "
        "dinner text);");
  }

  void setBreakfast(Meal &b) { Breakfast = b; }
  void setLunch(Meal &l) { Lunch = l; }
  void setDinner(Meal &d) { Dinner = d; }

  void printPlan() {
    std::string temp;
    std::cout << "Choose a date(yyyymmdd): ";
    std::cin >> temp;
    date = Date(temp);
    std::cout << date.getYear() << "." << date.getMonth() << "."
              << date.getDay() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Breakfast" << std::endl;
    Breakfast.printMeal();
    std::cout << "Lunch" << std::endl;
    Lunch.printMeal();
    std::cout << "Dinner" << std::endl;
    Dinner.printMeal();
    std::cout << "----------------------------------------" << std::endl;
  }

  void searchPlan() {
    std::cout << "Select a Mode (1. Print All 2. Select): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();  // 개행 문자 제거.
    system("cls");
    switch (selectNum) {
      case 1:
        // printAllPlan();
        break;
      case 2:
        selectPlan();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void selectPlan() {
    std::string name;
    std::cout << "Input Plan Name: ";
    std::getline(std::cin, name);
    std::cout << "----------------------------------------" << std::endl;
    dbm.executeQuery(
        ("SELECT * FROM plan WHERE name = '" + name + "';").c_str());
    std::cout << "----------------------------------------" << std::endl;
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
