#include "PuzzleGenerator.hpp"

#include <algorithm>
#include <limits>
#include <random>

#include "../utilities/Macros.hpp"

/**
 * @brief コンストラクタ
 * @param size パズルのサイズ
 * @param inner_marks パズルのオブジェクト
 * @note パズルのサイズとオブジェクトを設定する
 */
PuzzleGenerator::PuzzleGenerator(const SDL_Point &size, const std::string &inner_marks, const std::string &outer_marks, char start_mark, int start_num)
    : size(size),
      inner_marks(inner_marks),
      outer_marks(outer_marks),
      seed(std::numeric_limits<std::uint_fast32_t>::max()),
      start_mark(start_mark),
      start_num(start_num) {
}

/**
 * @brief パスワードをセットする
 * @param password パスワード
 * @note 未実装
 */
void PuzzleGenerator::set_password(const std::string &password) {
    ERR("Not implemented");
    this->password = password;
}

/**
 * @brief シードをセットする
 * @param seed シード
 */
void PuzzleGenerator::set_seed(std::uint_fast32_t seed) {
    this->seed = seed;
}

/**
 * @brief パズルを生成する
 * @return 二次元配列のパズル
 * @note パスワードがセットされている場合は復号化を行う（未実装）
 */
std::unique_ptr<std::vector<std::string>> PuzzleGenerator::generate() {
    if (!password.empty()) {
        return decrypt(password);
    }

    std::random_device seed_gen;
    std::mt19937 rand_gen;
    rand_gen.seed(seed == std::numeric_limits<std::uint_fast32_t>::max() ? seed_gen() : seed);

    std::vector<std::uint32_t> inner_rand_nums((size.x - 2) * (size.y - 2) + 4), outer_rand_nums(size.x * 2 + size.y * 2 - 4);
    std::ranges::generate(inner_rand_nums, [&] { return std::uniform_int_distribution<std::uint32_t>(0, inner_marks.size() - 1)(rand_gen); });
    std::ranges::generate(outer_rand_nums, [&] { return std::uniform_int_distribution<std::uint32_t>(0, outer_marks.size() - 1)(rand_gen); });

    std::vector<std::string> puzzle(size.y, std::string(size.x, ' '));
    auto inner_rand_iter = inner_rand_nums.begin();
    auto outer_rand_iter = outer_rand_nums.begin();
    for (int x = 0; x < size.x; x++) {
        puzzle[0][x] = outer_marks[*outer_rand_iter++];
        puzzle[size.y - 1][x] = outer_marks[*outer_rand_iter++];
    }
    for (int y = 1; y < size.y - 1; y++) {
        puzzle[y][0] = outer_marks[*outer_rand_iter++];
        puzzle[y][size.x - 1] = outer_marks[*outer_rand_iter++];
        for (int x = 1; x < size.x - 1; x++) {
            puzzle[y][x] = inner_marks[*inner_rand_iter++];
        }
    }

    std::vector<SDL_Point> start_coords(start_num);
    std::ranges::generate(start_coords, [&] {
        return SDL_Point{std::uniform_int_distribution<int>(1, size.x - 2)(rand_gen), std::uniform_int_distribution<int>(1, size.y - 2)(rand_gen)};
    });
    for (auto &coord : start_coords) {
        puzzle[coord.y][coord.x] = start_mark;
    }

    return std::make_unique<std::vector<std::string>>(puzzle);
}

/**
 * @brief パスワードを復号化する
 * @param password パスワード
 * @return 二次元配列のパズル
 * @note 未実装
 */
std::unique_ptr<std::vector<std::string>> PuzzleGenerator::decrypt(const std::string &password) {
    ERR("Not implemented");
    return {};
}

/**
 * @brief パズルを暗号化する
 * @param puzzle 二次元配列のパズル
 * @return パスワード
 * @note 未実装
 */
std::string PuzzleGenerator::encrypt(const std::vector<std::string> &puzzle) {
    ERR("Not implemented");
    return {};
}