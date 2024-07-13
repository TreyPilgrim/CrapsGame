#include "Node.h"

/*-----------------------------------------------------------------------------------------
    BetNode Functions
*/

// Setter for bet enum variable
bool BetNode::setBet(int betNum)
{
    switch (betNum)
    {
    case 1:
        this->BetNode::bet = BetNode::passBet;
        break;
    case 2:
        this->BetNode::bet = BetNode::dontPassBet;
        break;
    case 3:
        this->BetNode::bet = BetNode::fieldBelt;
        break;
    case 4:
        this->BetNode::bet = BetNode::placeBelt;
        break;
    case 5:
        this->BetNode::bet = BetNode::propositionBet;
        break;
    default:
        this->BetNode::bet = BetNode::defaultType;
        break;
    }

    return true;
}

// Setter for wager variable
void BetNode::setWager(int wage)
{
    this->BetNode::wager = wage;
}

// Setter for comeBet variable
void BetNode::setComeBet(int cb)
{
    this->BetNode::comeBet = cb;
}

/*-----------------------------------------------------------------------------------------
    PlayerNode Functions
*/

// Name Setter
bool PlayerNode::setName(string name)
{
    if (this->PlayerNode::gamblerName != "Default")
        return false;

    this->PlayerNode::gamblerName = name;
    return true;
}

// Set the balance
void PlayerNode::setBalance(int money)
{
    this->PlayerNode::balance = money;
}
