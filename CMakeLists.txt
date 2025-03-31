cmake_minimum_required(VERSION 3.27)
project(chess C)
set(CMAKE_C_STANDARD 11)


set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")


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
