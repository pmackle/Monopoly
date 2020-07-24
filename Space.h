#ifndef CPPHOARDING_SPACE_H
#define CPPHOARDING_SPACE_H

#include <string>
#include <vector>
#include "Player.h"
//#include "Board.h"
class Board;

class Space
{
    
    public:
    
        Space(Board* board, int index, std::string type, std::string name);
        
        int getIndex() const;
        std::string getType() const;
        std::string getName() const;
        
        virtual void activate(Player& activatingPlayer) = 0;
        virtual void display()  = 0;
        
        std::vector<Player*> playersOn;
        
        virtual int getSetID() const = 0;
        virtual int getIntrasetID() const = 0;
        
        virtual int getPropertyCost() const = 0;
        virtual int getHouseCost() const = 0;
        virtual int getHotelCost() const = 0;
        virtual int getRent() const = 0;
        virtual int getRentWithHouse() const = 0;
        virtual int getRentWithHotel() const = 0;
        virtual Player* getOwner() = 0;
        virtual void setOwner(Player& player) = 0;;
        
        virtual int getSalary() const = 0;
        
        
        
        Board* board;
        
        std::string upgrades;
        int numUpgrades;
        int moneyFreeParking;
    
    protected:

        int index;
        std::string type;
        std::string name;
    
    
};

class Property : public Space
{
    public:
    
        Property(int index, std::string type, std::string name, int setID,
                 int intrasetID, int propertyCost, int houseCost, int hotelCost,
                 int rent, int rentWithHouse, int rentWithHotel, Board* board);
        
        void AuctionProperties(int newPosition);
//int buyUpgrade(Player& player, Board& board, const Rules& rulebook);
        int sellUpgradesAvoidBankruptcy(Player& player);
        int sellUpgradesAvoidBankruptcyNoPrint(Player& player);
        int rentMult(Player& player);
        
        
        
        virtual int getSetID() const;
        virtual int getIntrasetID() const;
        //virtual std::string getName() const;
        virtual int getPropertyCost() const;
        virtual int getHouseCost() const;
        virtual int getHotelCost() const;
        virtual int getRent() const;
        virtual int getRentWithHouse() const;
        virtual int getRentWithHotel() const;
        virtual Player* getOwner();
        
        virtual int getSalary() const;
        
        virtual void activate(Player& activatingPlayer) override;
        virtual void display()  override;
        virtual void setOwner(Player& player);
        virtual ~Property();
        
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
        Player* owner;
};

class Go : public Space
{
    public:
        
        Go(Board* board, int index, std::string type, std::string name, int salary);
        
       
        
        virtual int getSalary() const;
        
        virtual void setOwner(Player& player);
        
        virtual int getSetID() const;
        virtual int getIntrasetID() const;
        //virtual std::string getName() const;
        virtual int getPropertyCost() const;
        virtual int getHouseCost() const;
        virtual int getHotelCost() const;
        virtual int getRent() const;
        virtual int getRentWithHouse() const;
        virtual int getRentWithHotel() const;
        virtual Player* getOwner();
        
        virtual void activate(Player& activatingPlayer) override;
       virtual void display()  override;
        
    private:
        
        Player* owner;
        int salary;
};

class FreeParking : public Space
{
    public:
    
        FreeParking(Board* board, int index, std::string type, std::string name);
        
        virtual int getSalary() const;
        
        
        
        
        virtual void setOwner(Player& player);
        
        virtual int getSetID() const;
        virtual int getIntrasetID() const;
        //virtual std::string getName() const;
        virtual int getPropertyCost() const;
        virtual int getHouseCost() const;
        virtual int getHotelCost() const;
        virtual int getRent() const;
        virtual int getRentWithHouse() const;
        virtual int getRentWithHotel() const;
        virtual Player* getOwner();
        
        virtual void activate(Player& activatingPlayer) override;
        virtual void display() override;
        
    private:
    
        Player* owner;
    
    
};

class PayToBank : public Space
{
    public:
    
        PayToBank(Board* board, int index, std::string type, std::string name, int amount);
        int amount;
        
        virtual int getSalary() const;
        
        virtual void setOwner(Player& player);
        
        virtual int getSetID() const;
        virtual int getIntrasetID() const;
        //virtual std::string getName() const;
        virtual int getPropertyCost() const;
        virtual int getHouseCost() const;
        virtual int getHotelCost() const;
        virtual int getRent() const;
        virtual int getRentWithHouse() const;
        virtual int getRentWithHotel() const;
        virtual Player* getOwner();
        
        virtual void activate(Player& activatingPlayer) override;
        virtual void display()  override;
        
    private:
    
        Player* owner;
        
};

#endif //CPPHOARDING_SPACE_H