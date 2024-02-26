#include "TitleScene.hpp"

#include "../../Define/Define.hpp"
#include "../../InputMonitor/InputMonitor.hpp"
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
void TitleScene::update() {
    Parameter params;
    params.set(GameScene::PARAM_KEY_LEVEL, -1);
    bool should_clear_stuck = false;
    if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_e) > 0) {
        params.set(GameScene::PARAM_KEY_LEVEL, static_cast<int>(Define::Level::Easy));
    } else if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_n) > 0) {
        params.set(GameScene::PARAM_KEY_LEVEL, static_cast<int>(Define::Level::Normal));
    } else if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_h) > 0) {
        params.set(GameScene::PARAM_KEY_LEVEL, static_cast<int>(Define::Level::Hard));
    }

    if (params.get(GameScene::PARAM_KEY_LEVEL) != -1) {
        listener->on_changed(SceneType::Game, params, should_clear_stuck);
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
    surface = TTF_RenderUTF8_Blended(font, "Title", Define::BLUE);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {0, 0, surface->w, surface->h};
    SDL_Rect dst = {0, 0, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, &rect, &dst);
}
