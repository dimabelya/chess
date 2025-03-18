
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"


void set_legal_moves(Board *board, int row, int col);
void reset_legal_moves(Board *board);
void set_legal_moves_2(Board *board, int row, int col);

#endif //CHESS_GAME_H
