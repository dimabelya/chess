
#include "raylib.h"
#include "board.h"
#include "gui.h"
#include "constants.h"


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

    load_piece_textures();
    Board board;
    init_board(&board);
    print_board(&board);

    // select_piece
    int selected_row = -1, selected_col = -1;
    bool is_piece_selected = false;


    // Main game loop
    while (!WindowShouldClose()) {

        select_piece(&board, &selected_row, &selected_col, &is_piece_selected);

        BeginDrawing();
        ClearBackground(DARKBROWN);

        draw_board(&board);
        draw_pieces(&board);
        display_captured(&board);

        highlight_square(&board, selected_row, selected_col, is_piece_selected);
        EndDrawing();
    }

    unload_piece_textures();
    free_board(&board);
    CloseWindow();
    return 0;
}
