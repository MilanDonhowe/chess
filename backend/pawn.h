/*
* Pawn Type
*/
#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
namespace chess {

enum PAWN_STATE {
    FIRST_MOVE,
    MOVED,
    EN_PASSANT
};

class Pawn : public Piece{
private:
    PAWN_STATE state;
public:
    Pawn(int, int, TEAM);
    virtual std::string text() const override {return " p ";};
    virtual Piece_ID id() const override;
    virtual void execute_move(const Move& mv);
    virtual std::vector<Move> generate_moves();
    virtual bool en_passant(){
        return state == EN_PASSANT;
    }
    virtual Piece* clone();

};
}
#endif