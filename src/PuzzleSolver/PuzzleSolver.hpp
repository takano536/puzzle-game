#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../Define/Define.hpp"

enum class Object {
    Floor,
    Wall,
    Start,
    Hole,
};

class PuzzleSolver final {
  public:
    PuzzleSolver(const std::map<Object, char> &marks);
    void solve(std::unique_ptr<std::vector<std::string>> input);
    void reset();
    std::unique_ptr<std::vector<std::string>> get_puzzle() const;
    std::vector<Define::DIRECTION> get_ans() const;
    int get_rate() const;

  private:
    std::unique_ptr<std::vector<std::string>> puzzle;
    std::map<Object, char> marks;
    std::vector<Define::DIRECTION> ans;
    int step;
};