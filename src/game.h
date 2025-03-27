
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"


typedef struct {
    int row;
    int col;
} Coordinate;

void get_potential_positions(Board *board, int row, int col, Position *p);
Coordinate find_king(Board *board, char color);
void set_legal_moves(Board *board, int from_row, int from_col);
void reset_legal_moves(Board *board);
bool moving_king_safe(Board *board, int row, int from_col, int to_row, int to_col);
bool is_king_safe(Board *board, int row, int col);
bool check_mate(Board *board, char color);


#endif //CHESS_GAME_H
