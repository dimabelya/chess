#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "raylib.h"


Texture2D piece_textures[12];


Piece *create_piece(char type, char color) {
    Piece *piece = (Piece *) malloc(sizeof(Piece));
    if (!piece) {
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }
    piece->type = type;
    piece->color = color;
    piece->moves = 0;
    return piece;
}


void load_piece_textures() {
    piece_textures[0] = LoadTexture("../assets/images/white-pawn.png");
    piece_textures[1] = LoadTexture("../assets/images/black-pawn.png");
    piece_textures[2] = LoadTexture("../assets/images/white-rook.png");
    piece_textures[3] = LoadTexture("../assets/images/black-rook.png");
    piece_textures[4] = LoadTexture("../assets/images/white-knight.png");
    piece_textures[5] = LoadTexture("../assets/images/black-knight.png");
    piece_textures[6] = LoadTexture("../assets/images/white-bishop.png");
    piece_textures[7] = LoadTexture("../assets/images/black-bishop.png");
    piece_textures[8] = LoadTexture("../assets/images/white-queen.png");
    piece_textures[9] = LoadTexture("../assets/images/black-queen.png");
    piece_textures[10] = LoadTexture("../assets/images/white-king.png");
    piece_textures[11] = LoadTexture("../assets/images/black-king.png");
    for (int i = 0; i < 12; i++) {
        if (piece_textures[i].id == 0) {
            printf("ERROR: loading piece [%d] texture.\n", i);
        }
    }
}


void unload_piece_textures() {
    for (int i = 0; i < 12; i++) {
        UnloadTexture(piece_textures[i]); // Unload each texture
        piece_textures[i].id = 0;
    }
}


void init_captured(Board *board) {
    for (int i = 0; i < 16; i++) {
        board->captured.white_capture[i] = NULL;
        board->captured.black_capture[i] = NULL;
    }
    board->captured.white_captured_count = -1;
    board->captured.black_captured_count = -1;
}


void init_board(Board *board) {
    printf("Initializing board...\n");
    init_captured(board);
    char const first_row[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

    // for each col (left to right)
    for (int i = 0; i < 8; i++) {
        // White (bottom): row 7, row 6
        board->squares[7][i].piece = create_piece(first_row[i], 'W');
        board->squares[6][i].piece = create_piece('P', 'W');

        // Black (top): row 0, row 1
        board->squares[0][i].piece = create_piece(first_row[i], 'B');
        board->squares[1][i].piece = create_piece('P', 'B');

        // Blank space: rows 2 3 4 5
        for (int j = 2; j < 6; j++) {
            board->squares[j][i].piece = NULL;
        }

        // Assign textures
        for (int j = 0; j < 8; j++) {
            Piece *p = board->squares[j][i].piece;
            if (p != NULL) {
                if (p->type == 'P' && p->color == 'W') p->texture = piece_textures[0];
                if (p->type == 'P' && p->color == 'B') p->texture = piece_textures[1];
                if (p->type == 'R' && p->color == 'W') p->texture = piece_textures[2];
                if (p->type == 'R' && p->color == 'B') p->texture = piece_textures[3];
                if (p->type == 'N' && p->color == 'W') p->texture = piece_textures[4];
                if (p->type == 'N' && p->color == 'B') p->texture = piece_textures[5];
                if (p->type == 'B' && p->color == 'W') p->texture = piece_textures[6];
                if (p->type == 'B' && p->color == 'B') p->texture = piece_textures[7];
                if (p->type == 'Q' && p->color == 'W') p->texture = piece_textures[8];
                if (p->type == 'Q' && p->color == 'B') p->texture = piece_textures[9];
                if (p->type == 'K' && p->color == 'W') p->texture = piece_textures[10];
                if (p->type == 'K' && p->color == 'B') p->texture = piece_textures[11];
            }
        }
    }
    printf("Initialization of board done.\n");
}


void free_board(Board *board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].piece) {
                free(board->squares[i][j].piece);
                board->squares[i][j].piece = NULL;
            }
        }
    }
    // Free captured pieces
    for (int i = 0; i < 16; i++) {
        if (board->captured.white_capture[i]) {
            free(board->captured.white_capture[i]);
            board->captured.white_capture[i] = NULL;
        }
        if (board->captured.black_capture[i]) {
            free(board->captured.black_capture[i]);
            board->captured.black_capture[i] = NULL;
        }
    }
    printf("Board memory freed.\n");
}


void print_board(Board *board) {
    // print board: bring last row first..
    for (int i = 0; i < 8; i++) {    // each col (left to right)
        for (int j = 0; j < 8; j++) {  // each row (top to bottom)
            if (board->squares[i][j].piece != NULL) {
                char type = board->squares[i][j].piece->type;
                char color = board->squares[i][j].piece->color;
                printf("%c%c ", color, type);
            } else {
                printf("-- ");
            }
        }
        printf("\n");
    }
}


void draw_board(Board *board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Color square_color;
            if ((row + col) % 2 == 0) {
                square_color = LIGHTGRAY;
            } else {
                square_color = DARKGRAY;
            }
            // Coordinates of top-left of each square
            int x = col * SQUARE_SIZE + EXTRA_WIDTH/2;
            int y = row * SQUARE_SIZE + EXTRA_HEIGHT/2;
            // int x = col * SQUARE_SIZE;
            // int y = row * SQUARE_SIZE;
            DrawRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, square_color);
        }
    }
}


void draw_pieces(Board *board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            Piece *p = board->squares[row][col].piece;
            if (p != NULL) {
                // Top left coordinates of each square
                float x = (float)col * SQUARE_SIZE;
                float y = (float)row * SQUARE_SIZE;

                // Scaled widths and heights of each texture
                float p_width = (float)p->texture.width * SCALE;
                float p_height = (float)p->texture.height * SCALE;

                // Centered coordinates within each square
                float center_x = (SQUARE_SIZE - p_width)/2 + (float)EXTRA_WIDTH/2;
                float center_y = (SQUARE_SIZE - p_height)/2 + (float)EXTRA_HEIGHT/2;

                // Coordinates get shifted for each square
                Vector2 v = (Vector2){x + center_x, y + center_y};

                if (p->texture.id != 0) {
                    DrawTextureEx(p->texture, v, 0.0f, SCALE, WHITE);
                } else {
                    printf("ERROR: Texture not set for piece at [%d][%d]\n", row, col);
                }
            }
        }
    }
}
