#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include "raylib.h"
#include "board.h"
#include "game.h"

void drag_n_drop(Board *board, int *cur_x, int *cur_y, bool *is_piece_selected);
void highlight_square(Board *board, int cur_x, int cur_y, bool is_piece_selected);



#endif //CHESS_GUI_H
