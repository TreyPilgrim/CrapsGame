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

public:
    playerNodePtr next;
    playerNodePtr prev;
    // List of bets made
    betAvlPtr playerBets;

    // Learning point: Must INITIALIZE playerBets. cannot set to nullptr like the next/prev values

    // Constructors
    PlayerNode() : next{nullptr},
                   prev{nullptr},
                   shooter{false},
                   balance{0},
                   gamblerName{"Default"},
                   playerBets{std::make_shared<BetAVL>()}
    {
    }

    PlayerNode(string name) : next{nullptr},
                              prev{nullptr},
                              shooter{false},
                              balance{0},
                              gamblerName{name},
                              playerBets{std::make_shared<BetAVL>()}
    {
    }

    PlayerNode(string name, int &balance) : next{nullptr},
                                            prev{nullptr},
                                            shooter{false},
                                            balance{0},
                                            gamblerName{name},
                                            playerBets{std::make_shared<BetAVL>()}
    {
        this->balance = std::move(balance);
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
};
