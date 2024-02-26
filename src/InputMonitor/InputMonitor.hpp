#pragma once

#include <SDL2/SDL.h>

#include <map>

#include "../Utilities/Singleton.hpp"

class InputMonitor : public Singleton<InputMonitor> {
    InputMonitor() = default;
    friend Singleton<InputMonitor>;

  public:
    int update();
    int get_pressing_frame_cnt(const SDL_Keycode &key);
    int get_releasing_frame_cnt(const SDL_Keycode &key);

  private:
    std::map<SDL_Keycode, long long int> pressing_frame_cnts;
    std::map<SDL_Keycode, long long int> releasing_frame_cnts;
    SDL_Point mouse_coord;
    SDL_Event event;

    bool is_valid_input(const SDL_Keycode &key) const;
};