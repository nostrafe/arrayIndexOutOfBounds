#include <iostream>
#include <string>
#include "battleship.h"
using namespace std;

const int empty    = 0;
const int full     = 1;
const int missed   = 2;
const int hit      = 3;
const int invalid  = 4;

int Player1[ 10 ][ 10 ];
int Player2[ 10 ][ 10 ]; //temp/unused, can be used for the computer player
int autoBoard1[10][10] = {{1,0,1,0,0,0,0,0,0,0},
                              {1,0,1,0,0,0,0,0,0,0},
                              {1,0,1,0,0,1,0,0,0,0},
                              {1,0,1,0,0,1,0,0,0,0},
                              {1,0,0,0,0,1,0,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0},
                              {1,1,0,0,1,0,0,0,0,0},
                              {0,0,0,0,1,0,0,0,0,0},
                              {0,0,0,0,1,0,0,0,0,0}};
int autoBoard2[10][10] = {{1,0,1,0,0,0,0,0,0,0},
                          {1,0,1,0,0,0,0,0,0,0},
                          {1,0,1,0,0,1,0,0,0,0},
                          {1,0,1,0,0,1,0,0,0,0},
                          {1,0,0,0,0,1,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0},
                          {1,1,0,0,1,0,0,0,0,0},
                          {0,0,0,0,1,0,0,0,0,0},
                          {0,0,0,0,1,0,0,0,0,0}};



int main() {
    int p1Hits = 0;
    int p2Hits = 0;
    printBoard(Player1);
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            attack(x,y,Player1);
        }
    }
    printBoard(Player1);
    return 0;
}