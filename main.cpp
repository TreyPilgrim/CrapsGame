#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>
#include "LinkedList.h"

// Function Prototypes
int randNum();
int *rollDice();
void Craps();

int main()
{
    // Ensure all numbers generated randomly are actually random
    srand(time(NULL));

    char quit = 'N';

    while (quit != 'y' && quit != 'Y')
    {
        Craps();
        std::cout << "quit game? " << std::endl;
        std::cin >> quit;
    }
    return 0;
}

// Function for rolling the Dice
// Generate random #
int randNum()
{
    // Generate 3 random #'s to ensure radomness
    int dice;
    for (int i = 0; i < 3; i++)
        dice = (rand() % 6) + 1;

    // Return dice value
    return dice;
}
int *rollDice()
{
    // Needs to be static so that the pointer can reference (local variable)
    static int theDie[2];

    // Assign two dice values
    theDie[0] = randNum();
    theDie[1] = randNum();

    // return pointer
    return theDie;
}
void Craps()
{
    LinkedList gamblers;
    string player1 = "default";
    int player1_Balance = 0;

    cout << "What will be your better's name? ";
    cin >> player1;

    while (player1_Balance <= 20)
    {
        cout << "What will be your starting balance ($20+)? " << endl;
        cin >> player1_Balance;
    }

    gamblers.push(player1, player1_Balance);

    int *theDie;
    theDie = rollDice();

    std::cout << "Dice 1 value: " << theDie[0] << std::endl;
    std::cout << "Dice 2 value: " << theDie[1] << std::endl;
}