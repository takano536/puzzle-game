cmake_minimum_required(VERSION 3.28)
project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

set(SDL2_LIB_DIR $ENV{HOME}/.local/lib)
set(SDL2_INCLUDE_DIR $ENV{HOME}/.local/include)
set(SDL2_LIBRARY $ENV{HOME}/.local/bin)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/Application/Application.cpp
    src/ColorGradator/ColorGradator.cpp
    src/Define/Define.cpp
    src/ErrorHandler/ErrorHandler.cpp
    src/FpsKeeper/FpsKeeper.cpp
    src/InputMonitor/InputMonitor.cpp
    src/Looper/Looper.cpp
    src/Object/Floor/Floor.cpp
    src/Object/Goal/Goal.cpp
    src/Object/Hole/Hole.cpp
    src/Object/ObjectManager/ObjectManager.cpp
    src/Object/Player/Player.cpp
    src/Object/Player/PlayerManager/PlayerManager.cpp
    src/Object/Wall/Wall.cpp
    src/PuzzleGenerator/PuzzleGenerator.cpp
    src/PuzzleSolver/IceFloorPuzzleSolver/IceFloorPuzzleSolver.cpp
    src/PuzzleSolver/SynchronizedPuzzleSolver/SynchronizedPuzzleSolver.cpp
    src/Scene/AbstractScene/AbstractScene.cpp
    src/Scene/GameScene/GameScene.cpp
    src/Scene/Parameter/Parameter.cpp
    src/Scene/TitleScene/TitleScene.cpp
    src/ShapeRenderer/ShapeRenderer.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    SDL2_gfx
)
