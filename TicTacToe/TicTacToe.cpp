//
// Created by Viraj P on 5/28/2019.
//

#include "TicTacToe.h"

TicTacToe::TicTacToe(){
    board = new char*[3];
    for(int i = 0;i<3;i++){
        board[i] = new char[3];
    }
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            board[i][j] = Empty;
        }
    }
    xMove = true;
    Game = false;
};

void TicTacToe ::destroy() {
    for(int i = 0;i<3;i++){
        delete[] board[i];
    }
    delete[] board;
}

void TicTacToe :: copy(TicTacToe const &other) {
    board = new char*[3];
    for(int i = 0;i<3;i++){
        board[i] = new char[3];
    }
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            board[i][j] = other.board[i][j];
        }
    }
    Game = other.Game;
    xMove = other.xMove;
}

TicTacToe& TicTacToe ::operator=(const TicTacToe &other) {
    if(&other == this){
        return *this;
    }
    destroy();
    copy(other);
    return *this;
}

TicTacToe :: TicTacToe(TicTacToe &other) {
    copy(other);
}

TicTacToe ::~TicTacToe() {
    destroy();
}

void TicTacToe ::Playinput() {
    string xin;
    string yin;
    bool correct = false;
    int x, y;

    //Get x and y coordinate to place the move in
    do {
        cout << "Enter Row: ";
        cin >> xin;
        cout << "\nEnter Column: ";
        cin >> yin;
        if (isdigit(xin[0]))
            correct = true;
        else
            cout<<"Invalid input try again\n";
    } while (!correct);

    x = stoi(xin);
    y = stoi(yin);

    if(x<0 || y<0 || x>2 || y>2){
     cout<<"Invalid input try again\n";
     Playinput();
     return;
    }

    if(board[x][y] != Empty){
     cout<<"This spot is already filled try again\n";
     Playinput();
     return;
    }

    Play(x,y);
}
void TicTacToe ::Play(int x, int y) {

    //xMove determines if the move is X or O

    if(xMove){
        board[x][y]=X;
        xMove = false;
    }
    else{
        board[x][y]=O;
        xMove = true;
    }
}

void TicTacToe ::Print() {
    char printBoard[3][3];
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == Empty)
                printBoard[i][j] = ' ';
            else if(board[i][j] == X){
                printBoard[i][j] = 'X';
            }
            else
                printBoard[i][j] = 'O';
        }
    }

    cout<<"  0      1      2  \n";
    for(int i = 0;i<3;i++){
        cout<<"      |     |     \n";
        cout<<i<<"  "<<printBoard[i][0]<<"  |  "<<printBoard[i][1]<<"  |  "<<printBoard[i][2]<<"  \n";
        cout<<"      |     |     \n";
        if(i != 2)
            cout<<" -----|-----|-----\n";
    }
}

void TicTacToe ::Win() {
    //3 Rows -> check if there are 3 Os or 3 Xs in each of the rows
    char printBoard[3][3];
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == Empty)
                printBoard[i][j] = ' ';
            else if(board[i][j] == X){
                printBoard[i][j] = 'X';
            }
            else
                printBoard[i][j] = 'O';
        }
    }

    if(printBoard[0][0] == printBoard[0][1] && printBoard[0][0] == printBoard [0][2]){
        if(printBoard[0][0] != 32){
            Game = true;
        }
    }
    else if (printBoard[1][0] == printBoard[1][1] && printBoard[1][0] == printBoard [1][2]){
        if(printBoard[1][0] != 32){
            Game = true;
        }
    }
    else if (printBoard[2][0] == printBoard[2][1] && printBoard[2][0] == printBoard [2][2]){
        if(printBoard[2][0] != 32){
            Game = true;
        }
    }
    //Check all 3 columns
    else if(printBoard[0][0] == printBoard [1][0] && printBoard[0][0] == printBoard[2][0]){
        if(printBoard[0][0] != 32)
            Game = true;
    }
    else if(printBoard[0][1] == printBoard[1][1] && printBoard[0][1] == printBoard [2][1]){
        if(printBoard[0][1] != 32)
            Game = true;
    }
    else if(printBoard[0][2] == printBoard[1][2] && printBoard[0][2] == printBoard[2][2]){
        if(printBoard[0][2] != 32){
            Game = true;
        }
    }
    //Check 2 diagonals
    else if(printBoard[0][0] == printBoard[1][1] && printBoard[0][0] == printBoard[2][2]){
        if(printBoard[0][0] != 32){
            Game = true;
        }
    }
    else if(printBoard[0][2] == printBoard[1][1] && printBoard[0][2] == printBoard[2][0]){
        if(printBoard[0][2] != 32){
            Game = true;
        }
    }
}

bool TicTacToe ::Gamestatus() {
    return Game;
}


void TicTacToe ::copyStateNext(Data &d) {
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            d.nextState[i][j] = board[i][j];
        }
    }
}


void TicTacToe ::copyStateCurrent(Data &d) {
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            d.curentState[i][j] = board[i][j];
        }
    }
}

bool TicTacToe :: isEmpty(int x, int y) {
    char printBoard[3][3];
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == Empty)
                printBoard[i][j] = ' ';
            else if(board[i][j] == X){
                printBoard[i][j] = 'X';
            }
            else
                printBoard[i][j] = 'O';
        }
    }

    if(printBoard[x][y] == ' '){
        return true;
    }
    return false;
}

bool Data ::compareNext(Data& other) {
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(this->nextState[i][j] != other.nextState[i][j])
                return false;
        }
    }
    return true;
}

bool Data ::compareCurrent(Data &other) {
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(this->curentState[i][j] != other.curentState[i][j])
                return false;
        }
    }
    return true;
}

bool Data ::compare(Data &other) {
    if(compareCurrent(other) && compareNext(other))
        return true;
    return false;
}