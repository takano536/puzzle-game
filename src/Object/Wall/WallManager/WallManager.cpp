#include "WallManager.hpp"

WallManager::WallManager() {
}

void WallManager::add(SDL_Point coord) {
    walls.push_back(Wall(coord));
}

void WallManager::update() {
    for (auto &wall : walls) {
        wall.update();
    }
}

void WallManager::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    for (const auto &wall : walls) {
        wall.draw(renderer, surface, texture, font);
    }
}