//
// Created by Henry on 5/12/2020.
//

#ifndef BATTLESHIPGAME_BATTLESHIP_H
#include <iostream>
#include <string>
#define BATTLESHIPGAME_BATTLESHIP_H

void initializeBoard(int board[10][10]); // function takes a 10 by 10 array and populates it with values
void printBoard(int board[10][10]); // prints a 10 by 10 array formatted as a battleship board
void secretPrintBoard(int board[10][10]); // prints a 10 by 10 array formatted as a battleship board
void gameSetup(int board[10][10]); // sets up player boats on the board
bool legalPlacement(int board[10][10], int x1, int y1, int x2, int y2, int shipSize); // checks to see if a boat is able to be placed
void copyArr(int board1[10][10], int board2[10][10]); // used in gamesetup
void attack(int x, int y, int board[10][10], int * numHit); // "attacks" cords



#endif //BATTLESHIPGAME_BATTLESHIP_H
