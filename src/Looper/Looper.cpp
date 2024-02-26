#include "Looper.hpp"

#include <SDL2/SDL.h>

#include "../Define/Define.hpp"
#include "../Scene/GameScene/GameScene.hpp"
#include "../Scene/TitleScene/TitleScene.hpp"
#include "../Utilities/Macros.h"

/**
 * @brief コンストラクタ
 * @details タイトルシーンをスタックに積む
 */
Looper::Looper() {
    Parameter params;
    scenes.push(std::make_shared<TitleScene>(this, params));
}

/**
 * @brief メインループ
 * @param event SDL_Event
 * @param renderer SDL_Renderer
 * @param surface SDL_Surface
 * @param texture SDL_Texture
 * @param font TTF_Font
 * @return 成功した場合は0, 失敗した場合は-1
 * @details　シーンスタックの一番上のシーンを更新し、描画する
 */
int Looper::loop(const SDL_Event &event, SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) {
    if (scenes.empty()) {
        ERR("Scene stack is empty");
    }

    scenes.top()->update(event);
    scenes.top()->draw(renderer, surface, texture, font);
    fps_keeper.wait();
    SDL_Log("FPS: %f", fps_keeper.get_fps());

    return Define::SUCCESS;
}

/**
 * @brief シーン変更時の処理
 * @param scene_type 変更するシーンの種類
 * @param params 前のシーンから引き継ぐパラメータ
 * @param should_clear_stuck シーンスタックをクリアするかどうか
 */
void Looper::on_changed(const SceneType scene_type, const Parameter &params, const bool should_clear_stuck) {
    if (should_clear_stuck) {
        while (!scenes.empty()) {
            scenes.pop();
        }
    }

    switch (scene_type) {
        case SceneType::Title:
            scenes.push(std::make_shared<TitleScene>(this, params));
            SDL_Log("TitleScene");
            break;
        case SceneType::Game:
            scenes.push(std::make_shared<GameScene>(this, params));
            SDL_Log("GameScene");
            break;
        default:
            ERR("Invalid scene type");
            break;
    }
}