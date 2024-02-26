cmake_minimum_required(VERSION 3.28)
project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")

set(SDL2_LIB_DIR $ENV{HOME}/.local/lib)
set(SDL2_INCLUDE_DIR $ENV{HOME}/.local/include)
set(SDL2_LIBRARY $ENV{HOME}/.local/bin)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/Application/Application.cpp
    src/Define/Define.cpp
    src/FpsKeeper/FpsKeeper.cpp
    src/InputMonitor/InputMonitor.cpp
    src/Looper/Looper.cpp
    src/Object/Player/Player.cpp
    src/Object/Wall/Wall.cpp
    src/Object/Wall/WallManager/WallManager.cpp
    src/Scene/AbstractScene/AbstractScene.cpp
    src/Scene/GameScene/GameScene.cpp
    src/Scene/Parameter/Parameter.cpp
    src/Scene/TitleScene/TitleScene.cpp
    src/Utilities/ErrorHandler/ErrorHandler.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)
