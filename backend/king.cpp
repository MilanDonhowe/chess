#include "king.h"

using namespace chess;

King::King(int r, int c, TEAM s): Piece(r, c, s) {firstMove = true;};

std::vector<Move> King::generate_moves(){
    std::vector<Move> movable_spaces;
    std::vector<std::array<int, 2> > destinations;

    add_king_move(1, 0, destinations);
    add_king_move(1, 1, destinations);
    add_king_move(1, -1, destinations);
    add_king_move(-1, 0, destinations);
    add_king_move(-1, 1, destinations);
    add_king_move(-1, -1, destinations);
    add_king_move(0, -1, destinations);
    add_king_move(0, 1, destinations);

    add_moves_vector(movable_spaces, destinations);

    /*giga-brain add castling move*/
    if (firstMove){
        Move castle_left(
            {{this->location[0], this->location[1]}}, 
            {{this->location[0], this->location[1]-2}},
            {{this->location[0], 0}},
            CASTLE
            );
        Move castle_right(
            {{this->location[0], this->location[1]}}, 
            {{this->location[0], this->location[1]+2}},
            {{this->location[0], 7}},
            CASTLE
        );
        movable_spaces.push_back(castle_left);
        movable_spaces.push_back(castle_right);
    }

    return movable_spaces;
}

void King::add_king_move(int row_offset, int col_offset, std::vector<std::array<int, 2> >& d){
    int row = this->location[0];
    int col = this->location[1];
    if (inBounds (row+row_offset) && inBounds(col+col_offset)){
        d.push_back({{row+row_offset, col+col_offset}});
    }
}

Piece_ID King::id() const {
    return {KING, this->side};
}

Piece* King::clone(){
    return new King(this->location[0], this->location[1], this->side);
};

void King::execute_move(const Move& mv){
    this->location[0] = mv.destination[0];
    this->location[1] = mv.destination[1];
    if (firstMove) firstMove = false;
}