#pragma once
#include <iostream>
#include <memory>
#include <string.h>
#include "BetAVL.h"
using std::string;

class PlayerNode;

// Type Alias
using playerNodePtr = std::shared_ptr<PlayerNode>;
using betAvlPtr = std::shared_ptr<BetAVL>;

// PlayerNode Class
class PlayerNode
{
private:
    // Is player shooting the dice?
    bool shooter;
    // Available balance
    int balance;
    // Player's name
    string gamblerName;

    // List of bets made - Learning point: Must INITIALIZE playerBets. cannot set to nullptr like the next/prev values
    betAvlPtr playerBets;

public:
    playerNodePtr next;
    playerNodePtr prev;

    // Constructors
    PlayerNode() : next{nullptr},
                   prev{nullptr},
                   shooter{false},
                   balance{0},
                   gamblerName{"Default"},
                   playerBets{std::make_shared<BetAVL>()}
    {
        this->setName("Default");
    }

    PlayerNode(string name) : next{nullptr},
                              prev{nullptr},
                              shooter{false},
                              balance{0},
                              playerBets{std::make_shared<BetAVL>()}
    {
        this->setName(name);
    }

    PlayerNode(string name, int &balance) : next{nullptr},
                                            prev{nullptr},
                                            shooter{false},
                                            playerBets{std::make_shared<BetAVL>(balance)}
    {
        this->setBalance(balance);
        this->setName(name);
        std::cout << "Player " << getName() << " with the balance of $" << getBalance() << " has been created\n";
    }

    // Checkers
    bool validFunds(int wage) const;

    // Getters
    bool isShooter() const;
    std::string getName() const;
    int getBalance() const;

    // Setters
    bool setName(string name);
    void setBalance(int money);
    void newShooter();

    // Round Choices Operations
    void placeWager(int wageType); // betAVL - needs balance [1st]
    void viewBets();               // betAVL - [2nd]
    void removeBet();              // betAVL - needs balance [3rd]
    void addFunds();               // betAVL - needs balance [4th]
};
