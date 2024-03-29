#include "IceFloorPuzzleSolver.hpp"

#include <algorithm>
#include <array>
#include <complex>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>

const int IceFloorPuzzleSolver::INF = std::numeric_limits<int>::max();
const int IceFloorPuzzleSolver::NaN = -1;

const std::map<Define::DIRECTION, std::pair<int, int>> IceFloorPuzzleSolver::DIR_VECS = {
    {Define::DIRECTION::UP, {-1, 0}},
    {Define::DIRECTION::RIGHT, {0, 1}},
    {Define::DIRECTION::DOWN, {1, 0}},
    {Define::DIRECTION::LEFT, {0, -1}},
};
const std::map<Define::DIRECTION, char> IceFloorPuzzleSolver::DIR_CHARS = {
    {Define::DIRECTION::UP, 'U'},
    {Define::DIRECTION::RIGHT, 'R'},
    {Define::DIRECTION::DOWN, 'D'},
    {Define::DIRECTION::LEFT, 'L'},
};

/**
 * @brief 初期化関数
 * @param marks パズルで使用するオブジェクトと文字の対応マップ
 */
void IceFloorPuzzleSolver::init(const std::map<Define::CELL_TYPE, char> &marks) {
    puzzle = std::make_unique<std::vector<std::string>>();
    this->marks = marks;
    step = NaN;
}

/**
 * @brief パズルを解く
 * @param input パズル
 * @note パズルを解いて解答を保存する
 */
void IceFloorPuzzleSolver::solve(std::unique_ptr<std::vector<std::string>> input) {
    this->puzzle = std::move(input);

    std::pair<int, int> size = {static_cast<int>(this->puzzle->size()), static_cast<int>((*this->puzzle)[0].size())};
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Start of BFS");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "size: %d, %d", size.first, size.second);

    std::pair<int, int> start;
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            if ((*this->puzzle)[i][j] == marks.at(Define::CELL_TYPE::START)) {
                start = {i, j};
            }
        }
    }

    std::vector<std::vector<int>> steps(size.first, std::vector<int>(size.second, NaN));
    std::vector<std::vector<int>> dists(size.first, std::vector<int>(size.second, INF));
    std::queue<std::pair<std::pair<int, int>, std::string>> que;
    std::map<std::pair<int, int>, std::string> pathes;
    steps[start.first][start.second] = 0;
    dists[start.first][start.second] = 0;
    pathes[start] = "";
    que.push({start, pathes[start]});

    auto move = [this, &size, &dists](const std::pair<int, int> &coord, const std::pair<int, int> &dir, const int step) -> std::pair<int, int> {
        auto next_coord = std::pair<int, int>(coord.first + dir.first, coord.second + dir.second);
        if (next_coord.first < 0 || next_coord.first >= size.first || next_coord.second < 0 || next_coord.second >= size.second) {
            return coord;
        }
        if ((*this->puzzle)[next_coord.first][next_coord.second] == marks.at(Define::CELL_TYPE::WALL)) {
            return coord;
        }
        auto curr_dist = step;
        dists[next_coord.first][next_coord.second] = std::min(dists[next_coord.first][next_coord.second], curr_dist++);
        while (true) {
            int next_h = next_coord.first + dir.first;
            int next_w = next_coord.second + dir.second;
            if (next_h < 0 || next_h >= size.first || next_w < 0 || next_w >= size.second) {
                return next_coord;
            }
            if ((*this->puzzle)[next_h][next_w] == marks.at(Define::CELL_TYPE::WALL)) {
                return next_coord;
            }
            next_coord.first = next_h;
            next_coord.second = next_w;
            dists[next_coord.first][next_coord.second] = std::min(dists[next_coord.first][next_coord.second], curr_dist++);
        }
        return next_coord;
    };

    while (!que.empty()) {
        const auto [curr, path] = que.front();
        que.pop();

        for (const auto &[dir, dir_vec] : DIR_VECS) {
            const auto next = move(curr, dir_vec, steps[curr.first][curr.second]);
            if (steps[next.first][next.second] != NaN) {
                continue;
            }
            steps[next.first][next.second] = steps[curr.first][curr.second] + 1;
            pathes[next] = path + DIR_CHARS.at(dir);
            que.push({next, pathes[next]});
        }
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "End of BFS");

    int max_dists = 0;
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            if (dists[i][j] == INF) {
                continue;
            }
            if (dists[i][j] > max_dists) {
                max_dists = dists[i][j];
                goal_coord = {j, i};
            }
        }
    }
    for (const auto &c : pathes[std::make_pair(goal_coord.y, goal_coord.x)]) {
        this->ans.push_back(std::ranges::find_if(DIR_CHARS, [c](const auto &dir) { return dir.second == c; })->first);
    }
    step = static_cast<int>(ans.size());
}

/**
 * @brief パズルをリセットする
 */
void IceFloorPuzzleSolver::reset() {
    if (this->puzzle->empty()) {
        return;
    }
    this->ans.clear();
    this->puzzle->clear();
    this->step = NaN;
}

/**
 * @brief パズルを取得する
 * @return パズル
 */
std::unique_ptr<std::vector<std::string>> IceFloorPuzzleSolver::get_puzzle() const {
    return std::make_unique<std::vector<std::string>>(*this->puzzle);
}

/**
 * @brief 解答を取得する
 * @return 解答
 */
std::vector<Define::DIRECTION> IceFloorPuzzleSolver::get_ans() const {
    return ans;
}

/**
 * @brief 評価値を取得する
 * @return 評価値
 */
int IceFloorPuzzleSolver::get_rate() const {
    return step;
}

/**
 * @brief ゴールの座標を取得する
 * @return ゴールの座標
 */
SDL_Point IceFloorPuzzleSolver::get_goal() const {
    return goal_coord;
}