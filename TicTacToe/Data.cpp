//
// Created by Viraj P on 5/28/2019.
//

#include "Data.h"

vector<Data> simulate(){
    TicTacToe simulate;
    vector<Data> DBTable;

    for(int j = 0;j<10;j++){
        simulateRecursion_1(DBTable,simulate);
    }

    for(int i = 0;i<10000;i++){
        simulateRecursion_2(DBTable,simulate);
    }
    return DBTable;
}


/*
 * Create a game
 * go to recursion method
 * create a new tic tac toe game board
 * pick a random move
 * play the move
 * on the new board
 * check if there is an entry in teh database with current state and next state already in
 * based on the random move
 * if so cool call the function again with recursion with the next move and pass the database
 * if the entry is not in the database crate a new Entry with next state == to the new ticktactoe board
 * and then pass into the function
 */

//2 step training first all random moves to adjust win percentages to resonable levels so 1000 times random. next 90,000 times with traversing win percentages

bool simulateRecursion_1(vector<Data>& DBtable, TicTacToe current){
    TicTacToe Next = current; //Create next state
    int x,y;
    bool entry = false;
    int index;

    do{
        x = rand()%3;
        y = rand()%3;
    }while(!Next.isEmpty(x,y));
    Next.Play(x,y); //Pick a random move and play it


    Data moveCurrent;
    current.copyStateCurrent(moveCurrent);
    Next.copyStateNext(moveCurrent);

    //check if there is an entry for the current
    for(int i = 0;i<DBtable.size();i++){
        if(moveCurrent.compare(DBtable[i])){
            entry = true;
            index = i;
            break;
        }
    }

    Next.Win();
    if(Next.Gamestatus()){
        moveCurrent.wins =1;
        moveCurrent.totalGames =1;
        moveCurrent.percent = (moveCurrent.wins*1.0)/(moveCurrent.totalGames*1.0);
        DBtable.push_back(moveCurrent);
        return current.xStatus();
    }

    if(entry){
        if(simulateRecursion_1(DBtable,Next) != current.xStatus())
            DBtable[index].wins += 1;
        DBtable[index].totalGames +=1;
        DBtable[index].percent = (DBtable[index].wins *1.0 / DBtable[index].totalGames *1.0);
    }
    else{
        moveCurrent.wins = 0;
        moveCurrent.totalGames = 0;
        moveCurrent.percent =0;

        /* if the current move was played an X and X wins(by returning xStatus)
         * then adjust the wins and win percentage
         */

        if(simulateRecursion_1(DBtable,Next) == current.xStatus())
            moveCurrent.wins +=1;

        moveCurrent.totalGames +=1;
        moveCurrent.percent = (moveCurrent.wins*1.0)/(moveCurrent.totalGames*1.0);
        DBtable.push_back(moveCurrent);
    }
}


//Find number of configurations with same current state pick try all next configurations see if win adjust as so
bool simulateRecursion_2(vector<Data>& DBtable, TicTacToe current){
    TicTacToe Next = current; //Create next state
    vector<Data> sameState;
    bool ret = false;

    Data moveCurrent;
    current.copyStateCurrent(moveCurrent);
    Next.copyStateNext(moveCurrent);

    for(int i = 0;i<DBtable.size();i++){
        if(DBtable[i].compareCurrent(moveCurrent)){
            sameState.push_back(DBtable[i]);
        }
    }

    for(int index = 0;index<sameState.size();index++){
        // play the move on next
        int x = 0,y = 0;
        for(int i = 0;i<3;i++){
            for(int j = 0;j<3;j++){
                if(sameState[index].nextState[i][j] != sameState[index].curentState[i][j]){
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        Next.Play(x,y);
        Next.Win();
        if(Next.Gamestatus()){
            ret = true;
        }
        else {
            if(simulateRecursion_2(DBtable,Next) == current.xStatus())
                sameState[index].wins += 1;
            sameState[index].totalGames +=1;
            sameState[index].percent = (sameState[index].wins *1.0 / sameState[index].totalGames *1.0);
        }
    }

    for(int i = 0;i<DBtable.size();i++){
        for(int j = 0;j<sameState.size();j++){
            if(DBtable[i].compare(sameState[j])){
                DBtable[i].wins = sameState[j].wins;
                DBtable[i].totalGames = sameState[j].totalGames;
                DBtable[i].percent = sameState[j].percent;
                break;
            }
        }
    }
    if(ret){
        return current.xStatus();
    }

}
