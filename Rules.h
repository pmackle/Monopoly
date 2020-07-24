#ifndef CPPHOARDING_RULES_H
#define CPPHOARDING_RULES_H

#include <string>

class Rules
{
    public:
    
        Rules(std::string rulesFile, int numPlayers);
        
        int numPlayersLeftInGame;
        
        int getStartCash() const;
        int getTurnLimit() const;
        int getNumPlayersLeft() const;
        int getPropertySetMultiplier() const;
        int getSalaryMultiplier() const;
        int getMaxDoublesReRolls() const;
        bool getAuctionProperties() const;
        bool getHousesEvenly() const;
        bool getMoneyFreeParking() const;
        
    private:
    
        int startCash;
        int turnLimit;
        int numPlayersLeft;
        int propertySetMultiplier;
        int requiredHouses;
        std::string housesEvenly;
        std::string moneyFreeParking;
        std::string auctionProperties;
        int salaryMultiplier;
        int maxDoublesReRolls;
};

#endif //CPPHOARDING_RULES_H