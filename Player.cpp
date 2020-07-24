//#include <string>
#include "Player.h"

//#include "Rules.h"
//#include "Board.h"

Player::Player(Rules* rulebook, int startCash, std::string name, int index) : currentPosition(0),newPosition(0),isIn(true),isInAuction(false), hasBet(false),  roll(0), rulebook(rulebook), cash(startCash), netWorth(startCash), name(name),  index(index) {

}

Player::Player() : rulebook(nullptr), name("None") {
    
}

    
int Player::getCash(){
    return cash;
}

int Player::getCurrentPosition(){
    return currentPosition;
}

int Player::getNewPosition(){
    return newPosition;
}

std::string Player::getName(){
    return name;
}
        
void Player::pay(int revenue){
    cash+=revenue;
}

void Player::charge(int loss){
    cash-=loss;
}

void Player::setCurrentPosition(int currentPosition1){
    currentPosition = currentPosition1;
}

void Player::setNewPosition(int newPosition1){
    newPosition = newPosition1;
}

void Player::increaseNetWorth(int amount)
{
    netWorth += amount;
}

void Player::decreaseNetWorth(int amount)
{
    netWorth -= amount;
}

int Player::getIndex(){
    return index;
}

int Player::getNetWorth(){
    return netWorth;
}



