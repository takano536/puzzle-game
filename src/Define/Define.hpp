#pragma once

#include <SDL2/SDL.h>

#include <string>

/**
 * @brief The Define class
 * 定数を管理するクラス
 */
class Define final {
  public:
    static const int WIN_W;
    static const int WIN_H;
    static const std::string WIN_TITLE;

    static const int SUCCESS;
    static const int ERROR;

    static const SDL_Color BLACK;
    static const SDL_Color WHITE;
    static const SDL_Color BLUE;

    static const std::string FONT_PATH;
    static const int FONT_SIZE;

    enum class LEVEL {
        EASY,
        NORMAL,
        HARD
    };

    enum class DIRECTION {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
};