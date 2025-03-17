#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <stdlib.h>
#include "raylib.h"
#include "constants.h"


typedef struct {
    char type;     // 'P' Pawn, 'R' Rook, 'N' Knight, 'B' Bishop, 'Q' Queen, 'K' King.
    char color;    // 'W' White, 'B' Black.
    int moves;     // for castling and en passant
    Texture2D texture;
} Piece;


typedef struct {
    Piece *white_capture[16];  // Set of black pieces that white captured
    Piece *black_capture[16];  // Set of white pieces that black captured
    int white_captured_count;  // Number of black pieced that white captured
    int black_captured_count;  // Number of white pieces that black captured
} CapturedPieces;


typedef struct {
    Piece *piece;
    bool legal_move;
    bool attacked_by_white;
    bool attacked_by_black;
} Square;


typedef struct {
    Square squares[8][8];
    CapturedPieces captured;
} Board;


void load_piece_textures();
void unload_piece_textures();

void init_board(Board *board);
void free_board(Board *board);

void draw_board(Board *board);
void draw_pieces(Board *board);


#endif