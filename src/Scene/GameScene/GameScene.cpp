#include "GameScene.hpp"

const std::string GameScene::PARAM_KEY_LEVEL = "PARAM_KEY_LEVEL";

/**
 * @brief コンストラクタ
 * @param listener リスナー
 * @param params パラメータ
 */
GameScene::GameScene(IOnChangedListener *listener, const Parameter &params)
    : AbstractScene(listener, params) {

    level = params.get(PARAM_KEY_LEVEL);
}

/**
 * @brief 更新
 * @param event イベントパラメータ
 */
void GameScene::update(const SDL_Event &event) {
}

/**
 * @brief 描画
 * @param renderer レンダラー
 * @param surface サーフェス
 * @param texture テクスチャ
 * @param font フォント
 */
void GameScene::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    std::string text = "Game Level: " + std::to_string(level);
    surface = TTF_RenderUTF8_Blended(font, text.c_str(), {0, 0, 0, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {0, 0, surface->w, surface->h};
    SDL_Rect dst = {0, 0, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, &rect, &dst);
}