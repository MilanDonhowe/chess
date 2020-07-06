/*
* King type
*/
#ifndef KING_H
#define KING_H

#include "piece.h"

namespace chess {

    class King : public Piece {
        private:
            bool firstMove;
        public:
            King(int r, int c, TEAM s);
            virtual std::string text() const override {return " K ";};
            virtual std::vector<Move> generate_moves();
            void add_king_move(int row_offset, int col_offset, std::vector<std::array<int, 2> >& d);
            virtual Piece_ID id() const override;
            virtual Piece* clone();
            virtual void execute_move(const Move&) override;
    };


}



#endif