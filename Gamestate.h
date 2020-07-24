#ifndef CPPHOARDING_GAMESTATE_H
#define CPPHOARDING_GAMESTATE_H

#include "Player.h"
#include "Rules.h"
#include <vector>

class Gamestate{
    public:
    Gamestate(Rules& rulebook);
        
        //void decreaseNumPlayers();
        void incrementTurns();
        int getNumTurns() const;
        bool gameIsOver() const;
        void getWinner(std::vector<Player>& players);
    
    private:
        //int numPlayersLeftInGame;
        int numTurns;
        Rules* myRulebook;
};

#endif