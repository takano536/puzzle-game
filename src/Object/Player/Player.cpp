#include "Player.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../InputMonitor/InputMonitor.hpp"
#include "../../ShapeRenderer/ShapeRenderer.hpp"
#include "../../Utilities/Macros.hpp"

const std::map<Define::DIRECTION, std::vector<SDL_KeyCode>> Player::KEY_MAPS = {
    {Define::DIRECTION::UP, {SDLK_w, SDLK_UP}},
    {Define::DIRECTION::RIGHT, {SDLK_d, SDLK_RIGHT}},
    {Define::DIRECTION::DOWN, {SDLK_s, SDLK_DOWN}},
    {Define::DIRECTION::LEFT, {SDLK_a, SDLK_LEFT}},
};
const std::map<Define::DIRECTION, SDL_Point> Player::MOVING_DIRS = {
    {Define::DIRECTION::UP, {0, -1}},
    {Define::DIRECTION::RIGHT, {1, 0}},
    {Define::DIRECTION::DOWN, {0, 1}},
    {Define::DIRECTION::LEFT, {-1, 0}},
};
const int Player::ACCERELATION = 2;
const int Player::VELOCITY = 5;

/**
 * @brief プレイヤーのコンストラクタ
 */
Player::Player(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color)
    : rect({coord.x, coord.y, player_size.x, player_size.y}),
      init_coord(coord),
      prev_coord(coord),
      cell_size(cell_size),
      color(color),
      moving_dir(Define::DIRECTION::NONE),
      dest(coord),
      frame_cnt(0) {
}

/**
 * @brief プレイヤーの更新(オーバーライド)
 */
void Player::update() {
    ERR("This function is not allowed");
}

/**
 * @brief プレイヤーの更新
 * @param object_positions オブジェクトの位置情報
 * @return 移動先が穴だったらDefine::FAILURE, それ以外はDefine::SUCCESS
 */
int Player::update(const bool are_stopped_everyone, const bool is_slip, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions) {
    return is_slip ? move_on_ice(are_stopped_everyone, object_positions) : move(are_stopped_everyone, object_positions);
}

/**
 * @brief プレイヤーの描画
 */
void Player::draw(SDL_Renderer *renderer) const {
    ShapeRenderer::aafilledCircleRGBA(renderer, rect.x + rect.w / 2, rect.y + rect.h / 2, rect.w / 2, color.r, color.g, color.b, color.a);
}

/**
 * @brief プレイヤーのリセット
 */
void Player::reset() {
    rect.x = init_coord.x;
    rect.y = init_coord.y;
    prev_coord = init_coord;
    moving_dir = Define::DIRECTION::NONE;
    dest = init_coord;
}

/**
 * @brief プレイヤーのアンドゥ
 */
void Player::undo() {
    rect.x = prev_coord.x;
    rect.y = prev_coord.y;
    moving_dir = Define::DIRECTION::NONE;
    dest = init_coord;
}

/**
 * @brief プレイヤーの移動
 * @param object_positions オブジェクトの位置情報
 * @return 移動先が穴だったらDefine::FAILURE, それ以外はDefine::SUCCESS
 */
int Player::move(const bool are_stopped_everyone, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions) {
    if (are_stopped_everyone && moving_dir == Define::DIRECTION::NONE) {
        for (const auto &[dir, keys] : KEY_MAPS) {
            for (const auto &key : keys) {
                if (InputMonitor::get_instance().get_pressing_frame_cnt(key) > 0) {
                    moving_dir = dir;
                }
            }
        }
        if (moving_dir == Define::DIRECTION::NONE) {
            return Define::SUCCESS;
        }
        int next_dest_x = rect.x + MOVING_DIRS.at(moving_dir).x * cell_size.x;
        int next_dest_y = rect.y + MOVING_DIRS.at(moving_dir).y * cell_size.y;
        SDL_Point cell_idx = {next_dest_x / cell_size.x, next_dest_y / cell_size.y};
        if (object_positions[cell_idx.y][cell_idx.x] == Define::CELL_TYPE::HOLE) {
            moving_dir = Define::DIRECTION::NONE;
            return Define::FAILURE;
        }
        if (object_positions[cell_idx.y][cell_idx.x] == Define::CELL_TYPE::WALL) {
            moving_dir = Define::DIRECTION::NONE;
            return Define::SUCCESS;
        }
        dest = {next_dest_x, next_dest_y};
    }
    if (moving_dir == Define::DIRECTION::NONE) {
        return Define::SUCCESS;
    }

    prev_coord = {rect.x, rect.y};
    rect.x += MOVING_DIRS.at(moving_dir).x * (VELOCITY + ACCERELATION * frame_cnt);
    rect.y += MOVING_DIRS.at(moving_dir).y * (VELOCITY + ACCERELATION * frame_cnt);
    frame_cnt++;

    switch (moving_dir) {
        case Define::DIRECTION::UP:
            if (rect.y < dest.y) {
                rect.y = dest.y;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        case Define::DIRECTION::RIGHT:
            if (rect.x > dest.x) {
                rect.x = dest.x;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        case Define::DIRECTION::DOWN:
            if (rect.y > dest.y) {
                rect.y = dest.y;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        case Define::DIRECTION::LEFT:
            if (rect.x < dest.x) {
                rect.x = dest.x;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        default:
            ERR("Invalid direction");
    }

    return Define::SUCCESS;
}

/**
 * @brief 氷の床上のプレイヤーの移動
 * @param object_positions オブジェクトの位置情報
 * @return Define::SUCCESS
 */
int Player::move_on_ice(const bool are_stopped_everyone, const std::vector<std::vector<Define::CELL_TYPE>> &object_positions) {
    if (are_stopped_everyone && moving_dir == Define::DIRECTION::NONE) {
        for (const auto &[dir, keys] : KEY_MAPS) {
            for (const auto &key : keys) {
                if (InputMonitor::get_instance().get_pressing_frame_cnt(key) > 0) {
                    moving_dir = dir;
                }
            }
        }
        if (moving_dir == Define::DIRECTION::NONE) {
            return Define::SUCCESS;
        }
        int next_dest_x = rect.x + MOVING_DIRS.at(moving_dir).x * cell_size.x;
        int next_dest_y = rect.y + MOVING_DIRS.at(moving_dir).y * cell_size.y;
        SDL_Point cell_idx = {next_dest_x / cell_size.x, next_dest_y / cell_size.y};
        if (object_positions[cell_idx.y][cell_idx.x] == Define::CELL_TYPE::WALL) {
            moving_dir = Define::DIRECTION::NONE;
            return Define::SUCCESS;
        }
        while (object_positions[cell_idx.y + MOVING_DIRS.at(moving_dir).y][cell_idx.x + MOVING_DIRS.at(moving_dir).x] != Define::CELL_TYPE::WALL) {
            next_dest_x += MOVING_DIRS.at(moving_dir).x * cell_size.x;
            next_dest_y += MOVING_DIRS.at(moving_dir).y * cell_size.y;
            cell_idx = {next_dest_x / cell_size.x, next_dest_y / cell_size.y};
        }
        dest = {next_dest_x, next_dest_y};
    }
    if (moving_dir == Define::DIRECTION::NONE) {
        return Define::SUCCESS;
    }

    prev_coord = {rect.x, rect.y};
    rect.x += MOVING_DIRS.at(moving_dir).x * (VELOCITY + ACCERELATION * frame_cnt);
    rect.y += MOVING_DIRS.at(moving_dir).y * (VELOCITY + ACCERELATION * frame_cnt);
    frame_cnt++;

    switch (moving_dir) {
        case Define::DIRECTION::UP:
            if (rect.y < dest.y) {
                rect.y = dest.y;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        case Define::DIRECTION::RIGHT:
            if (rect.x > dest.x) {
                rect.x = dest.x;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        case Define::DIRECTION::DOWN:
            if (rect.y > dest.y) {
                rect.y = dest.y;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        case Define::DIRECTION::LEFT:
            if (rect.x < dest.x) {
                rect.x = dest.x;
                moving_dir = Define::DIRECTION::NONE;
                prev_coord = dest;
                frame_cnt = 0;
            }
            break;
        default:
            ERR("Invalid direction");
    }

    return Define::SUCCESS;
}

/**
 * @brief プレイヤーが停止しているか
 */
bool Player::is_stopped() const {
    return moving_dir == Define::DIRECTION::NONE;
}
