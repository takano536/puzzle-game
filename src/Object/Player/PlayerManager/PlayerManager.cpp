#include "PlayerManager.hpp"

#include "../../../InputMonitor/InputMonitor.hpp"

/**
 * @brief プレイヤーマネージャのコンストラクタ
 */
PlayerManager::PlayerManager(bool is_slip)
    : is_slip(is_slip) {
}

/**
 * @brief プレイヤーの追加
 * @param coord 初期位置座標
 * @param player_size プレイヤーのサイズ
 * @param cell_size グリッドのサイズ
 * @param color プレイヤーの色
 * @param speed 移動速度
 */
void PlayerManager::add(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color) {
    players.push_back(std::make_unique<Player>(coord, player_size, cell_size, color));
}

/**
 * @brief 更新
 */
void PlayerManager::update() {
    if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_r) > 0) {
        for (const auto &Player : players) {
            Player->reset();
        }
        return;
    }

    bool are_stopped_everyone = true;
    for (const auto &Player : players) {
        are_stopped_everyone &= Player->is_stopped();
    }

    bool is_fallen = false;
    for (const auto &Player : players) {
        is_fallen |= Player->update(are_stopped_everyone, is_slip, object_positions) == Define::FAILURE;
    }
    if (is_fallen) {
        for (const auto &Player : players) {
            Player->undo();
        }
    }
}

/**
 * @brief 描画
 * @param renderer レンダラー
 */
void PlayerManager::draw(SDL_Renderer *renderer) const {
    for (const auto &Player : players) {
        Player->draw(renderer);
    }
}

/**
 * @brief オブジェクトの位置情報の設定
 * @param object_positions オブジェクトの位置情報
 */
void PlayerManager::set_object_positions(const std::vector<std::vector<Define::CELL_TYPE>> &object_positions) {
    this->object_positions = object_positions;
}