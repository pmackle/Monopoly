#include <iostream>
#include "Gamestate.h"
//#include "Player.h"
//#include "Rules.h"


Gamestate::Gamestate(Rules& rulebook) : numTurns(0), myRulebook(&rulebook){

}

/*void Gamestate::decreaseNumPlayers(){
    numPlayersLeftInGame--;
}*/

void Gamestate::incrementTurns(){
    numTurns++;
}

int Gamestate::getNumTurns() const{
    return numTurns;
}

void Gamestate::getWinner(std::vector<Player>& players){
    std::cout << "The winners are" << std::endl;

    unsigned int index;
    int maxNetWorth = 0;

    for (index = 0; index < players.size(); index++)
    {
        if (players[index].getNetWorth() > maxNetWorth && players[index].isIn == true)
        {
            maxNetWorth = players[index].getNetWorth();
        }
    }

    for (index = 0; index < players.size(); index++)
    {
        if (players[index].getNetWorth() == maxNetWorth && players[index].isIn == true)
        {
            std::cout << players[index].getName() << std::endl;
        }
    }
}

bool Gamestate::gameIsOver() const{
    if(myRulebook->numPlayersLeftInGame <= myRulebook->getNumPlayersLeft()){
        return true;
    }
    
    else if(numTurns >= myRulebook->getTurnLimit()){
        return true;
    }
    
    else{
        return false;
    }
}

//