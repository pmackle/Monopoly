//#include <string>
//#include <fstream>
#include "DiceRoller.h"

DiceRoller::DiceRoller(std::string randomNumsFile) : roll1(0), roll2(0)
{
    read.open(randomNumsFile);
}

int DiceRoller::rollDice()
{
    
    read >> roll1;
    read >> roll2;
    
    roll1 %= 6;
    roll1 += 1;
    roll2 %= 6;
    roll2 += 1;
    
    return roll1 + roll2;
}



DiceRoller::~DiceRoller()
{
    read.close();
}