#include <iostream>
#include "Data.h"
#include <vector>

int main() {
    auto DBtable = new vector<Data>;
    auto miniTable = new vector<Data>;
    auto miniTable2 = new vector<Data>;

    *miniTable = simulate();
    for (int j = 0; j < (*miniTable).size(); j++) {
        bool entry = false;
        for (int k = 0; k < DBtable->size(); k++) {
            if ((*DBtable)[k].compare((*miniTable)[j])) {
                (*DBtable)[k].wins += (*miniTable)[j].wins;
                (*DBtable)[k].totalGames += (*miniTable)[j].totalGames;
                (*DBtable)[k].percent = (*DBtable)[k].wins * 1.0 / (*DBtable)[k].totalGames * 1.0;
                entry = true;
            }
        }
        if (!entry)
            (*DBtable).push_back((*miniTable)[j]);
    }
    delete miniTable;

    TicTacToe game;
    string whichWay;
    bool xFirst;

    while(true){
        cout<<"Type X to go first or O to go second"<<endl;
        cin>>whichWay;
        if(whichWay == "X" || whichWay == "x"){
            cout<<"You go first"<<endl;
            xFirst = true;
            break;
        }
        else if(whichWay == "O" || whichWay == "o"){
            cout<<"You go second"<<endl;
            xFirst = false;
            break;
        }
        else{
            cout<<"Invalid input try again"<<endl;
        }
    }

    while(true){
        if(xFirst){
            game.Print();
            cout<<"Your Move: "<<endl;
            game.Playinput();
            game.Win();
            if(game.Gamestatus()){
                game.Print();
                cout<<"You Win!\n";
                break;
            }
            int x = 0,y = 0;
            // take the current game state compare it to all values in DBtable

            //create a data that is identical to the current state of the game
            Data moveCurrent;
            bool db = false;

            game.copyStateCurrent(moveCurrent);
            for(int i = 0;i<DBtable->size();i++){
                if(moveCurrent.compareCurrent((*DBtable)[i])){
                    if((*DBtable)[i].percent > .50){
                        for(int j = 0;j<3;j++){
                            for(int k=0;k<3;k++){
                                if((*DBtable)[i].curentState[j][k] != (*DBtable)[i].nextState[j][k]){
                                    x = j;
                                    y = k;
                                    if(game.isEmpty(x,y))
                                        db = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if(!db){
                do{
                    x = rand()%3;
                    y = rand()%3;
                }while(!game.isEmpty(x,y));
            }
            game.Print();
            cout<<"CPU Move"<<endl;
            game.Play(x,y);
            game.Win();
            if(game.Gamestatus()){
                game.Print();
                cout<<"CPU Wins!\n";
                break;
            }
        }

        else{
            int x = 0,y = 0;
            // take the current game state compare it to all values in DBtable

            //create a data that is identical to the current state of the game
            Data moveCurrent;
            bool db = false;

            game.copyStateCurrent(moveCurrent);
            for(int i = 0;i<DBtable->size();i++){
                if(moveCurrent.compareCurrent((*DBtable)[i])){
                    if((*DBtable)[i].percent > .50){
                        for(int j = 0;j<3;j++){
                            for(int k=0;k<3;k++){
                                if((*DBtable)[i].curentState[j][k] != (*DBtable)[i].nextState[j][k]){
                                    x = j;
                                    y = k;
                                    if(game.isEmpty(x,y))
                                        db = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if(!db){
                do{
                    x = rand()%3;
                    y = rand()%3;
                }while(!game.isEmpty(x,y));
            }
            cout<<"CPU Move"<<endl;
            game.Play(x,y);
            game.Win();
            if(game.Gamestatus()){
                game.Print();
                cout<<"CPU Wins!\n";
                break;
            }
            game.Print();
            cout<<"Your Move: "<<endl;
            game.Playinput();
            game.Win();
            if(game.Gamestatus()){
                game.Print();
                cout<<"You Win!\n";
                break;
            }
            game.Print();
        }
    }
}
