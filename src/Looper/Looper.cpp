#include "Looper.hpp"

#include <SDL.h>

#include "../Scene/TitleScene/TitleScene.hpp"

/**
 * @brief コンストラクタ
 * @details タイトルシーンをスタックに積む
 */
Looper::Looper() {
    scenes.push(std::make_shared<TitleScene>(this, Parameter()));
}

/**
 * @brief メインループ
 * @param window SDL_Window
 * @param renderer SDL_Renderer
 * @details　シーンスタックの一番上のシーンを更新し、描画する
 */
void Looper::loop(SDL_Window *window, SDL_Renderer *renderer) const {
    if (scenes.empty()) {
        return;
    }
    scenes.top()->update();
    scenes.top()->draw(renderer);
}

/**
 * @brief シーン変更時の処理
 * @param scene_type 変更するシーンの種類
 * @param param 前のシーンから引き継ぐパラメータ
 * @param should_clear_stuck シーンスタックをクリアするかどうか
 */
void Looper::on_changed(const SceneType scene_type, const Parameter &param, const bool should_clear_stuck) {
    if (should_clear_stuck) {
        scenes = std::stack<std::shared_ptr<AbstractScene>>();
    }

    switch (scene_type) {
        case SceneType::Title:
            scenes.push(std::make_shared<TitleScene>(this, param));
            break;
        default:
            break;
    }
}