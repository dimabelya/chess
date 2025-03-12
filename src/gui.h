#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include <stdio.h>
#include "raylib.h"
#include "game.h"


void select_piece(Board *board, int *cur_x, int *cur_y, bool *is_piece_selected);
void highlight_square(Board *board, int cur_x, int cur_y, bool is_piece_selected);
void display_captured(Board *board);


#endif //CHESS_GUI_H
