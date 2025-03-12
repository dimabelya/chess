//
// Created by Belya Dima on 3/11/25.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "board.h"

void set_legal_moves(Board *board, int row, int col);
void reset_legal_moves(Board *board);

#endif //CHESS_GAME_H
