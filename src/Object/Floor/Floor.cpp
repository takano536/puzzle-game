#include "Floor.hpp"

#include <SDL2/SDL.h>

#include "../../Define/Define.hpp"

/**
 * @brief 床のコンストラクタ
 */
Floor::Floor(SDL_Point coord, SDL_Point size, SDL_Color color)
    : rect({coord.x, coord.y, size.x, size.y}), color(color) {
}

/**
 * @brief 床の更新
 */
void Floor::update() {
}

/**
 * @brief 床の描画
 */
void Floor::draw(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
