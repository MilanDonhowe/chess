/*
* Rook Type
*/
#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

namespace chess {

    class Rook : public Piece {
        public:
            Rook(int, int, TEAM);
            virtual std::string text() const override {return " R ";};
            virtual std::vector<Move> generate_moves();
            void add_rook_moves(int, int, std::vector<std::array<int, 2> >&);
            virtual Piece_ID id() const override;
            virtual Piece* clone();

    };

}

#endif