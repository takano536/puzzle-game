#pragma once

#include <SDL.h>

#include <memory>

#include "../Looper/Looper.hpp"

/**
 * @brief The Application class
 * アプリケーション全体を管理するクラス
 */
class Application final {
  public:
    Application();
    ~Application() = default;

    int init();
    void deinit() const;
    void run();
    bool should_quit() const;

  private:
    Looper looper;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    SDL_Event event;
    bool is_running;
};