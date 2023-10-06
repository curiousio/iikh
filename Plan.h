#pragma once

#include <iostream>
#include <utility>
#include <set>
#include <vector>

#include "sqlite/sqlite3.h"
#include "DatabaseManager.h"

class Meal {
private :
    std::set<std::string> recipeName;

public :
    Meal(std::set<std::string> r) {
        for (std::string& temp : r) 
            recipeName.insert(temp);
    }

    void printMeal() {
        for (std::string& temp : recipeName) {
            std::cout << "-" << temp << std::endl;
        }
        std::cout << std::endl;
    }

    void addMeal(std::string &m) {
        if (searchMeal(m) == 0) {
            recipeName.insert(m);
        }
    }

    Meal searchMeal(std::string &target) {
        std::set<string>::iterator it = recipeName.find(target);
        if (it == recipeName.end())
            return 0;
        return recipeName.find(target);
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
    Date(const char* d) { sscanf_s(d, "%04d%02d%02d", &year, &month, &day); };
};

class Plan {
private:
    std::string planName;
    Date date;
    Meal Breakfast, Lunch, Dinner;

public:
    Plan(std::string& n, Date d, std::vector<Meal> m) :
        name(n), date(d), Breakfast(m[0]), Lunch(m[1]), Dinner(m[2]) {};

    void setBreakfast(Meal& b) {
        Breakfast = b;
    }
    void setLunch(Meal& l) {
        Lunch = l;
    }
    void setDinner(Meal& d) {
        Dinner = d;
    }
    void printPlan() {
        string temp;
        std::cout << "choose a date(yyyymmdd) : ";
        std::cin >> temp;
        date = Date(temp);
        std::cout << date.year << "." << date.month << "." << date.day << std::endl;
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