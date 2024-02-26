#include "Wall.hpp"

#include "../../Define/Define.hpp"

static const int SIZE = 20;

Wall::Wall(SDL_Point coord)
    : rect({coord.x, coord.y, SIZE, SIZE}), color(Define::BLACK) {
}

void Wall::update() {
}

void Wall::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
