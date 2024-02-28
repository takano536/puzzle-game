#include "PlayerManager.hpp"

PlayerManager::PlayerManager() {
}

void PlayerManager::add(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color, int speed) {
    Players.push_back(std::make_unique<Player>(coord, player_size, cell_size, color, speed));
}

void PlayerManager::update() {
    for (const auto &Player : Players) {
        Player->update();
    }
}

void PlayerManager::draw(SDL_Renderer *renderer) const {
    for (const auto &Player : Players) {
        Player->draw(renderer);
    }
}