#include "gameplay.h"
#include "raylib.h"
#include "board.h"
#include "gui.h"
#include "constants.h"

void game() {

    // TODO:  * fix the misaligned selection on the left of the board

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
    load_piece_textures();
    Board board;
    init_board(&board);
    int row, col = -1;
    bool selected = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBROWN);
        draw_board();
        draw_pieces(&board);
        draw_captured(&board);
        draw_turn(&board);
        draw_mate(&board);
        highlight_square(&board, row, col, selected);
        select_piece(&board, &row, &col, &selected);
        EndDrawing();
    }

    unload_piece_textures();
    free_board(&board);
    CloseWindow();
}
