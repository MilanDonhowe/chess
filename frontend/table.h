/**
 * filename: table.h
 * author: Milan Donhowe
 * date: 6/28/2020
 * Description:  Header file for GUI component of chess game.
 * Renders board & keep track of players.  Uses SDL 2.0
 **/

#ifndef TABLE_H
#define TABLE_H

#include <cstdlib>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>


/*Header Files to communicate with backend*/
#include "../backend/util.h"
#include "../backend/move.h"
#include "../backend/game.h"
#include <SDL2/SDL.h>


using namespace std;

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

class Table{
private:
    chess::TEAM playerTurn;
    chess::GameControl* CHESS_GAME;
    SDL_Window* win_ptr;
    SDL_Renderer* win_ren;


    // images for each chess piece
    // Type: {White, Black variant}
    unordered_map<chess::Piece_Type, std::array<SDL_Texture*, 2> > chessImages;

    // buffer to hold moves of active piece
    // key: tuple origin
    // value: move struct
    map<array<int, 2>, chess::Move> move_buffer;

    void init_chess_images();
    SDL_Texture* load_image(string);
    void init_sdl();
    void exit_sdl();
    void swap_render_color();
    void normalize(int& y, int& x);
    void handleMouseEvent();


public:
    Table(chess::TEAM, chess::GameControl*);
    void drawLoop();
    void drawCheckerBoard();
    void drawMoveBuffer();
    void drawPieces();
    void mouseEventHandler();
    ~Table();
};







#endif