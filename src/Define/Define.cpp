#include "Define.hpp"

#include <SDL2/SDL.h>

const SDL_Point Define::WINDOW_SIZE = {360, 640};
const SDL_Point Define::WINDOW_CENTER = {WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2};
const std::string Define::WIN_TITLE = "SYNCHRONIZED PUZZLE";

const int Define::SUCCESS = 0;
const int Define::ERROR = -1;

const SDL_Color Define::BLACK = {33, 33, 33, 255};
const SDL_Color Define::WHITE = {222, 222, 222, 255};
const SDL_Color Define::BLUE = {66, 165, 245, 255};
const SDL_Color Define::RED = {146, 40, 32, 255};

const std::string Define::FONT_PATH = "../assets/fonts/Montserrat-VariableFont_wght.ttf";
const int Define::FONT_SIZE = 24;