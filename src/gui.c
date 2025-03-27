
#include "gui.h"


void select_piece(Board *board, int *cur_x, int *cur_y, bool *is_piece_selected) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();
        int dest_x = (mouse_y - EXTRA_HEIGHT/2) / SQUARE_SIZE;  // col of chess board
        int dest_y = (mouse_x - EXTRA_WIDTH/2) / SQUARE_SIZE;   // row of chess board

        if (dest_x < 0 || dest_y < 0 || dest_x > 7 || dest_y >7) return;

        if (*is_piece_selected) {
            // Unselecting
            if (board->squares[*cur_x][*cur_y].piece == board->squares[dest_x][dest_y].piece ||
                !board->squares[dest_x][dest_y].legal_move) {
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
                board->turn= !board->turn;

            } else {  // Moving to nonempty square
                // check if the dest is legal
                if (board->squares[dest_x][dest_y].legal_move == true) {
                    // Add dest piece to players captured set and increment num of captured
                    // White capturing black
                    if (board->squares[dest_x][dest_y].piece->color == 'B') {
                        board->captured.white_captured_count += 1;
                        board->captured.white_capture[board->captured.white_captured_count] = board->squares[dest_x][dest_y].piece;
                    }
                    // Black capturing white
                    if (board->squares[dest_x][dest_y].piece->color == 'W') {
                        board->captured.black_captured_count += 1;
                        board->captured.black_capture[board->captured.black_captured_count] = board->squares[dest_x][dest_y].piece;
                    }
                    // Complete the move: move piece to dest, remove dest, reset things
                    board->squares[dest_x][dest_y].piece = board->squares[*cur_x][*cur_y].piece;
                    board->squares[*cur_x][*cur_y].piece = NULL;
                    *is_piece_selected = false;
                    reset_legal_moves(board);
                    board->squares[dest_x][dest_y].piece->moves += 1;
                    board->turn= !board->turn;
                }
            }
        }
        // If no piece is selected and mouse click on nonempty square
        else if (board->squares[dest_x][dest_y].piece) {
            if ((board->turn && board->squares[dest_x][dest_y].piece->color == 'W') ||
                (!board->turn && board->squares[dest_x][dest_y].piece->color == 'B')) {
                *cur_x = dest_x;
                *cur_y = dest_y;
                *is_piece_selected = true;
            }
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


void draw_captured(Board *board) {
    // Display the pieces that white captured
    int white_count = board->captured.white_captured_count;

    // bottom left
    // int x1 = 0;
    int y1 = SCREEN_HEIGHT - EXTRA_HEIGHT/4;
    // DrawCircle(x1, y1, 5, RED);

    for (int i = 0; i <= white_count; i++) {
        Piece *p = board->captured.white_capture[i];

        if (p != NULL) {
            float p_width = (float)p->texture.width * SCALE;
            float p_height = (float)p->texture.height * SCALE;

            float draw_x = (float)((float)i * p_width * 0.5);
            float draw_y = (float)(y1 - 0.5*(p_height/2));
            Vector2 v = {draw_x, draw_y};

            if (p->texture.id != 0) {
                DrawTextureEx(p->texture, v, 0.0f, SCALE*0.5, WHITE);
            }
        }
    }

    // Display the pieces that black captured
    int black_count = board->captured.black_captured_count;

    // bottom left
    // int x2 = 0;
    int y2 = EXTRA_HEIGHT/4;
    // DrawCircle(x1, y2, 5, RED);

    for (int i = 0; i <= black_count; i++) {
        Piece *p = board->captured.black_capture[i];

        if (p != NULL) {
            float p_width = (float)p->texture.width * SCALE;
            float p_height = (float)p->texture.height * SCALE;

            float draw_x = (float)((float)i * p_width * 0.5);
            float draw_y = (float)(y2 - 0.5*(p_height/2));
            Vector2 v = {draw_x, draw_y};

            if (p->texture.id != 0) {
                DrawTextureEx(p->texture, v, 0.0f, SCALE*0.5, WHITE);
            }
        }

    }
}


void draw_board() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Color square_color;
            if ((row + col) % 2 == 0) {
                square_color = LIGHTGRAY;
            } else {
                square_color = DARKGRAY;
            }
            // Coordinates of top-left of each square
            int x = col * SQUARE_SIZE + EXTRA_WIDTH/2;
            int y = row * SQUARE_SIZE + EXTRA_HEIGHT/2;
            DrawRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, square_color);
        }
    }
}


void draw_pieces(Board *board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            Piece *p = board->squares[row][col].piece;
            if (p != NULL) {
                // Top left coordinates of each square
                float x = (float)col * SQUARE_SIZE;
                float y = (float)row * SQUARE_SIZE;

                // Scaled widths and heights of each texture
                float p_width = (float)p->texture.width * SCALE;
                float p_height = (float)p->texture.height * SCALE;

                // Centered coordinates within each square
                float center_x = (SQUARE_SIZE - p_width)/2 + (float)EXTRA_WIDTH/2;
                float center_y = (SQUARE_SIZE - p_height)/2 + (float)EXTRA_HEIGHT/2;

                // Coordinates get shifted for each square
                Vector2 v = (Vector2){x + center_x, y + center_y};

                if (p->texture.id != 0) {
                    DrawTextureEx(p->texture, v, 0.0f, SCALE, WHITE);
                } else {
                    printf("ERROR: Texture not set for piece at [%d][%d]\n", row, col);
                }
            }
        }
    }
}


void draw_turn(Board *board) {
    int y = SCREEN_HEIGHT/2;
    int x = EXTRA_WIDTH/4;
    int text_width = MeasureText("Turn", 10);

    DrawText("Turn", x-(text_width/2), y-30, 10, BLACK);
    DrawCircle(x, y, 13, GRAY);

    if (board->turn) {
        DrawCircle(x, y, 10, WHITE);
    } else {
        DrawCircle(x, y, 10, BLACK);
    }

}


void draw_mate(Board *board) {
    if (board->mate) {
        // color is for the player that is being mated
        int y = SCREEN_HEIGHT/2;
        int x = SCREEN_WIDTH - (EXTRA_WIDTH/4);
        int text_width = MeasureText("Winner", 10);
        int text2_width = MeasureText("Game Over", 15);

        DrawText("Game Over", x-(text2_width/2), y-50, 15, RED);
        DrawText("Winner", x-(text_width/2), y-30, 10, BLACK);
        DrawCircle(x, y, 13, GRAY);

        // true: white,  false: black
        // so if black's turn, white wins
        if (board->turn == false) {
            DrawCircle(x, y, 10, WHITE);
        } else {
            DrawCircle(x, y, 10, BLACK);
        }
    }
}

