#include <iostream>
#include <string>
using namespace std;

const int empty    = 0;
const int full     = 1;
const int missed   = 2;
const int hit      = 3;
const string shipNames[] = {"Carrier","Battleship","Destroyer", "Submarine", "Patrol Boat"};
const int shipValues[] = {5,4,3,3,2};
int Player1[ 10 ][ 10 ];
int Player2[ 10 ][ 10 ];

void initializeBoard(int board[10][10]);
void printBoard(int board[10][10]);
void gameSetup(int board[10][10]);
bool legalPlacement(int board[10][10], int x1, int y1, int x2, int y2, int shipSize);
void copyArr(int board1[10][10], int board2[10][10]);

int main() {
    initializeBoard(Player1);
    printBoard(Player1);
    return 0;
}
void initializeBoard(int board[10][10]){
    for(int x = 0; x < 10; x++){
        for(int y = 0; y < 10; y++){
            board[x][y] = 0;
        }
    }
}
void printBoard(int board[10][10]){
    cout << "  A  B  C  D  E  F  G  H  I  J" << endl;
    for(int x = 0; x < 10; x++){
        cout << x + 1 << " ";
        for(int y = 0; y < 10; y++){
            cout << board[x][y] << "  ";
        }
        cout << endl;
    }
}
void gameSetup(int board[10][10]){
    int tempBoard[10][10];
    copyArr(board, tempBoard);
    int x1,x2,y1,y2;
    for(int i = 0; i < 10; i++){
        cout << "Where would you like to place the front of your " << shipNames[i] << "? (x1,y1)" << endl;
        do{
            cin >> x1 >> y1;
        } while(board[x1][y1] == 0);
        cout << "Where would you like to place the end of your " << shipNames[i] << "? (x2,y2)" << endl;
        do{
            cin >> x2 >> y2;
        } while(legalPlacement(board, x1, y1, x2, y2, shipValues[i]));
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
                cout << "Some other error (to be determined)" << endl;
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
