#include "Define.hpp"

#include <SDL2/SDL.h>

const int Define::WIN_W = 360;
const int Define::WIN_H = 640;
const std::string Define::WIN_TITLE = "SYNCHRONIZED PUZZLE";

const int Define::SUCCESS = 0;
const int Define::ERROR = -1;

const SDL_Color Define::BLACK = {33, 33, 33, 255};
const SDL_Color Define::BLUE = {66, 165, 245, 255};

const std::string Define::FONT_PATH = "../assets/fonts/NotoSansJP-VariableFont_wght.ttf";
const int Define::FONT_SIZE = 24;