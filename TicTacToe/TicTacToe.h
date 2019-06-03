//
// Created by Viraj P on 5/28/2019.
//

#ifndef TICTACTOE_TICTACTOE_H
#define TICTACTOE_TICTACTOE_H

#include <string>
#include <iostream>
#include <string.h>

using namespace std;
typedef enum {Empty,X,O} board;

struct Data{
    char curentState[3][3];
    char nextState[3][3];
    int wins;
    int totalGames;
    double percent;

    bool compareCurrent(Data& other);
    bool compareNext(Data& other);
    bool compare(Data& other);
};

class TicTacToe {
    char** board;
    bool Game;
    bool xMove;

    /* x = true means that the move places an x if x = false then the move places a o
     * the way it works is that x goes first so x is set to true in the constructor every
     * time play is invoked x is toggled
     */

    void copy(TicTacToe const &other);
    void destroy();

public:

    TicTacToe();
    ~TicTacToe();
    TicTacToe(TicTacToe& other);
    TicTacToe& operator=(const TicTacToe& other);

    bool compareCurrent(Data d);
    bool compareNext(Data d);
    void copyStateNext(Data& d);
    void copyStateCurrent(Data& d);
    void Playinput();
    void Play(int x, int y);
    void Win();
    void Print();
    bool Gamestatus();
    bool isEmpty(int x,int y);
    bool xStatus(){return xMove;}
};


#endif //TICTACTOE_TICTACTOE_H
