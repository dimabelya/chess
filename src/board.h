#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <stdlib.h>
#include "raylib.h"
#include "constants.h"


typedef struct {
    char type;     // 'P' Pawn, 'R' Rook, 'N' Knight, 'B' Bishop, 'Q' Queen, 'K' King.
    char color;    // 'W' White, 'B' Black.
    int moves;     // For castling and en passant
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
} Square;

typedef struct {
    Square squares[8][8];
    CapturedPieces captured;
} Board;

typedef struct {
    bool positions[8][8];
} Position;

Piece *create_piece(char type, char color);
void load_piece_textures();
void unload_piece_textures();
void init_board(Board *board);
void free_board(Board *board);
void reset_positions(Position *p);


#endif