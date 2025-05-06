#include "Dice.h"

int Dice::randNum()
{
    // Generate 3 random #'s to ensure radomness
    int dice;
    for (int i = 0; i < 3; i++)
        dice = (rand() % 6) + 1;

    // Return dice value
    return dice;
}

void Dice::rollDice()
{
    // Assign two dice values
    theDie[0] = randNum();
    theDie[1] = randNum();
    theDie[2] = theDie[0] + theDie[1]; // total
}
