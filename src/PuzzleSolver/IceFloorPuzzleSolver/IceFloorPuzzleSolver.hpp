#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../Define/Define.hpp"
#include "../PuzzleSolver.hpp"

/**
 * @brief パズルソルバー
 * @param marks std::map<Define::CELL_TYPE, char> - Define::CELL_TYPE と char の対応表
 */
class IceFloorPuzzleSolver : public PuzzleSolver {
  public:
    void init(const std::map<Define::CELL_TYPE, char> &marks) override;
    void solve(std::unique_ptr<std::vector<std::string>> input) override;
    void reset() override;
    std::unique_ptr<std::vector<std::string>> get_puzzle() const override;
    std::vector<Define::DIRECTION> get_ans() const override;
    int get_rate() const override;
    SDL_Point get_goal() const override;

  private:
    static const int INF;
    static const int NaN;
    static const std::map<Define::DIRECTION, std::pair<int, int>> DIR_VECS;
    static const std::map<Define::DIRECTION, char> DIR_CHARS;

    std::unique_ptr<std::vector<std::string>> puzzle;
    std::map<Define::CELL_TYPE, char> marks;
    std::vector<Define::DIRECTION> ans;
    int step;
    SDL_Point goal_coord;
};