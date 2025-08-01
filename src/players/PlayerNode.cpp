#include "PlayerNode.h"
//-----------------------------------------------------------------------------------------
// Private Functions

//-----------------------------------------------------------------------------------------
// Checkers
bool PlayerNode::validFunds(int wage) const
{
    if (this->balance < wage)
        return false;

    return true;
}

//-----------------------------------------------------------------------------------------
// Getters

// shooter?
bool PlayerNode::isShooter() const
{
    return this->PlayerNode::shooter;
}

// name
string PlayerNode::getName() const
{
    return this->PlayerNode::gamblerName;
}
// balance
int PlayerNode::getBalance() const
{
    return this->PlayerNode::balance;
}

//-----------------------------------------------------------------------------------------
// Setters

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
    this->PlayerNode::balance += money;
}

// Set Shooter
void PlayerNode::newShooter()
{
    if (this->shooter == true)
        this->shooter = false;
    else
        this->shooter = true;
}

//-----------------------------------------------------------------------------------------
// Game Logic

void PlayerNode::placeWager(int wageType)
{
    // this->playerBets->generateNewBet(wageType);
}

void PlayerNode::viewBets()
{
    // Call BetListFunction -- BetList.h
    // this->playerBets->viewBets();
}

void PlayerNode::removeBet()
{
    this->playerBets->remove();
}

bool PlayerNode::emptyBetAvl()
{
    return this->playerBets->isEmpty();
}