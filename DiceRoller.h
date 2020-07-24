#ifndef CPPHOARDING_DICEROLLER_H
#define CPPHOARDING_DICEROLLER_H

#include <fstream>
#include <string>

class DiceRoller
{
    public:
    
        DiceRoller(std::string randomNumsFile);
        
        int rollDice();
        
        int roll1, roll2;
        
        virtual ~DiceRoller();
    
    private:
    
        std::ifstream read;
};


#endif //CPPHOARDING_DICEROLLER_H