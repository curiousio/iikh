#pragma once

#include <iostream>
#include <set>
#include <utility>
#include <vector>

class Plan {
 private:
  std::string planName;
  std::string date, Breakfast, Lunch, Dinner;

 public:
  // constructor
  Plan() = default;

  // setter
  void setName(const std::string &n) { planName = n; }
  void setDate(const std::string &d) { date = d; }
  void setBreakfast(const std::string &b) { Breakfast = b; }
  void setLunch(const std::string &l) { Lunch = l; }
  void setDinner(const std::string &d) { Dinner = d; }

  // getter
  std::string getName() { return planName; }
  std::string getDate() { return date; }
  std::string getBreakfast() { return Breakfast; }
  std::string getLunch() { return Lunch; }
  std::string getDinner() { return Dinner; }

  int printPlan() {
    // 비어 있는 경우가 없는 거.
    if (planName.empty()) {
      std::cout << "No Plan" << std::endl;
      return 0;
    }
    std::cout << "----------------------------------------" << std::endl;
    if (planName != "NULL") {
      std::cout << "Plan Name: " << planName << std::endl;
    }
    if (date != "NULL") {
      std::cout << "Date: " << date << std::endl;
    }
    std::cout << "Breakfast: " << Breakfast << std::endl;
    std::cout << "Lunch: " << Lunch << std::endl;
    std::cout << "Dinner: " << Dinner << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Do you want to see a specific Recipe of Meal? [y/n]: ";
    char select;
    std::cin >> select;
    std::cin.ignore();
    if (select == 'y') {
      int selectNum;
      std::cout << "Select a Meal (1. Breakfast, 2. Lunch, 3. Dinner): ";
      std::cin >> selectNum;
      std::cin.ignore();
      if (selectNum >= 4) {
        std::cout << "Wrong Input" << std::endl;
        return 0;
      }
      return selectNum;
    }
    return 0;
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
