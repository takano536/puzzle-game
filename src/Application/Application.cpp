#include "Application.hpp"

#include "../Define/Define.hpp"
#include "../InputMonitor/InputMonitor.hpp"

/**
 * @brief アプリケーションのコンストラクタ
 */
Application::Application()
    : window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer),
      font(nullptr, TTF_CloseFont),
      surface(nullptr, SDL_FreeSurface),
      texture(nullptr, SDL_DestroyTexture) {

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
        SDL_Log("SDL could not initialize... SDL_Error: %s", SDL_GetError());
        return Define::ERROR;
    }

    // TTFの初期化
    if (TTF_Init() != 0) {
        SDL_Log("TTF could not initialize... TTF_Error: %s", TTF_GetError());
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
        SDL_Log("Window could not be created... SDL_Error: %s", SDL_GetError());
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
        SDL_Log("Renderer could not be created... SDL_Error: %s", SDL_GetError());
        return Define::ERROR;
    }
    SDL_SetRenderDrawColor(renderer.get(), Define::BLACK.r, Define::BLACK.g, Define::BLACK.b, Define::BLACK.a);

    // サーフェスの作成
    surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(
        SDL_CreateRGBSurface(0, Define::WIN_W, Define::WIN_H, 32, 0, 0, 0, 0),
        SDL_FreeSurface
    );
    if (surface == nullptr) {
        SDL_Log("Surface could not be created... SDL_Error: %s", SDL_GetError());
        return Define::ERROR;
    }

    // テクスチャの作成
    texture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(
        SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
        SDL_DestroyTexture
    );
    if (texture == nullptr) {
        SDL_Log("Texture could not be created... SDL_Error: %s", SDL_GetError());
        return Define::ERROR;
    }

    // フォントの作成
    font = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>(
        TTF_OpenFont(Define::FONT_PATH.c_str(), Define::FONT_SIZE),
        TTF_CloseFont
    );
    if (font == nullptr) {
        SDL_Log("Font could not be created... TTF_Error: %s", TTF_GetError());
        return Define::ERROR;
    }

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
    looper.loop(renderer.get(), surface.get(), texture.get(), font.get());
}

/**
 * @brief アプリケーションの終了判定
 * @return 終了する場合はtrue, それ以外はfalse
 */
bool Application::should_quit() const {
    return InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_ESCAPE) > 0;
}