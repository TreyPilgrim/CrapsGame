#include <cstdlib> // exit()
#include <string>
#include <list>
#include <memory>
#include <cctype> // isdigit
#include <iostream>
#include <limits>
#include "players/PlayerList.h"
#include "bets/BetNode.h"
#include "utils/Dice.h"
#include "utils/Tokenizer.h"

using dicePtr = std::shared_ptr<Dice>;
using betPtr = std::shared_ptr<BetNode>;
using playerPtr = std::shared_ptr<PlayerList>;
using p1Ptr = std::shared_ptr<PlayerNode>;

class Craps
{
private:
    /*
        Private Attributes
    */

    // Tokenizer
    Tokenizer token;

    // std::list<int> comeOutBetNumbers = {1, 2, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

    bool comeOutRoll = true;
    const int minWager{15};
    std::list<int> activePoints;
    dicePtr dice = std::make_shared<Dice>();
    playerPtr Gamblers = std::make_shared<PlayerList>(); // List of players
    p1Ptr p1;

    /*
        Private Functions
    */

    // Fail Safe
    void failIf(const std::string &errorMSG, int condition = -1);

    // Menu Functions
    // TODO: Welcome Screen
    void welcome();
    void placeWagerOptions(); // UPDATE *****

    /*
        Round Choices
    */
    void roundChoices();        // Engine
    void displayRoundChoices(); // Display RoundChoices™

    // 1 - Place Wager
    void placeWager(); // UPDATE *****
    bool validBetTypeSelected(const int intInput);
    bool isBetTypeThatNeedsPoint(const int intInput);
    int getPoint();

    bool placingTheWager(const int intInput);
    betNodePtr getChosenBet(const int intInput);
    bool pushWager(const int &intInput); // UPDATE *****

    // 2 - View Bets
    void viewBets();

    // 3 - Remove Bet
    void removeBets();

    // 4 - Add Funds
    void addFunds();

    // q - Quit
    void quit();
    // r - roll (Dice.h function)

    // -------------------------------------------------------------------------------------------

    /*
        Set P1
        - Getting a UserName
        - Getting starting balance
    */
    p1Ptr setP1();
    int getP1Balance();
    std::string createUserName();

public:
    void theGame();
};