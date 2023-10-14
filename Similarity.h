#pragma once

#include "DatabaseManager.h"

class Similarity {
 private:
  DatabaseManager dbm;
  std::string target;

 public:
  Similarity(std::string target) : dbm("iikh.db") { this->target = target; }

  void checkSimilarity(int flag) {
    std::set<std::string> candidate;
    std::set<std::string> ret;

    if (flag == 1) {
      dbm.executeQuery("SELECT name FROM plan;", &candidate, true);
    } else if (flag == 2) {
      dbm.executeQuery("SELECT name FROM recipe;", &candidate, true);
    }

    for (auto& i : candidate) {
      if (strstr(i.c_str(), target.c_str())) {
        ret.insert(i);
      }
    }

    if (ret.size() == 0) {
      return;
    }

    std::cout << "Containing user input \"" << target << "\" ..." << std::endl;
    for (auto& i : ret) {
      std::cout << i + " " << std::endl;
    }
  }
};
