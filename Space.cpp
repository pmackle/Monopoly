#include <ios>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Space.h"
#include "Board.h"

Space::Space(Board* board, int index, std::string type, std::string name) : board(board), upgrades(""),  numUpgrades(0), moneyFreeParking(0), index(index), type(type), name(name)
{
    
}

int Space::getIndex() const
{
    return index;
}

std::string Space::getType() const
{
    return type;
}

std::string Space::getName() const
{
    return name;
}

//void Space::display() const
//{
    
//}

Property::Property(int index, std::string type, std::string name, int setID, int intrasetID, int propertyCost, int houseCost,
                   int hotelCost, int rent, int rentWithHouse, int rentWithHotel, Board* board) : Space(board, index, type, name),
                                                                                    setID(setID), intrasetID(intrasetID),
                                                                                    propertyCost(propertyCost), houseCost(houseCost),
                                                                                    hotelCost(hotelCost), rent(rent), rentWithHouse(rentWithHouse),
                                                                                    rentWithHotel(rentWithHotel)
{
        
        owner = new Player;

}

int Property::rentMult(Player& player)
{
    std::string newOwner = this->board->spaces[player.newPosition]->getOwner()->getName();
    int newSetID = this->board->spaces[player.newPosition]->getSetID();
    int i;
    
    for(i = 1; i < board->getNumSpaces(); i++){
        if(this->board->spaces[i]->getSetID() == newSetID){
            break;
        }
    }
    
        while((i < this->board->getNumSpaces()) && (this->board->spaces[i]->getSetID() == newSetID)){
            if (this->board->spaces[i]->getOwner()->getName() != newOwner){
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
            
            if(this->board->spaces[inOrder[j]]->getOwner()->getName() != player.getName()){
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
            
            if(this->board->spaces[inOrder[j]]->getOwner()->getName() != player.getName()){
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

Player* Property::getOwner()
{
    return owner;
}

void Property::setOwner(Player& player)
{
    owner = &player;
}

void Property::activate(Player& activatingPlayer)
{
    
    activatingPlayer.pay((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) / this->board->getNumSpaces()) * this->board->spaces[0]->getSalary()));
            activatingPlayer.increaseNetWorth((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) / this->board->getNumSpaces()) * this->board->spaces[0]->getSalary()));
            
            if (this->board->spaces[activatingPlayer.getNewPosition()]->getOwner()->getName() == "None")
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
                          AuctionProperties(activatingPlayer.newPosition);
                       }
                    }
                
                
                
                }
                else
                {
                    std::cout << activatingPlayer.getName() << ", you don't have enough money to afford " << this->board->spaces[activatingPlayer.newPosition]->getName() << "." << std::endl;
                    std::cout << this->board->spaces[activatingPlayer.newPosition]->getName() << " costs $" << this->board->spaces[activatingPlayer.newPosition]->getPropertyCost() << " but you only have $" << activatingPlayer.getCash() << std::endl;
                   if(activatingPlayer.rulebook->getAuctionProperties()){
                            AuctionProperties(activatingPlayer.newPosition);
                        }
                }
            }
            
            
            else if (this->board->spaces[activatingPlayer.newPosition]->getOwner()->getName() != activatingPlayer.getName())
            {
                
                
                int rent;
                
                if (this->board->spaces[activatingPlayer.newPosition]->numUpgrades == 0)
                {
                   
                    rent = (this->board->spaces[activatingPlayer.newPosition]->getRent()) * rentMult(activatingPlayer);
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
                    
                    
                    std::cout << activatingPlayer.getName() << " paid " << this->board->spaces[activatingPlayer.newPosition]->getOwner()->getName() << " $" << rent << " for landing on " << this->board->spaces[activatingPlayer.newPosition]->getName() << std::endl;
                    this->getOwner()->pay(rent);
                    
                    
                   /* int w;
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == this->getOwner()->getName())
                            {
                                this->board->spaces[w]->playersOn[y]->pay(rent);
                                this->board->spaces[w]->playersOn[y]->increaseNetWorth( (rent));
                                break;
                            }
                        }
                    }*/
                    
                    
                    
                    
                   
                    
                    
                    this->getOwner()->increaseNetWorth( (rent));
                    activatingPlayer.charge( (rent));
                    
                    
                    
                    
                    /*for (w = 0; w < this->board->getNumSpaces(); w++)
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
                    }*/
                    
                    
                    
                    
                    
                    activatingPlayer.decreaseNetWorth ((rent));
                }
                else
                {
                    while (sellUpgradesAvoidBankruptcyNoPrint(activatingPlayer) != 0 && activatingPlayer.getCash() < rent)
                    {
                        std::cout << "You have $" << activatingPlayer.getCash() << " but you owe $" << rent << std::endl;
                        std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
                        int downgradeRevenue;
        downgradeRevenue = sellUpgradesAvoidBankruptcy(activatingPlayer);
        //int patar;

        activatingPlayer.pay(downgradeRevenue);
        /*
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
        }*/
                        //sellUpgradesAvoidBankruptcy(activatingPlayer, this->board, activatingPlayer.rulebook);
                    }
                    
                    //std::cout << activatingPlayer.getCash() << std::endl;
                    
                    if (activatingPlayer.getCash() < rent)
                    {
                    
                    
                    std::cout << activatingPlayer.getName() << " went bankrupt to " << this->board->spaces[activatingPlayer.newPosition]->getOwner()->getName() << " for landing on " << this->board->spaces[activatingPlayer.newPosition]->getName() << std::endl;
                    activatingPlayer.isIn = false;
                    /*int w;
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
                    }*/
                    this->getOwner()->pay(activatingPlayer.getCash());
                    this->getOwner()->increaseNetWorth(activatingPlayer.getNetWorth());
                    
            /*
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == this->getOwner()->getName())
                            {
                                this->board->spaces[w]->playersOn[y]->pay(activatingPlayer.getCash());
                                this->board->spaces[w]->playersOn[y]->increaseNetWorth( activatingPlayer.getNetWorth());
                                break;
                            }
                        }
                    }*/
                    
                    
                    
                    
                    
                    activatingPlayer.charge(activatingPlayer.getCash());
                    activatingPlayer.decreaseNetWorth(activatingPlayer.getNetWorth());
                    
                    /*
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
                        }*/
                  //  }
                    
                    
                    int i;
                    for (i = 1; i < this->board->getNumSpaces(); i++)
                    {
                        if (this->board->spaces[i]->getOwner()->getName() == activatingPlayer.getName()) 
                        {
                            this->board->spaces[i]->setOwner(*(this->board->spaces[activatingPlayer.newPosition]->getOwner()));
                        }
                    }
                    
                    activatingPlayer.rulebook -> numPlayersLeftInGame -= 1;
                    }
                    else
                    {
                        std::cout << activatingPlayer.getName() << " paid " << this->board->spaces[activatingPlayer.newPosition]->getOwner()->getName() << " $" << rent << " for landing on " << this->board->spaces[activatingPlayer.newPosition]->getName() << std::endl;
                    this->getOwner()->pay(rent);
                    
                    
                    /*int w;
                    for (w = 0; w < this->board->getNumSpaces(); w++)
                    {
                        unsigned int y;
                        
                        for (y = 0; y < this->board->spaces[w]->playersOn.size(); y++)
                        {
                            if (this->board->spaces[w]->playersOn[y]->getName() == this->getOwner()->getName())
                            {
                                this->board->spaces[w]->playersOn[y]->pay(rent);
                                this->board->spaces[w]->playersOn[y]->increaseNetWorth( (rent));
                                break;
                            }
                        }
                    }*/
                    
                    
                    
                    
                   
                    
                    
                    this->getOwner()->increaseNetWorth( (rent));
                    activatingPlayer.charge( (rent));
                    
                    
                    
                    /*
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
                    }*/
                    
                    
                    
                    
                    
                    activatingPlayer.decreaseNetWorth ((rent));
                    }
                    
                    
                }
                
                
                
                
            }
            else
            {
                std::cout << activatingPlayer.getName() << ", you landed on " << this->board->spaces[activatingPlayer.newPosition]->getName() << " which you already own" << std::endl;// ____, you landed on ____ which you already own
            }
        
        
        activatingPlayer.setCurrentPosition(activatingPlayer.getNewPosition());
        // MODIFY PLAYERSON FOR BOTH SPACES IN QUESTION
        unsigned int z;
        for(z = 0; z < this->board->spaces[activatingPlayer.newPosition]->playersOn.size(); z++){
            if(this->board->spaces[activatingPlayer.newPosition]->playersOn[z]->getIndex() > activatingPlayer.getIndex()){
                break;
            }
        }
        std::vector<Player*>::iterator it = this->board->spaces[activatingPlayer.newPosition]->playersOn.begin();
        this->board->spaces[activatingPlayer.newPosition]->playersOn.insert(it+z, &(activatingPlayer));
}

//void Property::display() const
//{
    
//}

int Property::getSalary() const
{
    return -1;
}

Go::Go(Board* board, int index, std::string type, std::string name, int salary) : Space(board, index, type, name), salary(salary)
{
    Player none;
    owner = &none;
}

int Go::getSetID() const{return -1;}

        int Go::getIntrasetID() const{return -1;}
         
         
         
         int Go::getPropertyCost() const{return -1;}
         int Go::getHouseCost() const{return -1;}
         int Go::getHotelCost() const{return -1;}
         int Go::getRent() const{return -1;}
         int Go::getRentWithHouse() const{return -1;}
         int Go::getRentWithHotel() const{return -1;}
         Player* Go::getOwner(){
                //Player none;
                return owner;
        }
         void Go::setOwner( Player& player){}

int Go::getSalary() const
{
    return salary;
}

int FreeParking::getSetID() const{return -1;}

        int FreeParking::getIntrasetID() const{return -1;}
         
         
         
         int FreeParking::getPropertyCost() const{return -1;}
         int FreeParking::getHouseCost() const{return -1;}
         int FreeParking::getHotelCost() const{return -1;}
         int FreeParking::getRent() const{return -1;}
         int FreeParking::getRentWithHouse() const{return -1;}
         int FreeParking::getRentWithHotel() const{return -1;}
         Player* FreeParking::getOwner(){
                //Player none;
                return owner;
        }
         void FreeParking::setOwner( Player& player){}
         
         FreeParking::FreeParking(Board* board, int index, std::string type, std::string name) : Space(board, index,  type,  name)
         {
             Player none;
    owner = &none;
         }
         
         int PayToBank::getSetID() const{return -1;}

        int PayToBank::getIntrasetID() const{return -1;}
         
void PayToBank::display()
{
     unsigned int isInCount;
    std::cout << std::setw(25) << std::left << this->getIndex() << " | ";
        std::cout << std::setw(25) << std::left << this->getName() << " | ";
        std::cout << std::setw(25) << std::left << "None" << " | ";
        std::cout << std::setw(25) << std::left << this->upgrades << " | ";
        
        unsigned int j;
        isInCount = 0;
        for (j = 0; j < this->playersOn.size(); j++)
        {
            if (this->playersOn[j]->isIn == true)
            {
                isInCount++;
                if(isInCount == 1)
                {
                    std::cout << "[" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
                else
                {
                    std::cout << ", [" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
            }
        }
            

            std::cout << std::endl;
            
        
}
 
 
void FreeParking::display()
{
     unsigned int isInCount;
    std::cout << std::setw(25) << std::left << this->getIndex() << " | ";
        std::cout << std::setw(25) << std::left << this->getName() << " | ";
        std::cout << std::setw(25) << std::left << "None" << " | ";
        std::cout << std::setw(25) << std::left << this->upgrades << " | ";
        
        unsigned int j;
        isInCount = 0;
        for (j = 0; j < this->playersOn.size(); j++)
        {
            if (this->playersOn[j]->isIn == true)
            {
                isInCount++;
                if(isInCount == 1)
                {
                    std::cout << "[" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
                else
                {
                    std::cout << ", [" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
            }
        }
            

            std::cout << std::endl;
}        

void PayToBank::activate(Player& activatingPlayer)
{
        if (activatingPlayer.getCash() < amount)
        {
            std::cout << activatingPlayer.getName() << " went bankrupt by landing on " << this->getName() << std::endl;
            activatingPlayer.charge(activatingPlayer.getCash());
            activatingPlayer.decreaseNetWorth(activatingPlayer.getCash());
            activatingPlayer.isIn = false;
            activatingPlayer.rulebook -> numPlayersLeftInGame -= 1;
        }
        else
        {
            std::cout << activatingPlayer.getName() << " paid the bank $" << amount << " for landing on " << this->getName() << std::endl;
            activatingPlayer.charge(amount);
            activatingPlayer.decreaseNetWorth(amount);
        }
    
    
        activatingPlayer.setCurrentPosition(activatingPlayer.getNewPosition());
        // MODIFY PLAYERSON FOR BOTH SPACES IN QUESTION
        unsigned int z;
        for(z = 0; z < this->playersOn.size(); z++){
            if(this->playersOn[z]->getIndex() > activatingPlayer.getIndex()){
                break;
            }
        }
        std::vector<Player*>::iterator it = this->playersOn.begin();

        this->playersOn.insert(it+z, &(activatingPlayer));
}

void FreeParking::activate(Player& activatingPlayer)
{
    activatingPlayer.pay(moneyFreeParking);
    activatingPlayer.increaseNetWorth(moneyFreeParking);
    moneyFreeParking = 0;
    
    activatingPlayer.setCurrentPosition(activatingPlayer.getNewPosition());
        // MODIFY PLAYERSON FOR BOTH SPACES IN QUESTION
        unsigned int z;
        for(z = 0; z < this->playersOn.size(); z++){
            if(this->playersOn[z]->getIndex() > activatingPlayer.getIndex()){
                break;
            }
        }
        std::vector<Player*>::iterator it = this->playersOn.begin();

        this->playersOn.insert(it+z, &(activatingPlayer));
}

         int PayToBank::getPropertyCost() const{return -1;}
         int PayToBank::getHouseCost() const{return -1;}
         int PayToBank::getHotelCost() const{return -1;}
         int PayToBank::getRent() const{return -1;}
         int PayToBank::getRentWithHouse() const{return -1;}
         int PayToBank::getRentWithHotel() const{return -1;}
         Player* PayToBank::getOwner(){
                //Player none;
                return owner;
        }
         void PayToBank::setOwner( Player& player){}
         
         PayToBank::PayToBank(Board* board, int index, std::string type, std::string name, int amount) : Space(board,  index,  type,  name) , amount(amount)
         {
             Player none;
    owner = &none;
         }
         
int PayToBank::getSalary() const
{
    return -1;
}
int FreeParking::getSalary() const
{
    return -1;
}

void Go::activate(Player& activatingPlayer)
{
    activatingPlayer.pay(((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) - 1) / this->board->getNumSpaces()) * this->board->spaces[0]->getSalary() + activatingPlayer.rulebook->getSalaryMultiplier() * this->board->spaces[0]->getSalary()));
    activatingPlayer.increaseNetWorth(((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) - 1) / this->board->getNumSpaces()) * this->board->spaces[0]->getSalary() + activatingPlayer.rulebook->getSalaryMultiplier() * this->board->spaces[0]->getSalary()));
    
    activatingPlayer.setCurrentPosition(activatingPlayer.getNewPosition());
        // MODIFY PLAYERSON FOR BOTH SPACES IN QUESTION
        unsigned int z;
        for(z = 0; z < this->playersOn.size(); z++){
            if(this->playersOn[z]->getIndex() > activatingPlayer.getIndex()){
                break;
            }
        }
        std::vector<Player*>::iterator it = this->playersOn.begin();

        this->playersOn.insert(it+z, &(activatingPlayer));
}

void Property::display() 
{
 //   unsigned int i = 0;
    unsigned int isInCount;
    std::cout << std::setw(25) << std::left << this->getIndex() << " | ";
        std::cout << std::setw(25) << std::left << this->getName() << " | ";
        std::cout << std::setw(25) << std::left << this->getOwner()->getName() << " | ";
        std::cout << std::setw(25) << std::left << this->upgrades << " | ";
        
        unsigned int j;
        isInCount = 0;
        for (j = 0; j < this->playersOn.size(); j++)
        {
            if (this->playersOn[j]->isIn == true)
            {
                isInCount++;
                if(isInCount == 1)
                {
                    std::cout << "[" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
                else
                {
                    std::cout << ", [" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
            }
        }
            

            std::cout << std::endl;
}

void Go::display() 
{
    //unsigned int i = 0;
    unsigned int isInCount;
    std::cout << std::setw(25) << std::left << this->getIndex() << " | ";
        std::cout << std::setw(25) << std::left << this->getName() << " | ";
        std::cout << std::setw(25) << std::left << "None" << " | ";
        std::cout << std::setw(25) << std::left << this->upgrades << " | ";
        
        unsigned int j;
        isInCount = 0;
        for (j = 0; j < this->playersOn.size(); j++)
        {
            if (this->playersOn[j]->isIn == true)
            {
                isInCount++;
                if(isInCount == 1)
                {
                    std::cout << "[" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
                else
                {
                    std::cout << ", [" << this->playersOn[j]->getName() << " : $" << this->playersOn[j]->getCash() << "]";
                }
            }
        }
            

            std::cout << std::endl;
}

void Property::AuctionProperties(int newPosition){
    int numPlayersInAuction = 0;
    unsigned int ss;
    std::string highestBidder = "";
    int highestBid = 0;

    std::cout << "Starting the auction for " << this->board->spaces[newPosition]->getName() << std::endl;
    for(ss = 0; ss < this->board->players->size(); ss++){
        if((*(this->board->players))[ss].isIn){
            numPlayersInAuction++;
            (*(this->board->players))[ss].isInAuction = true;
        }
    }
    while(numPlayersInAuction > 1){
        for(ss = 0; ss < this->board->players->size(); ss++){
            if((*(this->board->players))[ss].isInAuction && (numPlayersInAuction > 1 || !(*(this->board->players))[ss].hasBet)){
                if((*(this->board->players))[ss].getCash() > highestBid){
                    
                    if(highestBidder == ""){
                        std::cout << "No one has bid on " << this->board->spaces[newPosition]->getName() << " [$" << this->board->spaces[newPosition]->getPropertyCost() << "] yet" << std::endl;
                    }
                    else{
                        std::cout << "The current bid for " << this->board->spaces[newPosition]->getName() << " [$" << this->board->spaces[newPosition]->getPropertyCost() << "] is $" << highestBid << " by " << highestBidder << std::endl;
                    }
                    
                    int playerBid;
                    std::cout << (*(this->board->players))[ss].getName() << ", enter a bid of at least $" << (highestBid + 1) << " to bid on the property or a value less than that to leave the auction" << std::endl;
                    std::cout << "Your bid: ";
                    
                    std::cin >> playerBid;
                    if (playerBid > highestBid){
                        highestBid = playerBid;
                        highestBidder = (*(this->board->players))[ss].getName();
                        (*(this->board->players))[ss].hasBet = true;
                    }
                    else{
                        (*(this->board->players))[ss].isInAuction = false;
                        numPlayersInAuction--;
                    }
                }
                
                else{
                        (*(this->board->players))[ss].isInAuction = false;
                        numPlayersInAuction--;
                }
            }
        }
        
        if(highestBidder == ""){
            std::cout << "No one decided to purchase " << this->board->spaces[newPosition]->getName() << std::endl;
        }
        
        
    }
    //unsigned int pp;
    for(ss = 0; ss < this->board->players->size(); ss++){
            if((*(this->board->players))[ss].getName() == highestBidder){
                (*(this->board->players))[ss].charge(highestBid);
                this->board->spaces[newPosition]->setOwner((*(this->board->players))[ss]);
                std::cout << (*(this->board->players))[ss].getName() << " won " << this->board->spaces[newPosition]->getName() << " for $" << highestBid << std::endl;
                /*for(pp = 0; pp < this->board->spaces.size(); pp++){
                    unsigned int qq;
                    for(qq = 0; qq < this->board->spaces[pp]->playersOn.size(); qq++){
                        if(this->board->spaces[pp]->playersOn[qq]->getName() == highestBidder){
                            this->board->spaces[pp]->playersOn[qq]->charge(highestBid);
                            break;
                        }
                    }
                }*/
                break;
            }
        }
}

Property::~Property()
{
    //delete owner;
}