# Monopoly
Text-based multiplayer monopoly game written with Dhruva Eswar for Matt Butner's ECS 36B course in Winter 2018. Includes adjustable boards, rules, and more.

Board.cpp - Reads the board file for hotel cost, rent, type, properties/spaces, etc.
DiceRoller.cpp - As the name implies.
Gamestate.cpp - Operates like a finite state machine. Helps organize.
Go.cpp - For passing go or landing on a space, really wishing we had more damn comments here. Rookie mistake for a first big project.
main.cpp - Self explanatory. Takes in textfile of rules/properties.
play.cpp - Our monolith of code. Does most of the actual actions and calling to other .cpp files.
Player.cpp - Player object with cash, current poisition, name, and actions.
Property.cpp - Properties of properties, including rent, amount of hotels, owner, etc.
Rules.cpp - Reads the rules file for if there should be a salary multiplier, getting money when landing on free parking, turn limit, etc.
Space.cpp - Another monolith of code. The actual spaces on the board. All properties are spaces but not all spaces are properties. i.e Go is not a property.
