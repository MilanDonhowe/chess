/***
Filename: space.h
Author: Milan Donhowe
Date: 6/22/2020
Description: Space class headerfile.  Each "space" represents an arbitrary square on the board.
             The space only cares about whether or not it is occupied by a "Piece" object,
             it doesn't even know where it is on the board because it doesn't need to (that's
             only important information for the piece object.)
***/


#ifndef SPACE_H
#define SPACE_H

#include "piece.h"
#include <vector>
#include <string>
#include <iostream>

namespace chess {

class Space {
private:
    Piece* contained_piece;
public:
    Space();
    // extract piece
    Piece* extract_piece();
    bool isEmpty();
    bool en_passant(){
        return (this->isEmpty()) ? false : this->contained_piece->en_passant();
    };
    void operator=(Piece*);
    void operator=(const Space&);
    void updatePiece(const Move&);
    std::vector<Move> get_moves();
    void eliminate_piece();
    Piece_ID query_id();
    std::string text() const;
    ~Space();
};

}

#endif