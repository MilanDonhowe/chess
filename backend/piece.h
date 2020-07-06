/***
Filename: piece.h
Author: Milan Donhowe
Date: 6/22/2020
Description: Header file for polymorphic "piece" class.  Each piece
functions generally in the same way in terms of determining
possible moves given a board layout.

The variants of this class is where most of the "chess-game"
logic takes place along with some primitive analysis done
by the GameController object.

***/


#ifndef PIECE_H
#define PIECE_H

#include "move.h"
#include "util.h"
#include <vector>
#include <string>

namespace chess
{
    class Piece
    {

    protected:
        bool inBounds(int a) const {
            return (a > -1) && (a < 8);
        };
        
        // row, col
        int location[2];
        TEAM side;


    public:
        Piece(int, int, TEAM);
        virtual ~Piece(){};
        virtual Piece* clone()=0;
        virtual std::string text() const =0;
        virtual Piece_ID id() const =0;
        virtual void execute_move(const Move& mv);
        virtual std::vector<Move> generate_moves() = 0;
        void add_moves_vector(std::vector<Move>&, std::vector<std::array<int, 2> >&);
        virtual bool en_passant(){
            return false;
        };
    };

} // namespace chess

#endif