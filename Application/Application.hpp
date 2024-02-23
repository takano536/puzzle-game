#pragma once

#include <SDL.h>

#include <memory>

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
    void run() const;

  private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
};