#include "BetNode.h"

/*-----------------------------------------------------------------------------------------
    BetNode Functions
*/

// Setter for bet enum variable
void BetNode::setWageType(int betNum)
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
        this->bet = BetNode::comeBet;
        break;
    case 4:
        this->bet = BetNode::dontComeBet;
        break;
    default:
        this->bet = BetNode::defaultType;
        break;
    }

    std::cout << "WageType " << this->bet << std::endl;
}

// Setter for wager variable
void BetNode::setWager(int wage)
{
    this->wager = std::move(wage);
    std::cout << "Wager: " << this->wager << std::endl;
}
