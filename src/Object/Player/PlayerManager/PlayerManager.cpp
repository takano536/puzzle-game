#include "PlayerManager.hpp"

PlayerManager::PlayerManager() {
}

void PlayerManager::add(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color, int speed) {
    Players.push_back(std::make_unique<Player>(coord, size, color, speed));
}

void PlayerManager::update() {
    for (auto &Player : Players) {
        Player->update();
    }
}

void PlayerManager::draw(SDL_Renderer *renderer) const {
    for (const auto &Player : Players) {
        Player->draw(renderer);
    }
}