
#include "game.h"
#include "gui.h"
#include <stdio.h>
#include <string.h>


void get_potential_positions(Board *board, int row, int col, Position *p) {
    const char type = board->squares[row][col].piece->type;
    const char color = board->squares[row][col].piece->color;

    switch (type) {
        case 'P': {  /*---- PAWN ----*/
            // TODO:  * Promoting

            int direction = (color == 'B') ? 1 : -1;
            int start_row = (color == 'B') ? 1 : 6;

            // Single move forward
            if ((row+direction) < 8  &&  (row+direction) >= 0  &&  board->squares[row + direction][col].piece == NULL ) {
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

            // En Passant
            // TODO: does not capture the passed enemy pawn
            if (color == 'W') {
                if (row == 3) {
                    // Check for all black pawns at row 3 that moved once
                    for (int i = 0; i < 8; i++) {
                        if (board->squares[3][i].piece  &&
                            board->squares[3][i].piece->color != color  &&
                            board->squares[3][i].piece->moves == 1  &&
                            board->black_last_move.row == row  &&
                            board->black_last_move.col == i) {

                            p->positions[2][i] = true;
                        }
                    }
                }
            } else {
                if (row == 4) {
                    // Check for all white pawns at row 4 that moved once
                    for (int i = 0; i < 8; i++) {
                        if (board->squares[4][i].piece  &&
                            board->squares[4][i].piece->color != color  &&
                            board->squares[4][i].piece->moves == 1  &&
                            board->white_last_move.row == row  &&
                            board->white_last_move.col == i) {

                            p->positions[5][i] = true;
                        }
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

            // Castling
            // King has not moved and not in check
            if (board->squares[row][col].piece->moves == 0) {
                // Left rook has not moved
                if (board->squares[row][0].piece  &&
                    board->squares[row][0].piece->type == 'R'  &&
                    board->squares[row][0].piece->moves == 0) {

                    // Empty squares between left rook and king
                    if (!board->squares[row][1].piece  &&
                        !board->squares[row][2].piece  &&
                        !board->squares[row][3].piece) {

                        p->positions[row][2] = true;
                    }
                }
                // Right rook has not moved
                if (board->squares[row][7].piece  &&
                    board->squares[row][7].piece->type == 'R'  &&
                    board->squares[row][7].piece->moves == 0) {

                    // Empty squares between king and right rook
                    if (!board->squares[row][5].piece  &&
                        !board->squares[row][6].piece) {

                        p->positions[row][6] = true;
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


Coordinate find_king(Board *board, char color) {
    // Get king location
    int king_row = -1;
    int king_col = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].piece &&
                board->squares[i][j].piece->color == color &&
                board->squares[i][j].piece->type == 'K') {
                king_row = i;
                king_col = j;
            }
        }
    }
    Coordinate c = {king_row, king_col};
    return c;
}


void set_legal_moves(Board *board, int from_row, int from_col) {
    char color = board->squares[from_row][from_col].piece->color;
    Coordinate c = find_king(board, color);
    if (c.row == -1 || c.col == -1 ) { printf("King Gone\n"); return; }

    if (is_king_safe(board, c.row, c.col)) {
        Position p;
        reset_positions(&p);
        get_potential_positions(board, from_row, from_col, &p);

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (p.positions[i][j]) {
                    // Check if moving the piece will check own king
                    // 1. simulate the move
                    Piece *destination = board->squares[i][j].piece;                        // save destination piece
                    board->squares[i][j].piece = board->squares[from_row][from_col].piece;  // move piece over
                    board->squares[from_row][from_col].piece = NULL;                        // erase the piece that was moved

                    // 2a. check if it unchecks king
                    Coordinate c2 = find_king(board, color);  // in case king moved
                    bool safe = is_king_safe(board, c2.row, c2.col);

                    // 2b. set result
                    p.positions[i][j] = safe;

                    // 3. restore the board
                    board->squares[from_row][from_col].piece = board->squares[i][j].piece;  // move the piece back
                    board->squares[i][j].piece = destination;                     // restore the destination


                    if (safe) board->squares[i][j].legal_move = true;
                }
            }
        }
    } else {  // Force king to uncheck -----
        printf("King checked.\n");

        // For all pieces of the same color
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board->squares[i][j].piece && board->squares[i][j].piece->color == color) {
                    // Looking at piece [i][j], save Piece->(Position)legal_positions
                    Position p;
                    reset_positions(&p);
                    get_potential_positions(board, i, j, &p);

                    // For all potential moves, only save the ones that protect the king
                    for (int ii = 0; ii < 8; ii++) {
                        for (int jj = 0; jj < 8; jj++) {
                            if (p.positions[ii][jj]) {

                                // 1. simulate the move
                                Piece *destination = board->squares[ii][jj].piece;          // save destination piece
                                board->squares[ii][jj].piece = board->squares[i][j].piece;  // move piece [i][j] over
                                board->squares[i][j].piece = NULL;                          // erase the piece that was moved

                                // 2a. check if it unchecks king
                                Coordinate c2 = find_king(board, color);
                                bool safe = is_king_safe(board, c2.row, c2.col);

                                // 2b. set result
                                p.positions[ii][jj] = safe;

                                // 3. restore the board
                                board->squares[i][j].piece = board->squares[ii][jj].piece;  // move the piece back
                                board->squares[ii][jj].piece = destination;                     // restore the destination
                            }
                        }
                    }
                    board->squares[i][j].piece->legal_positions = p;  // Save positions that will uncheck the king
                }
            }
        }

        // All safe positions saved, use them to update legal_move of each square
        Position pp = board->squares[from_row][from_col].piece->legal_positions;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (pp.positions[i][j]) {
                    // Default
                    board->squares[i][j].legal_move = true;
                    // Assure king can only move to safe squares
                    if (board->squares[from_row][from_col].piece->type == 'K') {
                        board->squares[i][j].legal_move = moving_king_safe(board, from_row, from_col, i, j);
                    }
                }
            }
        }

        // Remove possible castling positions
        if (board->squares[from_row][from_col].piece->type == 'K') {

            //  (King checked) If king at origin, can't go to castling positions
            if (board->squares[from_row][from_col].piece->moves == 0) {
                board->squares[from_row][1].legal_move = false;
                board->squares[from_row][6].legal_move = false;
            }
        }

        // End of force king to uncheck -----
        bool mate = check_mate(board, color);
        if (mate) { board->mate = mate; }
    }
}


void reset_legal_moves(Board *board) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            board->squares[r][c].legal_move = false;
        }
    }
}


bool moving_king_safe(Board *board, int from_row, int from_col, int to_row, int to_col) {
    bool result = true;

    // Temporarily move the king
    Piece *king = board->squares[from_row][from_col].piece;
    Piece *destination = board->squares[to_row][to_col].piece;
    board->squares[to_row][to_col].piece = king;
    board->squares[from_row][from_col].piece = NULL;

    // For all enemy pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].piece  &&
                board->squares[i][j].piece->color != king->color) {

                Position attacker_ps;
                reset_positions(&attacker_ps);
                get_potential_positions(board, i, j, &attacker_ps);

                if (attacker_ps.positions[to_row][to_col]) {
                    result = false;
                    goto found;
                }
            }
        }
    }
    found:
    // Found at least one enemy piece attacking king's destination
    // Restore the board
    board->squares[from_row][from_col].piece = king;
    board->squares[to_row][to_col].piece = destination;
    return result;
}


bool is_king_safe(Board *board, int row, int col) {
    char king_color = board->squares[row][col].piece->color;

    // For all enemy pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("TEST:  i=%d, j=%d\n", i, j);
            if (board->squares[i][j].piece &&
                board->squares[i][j].piece->color != king_color) {

                Position p;
                reset_positions(&p);
                get_potential_positions(board, i, j, &p);

                if (p.positions[row][col]) return false;
            }
        }
    }
    return true;
}


bool check_mate(Board *board, char color) {
    bool mate = true;

    // For all pieces of the same color
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].piece &&
                board->squares[i][j].piece->color == color) {

                Position p = board->squares[i][j].piece->legal_positions;

                // For all potential moves, only save the ones that protect the king
                for (int ii = 0; ii < 8; ii++) {
                    for (int jj = 0; jj < 8; jj++) {
                        if (p.positions[ii][jj]) {
                            mate = false;
                            goto end;
                        }
                    }
                }
            }
        }
    }
    end:
    return mate;
}


void perform_move(Board *board, int cur_row, int cur_col, int dest_row, int dest_col) {
    char color = board->squares[cur_row][cur_col].piece->color;

    // Unselecting
    if (board->squares[cur_row][cur_col].piece == board->squares[dest_row][dest_col].piece  ||
        !board->squares[dest_row][dest_col].legal_move) {
        reset_legal_moves(board);
    }

    if (board->squares[dest_row][dest_col].legal_move) {

        /*---- Moving to empty square ----*/
        if (board->squares[dest_row][dest_col].piece == NULL) {
            // Handle: Default, Castling, En Passant
            /*---- Castling ----*/
            if (board->squares[cur_row][cur_col].piece &&
                board->squares[cur_row][cur_col].piece->type == 'K' &&
                board->squares[cur_row][cur_col].piece->moves == 0 &&
                (dest_col == cur_col + 2  ||  dest_col == cur_col - 2)) {
                // Left rook castling
                if (board->squares[cur_row][0].piece &&
                    board->squares[cur_row][0].piece->type == 'R' &&
                    dest_row == cur_row && dest_col == 2) {
                    // Move rook over
                    board->squares[dest_row][3].piece = board->squares[cur_row][0].piece;
                    board->squares[cur_row][0].piece = NULL;

                }
                // Right rook castling
                if (board->squares[cur_row][7].piece &&
                    board->squares[cur_row][7].piece->type == 'R' &&
                    dest_row == cur_row && dest_col == 6) {
                    // Move rook over
                    board->squares[dest_row][5].piece = board->squares[cur_row][7].piece;
                    board->squares[cur_row][7].piece = NULL;
                }
                // Move king over
                board->squares[dest_row][dest_col].piece = board->squares[cur_row][cur_col].piece;
                board->squares[cur_row][cur_col].piece = NULL;

                // End of turn (only if move completed)
                reset_legal_moves(board);
                board->squares[dest_row][dest_col].piece->moves += 1;
                board->turn= !board->turn;
                update_last_move(board, color, dest_row, dest_col);
            }

            /*---- Default (Moving to empty square) ----*/
            else {
                // Move piece over
                board->squares[dest_row][dest_col].piece = board->squares[cur_row][cur_col].piece;
                board->squares[cur_row][cur_col].piece = NULL;

                // End of turn (only if move completed)
                reset_legal_moves(board);
                board->squares[dest_row][dest_col].piece->moves += 1;
                board->turn= !board->turn;
                update_last_move(board, color, dest_row, dest_col);
            }
        }

        /*---- Moving to nonempty square ----*/
        else {
            // White capturing black
            if (board->squares[dest_row][dest_col].piece->color == 'B') {
                board->captured.white_captured_count += 1;
                board->captured.white_capture[board->captured.white_captured_count] = board->squares[dest_row][dest_col].piece;
            }
            // Black capturing white
            if (board->squares[dest_row][dest_col].piece->color == 'W') {
                board->captured.black_captured_count += 1;
                board->captured.black_capture[board->captured.black_captured_count] = board->squares[dest_row][dest_col].piece;
            }
            // Complete the move
            board->squares[dest_row][dest_col].piece = board->squares[cur_row][cur_col].piece;
            board->squares[cur_row][cur_col].piece = NULL;

            // End of turn (only if move completed)
            reset_legal_moves(board);
            board->squares[dest_row][dest_col].piece->moves += 1;
            board->turn= !board->turn;
            update_last_move(board, color, dest_row, dest_col);
        }

        /* ----- Promoting ----- */
        // Detect if a promoting happen
        if (board->squares[dest_row][dest_col].piece->type == 'P'  &&
            (dest_row == 0  ||  dest_row == 7)) {

            if (color == 'W') {
                printf("White Promoting\n");
            } else {
                printf("Black Promoting\n");
            }
            draw_promotion(color);

        }

    }
}

