/*
* Queen type
*/
#ifndef QUEEN_H
#define QUEEN_H
#include "bishop.h"
#include "knight.h"

namespace chess {
    class Queen : public Bishop {
        public:
            Queen(int, int, TEAM);
            virtual std::string text() const override {return " Q ";};
            virtual std::vector<Move> generate_moves() final;
            virtual Piece_ID id() const override;
            virtual Piece* clone();

    };
}

#endif