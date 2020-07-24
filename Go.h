#include "Space.h"


class Go : public Space
{
    public:
        
        Go(Board* board, int index, std::string type, std::string name, int salary);
        
        virtual int getSalary() const;
        
        virtual void setOwner(const Player& player);
        
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
        
        virtual void activate(Player& activatingPlayer) override;
       // virtual void display() const override;
        
    private:
    
        int salary;
};