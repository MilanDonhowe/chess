#include "bishop.h"

using namespace chess;

Bishop::Bishop(int r, int c, TEAM s): Rook(r, c, s){};

std::vector<Move> Bishop::generate_moves(){
    std::vector<Move> movable_spaces;
    std::vector<std::array<int, 2> > destinations;
    
    // add bishop moves
    add_bishop_moves(1, 1, destinations);
    add_bishop_moves(1, -1, destinations);
    add_bishop_moves(-1, 1, destinations);
    add_bishop_moves(-1, -1, destinations);

    add_moves_vector(movable_spaces, destinations);

    return movable_spaces;
};

void Bishop::add_bishop_moves(int row_offset, int col_offset, std::vector<std::array<int, 2> >& d){
    int row = this->location[0];
    int col = this->location[1];
    while (inBounds(row+row_offset) && inBounds(col+col_offset)){
        row += row_offset;
        col += col_offset;
        d.push_back({{row, col}});
    }
};

Piece_ID Bishop::id() const{
    return {BISHOP, this->side};
};

Piece* Bishop::clone(){
    return new Bishop(this->location[0], this->location[1], this->side);
};
