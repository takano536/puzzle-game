#include "TitleScene.hpp"

#include "../../Define/Define.hpp"
#include "../../InputMonitor/InputMonitor.hpp"
#include "../GameScene/GameScene.hpp"

static const std::map<Define::LEVEL, SDL_KeyCode> KEY_MAPS = {
    {Define::LEVEL::EASY, SDLK_e},
    {Define::LEVEL::NORMAL, SDLK_n},
    {Define::LEVEL::HARD, SDLK_h},
};

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
 */
void TitleScene::update() {
    Parameter params;
    params.set(GameScene::PARAM_KEY_LEVEL, -1);
    bool should_clear_stuck = false;

    for (const auto &[level, key] : KEY_MAPS) {
        if (InputMonitor::get_instance().get_pressing_frame_cnt(key) > 0) {
            params.set(GameScene::PARAM_KEY_LEVEL, static_cast<int>(level));
            break;
        }
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
    surface = TTF_RenderUTF8_Blended(font, "Title", Define::WHITE);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {0, 0, surface->w, surface->h};
    SDL_Rect dst = {0, 0, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, &rect, &dst);
}
