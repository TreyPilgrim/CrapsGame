#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib> // rand

class Dice
{
private:
    int randNum();
    int theDie[3];

public:
    // Dice Functions
    void rollDice();
    void printDice();

    Dice() = default;
    ~Dice() = default;
};