#pragma once
#include <iostream>
#include <memory>
#include <string.h>
#include "BetList.h"
using std::string;

class PlayerNode;

// Type Alias
using ptr = std::shared_ptr<PlayerNode>;
using BetPtr = std::shared_ptr<BetList>;

// PlayerNode Class
class PlayerNode
{
public:
    ptr next;
    ptr prev;

    // Is player shooting the dice?
    bool shooter;
    // Available balance
    int balance;
    // Player's name
    string gamblerName;
    // List of bets made
    BetPtr playerBets;

    PlayerNode() : next{nullptr}, prev{nullptr}, shooter{false}, balance{0}, gamblerName{"Default"}, playerBets{std::make_shared<BetList>()} {}
    PlayerNode(string name) : next{nullptr}, prev{nullptr}, shooter{false}, balance{0}, gamblerName{name}, playerBets{std::make_shared<BetList>()} {}
    PlayerNode(string name, int &balance) : next{nullptr}, prev{nullptr}, shooter{false}, balance{0}, gamblerName{name}, playerBets{std::make_shared<BetList>()} { this->balance = std::move(balance); } // Move playerBalance

    bool setName(string name);
    void setBalance(int money);
};
