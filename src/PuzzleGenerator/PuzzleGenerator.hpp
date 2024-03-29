#pragma once

#include <SDL2/SDL.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../Define/Define.hpp"

/**
 * @brief パズル生成クラス
 * @param size SDL_Point - パズルのサイズ
 * @param inner_marks std::string - 内側で使用するマーク
 * @param outer_marks std::string - 外側で使用するマーク
 * @param start_mark char - スタートのマーク
 * @param start_num int - スタートの数
 */
class PuzzleGenerator final {
  public:
    PuzzleGenerator(const SDL_Point &size, const std::string &inner_marks, const std::string &outer_marks, char start_mark, int start_num);
    void set_password(const std::string &password);
    void set_seed(std::uint_fast32_t seed);
    std::unique_ptr<std::vector<std::string>> generate();

  private:
    SDL_Point size;
    std::string inner_marks;
    std::string outer_marks;
    char start_mark;
    int start_num;
    std::uint_fast32_t seed;
    std::string password;

    std::unique_ptr<std::vector<std::string>> decrypt(const std::string &password);
    std::string encrypt(const std::vector<std::string> &puzzle);
};