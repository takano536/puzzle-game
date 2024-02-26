#include "TitleScene.hpp"

#include <SDL_opengl.h>

/**
 * @brief コンストラクタ
 */
TitleScene::TitleScene(IOnChangedListener *listener, const Parameter &param)
    : AbstractScene(listener, param) {
}

/**
 * @brief 更新
 */
void TitleScene::update() {
}

/**
 * @brief 描画
 * @param renderer レンダラー
 */
void TitleScene::draw(SDL_Renderer *renderer) const {
    SDL_RenderClear(renderer);
}

/**
 * @brief シーン変更時の処理
 * @param listener シーン変更リスナー
 */
void TitleScene::on_changed(const IOnChangedListener *listener) {
}

/**
 * @brief パラメータの設定
 * @param param パラメータ
 */
void TitleScene::set_param(const Parameter param) {
}