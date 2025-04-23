#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype> // isdigit
#include <iostream>
#include <limits>
#include "PlayerList.h"
class Craps
{
private:
    /*
        Private Attributes
    */
    bool comeOutRoll = true;
    PlayerList Gamblers; // List of players
    const int minWager{15};
    std::list<int> activePoints;

    /*
        Private Functions
    */
    // Dice Functions
    int randNum();
    int *rollDice();

    // Menu Functions
    // TODO: Welcome Screen
    void welcome();
    void displayNewRound(bool comeOutRoll);

    // Game Helpers
    std::string inputType(const std::string &userInput);

    int getWager();
    void setP1();

public:
    void play();
};