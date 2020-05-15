//
// Created by Henry on 5/12/2020.
//
#include "battleship.h"
const std::string shipNames[] = {"Carrier","Battleship","Destroyer", "Submarine", "Patrol Boat"};
const int shipValues[] = {5,4,3,3,2};

void initializeBoard(int board[10][10]){
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            board[x][y] = 0;
        }
    }
}
void printBoard(int board[10][10]){
    std::cout << "  A  B  C  D  E  F  G  H  I  J" << std::endl;
    for(int x = 0; x < 10; x++){
        std::cout << x + 1 << " ";
        for(int y = 0; y < 10; y++){
            std::cout << board[x][y] << "  ";
        }
        std::cout << std::endl;
    }
}
void gameSetup(int board[10][10]){
    int tempBoard[10][10];
    copyArr(board, tempBoard);
    int x1,x2,y1,y2;
    for(int i = 0; i < 5; i++){
        std::cout << "Where would you like to place the front of your " << shipNames[i] << "? (x1,y1)" << std::endl;
        std::cin >> x1;
        std::cin >> y1;
        std::cout << "Where would you like to place the end of your " << shipNames[i] << "? (x2,y2)" << std::endl;
        do{
            std::cin >> x2;
            std::cin >> y2;
        } while(!legalPlacement(board, x1, y1, x2, y2, shipValues[i]));
    }
}
bool legalPlacement(int board[10][10], int x1, int y1, int x2, int y2,  int shipLength){
    if(x1 == x2){
        for(int i = 0; i < y2-y1 ; i++){
            if(board[x1][i] != 0) return false;
        }
    }// up and down
    else if (y1 == y2){
        for(int i = 0; i < x2-x1 ; i++){
            if(board[i][y1] != 0) return false;
        }
    } // side to side
    else{
        std::cout << "Some other error (to be determined)" << std::endl;
        return false;
    }
    return true;
}

void copyArr(int board1[10][10], int board2[10][10]){
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            board2[x][y] = board1[x][y];
        }
    }
}

void attack(int x, int y, int board[10][10], int * numHit){
    int val = board[x][y];
    switch(val){
        case 0:
            board[x][y] = 2;
            std::cout << "Miss!" << std::endl;
            break;
        case 1:
            board[x][y] = 3;
            numHit++;
            std::cout << "Hit!" << std::endl;
            break;
    }
}
void secretPrintBoard(int board[10][10]){
    std::cout << "  A  B  C  D  E  F  G  H  I  J" << std::endl;
    for(int x = 0; x < 10; x++){
        std::cout << x << " ";
        for(int y = 0; y < 10; y++){
            if(board[x][y] != 1) {
                std::cout << board[x][y] << "  ";
            }
            else{
                std::cout << "0  ";
            }
        }
        std::cout << std::endl;
    }
    }