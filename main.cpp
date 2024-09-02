#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>
#include "PlayerList.h"

const int minWager = 15;
// Function Prototypes
int randNum();
int *rollDice();
void Craps();
char displayNewRound(char &input);
bool validBet();
bool validBet(const string name, int typeBet, int point); // implement
int getWager();
void makeBet(PlayerList &list, const string name, int typeBet);

int main()
{

    PlayerList players;
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

/*
   // Function Declarations //
*/

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
    static int theDie[3];

    // Assign two dice values
    theDie[0] = randNum();
    theDie[1] = randNum();
    theDie[2] = theDie[0] + theDie[1]; // total

    // return pointer
    return theDie;
}

char displayNewRound(char &input) // Pass Bet & Don't Pass Bet
{
    std::cout << "------------------------" << std::endl;
    std::cout << "Enter what you want to do this round:" << std::endl;
    std::cout << "a. Pass Bet" << std::endl;
    std::cout << "b. Don't Pass Bet" << std::endl;
    std::cout << "q. Quit" << std::endl;

    std::cin >> input;

    while (input != 'a' && input != 'b' && input != 'q') // Check that user inputs proper value
    {
        std::cout << input << "is an invalid input!" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << "Enter what you want to do this round:" << std::endl;
        std::cout << "a. Pass Bet" << std::endl;
        std::cout << "b. Don't Pass Bet" << std::endl;
        std::cout << "q. Quit" << std::endl;

        std::cin >> input;
    }

    return input;
}

// bool validBet()
// {
// }

int getWager() // Applicable for Pass/Don'tPass and Come/DontCome
{
    int wage = 0;
    while (wage < 15)
    {
        std::cout << "How much would you like to wage?" << std::endl;
        std::cin >> wage;
    }

    return wage;
}
void makeBet(PlayerList &list, const string name, int betType)
{
    int wage = 0;
    switch (betType)
    {
    case 1: // Pass Bet
        wage = getWager();
        list.pushWager(name, betType, wage); // Add Pass wager to player's betList
                                             // std::cout << name << " is not a player in our database" << std::endl;
        break;
    case 2: // Don't Pass Bet
        wage = getWager();
        list.pushWager(name, betType, wage); // Add Don't Pass wager to player's betList
                                             // std::cout << name << " is not a player in our database" << std::endl;
        break;
    case 3: // Come Bet
        wage = getWager();
        list.pushWager(name, betType, wage); // Add Come wager to player's betList
                                             // std::cout << name << " is not a player in our database" << std::endl;
        break;
    case 4: // Don't Come Bet
        wage = getWager();
        list.pushWager(name, betType, wage); // Add Don't Come wager to player's betList
                                             // std::cout << name << " is not a player in our database" << std::endl;
        break;
    }
}
void Craps()
{
    PlayerList Gamblers;        // create player list
    string player1 = "default"; // pass P1 name
    int player1_Balance = 0;    // P1 Balance
    bool newRound = true;       // Pass/DontPass vs Come/DontCome

    std::cout << "What will be your better's name? ";
    std::cin >> player1;

    while (player1_Balance <= minWager)
    {
        std::cout << "What will be your starting balance ($" << minWager << "+)? " << std::endl;
        std::cin >> player1_Balance;
    }

    Gamblers.pushPlayer(player1, player1_Balance);

    char roundInput = ' ';
    displayNewRound(roundInput);

    /*
        Now we have the user's name and balance
        We also know what type of opening bet the user wants to make
        TODO::
        good 1. get bet $
        good 2. add bet to list
        good 3. roll dice

        4. check dice isn't Craps/Winning number
        5. Ongoing bets
    */
    int wage = 0;
    switch (roundInput)
    {
    case 'a':
        wage = getWager();
        Gamblers.pushWager(player1, 1, wage);
        std::cout << wage << " added to betters list" << std::endl;
        break;

    case 'b':
        wage = getWager();
        Gamblers.pushWager(player1, 2, wage);
        std::cout << wage << " added to betters list" << std::endl;
        break;
    default:
        std::cout << "You have opted to quit...\nSee ya later, Alligator" << std::endl;
        return;
        break;
    }

    int *theDie;
    theDie = rollDice();

    std::cout << "Dice 1 value: " << theDie[0] << std::endl;
    std::cout << "Dice 2 value: " << theDie[1] << std::endl;
    std::cout << "You rolled a: " << theDie[2] << std::endl;

    Gamblers.displaySelf();
}