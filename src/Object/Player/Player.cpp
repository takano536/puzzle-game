#include "Player.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../InputMonitor/InputMonitor.hpp"
#include "../../ShapeRenderer/ShapeRenderer.hpp"

const std::array<std::tuple<Define::DIRECTION, std::vector<SDL_KeyCode>, SDL_Point>, 4> Player::KEY_MAPS = {
    std::make_tuple(Define::DIRECTION::UP, std::vector<SDL_KeyCode>{SDLK_w, SDLK_UP}, SDL_Point{0, -1}),
    std::make_tuple(Define::DIRECTION::RIGHT, std::vector<SDL_KeyCode>{SDLK_d, SDLK_RIGHT}, SDL_Point{1, 0}),
    std::make_tuple(Define::DIRECTION::DOWN, std::vector<SDL_KeyCode>{SDLK_s, SDLK_DOWN}, SDL_Point{0, 1}),
    std::make_tuple(Define::DIRECTION::LEFT, std::vector<SDL_KeyCode>{SDLK_a, SDLK_LEFT}, SDL_Point{-1, 0}),
};

/**
 * @brief プレイヤーのコンストラクタ
 */
Player::Player(SDL_Point coord, SDL_Point size, SDL_Color color, int speed)
    : rect({coord.x, coord.y, size.x, size.y}), color(color), speed(speed) {
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
    SDL_Point moving_vec = {0, 0};

    for (const auto &[direction, keys, vec] : KEY_MAPS) {
        for (const auto &key : keys) {
            if (InputMonitor::get_instance().get_pressing_frame_cnt(key) > 0) {
                moving_vec.x += vec.x * speed;
                moving_vec.y += vec.y * speed;
            }
        }
    }

    rect.x += moving_vec.x;
    rect.y += moving_vec.y;
}