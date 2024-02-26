#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../AbstractScene/AbstractScene.hpp"

#include <string>

/**
 * @brief ゲームシーン
 */
class GameScene : public AbstractScene {
  public:
    GameScene(IOnChangedListener *listener, const Parameter &params);
    ~GameScene() = default;
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;

    const static std::string PARAM_KEY_LEVEL;

  private:
    int level;
};