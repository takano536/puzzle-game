#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <stack>

#include "../Scene/AbstractScene/AbstractScene.hpp"
#include "../Scene/IOnChangedListener.hpp"
#include "../Scene/Parameter/Parameter.hpp"
#include "../Scene/SceneType.hpp"

/**
 * @brief The Looper class
 * メインループを管理するクラス
 */
class Looper final : public IOnChangedListener {
  public:
    Looper();
    ~Looper() = default;
    int loop(const SDL_Event &event, SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const;
    void on_changed(const SceneType scene_type, const Parameter &params, const bool should_clear_stuck) override;

  private:
    std::stack<std::shared_ptr<AbstractScene>> scenes;
};