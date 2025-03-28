#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include <stdio.h>
#include "raylib.h"
#include "game.h"


void select_piece(Board *board, int *cur_x, int *cur_y, bool *is_piece_selected);
void highlight_square(Board *board, int cur_x, int cur_y, bool is_piece_selected);

void draw_captured(Board *board);
void draw_board();
void draw_pieces(Board *board);
void draw_turn(Board *board);
void draw_mate(Board *board);


#endif //CHESS_GUI_H
