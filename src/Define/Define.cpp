#include "Define.hpp"

#include <SDL2/SDL.h>

const int Define::WIN_W = 1280;
const int Define::WIN_H = 720;
const std::string Define::WIN_TITLE = "SYNCHRONIZED PUZZLE";

const int Define::SUCCESS = 0;
const int Define::ERROR = -1;

const int Define::BG_R = 0xdf;
const int Define::BG_G = 0xff;
const int Define::BG_B = 0xdf;
const int Define::BG_A = SDL_ALPHA_OPAQUE;

const std::string Define::FONT_PATH = "../assets/fonts/marukiya.ttf";
const int Define::FONT_SIZE = 24;