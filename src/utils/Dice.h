#pragma once
#include <ctime>
#include <cstdlib> // rand

class Dice
{
private:
    int randNum();

public:
    int theDie[3];

    // Dice Functions
    void rollDice();

    Dice() = default;
    ~Dice() = default;
};