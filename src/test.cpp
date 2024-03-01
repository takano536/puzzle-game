#include "Define/Define.hpp"
#include "PuzzleGenerator/PuzzleGenerator.hpp"
#include "PuzzleSolver/SynchronizedPuzzleSolver/SynchronizedPuzzleSolver.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <queue>
#include <string>
#include <vector>

int WinMain(int argc, char *argv[]) {
    SDL_Point size = {10, 10};
    std::map<Define::CELL_TYPE, char> cell_marks = {
        {Define::CELL_TYPE::FLOOR, '.'},
        {Define::CELL_TYPE::WALL, '#'},
        {Define::CELL_TYPE::START, 'P'},
        {Define::CELL_TYPE::HOLE, 'o'},
    };
    std::map<Define::DIRECTION, char> direction_marks = {
        {Define::DIRECTION::UP, 'U'},
        {Define::DIRECTION::RIGHT, 'R'},
        {Define::DIRECTION::DOWN, 'D'},
        {Define::DIRECTION::LEFT, 'L'},
    };
    std::string inner_marks = ".......oo#";
    std::string outer_marks = "ooooooooo#";
    std::queue<std::pair<std::pair<int, int>, std::string>> que;
    std::map<std::pair<int, int>, std::string> pathes;
    que.push({{0, 0}, ""});
    pathes[{0, 0}] = "";
    // SynchronizedPuzzleSolver puzzle_solver;
    // puzzle_solver.init(cell_marks);

    // while (puzzle_solver.get_rate() < 20) {
    //     puzzle_solver.reset();
    //     auto puzzle = puzzle_generator.generate();
    //     puzzle_solver.solve(std::move(puzzle));
    // }

    // std::unique_ptr<std::vector<std::string>> puzzle = puzzle_solver.get_puzzle();
    // for (const auto &row : *puzzle) {
    //     std::cout << row << std::endl;
    // }
    // std::cout << puzzle_solver.get_rate() << std::endl;
    // for (const auto &direction : puzzle_solver.get_ans()) {
    //     std::cout << direction_marks.at(direction);
    // }

    return 0;
}