#pragma once

#include <iostream>
#include <utility>
#include <set>
#include <vector>

#include "sqlite/sqlite3.h"
#include "DatabaseManager.h"

class Meal {
 private :
  DatabaseManager dbm;
  std::set<std::string> recipeName;

 public :
  //NoArgsConstructor
  Meal() : dbm("recipe.db") {
    //set타입으로 RecipeDB에 있는 Name만 가져옴.
    dbm.executeQuery("Select name from recipe;", &recipeName);
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
    if (it == recipeName.end())
      return "NULL";
    return *it;
  }

  void deleteMeal(std::string &target) {
    recipeName.erase(target);
  }
};

class Date {
 private:
  int year, month, day;

 public:
  Date(int y, int m, int d) :
      year(y), month(m), day(d) {};
  Date(std::string &d) {
    year = std::stoi(std::string(d).substr(0, 4));
    month = std::stoi(std::string(d).substr(4, 2));
    day = std::stoi(std::string(d).substr(6, 2));
  };
  //getter
  int getYear() {
    return year;
  }
  int getMonth() {
    return month;
  }
  int getDay() {
    return day;
  }

};

class Plan {
 private:
  std::string planName;
  Date date;
  Meal Breakfast, Lunch, Dinner;

 public:
  Plan(std::string &n, Date d, std::vector<Meal> m) :
      planName(n), date(d), Breakfast(m[0]), Lunch(m[1]), Dinner(m[2]) {};

  void setBreakfast(Meal &b) {
    Breakfast = b;
  }
  void setLunch(Meal &l) {
    Lunch = l;
  }
  void setDinner(Meal &d) {
    Dinner = d;
  }
  void printPlan() {
    std::string temp;
    std::cout << "choose a date(yyyymmdd) : ";
    std::cin >> temp;
    date = Date(temp);
    std::cout << date.getYear() << "." << date.getMonth() << "." << date.getDay() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Breakfast" << std::endl;
    Breakfast.printMeal();
    std::cout << "Lunch" << std::endl;
    Lunch.printMeal();
    std::cout << "Dinner" << std::endl;
    Dinner.printMeal();
    std::cout << "----------------------------------------" << std::endl;
  }

};