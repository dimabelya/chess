
#include "game.h"
#include <stdio.h>

void set_legal_moves(Board *board, int row, int col) {
    char type = board->squares[row][col].piece->type;
    char color = board->squares[row][col].piece->color;

    switch (type) {
        case 'P':
            if (color == 'B') {
                // Single move down
                if (row < 7  &&  board->squares[row+1][col].piece == NULL) {
                    board->squares[row + 1][col].legal_move = true;
                }
                // Double move down
                if (board->squares[row][col].piece->moves == 0 &&
                    board->squares[row + 1][col].piece == NULL &&
                    board->squares[row + 2][col].piece == NULL) {
                    board->squares[row + 2][col].legal_move = true;
                }
                // Diagonal capture down left
                if (row < 7  &&  col > 0  &&  board->squares[row+1][col-1].piece != NULL) {
                    if (board->squares[row+1][col-1].piece->color == 'W') {
                        board->squares[row+1][col-1].legal_move = true;
                    }
                }
                // Diagonal capture down right
                if (row < 7  && col < 7  &&  board->squares[row+1][col+1].piece != NULL) {
                    if (board->squares[row+1][col+1].piece->color == 'W') {
                        board->squares[row+1][col+1].legal_move = true;
                    }
                }
            }
            if (color == 'W') {
                // Single move up
                if (row > 0  &&  board->squares[row-1][col].piece == NULL){
                    board->squares[row-1][col].legal_move = true;
                }
                // Double move up
                if (board->squares[row][col].piece->moves == 0 &&
                    board->squares[row-1][col].piece == NULL &&
                    board->squares[row-2][col].piece == NULL) {
                    board->squares[row-2][col].legal_move = true;
                }
                // Diagonal capture up left
                if (row > 0  && col > 0  &&  board->squares[row-1][col-1].piece != NULL) {
                    if (board->squares[row-1][col-1].piece->color == 'B') {
                        board->squares[row-1][col-1].legal_move = true;
                    }
                }
                // Diagonal capture up right
                if (row > 0  &&  col < 7  &&  board->squares[row-1][col+1].piece != NULL) {
                    if (board->squares[row-1][col+1].piece->color == 'B') {
                        board->squares[row-1][col+1].legal_move = true;
                    }
                }
            }
            break;
        case 'R':
            break;
        case 'N':
            break;
        case 'B':
            break;
        case 'Q':
            break;
        case 'K':
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


