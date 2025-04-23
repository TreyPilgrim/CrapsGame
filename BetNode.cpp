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

// wager variable
void BetNode::setWager(int wage)
{
    this->wager = std::move(wage);
    std::cout << "Wager: " << this->wager << std::endl;
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

// wager amount
int BetNode::getWager()
{
    return this->wager;
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
// Update First roll status

// Is this the first roll for the bet?
bool BetNode::isFirstRoll()
{
    return this->firstRoll;
}

// Turn first roll status to false
void BetNode::secondRoll()
{
    this->firstRoll = false;
}