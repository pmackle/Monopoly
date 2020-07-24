hoarding.out : main.o Player.o Space.o Board.o Rules.o DiceRoller.o play.o Gamestate.o
	g++-5 --std=c++14 -g -Wall -Werror -o hoarding.out main.o Player.o Space.o Board.o Rules.o DiceRoller.o play.o Gamestate.o
	
main.o : main.cpp play.h 
	g++-5 --std=c++14 -g -c -Wall -Werror main.cpp
	
Player.o : Player.cpp Player.h
	g++-5 --std=c++14 -g -c -Wall -Werror Player.cpp	

Space.o : Space.cpp Space.h Board.h
	g++-5 --std=c++14 -g -c -Wall -Werror Space.cpp

Board.o : Board.cpp Board.h
	g++-5 --std=c++14 -g -c -Wall -Werror Board.cpp
	
play.o : play.cpp play.h DiceRoller.h Space.h Gamestate.h
	g++-5 --std=c++14 -g -c -Wall -Werror play.cpp

Rules.o : Rules.cpp Rules.h
	g++-5 --std=c++14 -g -c -Wall -Werror Rules.cpp

DiceRoller.o : DiceRoller.cpp DiceRoller.h
	g++-5 --std=c++14 -g -c -Wall -Werror DiceRoller.cpp
	
Gamestate.o : Gamestate.cpp Gamestate.h
	g++-5 --std=c++14 -g -c -Wall -Werror Gamestate.cpp
	
clean :
	rm -fr *.o *.out