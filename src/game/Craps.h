#include <cstdlib> // exit()
#include <string>
#include <list>
#include <memory>
#include <cctype> // isdigit
#include <iostream>
#include <limits>
#include "players/PlayerList.h"
#include "utils/Dice.h"
#include "utils/Tokenizer.h"

using dicePtr = std::shared_ptr<Dice>;
using playerPtr = std::shared_ptr<PlayerList>;
class Craps
{
private:
    // Tokenizer
    Tokenizer token;

    std::list<int> comeOutBetNumbers = {1, 2, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

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
    void placeWagerOptions();
    void roundChoices();

    // Round Choices - Helpers
    void roundChoicesDisplay();
    //---------------------------------------
    void placeWager();
    bool pushWager(const int &intInput);
    //---------------------------------------
    void viewBets();
    void removeBets();
    void addFunds();
    void quit();

    int getP1Balance();
    std::string createUserName();

    void setP1();

public:
    void theGame();
};