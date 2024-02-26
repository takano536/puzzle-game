#include "Application.hpp"

#include "../Define/Define.hpp"

/**
 * @brief アプリケーションのコンストラクタ
 */
Application::Application()
    : window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer) {
    event = SDL_Event();
    is_running = true;
}

/**
 * @brief アプリケーションの初期化
 * @return 成功した場合は0, 失敗した場合は-1
 */
int Application::init() {
    // SDLの初期化
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDLの初期化に失敗しました: %s", SDL_GetError());
        return Define::ERROR;
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
        return Define::ERROR;
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
        return Define::ERROR;
    }
    SDL_SetRenderDrawColor(renderer.get(), Define::BG_R, Define::BG_G, Define::BG_B, Define::BG_A);

    return Define::SUCCESS;
}

/**
 * @brief アプリケーションの終了処理
 */
void Application::deinit() const {
    SDL_Quit();
}

/**
 * @brief アプリケーションのメインループ
 */
void Application::run() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;
            case SDL_KEYDOWN:
                is_running = false;
                break;
            default:
                break;
        }
    }
    looper.loop(window.get(), renderer.get());
    SDL_RenderPresent(renderer.get());
}

/**
 * @brief アプリケーションの終了判定
 * @return 終了する場合はtrue, それ以外はfalse
 */
bool Application::should_quit() const {
    return !is_running;
}