#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
    bool is_running() const;

  private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;
    SDL_Event event;

    SDL_Color bg_color;

    Looper looper;
};