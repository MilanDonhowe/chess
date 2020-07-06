/***
Filename: prog.cpp
Author: Milan Donhowe
Date: 6/22/2020
Description: Driver file which connects the front & backend
             to create a functional chess game.
***/

#include <iostream>
#include "./backend/game.h"
#include "./frontend/table.h"

using namespace std;

int main(int argc, char *argv[]){

    cout << "Program Execution has begun" << endl;

    
    chess::GameControl regular_game;
    Table GUI(chess::WHITE, &regular_game);


    cout << "Program Exiting..." << endl;
    return 0;
}
