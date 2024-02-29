#include "Application.hpp"

#include "../Define/Define.hpp"
#include "../InputMonitor/InputMonitor.hpp"
#include "../Utilities/Macros.hpp"

/**
 * @brief アプリケーションのコンストラクタ
 */
Application::Application()
    : window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer),
      surface(nullptr, SDL_FreeSurface),
      texture(nullptr, SDL_DestroyTexture),
      font(nullptr, TTF_CloseFont),
      bg_color(Define::WHITE) {
}

/**
 * @brief アプリケーションの初期化
 * @return 成功した場合はDefine::SUCCESS, 失敗した場合はDefine::FAILURE
 */
int Application::init() {
    // SDLの初期化
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        ERR("SDL could not initialize... SDL_Error: " + std::string(SDL_GetError()));
        return Define::FAILURE;
    }

    // TTFの初期化
    if (TTF_Init() != 0) {
        ERR("TTF could not initialize... TTF_Error: " + std::string(TTF_GetError()));
        return Define::FAILURE;
    }

    // ウィンドウの作成
    window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
        SDL_CreateWindow(
            Define::WIN_TITLE.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Define::WINDOW_SIZE.x,
            Define::WINDOW_SIZE.y,
            SDL_WINDOW_SHOWN
        ),
        SDL_DestroyWindow
    );
    if (window == nullptr) {
        ERR("Window could not be created... SDL_Error: %s" + std::string(SDL_GetError()));
        return Define::FAILURE;
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
        ERR("Renderer could not be created... SDL_Error: %s" + std::string(SDL_GetError()));
        return Define::FAILURE;
    }

    // サーフェスの作成
    surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(
        SDL_CreateRGBSurface(0, Define::WINDOW_SIZE.x, Define::WINDOW_SIZE.y, 32, 0, 0, 0, 0),
        SDL_FreeSurface
    );
    if (surface == nullptr) {
        ERR("Surface could not be created... SDL_Error: %s" + std::string(SDL_GetError()));
        return Define::FAILURE;
    }

    // テクスチャの作成
    texture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(
        SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
        SDL_DestroyTexture
    );
    if (texture == nullptr) {
        ERR("Texture could not be created... SDL_Error: %s" + std::string(SDL_GetError()));
        return Define::FAILURE;
    }

    // フォントの作成
    font = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>(
        TTF_OpenFont(Define::FONT_PATH.c_str(), Define::FONT_SIZE),
        TTF_CloseFont
    );
    if (font == nullptr) {
        ERR("Font could not be created... TTF_Error: %s" + std::string(TTF_GetError()));
        return Define::FAILURE;
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
bool Application::is_running() const {
    return InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_ESCAPE) > 0;
}