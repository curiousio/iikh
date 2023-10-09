#pragma once

#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "DatabaseManager.h"
#include "sqlite/sqlite3.h"

/*
class Meal {
 private:
  DatabaseManager dbm;
  std::set<std::string> recipeName;

 public:
  // NoArgsConstructor
  Meal() : dbm("iikh.db") {
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
*/

/*
class Date {
 private:
  int year, month, day;

 public:
  Date(int y, int m, int d) : year(y), month(m), day(d) {};
  Date(std::string &d) {
    year = std::stoi(std::string(d).substr(0, 4));
    month = std::stoi(std::string(d).substr(4, 2));
    day = std::stoi(std::string(d).substr(6, 2));
  };

  int getYear() { return year; }
  int getMonth() { return month; }
  int getDay() { return day; }
};
*/

class Plan {
 private:
  std::string planName;
  //Date date;
  std::string date, Breakfast, Lunch, Dinner;

 public:
  //constructor
  Plan() = default;
  //setter
  void setName(const std::string &n) { planName = n; }
  void setDate(const std::string &d) { date = d; }
  void setBreakfast(const std::string &b) { Breakfast = b; }
  void setLunch(const std::string &l) { Lunch = l; }
  void setDinner(const std::string &d) { Dinner = d; }

  void printPlan() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Plan Name: " << planName << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Breakfast: " << Breakfast << std::endl;
    std::cout << "Lunch: " << Lunch << std::endl;
    std::cout << "Dinner: " << Dinner << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }

  void printPlanName() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Plan Name: " << planName << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }

  void printPlanDate() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }

};
