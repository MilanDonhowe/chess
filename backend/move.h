/***
Filename: move.h
Author: Milan Donhowe
Date: 6/22/2020
Description: Aggregate type describing a possible board movement.
             The origin is a tuple pair of the location from where some
             arbitrary piece was located and destination the location
             which the arbitrary piece would move.

             The target_piece pointer refers to the piece whose state
             must be checked for the move to be considered valid.
             
             (e.g. "En passant" where a pawn moves behind
             another pawn after their first move to capture it)

             Additionally it should make certainly movement "look-ups"
             a little faster (e.g. determining checkmate via linear search).
***/

#ifndef MOVE_H
#define MOVE_H

#include <array>

namespace chess
{

    enum SPECIAL_MOVE_FLAG {
        NORMAL_MOVE,
        EN_PASSANT_MOVE,
        PAWN_CAPTURE,
        PAWN_ADVANCE,
        CASTLE  
    };


    struct Move
    {
    public:
        // row, col
        std::array<int, 2> origin;
        std::array<int, 2> destination;
        // need target_location for castling & en_passant
        std::array<int, 2> target_location;

        // move flag ids special moves
        SPECIAL_MOVE_FLAG move_flag;

        Move(std::array<int, 2> ori, std::array<int, 2> dest, SPECIAL_MOVE_FLAG flg):
        origin(ori), destination(dest), target_location(dest), move_flag(flg) {};


        Move(std::array<int, 2> ori, std::array<int, 2> dest, std::array<int, 2> target, SPECIAL_MOVE_FLAG flg):
        origin(ori), destination(dest), target_location(target), move_flag(flg){};

        Move(std::array<int, 2> ori, std::array<int, 2> dest):
        origin(ori), destination(dest), target_location(dest){
            move_flag = NORMAL_MOVE;
        };



        Move(){
            this->origin = {-1, -1};
            this->destination = {-1, -1};
            this->target_location = destination;
            this->move_flag = NORMAL_MOVE;
        }

        Move(const Move& mv){
            this->origin[0] = mv.origin[0];
            this->origin[1] = mv.origin[1];
            this->destination[0] = mv.destination[0];
            this->destination[1] = mv.destination[1];
            this->target_location[0] = mv.target_location[0];
            this->target_location[1] = mv.target_location[1];
            this->move_flag = mv.move_flag;
        }
    };

} // namespace chess

#endif