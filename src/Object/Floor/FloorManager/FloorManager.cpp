#include "FloorManager.hpp"

FloorManager::FloorManager() {
}

void FloorManager::add(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color) {
    Floors.push_back(std::make_unique<Floor>(coord, size, color));
}

void FloorManager::update() {
    for (auto &Floor : Floors) {
        Floor->update();
    }
}

void FloorManager::draw(SDL_Renderer *renderer) const {
    for (const auto &Floor : Floors) {
        Floor->draw(renderer);
    }
}