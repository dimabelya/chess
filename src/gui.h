#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include "raylib.h"
#include "game.h"
//#include "board.h"
//#include "constants.h"
//#define BOARD_SIZE (SQUARE_SIZE * 8)
//#define EXTRA_WIDTH (SQUARE_SIZE * 4)
//#define EXTRA_HEIGHT (SQUARE_SIZE * 2)

void drag_n_drop(Board *board, int *cur_x, int *cur_y, bool *is_piece_selected);
void highlight_square(Board *board, int cur_x, int cur_y, bool is_piece_selected);



#endif //CHESS_GUI_H
