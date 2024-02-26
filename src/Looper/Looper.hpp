#pragma once

#include <SDL.h>

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
    void loop(SDL_Window *window, SDL_Renderer *renderer) const;
    void on_changed(const SceneType scene_type, const Parameter &param, const bool should_clear_stuck) override;

  private:
    std::stack<std::shared_ptr<AbstractScene>> scenes;
};