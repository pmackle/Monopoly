#ifndef CPPHOARDING_PROPERTY_H
#define CPPHOARDING_PROPERTY_H

#include <string>
//#include "Player.h"
#include "Space.h"

class Property : public Space
{
    public:
    
        Property(int index, std::string type, std::string name, int setID,
                 int intrasetID, int propertyCost, int houseCost, int hotelCost,
                 int rent, int rentWithHouse, int rentWithHotel, Board* board);
        
        void AuctionProperties(std::vector <Player>& players, Board& board, int newPosition);
//int buyUpgrade(Player& player, Board& board, const Rules& rulebook);
int sellUpgradesAvoidBankruptcy(Player& player, Board& board, const Rules& rulebook);
        int sellUpgradesAvoidBankruptcyNoPrint(Player& player, Board& board, const Rules& rulebook);
        int rentMult(const Rules& rulebook, int newPosition, Board& board);
        
        virtual int getSetID() const;
        virtual int getIntrasetID() const;
        virtual std::string getName() const;
        virtual int getPropertyCost() const;
        virtual int getHouseCost() const;
        virtual int getHotelCost() const;
        virtual int getRent() const;
        virtual int getRentWithHouse() const;
        virtual int getRentWithHotel() const;
        virtual Player& getOwner();
        
        virtual int getSalary() const;
        
        virtual void activate(Player& activatingPlayer) override;
     //   virtual void display() override;
        virtual void setOwner(const Player& player);
        
        //std::string upgrades;
        //int numUpgrades;
        
    private:
    
        int setID;
        int intrasetID;
        int propertyCost;
        int houseCost;
        int hotelCost;
        int rent;
        int rentWithHouse;
        int rentWithHotel;
        Player owner;
};

#endif //CPPHOARDING_PROPERTY_H