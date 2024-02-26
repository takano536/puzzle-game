#pragma once

#include <string>
#include <vector>

class Solver {
  public:
    void initialize(const std::vector<std::string> &map);
    void solve();

  private:
    std::vector<std::string> map;
};