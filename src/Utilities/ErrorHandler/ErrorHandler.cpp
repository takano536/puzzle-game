#include "ErrorHandler.hpp"

#include <SDL2/SDL.h>

#include "../../Define/Define.hpp"

/**
 * @brief エラー終了処理
 * @param error エラーコード
 * @details エラーメッセージを出力し、プログラムを終了する
 */
void ErrorHandler::finish(const std::string &error_message, const char *func, const int line) {
    SDL_Log("%s:%d", func, line);
    SDL_Log("Error: %s", error_message.c_str());
    SDL_Quit();
    exit(99);
}