#include "Wall.hpp"

#include "../../Define/Define.hpp"
#include "../../ShapeRenderer/ShapeRenderer.hpp"

const int Wall::RADIUS = 5;

Wall::Wall(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color)
    : rect({coord.x, coord.y, size.x, size.y}), color(color) {
}

void Wall::update() {
}

void Wall::draw(SDL_Renderer *renderer) const {
    ShapeRenderer::aafilledRoundRectRGBA(renderer, rect.x + rect.w, rect.y, rect.x, rect.y + rect.h, Wall::RADIUS, color.r, color.g, color.b, color.a);
}
