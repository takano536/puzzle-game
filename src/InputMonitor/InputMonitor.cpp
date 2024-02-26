#include "InputMonitor.hpp"

#include <SDL2/SDL.h>

#include <limits>
#include <set>
#include <string>

/**
 * @brief 押されたボタンを検知して、フレーム数を更新する
 */
int InputMonitor::update() {
    std::set<SDL_Keycode> pressing_keys, releasing_keys;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                pressing_keys.insert(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                releasing_keys.insert(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }

    for (const auto &input : pressing_keys) {
        releasing_frame_cnts[input] = 0;
        if (pressing_frame_cnts[input] == 0) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Key Down: %s", SDL_GetKeyName(input));
            pressing_frame_cnts[input] = 1;
        }
    }
    for (const auto &input : releasing_keys) {
        pressing_frame_cnts[input] = 0;
        if (releasing_frame_cnts[input] == 0) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Key Up  : %s", SDL_GetKeyName(input));
            releasing_frame_cnts[input] = 1;
        }
    }
    for (auto &[input, frame_cnt] : pressing_frame_cnts) {
        if (frame_cnt > 0) {
            frame_cnt = (frame_cnt + 1 == std::numeric_limits<long long int>::max() ? 1 : frame_cnt + 1);
        }
    }
    for (auto &[input, frame_cnt] : releasing_frame_cnts) {
        if (frame_cnt > 0) {
            frame_cnt = (frame_cnt + 1 == std::numeric_limits<long long int>::max() ? 1 : frame_cnt + 1);
        }
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
    return std::string(SDL_GetKeyName(key)).empty() ? false : true;
}