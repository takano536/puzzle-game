#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../Define/Define.hpp"

/**
 * @brief パズルソルバー
 * @param marks std::map<Define::CELL_TYPE, char> - PuzzleSolver::CELL_TYPE と char の対応表
 */
class PuzzleSolver final {
  public:
    PuzzleSolver(const std::map<Define::CELL_TYPE, char> &marks);
    void solve(std::unique_ptr<std::vector<std::string>> input);
    void reset();
    std::unique_ptr<std::vector<std::string>> get_puzzle() const;
    std::vector<Define::DIRECTION> get_ans() const;
    int get_rate() const;

  private:
    static const int INF;
    static const int NaN;
    static const std::map<Define::DIRECTION, SDL_Point> DIR_VECS;
    static const std::map<Define::DIRECTION, char> DIR_MAPS;

    std::unique_ptr<std::vector<std::string>> puzzle;
    std::map<Define::CELL_TYPE, char> marks;
    std::vector<Define::DIRECTION> ans;
    int step;
};