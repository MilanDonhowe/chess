/*
* Bishop type
*/

#ifndef BISHOP_H
#define BISHOP_H
#include "rook.h"

namespace chess {
    class Bishop : public Rook {
        public:
            Bishop(int, int, TEAM);
            virtual std::string text() const override {return " B ";};
            virtual std::vector<Move> generate_moves();
            void add_bishop_moves(int, int, std::vector<std::array<int, 2> >&);
            virtual Piece_ID id() const override;
            virtual Piece* clone();

    };
}


#endif