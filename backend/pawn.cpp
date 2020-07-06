
#include "pawn.h"
#include <iostream>

using namespace chess;

Pawn::Pawn(int row, int col, TEAM side): Piece(row, col, side){
    this->state = FIRST_MOVE;
};


std::vector<Move> Pawn::generate_moves(){
    std::vector<Move> movable_spaces;
    int row = this->location[0];
    int col = this->location[1];

    // Both sides move in different directions    
    int teamDirection = (side == BLACK) ? 1 : -1;

    if (this->state == FIRST_MOVE){
         if (inBounds(row+(2*teamDirection))){
             Move double_jump ({{row, col}}, {{row+(2*teamDirection), col}}, {{-1, -1}});
             movable_spaces.push_back(double_jump);
         }
    }
   
   if (inBounds(row+(1*teamDirection))){

       Move single_jump ({{row, col}}, {{row+(1*teamDirection), col}}, {{-1, -1}});
       movable_spaces.push_back(single_jump);
       /*Add Capture Moves Utilizing Target Piece*/
       if(inBounds(col+1)){
            single_jump.destination = {{row+(1*teamDirection), col+1}};
            single_jump.target_location = single_jump.destination;
            single_jump.mustCapture = true;
            movable_spaces.push_back(single_jump);

            /*ADD EN PASSANT*/
            single_jump.target_location = {{row, col+1}};
            single_jump.mustCapture = false;
            movable_spaces.push_back(single_jump);

       }
       if (inBounds(col-1)){
           single_jump.destination = {{row+(1*teamDirection), col-1}};
           single_jump.target_location = single_jump.destination;
           single_jump.mustCapture = true;
           movable_spaces.push_back(single_jump);

           /*ADD EN PASSANT*/
            single_jump.target_location = {{row, col-1}};
            single_jump.mustCapture = false; //<-- has to be false or will be interpreted
                                             //    as an illegal diagonal pawn move.
            movable_spaces.push_back(single_jump);

       }

   }

    return movable_spaces;
}



Piece_ID Pawn::id() const {
    return {PAWN, this->side};
}


void Pawn::execute_move(const Move& mv){
    this->location[0] = mv.destination[0];
    this->location[1] = mv.destination[1];
    if (state == FIRST_MOVE){
        state = EN_PASSANT;
    } else if (state == EN_PASSANT){
        state = MOVED;
    }
};


Piece* Pawn::clone(){
    return new Pawn(this->location[0], this->location[1], this->side);
};
