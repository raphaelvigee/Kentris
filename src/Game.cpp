//
// Created by raphael on 01/03/17.
//

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "Game.h"
#include "Pieces.h"


void Game::setup() {
    delay(1000);
    this->neoMatrix.begin();
    this->neoMatrix.setRotation(1);
    this->neoMatrix.setBrightness(10);
    this->neoMatrix.show();

    this->neoMatrix.fillScreen(0);

    this->neoMatrix.drawLine(1, 6, 5, 6, green);

    this->neoMatrix.show();

    this->createNewPiece();

    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLUMNS; ++x) {
            this->staticBlocks[y][x] = 0;
        }
    }
}

void Game::drawBoard() {
    this->neoMatrix.fillScreen(0);
    this->drawCurrentPiece();
    this->drawStaticBlocks();
    this->neoMatrix.show();
}

void Game::drawCurrentPiece() {
    for (int shapeY = 0; shapeY < 5; ++shapeY) {
        for (int shapeX = 0; shapeX < 5; ++shapeX) {
            int x = this->currentPieceX + shapeX;
            int y = this->currentPieceY + shapeY;

            if(x > COLUMNS - 1 || y > ROWS - 1 || x < 0 || y < 0) {
                continue;
            }

            uint16_t color = Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, shapeX, shapeY);

            if(color != 0) {
                this->neoMatrix.drawPixel(x, y, color);
                // Serial.println("X:"+String(x));
                // Serial.println("Y:"+String(y));
            }
        }
    }
}

void Game::drawStaticBlocks() {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLUMNS; ++x) {
            if(this->staticBlocks[y][x] != 0) {
                this->neoMatrix.drawPixel(x, y, purple);
            }
        }
    }
}

void Game::lost() {
    this->neoMatrix.fillScreen(0);

    this->neoMatrix.drawLine(0, 0, 6, 9, red);
    this->neoMatrix.drawLine(0, 9, 6, 0, red);

    this->neoMatrix.show();
}

void Game::createNewPiece() {
    this->currentPieceKind = (int) random(0, 6);
    this->currentPieceRotation = (int) random(0, 3);

    // Serial.println("Kind:"+String(this->currentPieceKind));
    // Serial.println("Rotation:"+String(this->currentPieceRotation));

    this->currentPieceX = Pieces::GetXInitialPosition(this->currentPieceKind, this->currentPieceRotation);
    this->currentPieceY = Pieces::GetYInitialPosition(this->currentPieceKind, this->currentPieceRotation);
}

void Game::requestDown() {
    if(this->canGo(DIR_DOWN)) {
        this->currentPieceY++;
    }else{
        this->transformToStaticBlock();
        delay(700);
        this->createNewPiece();
    }
}

void Game::requestLeft() {
    if(this->canGo(DIR_LEFT)) {
        this->currentPieceX--;
    }
}

void Game::requestRight() {
    if(this->canGo(DIR_RIGHT)) {
        this->currentPieceX++;
    }
}

void Game::transformToStaticBlock() {
    for (int shapeY = 0; shapeY < 5; ++shapeY) {
        for (int shapeX = 0; shapeX < 5; ++shapeX) {
            int x = this->currentPieceX + shapeX;
            int y = this->currentPieceY + shapeY;

            if(x > COLUMNS - 1 || y > ROWS - 1 || x < 0 || y < 0) {
                continue;
            }

            uint16_t color = Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, shapeX, shapeY);

            if(color != 0) {
                this->staticBlocks[y][x] = color;
            }
        }
    }
}

bool Game::isCurrentPieceClashing() {
    for (int shapeY = 0; shapeY < 5; ++shapeY) {
        for (int shapeX = 0; shapeX < 5; ++shapeX) {
            bool isDefined = true;

            if(Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, shapeX, shapeY) != 0) {
                int x = this->currentPieceX + shapeX;
                int y = this->currentPieceY + shapeY;

                if(x > COLUMNS - 1 || y > ROWS - 1 || x < 0 || y < 0) {
                    isDefined = false;
                }

                if(this->staticBlocks[y][x] != 0 && isDefined) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Game::canGo(int direction) {
    for (int shapeY = 0; shapeY < 5; ++shapeY) {
        for (int shapeX = 0; shapeX < 5; ++shapeX) {
            bool isDefined = true;

            if(Pieces::GetColor(this->currentPieceKind, this->currentPieceRotation, shapeX, shapeY) != 0) {
                int x = this->currentPieceX + shapeX;
                int y = this->currentPieceY + shapeY;

                switch (direction) {
                    case DIR_DOWN:
                        y += 1;
                        if(y > ROWS - 1) {
                            return false;
                        }
                        break;
                    case DIR_LEFT:
                        x -= 1;
                        if(x < 0) {
                            return false;
                        }
                        break;
                    case DIR_RIGHT:
                        x += 1;
                        if(x > COLUMNS - 1) {
                            return false;
                        }
                        break;
                    default:
                        return false;
                }

                if(x > COLUMNS - 1 || y > ROWS - 1 || x < 0 || y < 0) {
                    isDefined = false;
                }

                if(this->staticBlocks[y][x] != 0 && isDefined) {
                    return false;
                }
            }
        }
    }

    return true;
}

uint16_t Game::getStaticBlock(int x, int y) {
    return this->staticBlocks[y][x];
}
