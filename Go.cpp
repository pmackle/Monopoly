#include "Go.h"

Go::Go(Board* board, int index, std::string type, std::string name, int salary) : Space(board, index, type, name), salary(salary)
{
    
}

virtual int Go::getSetID() const{}

        virtual int getIntrasetID() const{return -1;}
        virtual std::string getName() const{return -1;}
        virtual int getPropertyCost() const{return -1;}
        virtual int getHouseCost() const{return -1;}
        virtual int getHotelCost() const{return -1;}
        virtual int getRent() const{return -1;}
        virtual int getRentWithHouse() const{return -1;}
        virtual int getRentWithHotel() const{return -1;}
        virtual Player& getOwner(){
                Player none;
                return none;
        }
        virtual void setOwner(const Player& player){}

int Go::getSalary() const
{
    return salary;
}

virtual void Go::activate(Player& activatingPlayer)
{
    activatingPlayer.pay(((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) - 1) / this->board->getNumSpaces()) * ActivatingPlayer->board->spaces[0]->getSalary() + activatingPlayer.rulebook->getSalaryMultiplier() * this->board->spaces[0]->getSalary()));
    activatingPlayer.increaseNetWorth(((((activatingPlayer.getCurrentPosition() + activatingPlayer.roll) - 1) / this->board->getNumSpaces()) * this->board->spaces[0]->getSalary() + activatingPlayer.rulebook->getSalaryMultiplier() * this->board->spaces[0]->getSalary()));
    
    activatingPlayer.setCurrentPosition(activatingPlayer.getNewPosition());
        // MODIFY PLAYERSON FOR BOTH SPACES IN QUESTION
        unsigned int z;
        for(z = 0; z < this->board.spaces[players[playerTurn].newPosition]->playersOn.size(); z++){
            if(this->board.spaces[activatingPlayer.newPosition]->playersOn[z]->getIndex() > playerTurn){
                break;
            }
        }
        it = board.spaces[activatingPlayer..newPosition]->playersOn.begin();
        
        board.spaces[activatingPlayer.newPosition]->playersOn.insert(it+z, &(activatingPlayer));
}

//virtual void display() const
//{
//    
//}