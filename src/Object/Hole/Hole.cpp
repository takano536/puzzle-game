#include "Hole.hpp"

#include <SDL2/SDL.h>

#include "../../Define/Define.hpp"
#include "../../ShapeRenderer/ShapeRenderer.hpp"

/**
 * @brief 穴のコンストラクタ
 */
Hole::Hole(SDL_Point coord, SDL_Point size, SDL_Color color)
    : rect({coord.x, coord.y, size.x, size.y}), color(color) {
}

/**
 * @brief 穴の更新
 */
void Hole::update() {
}

/**
 * @brief 穴の描画
 */
void Hole::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    ShapeRenderer::aafilledCircleRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2, rect.w / 2, color.r, color.g, color.b, color.a);
}
