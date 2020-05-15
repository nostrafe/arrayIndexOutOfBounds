#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
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
    int p1Hits;
    int p2Hits;
    srand(time(0));
    int p1x, p1y; // player 1 attack cords
    int p2x, p2y; // player 2/computer attack cords
    char exitGame = 'n';
    // gameSetup(Player1); //optional for demo
    do {
    p1Hits = 0;
    p2Hits = 0;
    copyArr(autoBoard1, Player1);
    copyArr(autoBoard2, Player2);
    do {
        //player attacks enemy
        cout << "           Enemy Board" << endl;
        secretPrintBoard(Player2);
        cout << "What cords would you like to attack? (x,y):" << endl;
        cin >> p1x;
        cin >> p1y;
        attack(p1x, p1y, Player2, reinterpret_cast<int *>(p1Hits));
        //enemy attacks player
        p2x = rand() % 9;
        p2y = rand() % 9;
        cout << "The computer:" << endl;
        attack(p2x, p2y, Player1, reinterpret_cast<int *>(p2Hits));
        cout << "           Your Board" << endl;
        printBoard(Player1);
    } while ((p1Hits < 17) && (p2Hits < 17));
        if(p2Hits == 17)
            cout << "The computer wins!" << endl;
        else cout << "Player 1 wins!" << endl;

        cout << "Would you like to exit? (y/n):" << endl;
        cin >> exitGame;
} while(exitGame != 'y');

    return 0;
}
