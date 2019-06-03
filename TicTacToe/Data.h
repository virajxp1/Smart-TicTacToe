//
// Created by Viraj P on 5/28/2019.
//

#ifndef TICTACTOE_DATA_H
#define TICTACTOE_DATA_H

#include "TicTacToe.h"
#include <vector>


vector<Data> simulate();

bool simulateRecursion_1(vector<Data>& DBtable, TicTacToe current);
bool simulateRecursion_2(vector<Data>& DBtable, TicTacToe current);


#endif //TICTACTOE_DATA_H
