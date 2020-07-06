/*
* Knight Type
*/
#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

namespace chess {

    class Knight : public Piece {
        public:
            Knight(int, int, TEAM);
            virtual std::string text() const override {return " k ";};
            virtual std::vector<Move> generate_moves();
            void add_knight_moves(int row_offset, int col_offset, std::vector<std::array<int, 2> >& d);
            virtual Piece_ID id() const override;
            virtual Piece* clone();

    };

}
#endif