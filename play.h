#ifndef CPPHOARDING_PLAY_H
#define CPPHOARDING_PLAY_H

#include "Rules.h"
#include "Board.h"

/*class Rules
{
    public:
    
        Rules(std::string rulesFile);
        
        int getStartCash() const;
        int getTurnLimit() const;
        int getNumPlayersLeft() const;
        int getPropertySetMultiplier() const;
        int getSalaryMultiplier() const;
        
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
};*/
void play(int argc, char** argv);
int sellingUpgrades(Player& player, Board& board, const Rules& rulebook);
void removeUpgrades(Player& player, Board& board);
//int rentMult(const Rules& rulebook, int newPosition, Board& board);
//void AuctionProperties(std::vector <Player>& players, Board& board, int newPosition);
int buyUpgrade(Player& player, Board& board, const Rules& rulebook);
//int sellUpgradesAvoidBankruptcy(Player& player, Board& board, const Rules& rulebook);

#endif