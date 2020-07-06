#include "game.h"

using namespace chess;


GameControl::GameControl(){
    this->game_state = NOCHECK;
    this->setupBoard();
}

/*
[Setup Board]: 
    -> Populates the board matrix with pieces.
      The Game Control object should
      never repopulate the board state,
      instead a new gamecontrol object
      should be allocated if the player
      runs another game.
    
*/
void GameControl::setupBoard(){
    
    // ADD FIRST LINE OF BLACK PIECES
    this->addPiece<Rook>(BLACK, 0, 0);
    this->addPiece<Rook>(BLACK, 0, 7);
    this->addPiece<Knight>(BLACK, 0, 1);
    this->addPiece<Knight>(BLACK, 0, 6);
    this->addPiece<Bishop>(BLACK, 0, 2);
    this->addPiece<Bishop>(BLACK, 0, 5);
    this->addPiece<Queen>(BLACK, 0, 3);
    this->addPiece<King>(BLACK, 0, 4);


    // {ADD PAWNS}
    for (int i=0; i < 8; i++){
        this->addPiece<Pawn>(BLACK, 1, i);
        this->addPiece<Pawn>(WHITE, 6, i);
    }

    // Add first line of white pieces
    this->addPiece<Rook>(WHITE, 7, 0);
    this->addPiece<Rook>(WHITE, 7, 7);
    this->addPiece<Knight>(WHITE, 7, 1);
    this->addPiece<Knight>(WHITE, 7, 6);
    this->addPiece<Bishop>(WHITE, 7, 2);
    this->addPiece<Bishop>(WHITE, 7, 5);
    this->addPiece<Queen>(WHITE, 7, 3);
    this->addPiece<King>(WHITE, 7, 4);

    // Add white pawns
    return;
}

std::string GameControl::text(){
    std::string board_txt = "";
    for (int i=0; i < BOARD_LENGTH; i++){
        for (int j=0; j < BOARD_LENGTH; j++){
            board_txt += board[i][j].text();
        }
        board_txt += "\n";
    }
    return board_txt;
}

/*TODO: add move validator*/
std::vector<Move> GameControl::get_moves(int row, int col){
    //return this->board[row][col].get_moves();

    std::vector<Move> potential_moves = this->board[row][col].get_moves();
    Piece_ID moving_piece = this->board[row][col].query_id();
    return validate_moveset(potential_moves, moving_piece);
}

void GameControl::perform_move(const Move& mv){
    Space& origin_space = this->board[mv.origin[0]][mv.origin[1]];
    Space& destination_space = this->board[mv.destination[0]][mv.destination[1]];
    if(origin_space.isEmpty()){
        std::cout << "Error: Empty Move Origin Detected." << std::endl;
        return;
    }
    // First Update Piece so it knows about it's new location.
    origin_space.updatePiece(mv);
    // Now we take the piece from the origin square
    // (this sets the origin space piece ptr to null)
    Piece* movingPiece = origin_space.extract_piece();
    // And we add the new piece to the destination space
    destination_space = movingPiece;

    /*
    Now we just double check to see if there's a piece
    we need to remove in the case of En Passant
    */
   if (mv.target_location[0] != mv.destination[0] && mv.target_location[0] != -1){
       //std::cout << "removing piece @ " << mv.target_location[0] << ", " << mv.target_location[1] << std::endl;
       this->board[mv.target_location[0]][mv.target_location[1]].eliminate_piece();
   }

}

Piece_ID GameControl::query(int row, int col) {
    if (this->board[row][col].isEmpty()) return {NO_PIECE, NO_SIDE};
    return this->board[row][col].query_id();
}






/*Validate Moves --> basically remove moves that pieces
                     shouldn't be able to make*/
std::vector<Move> GameControl::validate_moveset(std::vector<Move> possible_moves, Piece_ID& moving_piece){
    if (possible_moves.empty()) return possible_moves;
    std::vector<Move> valid_moves;

    /*Collision Check*/
    for (const Move& mv : possible_moves){   
        Piece_ID dest_piece = this->query(mv.destination[0], mv.destination[1]);
        if (dest_piece.Side != moving_piece.Side){
            if (moving_piece.Type != KNIGHT){
                // if illegal move then don't add it to buffer 
                if (!isMoveLegal(mv)){
                    continue;
                }
            }

            // okay I'm def losing brain cells at this point
            // but here is the extra stuff for validating pawn
            // moves since their move set depends on the pieces
            // around them (e.g. diagonal capture, forward movement, en passant).

            // remove illegal advancement moves (for pawns)
            if (mv.target_location[0] == -1 && dest_piece.Side != NO_SIDE){
                continue;
            }
            // remove illegal diagonal pawn moves (where pawn doesn't capture)
            if (dest_piece.Side == NO_SIDE && mv.mustCapture){
                continue;
            }

            // remove illegal en passant
            if (mv.destination[0] != mv.target_location[0] && mv.target_location[0] != -1){
                if (!this->board[mv.target_location[0]][mv.target_location[1]].en_passant()){
                    continue;
                }
            }

            valid_moves.push_back(mv);
        }
    }

    /*Todo: does move result in check?*/
    return valid_moves;
}



/*
isMoveLegal --> Determines if a move is invalid
                if between the origin & destination
                squares there exists a piece.
                This should be called on all
                potential moves except those
                of the knight since the
                knight can actually "hop"
                over surrounding pieces.
*/
bool GameControl::isMoveLegal(const Move& mv){
    int d_row = (mv.destination[0] - mv.origin[0]);
    if (d_row != 0)
        d_row /= abs(mv.destination[0] - mv.origin[0]);
    
    int d_col = (mv.destination[1] - mv.origin[1]);
    if (d_col != 0)
        d_col /= abs(mv.destination[1] - mv.origin[1]);

    int start_row_pos = mv.origin[0];
    int start_col_pos = mv.origin[1];

    while ((start_row_pos+d_row != mv.destination[0]) || (start_col_pos+d_col != mv.destination[1])){
        start_row_pos += d_row; start_col_pos += d_col;

        if (!this->board[start_row_pos][start_col_pos].isEmpty()){
            return false;
        }
    }
    return true;
}



std::vector<Move> GameControl::get_all_moves(TEAM side){
    std::vector<Move> all_team_moves;
    for (int i=0; i < 8; i++){
        for (int j=0; j < 8; j++){
            Piece_ID piece = this->query(i, j);
            if (piece.Side == side){
                std::vector<Move> piece_moves = get_moves(i, j);
                for (auto mv : piece_moves){
                    all_team_moves.push_back(mv);
                }
            }
        }
    }
    return all_team_moves;
};


std::vector<Move> GameControl::get_all_legal_moves(TEAM side){
    std::vector<Move> all_legal_team_moves;
    for (int i=0; i < 8; i++){
        for (int j=0; j < 8; j++){
            Piece_ID piece = this->query(i, j);
            if (piece.Side == side){
                std::vector<Move> piece_moves = get_legal_moves(i, j);
                for (auto mv : piece_moves){
                    all_legal_team_moves.push_back(mv);
                }
            }
        }
    }
    return all_legal_team_moves;
};



bool GameControl::isTeamInCheck(TEAM side){
    TEAM enemy = (side == WHITE) ? BLACK : WHITE;
    std::vector<Move> oppositeTeamMoves = get_all_moves(enemy);
    for (auto mv : oppositeTeamMoves){
        Piece_ID target = query(mv.destination[0], mv.destination[1]);
        if (target.Type == KING && target.Side == side){
            return true;
        }
    }
    return false;
}

std::vector<Move> GameControl::get_legal_moves(int row, int col){
    // Get the all possible pieces
    std::vector<Move> all_moves = get_moves(row, col);
    std::vector<Move> legal_moves;
    Piece_ID moving_piece = query(row, col);

    for (auto mv : all_moves){
        GameControl hypotheticalBoard(*this);
        hypotheticalBoard.perform_move(mv);
        if (!hypotheticalBoard.isTeamInCheck(moving_piece.Side)){
            legal_moves.push_back(mv);
        }
    }

    return legal_moves;
}



bool GameControl::isCheckMate(TEAM s){
    return (isTeamInCheck(s)) && (get_all_legal_moves(s).size() == 0);
}



GameControl::GameControl(const GameControl& old_gc){
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            board[row][col] = old_gc.board[row][col];
        }
    }
    //std::copy(gc.board.begin(), gc.board.end(), board.begin());
}