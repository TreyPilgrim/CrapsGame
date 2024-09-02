#pragma once
#include <iostream>
#include <memory>
#include <string.h>

// BetNode CLass
class BetNode
{
private:
    enum betTypes
    {
        defaultType, // 0
        passBet,     // 1
        dontPassBet, // 2
        comeBet,     // 3
        dontComeBet, // 4

    };

    betTypes bet;
    int wager;

public:
    // Type Alias
    using ptr = std::shared_ptr<BetNode>;
    ptr next;
    ptr prev;

    // Constructor
    BetNode() : next(nullptr), prev(nullptr), bet{BetNode::defaultType}, wager{0} {}
    BetNode(int wageType, int wage) : next(nullptr), prev(nullptr)
    {
        this->setWageType(wageType);
        this->setWager(wage);
        std::cout << "BetNode initialized\n";
    }

    // Setters
    void setWageType(int betNum);
    void setWager(int wage);

    // Getters
};