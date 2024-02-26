#include "InputMonitor.hpp"

#include <SDL2/SDL.h>

#include <set>

/**
 * @brief 押されたボタンを検知して、フレーム数を更新する
 */
int InputMonitor::update() {
    std::set<SDL_Keycode> inputs;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                inputs.insert(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }

    for (const auto &input : inputs) {
        releasing_frame_cnts[input] = 0;
        pressing_frame_cnts[input]++;
    }
    for (auto &[key, value] : releasing_frame_cnts) {
        if (inputs.contains(key)) {
            continue;
        }
        pressing_frame_cnts[key] = 0;
        value++;
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