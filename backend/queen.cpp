#include "queen.h"

using namespace chess;

Queen::Queen(int r, int c, TEAM s): Bishop(r, c, s){};

std::vector<Move> Queen::generate_moves(){
    std::vector<Move> movable_spaces;
    std::vector<std::array<int, 2> > destinations;

    
    add_bishop_moves(1, 1, destinations);
    add_bishop_moves(1, -1, destinations);
    add_bishop_moves(-1, 1, destinations);
    add_bishop_moves(-1, -1, destinations);
    add_rook_moves(0, 1, destinations);
    add_rook_moves(0, -1, destinations);
    add_rook_moves(1, 0, destinations);
    add_rook_moves(-1, 0, destinations);

    add_moves_vector(movable_spaces, destinations);

    return movable_spaces;
};

Piece_ID Queen::id() const {
    return {QUEEN, this->side};
};

Piece* Queen::clone(){
    return new Queen(this->location[0], this->location[1], this->side);
};
