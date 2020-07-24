#ifndef CPPHOARDING_BOARD_H
#define CPPHOARDING_BOARD_H

#include <string>
#include <memory>
#include <vector>
#include "Space.h"
//#include "Player.h"

//class Space;

class Board
{
    public:
        Board(std::string boardFile);
        
        int getNumSpaces() const;
        std::vector< std::unique_ptr<Space> > spaces;
        std::vector<Player>* players;
        void print();
        
        virtual ~Board();
    
    private:
        unsigned int numSpaces;
        
};

#endif  //CPPHOARDING_BOARD_H