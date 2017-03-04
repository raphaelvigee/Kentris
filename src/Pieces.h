/*****************************************************************************************
/* File: Pieces.h
/* Desc: All the Tetris pieces with their respective rotations and displacements for the hotspot
/*
/* gametuto.com - Javier L�pez L�pez (javilop.com)
/*
/*****************************************************************************************
/*
/* Creative Commons - Attribution 3.0 Unported
/* You are free:
/*	to Share � to copy, distribute and transmit the work
/*	to Remix � to adapt the work
/*
/* Under the following conditions:
/* Attribution. You must attribute the work in the manner specified by the author or licensor 
/* (but not in any way that suggests that they endorse you or your use of the work).
/*
/*****************************************************************************************/

#ifndef _PIECES_
#define _PIECES_

#define PIECE_O 0
#define PIECE_I 1
#define PIECE_L 2
#define PIECE_J 3
#define PIECE_Z 4
#define PIECE_S 5
#define PIECE_T 6

class Pieces {
public:
    static char GetBlockType(int pPiece, int pRotation, int pX, int pY);

    static int GetXInitialPosition(int pPiece, int pRotation);

    static int GetYInitialPosition(int pPiece, int pRotation);

    static uint16_t GetColor(int pPiece, int pRotation, int x, int y);
};

const uint16_t green = Adafruit_NeoMatrix::Color(0, 255, 0);
const uint16_t blue = Adafruit_NeoMatrix::Color(0, 0, 255);
const uint16_t red = Adafruit_NeoMatrix::Color(255, 0, 0);
const uint16_t orange = Adafruit_NeoMatrix::Color(255, 165, 0);
const uint16_t purple = Adafruit_NeoMatrix::Color(255, 0, 255);
const uint16_t yellow = Adafruit_NeoMatrix::Color(255, 255, 0);
const uint16_t cyan = Adafruit_NeoMatrix::Color(0, 255, 255);
const uint16_t white = 0xFFFF;

#endif // _PIECES_
