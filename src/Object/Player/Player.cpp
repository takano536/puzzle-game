#include "Player.hpp"

#include <SDL2/SDL.h>

#include <map>
#include <vector>

#include "../../Define/Define.hpp"
#include "../../InputMonitor/InputMonitor.hpp"

static const int SIZE = 20;
static const int SPEED = 5;

static const std::map<Define::DIRECTION, std::vector<SDL_KeyCode>> KEY_MAPS = {
    {Define::DIRECTION::UP, {SDLK_w, SDLK_UP}},
    {Define::DIRECTION::RIGHT, {SDLK_d, SDLK_RIGHT}},
    {Define::DIRECTION::DOWN, {SDLK_s, SDLK_DOWN}},
    {Define::DIRECTION::LEFT, {SDLK_a, SDLK_LEFT}},
};
static const std::map<Define::DIRECTION, SDL_Point> VECS = {
    {Define::DIRECTION::UP, {0, -SPEED}},
    {Define::DIRECTION::RIGHT, {SPEED, 0}},
    {Define::DIRECTION::DOWN, {0, SPEED}},
    {Define::DIRECTION::LEFT, {-SPEED, 0}},
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
    SDL_Point vec = {0, 0};

    for (const auto &[direction, keys] : KEY_MAPS) {
        for (const auto &key : keys) {
            if (InputMonitor::get_instance().get_pressing_frame_cnt(key) > 0) {
                vec.x += VECS.at(direction).x;
                vec.y += VECS.at(direction).y;
                break;
            }
        }
    }

    rect.x += vec.x;
    rect.y += vec.y;
}