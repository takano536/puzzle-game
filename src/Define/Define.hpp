#pragma once

#include <SDL2/SDL.h>

#include <string>

/**
 * @brief The Define class
 * 定数を管理するクラス
 */
class Define final {
  public:
    const static int WIN_W;
    const static int WIN_H;
    const static std::string WIN_TITLE;

    const static int SUCCESS;
    const static int ERROR;

    const static SDL_Color BLACK;
    const static SDL_Color WHITE;
    const static SDL_Color BLUE;

    const static std::string FONT_PATH;
    const static int FONT_SIZE;

    enum class Level {
        Easy,
        Normal,
        Hard
    };
};