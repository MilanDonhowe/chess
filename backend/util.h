/***
Filename: util.h
Author: Milan Donhowe
Date: 6/22/2020
Description: Utility file w/ a variety of helper functions and macros.

Also describes some enum types for determining the game state.


***/
// Utility File
#ifndef UTIL_H
#define UTIL_H
#include <array>
#include <unordered_set>

namespace chess {

    class Space;

    enum TEAM {
        WHITE = 0,
        BLACK = 1,
        NO_SIDE = 2
    };
    enum TEAM_STATE {
        NOCHECK = 0, //00000
        WHITE_CHECK = 1, //00001
        WHITE_CHECKMATE = 2, //00010
        BLACK_CHECK = 4, //00100
        BLACK_CHECKMATE = 8 //01000
    };

   

    enum Piece_Type {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        KING,
        QUEEN,
        NO_PIECE
    };

    struct Piece_ID {
        Piece_Type Type;
        TEAM Side;
    };


    const int BOARD_LENGTH = 8;
    
    int operator*(int& num, TEAM& t);

    // sanity saving macro for board type
    typedef std::array< std::array<Space, BOARD_LENGTH>, BOARD_LENGTH> BOARD_T;
}

#endif