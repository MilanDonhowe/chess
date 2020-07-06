#include "util.h"

using namespace chess;

int operator*(int& num, TEAM& t){
    if (t == WHITE){
        return num * -1;
    }
    return num * 1;
}