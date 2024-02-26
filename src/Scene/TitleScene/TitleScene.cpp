#include "TitleScene.hpp"

#include "../../Define/Define.hpp"
#include "../GameScene/GameScene.hpp"

/**
 * @brief コンストラクタ
 * @param listener リスナー
 * @param params パラメータ
 */
TitleScene::TitleScene(IOnChangedListener *listener, const Parameter &params)
    : AbstractScene(listener, params) {
}

/**
 * @brief 更新
 * @param event イベントパラメータ
 */
void TitleScene::update(const SDL_Event &event) {
    if (event.type != SDL_KEYDOWN) {
        return;
    }
    switch (event.key.keysym.sym) {
        case SDLK_e: {
            Parameter params;
            params.set(GameScene::PARAM_KEY_LEVEL, static_cast<int>(Define::Level::Easy));
            bool should_clear_stuck = false;
            listener->on_changed(SceneType::Game, params, should_clear_stuck);
            break;
        }
        case SDLK_n: {
            Parameter params;
            params.set(GameScene::PARAM_KEY_LEVEL, static_cast<int>(Define::Level::Normal));
            bool should_clear_stuck = false;
            listener->on_changed(SceneType::Game, params, should_clear_stuck);
            break;
        }
        case SDLK_h: {
            Parameter params;
            params.set(GameScene::PARAM_KEY_LEVEL, static_cast<int>(Define::Level::Hard));
            bool should_clear_stuck = false;
            listener->on_changed(SceneType::Game, params, should_clear_stuck);
            break;
        }
        default:
            break;
    }
}

/**
 * @brief 描画
 * @param renderer レンダラー
 * @param surface サーフェス
 * @param texture テクスチャ
 * @param font フォント
 */
void TitleScene::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    surface = TTF_RenderUTF8_Blended(font, "Title", {0, 0, 0, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {0, 0, surface->w, surface->h};
    SDL_Rect dst = {0, 0, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, &rect, &dst);
}
