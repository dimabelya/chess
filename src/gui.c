
#include "gui.h"


void select_piece(Board *board, int *cur_x, int *cur_y, bool *is_piece_selected) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();
        int dest_x = (mouse_y - EXTRA_HEIGHT/2) / SQUARE_SIZE;  // col of chess board
        int dest_y = (mouse_x - EXTRA_WIDTH/2) / SQUARE_SIZE;   // row of chess board

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
            if (board->squares[dest_x][dest_y].piece == NULL && board->squares[dest_x][dest_y].legal_move) {
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
                    // TODO: adding pieces to CapturedPieces
                    if (board->squares[dest_x][dest_y].piece->color == 'B') {
                        // black is being captured by white
                        printf("Before increment: %d\n", board->captured.white_captured_count);
                        board->captured.white_captured_count += 1;
                        printf("After increment: %d\n", board->captured.white_captured_count);

                        board->captured.white_capture[board->captured.white_captured_count] = board->squares[dest_x][dest_y].piece;
                        display_captured(board);
                        // TODO: check edge cases
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
        float box_x = (float)cur_y * SQUARE_SIZE + (float)EXTRA_WIDTH/2;
        float box_y = (float)cur_x * SQUARE_SIZE + (float)EXTRA_HEIGHT/2;

        Rectangle r = {box_x, box_y, SQUARE_SIZE, SQUARE_SIZE};
        DrawRectangleLinesEx(r, 5, BLUE);


        set_legal_moves(board, cur_x, cur_y);

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (board->squares[row][col].legal_move) {
                    // Top left coordinates of each square
                    float x = (float)col * SQUARE_SIZE + (float)EXTRA_WIDTH/2;
                    float y = (float)row * SQUARE_SIZE + (float)EXTRA_HEIGHT/2;

                    float center_x = x + ((float)SQUARE_SIZE/2);
                    float center_y = y + ((float)SQUARE_SIZE/2);

                    DrawCircle((int)center_x, (int)center_y, 7, BLUE);
                }
            }
        }
    }
}

void display_captured(Board *board) {
    // Display the pieces that white captured
    int white_count = board->captured.white_captured_count;

    // bottom left
    int x = EXTRA_WIDTH/4;
    int y = SCREEN_HEIGHT - EXTRA_HEIGHT/4;
    int spacing = 40;
    DrawCircle(x, y, 10, RED);

    // TODO: for each captured piece draw them ...
    for (int i = 0; i <= white_count; i++) {
        Piece *p = board->captured.white_capture[i];

        if (p != NULL) {
            // Scaled widths and heights of each texture
            float p_width = (float)p->texture.width * SCALE;
            float p_height = (float)p->texture.height * SCALE;

            // Adjust positioons
            float draw_x = x + (i * spacing);
            float draw_y = y - (p_height/2);

            Vector2 v = {draw_x, draw_y};


            if (p->texture.id != 0) {
                DrawTextureEx(p->texture, v, 0.0f, SCALE*0.5, WHITE);
            } else {
                printf("ERROR in texture --------\n");
            }
        }

    }
}