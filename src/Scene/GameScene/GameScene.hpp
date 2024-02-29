#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <string>

#include "../../Object/Floor/FloorManager/FloorManager.hpp"
#include "../../Object/Hole/HoleManager/HoleManager.hpp"
#include "../../Object/Player/PlayerManager/PlayerManager.hpp"
#include "../../Object/Wall/WallManager/WallManager.hpp"
#include "../../PuzzleGenerator/PuzzleGenerator.hpp"
#include "../../PuzzleSolver/PuzzleSolver.hpp"
#include "../AbstractScene/AbstractScene.hpp"

/**
 * @brief ゲームシーン
 */
class GameScene : public AbstractScene {
  public:
    GameScene(IOnChangedListener *listener, const Parameter &params);
    ~GameScene() = default;
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;

    static const std::string PARAM_KEY_LEVEL;
    static const std::map<Define::CELL_TYPE, char> CELL_MARKS;

  private:
    static const std::string INNER_MARKS;
    static const std::string OUTER_MARKS;
    static const char START_MARK;
    static const int START_NUM;

    static const int THRESHOLD;
    static const SDL_Point PUZZLE_SIZE;

    static const int PLAYER_SPEED;

    static const std::map<Define::DIRECTION, int> MARGIN;

    int level;

    std::unique_ptr<FloorManager> floors;
    std::unique_ptr<HoleManager> holes;
    std::unique_ptr<PlayerManager> players;
    std::unique_ptr<WallManager> walls;

    std::unique_ptr<PuzzleGenerator> puzzle_generator;
    std::unique_ptr<PuzzleSolver> puzzle_solver;
    std::vector<std::string> puzzle;
    std::vector<Define::DIRECTION> ans;

    int cell_size;
    SDL_Point upper_left;
};