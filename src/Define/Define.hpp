#pragma once

#include <SDL2/SDL.h>

#include <array>
#include <string>

/**
 * @brief The Define class
 * 定数を管理するクラス
 */
class Define final {
  public:
    const static SDL_Point WINDOW_SIZE;
    const static SDL_Point WINDOW_CENTER;
    const static std::string WIN_TITLE;

    const static int SUCCESS;
    const static int ERROR;

    const static SDL_Color BLACK;
    const static SDL_Color WHITE;
    const static SDL_Color BLUE;
    const static SDL_Color RED;

    const static std::string FONT_PATH;
    const static int FONT_SIZE;

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

    enum class CELL_TYPE {
        FLOOR,
        WALL,
        START,
        HOLE,
    };
};