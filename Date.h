#pragma once

#include <iostream>
#include <string>
#include <utility>

class Date {
 private:
 public:
  Date() = default;

  bool compareDate(std::string const &date1, std::string const &date2) {
    int date1Year = std::stoi(date1.substr(0, 4));
    int date1Month = std::stoi(date1.substr(5, 2));
    int date1Day = std::stoi(date1.substr(8, 2));
    int date2Year = std::stoi(date2.substr(0, 4));
    int date2Month = std::stoi(date2.substr(5, 2));
    int date2Day = std::stoi(date2.substr(8, 2));

    if (date1Year > date2Year) {
      return true;
    } else if (date1Year == date2Year) {
      if (date1Month > date2Month) {
        return true;
      } else if (date1Month == date2Month) {
        if (date1Day > date2Day) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  static std::string getToday() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    std::string year = std::to_string(1900 + ltm->tm_year);
    std::string month = std::to_string(1 + ltm->tm_mon);
    std::string day = std::to_string(ltm->tm_mday);

    if (month.length() == 1) {
      month = "0" + month;
    }

    if (day.length() == 1) {
      day = "0" + day;
    }

    return year + "-" + month + "-" + day;
  }
};
