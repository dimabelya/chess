
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"


void get_potential_positions(Board *board, int row, int col, Position *p);
void set_legal_moves(Board *board, int row, int col);
void reset_legal_moves(Board *board);
bool moving_king_safe(Board *board, int row, int from_col, int to_row, int to_col);
bool is_king_safe(Board *board, int row, int col);
bool is_king_safe_2(Board *board, char king_color);



#endif //CHESS_GAME_H
