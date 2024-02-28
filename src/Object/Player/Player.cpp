#include "Player.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../InputMonitor/InputMonitor.hpp"
#include "../../ShapeRenderer/ShapeRenderer.hpp"
#include "../../Utilities/Macros.hpp"

const std::map<Define::DIRECTION, std::vector<SDL_KeyCode>> Player::KEY_MAPS = {
    {Define::DIRECTION::UP, {SDLK_w, SDLK_UP}},
    {Define::DIRECTION::RIGHT, {SDLK_d, SDLK_RIGHT}},
    {Define::DIRECTION::DOWN, {SDLK_s, SDLK_DOWN}},
    {Define::DIRECTION::LEFT, {SDLK_a, SDLK_LEFT}},
};
const std::map<Define::DIRECTION, SDL_Point> Player::MOVING_DIRS = {
    {Define::DIRECTION::UP, {0, -1}},
    {Define::DIRECTION::RIGHT, {1, 0}},
    {Define::DIRECTION::DOWN, {0, 1}},
    {Define::DIRECTION::LEFT, {-1, 0}},
};

/**
 * @brief プレイヤーのコンストラクタ
 */
Player::Player(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color, int speed)
    : rect({coord.x, coord.y, player_size.x, player_size.y}),
      cell_size(cell_size),
      color(color),
      moving_dir(Define::DIRECTION::NONE),
      dest({-1, -1}),
      speed(speed) {
}

/**
 * @brief プレイヤーの更新
 */
void Player::update() {
    move();
}

/**
 * @brief プレイヤーの描画
 */
void Player::draw(SDL_Renderer *renderer) const {
    ShapeRenderer::aafilledCircleRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2, rect.w / 2, color.r, color.g, color.b, color.a);
}

/**
 * @brief プレイヤーの移動
 */
void Player::move() {
    if (moving_dir == Define::DIRECTION::NONE) {
        for (const auto &[dir, keys] : KEY_MAPS) {
            for (const auto &key : keys) {
                if (InputMonitor::get_instance().get_pressing_frame_cnt(key) > 0) {
                    moving_dir = dir;
                }
            }
        }
        if (moving_dir == Define::DIRECTION::NONE) {
            return;
        }
        update_dest();
    }

    rect.x += MOVING_DIRS.at(moving_dir).x * speed;
    rect.y += MOVING_DIRS.at(moving_dir).y * speed;

    switch (moving_dir) {
        case Define::DIRECTION::UP:
            if (rect.y <= dest.y) {
                rect.y = dest.y;
                moving_dir = Define::DIRECTION::NONE;
            }
            break;
        case Define::DIRECTION::RIGHT:
            if (rect.x >= dest.x) {
                rect.x = dest.x;
                moving_dir = Define::DIRECTION::NONE;
            }
            break;
        case Define::DIRECTION::DOWN:
            if (rect.y >= dest.y) {
                rect.y = dest.y;
                moving_dir = Define::DIRECTION::NONE;
            }
            break;
        case Define::DIRECTION::LEFT:
            if (rect.x <= dest.x) {
                rect.x = dest.x;
                moving_dir = Define::DIRECTION::NONE;
            }
            break;
        default:
            ERR("Invalid moving_dir");
    }
}

/**
 * @brief プレイヤーの目的地の更新
 */
void Player::update_dest() {
    dest = {rect.x + MOVING_DIRS.at(moving_dir).x * cell_size.x, rect.y + MOVING_DIRS.at(moving_dir).y * cell_size.y};
}