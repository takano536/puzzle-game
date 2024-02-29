#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <vector>

#include "../../Define/Define.hpp"
#include "../Object.hpp"

/**
 * @brief プレイヤークラス
 * @param coord SDL_Point - 初期位置座標
 * @param player_size SDL_Point - プレイヤーのサイズ
 * @param cell_size SDL_Point - グリッドのサイズ
 * @param color SDL_Color - プレイヤーの色
 * @param speed int - 移動速度
 */
class Player : public Object {
  public:
    Player(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color, int speed);
    virtual ~Player() = default;
    void update() override;
    int update(const bool are_stopped_everyone, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions);
    void draw(SDL_Renderer *renderer) const override;
    void reset();
    void undo();
    bool is_stopped() const;

  private:
    static const std::map<Define::DIRECTION, std::vector<SDL_KeyCode>> KEY_MAPS;
    static const std::map<Define::DIRECTION, SDL_Point> MOVING_DIRS;

    SDL_Rect rect;
    SDL_Point init_coord;
    SDL_Point prev_coord;
    SDL_Point cell_size;
    SDL_Color color;
    Define::DIRECTION moving_dir;
    SDL_Point dest;
    int speed;

    int move(const bool are_stopped_everyone, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions);
};