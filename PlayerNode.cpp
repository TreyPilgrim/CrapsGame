#include "PlayerNode.h"

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
