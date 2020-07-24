//#include <limits>
//#include <string>
#include <fstream>
#include "Rules.h"

Rules::Rules(std::string rulesFile, int numPlayers) : numPlayersLeftInGame(numPlayers)
{
    //int maxStream = std::numeric_limits<std::streamsize>::max();
    std::ifstream read;
    
    read.open(rulesFile);
    char ignoreChar;
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> startCash;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> turnLimit;
    
    if (turnLimit == -1)
    {
        turnLimit = 69420;
    }
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> numPlayersLeft;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> propertySetMultiplier;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> requiredHouses;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> housesEvenly;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> moneyFreeParking;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> auctionProperties;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> salaryMultiplier;
    
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ':');
    read >> maxDoublesReRolls;
    
    read.close();
}

int Rules::getStartCash() const
{
    return startCash;
}

int Rules::getTurnLimit() const
{
    return turnLimit;
}

int Rules::getNumPlayersLeft() const
{
   return numPlayersLeft; 
}

int Rules::getPropertySetMultiplier() const
{
    return propertySetMultiplier;
}

int Rules::getSalaryMultiplier() const
{
    return salaryMultiplier;
}

int Rules::getMaxDoublesReRolls() const
{
    return maxDoublesReRolls;
}

bool Rules::getAuctionProperties() const{
    if (auctionProperties == "Yes")
        return true;
        
        return false;
}

bool Rules::getHousesEvenly() const{
    
    if (housesEvenly == "Yes")
        return true;
        
        return false;
}

bool Rules::getMoneyFreeParking() const{
    
    if (moneyFreeParking == "Yes")
        return true;
        
        return false;
}