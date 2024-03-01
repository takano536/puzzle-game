#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../Define/Define.hpp"

/**
 * @brief パズルソルバーの抽象クラス
 */
class PuzzleSolver {
  public:
    PuzzleSolver() = default;
    virtual ~PuzzleSolver() = default;
    virtual void init(const std::map<Define::CELL_TYPE, char> &marks) = 0;
    virtual void solve(std::unique_ptr<std::vector<std::string>> input) = 0;
    virtual void reset() = 0;
    virtual std::unique_ptr<std::vector<std::string>> get_puzzle() const = 0;
    virtual std::vector<Define::DIRECTION> get_ans() const = 0;
    virtual int get_rate() const = 0;
};