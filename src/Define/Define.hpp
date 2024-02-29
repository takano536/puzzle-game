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
    static const SDL_Point WINDOW_SIZE;
    static const SDL_Point WINDOW_CENTER;
    static const std::string WIN_TITLE;

    static const int SUCCESS;
    static const int FAILURE;

    static const SDL_Color BLACK;
    static const SDL_Color WHITE;
    static const SDL_Color BLUE;
    static const SDL_Color RED;

    static const std::string FONT_PATH;
    static const int FONT_SIZE;

    enum class LEVEL {
        EASY,
        NORMAL,
        HARD
    };

    enum class DIRECTION {
        NONE = -1,
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