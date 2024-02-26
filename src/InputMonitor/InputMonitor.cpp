#include "InputMonitor.hpp"

#include <SDL2/SDL.h>

#include <set>

/**
 * @brief 押されたボタンを検知して、フレーム数を更新する
 */
int InputMonitor::update() {
    std::set<SDL_Keycode> pressing_inputs, releasing_inputs;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                SDL_Log("Key Down: %s", SDL_GetKeyName(event.key.keysym.sym));
                pressing_inputs.insert(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                SDL_Log("Key Up: %s", SDL_GetKeyName(event.key.keysym.sym));
                releasing_inputs.insert(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }

    for (const auto &input : pressing_inputs) {
        releasing_frame_cnts[input] = 0;
        pressing_frame_cnts[input]++;
    }
    for (const auto &input : releasing_inputs) {
        pressing_frame_cnts[input] = 0;
        releasing_frame_cnts[input]++;
    }
    return 0;
}

/**
 * @brief 指定されたキーの押されているフレーム数を返す
 * @param key SDL_Keycode
 */
int InputMonitor::get_pressing_frame_cnt(const SDL_Keycode &key) {
    return is_valid_input(key) ? pressing_frame_cnts[key] : -1;
}

/**
 * @brief 指定されたキーの離されているフレーム数を返す
 * @param key SDL_Keycode
 */
int InputMonitor::get_releasing_frame_cnt(const SDL_Keycode &key) {
    return is_valid_input(key) ? releasing_frame_cnts[key] : -1;
}

/**
 * @brief 指定されたキーが有効かどうかを返す
 * @param key SDL_Keycode
 */
bool InputMonitor::is_valid_input(const SDL_Keycode &key) const {
    return SDL_GetKeyName(key) == "" ? false : true;
}