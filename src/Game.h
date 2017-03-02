//
// Created by raphael on 01/03/17.
//
#include <Adafruit_NeoMatrix.h>


#ifndef KENTRIS_GAME_H
#define KENTRIS_GAME_H

#define ROWS 10
#define COLUMNS 7


class Game {
private:
    int currentPieceKind, currentPieceRotation;
    uint16_t staticBlocks[ROWS][COLUMNS];
    int currentPieceX, currentPieceY;

public:
    Adafruit_NeoMatrix neoMatrix = Adafruit_NeoMatrix(ROWS, COLUMNS, 6,
                                                      NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                                                      NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                                      NEO_GRB + NEO_KHZ800);
public:
    void drawCurrentPiece();
    void drawStaticBlocks();
    void setup();
    void drawBoard();
    void createNewPiece();
    void requestDown();
    bool canGoDown();
    uint16_t getStaticBlock(int x, int y);
    void transformToStaticBlock();
    void lost();
    bool isCurrentPieceClashing();
};

#endif //KENTRIS_GAME_H