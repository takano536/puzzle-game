#include "WallManager.hpp"

WallManager::WallManager() {
}

void WallManager::add(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color) {
    walls.push_back(std::make_unique<Wall>(coord, size, color));
}

void WallManager::update() {
    for (auto &wall : walls) {
        wall->update();
    }
}

void WallManager::draw(SDL_Renderer *renderer) const {
    for (const auto &wall : walls) {
        wall->draw(renderer);
    }
}