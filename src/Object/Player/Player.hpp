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
    Player(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color);
    virtual ~Player() = default;
    void update() override;
    int update(const bool are_stopped_everyone, const bool is_slip, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions);
    void draw(SDL_Renderer *renderer) const override;
    void reset();
    void undo();
    bool is_stopped() const;

  private:
    static const std::map<Define::DIRECTION, std::vector<SDL_KeyCode>> KEY_MAPS;
    static const std::map<Define::DIRECTION, SDL_Point> MOVING_DIRS;
    static const int ACCERELATION;
    static const int VELOCITY;

    SDL_Rect rect;
    SDL_Point init_coord;
    SDL_Point prev_coord;
    SDL_Point cell_size;
    SDL_Color color;
    Define::DIRECTION moving_dir;
    SDL_Point dest;
    int frame_cnt;

    int move(const bool are_stopped_everyone, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions);
    int move_on_ice(const bool are_stopped_everyone, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions);
};