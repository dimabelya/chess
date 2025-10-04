#ifndef CHESS_GAMEPLAY_H
#define CHESS_GAMEPLAY_H

#include "board.h"
#include "raylib.h"

// TODO: will be used to enable pawn promotion menu
typedef enum {
    MAIN_MENU,
    PAUSED,
    PLAYING,
    PROMOTING,
    GAME_OVER
} GameState;

typedef struct {
    int row;
    int col;
    bool selected;
} Selection;

typedef struct {
    Texture2D white_pawn;
    Texture2D black_pawn;
    Texture2D white_rook;
    Texture2D black_rook;
    Texture2D white_knight;
    Texture2D black_knight;
    Texture2D white_bishop;
    Texture2D black_bishop;
    Texture2D white_queen;
    Texture2D black_queen;
    Texture2D white_king;
    Texture2D black_king;
} GameTextures;

typedef struct {
    Board board;
    GameState gameState;
    Selection selection;
    Coordinate promotion;
    GameTextures textures;
} Game;

void init_game();
void free_game();
void game();


#endif //CHESS_GAMEPLAY_H
