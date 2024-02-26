#include "Player.hpp"

#include <SDL2/SDL.h>

#include "../../Define/Define.hpp"
#include "../../InputMonitor/InputMonitor.hpp"

const static float SPEED = 5;

/**
 * @brief プレイヤーのコンストラクタ
 */
Player::Player() {
    rect = {100.f, 100.f, 25.f, 25.f};
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
    SDL_SetRenderDrawColor(renderer, Define::BLUE.r, Define::BLUE.g, Define::BLUE.b, Define::BLUE.a);
    SDL_RenderFillRectF(renderer, &rect);
}

/**
 * @brief プレイヤーの移動
 */
void Player::move() {
    float vec_x = 0;
    float vec_y = 0;

    if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_LEFT) > 0) {
        vec_x = -SPEED;
    }
    if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_RIGHT) > 0) {
        vec_x = SPEED;
    }
    if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_UP) > 0) {
        vec_y = -SPEED;
    }
    if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_DOWN) > 0) {
        vec_y = SPEED;
    }

    rect.x += vec_x;
    rect.y += vec_y;
}