#pragma once
#include <iostream>
#include <limits>
#include <unordered_set>
#include <memory>
#include <map>
#include <string>
#include <list>
#include <stdexcept>
#include "Tokenizer.h"

// BetNode CLass
class BetNode;
// Type Alias
using betNodePtr = std::shared_ptr<BetNode>;
using arr = std::shared_ptr<int[]>;

/*
    TODO
    create a "toWin" value to provide quick
    - setters
    - getters
*/

class BetNode
{
private:
    // Tree Attributes
    int bf{0}, height{0};

    // Bet Attributes
    std::string betId{"void"};
    int wager{0}, point{0};

    // Generate ID
    int randNum();

protected:
    Tokenizer token;
    std::map<int, double> payoutOdds{};
    std::unordered_set<int> losingVals{};
    bool firstRoll{true};

    // Fail safe
    void failIf(const std::string &errorMsg, int condition = -1);

    // Wage Helpers - Set up to handle 1:1 payouts
    bool validInt();                                             // Make sure input is an Int
    virtual bool validPayout(const int wage, const int balance); // payout isn't a decimal
    int getNorthVal(int wage, const int balance);                // Get Next valid Wager amount
    int getSouthVal(int wage, const int balance);                // Get Previous valid Wager amount
    int evaluateNextVal(arr wageArr, const int &balance);
    arr getNextValues(int wage, const int balance);         // function that's going to return an array to next and prev valid wager amounts
    int setTheWagePhasePointIndependent(const int balance); // Bets that pay 1:1
    int setTheWagePhasePointDependent(const int balance);   // Bets that require a point to calculate winnings

    // ID Helpers
    arr randomArr();
    std::string arrToString(arr tmp);
    virtual std::string generateID();

public:
    // Tree Attributes
    betNodePtr lChild{nullptr};
    betNodePtr rChild{nullptr};

    // Constructord
    BetNode()
    {
        std::cout << "BetNode Initialized: Default Constructor" << std::endl;
    }

    BetNode(int balance, int point = 0)
    {

        generateID();          // Virtual
        this->setPoint(point); // virtual - make sure valid point
        this->setWage(this->setTheWagePhasePointIndependent(balance));

        std::cout << "BetNode Initialized\n";
        std::cout << "Bet ID: " << this->getID() << std::endl;
        std::cout << "Wage: " << this->getWager() << std::endl;

        if (this->getPoint() != 0)
            std::cout << "Point: " << this->getPoint() << std::endl;

        std::cout << "=============================================================" << std::endl;
    }
    virtual ~BetNode() = default;

    // Initializer Functions
    void generateNewID();

    // Setters
    void setID(std::string str);
    void setBF(int balFact);
    void setHeight(int h);
    virtual void setPoint(int point); // virtual for the betTypes that require a point val
    void setWage(const int balance);  // Set the wage -- after being thoroughly checked

    // Getters
    std::string getID();
    int getBF();
    int getHeight();
    int getPoint();
    int getWager();
    char getBetType(); // ?
    int const childSupport();
};

//-----------------------------------------------------------------------------------------
// Come Out Roll Bets -- Add pointer to
// Pass Line Bet - A
/*
    - First Roll
        - Win on 7 or 11
        - Lose on 2, 3, or 12
    - Ongoing Game (point established)
        - Win on Point
        - Lose on 7

    - Payout 1:1
*/
class PassLineBet : public BetNode
{
private:
    bool firstRoll{true};
    betNodePtr oddsOnPassPtr{nullptr}; // Odds on Pass Line Bet

    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;

public:
    PassLineBet()
    {
        this->payoutOdds = {
            {7, 1.0},
            {11, 1.0}};
        this->losingVals = {2, 3, 12};

        std::cout << "Pass Line Bet Node Initialized: Default" << std::endl;
        this->generateNewID(); // Automatic
    }

    PassLineBet(const int balance)
    {
        this->payoutOdds = {
            {7, 1.0},
            {11, 1.0}};
        this->losingVals = {2, 3, 12};

        std::cout << "Pass Line Bet Node Initialized Starting balance passed" << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }

    // Possible virutal function tbd
    void notFirstRoll();

    // TODO (5/3/25) --- make these functions virtual
    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Don't Pass Line Bet - B
/*
    - First Roll
        - Win on 2 or 3
        - Lose on 7 or 11
        - Wash on 12
    - Ongoing Game (point established)
        - Win on 7
        - Lose on Point

    - Payout 1:1
*/
class DontPassLineBet : public BetNode
{
private:
    bool firstRoll{true};
    betNodePtr oddsOnDontPassPtr{nullptr}; // Odds on Don't Pass Line Bet

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    DontPassLineBet()
    {
        this->payoutOdds = {
            {2, 1.0},
            {3, 1.0},
            {12, 1.0}};
        this->losingVals = {7, 11};

        std::cout << "Dont Pass Line Bet Node Initialized: Default" << std::endl;
        this->generateNewID();
    }

    DontPassLineBet(const int balance)
    {
        this->payoutOdds = {
            {2, 1.0},
            {3, 1.0},
            {12, 1.0}};
        this->losingVals = {7, 11};

        std::cout << "Dont Pass Line Bet Node Initialized: Balance passed" << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }

    void notFirstRoll();

    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Post Come Out Roll Bets

// Come Bet - C
/*
    - First Roll
        - Win on 7 or 11
        - Lose on 2, 3, or 12

    - Ongoing Game (point established)
        - Win on point
        - Lose on 7

    - Payout 1:1
*/
class ComeBet : public BetNode
{
private:
    bool firstRoll{true};
    betNodePtr oddsOnComePtr{nullptr}; // Odds on Come Bet

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    ComeBet()
    {
        this->payoutOdds = {
            {7, 1.0},
            {11, 1.0}};
        this->losingVals = {2, 3, 12};

        std::cout << "Come Bet Initialized: Default" << std::endl;
        this->generateNewID();
    }

    ComeBet(const int balance)
    {
        this->payoutOdds = {
            {7, 1.0},
            {11, 1.0}};
        this->losingVals = {2, 3, 12};

        std::cout << "Come Bet Initialized: Balance Passed" << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }

    // Possible virutal function tbd
    void notFirstRoll();

    // TODO (5/3/25) --- make these functions virtual
    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Don't Come Bet - D
/*
    - First Roll
        - Win on 2 or 3
        - Lose on 7 or 11
        - Wash on 12
    - Ongoing Game (Point established)
        - Win on 7
        - Lose on Point

    - Payout 1:1
*/
class DontComeBet : public BetNode
{
private:
    betNodePtr oddsOnDontComePtr{nullptr}; // Odds on Don't Come Bet

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    DontComeBet()
    {
        this->payoutOdds = {
            {2, 1.0},
            {3, 1.0},
            {12, 1.0}};
        this->losingVals = {7, 11};

        std::cout << "Don't Come Bet Initialized: Default" << std::endl;
        this->generateNewID();
    }

    DontComeBet(const int balance)
    {
        this->payoutOdds = {
            {2, 1.0},
            {3, 1.0},
            {12, 1.0}};
        this->losingVals = {7, 11};

        std::cout << "Don't Come Bet Initialized: Balance Passed" << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }

    void notFirstRoll();

    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

/*
    Be Mindful
    - Odds on ____ Bets can only be made if line/come bet exists already
        -> Point must be established
    - Odds on [Dont] Pass Bets can only be made once -> [Dont] Come can be made once per come bet

    TODO 5/4/25
        - Add pointer to one of these nodes in [Dont] Pass/Come bets
            -> ensure that each [Dont] Pass/Come bet has 1 corresponding  Odds bet
        Completed:

        - Add functionality to

*/
// Odds on Pass Bet - E
/*
    - Attached to a Pass Bet

    - Win on point
    - lose on 7

    Payouts:
    6 or 8 pays 6/5
    5 or 9 pays 3/2
    4 or 10 pays 2/1
*/
class OddsOnPassBet : public PassLineBet
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    OddsOnPassBet()
    {
        this->payoutOdds = {
            {4, 2.0},
            {5, 3 / 2},
            {6, 6 / 5},
            {8, 6 / 5},
            {9, 3 / 2},
            {10, 2.0}};
        this->losingVals = {7};

        std::cout << "Odds on Pass Bet Initialized: Default" << std::endl;
        this->generateNewID();
        this->setPoint(2);
    }

    OddsOnPassBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 2.0},
            {5, 3 / 2},
            {6, 6 / 5},
            {8, 6 / 5},
            {9, 3 / 2},
            {10, 2.0}};
        this->losingVals = {7};

        std::cout << "Odds on Pass Bet Initialized: Balance Passed" << std::endl;
        this->generateNewID();
        this->setPoint(point);

        // Set Wage Phase
        this->setWage(balance);
    }
};

// Odds on Don't Pass Bet - F
/*
    - Attached to a Don't Pass Bet

    - Win on 7
    - lose on point

    Payouts:
    6 or 8 pays 5/6
    5 or 9 pays 2/3
    4 or 10 pays 1/2
*/
class OddsOnDontPassBet : public BetNode
{
private:
    const int winningNumber{7};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    OddsOnDontPassBet()
    {
        this->payoutOdds = {
            {4, 1 / 2},
            {5, 2 / 3},
            {6, 5 / 6},
            {8, 5 / 6},
            {9, 2 / 3},
            {10, 1 / 2}};
        this->losingVals = {};

        std::cout << "Odds On Dont Pass Bet: Default" << std::endl;
        this->generateNewID();
    }

    OddsOnDontPassBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 1 / 2},
            {5, 2 / 3},
            {6, 5 / 6},
            {8, 5 / 6},
            {9, 2 / 3},
            {10, 1 / 2}};
        this->losingVals = {point};

        std::cout << "Odds On Dont Pass Bet: Balance Passed" << std::endl;
        this->generateNewID();
        this->setPoint(point);

        // Set Wage Phase
        this->setWage(balance);
    }
};

// Odds on Come Bet - G
/*
    - Attached to a Pass Bet

    - Win on point
    - lose on 7

    Payouts:
    6 or 8 pays 6/5
    5 or 9 pays 3/2
    4 or 10 pays 2/1
*/
class OddsOnComeBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    OddsOnComeBet()
    {
        this->payoutOdds = {
            {4, 2.0},
            {5, 3 / 2},
            {6, 6 / 5},
            {8, 6 / 5},
            {9, 3 / 2},
            {10, 2.0}};
        this->losingVals = {7};

        std::cout << "Odds On Come Bet Initialized: Default" << std::endl;
        this->generateNewID();
    }

    OddsOnComeBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 2.0},
            {5, 3 / 2},
            {6, 6 / 5},
            {8, 6 / 5},
            {9, 3 / 2},
            {10, 2.0}};
        this->losingVals = {7};

        std::cout << "Odds On Come Bet Initialized: Balance Passed" << std::endl;
        this->generateNewID();
        this->setPoint(point);

        // Set Wage Phase
        this->setWage(balance);
    }
};

// Odds on Don't Come Bet - H
/*
    - Attached to a Don't Pass Bet

    - Win on 7
    - lose on point

    Payouts:
    6 or 8 pays 5/6
    5 or 9 pays 2/3
    4 or 10 pays 1/2
*/
class OddsOnDontComeBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    OddsOnDontComeBet() : BetNode()
    {
        this->payoutOdds = {
            {4, 1 / 2},
            {5, 2 / 3},
            {6, 5 / 6},
            {8, 5 / 6},
            {9, 2 / 3},
            {10, 1 / 2}};
        this->losingVals = {};

        std::cout << "Odds On Dont Come Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    OddsOnDontComeBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 1 / 2},
            {5, 2 / 3},
            {6, 5 / 6},
            {8, 5 / 6},
            {9, 2 / 3},
            {10, 1 / 2}};
        this->losingVals = {point};

        std::cout << "Odds On Dont Come Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(point);
        this->setWage(balance);
    }
};

// Place Bets - Made any time after come out roll

// Place to Win Bet - I
/*
    - can be made ANYTIME
    - Win on number you pick
    - Loses on 7
    - Must specify number to bet on

    Payouts
    6 or 8 = 7/6
    5 or 9 = 7/5
    4 or 10 = 9/5
*/
class PlaceToWinBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    PlaceToWinBet() : BetNode()
    {
        this->payoutOdds = {
            {4, 9 / 5},
            {5, 7 / 5},
            {6, 7 / 6},
            {8, 7 / 6},
            {9, 7 / 5},
            {10, 9 / 5}};

        std::cout << "Place To Win Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    PlaceToWinBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 9 / 5},
            {5, 7 / 5},
            {6, 7 / 6},
            {8, 7 / 6},
            {9, 7 / 5},
            {10, 9 / 5}};
        this->losingVals = {7};

        std::cout << "Place To Win Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(point);
        this->setWage(balance);
    }
};

// Place to Lose Bet - J
/*
    - can be placed ANYTIME
    - Win on 7
    - Lose on point

    Payout
    6 or 8 = 4/5
    5 or 9 = 5/8
    4 or 10 = 5/11
*/
class PlaceToLoseBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    PlaceToLoseBet()
    {
        this->payoutOdds = {
            {4, 5 / 11},
            {5, 5 / 8},
            {6, 4 / 5},
            {8, 4 / 5},
            {9, 5 / 8},
            {10, 5 / 11}};

        std::cout << "Place To Lose Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    PlaceToLoseBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 5 / 11},
            {5, 5 / 8},
            {6, 4 / 5},
            {8, 4 / 5},
            {9, 5 / 8},
            {10, 5 / 11}};
        this->losingVals = {point};
        std::cout << "Place To Lose Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }
};

// Buy Bet - K
/*
    - can be placed ANYTIME
    - Win on (selected) point
    - Lose on 7

    Payouts
    6 or 8 = 6/5
    5 or 9 = 3/2
    4 or 10 = 2/1

    - whatever the wage is
        * Must pay the house 5% of that number (non-refundable)
*/
class BuyBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    BuyBet()
    {
        this->payoutOdds = {
            {4, 2.0},
            {5, 3 / 2},
            {6, 6 / 5},
            {8, 6 / 5},
            {9, 3 / 2},
            {10, 2.0}};
        std::cout << "Buy Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    BuyBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 2.0},
            {5, 3 / 2},
            {6, 6 / 5},
            {8, 6 / 5},
            {9, 3 / 2},
            {10, 2.0}};
        this->losingVals = {point};

        std::cout << "Buy Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(point);

        // Set Wage Phase
        this->setWage(balance);
    }
};

// Lay Bet - L
/*
    - Can Be placed ANYTIME
    - Win on 7
    - Lose on Point

    Payouts
    6 or 8 = 5/6
    5 or 9 = 2/3
    4 or 10 = 1/2

    - 5% commission
*/
class LayBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    LayBet()
    {
        this->payoutOdds = {
            {4, 1 / 2},
            {5, 2 / 3},
            {6, 5 / 6},
            {8, 5 / 6},
            {9, 2 / 3},
            {10, 1 / 2}};

        std::cout << "Lay Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    LayBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 1 / 2},
            {5, 2 / 3},
            {6, 5 / 6},
            {8, 5 / 6},
            {9, 2 / 3},
            {10, 1 / 2}};
        this->losingVals = {point};
        std::cout << "Lay Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(point);
        this->setWage(balance);
    }
};

// Big 6 Bet - M
/*
    - Can be made ANYTIME
    - Win 6
    - Lose on 7

    Payout
    1:1
*/
class Big6Bet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO  1:1 payout
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    Big6Bet()
    {
        this->payoutOdds = {{6, 1.0}};

        std::cout << "Big 6 Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(6);
    }

    Big6Bet(const int balance)
    {
        this->payoutOdds = {{6, 1.0}};
        this->losingVals = {7};

        std::cout << "Big 6 Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(6);
        this->setWage(balance);
    }
};

// Big 8 Bet - N
/*
    - Can be made ANYTIME
    - Win on 8
    - Lose on 7

    Payout
    1:1
*/
class Big8Bet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - 1:1 payout
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    Big8Bet()
    {
        this->payoutOdds = {{8, 1.0}};
        std::cout << "Big 8 Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(8);
    }

    Big8Bet(const int balance)
    {
        this->payoutOdds = {{8, 1.0}};
        this->losingVals = {7};

        std::cout << "Big 8 Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(8);
        this->setWage(balance);
    }
};

// Single-Roll Proposition Bets - Any Time

// Field Bet - O
/*
   - Can Be placed ANYTIME
   - Wins on 2(double), 3, 4, 9, 10, 11, 12(double)
   - Lose on 5, 6, 7, 8
*/
class FieldBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    FieldBet()
    {
        this->payoutOdds = {
            {2, 2.0},
            {3, 1.0},
            {4, 1.0},
            {9, 1.0},
            {10, 1.0},
            {11, 1.0},
            {12, 2.0}};

        std::cout << "Field Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    FieldBet(const int balance)
    {
        this->payoutOdds = {
            {2, 2.0},
            {3, 1.0},
            {4, 1.0},
            {9, 1.0},
            {10, 1.0},
            {11, 1.0},
            {12, 2.0}};
        this->losingVals = {5, 6, 7, 8};

        std::cout << "Field Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }
};

// Any Craps Bet - P
/*
    - Can be placed ANYTIME
    - Wins on 2, 3, 12
    - Loses on Everything else

    Payout
    7/1
*/
class AnyCrapsBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    AnyCrapsBet()
    {
        this->payoutOdds = {
            {2, 7.0},
            {3, 7.0},
            {12, 7.0}};

        std::cout << "Any Craps Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    AnyCrapsBet(const int balance)
    {
        this->payoutOdds = {
            {2, 7.0},
            {3, 7.0},
            {12, 7.0}};
        this->losingVals = {4, 5, 6, 7, 8, 9, 10, 11};

        std::cout << "Any Craps Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }
};

// Any Seven Bet - R
/*
    - Place ANYTIME
    - Wins on 7
    - Loses on anything else

    Payout
    4/1
*/
class AnySevenBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    AnySevenBet()
    {
        this->payoutOdds = {{7, 4.0}};

        std::cout << "Any Seven Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(7);
    }

    AnySevenBet(const int balance)
    {
        this->payoutOdds = {{7, 4.0}};

        std::cout << "Any Seven Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(7);
        this->setWage(balance);
    }
};

// Yo Bet - S
/*
    - ANYTIME bet
    - Win on 11
    - lose on everything else

    payout
    15/1
*/
class YoBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    YoBet() : BetNode()
    {
        this->payoutOdds = {{11, 15.0}};

        std::cout << "Yo Bet Initialized: Default" << std::endl;
        this->generateNewID();
        this->setPoint(11);
    }

    YoBet(const int balance)
    {
        this->payoutOdds = {{11, 15.0}};

        std::cout << "Yo Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(11);
        this->setWage(balance);
    }
};

// Ace Deuce Bet - T
/*
    - ANYTIME
    - Wins on 3
    - Lose on everything else

    Payout
    15/1
*/
class AceDeuceBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    AceDeuceBet()
    {
        this->payoutOdds = {{3, 15.0}};

        std::cout << "Ace Deuce Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(3);
    }

    AceDeuceBet(const int balance)
    {
        this->payoutOdds = {{3, 15.0}};

        std::cout << "Ace Deuce Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(3);
        this->setWage(balance);
    }
};

// Snake Eyes Bet - U
/*
    - ANYTIME bet
    - Win on 2
    - Lose on everything else

    Payout
    30/1
*/
class SnakeEyesBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    SnakeEyesBet()
    {
        this->payoutOdds = {{2, 30.0}};

        std::cout << "Snake Eyes Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(2);
    }

    SnakeEyesBet(const int balance)
    {
        this->payoutOdds = {{2, 30.0}};

        std::cout << "Snake Eyes Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(2);
        this->setWage(balance);
    }
};

// Box Cars Bet - V
/*
    - ANYTIME
    - Win on 12
    - Lose on everything else

    Payout
    30/1
*/
class BoxCarsBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    BoxCarsBet()
    {
        this->payoutOdds = {{12, 30.0}};

        std::cout << "Box Cars Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(12);
    }

    BoxCarsBet(const int balance)
    {
        this->payoutOdds = {{12, 30.0}};

        std::cout << "Box Cars Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(12);
        this->setWage(balance);
    }
};

// World Bet - Wage must be divisible by 5 W
/*
    - Bet must be divisible by 5
    - dividen is divided amongst the 5 winning values
        * this is what gets multiplied for the winnings
    - Wins on 2, 3, 7, 11, 12

    Payout
    2 or 12 = 30.0
    3 or 11 = 15.0
    7 = 4.0
*/
class WorldBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    WorldBet()
    {
        this->payoutOdds = {
            {2, 30.0},
            {3, 15.0},
            {7, 4.0},
            {11, 15.0},
            {12, 30.0}};

        std::cout << "World Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    WorldBet(const int balance)
    {
        this->payoutOdds = {
            {2, 30.0},
            {3, 15.0},
            {7, 4.0},
            {11, 15.0},
            {12, 30.0}};

        std::cout << "World Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }
};

// Horn Bet - X
/*
    - Wage must be divisible by 4
    - Dividen is what gets multiplied on payouts
    - Wins on 2, 3, 11, 12
    - Loses - Everything else

    Payouts
    2 or 12 = 30/4
    3 or 11 = 15/4
*/
class HornBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID();
    // int setTheWagePhase(const int balance) override;

public:
    HornBet()
    {
        this->payoutOdds = {
            {2, 30 / 4},
            {3, 15 / 4},
            {11, 15 / 4},
            {12, 30 / 4}};
        this->losingVals = {4, 5, 6, 7, 8, 9, 10};

        std::cout << "Horn Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    HornBet(const int balance)
    {
        this->payoutOdds = {
            {2, 30 / 4},
            {3, 15 / 4},
            {11, 15 / 4},
            {12, 30 / 4}};
        this->losingVals = {4, 5, 6, 7, 8, 9, 10};

        std::cout << "Horn Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }
};

// Horn High Bet - Y
/*
    - Same as Horn Bet with Nuances
    - Wage must be divisible by 5 (still same 4 winning numbers)
    - User Picks a point (out of winning #s)
        * This gets the extra money - Breakdown below

    Extra $
    - Example

    User bets $45 & picks 3 as the High #
    ~ 45 / 5 = 9
        * 2, 11, & 12 get a wage amount of $9

    ~ 9 * 3 = 27
    ~ 45 - 27 = $18 remaining or 9 * 2 times more
        - this is the wage amount for the high #

*/
class HornHighBet : public HornBet
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO (HIGH # HAS DIF PAYOUT)
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    HornHighBet() : HornBet()
    {
        std::cout << "Horn High Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID(); // HornBet() will run its version of generateNewID*
    }

    HornHighBet(const int balance, const int point) : HornBet()
    {
        std::cout << "Horn High Bet Initialized: Balance Passed" << std::endl;
        this->generateNewID(); // HornBet() will run its version of generateNewID*
        this->setPoint(point); // High #
        this->setWage(balance);
    }
};

// All Small Bet - Z
/*
    - Win by having all winning #s rolled (once minimum0) before 7
    - Lose by 7 being rolled before all winning #s rolled

    Payout
    30/1
*/
class AllSmallBet : public BetNode
{
private:
    std::unordered_set<int> rolledVals{};
    const int winningNumbers[5] = {2, 3, 4, 5, 6};
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    AllSmallBet()
    {
        this->payoutOdds = {{5, 30.0}}; // sizeOf rolledVals is the key (must be 5)

        std::cout << "All Small Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    AllSmallBet(const int balance)
    {
        this->payoutOdds = {{5, 30.0}}; // sizeOf rolledVals is the key (must be 5)

        std::cout << "All Small Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }
};

// All Tall Bet - a
/*
    - Win by having all winning #s rolled (once minimum0) before 7
    - Lose by 7 being rolled before all winning #s rolled

    Payout
    30/1
*/
class AllTallBet : public BetNode
{
private:
    std::unordered_set<int> rolledVals{};
    int winningNumbers[5] = {8, 9, 10, 11, 12};

    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    AllTallBet()
    {
        this->payoutOdds = {{5, 30.0}}; // sizeOf rolledVals is the key (must be 5)

        std::cout << "All Tall Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    AllTallBet(const int balance)
    {
        this->payoutOdds = {{5, 30.0}}; // sizeOf rolledVals is the key (must be 5)

        std::cout << "All Tall Bet Initialzied: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setWage(balance);
    }
};

// Multi-Roll Proposition Bets - Any Time

// Hardway Bet - b
/*
    - ANYTIME
    - User Picks Hardway #
    - Wins by rolling an exact pair (3 + 3 = 6) before "easy way" or 7
    - Loses on "easy way" (4 + 2 = 6) roll or 7

    Payout
    6 or 8 = 9/1
    4 or 10 = 7/1
*/
class HardwayBet : public BetNode
{
private:
    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    HardwayBet()
    {
        this->payoutOdds = {
            {4, 7.0},
            {6, 9.0},
            {8, 9.0},
            {10, 7.0}};
        this->losingVals = {7};

        std::cout << "Hardway Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    HardwayBet(const int balance, const int point)
    {
        this->payoutOdds = {
            {4, 7.0},
            {6, 9.0},
            {8, 9.0},
            {10, 7.0}};
        this->losingVals = {7};

        std::cout << "Hardway Bet Initialized: Balance Passed\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(point);

        // Set Wage Phase
        this->setWage(balance);
    }
};

// Fire Bet - c
/*
    - Only able to make on Come Out Roll
    - Tied directly to current shooter
        * if shooter defers turn, this bet loses. all other bets carry over

    - Bet that the shooter will "make" 4+ points before rolling a 7
    ~ rolls 4 (point)
    ~ rolls 4 *again* (thats a make)
    ~ rolls 7 - bet loses (only 1 make)

    Payouts
    4 hits = 25/1
    5 hits = 250/1
    6+ hits = 1000/1
*/
class FireBet : public BetNode
{
private:
    std::unordered_set<int> pointTracker{};
    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage, const int balance) override;
    // int setTheWagePhase(const int balance) override;

public:
    FireBet()
    {
        this->payoutOdds = {
            {4, 25.0},
            {5, 250.0},
            {6, 1000.0}};
        this->losingVals = {7};

        std::cout << "Fire Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }

    FireBet(const int balance)
    {
        this->payoutOdds = {
            {4, 25.0},
            {5, 250.0},
            {6, 1000.0}};
        this->losingVals = {7};

        std::cout << "Fire Bet Initialized\n"
                  << std::endl;
        this->generateNewID();

        // Set Wage Phase
        this->setWage(balance);
    }
};
