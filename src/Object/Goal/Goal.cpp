#include "Goal.hpp"

#include <SDL2/SDL.h>

#include "../../Define/Define.hpp"
#include "../../ShapeRenderer/ShapeRenderer.hpp"

/**
 * @brief ゴールのコンストラクタ
 */
Goal::Goal(SDL_Point coord, SDL_Point size, SDL_Color color)
    : rect({coord.x, coord.y, size.x, size.y}), color(color) {
}

/**
 * @brief ゴールの更新
 */
void Goal::update() {
}

/**
 * @brief ゴールの描画
 */
void Goal::draw(SDL_Renderer *renderer) const {
    ShapeRenderer::aafilledCircleRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2, rect.w / 2, color.r, color.g, color.b, color.a);
}
