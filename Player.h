#ifndef CPPHOARDING_PLAYER_H
#define CPPHOARDING_PLAYER_H

#include <string>

#include "Rules.h"
//#include "Board.h"
//class Board;

class Player
{
    public:
    
        Player(Rules* rulebook, int startCash, std::string name, int index);
        Player();
    
        
        int currentPosition;
        int newPosition;
        bool isIn;
        bool isInAuction;
        bool hasBet;
        int getCash();
        int getCurrentPosition();
        int getNewPosition();
        int getNetWorth();
        std::string getName();
        void pay(int revenue);
        void charge(int loss);
        void setCurrentPosition(int currentPosition);
        void setNewPosition(int newPosition);
        void increaseNetWorth(int amount);
        void decreaseNetWorth(int amount);
        int getIndex();
        
        int roll;
        
        //Board* board;
        Rules* rulebook;
        
        
    private:
        
        int cash;
        int netWorth;
        std::string name;
        int index;
        
        
};

#endif //CPPHOARDING_PLAYER_H