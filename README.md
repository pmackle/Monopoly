# Monopoly
Text-based multiplayer monopoly game written from January - March 2018 for ECS 40 (Now known as ECS 36B). Includes adjustable boards, rules, and more by reading in CSV files.
# Files
Board.cpp - Reads the board file for hotel cost, rent, type, properties/spaces, etc.

DiceRoller.cpp - As the name implies.

Gamestate.cpp - Operates like a finite state machine. Helps organize.

Go.cpp - For passing go or landing on a space. I have retroactively tried to add comments 3 years later but am unable to decipher a lot of it. Rookie mistake for a first big project.

main.cpp - Self explanatory. Takes in textfile of rules/properties.

play.cpp - Our monolith of code. Does most of the actual actions and calling to other .cpp files.

Player.cpp - Player object with cash, current poisition, name, and actions.

Property.cpp - Properties of properties, including rent, amount of hotels, owner, etc.

Rules.cpp - Reads the rules file for if there should be a salary multiplier, getting money when landing on free parking, turn limit, etc.

Space.cpp - Another monolith of code. The actual spaces on the board. All properties are spaces but not all spaces are properties. i.e Go is not a property.

# Authors
* [Patrick Mackle](https://github.com/pmackle) - *Developer*

* [Dhruva Eswar](https://github.com/dhruvaeswar) - *Developer*

# Acknowledgments
Matt Butner for all that C++ teaching. Youtube and stack overflow for everytime we got a segment fault and prayed someone else has had a similiar problem.
