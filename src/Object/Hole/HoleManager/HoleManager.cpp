#include "HoleManager.hpp"

HoleManager::HoleManager() {
}

void HoleManager::add(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color) {
    Holes.push_back(std::make_unique<Hole>(coord, size, color));
}

void HoleManager::update() {
    for (auto &Hole : Holes) {
        Hole->update();
    }
}

void HoleManager::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    for (const auto &Hole : Holes) {
        Hole->draw(renderer, surface, texture, font);
    }
}