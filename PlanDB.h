#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "DatabaseManager.h"
#include "Date.h"
#include "Plan.h"
#include "RecipeDB.h"
#include "Similarity.h"

class PlanDB {
 private:
  DatabaseManager dbm;
  RecipeDB recipe_db_;
  std::set<std::string> RecipeName;
  std::vector<std::pair<std::string, std::set<std::string>>> ingredients;
  Date _date;

 public:
  PlanDB() : dbm("iikh.db") {
    // createTable
    dbm.executeQuery(
        "CREATE TABLE IF NOT EXISTS plan (plan_id INTEGER PRIMARY KEY "
        "AUTOINCREMENT, name TEXT, date DATE, breakfast TEXT, lunch TEXT, "
        "dinner text);");

    // insert into map
    makeDatePlanGroceryList();
  }

  std::set<std::string> getNames() {
    std::set<std::string> temp;

    dbm.executeQuery("SELECT name FROM plan WHERE name IS NOT NULL;", &temp,
                     true);

    return temp;
  }

  std::set<std::string> getDates() {
    std::set<std::string> temp;

    dbm.executeQuery(
        "SELECT date FROM plan WHERE date IS NOT NULL ORDER BY date ASC;",
        &temp, true);

    return temp;
  }

  void searchPlan() {
    std::cout << "Select a Mode (1. Print All Date Plan, 2. Print All Name "
                 "Plan, 3. Select Date, 4. Select Name, 5. Select Period): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();
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
      case 5:
        selectPeriodList();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void printAllPlanByDate() {
    std::vector<Plan> plans;

    std::cout << "All Plan" << std::endl;
    dbm.executeQuery(
        "SELECT * FROM plan WHERE date IS NOT NULL ORDER BY date ASC;", &plans,
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
    std::vector<Plan> plans;

    std::cout << "All Plan" << std::endl;
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
      Similarity similarity(name);
      similarity.checkSimilarity(1);
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
    std::cin.ignore();
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

    std::cout << "-------------Name Plan List-------------" << std::endl;
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
    std::string today = Date::getToday();
    if (_date.compareDate(today, planDate)) {
      std::cout << "Enter Date After " + today << std::endl;
      return;
    }
    if (Date.find(planDate) != Date.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }

    dbm.executeQuery(
        ("SELECT * FROM plan WHERE name = '" + planName + "';").c_str(),
        &inputPlan);
    // planDate & breakfast, lunch, dinner of inputPlan
    dbm.executeQuery(("INSERT INTO plan VALUES(NULL, NULL, '" + planDate +
                      "', '" + inputPlan.getBreakfast() + "', '" +
                      inputPlan.getLunch() + "', '" + inputPlan.getDinner() +
                      "');")
                         .c_str());
    makeDatePlanGroceryList(planDate);
  }

  void addNamePlan() {
    std::string planName;
    std::string planBreakfast;
    std::string planLunch;
    std::string planDinner;
    RecipeName = recipe_db_.getRecipeNames();

    std::cout << "Input Plan Name: ";
    std::getline(std::cin, planName);

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
    // plan_id & date = NULL
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
    std::set<std::string> Date = getDates();
    RecipeName = recipe_db_.getRecipeNames();

    std::cout << "Input Date (YYYY-MM-DD): ";
    std::getline(std::cin, planDate);
    std::string today = Date::getToday();
    if (_date.compareDate(today, planDate)) {
      std::cout << "Enter Date After " + today << std::endl;
      return;
    }
    if (Date.find(planDate) != Date.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }

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

    // plan_id & name = NULL
    dbm.executeQuery(("INSERT INTO Plan VALUES(NULL, NULL, '" + planDate +
                      "', '" + planBreakfast + "', '" + planLunch + "', '" +
                      planDinner + "');")
                         .c_str());
    makeDatePlanGroceryList(planDate);
  }

  void deletePlan() {
    std::cout << "Select a Mode (1. Delete Date Plan, 2. Delete Name Plan): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();
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
      Similarity similarity(planName);
      similarity.checkSimilarity(1);
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
    deleteDatePlanGroceryList(planDate);
  }

  void updatePlan() {
    std::cout << "Select a Mode (1. Update Date Plan, 2. Update Name Plan): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();
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
    deleteDatePlanGroceryList(planDate);
    if (item == "date") {
      makeDatePlanGroceryList(content);
    } else {
      makeDatePlanGroceryList(planDate);
    }
  }

  void updateNamePlan() {
    std::string planName;
    std::string item;
    std::string content;
    std::set<std::string> Name = getNames();

    std::cout << "Input Target Plan Name: ";
    std::getline(std::cin, planName);
    if (Name.find(planName) == Name.end()) {
      Similarity similarity(planName);
      std::cout << "Wrong Input" << std::endl;
      similarity.checkSimilarity(1);
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

  void selectPeriodList() {
    std::string start_date;
    std::string end_date;

    std::cout << "Input Start Date (YYYY-MM-DD): ";
    std::getline(std::cin, start_date);
    std::cout << "Input End Date (YYYY-MM-DD): ";
    std::getline(std::cin, end_date);
    if (_date.compareDate(start_date, end_date)) {
      std::cout << "The order of the start and end dates is not correct. The "
                   "order has been changed automatically."
                << std::endl;
      swap(start_date, end_date);
    }

    std::vector<Plan> plans;
    dbm.executeQuery(("SELECT * FROM plan WHERE date BETWEEN '" + start_date +
                      "' AND '" + end_date + "' ORDER BY date ASC;")
                         .c_str(),
                     &plans, true);
    if (plans.empty()) {
      std::cout << "No Plan Between " + start_date + " and " + end_date
                << std::endl;
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

  void showGroceryList() {
    std::cout << "Select a Mode (1. Show Period Grocery List, 2. Show Specific "
                 "Date Grocery List): ";
    int selectNum;
    std::cin >> selectNum;
    std::cin.ignore();
    system("cls");

    switch (selectNum) {
      case 1:
        showPeriodGroceryList();
        break;
      case 2:
        showSpecificDateGroceryList();
        break;
      default:
        std::cout << "Wrong Input" << std::endl;
        break;
    }
  }

  void showPeriodGroceryList() {
    std::string start_date;
    std::string end_date;
    std::set<std::string> temp;
    std::set<std::string> tempDate;

    std::cout << "Input Start Date (YYYY-MM-DD): ";
    std::getline(std::cin, start_date);
    std::cout << "Input End Date (YYYY-MM-DD): ";
    std::getline(std::cin, end_date);
    if (_date.compareDate(start_date, end_date)) {
      std::cout << "The order of the start and end dates is not correct. The "
                   "order has been changed automatically."
                << std::endl;
      swap(start_date, end_date);
    }

    dbm.executeQuery(
        ("SELECT date FROM plan WHERE date BETWEEN '" + start_date + "' AND '" +
         end_date + "' ORDER BY date ASC;")
            .c_str(),
        &tempDate, true);
    if (tempDate.empty()) {
      std::cout << "No Plan Between " + start_date + " and " + end_date
                << std::endl;
      return;
    }

    for (auto &i : tempDate) {
      std::set<std::string> tempIngredients;
      for (auto const &j : ingredients) {
        if (j.first == i) {
          tempIngredients = j.second;
        }
      }
      for (auto &j : tempIngredients) {
        temp.insert(j);
      }
    }

    std::cout << "--------------Grocery List--------------" << std::endl;
    for (const auto &i : temp) {
      std::cout << i << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
  }

  void showSpecificDateGroceryList() {
    std::string planDate;
    std::set<std::string> Date = getDates();

    std::cout << "Input Target Plan Date (YYYY-MM-DD): ";
    std::getline(std::cin, planDate);
    if (Date.find(planDate) == Date.end()) {
      std::cout << "Wrong Input" << std::endl;
      return;
    }

    std::set<std::string> temp;
    for (auto const &i : ingredients) {
      if (i.first == planDate) {
        temp = i.second;
      }
    }

    std::cout << "--------------Grocery List--------------" << std::endl;
    for (const auto &i : temp) {
      std::cout << i << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
  }

  void makeDatePlanGroceryList() {
    std::vector<Plan> plans;

    dbm.executeQuery("SELECT * FROM plan WHERE date IS NOT NULL;", &plans,
                     true);
    for (auto &plan : plans) {
      std::string planDate = plan.getDate();
      std::string breakfast = plan.getBreakfast();
      std::string lunch = plan.getLunch();
      std::string dinner = plan.getDinner();
      std::vector<Recipe> recipes;
      recipes.push_back(recipe_db_.selectRecipe(breakfast, true));
      recipes.push_back(recipe_db_.selectRecipe(lunch, true));
      recipes.push_back(recipe_db_.selectRecipe(dinner, true));

      std::set<std::string> tempIngredients;
      for (auto &recipe : recipes) {
        std::set<std::string> temp = recipe.getIngredients();
        for (auto &ingredient : temp) {
          tempIngredients.insert(ingredient);
        }
      }
      ingredients.push_back({planDate, tempIngredients});
    }
  }

  void makeDatePlanGroceryList(std::string const &planDate) {
    Plan plan;

    dbm.executeQuery(
        ("SELECT * FROM plan WHERE date = '" + planDate + "';").c_str(), &plan);
    std::string breakfast = plan.getBreakfast();
    std::string lunch = plan.getLunch();
    std::string dinner = plan.getDinner();
    std::vector<Recipe> recipes;

    recipes.push_back(recipe_db_.selectRecipe(breakfast, true));
    recipes.push_back(recipe_db_.selectRecipe(lunch, true));
    recipes.push_back(recipe_db_.selectRecipe(dinner, true));
    std::set<std::string> tempIngredients;
    for (auto &recipe : recipes) {
      std::set<std::string> temp = recipe.getIngredients();
      for (auto &ingredient : temp) {
        tempIngredients.insert(ingredient);
      }
    }
    ingredients.push_back({planDate, tempIngredients});
  }

  void deleteDatePlanGroceryList(std::string const &planDate) {
    for (int i = 0; i < ingredients.size(); i++) {
      if (ingredients[i].first == planDate) {
        ingredients.erase(ingredients.begin() + i);
      }
    }
  }
};
