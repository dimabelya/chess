
#include "raylib.h"
#include "board.h"
#include "gui.h"


int main() {
    int screen_width = BOARD_SIZE + EXTRA_WIDTH;
    int screen_height = BOARD_SIZE + EXTRA_HEIGHT;
    InitWindow(screen_width, screen_height, "Chess");

    load_piece_textures();
    Board board;
    init_board(&board);
    print_board(&board);

    // Basic drag-and-drop
    int selected_row = -1, selected_col = -1;
    bool is_piece_selected = false;


    // Main game loop
    while (!WindowShouldClose()) {

        drag_n_drop(&board, &selected_row, &selected_col, &is_piece_selected);

        BeginDrawing();
        draw_board(&board);
        draw_pieces(&board);
        highlight_square(&board, selected_row, selected_col, is_piece_selected);
        EndDrawing();
    }

    unload_piece_textures();
    free_board(&board);
    CloseWindow();
    return 0;
}
