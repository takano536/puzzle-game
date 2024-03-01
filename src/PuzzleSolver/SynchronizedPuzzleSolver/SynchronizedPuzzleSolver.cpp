#include "SynchronizedPuzzleSolver.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <array>
#include <complex>
#include <limits>
#include <queue>

const int SynchronizedPuzzleSolver::INF = std::numeric_limits<int>::max();
const int SynchronizedPuzzleSolver::NaN = -1;

const std::map<Define::DIRECTION, SDL_Point> SynchronizedPuzzleSolver::DIR_VECS = {
    {Define::DIRECTION::UP, {-1, 0}},
    {Define::DIRECTION::RIGHT, {0, 1}},
    {Define::DIRECTION::DOWN, {1, 0}},
    {Define::DIRECTION::LEFT, {0, -1}},
};
const std::map<Define::DIRECTION, char> SynchronizedPuzzleSolver::DIR_CHARS = {
    {Define::DIRECTION::UP, 'U'},
    {Define::DIRECTION::RIGHT, 'R'},
    {Define::DIRECTION::DOWN, 'D'},
    {Define::DIRECTION::LEFT, 'L'},
};

/**
 * @brief 初期化関数
 * @param marks パズルで使用するオブジェクトと文字の対応マップ
 */
void SynchronizedPuzzleSolver::init(const std::map<Define::CELL_TYPE, char> &marks) {
    puzzle = std::make_unique<std::vector<std::string>>();
    this->marks = marks;
    step = NaN;
}

/**
 * @brief パズルを解く
 * @param input パズル
 * @note パズルを解いて解答を保存する
 */
void SynchronizedPuzzleSolver::solve(std::unique_ptr<std::vector<std::string>> input) {
    this->puzzle = std::move(input);

    SDL_Point size = {static_cast<int>((*this->puzzle)[0].size()), static_cast<int>(this->puzzle->size())};

    int player_num = 0;
    for (const auto &row : *this->puzzle) {
        player_num += std::ranges::count(row, marks.at(Define::CELL_TYPE::START));
    }

    std::vector<SDL_Point> start_coords(player_num);
    auto iter = start_coords.begin();
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            if ((*this->puzzle)[i][j] == marks.at(Define::CELL_TYPE::START)) {
                *iter = {i, j};
                iter++;
            }
        }
    }

    auto coords2id = [&size](const std::vector<SDL_Point> &coords) -> int {
        int id = 0;
        for (const auto &coord : coords) {
            id = id * size.y + coord.y;
            id = id * size.x + coord.x;
        }
        return id;
    };
    auto id2coords = [&size](int id, int num) -> std::vector<SDL_Point> {
        std::vector<SDL_Point> coords(num);
        for (auto iter = coords.rbegin(); iter != coords.rend(); iter++) {
            iter->x = id % size.x, id /= size.x;
            iter->y = id % size.y, id /= size.y;
        }
        return coords;
    };

    std::vector<int> dists(std::pow(size.x * size.y, player_num), INF);
    int start_id = coords2id(start_coords);
    dists[start_id] = 0;
    std::queue<std::pair<int, std::string>> que;
    que.push({start_id, ""});
    std::map<int, std::string> pathes;

    auto move = [this, &size](std::vector<SDL_Point> coords, const SDL_Point &dir) -> std::vector<SDL_Point> {
        std::vector<SDL_Point> next_coords(coords);
        for (auto &coord : next_coords) {
            auto next_coord = coord;
            next_coord.x += dir.x;
            next_coord.y += dir.y;
            if (next_coord.x < 0 || next_coord.x >= size.x || next_coord.y < 0 || next_coord.y >= size.y) {
                continue;
            }
            if ((*this->puzzle)[next_coord.x][next_coord.y] == marks.at(Define::CELL_TYPE::WALL)) {
                continue;
            }
            if ((*this->puzzle)[next_coord.x][next_coord.y] == marks.at(Define::CELL_TYPE::HOLE)) {
                return coords;
            }
            coord.x = next_coord.x;
            coord.y = next_coord.y;
        }
        return next_coords;
    };

    while (!que.empty()) {
        auto [id, path] = que.front();
        que.pop();
        auto coords = id2coords(id, player_num);
        for (const auto &[dir, dir_vec] : DIR_VECS) {
            auto next_coords = move(coords, dir_vec);
            int next_id = coords2id(next_coords);
            if (dists[next_id] != INF) {
                continue;
            }
            dists[next_id] = dists[id] + 1;
            que.push({next_id, path + DIR_CHARS.at(dir)});
            pathes[next_id] = path + DIR_CHARS.at(dir);
        }
    }

    int min_dist = INF;
    int goal_id = INF;
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            std::vector<SDL_Point> coords(player_num, {i, j});
            int id = coords2id(coords);
            if (dists[id] < min_dist) {
                min_dist = dists[id];
                goal_id = id;
            }
        }
    }
    if (min_dist == INF) {
        return;
    }

    this->step = min_dist;
    this->goal_coord = id2coords(goal_id, player_num).back();
    for (const auto &c : pathes[goal_id]) {
        this->ans.push_back(std::ranges::find_if(DIR_CHARS, [c](const auto &dir) { return dir.second == c; })->first);
    }
}

/**
 * @brief パズルをリセットする
 */
void SynchronizedPuzzleSolver::reset() {
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
std::unique_ptr<std::vector<std::string>> SynchronizedPuzzleSolver::get_puzzle() const {
    return std::make_unique<std::vector<std::string>>(*this->puzzle);
}

/**
 * @brief 解答を取得する
 * @return 解答
 */
std::vector<Define::DIRECTION> SynchronizedPuzzleSolver::get_ans() const {
    return ans;
}

/**
 * @brief 評価値を取得する
 * @return 評価値
 */
int SynchronizedPuzzleSolver::get_rate() const {
    return step;
}

/**
 * @brief ゴールの座標を取得する
 * @return ゴールの座標
 */
SDL_Point SynchronizedPuzzleSolver::get_goal() const {
    return goal_coord;
}