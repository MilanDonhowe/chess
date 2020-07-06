/*
* Rook Type
*/
#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

namespace chess {

    class Rook : public Piece {
        private:
            bool firstMove;
        public:
            Rook(int, int, TEAM);
            Rook(int, int, TEAM, bool);
            virtual std::string text() const override {return " R ";};
            virtual std::vector<Move> generate_moves();
            void add_rook_moves(int, int, std::vector<std::array<int, 2> >&);
            virtual Piece_ID id() const override;
            virtual Piece* clone();
            virtual bool castle() override;
            virtual void execute_move(const Move& mv) override;

    };

}

#endif