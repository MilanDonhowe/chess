/***
Filename: game.h
Author: Milan Donhowe
Date: 6/22/2020
Description: Headerfile for the game controller class.  This is the
            main wrapper object for the "back-end" logic of the 
            chess game.  It predominately focueses on querying
            an internally stored board for possible moves
            and executing requested moves.

            Additionally it will determine if the internal
            board layout represents a "check" or "check-mate"
            scenario.

***/


#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <algorithm>

#include "space.h"
#include "move.h"
#include "util.h"

// add all piece types
#include "king.h"
#include "queen.h"
#include "pawn.h"
#include "rook.h"

namespace chess {

class GameControl {
private:
    
    std::array< std::array<Space, BOARD_LENGTH>, BOARD_LENGTH> board;
    TEAM_STATE game_state;

    bool isMoveLegal(const Move&);
    std::vector<Move> removeIllegalMoves(std::vector<Move>);

public:
    GameControl();
    GameControl(const GameControl&);
    //~GameControl();
    
    template<typename PIECE_TYPE>
    void addPiece(TEAM side, int row, int col){
        this->board[row][col] = new PIECE_TYPE(row, col, side);
    }

    std::vector<Move> validate_moveset(std::vector<Move>, Piece_ID&);
    
    void setupBoard();
    void determine_game_state() const;
    
    bool isCheckMate(TEAM);
    bool isTeamInCheck(TEAM team);
    
    std::vector<Move> get_all_moves(TEAM side);
    std::vector<Move> get_all_legal_moves(TEAM side);

    std::vector<Move> get_moves(int row, int col);
    std::vector<Move> get_legal_moves(int row, int col);

    void perform_move(const Move&);
    Piece_ID query(int row, int col);

    // debugging terminal text representation
    std::string text();
};

}
#endif