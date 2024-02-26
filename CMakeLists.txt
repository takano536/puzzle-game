cmake_minimum_required(VERSION 3.12)
project(synchronized-puzzle)

set (SDL2_DIR "$ENV{HOME}/.local/lib/cmake/SDL2")
find_package(SDL2 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

include_directories($ENV{HOME}/.local/include/SDL2)
link_directories($ENV{HOME}/.local/lib)

file(GLOB_RECURSE TARGETS *.cpp)

add_executable(
    synchronized-puzzle
    src/main.cpp
    src/Application/Application.cpp
    src/Define/Define.cpp
    src/Looper/Looper.cpp
    src/Scene/AbstractScene/AbstractScene.cpp
    src/Scene/Parameter/Parameter.cpp
    src/Scene/TitleScene/TitleScene.cpp
)

target_include_directories(
    synchronized-puzzle PUBLIC
    ${SDL2_INCLUDE_DIRS} 
)
target_link_libraries(
    synchronized-puzzle
    ${SDL2_LIBRARIES} 
    OpenGL32
)

set (
    RUN_TIME_LIBS
    $ENV{HOME}/.local/bin/SDL2.dll
)
install(FILES ${RUN_TIME_LIBS} DESTINATION ${CMAKE_BINARY_DIR})