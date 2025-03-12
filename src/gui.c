
#include "gui.h"


void drag_n_drop(Board *board, int *cur_x, int *cur_y, bool *is_piece_selected) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();
        int dest_x = mouse_y/SQUARE_SIZE;  // for some reason this works...
        int dest_y = mouse_x/SQUARE_SIZE;


        if (dest_x < 0 || dest_y < 0 || dest_x > 7 || dest_y >7) {
            return;
        }

        if (*is_piece_selected) {
            // Unselecting
            if (board->squares[dest_x][dest_y].piece == board->squares[*cur_x][*cur_y].piece) {
                *is_piece_selected = false;
                reset_legal_moves(board);
            }
            // Moving to empty square
            if (board->squares[dest_x][dest_y].piece == NULL) {
                board->squares[dest_x][dest_y].piece = board->squares[*cur_x][*cur_y].piece;
                board->squares[*cur_x][*cur_y].piece = NULL;
                *is_piece_selected = false;
                reset_legal_moves(board);
                board->squares[dest_x][dest_y].piece->moves += 1;
            }
            // Moving to nonempty square
            else {
                // check if the dest is legal
                if (board->squares[dest_x][dest_y].legal_move == true) {
                    // Add dest piece to players captured set
                    // who is getting captured??
                    if (board->squares[dest_x][dest_y].piece->color == 'B') {

                    }
                    board->squares[dest_x][dest_y].piece = board->squares[*cur_x][*cur_y].piece;
                    board->squares[*cur_x][*cur_y].piece = NULL;
                    *is_piece_selected = false;
                    reset_legal_moves(board);
                    board->squares[dest_x][dest_y].piece->moves += 1;
                }
            }
        }
        // If no piece is selected and mouse click on nonempty square
        else if (board->squares[dest_x][dest_y].piece != NULL) {
            *cur_x = dest_x;
            *cur_y = dest_y;
            *is_piece_selected = true;
        }
    }
}


void highlight_square(Board *board, int cur_x, int cur_y, bool is_piece_selected) {
    if (is_piece_selected) {
        float box_x = (float)cur_y * SQUARE_SIZE;
        float box_y = (float)cur_x * SQUARE_SIZE;
        Rectangle r = {box_x, box_y, SQUARE_SIZE, SQUARE_SIZE};
        DrawRectangleLinesEx(r, 5, BLUE);

        set_legal_moves(board, cur_x, cur_y);

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (board->squares[row][col].legal_move) {
                    // Top left coordinates of each square
                    float x = (float)col * SQUARE_SIZE;
                    float y = (float)row * SQUARE_SIZE;
                    float center_x = x + ((float)SQUARE_SIZE/2);
                    float center_y = y + ((float)SQUARE_SIZE/2);

                    DrawCircle((int)center_x, (int)center_y, 7, BLUE);
                }
            }
        }

    }
}