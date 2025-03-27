cmake_minimum_required(VERSION 3.27)
project(chess C)
set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)

add_executable(chess src/main.c
                     src/board.c
                     src/board.h
                     src/gui.c
                     src/gui.h
                     src/game.c
                     src/game.h
                     src/constants.h
                     src/gameplay.c
                     src/gameplay.h )

target_link_libraries(chess raylib)
