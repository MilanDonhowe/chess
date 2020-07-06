#include "rook.h"

using namespace chess;

Rook::Rook(int r, int c, TEAM s): Piece(r, c, s){};

std::vector<Move> Rook::generate_moves(){
    std::vector<Move> movable_spaces;
    std::vector<std::array<int, 2> > destinations;
    add_rook_moves(0, 1, destinations);
    add_rook_moves(0, -1, destinations);
    add_rook_moves(1, 0, destinations);
    add_rook_moves(-1, 0, destinations);
    add_moves_vector(movable_spaces, destinations);
    return movable_spaces;
};

void Rook::add_rook_moves(int row_offset, int col_offset, std::vector<std::array<int, 2> >& d){
    int row = this->location[0];
    int col = this->location[1];
    while (inBounds(row+row_offset) && inBounds(col+col_offset)){
        row += row_offset; col += col_offset;
        d.push_back({{row, col}});
    }
    return;
};

Piece_ID Rook::id() const {
    return {ROOK, this->side};
}

Piece* Rook::clone(){
    return new Rook(this->location[0], this->location[1], this->side);
};
