#include "knight.h"

using namespace chess;

Knight::Knight(int row, int col, TEAM side): Piece(row, col, side) {
    return;
}

std::vector<Move> Knight::generate_moves(){
    std::vector<Move> movable_spaces;

    // add all destinations into a vector
    std::vector<std::array<int, 2> > destinations;
    // check northern moves
    add_knight_moves(-2, 1, destinations);
    // check southern moves
    add_knight_moves(2, 1, destinations);
    // add eastern moves
    add_knight_moves(1, 2, destinations);
    add_knight_moves(-1, 2, destinations);

    // add western moves
    add_knight_moves(1, -2, destinations);
    add_knight_moves(-1, -2, destinations);


    // use destinations to push possible moves onto array
    add_moves_vector(movable_spaces, destinations);

    return movable_spaces;
}


void Knight::add_knight_moves(int row_offset, int col_offset, std::vector<std::array<int, 2> >& d){
    int row = this->location[0];
    int col = this->location[1];

    if (inBounds(row+row_offset)){
        if(inBounds(col-col_offset)){
            d.push_back({{row+row_offset,col-col_offset}});
        }
        if (inBounds(col+col_offset)){
            d.push_back({{row+row_offset, col+col_offset}});
        }
    }
}

Piece_ID Knight::id() const{
    return {KNIGHT, this->side};
}

Piece* Knight::clone(){
    return new Knight(this->location[0], this->location[1], this->side);
};
