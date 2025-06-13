#include <cstdlib> // exit()
#include <string>
#include <list>
#include <memory>
#include <cctype> // isdigit
#include <iostream>
#include <limits>
#include "players/PlayerList.h"
#include "utils/Dice.h"

using dicePtr = std::shared_ptr<Dice>;
using playerPtr = std::shared_ptr<PlayerList>;
class Craps
{
private:
    /*
        Private Attributes
    */
    bool comeOutRoll = true;
    const int minWager{15};
    std::list<int> activePoints;
    dicePtr dice = std::make_shared<Dice>();
    playerPtr Gamblers = std::make_shared<PlayerList>(); // List of players

    /*
        Private Functions
    */

    // Fail Safe
    void failIf(const std::string &errorMSG, int condition = -1);

    // Menu Functions
    // TODO: Welcome Screen
    void welcome();
    void placeWagerOptions(bool comeOutRoll);
    void roundChoices();

    // Round Choices - Helpers
    void roundChoicesDisplay();
    void placeWager();
    void viewBets();
    void removeBets();
    void addFunds();

    // Game Helpers
    std::string inputType(const std::string &userInput);

    int getWager();
    void setP1();

public:
    void play();
};