#pragma once
#include <iostream>
#include <memory>
#include "BetNode.h"

class BetList
{
private:
    using betPtr = std::shared_ptr<BetNode>; // For tmp pointers

    betPtr head;
    betPtr tail;

    bool peek();

public:
    BetList() : head(nullptr), tail(nullptr) {}
    ~BetList() = default;

    void pushBet(int typeBet, int wage);
};