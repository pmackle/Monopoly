#include <iostream>
#include <fstream>
#include <ios>
#include <iomanip>
//#include "Property.h"
//#include "Space.h"
#include "Board.h"
//#include "Go.h"


Board::Board(std::string boardFile)
{
    std::ifstream read;
    
    read.open(boardFile);
    
    char ignoreChar;
    do
    {
        ignoreChar = read.get();
    }
    while (ignoreChar != ',');
    
    read >> numSpaces;
    
    std::string ignoreLine;
    getline(read, ignoreLine);
    getline(read, ignoreLine);
    getline(read, ignoreLine);
    getline(read, ignoreLine);
    
    std::string type = "", name = "";
    
    do
    {
        ignoreChar = read.get();
        type.push_back(ignoreChar);
    }
    while (ignoreChar != ',');
    type.pop_back();
    
    int salary;
    read >> salary;
    
    ignoreChar = read.get();
    
    
    do
    {
        ignoreChar = read.get();
        name.push_back(ignoreChar);
    }
    while (ignoreChar != ',');
    name.pop_back();
    
    
    
    std::unique_ptr<Space> go = std::make_unique<Go>(this, 0, type, name, salary);
    spaces.push_back(std::move(go));
    
    getline(read, ignoreLine);
    
    unsigned int i;
    int setID, intrasetID, propertyCost, houseCost, hotelCost, rent, rentWithHouse, rentWithHotel, amount;
    //std::string type, name;
    for (i = 1; i < numSpaces; i++)
    {
        type = "";
        name = "";
        //int setID, intrasetID, propertyCost, houseCost, hotelCost, rent, rentWithHouse, rentWithHotel;
        
        do
        {
            ignoreChar = read.get();
            type.push_back(ignoreChar);
        }
        while (ignoreChar != ',');
        type.pop_back();
        
    if (type == "Property")
    {    
        read >> setID;
        ignoreChar = read.get();
        read >> intrasetID;
        ignoreChar = read.get();
        
        do
        {
            ignoreChar = read.get();
            name.push_back(ignoreChar);
        }
        while (ignoreChar != ',');
        name.pop_back();
        
        read >> propertyCost;
        ignoreChar = read.get();
        read >> houseCost;
        ignoreChar = read.get();
        read >> hotelCost;
        ignoreChar = read.get();
        read >> rent;
        ignoreChar = read.get();
        read >> rentWithHouse;
        ignoreChar = read.get();
        read >> rentWithHotel;
        ignoreChar = read.get();
        ignoreChar = read.get();
        
        
        spaces.push_back(std::make_unique<Property>(i, type, name, setID, intrasetID, propertyCost, houseCost, hotelCost, rent, rentWithHouse, rentWithHotel, this));
    }
    else if (type == "Pay")
    {
        do
        {
            ignoreChar = read.get();
            name.push_back(ignoreChar);
        }
        while (ignoreChar != ',');
        name.pop_back();
        
        read >> amount;
        
        spaces.push_back(std::make_unique<PayToBank>(this, i, type, name, amount));
    }
    else
    {
        do
        {
            ignoreChar = read.get();
            name.push_back(ignoreChar);
        }
        while (ignoreChar != ',');
        name.pop_back();
        
        spaces.push_back(std::make_unique<FreeParking>(this, i, type, name));
    }
    }
    
    read.close();
}

int Board::getNumSpaces() const
{
    return numSpaces;
}

/*std::vector<Space>& Board::getSpaces()
{
    return spaces;
}*/

void Board::print()
{//print everything to 25 spaces
    
    
    std::cout << std::setw(25) << std::left  << "Space Number" << " | ";
    std::cout << std::setw(25) << std::left  << "Space Name" << " | ";
    std::cout << std::setw(25) << std::left  << "Owner" << " | ";
    std::cout << std::setw(25) << std::left  << "Upgrades" << " | ";
    std::cout << "Players" << std::endl;
    
    
    unsigned int i;
    for (i = 0; i < numSpaces; i++)
    {
        spaces[i]->display();
    }
    /*
    
    unsigned int i = 0;
    unsigned int isInCount;
    std::cout << std::setw(25) << std::left << i << " | ";
        std::cout << std::setw(25) << std::left << spaces[i]->getName() << " | ";
        std::cout << std::setw(25) << std::left << "None" << " | ";
        std::cout << std::setw(25) << std::left << spaces[i]->upgrades << " | ";
        
        unsigned int j;
        isInCount = 0;
        for (j = 0; j < spaces[i]->playersOn.size(); j++)
        {
            if (spaces[i]->playersOn[j]->isIn == true)
            {
                isInCount++;
                if(isInCount == 1)
                {
                    std::cout << "[" << spaces[i]->playersOn[j]->getName() << " : $" << spaces[i]->playersOn[j]->getCash() << "]";
                }
                else
                {
                    std::cout << ", [" << spaces[i]->playersOn[j]->getName() << " : $" << spaces[i]->playersOn[j]->getCash() << "]";
                }
            }
        }
            

            std::cout << std::endl;
    
    //unsigned int i;
    
    
    for(i = 1; i < numSpaces; i++){
        
        std::cout << std::setw(25) << std::left << i << " | ";
        std::cout << std::setw(25) << std::left << spaces[i]->getName() << " | ";
        std::cout << std::setw(25) << std::left << spaces[i]->getOwner()->getName() << " | ";
        std::cout << std::setw(25) << std::left << spaces[i]->upgrades << " | ";
        
        unsigned int j;
        isInCount = 0;
        for (j = 0; j < spaces[i]->playersOn.size(); j++)
        {
            if (spaces[i]->playersOn[j]->isIn == true)
            {
                isInCount++;
                if(isInCount == 1)
                {
                    std::cout << "[" << spaces[i]->playersOn[j]->getName() << " : $" << spaces[i]->playersOn[j]->getCash() << "]";
                }
                else
                {
                    std::cout << ", [" << spaces[i]->playersOn[j]->getName() << " : $" << spaces[i]->playersOn[j]->getCash() << "]";
                }
            }
        }
            

            std::cout << std::endl;
    }
    
    */
        
}

Board::~Board()
{
    unsigned int i;
    
    for (i = 0; i < numSpaces; i++)
    {
        spaces[i].reset();
    }
    
}


// make
// ./cpp_hoarding.out ../CHoarding/Oracle/Rules/CampusRules.txt ../CHoarding/Oracle/Boards/CampusBoard.csv ../CHoarding/Oracle/RandomFiles/RandomNums10000.txt