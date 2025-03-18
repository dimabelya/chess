
#include "game.h"
#include <stdio.h>



// refactoring set_legal_positions to get_potential_positions
void get_potential_positions(Board *board, int row, int col, Position *p) {
    char type = board->squares[row][col].piece->type;
    char color = board->squares[row][col].piece->color;

    switch (type) {
        case 'P': {  /*---- KNIGHT ----*/
            // TODO:  * En Passant,  * Promoting

            int direction = (color == 'B') ? 1 : -1;
            int start_row = (color == 'B') ? 1 : 6;

            // Single move forward
            if (board->squares[row + direction][col].piece == NULL) {
                p->positions[row + direction][col] = true;

                // Double move forward
                if (row == start_row  &&  board->squares[row + 2 * direction][col].piece == NULL) {
                    p->positions[row + 2 * direction][col] = true;
                }
            }

            // Diagonal captures
            for (int dc = -1; dc <= 1; dc += 2) { // Check both left (-1) and right (+1)
                int r = row + direction;
                int c = col + dc;

                if (c >= 0 && c <= 7 && r >= 0 && r <= 7) {
                    Piece *target = board->squares[r][c].piece;
                    if (target  &&  target->color != color) {
                        p->positions[r][c] = true;
                    }
                }
            }
        }
            break;
        case 'R': {  /*---- ROOK ----*/

            int directions[4][2] = {
                    {-1,  0},  // Up
                    { 1,  0},  // Down
                    { 0, -1},  // Left
                    { 0,  1}   // Right
            };

            for (int i = 0; i < 4; i++) {  // For all directions
                int r = row, c = col;

                while (true) {
                    r += directions[i][0];
                    c += directions[i][1];
                    if (r < 0 || r > 7 || c < 0 || c > 7) break;

                    // Empty square
                    if (board->squares[r][c].piece == NULL) {
                        p->positions[r][c] = true;
                    }
                    // Capture, stop
                    else if (board->squares[r][c].piece->color != color) {
                        p->positions[r][c] = true;
                        break;
                    }
                    // Same color, stop
                    else break;
                }
            }
        }
            break;
        case 'N': {  /*---- KNIGHT ----*/

            int directions[8][2] = {
                    {-2, -1}, {-2,  1},  // Up-left,   Up-right
                    { 2, -1}, { 2,  1},  // Down-left, Down-right
                    {-1, -2}, { 1, -2},  // Left-up,   Left-down
                    {-1,  2}, { 1,  2}   // Right-up,  Right-down
            };

            for (int i = 0; i < 8; i++) {
                int r = row + directions[i][0];
                int c = col + directions[i][1];

                if (c >= 0 && c <= 7 && r >= 0 && r <= 7) {
                    if (board->squares[r][c].piece == NULL  ||  board->squares[r][c].piece->color != color ) {
                        p->positions[r][c] = true;
                    }
                }
            }
        }
            break;
        case 'B': {  /*---- BISHOP ----*/

            int directions[4][2] = {
                    {-1, -1},  // Up-left
                    {-1,  1},  // Up-right
                    { 1, -1},  // Down-left
                    { 1,  1},  // Down-right
            };

            for (int i = 0; i < 4; i++) {
                int r = row, c = col;

                while (true) {
                    r += directions[i][0];
                    c += directions[i][1];

                    if (r < 0 || r > 7 || c < 0 || c > 7) break;

                    // Empty square
                    if (board->squares[r][c].piece == NULL) {
                        p->positions[r][c] = true;
                    }
                    // Capture, stop
                    else if (board->squares[r][c].piece->color != color) {
                        p->positions[r][c] = true;
                        break;
                    }
                    // Same color, stop
                    else break;
                }
            }
        }
            break;
        case 'Q': {  /*---- QUEEN ----*/

            int directions[8][2] = {
                    {-1,  0},  // Up
                    { 1,  0},  // Down
                    { 0, -1},  // Left
                    { 0,  1},  // Right
                    {-1, -1},  // Up-left
                    {-1,  1},  // Up-right
                    { 1, -1},  // Down-left
                    { 1,  1},  // Down-right
            };

            for (int i = 0; i < 8; i++) {  // For all directions
                int r = row, c = col;

                while (true) {
                    r += directions[i][0];
                    c += directions[i][1];
                    if (r < 0 || r > 7 || c < 0 || c > 7) break;

                    // Empty square
                    if (board->squares[r][c].piece == NULL) {
                        p->positions[r][c] = true;
                    }
                    // Capture, stop
                    else if (board->squares[r][c].piece->color != color) {
                        p->positions[r][c] = true;
                        break;
                    }
                    // Same color, stop
                    else break;
                }
            }
        }
            break;
        case 'K': {  /*---- KING ----*/

            int directions[8][2] = {
                    {-1,  0},  // Up
                    { 1,  0},  // Down
                    { 0, -1},  // Left
                    { 0,  1},  // Right
                    {-1, -1},  // Up-left
                    {-1,  1},  // Up-right
                    { 1, -1},  // Down-left
                    { 1,  1},  // Down-right
            };

            for (int i = 0; i < 8; i++) {
                int r = row + directions[i][0];
                int c = col + directions[i][1];

                if (c >= 0 && c <= 7 && r >= 0 && r <= 7) {
                    if (board->squares[r][c].piece == NULL  ||
                        board->squares[r][c].piece->color != color ) {
                        p->positions[r][c] = true;
                    }
                }
            }
        }
            break;
        default:
            printf("ERROR: get_potential_positions() unable to find piece type.");
            break;
    }
}


void set_legal_moves_2(Board *board, int row, int col) {
    // get_potential_positions(Board *board, int row, int col, bool potential_positions[8][8])
    Position p;
    reset_positions(&p);
    get_potential_positions(board, row, col, &p);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (p.positions[i][j]) {
                board->squares[i][j].legal_move = true;
            }
        }
    }

}


void set_legal_moves(Board *board, int row, int col) {
    char type = board->squares[row][col].piece->type;
    char color = board->squares[row][col].piece->color;

    switch (type) {
        case 'P': {  /*---- KNIGHT ----*/
            // TODO:  * En Passant,  * Promoting

            int direction = (color == 'B') ? 1 : -1;
            int start_row = (color == 'B') ? 1 : 6;

            // Single move forward
            if (board->squares[row + direction][col].piece == NULL) {
                board->squares[row + direction][col].legal_move = true;

                // Double move forward
                if (row == start_row  &&  board->squares[row + 2 * direction][col].piece == NULL) {
                    board->squares[row + 2 * direction][col].legal_move = true;
                }
            }

            // Diagonal captures
            for (int dc = -1; dc <= 1; dc += 2) { // Check both left (-1) and right (+1)
                int r = row + direction;
                int c = col + dc;

                if (c >= 0 && c <= 7 && r >= 0 && r <= 7) {
                    Piece *target = board->squares[r][c].piece;
                    if (target  &&  target->color != color) {
                        board->squares[r][c].legal_move = true;
                    }
                }
            }
        }
        break;
        case 'R': {  /*---- ROOK ----*/

            int directions[4][2] = {
                    {-1,  0},  // Up
                    { 1,  0},  // Down
                    { 0, -1},  // Left
                    { 0,  1}   // Right
            };

            for (int i = 0; i < 4; i++) {  // For all directions
                int r = row, c = col;

                while (true) {
                    r += directions[i][0];
                    c += directions[i][1];
                    if (r < 0 || r > 7 || c < 0 || c > 7) break;

                    // Empty square
                    if (board->squares[r][c].piece == NULL) {
                        board->squares[r][c].legal_move = true;
                    }
                    // Capture, stop
                    else if (board->squares[r][c].piece->color != color) {
                        board->squares[r][c].legal_move = true;
                        break;
                    }
                    // Same color, stop
                    else break;
                }
            }
        }
            break;
        case 'N': {  /*---- KNIGHT ----*/

            int directions[8][2] = {
                    {-2, -1}, {-2,  1},  // Up-left,   Up-right
                    { 2, -1}, { 2,  1},  // Down-left, Down-right
                    {-1, -2}, { 1, -2},  // Left-up,   Left-down
                    {-1,  2}, { 1,  2}   // Right-up,  Right-down
            };

            for (int i = 0; i < 8; i++) {
                int r = row + directions[i][0];
                int c = col + directions[i][1];

                if (c >= 0 && c <= 7 && r >= 0 && r <= 7) {
                    if (board->squares[r][c].piece == NULL  ||  board->squares[r][c].piece->color != color ) {
                        board->squares[r][c].legal_move = true;
                    }
                }
            }
        }
            break;
        case 'B': {  /*---- BISHOP ----*/

            int directions[4][2] = {
                    {-1, -1},  // Up-left
                    {-1,  1},  // Up-right
                    { 1, -1},  // Down-left
                    { 1,  1},  // Down-right
            };

            for (int i = 0; i < 4; i++) {
                int r = row, c = col;

                while (true) {
                    r += directions[i][0];
                    c += directions[i][1];

                    if (r < 0 || r > 7 || c < 0 || c > 7) break;

                    // Empty square
                    if (board->squares[r][c].piece == NULL) {
                        board->squares[r][c].legal_move = true;
                    }
                    // Capture, stop
                    else if (board->squares[r][c].piece->color != color) {
                        board->squares[r][c].legal_move = true;
                        break;
                    }
                    // Same color, stop
                    else break;
                }
            }
        }
            break;
        case 'Q': {  /*---- QUEEN ----*/

            int directions[8][2] = {
                    {-1,  0},  // Up
                    { 1,  0},  // Down
                    { 0, -1},  // Left
                    { 0,  1},  // Right
                    {-1, -1},  // Up-left
                    {-1,  1},  // Up-right
                    { 1, -1},  // Down-left
                    { 1,  1},  // Down-right
            };

            for (int i = 0; i < 8; i++) {  // For all directions
                int r = row, c = col;

                while (true) {
                    r += directions[i][0];
                    c += directions[i][1];
                    if (r < 0 || r > 7 || c < 0 || c > 7) break;

                    // Empty square
                    if (board->squares[r][c].piece == NULL) {
                        board->squares[r][c].legal_move = true;
                    }
                    // Capture, stop
                    else if (board->squares[r][c].piece->color != color) {
                        board->squares[r][c].legal_move = true;
                        break;
                    }
                    // Same color, stop
                    else break;
                }
            }
        }
            break;
        case 'K': {  /*---- KING ----*/

            int directions[8][2] = {
                    {-1,  0},  // Up
                    { 1,  0},  // Down
                    { 0, -1},  // Left
                    { 0,  1},  // Right
                    {-1, -1},  // Up-left
                    {-1,  1},  // Up-right
                    { 1, -1},  // Down-left
                    { 1,  1},  // Down-right
            };

            for (int i = 0; i < 8; i++) {
                int r = row + directions[i][0];
                int c = col + directions[i][1];

                if (c >= 0 && c <= 7 && r >= 0 && r <= 7) {
                    if (board->squares[r][c].piece == NULL  ||
                        board->squares[r][c].piece->color != color ) {
                        // TODO: further check so king can move to safe squares only
                        board->squares[r][c].legal_move = true;


                    }
                }
            }
        }
            break;
        default:
            printf("ERROR: set_legal_moves() unable to find piece type.");
            break;
    }
}


void reset_legal_moves(Board *board) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            board->squares[r][c].legal_move = false;
        }
    }
}


