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
        this->bet = BetNode::passBet;
        break;
    case 2:
        this->bet = BetNode::dontPassBet;
        break;
    case 3:
        this->bet = BetNode::fieldBelt;
        break;
    case 4:
        this->bet = BetNode::placeBelt;
        break;
    case 5:
        this->bet = BetNode::propositionBet;
        break;
    default:
        this->bet = BetNode::default;
        return false;
        break;
    }

    return true;
}

// Setter for wager variable
void BetNode::setWager(int wage)
{
    this->wager = wage;
}

// Setter for comeBet variable
void BetNode::setComeBet(int cb)
{
    this->comeBet = cb;
}

/*-----------------------------------------------------------------------------------------
    PlayerNode Functions
*/

// Name Setter
bool PlayerNode::setName(string name)
{
    if (this->gamblerName != "Default")
        return false;

    this->gamblerName = name;
    return true;
}

// Set the balance
void PlayerNode::setBalance(int money)
{
    this->balance = money;
}
