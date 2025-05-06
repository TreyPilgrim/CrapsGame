#include "BetNode.h"
#include <ctime>

/*-----------------------------------------------------------------------------------------
   BetNode Functions
*/

// Setters

// ID
void BetNode::setID(std::string str)
{
    this->betId = std::move(str);
    std::cout << "Node's ID: " << this->betId << std::endl;
}

// balance factor
void BetNode::setBF(int balFact)
{
    this->bf = std::move(balFact);
}

// height
void BetNode::setHeight(int h)
{
    this->height = std::move(h);
}

// the Point
void BetNode::setPoint(int point)
{
    this->point = std::move(point);
    std::cout << "Point: " << this->point << std::endl;
}

// Wager - and helpers related

// Valid Wager - return whole number

// wage variable
void BetNode::setWager(int wage)
{
    this->wage = std::move(wage);
    std::cout << "Wager: " << this->wage << std::endl;
}

//-----------------------------------------------------------------------------------------
// Getters

// id getter
std::string BetNode::getID()
{
    return this->betId;
}

// balance factor
int BetNode::getBF()
{
    return this->bf;
}

// height
int BetNode::getHeight()
{
    return this->height;
}

// point
int BetNode::getPoint()
{
    return this->point;
}

// wage amount
int BetNode::getWager()
{
    return this->wage;
}

// bet type
char BetNode::getBetType()
{
    return this->betId[0];
}

// How many kids does the node have?
int const BetNode::childSupport()
{
    return (this->lChild != nullptr && this->rChild != nullptr)   ? 2
           : (this->lChild != nullptr || this->rChild != nullptr) ? 1
                                                                  : 0;
}

//-----------------------------------------------------------------------------------------
// ID Implementation

/*----------------------------------------------
    // Generate random Array
    arr tmp = randomArr();

    // Convert array to string
    tmpID = arrToString(tmp);

    // Concatenation
    id = prefix + tmpID;

    return id;
}
---------------------------------------------*/
//-----------------------------------------------------------------------------------------
/*
    Come Out Roll Bets
*/

// Derived Class : Pass Line Bet

// Update the first roll value - point needs to be establish
void PassLineBet::notFirstRoll()
{
    this->firstRoll = false;
}

// Winning Ticket Checker
bool PassLineBet::winningTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // iterator for searching
        auto it = winningVals.find(diceVal);

        // return false if value not found - does not always mean it is a loser... don't assume
        return (it == winningVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == this->point) ? true : false;
}

// Losing Ticket Checker
bool PassLineBet::losingTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // Iterator for searching
        auto it = losingVals.find(diceVal);

        // Return false if value not found - does not always mean winner... don't assume
        return (it == losingVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == 7) ? true : false;
}

//-----------------------------------------------------------------------------------------
// Derived Class : Dont Pass Line Bet

// Update the first roll value - point needs to be establish
void DontPassLineBet::notFirstRoll()
{
    this->firstRoll = false;
}

// Winning Ticket Checker
bool DontPassLineBet::winningTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // iterator for searching
        auto it = winningVals.find(diceVal);

        // return false if value not found - does not always mean it is a loser... don't assume
        return (it == winningVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == 7) ? true : false;
}

// Losing Ticket Checker
bool DontPassLineBet::losingTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // Iterator for searching
        auto it = losingVals.find(diceVal);

        // Return false if value not found - does not always mean winner... don't assume
        return (it == losingVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == this->point) ? true : false;
}

//-----------------------------------------------------------------------------------------
/*
    Post-Come Out Roll Bets
*/
// Derived Class : Pass Line Bet

// Update the first roll value - point needs to be establish
void ComeBet::notFirstRoll()
{
    this->firstRoll = false;
}

// Winning Ticket Checker
bool ComeBet::winningTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // iterator for searching
        auto it = winningVals.find(diceVal);

        // return false if value not found - does not always mean it is a loser... don't assume
        return (it == winningVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == this->point) ? true : false;
}

// Losing Ticket Checker
bool ComeBet::losingTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // Iterator for searching
        auto it = losingVals.find(diceVal);

        // Return false if value not found - does not always mean winner... don't assume
        return (it == losingVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == 7) ? true : false;
}

//-----------------------------------------------------------------------------------------
// Derived Class : Dont Come Bet

// Update the first roll value - point needs to be establish
void DontComeBet::notFirstRoll()
{
    this->firstRoll = false;
}

// Winning Ticket Checker
bool DontComeBet::winningTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // iterator for searching
        auto it = winningVals.find(diceVal);

        // return false if value not found - does not always mean it is a loser... don't assume
        return (it == winningVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == 7) ? true : false;
}

// Losing Ticket Checker
bool DontComeBet::losingTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // Iterator for searching
        auto it = losingVals.find(diceVal);

        // Return false if value not found - does not always mean winner... don't assume
        return (it == losingVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == this->point) ? true : false;
}