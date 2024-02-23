#include "Application.hpp"

#include "../Define/Define.hpp"
#include "../Looper/Looper.hpp"

/**
 * @brief アプリケーションのコンストラクタ
 */
Application::Application()
    : window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer) {
    return;
}

/**
 * @brief アプリケーションの初期化
 * @return 成功した場合は0, 失敗した場合は-1
 */
int Application::init() {
    // SDLの初期化
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDLの初期化に失敗しました: %s", SDL_GetError());
        return -1;
    }

    // ウィンドウの作成
    window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
        SDL_CreateWindow(
            Define::WIN_TITLE.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Define::WIN_W,
            Define::WIN_H,
            SDL_WINDOW_SHOWN
        ),
        SDL_DestroyWindow
    );
    if (window == nullptr) {
        SDL_Log("ウィンドウの作成に失敗しました: %s", SDL_GetError());
        return -1;
    }

    // レンダラの作成
    renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(
        SDL_CreateRenderer(
            window.get(),
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        ),
        SDL_DestroyRenderer
    );
    if (renderer == nullptr) {
        SDL_Log("レンダラの作成に失敗しました: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief アプリケーションの終了処理
 */
void Application::deinit() const {
    SDL_Quit();
    return;
}

/**
 * @brief アプリケーションのメインループ
 */
void Application::run() const {
    Looper looper;
    while (true) {
        looper.loop();
    }
    return;
}