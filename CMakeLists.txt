cmake_minimum_required(VERSION 3.27)
project(chess C)

set(CMAKE_C_STANDARD 11)

# Find raylib ( assumes installed Raylib with Homebrew)
# find_package(raylib REQUIRED)
include_directories("/opt/homebrew/Cellar/raylib/5.5/include")

add_executable(chess src/main.c src/board.c
        src/gui.c
        src/gui.h
        src/game.c
        src/game.h
)

target_link_libraries(chess "/opt/homebrew/Cellar/raylib/5.5/lib/libraylib.5.5.0.dylib")

# Link raylib to your project
# target_link_libraries(chess raylib)
link_directories("/opt/homebrew/Cellar/raylib/5.5/lib")
