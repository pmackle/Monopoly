#include "Property.h"
#include <iostream>
//#include "Player.h"
//#include "Space.h"


Property::Property(int index, std::string type, std::string name, int setID, int intrasetID, int propertyCost, int houseCost,
                   int hotelCost, int rent, int rentWithHouse, int rentWithHotel, Board* board) : Space(board, index, type, name),
                                                                                    setID(setID), intrasetID(intrasetID),
                                                                                    propertyCost(propertyCost), houseCost(houseCost),
                                                                                    hotelCost(hotelCost), rent(rent), rentWithHouse(rentWithHouse),
                                                                                    rentWithHotel(rentWithHotel)
{
        Player none;
        owner = none;

}

int Property::rentMult(Player& player)
{
    std::string newOwner = this->board->spaces[player.newPosition]->getOwner().getName();
    int newSetID = this->board->spaces[player.newPosition]->getSetID();
    
    int i;
    for(i = 1; i < board->getNumSpaces(); i++){
        if(this->board->spaces[i]->getSetID() == newSetID){
            break;
        }
    }
        while((this->board->spaces[i]->getSetID() == newSetID) && (i < this->board->getNumSpaces())){
            if (this->board->spaces[i]->getOwner().getName() != newOwner){
                return 1;
            }
            i++;
        
    }
    return player.rulebook->getPropertySetMultiplier();
}

int Property::sellUpgradesAvoidBankruptcyNoPrint(Player& player)
{
    
    int boardSize = this->board->spaces.size();
     int mee;
    std::vector<int> inOrder;
    int maxSetID = 0;
    for (mee = 1; mee < boardSize; mee++)
    {
        if (this->board->spaces[mee]->getSetID() > maxSetID)
        {
            maxSetID = this->board->spaces[mee]->getSetID();
        }
    }
    
    int as;
    unsigned int pee;
    
    for (as = 0; as <= maxSetID; as++)
    {
        for (pee = 1; pee < this->board->spaces.size(); pee++)
        {
            if (this->board->spaces[pee]->getSetID() == as)
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

        while(j < inOrder.size() && this->board->spaces[inOrder[j]]->getSetID() == l)
        {
            
            if(this->board->spaces[inOrder[j]]->getOwner().getName() != player.getName()){
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
        
    if(player.rulebook->getHousesEvenly())
    {
        int curSetID = this->board->spaces[ monopolies[0] ]->getSetID();
        
        for(i = 0; i < monopolies.size(); i++){
            int maxNumUpgrades = 0;
            j = i;
            while (j < monopolies.size() && this->board->spaces[ monopolies[j] ]->getSetID() == curSetID){
                if(this->board->spaces[ monopolies[j] ]->numUpgrades > maxNumUpgrades){
                    maxNumUpgrades = this->board->spaces[monopolies[j]]->numUpgrades;

                }
                j++;
                
            }
            if (j < monopolies.size())
            {
            curSetID = this->board->spaces[ monopolies[j] ]->getSetID();
            }
            
            std::vector<int>::iterator it = monopolies.begin();
            
            for (z = 0; z < j; z++)
            {
                if(maxNumUpgrades == 0 || this->board->spaces[ monopolies[z] ]->numUpgrades != maxNumUpgrades){
                    
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
                    if (this->board->spaces[ monopolies[i] ]->numUpgrades == 0)
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

int Property::sellUpgradesAvoidBankruptcy(Player& player)
{
    
    int boardSize = this->board->spaces.size();
     int mee;
    std::vector<int> inOrder;
    int maxSetID = 0;
    for (mee = 1; mee < boardSize; mee++)
    {
        if (this->board->spaces[mee]->getSetID() > maxSetID)
        {
            maxSetID = this->board->spaces[mee]->getSetID();
        }
    }
    
    int as;
    unsigned int pee;
    
    for (as = 0; as <= maxSetID; as++)
    {
        for (pee = 1; pee < this->board->spaces.size(); pee++)
        {
            if (this->board->spaces[pee]->getSetID() == as)
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

        while(j < inOrder.size() && this->board->spaces[inOrder[j]]->getSetID() == l)
        {
            
            if(this->board->spaces[inOrder[j]]->getOwner().getName() != player.getName()){
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
        
    if(player.rulebook->getHousesEvenly())
    {
        int curSetID = this->board->spaces[ monopolies[0] ]->getSetID();
        
        for(i = 0; i < monopolies.size(); i++){
            int maxNumUpgrades = 0;
            j = i;
            while (j < monopolies.size() && this->board->spaces[ monopolies[j] ]->getSetID() == curSetID){
                if(this->board->spaces[ monopolies[j] ]->numUpgrades > maxNumUpgrades){
                    maxNumUpgrades = this->board->spaces[monopolies[j]]->numUpgrades;

                }
                j++;
                
            }
            if (j < monopolies.size())
            {
            curSetID = this->board->spaces[ monopolies[j] ]->getSetID();
            }
            
            std::vector<int>::iterator it = monopolies.begin();
            
            for (z = 0; z < j; z++)
            {
                if(maxNumUpgrades == 0 || this->board->spaces[ monopolies[z] ]->numUpgrades != maxNumUpgrades){
                    
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
                    if (this->board->spaces[ monopolies[i] ]->numUpgrades == 0)
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
                        std::cout << i << ". " << this->board->spaces[ monopolies[i] ]->getName() << " [$";
                        if (this->board->spaces[ monopolies[i] ]->numUpgrades == 5)
                        {
                            std::cout << this->board->spaces[ monopolies[i] ]->getHotelCost()/2;
                        }
                        else{
                            std::cout << this->board->spaces[ monopolies[i] ]->getHouseCost()/2;
                        }
                        
                        std::cout << "]" << std::endl;
                    }
                    
                    std::cout << "Your choice: ";
                    
                    int sel;
                    std::cin >> sel;
                    
                    if (this->board->spaces[ monopolies[sel] ]->numUpgrades == 5)
                    {
                        this->board->spaces[ monopolies[sel] ]->numUpgrades -= 1;
                        this->board->spaces[ monopolies[sel] ]->upgrades.pop_back();
                        this->board->spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        this->board->spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        this->board->spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        this->board->spaces[ monopolies[sel] ]->upgrades.push_back('h');
                        return this->board->spaces[ monopolies[sel] ]->getHotelCost()/2;
                    }
                    else
                    {
                        this->board->spaces[ monopolies[sel] ]->numUpgrades -= 1;
                        this->board->spaces[ monopolies[sel] ]->upgrades.pop_back();
                        return this->board->spaces[ monopolies[sel] ]->getHouseCost()/2;
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

int Property::getSetID() const
{
    return setID;
}

int Property::getIntrasetID() const
{
    return intrasetID;
}

int Property::getPropertyCost() const
{
    return propertyCost;
}

int Property::getHouseCost() const
{
    return houseCost;
}

int Property::getHotelCost() const
{
    return hotelCost;
}

int Property::getRent() const
{
    return rent;
}

int Property::getRentWithHouse() const
{
    return rentWithHouse;
}

int Property::getRentWithHotel() const
{
    return rentWithHotel;
}

Player& Property::getOwner()
{
    return owner;
}

void Property::setOwner(const Player& player)
{
    owner = player;
}

virtual void Property::activate(Player& activatingPlayer)
{
    activatingPlayer.pay((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) / this->board->getNumSpaces()) * this->board->spaces[0]->getSalary()));
            activatingPlayer.increaseNetWorth((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) / this->board->getNumSpaces()) * this->board->spaces[0]->getSalary()));
            
            if (this->board->spaces[activatingPlayer.getNewPosition()]->getOwner().getName() == "None")
            {
               //////////////////////////////////////////////////////////////////////////////
                if (activatingPlayer.getCash() >= this->board->spaces[activatingPlayer.newPosition]->getPropertyCost())
                {
                    std::cout << "Would you like to buy " << this->board->spaces[activatingPlayer.newPosition]->getName() << " for $" <<  this->board->spaces[activatingPlayer.newPosition]->getPropertyCost() << "?" << std::endl;
                    std::cout << "Rent on " << this->board->spaces[activatingPlayer.newPosition]->getName() << " is $" << this->board->spaces[activatingPlayer.newPosition]->getRent() << std::endl;
                    //std::cout << "You currently have $" << activatingPlayer.getCash() << std::endl;
                    std::cout << "Enter y for yes or n for no: ";
                    //printf("Owner = %d\n", spaces[activatingPlayer.newSpace - 1].owner);
                    char buy;
                    std::cin >> buy;
                
                
                    if (buy == 'y')
                    {
                        activatingPlayer.charge(this->board->spaces[activatingPlayer.newPosition]->getPropertyCost());
                        this->board->spaces[activatingPlayer.newPosition]->setOwner(activatingPlayer);
                        std::cout << activatingPlayer.getName() << " bought " << this->board->spaces[activatingPlayer.newPosition]->getName() << " for $" << this->board->spaces[activatingPlayer.newPosition]->getPropertyCost() << std::endl;
                    }
                    
                    else{
                        if(activatingPlayer.rulebook->getAuctionProperties()){
                            AuctionProperties(players, this->board, activatingPlayer->newPosition);
                        }
                    }
                
                
                
                }
                else
                {
                    std::cout << activatingPlayer.getName() << ", you don't have enough money to afford " << this->board->spaces[activatingPlayer.newPosition]->getName() << "." << std::endl;
                    std::cout << this->board->spaces[activatingPlayer.newPosition]->getName() << " costs $" << this->board->spaces[activatingPlayer.newPosition]->getPropertyCost() << " but you only have $" << activatingPlayer.getCash() << std::endl;
                    if(activatingPlayer.rulebook->getAuctionProperties()){
                            AuctionProperties(players, this->board, activatingPlayer.newPosition);
                        }
                }
            }
            
            
            else if (this->board->spaces[activatingPlayer.newPosition]->getOwner().getName() != activatingPlayer.getName())
            {
                
                int rent;
                
                if (this->board->spaces[activatingPlayer.newPosition]->numUpgrades == 0)
                {
                    rent = (this->board->spaces[activatingPlayer.newPosition]->getRent()) * rentMult(activatingPlayer.rulebook, activatingPlayer.newPosition, this->board);
                }
                else if (this->board->spaces[activatingPlayer.newPosition]->numUpgrades <= 4)
                {
                    rent = this->board->spaces[activatingPlayer.newPosition]->getRentWithHouse() * pow(2, this->board->spaces[activatingPlayer.newPosition]->numUpgrades - 1);
                }
                else
                {
                    rent = this->board->spaces[activatingPlayer.newPosition]->getRentWithHotel();
                }
                
                if (activatingPlayer.getCash() > (rent))
                {   
                    
                    std::cout << activatingPlayer.getName() << " paid " << this->board->spaces[activatingPlayer.newPosition]->getOwner().getName() << " $" << rent << " for landing on " << this->board->spaces[activatingPlayer.newPosition]->getName() << std::endl;
                    players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].pay(rent);
                    
                    
                    int w;
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].getName())
                            {
                                this->board->spaces[w]->playersOn[y]->pay(rent);
                                this->board->spaces[w]->playersOn[y]->increaseNetWorth( (rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                   
                    
                    
                    players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].increaseNetWorth( (rent));
                    activatingPlayer.charge( (rent));
                    
                    
                    
                    
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == activatingPlayer.getName())
                            {
                                this->board->spaces[w]->playersOn[y]->charge( (rent));
                                this->board->spaces[w]->playersOn[y]->decreaseNetWorth ((rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    activatingPlayer.decreaseNetWorth ((rent));
                }
                else
                {
                    while (sellUpgradesAvoidBankruptcyNoPrint(activatingPlayer, this->board, activatingPlayer.rulebook) != 0 && activatingPlayer.getCash() < rent)
                    {
                        std::cout << "You have $" << activatingPlayer.getCash() << " but you owe $" << rent << std::endl;
                        std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
                        int downgradeRevenue;
        downgradeRevenue = sellUpgradesAvoidBankruptcy(activatingPlayer, this->board, activatingPlayer.rulebook);
        int patar;

        activatingPlayer.pay(downgradeRevenue);
        
        for (patar = 0; patar < this->board->getNumSpaces(); patar++)
        {
            unsigned int douy;
                        
            for (douy = 0; douy < this->board->spaces[patar]->playersOn.size(); douy++)
            {
                if (this->board->spaces[patar]->playersOn[douy]->getName() == activatingPlayer.getName())
                    {
                        this->board->spaces[patar]->playersOn[douy]->pay(downgradeRevenue);
                        break;
                    }
            }
        }
                        //sellUpgradesAvoidBankruptcy(activatingPlayer, this->board, activatingPlayer.rulebook);
                    }
                    
                    //std::cout << activatingPlayer.getCash() << std::endl;
                    
                    if (activatingPlayer.getCash() < rent)
                    {
                    
                    
                    std::cout << activatingPlayer.getName() << " went bankrupt to " << this->board->spaces[activatingPlayer.newPosition]->getOwner().getName() << " for landing on " << this->board->spaces[activatingPlayer.newPosition]->getName() << std::endl;
                    activatingPlayer.isIn = false;
                    int w;
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == activatingPlayer.getName())
                            {
                                this->board->spaces[w]->playersOn[y]->isIn = false;
                                break;
                            }
                        }
                    }
                    players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].pay(activatingPlayer.getCash());
                    players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].increaseNetWorth(activatingPlayer.getNetWorth());
                    
            
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].getName())
                            {
                                this->board->spaces[w]->playersOn[y]->pay(activatingPlayer.getCash());
                                this->board->spaces[w]->playersOn[y]->increaseNetWorth( activatingPlayer.getNetWorth());
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    activatingPlayer.charge(activatingPlayer.getCash());
                    activatingPlayer.decreaseNetWorth(activatingPlayer.getNetWorth());
                    
                    
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == activatingPlayer.getName())
                            {
                                this->board->spaces[w]->playersOn[y]->charge( activatingPlayer.getCash());
                                this->board->spaces[w]->playersOn[y]->decreaseNetWorth (activatingPlayer.getNetWorth());
                                break;
                            }
                        }
                    }
                    
                    
                    
                    for (i = 1; i < this->board->getNumSpaces(); i++)
                    {
                        if (this->board->spaces[i]->getOwner().getName() == activatingPlayer.getName()) 
                        {
                            this->board->spaces[i]->setOwner(this->board->spaces[activatingPlayer.newPosition]->getOwner());
                        }
                    }
                    
                    game.decreaseNumPlayers();
                    }
                    else
                    {
                        std::cout << activatingPlayer.getName() << " paid " << this->board->spaces[activatingPlayer.newPosition]->getOwner().getName() << " $" << rent << " for landing on " << this->board->spaces[activatingPlayer.newPosition]->getName() << std::endl;
                    players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].pay(rent);
                    
                    
                    int w;
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].getName())
                            {
                                this->board->spaces[w]->playersOn[y]->pay(rent);
                                this->board->spaces[w]->playersOn[y]->increaseNetWorth( (rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                   
                    
                    
                    players[this->board->spaces[activatingPlayer.newPosition]->getOwner().getIndex()].increaseNetWorth( (rent));
                    activatingPlayer.charge( (rent));
                    
                    
                    
                    
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == activatingPlayer.getName())
                            {
                                this->board->spaces[w]->playersOn[y]->charge( (rent));
                                this->board->spaces[w]->playersOn[y]->decreaseNetWorth ((rent));
                                break;
                            }
                        }
                    }
                    
                    
                    
                    
                    
                    activatingPlayer.decreaseNetWorth ((rent));
                    }
                    
                    
                }
                
                
                
                
            }
            else
            {
                std::cout << activatingPlayer.getName() << ", you landed on " << this->board->spaces[activatingPlayer.newPosition]->getName() << " which you already own" << std::endl;// ____, you landed on ____ which you already own
            }
        }
        
        activatingPlayer.setCurrentPosition(activatingPlayer.getNewPosition());
        // MODIFY PLAYERSON FOR BOTH SPACES IN QUESTION
        unsigned int z;
        for(z = 0; z < this->board->spaces[activatingPlayer.newPosition]->playersOn.size(); z++){
            if(this->board->spaces[activatingPlayer.newPosition]->playersOn[z]->getIndex() > playerTurn){
                break;
            }
        }
        it = this->board->spaces[activatingPlayer.newPosition]->playersOn.begin();
        
        this->board->spaces[activatingPlayer.newPosition]->playersOn.insert(it+z, &(activatingPlayer));
}

//void Property::display() const
//{
    
//}

virtual int Property::getSalary() const
{
    return -1;
}