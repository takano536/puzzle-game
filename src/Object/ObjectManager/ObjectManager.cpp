#include "ObjectManager.hpp"

#include "../../Utilities/Macros.hpp"
#include "../Floor/Floor.hpp"
#include "../Goal/Goal.hpp"
#include "../Hole/Hole.hpp"
#include "../Wall/Wall.hpp"

ObjectManager::ObjectManager() {
}

void ObjectManager::add(Define::CELL_TYPE object_type, const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color) {
    switch (object_type) {
        case Define::CELL_TYPE::GOAL:
            objects.push_back(std::make_unique<Goal>(coord, size, color));
            break;
        case Define::CELL_TYPE::WALL:
            objects.push_back(std::make_unique<Wall>(coord, size, color));
            break;
        case Define::CELL_TYPE::HOLE:
            objects.push_back(std::make_unique<Hole>(coord, size, color));
            break;
        case Define::CELL_TYPE::FLOOR:
            objects.push_back(std::make_unique<Floor>(coord, size, color));
            break;
        case Define::CELL_TYPE::START:
            ERR("Player does not allow to be added to ObjectManager");
            break;
        default:
            ERR("Invalid object_type");
            break;
    }
}

void ObjectManager::update() {
    for (auto &object : objects) {
        object->update();
    }
}

void ObjectManager::draw(SDL_Renderer *renderer) const {
    for (const auto &object : objects) {
        object->draw(renderer);
    }
}