#include "GameScene.hpp"

#include "../../Define/Define.hpp"

const std::string GameScene::PARAM_KEY_LEVEL = "PARAM_KEY_LEVEL";

/**
 * @brief コンストラクタ
 * @param listener リスナー
 * @param params パラメータ
 */
GameScene::GameScene(IOnChangedListener *listener, const Parameter &params)
    : AbstractScene(listener, params) {

    level = params.get(PARAM_KEY_LEVEL);
    player = std::make_shared<Player>();
}

/**
 * @brief 更新
 */
void GameScene::update() {
    player->update();
}

/**
 * @brief 描画
 * @param renderer レンダラー
 * @param surface サーフェス
 * @param texture テクスチャ
 * @param font フォント
 */
void GameScene::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    player->draw(renderer, surface, texture, font);

    std::string text = "Game Level: " + std::to_string(level);
    surface = TTF_RenderUTF8_Blended(font, text.c_str(), Define::WHITE);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {0, 0, surface->w, surface->h};
    SDL_Rect dst = {0, 0, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, &rect, &dst);
}