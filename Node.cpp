#include "Node.h"

/*
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

/*
    BetNode Functions
*/