#include "GameScene.hpp"

#include <algorithm>

#include "../../Define/Define.hpp"
#include "../../InputMonitor/InputMonitor.hpp"
#include "../../PuzzleSolver/IceFloorPuzzleSolver/IceFloorPuzzleSolver.hpp"
#include "../../PuzzleSolver/SynchronizedPuzzleSolver/SynchronizedPuzzleSolver.hpp"
#include "../SceneType.hpp"

const std::string GameScene::PARAM_KEY_LEVEL = "PARAM_KEY_LEVEL";
const std::string GameScene::PARAM_KEY_PUZZLE = "PARAM_KEY_PUZZLE";

const std::map<Define::CELL_TYPE, char> GameScene::CELL_MARKS = {
    {Define::CELL_TYPE::FLOOR, '.'},
    {Define::CELL_TYPE::WALL, '#'},
    {Define::CELL_TYPE::START, 'P'},
    {Define::CELL_TYPE::GOAL, 'G'},
    {Define::CELL_TYPE::HOLE, 'o'},
};

const std::map<Define::CELL_TYPE, SDL_Color> GameScene::OBJECT_COLORS = {
    {Define::CELL_TYPE::WALL, Define::BLACK},
    {Define::CELL_TYPE::START, Define::RED},
    {Define::CELL_TYPE::GOAL, Define::BLUE},
    {Define::CELL_TYPE::HOLE, Define::WHITE},
};

const std::string GameScene::INNER_MARKS =
    std::string(10, CELL_MARKS.at(Define::CELL_TYPE::FLOOR)) +
    std::string(1, CELL_MARKS.at(Define::CELL_TYPE::WALL));
const std::string GameScene::OUTER_MARKS =
    std::string(1, CELL_MARKS.at(Define::CELL_TYPE::WALL));

const int GameScene::START_NUM = 1;

const int GameScene::THRESHOLD = 10;
const SDL_Point GameScene::PUZZLE_SIZE = {9, 17};

const std::map<Define::DIRECTION, int> GameScene::MARGIN = {
    {Define::DIRECTION::UP, 25},
    {Define::DIRECTION::DOWN, 25},
    {Define::DIRECTION::LEFT, 25},
    {Define::DIRECTION::RIGHT, 25},
};

/**
 * @brief コンストラクタ
 * @param listener リスナー
 * @param params パラメータ
 */
GameScene::GameScene(IOnChangedListener *listener, const Parameter &params)
    : AbstractScene(listener, params),
      objects(std::make_unique<ObjectManager>()),
      players(std::make_unique<PlayerManager>(true)),
      puzzle_generator(nullptr),
      puzzle_solver(nullptr) {

    level = params.get(PARAM_KEY_LEVEL);

    puzzle_generator = std::make_unique<PuzzleGenerator>(
        PUZZLE_SIZE,
        INNER_MARKS,
        OUTER_MARKS,
        GameScene::CELL_MARKS.at(Define::CELL_TYPE::START),
        START_NUM
    );
    puzzle_solver = std::make_unique<IceFloorPuzzleSolver>();
    puzzle_solver->init(GameScene::CELL_MARKS);

    int max_step = -1;
    while (puzzle_solver->get_rate() < THRESHOLD) {
        puzzle_solver->reset();
        auto puzzle = puzzle_generator->generate();
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "End of generate");
        for (const auto &str : *puzzle) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", str.c_str());
        }
        puzzle_solver->solve(std::move(puzzle));
        if (max_step < puzzle_solver->get_rate()) {
            max_step = puzzle_solver->get_rate();
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "max_step: %d", max_step);
        }
    }

    this->puzzle = *puzzle_solver->get_puzzle();
    this->ans = puzzle_solver->get_ans();

    SDL_Point goal_coord = puzzle_solver->get_goal();
    puzzle[goal_coord.y][goal_coord.x] = CELL_MARKS.at(Define::CELL_TYPE::GOAL);

    static const int width = Define::WINDOW_SIZE.x - MARGIN.at(Define::DIRECTION::LEFT) - MARGIN.at(Define::DIRECTION::RIGHT);
    static const int height = Define::WINDOW_SIZE.y - MARGIN.at(Define::DIRECTION::UP) - MARGIN.at(Define::DIRECTION::DOWN);
    cell_size = std::min(width / PUZZLE_SIZE.x, height / PUZZLE_SIZE.y);
    upper_left = {MARGIN.at(Define::DIRECTION::LEFT), MARGIN.at(Define::DIRECTION::UP)};

    static const int padding = 1;

    std::vector object_positions(PUZZLE_SIZE.y, std::vector<Define::CELL_TYPE>(PUZZLE_SIZE.x, Define::CELL_TYPE::FLOOR));

    std::array<SDL_Color, 2> floor_colors = {
        SDL_Color(Define::WHITE.r - 50, Define::WHITE.g - 50, Define::WHITE.b - 50, Define::WHITE.a),
        SDL_Color(Define::WHITE.r - 70, Define::WHITE.g - 70, Define::WHITE.b - 70, Define::BLACK.a),
    };

    for (int i = 0; i < PUZZLE_SIZE.y; i++) {
        for (int j = 0; j < PUZZLE_SIZE.x; j++) {
            object_positions[i][j] = std::ranges::find_if(CELL_MARKS, [this, i, j](const auto &cell) { return cell.second == this->puzzle[i][j]; })->first;
            SDL_Point coord = {j * cell_size + upper_left.x, i * cell_size + upper_left.y};
            SDL_Point size = {cell_size, cell_size};
            SDL_Point upper_left_coord = {coord.x + padding, coord.y + padding};
            SDL_Point size_with_padding = {size.x - padding * 2 - 1, size.y - padding * 2 - 1};

            objects->add(Define::CELL_TYPE::FLOOR, coord, size, floor_colors[(i + j) % 2]);
            if (object_positions[i][j] == Define::CELL_TYPE::START) {
                players->add(upper_left_coord, size_with_padding, size, Define::RED);
            } else if (object_positions[i][j] != Define::CELL_TYPE::FLOOR) {
                objects->add(object_positions[i][j], upper_left_coord, size_with_padding, OBJECT_COLORS.at(object_positions[i][j]));
            }
        }
    }
    players->set_object_positions(object_positions);

    for (const auto &vec : object_positions) {
        std::string str;
        for (const auto &cell : vec) {
            str += CELL_MARKS.at(cell);
        }
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", str.c_str());
    }

    const std::map<Define::DIRECTION, char> DIRECTION_CHARS = {
        {Define::DIRECTION::UP, 'U'},
        {Define::DIRECTION::RIGHT, 'R'},
        {Define::DIRECTION::DOWN, 'D'},
        {Define::DIRECTION::LEFT, 'L'},
    };
    std::string ans_str;
    for (const auto &dir : ans) {
        ans_str += DIRECTION_CHARS.at(dir);
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Answer: %s", ans_str.c_str());
}

/**
 * @brief 更新
 */
void GameScene::update() {
    objects->update();
    players->update();

    if (InputMonitor::get_instance().get_pressing_frame_cnt(SDLK_n) == 1) {
        Parameter param;
        param.set(GameScene::PARAM_KEY_LEVEL, level);
        listener->on_changed(SceneType::Game, param, true);
    }
}

/**
 * @brief 描画
 * @param renderer レンダラー
 * @param surface サーフェス
 * @param texture テクスチャ
 * @param font フォント
 */
void GameScene::draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const {
    static_cast<void>(surface), static_cast<void>(texture), static_cast<void>(font);
    objects->draw(renderer);
    players->draw(renderer);
}