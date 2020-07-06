#include "piece.h"

using namespace chess;

// this probably gonna break lol
Piece::Piece(int row, int col, TEAM s):side(s){
    location[0] = row; location[1] = col;
}

void Piece::add_moves_vector(std::vector<Move>& moves, std::vector<std::array<int, 2> >& dest){
        
    for (auto d : dest){
        // this crazy {{row, col}} works since I am basically passing 
        // a struct to the constructor since std::array is just a struct
        // with an array inside
        Move t_move({{this->location[0], this->location[1]}}, d);
        moves.push_back(t_move);
    }


};

// Updates Piece Location
void Piece::execute_move(const Move& mv){
    this->location[0] = mv.destination[0];
    this->location[1] = mv.destination[1];
}

