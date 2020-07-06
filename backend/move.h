/***
Filename: move.h
Author: Milan Donhowe
Date: 6/22/2020
Description: Aggregate type describing a possible board movement.
             The origin is a tuple pair of the location from where some
             arbitrary piece was located and destination the location
             which the arbitrary piece would move.

             The target_piece pointer refers to the piece which would be
             removed if such a movement were executed.  
             
             It is necessary to have the target_piece pointer 
             in addition to the destination tuple 
             since a captured piece may not be where the
             moving piece will end up.
             
             (e.g. "En passant" where a pawn moves behind
             another pawn to capture it)

             Additionally it should make certainly movement "look-ups"
             a little faster (e.g. determining checkmate via linear search).
***/

#ifndef MOVE_H
#define MOVE_H

#include <array>

namespace chess
{

    // forward delcaration so when I declare pointer type
    // g++ doesn't scream @ me"

    class Piece;

    struct Move
    {
    public:
        // row, col
        std::array<int, 2> origin;
        std::array<int, 2> destination;
        std::array<int, 2> target_location;
        bool mustCapture;

        //Piece *target_piece;
        Move(std::array<int, 2> ori, std::array<int, 2> dest):
        origin(ori), destination(dest), target_location(dest){mustCapture = false;};


        Move(std::array<int, 2> ori, std::array<int, 2> dest, std::array<int, 2> target):
        origin(ori), destination(dest), target_location(target){mustCapture = false;};

        Move(std::array<int, 2> ori, std::array<int, 2> dest, bool cap):
        origin(ori), destination(dest), target_location(dest), mustCapture(cap){};



        Move(){
            this->origin = {-1, -1};
            this->destination = {-1, -1};
            this->target_location = destination;
            mustCapture = false;
        }

        Move(const Move& mv){
            this->origin[0] = mv.origin[0];
            this->origin[1] = mv.origin[1];
            this->destination[0] = mv.destination[0];
            this->destination[1] = mv.destination[1];
            this->target_location[0] = mv.target_location[0];
            this->target_location[1] = mv.target_location[1];
            this->mustCapture = mv.mustCapture;
        }
    };

} // namespace chess

#endif