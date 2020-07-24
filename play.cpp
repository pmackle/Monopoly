//#include <cmath>
#include <iostream>
//#include <string>
//#include <fstream>
//#include <vector>
//#include "Property.h"
#include "DiceRoller.h"
//#include "Board.h"
//#include "Rules.h"
#include "Space.h"
//#include "Player.h"
#include "play.h"
#include "Gamestate.h"
//#include "Go.h"

int buyUpgrade(Player& player, Board& board, const Rules& rulebook)
{
    int boardSize = board.spaces.size();
    int mee;
    std::vector<int> inOrder;
    int maxSetID = 0;
    for (mee = 1; mee < boardSize; mee++)
    {
        if (board.spaces[mee]->getSetID() > maxSetID)
        {
            maxSetID = board.spaces[mee]->getSetID();
        }
    }
    
    int as;
    unsigned int pee;
    
    for (as = 0; as <= maxSetID; as++)
    {
        for (pee = 1; pee < board.spaces.size(); pee++)
        {
            if (board.spaces[pee]->getSetID() == as)
            {
                inOrder.push_back(pee);
            }
        }
    } 
   
    
    std::vector<int> monopolies;
    bool monopoly;
    unsigned int i;
    
    unsigned int j = 0;
    unsigned int k;
    unsigned int z;
    int l = 0;
    for(i = 0; i < inOrder.size(); i++){
        monopoly = true;

        while(j < inOrder.size() && board.spaces[inOrder[j]]->getSetID() == l)
        {
            
            if(board.spaces[inOrder[j]]->getOwner()->getName() != player.getName()){
                monopoly = false;
            }
            j++;
            
        }
        if (monopoly)
        {
        for (k = i; k < j; k++)
        {
            monopolies.push_back(inOrder[k]);
        }
        }
        i = j - 1;
        l++;
    }

    
    if (monopolies.size() > 0)
    {
    if(rulebook.getHousesEvenly())
    {
        int curSetID = board.spaces[ monopolies[0] ]->getSetID();
        
        for(i = 0; i < monopolies.size(); i++){
            int minNumUpgrades = 5;
            j = i;
            while (j < monopolies.size() && board.spaces[ monopolies[j] ]->getSetID() == curSetID){
                if(board.spaces[ monopolies[j] ]->numUpgrades < minNumUpgrades){
                    minNumUpgrades = board.spaces[monopolies[j]]->numUpgrades;

                }
                j++;
                
            }
            if (j < monopolies.size())
            {
            curSetID = board.spaces[ monopolies[j] ]->getSetID();
            }
            
            std::vector<int>::iterator it = monopolies.begin();
            
            for (z = i; z < j; z++)
            {
                if(minNumUpgrades == 5 || board.spaces[ monopolies[z] ]->numUpgrades != minNumUpgrades){
                    
                    monopolies.erase(it + z);
                    z--;
                    j--;
                }
            }
            
            i = z - 1;
            
        }
    }
            
            if (monopolies.size() == 0)
            {
                
                std::cout << "You don't have any properties that you can upgrade" << std::endl;
                return 0;
            }
            else
            {
                std::vector<int>::iterator iter = monopolies.begin();
                for (i = 0; i < monopolies.size(); i++)
                {
                    
                    if (board.spaces[ monopolies[i] ]->numUpgrades == 5)
                    {
                        monopolies.erase(iter + i);
                        i--;
                    }
                    else if (board.spaces[ monopolies[i] ]->numUpgrades == 4)
                    {
                        if(player.getCash() < board.spaces[ monopolies[i] ]->getHotelCost())
                        {
                std::cout << std::endl;
                            monopolies.erase(iter + i);
                            i--;
                        }
                    }
                    else 
                    {
                        if(player.getCash() < board.spaces[ monopolies[i] ]->getHouseCost())
                        {
                            monopolies.erase(iter + i);
                            i--;
                        }
                    }
                }
                
                //////////////////////////////////////////////////////PRINT STATEMENT
                /*
                for(ff = 0; ff < monopolies.size(); ff++){
                    std::cout << monopolies[ff] << " ";
                }
                std::cout << std::endl;*/
                
                if (monopolies.size() == 0)
                {
                std::cout << "You don't have any properties that you can upgrade" << std::endl;
                return 0;
                }
                else
                {
                    std::cout << "Which property do you want to upgrade?" << std::endl;
                    
                    for (i = 0; i < monopolies.size(); i++)
                    {
                        std::cout << i << ". " << board.spaces[ monopolies[i] ]->getName() << " [$";
                        if (board.spaces[ monopolies[i] ]->numUpgrades == 4)
                        {
                            std::cout << board.spaces[ monopolies[i] ]->getHotelCost();
                        }
                        else{
                            std::cout << board.spaces[ monopolies[i] ]->getHouseCost();
                        }
                        
                        std::cout << "]" << std::endl;
                    }
                    
                    std::cout << "Your choice: ";
                    
                    int sel;
                    std::cin >> sel;
                    board.spaces[ monopolies[sel] ]->numUpgrades += 1;
                    
                    
                    if (board.spaces[ monopolies[sel] ]->numUpgrades == 5)
                    {
                        board.spaces[ monopolies[sel] ]->upgrades = "H";
                        return board.spaces[ monopolies[sel] ]->getHotelCost();
                    }
                    else
                    {
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        return board.spaces[ monopolies[sel] ]->getHouseCost();
                    }
                    
                }
            }
    }
    else
    {
        std::cout << "You don't have any properties that you can upgrade" << std::endl;
        return 0;
    }
    return 0;
}

void removeUpgrades(Player& player, Board& board)
{
    unsigned int i;
    
    
    for(i = 1; i < board.spaces.size(); i++)
    {
        
        if (board.spaces[i]->getOwner()->getName() == player.getName())
        {
                
                board.spaces[i]->numUpgrades = 0;
                board.spaces[i]->upgrades.clear();
        }
    }
}

/*int rentMult(const Rules& rulebook, int newPosition, Board& board)
{
    std::string newOwner = board.spaces[newPosition]->getOwner()->getName();
    int newSetID = board.spaces[newPosition]->getSetID();
    
    int i;
    for(i = 1; i < board.getNumSpaces(); i++){
        if(board.spaces[i]->getSetID() == newSetID){
            break;
        }
    }
        while((board.spaces[i]->getSetID() == newSetID) && (i < board.getNumSpaces())){
            if (board.spaces[i]->getOwner()->getName() != newOwner){
                return 1;
            }
            i++;
        
    }
    return rulebook.getPropertySetMultiplier();
}

int sellUpgradesAvoidBankruptcyNoPrint(Player& player, Board& board, const Rules& rulebook)
{
    
    int boardSize = board.spaces.size();
     int mee;
    std::vector<int> inOrder;
    int maxSetID = 0;
    for (mee = 1; mee < boardSize; mee++)
    {
        if (board.spaces[mee]->getSetID() > maxSetID)
        {
            maxSetID = board.spaces[mee]->getSetID();
        }
    }
    
    int as;
    unsigned int pee;
    
    for (as = 0; as <= maxSetID; as++)
    {
        for (pee = 1; pee < board.spaces.size(); pee++)
        {
            if (board.spaces[pee]->getSetID() == as)
            {
                inOrder.push_back(pee);
            }
        }
    } 
   
    
    std::vector<int> monopolies;
    bool monopoly;
    unsigned int i;
    
    unsigned int j = 0;
    unsigned int k;
    unsigned int z;
    int l = 0;
    for(i = 0; i < inOrder.size(); i++){
        monopoly = true;

        while(j < inOrder.size() && board.spaces[inOrder[j]]->getSetID() == l)
        {
            
            if(board.spaces[inOrder[j]]->getOwner()->getName() != player.getName()){
                monopoly = false;
            }
            j++;
            
        }
        if (monopoly)
        {
        for (k = i; k < j; k++)
        {
            monopolies.push_back(inOrder[k]);
        }
        }
        i = j - 1;
        l++;
    }

    
    if (monopolies.size() > 0)
    {
        
    if(rulebook.getHousesEvenly())
    {
        int curSetID = board.spaces[ monopolies[0] ]->getSetID();
        
        for(i = 0; i < monopolies.size(); i++){
            int maxNumUpgrades = 0;
            j = i;
            while (j < monopolies.size() && board.spaces[ monopolies[j] ]->getSetID() == curSetID){
                if(board.spaces[ monopolies[j] ]->numUpgrades > maxNumUpgrades){
                    maxNumUpgrades = board.spaces[monopolies[j]]->numUpgrades;

                }
                j++;
                
            }
            if (j < monopolies.size())
            {
            curSetID = board.spaces[ monopolies[j] ]->getSetID();
            }
            
            std::vector<int>::iterator it = monopolies.begin();
            
            for (z = 0; z < j; z++)
            {
                if(maxNumUpgrades == 0 || board.spaces[ monopolies[z] ]->numUpgrades != maxNumUpgrades){
                    
                    monopolies.erase(it + z);
                    z--;
                    j--;
                }
            }
            i = z - 1;
            
        }
    }
            
            if (monopolies.size() == 0)
            {
                //std::cout << "You don't have any upgrades that you can sell" << std::endl;
                return 0;
            }
            else
            {
                std::vector<int>::iterator iter = monopolies.begin();
                for (i = 0; i < monopolies.size(); i++)
                {
                    if (board.spaces[ monopolies[i] ]->numUpgrades == 0)
                    {
                        monopolies.erase(iter + i);
                        i--;
                    }
                }
                
                if (monopolies.size() == 0)
                {
                //std::cout << "You don't have any upgrades that you can sell" << std::endl;
                return 0;
                }
                else
                {
                    return monopolies.size();
                    

                    
                }
            }
    }
    else
    {
        //std::cout << "You don't have any upgrades that you can sell" << std::endl;
        return 0;
    }
    return monopolies.size();
}

int sellUpgradesAvoidBankruptcy(Player& player, Board& board, const Rules& rulebook)
{
    
    int boardSize = board.spaces.size();
     int mee;
    std::vector<int> inOrder;
    int maxSetID = 0;
    for (mee = 1; mee < boardSize; mee++)
    {
        if (board.spaces[mee]->getSetID() > maxSetID)
        {
            maxSetID = board.spaces[mee]->getSetID();
        }
    }
    
    int as;
    unsigned int pee;
    
    for (as = 0; as <= maxSetID; as++)
    {
        for (pee = 1; pee < board.spaces.size(); pee++)
        {
            if (board.spaces[pee]->getSetID() == as)
            {
                inOrder.push_back(pee);
            }
        }
    } 
   
    
    std::vector<int> monopolies;
    bool monopoly;
    unsigned int i;
    
    unsigned int j = 0;
    unsigned int k;
    unsigned int z;
    int l = 0;
    for(i = 0; i < inOrder.size(); i++){
        monopoly = true;

        while(j < inOrder.size() && board.spaces[inOrder[j]]->getSetID() == l)
        {
            
            if(board.spaces[inOrder[j]]->getOwner()->getName() != player.getName()){
                monopoly = false;
            }
            j++;
            
        }
        if (monopoly)
        {
        for (k = i; k < j; k++)
        {
            monopolies.push_back(inOrder[k]);
        }
        }
        i = j - 1;
        l++;
    }

    
    if (monopolies.size() > 0)
    {
        
    if(rulebook.getHousesEvenly())
    {
        int curSetID = board.spaces[ monopolies[0] ]->getSetID();
        
        for(i = 0; i < monopolies.size(); i++){
            int maxNumUpgrades = 0;
            j = i;
            while (j < monopolies.size() && board.spaces[ monopolies[j] ]->getSetID() == curSetID){
                if(board.spaces[ monopolies[j] ]->numUpgrades > maxNumUpgrades){
                    maxNumUpgrades = board.spaces[monopolies[j]]->numUpgrades;

                }
                j++;
                
            }
            if (j < monopolies.size())
            {
            curSetID = board.spaces[ monopolies[j] ]->getSetID();
            }
            
            std::vector<int>::iterator it = monopolies.begin();
            
            for (z = 0; z < j; z++)
            {
                if(maxNumUpgrades == 0 || board.spaces[ monopolies[z] ]->numUpgrades != maxNumUpgrades){
                    
                    monopolies.erase(it + z);
                    z--;
                    j--;
                }
            }
            i = z - 1;
            
        }
    }
            
            if (monopolies.size() == 0)
            {
                //std::cout << "You don't have any upgrades that you can sell" << std::endl;
                return 0;
            }
            else
            {
                std::vector<int>::iterator iter = monopolies.begin();
                for (i = 0; i < monopolies.size(); i++)
                {
                    if (board.spaces[ monopolies[i] ]->numUpgrades == 0)
                    {
                        monopolies.erase(iter + i);
                        i--;
                    }
                }
                
                if (monopolies.size() == 0)
                {
                //std::cout << "You don't have any upgrades that you can sell" << std::endl;
                return 0;
                }
                else
                {
                    //std::cout << "Which property do you want to downgrade?" << std::endl;
                    for (i = 0; i < monopolies.size(); i++)
                    {
                        std::cout << i << ". " << board.spaces[ monopolies[i] ]->getName() << " [$";
                        if (board.spaces[ monopolies[i] ]->numUpgrades == 5)
                        {
                            std::cout << board.spaces[ monopolies[i] ]->getHotelCost()/2;
                        }
                        else{
                            std::cout << board.spaces[ monopolies[i] ]->getHouseCost()/2;
                        }
                        
                        std::cout << "]" << std::endl;
                    }
                    
                    std::cout << "Your choice: ";
                    
                    int sel;
                    std::cin >> sel;
                    
                    if (board.spaces[ monopolies[sel] ]->numUpgrades == 5)
                    {
                        board.spaces[ monopolies[sel] ]->numUpgrades -= 1;
                        board.spaces[ monopolies[sel] ]->upgrades.pop_back();
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        return board.spaces[ monopolies[sel] ]->getHotelCost()/2;
                    }
                    else
                    {
                        board.spaces[ monopolies[sel] ]->numUpgrades -= 1;
                        board.spaces[ monopolies[sel] ]->upgrades.pop_back();
                        return board.spaces[ monopolies[sel] ]->getHouseCost()/2;
                    }
                    
                    

                    
                }
            }
    }
    else
    {
        //std::cout << "You don't have any upgrades that you can sell" << std::endl;
        return 0;
    }
    return 0;
}

*/

int sellingUpgrades(Player& player, Board& board, const Rules& rulebook)
{
    
    int boardSize = board.spaces.size();
     int mee;
    std::vector<int> inOrder;
    int maxSetID = 0;
    for (mee = 1; mee < boardSize; mee++)
    {
        if (board.spaces[mee]->getSetID() > maxSetID)
        {
            maxSetID = board.spaces[mee]->getSetID();
        }
    }
    
    int as;
    unsigned int pee;
    
    for (as = 0; as <= maxSetID; as++)
    {
        for (pee = 1; pee < board.spaces.size(); pee++)
        {
            if (board.spaces[pee]->getSetID() == as)
            {
                inOrder.push_back(pee);
            }
        }
    } 
   
    
    std::vector<int> monopolies;
    bool monopoly;
    unsigned int i;
    
    unsigned int j = 0;
    unsigned int k;
    unsigned int z;
    int l = 0;
    for(i = 0; i < inOrder.size(); i++){
        monopoly = true;

        while(j < inOrder.size() && board.spaces[inOrder[j]]->getSetID() == l)
        {
            
            if(board.spaces[inOrder[j]]->getOwner()->getName() != player.getName()){
                monopoly = false;
            }
            j++;
            
        }
        
        if (monopoly)
        {
        for (k = i; k < j; k++)
        {
            monopolies.push_back(inOrder[k]);
        }
        }
        i = j - 1;
        l++;
    }
    
     

    
    if (monopolies.size() > 0)
    {
        
    if(rulebook.getHousesEvenly())
    {
        int curSetID = board.spaces[ monopolies[0] ]->getSetID();
        
        for(i = 0; i < monopolies.size(); i++){
            int maxNumUpgrades = 0;
            j = i;
            
            while (j < monopolies.size() && board.spaces[ monopolies[j] ]->getSetID() == curSetID){
                if(board.spaces[ monopolies[j] ]->numUpgrades > maxNumUpgrades){
                    maxNumUpgrades = board.spaces[monopolies[j]]->numUpgrades;

                }
                j++;
                
            }
            if (j < monopolies.size())
            {
            curSetID = board.spaces[ monopolies[j] ]->getSetID();
            }
            
            std::vector<int>::iterator it = monopolies.begin();
            
            for (z = i; z < j; z++)
            {
                if(maxNumUpgrades == 0 || board.spaces[ monopolies[z] ]->numUpgrades != maxNumUpgrades){
                    monopolies.erase(it + z);
                    z--;
                    j--;
                    it = monopolies.begin();
                }
            }
            i = z - 1;
        }
    }
            
            if (monopolies.size() == 0)
            {
                std::cout << "You don't have any upgrades that you can sell" << std::endl;
                return 0;
            }
            else
            {
                std::vector<int>::iterator iter = monopolies.begin();
                for (i = 0; i < monopolies.size(); i++)
                {
                    if (board.spaces[ monopolies[i] ]->numUpgrades == 0)
                    {
                        monopolies.erase(iter + i);
                        i--;
                         iter = monopolies.begin();
                    }
                }
                
                if (monopolies.size() == 0)
                {
                std::cout << "You don't have any upgrades that you can sell" << std::endl;
                return 0;
                }
                else
                {
                    std::cout << "Which property do you want to downgrade?" << std::endl;
                    for (i = 0; i < monopolies.size(); i++)
                    {
                        std::cout << i << ". " << board.spaces[ monopolies[i] ]->getName() << " [$";
                        if (board.spaces[ monopolies[i] ]->numUpgrades == 5)
                        {
                            std::cout << board.spaces[ monopolies[i] ]->getHotelCost()/2;
                        }
                        else{
                            std::cout << board.spaces[ monopolies[i] ]->getHouseCost()/2;
                        }
                        
                        std::cout << "]" << std::endl;
                    }
                    
                    std::cout << "Your choice: ";
                    
                    int sel;
                    std::cin >> sel;
                    
                    if (board.spaces[ monopolies[sel] ]->numUpgrades == 5)
                    {
                        board.spaces[ monopolies[sel] ]->numUpgrades -= 1;
                        board.spaces[ monopolies[sel] ]->upgrades.pop_back();
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        board.spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        return board.spaces[ monopolies[sel] ]->getHotelCost()/2;
                    }
                    else
                    {
                        board.spaces[ monopolies[sel] ]->numUpgrades -= 1;
                        board.spaces[ monopolies[sel] ]->upgrades.pop_back();
                        return board.spaces[ monopolies[sel] ]->getHouseCost()/2;
                    }
                    
                    

                    
                }
            }
    }
    else
    {
        std::cout << "You don't have any upgrades that you can sell" << std::endl;
        return 0;
    }
    return 0;
}

void play(int argc, char** argv)
{
    
    std::string randomNumsFile(argv[3]);
    DiceRoller dice(randomNumsFile);
    
    int numPlayers;
    
    std::cout << "Enter how many players will be playing: ";
    std::cin >> numPlayers;
    std::string rulesFile(argv[1]);
    Rules rulebook(rulesFile, numPlayers);
        
    std::string boardFile(argv[2]);
    
    Board board(boardFile);
    
    std::vector<Player> players;

    int i;
    
    for (i = 0; i < numPlayers; i++)
    {
        std::string tmpName;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> tmpName;
        
        Player tmpPlayer(&rulebook, rulebook.getStartCash(), tmpName, i);
        players.push_back(tmpPlayer);
    }
    
    
    board.players = &players;
    Gamestate game(rulebook);
    int playerTurn = 0;
    
    for (i = 0; i < numPlayers; i++)
    {
        board.spaces[0]->playersOn.push_back(&(players[i]));
    }

     while(!game.gameIsOver()){
         int reRolls = 0;
    playerRolledDoubles:
    dice.roll1 = 0;
    dice.roll2 = -1;
    board.print();
    std::cout << players[playerTurn].getName() << " please enter your move" << std::endl;
    std::cout << "1 to roll dice" << std::endl;
    std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
    std::cout << "3 to sell a house or hotel" << std::endl;
    std::cout << "4 to leave the game" << std::endl;
    std::cout << "Your move: ";
    int playerChoice;
    std::cin >> playerChoice;
    
    if(playerChoice == 1){
        players[playerTurn].roll = dice.rollDice();
        std::cout << players[playerTurn].getName() << ", you rolled a " << players[playerTurn].roll << std::endl;
        players[playerTurn].setNewPosition((players[playerTurn].roll + players[playerTurn].getCurrentPosition()) % (board.getNumSpaces()));
        
        unsigned int q;
        std::vector<Player*>::iterator it;
        
        for(q = 0; q < board.spaces[players[playerTurn].currentPosition]->playersOn.size(); q++){
            if(board.spaces[players[playerTurn].currentPosition]->playersOn[q]->getIndex() == playerTurn){
                break;
            }
        }
        it = board.spaces[players[playerTurn].currentPosition]->playersOn.begin();
        board.spaces[players[playerTurn].getCurrentPosition()]->playersOn.erase(it + q);
        
        board.spaces[players[playerTurn].newPosition]->activate(players[playerTurn]);
        
        /*
        if (players[playerTurn].getNewPosition() == 0)
        {
            players[playerTurn].pay(((((players[playerTurn].getCurrentPosition() + roll) - 1) / board.getNumSpaces()) * board.spaces[0]->getSalary() + rulebook.getSalaryMultiplier() * board.spaces[0]->getSalary()));
            players[playerTurn].increaseNetWorth(((((players[playerTurn].getCurrentPosition() + roll) - 1) / board.getNumSpaces()) * board.spaces[0]->getSalary() + rulebook.getSalaryMultiplier() * board.spaces[0]->getSalary()));
        }
        else
        {
            players[playerTurn].pay((((players[playerTurn].getCurrentPosition() + roll) / board.getNumSpaces()) * board.spaces[0]->getSalary()));
            players[playerTurn].increaseNetWorth((((players[playerTurn].getCurrentPosition() + roll) / board.getNumSpaces()) * board.spaces[0]->getSalary()));
            
            if (board.spaces[players[playerTurn].getNewPosition()]->getOwner()->getName() == "None")
            {
               //////////////////////////////////////////////////////////////////////////////
                if (players[playerTurn].getCash() >= board.spaces[players[playerTurn].newPosition]->getPropertyCost())
                {
                    std::cout << "Would you like to buy " << board.spaces[players[playerTurn].newPosition]->getName() << " for $" <<  board.spaces[players[playerTurn].newPosition]->getPropertyCost() << "?" << std::endl;
                    std::cout << "Rent on " << board.spaces[players[playerTurn].newPosition]->getName() << " is $" << board.spaces[players[playerTurn].newPosition]->getRent() << std::endl;
                    //std::cout << "You currently have $" << players[playerTurn].getCash() << std::endl;
                    std::cout << "Enter y for yes or n for no: ";
                    //printf("Owner = %d\n", spaces[players[playerTurn].newSpace - 1].owner);
                    char buy;
                    std::cin >> buy;
                
                
                    if (buy == 'y')
                    {
                        players[playerTurn].charge(board.spaces[players[playerTurn].newPosition]->getPropertyCost());
                        board.spaces[players[playerTurn].newPosition]->setOwner(players[playerTurn]);
                        std::cout << players[playerTurn].getName() << " bought " << board.spaces[players[playerTurn].newPosition]->getName() << " for $" << board.spaces[players[playerTurn].newPosition]->getPropertyCost() << std::endl;
                    }
                    
                    else{
                        if(rulebook.getAuctionProperties()){
                            AuctionProperties(players, board, players[playerTurn]->newPosition);
                        }
                    }
                
                
                
                }
                else
                {
                    std::cout << players[playerTurn].getName() << ", you don't have enough money to afford " << board.spaces[players[playerTurn].newPosition]->getName() << "." << std::endl;
                    std::cout << board.spaces[players[playerTurn].newPosition]->getName() << " costs $" << board.spaces[players[playerTurn].newPosition]->getPropertyCost() << " but you only have $" << players[playerTurn].getCash() << std::endl;
                    if(rulebook.getAuctionProperties()){
                            AuctionProperties(players, board, players[playerTurn].newPosition);
                        }
                }
            }
            
            
            else if (board.spaces[players[playerTurn].newPosition]->getOwner()->getName() != players[playerTurn].getName())
            {
                
                int rent;
                
                if (board.spaces[players[playerTurn].newPosition]->numUpgrades == 0)
                {
                    rent = (board.spaces[players[playerTurn].newPosition]->getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board);
                }
                else if (board.spaces[players[playerTurn].newPosition]->numUpgrades <= 4)
                {
                    rent = board.spaces[players[playerTurn].newPosition]->getRentWithHouse() * pow(2, board.spaces[players[playerTurn].newPosition]->numUpgrades - 1);
                }
                else
                {
                    rent = board.spaces[players[playerTurn].newPosition]->getRentWithHotel();
                }
                
                if (players[playerTurn].getCash() > (rent))
                {   
                    
                    std::cout << players[playerTurn].getName() << " paid " << board.spaces[players[playerTurn].newPosition]->getOwner()->getName() << " $" << rent << " for landing on " << board.spaces[players[playerTurn].newPosition]->getName() << std::endl;
                    players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].pay(rent);
                    
                    
                    int w;
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].getName())
                            {
                                board.spaces[w]->playersOn[y]->pay(rent);
                                board.spaces[w]->playersOn[y]->increaseNetWorth( (rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                   
                    
                    
                    players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].increaseNetWorth( (rent));
                    players[playerTurn].charge( (rent));
                    
                    
                    
                    
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[playerTurn].getName())
                            {
                                board.spaces[w]->playersOn[y]->charge( (rent));
                                board.spaces[w]->playersOn[y]->decreaseNetWorth ((rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    players[playerTurn].decreaseNetWorth ((rent));
                }
                else
                {
                    while (sellUpgradesAvoidBankruptcyNoPrint(players[playerTurn], board, rulebook) != 0 && players[playerTurn].getCash() < rent)
                    {
                        std::cout << "You have $" << players[playerTurn].getCash() << " but you owe $" << rent << std::endl;
                        std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
                        int downgradeRevenue;
        downgradeRevenue = sellUpgradesAvoidBankruptcy(players[playerTurn], board, rulebook);
        int patar;

        players[playerTurn].pay(downgradeRevenue);
        
        for (patar = 0; patar < board.getNumSpaces(); patar++)
        {
            unsigned int douy;
                        
            for (douy = 0; douy < board.spaces[patar]->playersOn.size(); douy++)
            {
                if (board.spaces[patar]->playersOn[douy]->getName() == players[playerTurn].getName())
                    {
                        board.spaces[patar]->playersOn[douy]->pay(downgradeRevenue);
                        break;
                    }
            }
        }
                        //sellUpgradesAvoidBankruptcy(players[playerTurn], board, rulebook);
                    }
                    
                    //std::cout << players[playerTurn].getCash() << std::endl;
                    
                    if (players[playerTurn].getCash() < rent)
                    {
                    
                    
                    std::cout << players[playerTurn].getName() << " went bankrupt to " << board.spaces[players[playerTurn].newPosition]->getOwner()->getName() << " for landing on " << board.spaces[players[playerTurn].newPosition]->getName() << std::endl;
                    players[playerTurn].isIn = false;
                    int w;
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[playerTurn].getName())
                            {
                                board.spaces[w]->playersOn[y]->isIn = false;
                                break;
                            }
                        }
                    }
                    players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].pay(players[playerTurn].getCash());
                    players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].increaseNetWorth(players[playerTurn].getNetWorth());
                    
            
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].getName())
                            {
                                board.spaces[w]->playersOn[y]->pay(players[playerTurn].getCash());
                                board.spaces[w]->playersOn[y]->increaseNetWorth( players[playerTurn].getNetWorth());
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    players[playerTurn].charge(players[playerTurn].getCash());
                    players[playerTurn].decreaseNetWorth(players[playerTurn].getNetWorth());
                    
                    
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[playerTurn].getName())
                            {
                                board.spaces[w]->playersOn[y]->charge( players[playerTurn].getCash());
                                board.spaces[w]->playersOn[y]->decreaseNetWorth (players[playerTurn].getNetWorth());
                                break;
                            }
                        }
                    }
                    
                    
                    
                    for (i = 1; i < board.getNumSpaces(); i++)
                    {
                        if (board.spaces[i]->getOwner()->getName() == players[playerTurn].getName()) 
                        {
                            board.spaces[i]->setOwner(board.spaces[players[playerTurn].newPosition]->getOwner());
                        }
                    }
                    
                    game.decreaseNumPlayers();
                    }
                    else
                    {
                        std::cout << players[playerTurn].getName() << " paid " << board.spaces[players[playerTurn].newPosition]->getOwner()->getName() << " $" << rent << " for landing on " << board.spaces[players[playerTurn].newPosition]->getName() << std::endl;
                    players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].pay(rent);
                    
                    
                    int w;
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].getName())
                            {
                                board.spaces[w]->playersOn[y]->pay(rent);
                                board.spaces[w]->playersOn[y]->increaseNetWorth( (rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                   
                    
                    
                    players[board.spaces[players[playerTurn].newPosition]->getOwner()->getIndex()].increaseNetWorth( (rent));
                    players[playerTurn].charge( (rent));
                    
                    
                    
                    
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[playerTurn].getName())
                            {
                                board.spaces[w]->playersOn[y]->charge( (rent));
                                board.spaces[w]->playersOn[y]->decreaseNetWorth ((rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    players[playerTurn].decreaseNetWorth ((rent));
                    }
                    
                    
                }
                
                
            if (players[playerTurn].getCash() >= (board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board))
                {   
                    int x = board.spaces[players[playerTurn].newPosition].getRent() * rentMult(rulebook, players[playerTurn].newPosition, board);
                    std::cout << players[playerTurn].getName() << " paid " << board.spaces[players[playerTurn].newPosition].getOwner()->getName() << " $" << x << " for landing on " << board.spaces[players[playerTurn].newPosition].getName() << std::endl;
                    players[board.spaces[players[playerTurn].newPosition].getOwner()->getIndex()].pay((board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook,  players[playerTurn].newPosition, board));
                    
                    
                    int w;
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w].playersOn.size(); y++)
                        {
                            if (board.spaces[w].playersOn[y].getName() == players[board.spaces[players[playerTurn].newPosition].getOwner()->getIndex()].getName())
                            {
                                board.spaces[w].playersOn[y].pay((board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook,  players[playerTurn].newPosition, board));
                                board.spaces[w].playersOn[y].increaseNetWorth( (board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                   
                    
                    
                    players[board.spaces[players[playerTurn].newPosition].getOwner()->getIndex()].increaseNetWorth( (board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board));
                    players[playerTurn].charge( (board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board));
                    
                    
                    
                    
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w].playersOn.size(); y++)
                        {
                            if (board.spaces[w].playersOn[y].getName() == players[playerTurn].getName())
                            {
                                board.spaces[w].playersOn[y].charge( (board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board));
                                board.spaces[w].playersOn[y].decreaseNetWorth ((board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    players[playerTurn].decreaseNetWorth ((board.spaces[players[playerTurn].newPosition].getRent()) * rentMult(rulebook, players[playerTurn].newPosition, board));
                }
                else
                {
                    std::cout << players[playerTurn].getName() << " went bankrupt to " << board.spaces[players[playerTurn].newPosition].getOwner()->getName() << " for landing on " << board.spaces[players[playerTurn].newPosition].getName() << std::endl;
                    players[playerTurn].isIn = false;
                    int w;
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w].playersOn.size(); y++)
                        {
                            if (board.spaces[w].playersOn[y].getName() == players[playerTurn].getName())
                            {
                                board.spaces[w].playersOn[y].isIn = false;
                                break;
                            }
                        }
                    }
                    players[board.spaces[players[playerTurn].newPosition].getOwner()->getIndex()].pay(players[playerTurn].getCash());
                    players[board.spaces[players[playerTurn].newPosition].getOwner()->getIndex()].increaseNetWorth(players[playerTurn].getNetWorth());
                    
            
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w].playersOn.size(); y++)
                        {
                            if (board.spaces[w].playersOn[y].getName() == players[board.spaces[players[playerTurn].newPosition].getOwner()->getIndex()].getName())
                            {
                                board.spaces[w].playersOn[y].pay(players[playerTurn].getCash());
                                board.spaces[w].playersOn[y].increaseNetWorth( players[playerTurn].getNetWorth());
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    players[playerTurn].charge(players[playerTurn].getCash());
                    players[playerTurn].decreaseNetWorth(players[playerTurn].getNetWorth());
                    
                    
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w].playersOn.size(); y++)
                        {
                            if (board.spaces[w].playersOn[y].getName() == players[playerTurn].getName())
                            {
                                board.spaces[w].playersOn[y].charge( players[playerTurn].getCash());
                                board.spaces[w].playersOn[y].decreaseNetWorth (players[playerTurn].getNetWorth());
                                break;
                            }
                        }
                    }
                    
                    
                    
                    for (i = 1; i < board.getNumSpaces(); i++)
                    {
                        if (board.spaces[i].getOwner()->getName() == players[playerTurn].getName()) 
                        {
                            board.spaces[i].setOwner(board.spaces[players[playerTurn].newPosition].getOwner());
                        }
                    }
                    
                    game.decreaseNumPlayers();
                    
                    
                }
                
            }
            else
            {
                std::cout << players[playerTurn].getName() << ", you landed on " << board.spaces[players[playerTurn].newPosition]->getName() << " which you already own" << std::endl;// ____, you landed on ____ which you already own
            }
        }
        
        players[playerTurn].setCurrentPosition(players[playerTurn].getNewPosition());
        // MODIFY PLAYERSON FOR BOTH SPACES IN QUESTION
        unsigned int z;
        for(z = 0; z < board.spaces[players[playerTurn].newPosition]->playersOn.size(); z++){
            if(board.spaces[players[playerTurn].newPosition]->playersOn[z]->getIndex() > playerTurn){
                break;
            }
        }
        it = board.spaces[players[playerTurn].newPosition]->playersOn.begin();
        
        board.spaces[players[playerTurn].newPosition]->playersOn.insert(it+z, &(players[playerTurn]));
        */
    }
    
    /////////////////////BUY UPGRADE///////////////////////////////////////////
    else if(playerChoice == 2){
        int upgradeCost;
        upgradeCost = buyUpgrade(players[playerTurn], board, rulebook);
        //int patar;

        players[playerTurn].charge(upgradeCost);
        
        /*for (patar = 0; patar < board.getNumSpaces(); patar++)
        {
            unsigned int douy;
                        
            for (douy = 0; douy < board.spaces[patar]->playersOn.size(); douy++)
            {
                if (board.spaces[patar]->playersOn[douy]->getName() == players[playerTurn].getName())
                    {
                        board.spaces[patar]->playersOn[douy]->charge(upgradeCost);
                        break;
                    }
            }
        }*/
        
        
        
        
        goto playerRolledDoubles;
    }
    
    /////////////////////SELL UPGRADE/////////////////////////////////////////
    else if(playerChoice == 3){
        int downgradeRevenue;
        downgradeRevenue = sellingUpgrades(players[playerTurn], board, rulebook);
       // int patar;

        players[playerTurn].pay(downgradeRevenue);
        
        /*for (patar = 0; patar < board.getNumSpaces(); patar++)
        {
            unsigned int douy;
                        
            for (douy = 0; douy < board.spaces[patar]->playersOn.size(); douy++)
            {
                if (board.spaces[patar]->playersOn[douy]->getName() == players[playerTurn].getName())
                    {
                        board.spaces[patar]->playersOn[douy]->pay(downgradeRevenue);
                        break;
                    }
            }
        }*/
        
        
        goto playerRolledDoubles;
    }
    
    //////////////////////LEAVE GAME//////////////////////////////////////////
    else if(playerChoice == 4){

        removeUpgrades(players[playerTurn], board);
        
        for (i = 1; i < board.getNumSpaces(); i++)
        {
            if (board.spaces[i]->getOwner()->getName() == players[playerTurn].getName())
            {
                Player none;
                board.spaces[i]->setOwner(none);
                
            }
        }
        
        
        players[playerTurn].charge(players[playerTurn].getCash());
        players[playerTurn].isIn = false;
        /*int w;
                    for (w = 0; w < board.getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < board.spaces[w]->playersOn.size(); y++)
                        {
                            if (board.spaces[w]->playersOn[y]->getName() == players[playerTurn].getName())
                            {
                                board.spaces[w]->playersOn[y]->isIn = false;
                                break;
                            }
                        }
                    }*/
        rulebook.numPlayersLeftInGame--;
    }
    
    
    if (dice.roll1 == dice.roll2 && players[playerTurn].isIn && reRolls < rulebook.getMaxDoublesReRolls())
    {
        reRolls++;
        goto playerRolledDoubles;
    }
    
    
    game.incrementTurns();
    do
    {
        playerTurn++;
        playerTurn %= numPlayers;
    }
    while (players[playerTurn].isIn != true);
    }
    board.print();
    game.getWinner(players);
}

/*
void AuctionProperties(std::vector <Player>& players, Board& board, int newPosition){
    int numPlayersInAuction = 0;
    unsigned int ss;
    std::string highestBidder = "";
    int highestBid = 0;

    std::cout << "Starting the auction for " << board.spaces[newPosition]->getName() << std::endl;
    for(ss = 0; ss < players.size(); ss++){
        if(players[ss].isIn){
            numPlayersInAuction++;
            players[ss].isInAuction = true;
        }
    }
    while(numPlayersInAuction > 1){
        for(ss = 0; ss < players.size(); ss++){
            if(players[ss].isInAuction && (numPlayersInAuction > 1 || !players[ss].hasBet)){
                if(players[ss].getCash() > highestBid){
                    
                    if(highestBidder == ""){
                        std::cout << "No one has bid on " << board.spaces[newPosition]->getName() << " [$" << board.spaces[newPosition]->getPropertyCost() << "] yet" << std::endl;
                    }
                    else{
                        std::cout << "The current bid for " << board.spaces[newPosition]->getName() << " [$" << board.spaces[newPosition]->getPropertyCost() << "] is $" << highestBid << " by " << highestBidder << std::endl;
                    }
                    
                    int playerBid;
                    std::cout << players[ss].getName() << ", enter a bid of at least $" << (highestBid + 1) << " to bid on the property or a value less than that to leave the auction" << std::endl;
                    std::cout << "Your bid: ";
                    
                    std::cin >> playerBid;
                    if (playerBid > highestBid){
                        highestBid = playerBid;
                        highestBidder = players[ss].getName();
                        players[ss].hasBet = true;
                    }
                    else{
                        players[ss].isInAuction = false;
                        numPlayersInAuction--;
                    }
                }
                
                else{
                        players[ss].isInAuction = false;
                        numPlayersInAuction--;
                }
            }
        }
        
        if(highestBidder == ""){
            std::cout << "No one decided to purchase " << board.spaces[newPosition]->getName() << std::endl;
        }
        
        
    }
    unsigned int pp;
    for(ss = 0; ss < players.size(); ss++){
            if(players[ss].getName() == highestBidder){
                players[ss].charge(highestBid);
                board.spaces[newPosition]->setOwner(players[ss]);
                std::cout << players[ss].getName() << " won " << board.spaces[newPosition]->getName() << " for $" << highestBid << std::endl;
                for(pp = 0; pp < board.spaces.size(); pp++){
                    unsigned int qq;
                    for(qq = 0; qq < board.spaces[pp]->playersOn.size(); qq++){
                        if(board.spaces[pp]->playersOn[qq]->getName() == highestBidder){
                            board.spaces[pp]->playersOn[qq]->charge(highestBid);
                            break;
                        }
                    }
                }
                break;
            }
        }
}
*/