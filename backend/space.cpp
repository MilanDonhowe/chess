#include "space.h"

using namespace chess;

Space::Space(){
    contained_piece = nullptr;
}

Space::~Space(){
    eliminate_piece();
}

std::string Space::text() const {
    if (contained_piece != nullptr){
        return contained_piece->text();
    }
    return " 0 ";
}

Piece* Space::extract_piece(){
    Piece* pce = this->contained_piece;
    this->contained_piece = nullptr;
    return pce;
}



void Space::operator=(Piece* pce){
    this->eliminate_piece();
    this->contained_piece = pce;
    return;
};

bool Space::isEmpty(){
    return this->contained_piece == nullptr;
}


std::vector<Move> Space::get_moves(){
    if (isEmpty()){
        std::vector<Move> noMoves;
        return noMoves;
    }
    return this->contained_piece->generate_moves();
}

void Space::updatePiece(const Move& mv){
    this->contained_piece->execute_move(mv);
}

Piece_ID Space::query_id() {
    if (this->isEmpty()) return {NO_PIECE, NO_SIDE};
    return this->contained_piece->id();
}


void Space::eliminate_piece(){
    if (this->contained_piece != nullptr){
        delete this->contained_piece;
        this->contained_piece = nullptr;
    }
}


void Space::operator=(const Space& sc){
    if (sc.contained_piece != nullptr)
        this->contained_piece = sc.contained_piece->clone();
    return;
};
