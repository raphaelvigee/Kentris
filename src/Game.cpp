//
// Created by raphael on 01/03/17.
//

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "Game.h"
#include "Pieces.h"


void Game::setup() {
    this->neoMatrix.begin();
    this->neoMatrix.setBrightness(10);
    this->neoMatrix.show();

    this->neoMatrix.drawLine(1, 4, 8, 4, red);

    this->neoMatrix.show();

    this->createNewPiece();

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLUMNS; ++c) {
            this->staticBlocks[r][c] = 0;
        }
    }
}

void Game::drawBoard() {
    this->drawCurrentPiece();
    this->drawStaticBlocks();
    this->neoMatrix.show();
}

void Game::drawCurrentPiece() {
    this->neoMatrix.fillScreen(0);

    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            int matrixX = this->currentPieceX + r;
            int matrixY = this->currentPieceY + c;

            uint16_t color = Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, c, r);

            if(color != 0) {
                this->neoMatrix.drawPixel(matrixX, matrixY, color);
            }
        }
    }
}

void Game::drawStaticBlocks() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLUMNS; ++c) {
            if(this->staticBlocks[r][c] != 0) {
                this->neoMatrix.drawPixel(c, r, purple);
            }
        }
    }
}
void Game::lost() {
    this->neoMatrix.drawLine(1, 6, 8, 6, red);
    this->neoMatrix.show();
}

void Game::createNewPiece() {
    this->currentPieceKind = (int) random(0, 6);
    this->currentPieceRotation = (int) random(0, 3);

    this->currentPieceX = Pieces::GetXInitialPosition(this->currentPieceKind, this->currentPieceRotation);
    this->currentPieceY = Pieces::GetYInitialPosition(this->currentPieceKind, this->currentPieceRotation);
}

void Game::requestDown() {
    if(this->canGoDown()) {
        this->currentPieceY++;
    }else{
        this->transformToStaticBlock();
        this->createNewPiece();
    }
}

void Game::transformToStaticBlock() {
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            int x = this->currentPieceX + r;
            int y = this->currentPieceY + c;

            uint16_t color = Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, c, r);

            if(color != 0) {
                this->staticBlocks[y][x] = color;
            }
        }
    }
}

bool Game::isCurrentPieceClashing() {
    bool isClashing = false;
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            if(Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, c, r) != 0) {
                int x = this->currentPieceX + r;
                int y = this->currentPieceY + c;

                if(this->staticBlocks[y][x] != 0) {
                    isClashing = true;
                }
            }
        }
    }

    return isClashing;
}


bool Game::canGoDown() {
    bool canGoDown = true;

    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            if(canGoDown) {
                if(Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, c, r) != 0) {
                    int x = this->currentPieceX + r;
                    int y = this->currentPieceY + c + 1;

                    if(y > COLUMNS - 1) {
                        canGoDown = false;
                    }

                    if(canGoDown && this->staticBlocks[y][x] != 0) {
                        canGoDown = false;
                    }
                }

            }
        }
    }

    return canGoDown;
}

uint16_t Game::getStaticBlock(int x, int y) {
    return this->staticBlocks[y][x];
}
