#include "Player.hpp"

#include <SDL2/SDL.h>

#include <array>
#include <tuple>
#include <vector>

#include "../../Define/Define.hpp"
#include "../../InputMonitor/InputMonitor.hpp"

static const int SIZE = 20;
const static int SPEED = 5;

const static std::array<std::tuple<Define::DIRECTION, std::vector<SDL_KeyCode>, SDL_Point>, 4> KEY_MAPS = {
    std::make_tuple(Define::DIRECTION::UP, std::vector<SDL_KeyCode>{SDLK_w, SDLK_UP}, SDL_Point{0, -SPEED}),
    std::make_tuple(Define::DIRECTION::RIGHT, std::vector<SDL_KeyCode>{SDLK_d, SDLK_RIGHT}, SDL_Point{SPEED, 0}),
    std::make_tuple(Define::DIRECTION::DOWN, std::vector<SDL_KeyCode>{SDLK_s, SDLK_DOWN}, SDL_Point{0, SPEED}),
    std::make_tuple(Define::DIRECTION::LEFT, std::vector<SDL_KeyCode>{SDLK_a, SDLK_LEFT}, SDL_Point{-SPEED, 0}),
};

/**
 * @brief プレイヤーのコンストラクタ
 */
Player::Player()
    : rect({0, 0, SIZE, SIZE}), color(Define::BLUE) {
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
void Player::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRectF(renderer, &rect);
}

/**
 * @brief プレイヤーの移動
 */
void Player::move() {
    SDL_Point moving_vec = {0, 0};

    for (const auto &[direction, keys, vec] : KEY_MAPS) {
        for (const auto &key : keys) {
            if (InputMonitor::get_instance().get_pressing_frame_cnt(key) > 0) {
                moving_vec.x += vec.x;
                moving_vec.y += vec.y;
            }
        }
    }

    rect.x += moving_vec.x;
    rect.y += moving_vec.y;
}