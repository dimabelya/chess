
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"


void get_potential_positions(Board *board, int row, int col, Position *p);
void set_legal_moves(Board *board, int from_row, int from_col);
void reset_legal_moves(Board *board);

Coordinate find_king(Board *board, char color);
bool moving_king_safe(Board *board, int row, int from_col, int to_row, int to_col);
bool is_king_safe(Board *board, int row, int col);
bool check_mate(Board *board, char color);

void perform_move(Board *board, int cur_row, int cur_col, int dest_row, int dest_col);


#endif //CHESS_GAME_H
