#include "Craps.h"

/*
    Private Functions
*/

//-----------------------------------------------------------------------------------------
// Menu Functions

// Welcome Screen
void Craps::welcome()
{
    std::cout << "Welcome to Our Implementation of the game Craps!" << std::endl;
    std::cout << "------------------------------------------------\n";
    std::cout << std::endl;

    std::cout << "I'm Trey, and I'll be your dealer" << std::endl;
}

// Betting Phase Display
void Craps::displayNewRound(bool comeOutRoll) // Pass Bet & Don't Pass Bet
{

    /*
        4/5/25: TODO
        Add Logic:
        - viewing current bets
        - removing bets
        - Checking Balance
        - Adding Funds
    */

    std::cout << "PLACE YOUR BETS!! (Case Sensitive)" << std::endl;

    if (comeOutRoll) // Only Pass or Don't Pass bets
    {

        // Come out roll
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Come Out Roll Bets (Must select 1 if you are the shooter)" << std::endl;
        std::cout << "1. Pass Bet" << std::endl;
        std::cout << "2. Don't Pass Bet" << std::endl;

        // Any-Time Place Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Any-Time Place Bets" << std::endl;
        std::cout << "11. Buy Bet" << std::endl;
        std::cout << "12. Lay Bet" << std::endl;
        std::cout << "13. Big 6 Bet" << std::endl;
        std::cout << "14. Big 8 Bet" << std::endl;

        // Single-Roll Proposition Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Single-Roll Proposition Bets" << std::endl;
        std::cout << "15. Field Bet" << std::endl;
        std::cout << "16. Any Craps Bet" << std::endl;
        std::cout << "17. Any 7s Bet" << std::endl;
        std::cout << "18. Yo Bet" << std::endl;
        std::cout << "19. Ace Deuce Bet" << std::endl;
        std::cout << "20. Snake Eyes Bet" << std::endl;
        std::cout << "21. Box Cars Bet" << std::endl;
        std::cout << "22. Craps And Eleven Bet" << std::endl;
        std::cout << "23. Whirl Bet" << std::endl;
        std::cout << "24. Horn Bet" << std::endl;
        std::cout << "25. Horn High Bet " << std::endl;
        std::cout << "26. All Small Bet" << std::endl;
        std::cout << "27. All Tall Bet" << std::endl;

        // Multi-Roll Proposition Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Multi-Roll Proposition Bets" << std::endl;
        std::cout << "28. Hardways Bet" << std::endl;
        std::cout << "29. Fire Bet" << std::endl;

        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "a. View Bets" << std::endl;
        std::cout << "b. Remove Bets" << std::endl;
        std::cout << "c. Add Funds" << std::endl;
        std::cout << "Finished Betting?" << std::endl;
        std::cout << "q. Quit" << std::endl;
        std::cout << "z. Roll" << std::endl;
    }
    else // Can't do pass/dontPass bets
    {
        // Ongoing Game
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Ongoing Game Bets" << std::endl;
        std::cout << "3. Come Bet" << std::endl;
        std::cout << "4. Don't Come Bet" << std::endl;
        std::cout << "5. Odds On Pass Bet" << std::endl;
        std::cout << "6. Odds On Don't Pass Bet" << std::endl;
        std::cout << "7. Odds On Come Bet" << std::endl;
        std::cout << "8. Odds On Don't Come Bet" << std::endl;
        std::cout << "9. Place To Win Bet" << std::endl;
        std::cout << "10. Place To Lose Bet" << std::endl;

        // Any-Time Place Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Any-Time Place Bets" << std::endl;
        std::cout << "11. Buy Bet" << std::endl;
        std::cout << "12. Lay Bet" << std::endl;
        std::cout << "13. Big 6 Bet" << std::endl;
        std::cout << "14. Big 8 Bet" << std::endl;

        // Single-Roll Proposition Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Single-Roll Proposition Bets" << std::endl;
        std::cout << "15. Field Bet" << std::endl;
        std::cout << "16. Any Craps Bet" << std::endl;
        std::cout << "17. Any 7s Bet" << std::endl;
        std::cout << "18. Yo Bet" << std::endl;
        std::cout << "19. Ace Deuce Bet" << std::endl;
        std::cout << "20. Snake Eyes Bet" << std::endl;
        std::cout << "21. Box Cars Bet" << std::endl;
        std::cout << "22. Craps And Eleven Bet" << std::endl;
        std::cout << "23. Whirl Bet" << std::endl;
        std::cout << "24. Horn Bet" << std::endl;
        std::cout << "25. Horn High Bet " << std::endl;
        std::cout << "26. All Small Bet" << std::endl;
        std::cout << "27. All Tall Bet" << std::endl;

        // Multi-Roll Proposition Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Multi-Roll Proposition Bets" << std::endl;
        std::cout << "28. Hardways Bet" << std::endl;
        std::cout << "29. Fire Bet" << std::endl;

        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "a. View Bets" << std::endl;
        std::cout << "b. Remove Bets" << std::endl;
        std::cout << "c. Add Funds" << std::endl;
        std::cout << "Finished Betting?" << std::endl;
        std::cout << "q. Quit" << std::endl;
        std::cout << "z. Roll" << std::endl;
    }
}

/*
    Game Helper
*/
std::string Craps::inputType(const std::string &userInput)
{
    bool isInt{false};

    for (int i{0}; i < userInput.size(); i++)
    {
        if (!isdigit(userInput[i])) // if any input val is a char, break
            break;

        if (isdigit(userInput[userInput.size() - 1])) // if the last char is a #, return true
            isInt = true;
    }

    if (isInt)
        return "Integer";

    if (userInput.size() != 1)
        return "Invalid";

    return "Char";
}

// 4/5/25 - check on status of this
// TODO: Add a checker to make sure funds are valid
int Craps::getWager() // Applicable for Pass/Don'tPass and Come/DontCome
{
    int wage = 0;
    while (wage < 15)
    {
        std::cout << "How much would you like to wage? (Minimum Bets: $" << minWager << ")" << std::endl;
        std::cin >> wage;
    }

    return wage;
}

void Craps::setP1()
{
    string player1 = "default"; // pass P1 name
    int p1Balance = 0;          // P1 Balance

    std::cout << "What will be your better's name? " << std::endl;
    std::cin >> player1;

    while (p1Balance <= minWager)
    {
        std::cout << "What will be your starting balance ($" << minWager << "+)? " << std::endl;
        if (std::cin >> p1Balance)
            continue;
        else
        {
            std::cout << "Invalid input. Please enter whole numbers\n";

            // Clear error flag on cin
            std::cin.clear();

            // Discard invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // assign invalid value to p1Balance to continue loop
            p1Balance = 0;
        }
    }

    std::cout << p1Balance << " will be your starting balance" << std::endl;

    while (!Gamblers->pushPlayer(player1, p1Balance))
    {
        std::cout << "The name \"" << player1 << "\" is already in use by another player..." << std::endl;
        std::cout << "Enter another player name\n";
        std::cin >> player1;
    }

    std::cout << "returning from setP1 func\n";
}

/*
    Public Functions
*/

// Main Game
void Craps::play()
{
    welcome();
    setP1();
}