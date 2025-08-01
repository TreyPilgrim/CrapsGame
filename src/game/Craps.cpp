#include "Craps.h"

/*
    Private Functions
*/

// Fail Safe
void Craps::failIf(const std::string &errorMsg, int condition)
{
    if (condition == -1)
    {
        std::cerr << "Error: " << errorMsg << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

//-----------------------------------------------------------------------------------------
// Menu Functions

// Welcome Screen
void Craps::welcome()
{
    std::cout << "Welcome to Our Implementation of the game Craps!" << std::endl;
    std::cout << "------------------------------------------------\n";
    std::cout << std::endl;

    std::cout << "I'm Trey, and I'll be your dealer" << std::endl;
    std::cout << "The table's minimum wager is $" << this->minWager << std::endl;
    std::cout << "If you don't know how to play, it's never too late to open Google..." << std::endl;
}

// Betting Phase Display
void Craps::placeWagerOptions() // Pass Bet & Don't Pass Bet
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

    if (this->comeOutRoll) // Only Pass or Don't Pass bets
    {

        // Come out roll
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Come Out Roll Bets (Must select 1 if you are the shooter)" << std::endl;
        std::cout << "1. Pass Bet" << std::endl;
        std::cout << "2. Don't Pass Bet" << std::endl;

        // Any-Time Place Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Any-Time Place Bets" << std::endl;
        std::cout << "9. Place To Win Bet" << std::endl;
        std::cout << "10. Place To Lose Bet" << std::endl;
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
        std::cout << "22. Whirl Bet" << std::endl;
        std::cout << "23. Horn Bet" << std::endl;
        std::cout << "24. Horn High Bet " << std::endl;

        // Multi-Roll Proposition Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Multi-Roll Proposition Bets" << std::endl;
        std::cout << "25. All Small Bet" << std::endl;
        std::cout << "26. All Tall Bet" << std::endl;
        std::cout << "27. Hardways Bet" << std::endl;
        std::cout << "28. Fire Bet" << std::endl;

        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "a. View Bets" << std::endl;
        std::cout << "b. Remove Bets" << std::endl;
        std::cout << "c. Add Funds" << std::endl;
        std::cout << "Finished Betting?" << std::endl;
        std::cout << "q. Quit" << std::endl;
        std::cout << "r. Roll" << std::endl;
        std::cout << "z. Return to Round Choices Menu" << std::endl;
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
        std::cout << "22. Whirl Bet" << std::endl;
        std::cout << "23. Horn Bet" << std::endl;
        std::cout << "24. Horn High Bet " << std::endl;

        // Multi-Roll Proposition Bets
        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "Multi-Roll Proposition Bets" << std::endl;
        std::cout << "25. All Small Bet" << std::endl;
        std::cout << "26. All Tall Bet" << std::endl;

        std::cout << "27. Hardways Bet" << std::endl;
        std::cout << "28. Fire Bet" << std::endl;

        std::cout << "\n------------------------------------------------" << std::endl;
        std::cout << "a. View Bets" << std::endl;
        std::cout << "b. Remove Bets" << std::endl;
        std::cout << "c. Add Funds" << std::endl;
        std::cout << "Finished Betting?" << std::endl;
        std::cout << "q. Quit" << std::endl;
        std::cout << "r. Roll" << std::endl;
        std::cout << "z. Return to Round Choices Menu" << std::endl;
    }
}

void Craps::roundChoices()
{
    int userInput{0};
    char charInput{'t'};
    /*
        - Place Wager
        - View Bet
        - Remove Bet
        - Add Funds
    */
    this->roundChoicesDisplay();

    while ((userInput > 4 || userInput < 1) && charInput != 'q')
    {
        if (!token.readInt(userInput))
        {
            if (!token.readChar(charInput))
                return this->failIf("Craps::roundChoices - invalid input?");

            if (charInput != 'q')
                std::cout << "Invalid option" << std::endl;

            token.isDone();
        }
    }

    switch (userInput)
    {
    case '1':
        this->placeWager();
        break;

    case '2':
        this->viewBets();
        break;

    case '3':
        this->removeBets();
        break;

    case '4':
        this->addFunds();
        break;

    default:
        this->quit();
        break;
    }
}
void Craps::quit()
{
}
void Craps::roundChoicesDisplay()
{
    std::cout << "\nRound Choices \n------------------------------------------------" << std::endl;
    std::cout << "1. Place Wager" << std::endl;
    std::cout << "2. View Bets" << std::endl;
    std::cout << "3. Remove Bets" << std::endl;
    std::cout << "4. Add Funds" << std::endl;
    std::cout << "r. Roll" << std::endl;
    std::cout << "q. Quit" << std::endl;
}

void Craps::placeWager()
{
    double dubInput{0.0};
    int intInput{0};
    char charInput{'t'};
    bool placeWage{true};

    while (placeWage)
    {
        this->placeWagerOptions();

        if (token.readDouble(dubInput))
        {
            std::cout << "Invalid input..." << std::endl;
            token.isDone();
            continue;
        }

        if (!token.readInt(intInput))
        {
            token.readChar(charInput);

            switch (charInput)
            {
            case 'a':
                this->viewBets();
                break;

            case 'b':
                this->removeBets();
                break;

            case 'c':
                this->addFunds();
                break;

            case 'q':
                this->quit();
                break;

            case 'r':
                this->dice->rollDice();
                break;

            case 'z':
                token.isDone();
                return;
                break;

            default:
                std::cout << "Invalid Input..." << std::endl;
                charInput = 't';
                token.isDone();
                continue;
            }

            token.isDone();
            placeWage = false;
            continue;
        }

        if (!this->pushWager(intInput))
        {
            std::cout << "Invalid input..." << std::endl;
            continue;
        }
    }
}

bool Craps::pushWager(const int &intInput)
{
    if (intInput < 1 || intInput > 28)
        return false;

    return this->Gamblers->pushWagerP1Version(intInput);
}

void Craps::viewBets()
{
}

void Craps::removeBets()
{
}

void Craps::addFunds()
{
}

int Craps::getP1Balance()
{
    int balance = 0;
    double doubleChecker{0.0};

    while (balance < minWager)
    {
        std::cout << "How much would you like your starting balance to be? (Minimum Bets: $" << minWager << ")" << std::endl;

        // No betting with coins!
        if (token.readDouble(doubleChecker))
        {
            std::cout << "We don't deal with coins, peasant..." << std::endl;
            token.isDone();
            continue;
        }

        if (!token.readInt(balance))
            std::cout << "Is this even money?? We will throw you out..." << std::endl;

        if (balance < minWager)
            std::cout << "Up the ante..." << std::endl;

        token.isDone();
    }

    return balance;
}

std::string Craps::createUserName()
{
    std::string userName{"default"};

    std::cout << "What will be your better's name? " << std::endl;
    if (!this->token.readLine(userName))
        this->failIf(("Craps::createUserName() - Invalid name input? (" + userName + ")"));

    // Clear stream - done w/ it
    this->token.isDone();
    return userName;
}

void Craps::setP1()
{
    // Member initializers for PlayerList() for creation of P1
    string player1 = this->createUserName();
    int p1Balance = this->getP1Balance();

    // Search For if name is Unique
    while (!this->Gamblers->uniqueName(player1))
    {
        std::cout << "Sorry, that username has already been taken...\n"
                  << std::endl;
        player1 = this->createUserName();
    }

    std::cout << "$" << p1Balance << " will be your starting balance" << std::endl;

    if (!Gamblers->pushPlayer(player1, p1Balance))
        this->failIf("Craps::setP1 - Unable to push P1");

    std::cout << "returning from setP1 func\n";
}

/*
    Public Functions
*/

// Main Game
void Craps::theGame()
{
    welcome();
    setP1();

    int intInput{0};
    double dubInput{0.0};
    char charInput{'t'};

    while (charInput != 'q' || charInput != 'Q')
    {
        this->roundChoicesDisplay();

        if (token.readDouble(dubInput)) // Invalid Input
        {
            std::cout << "Invalid input..." << std::endl;
            continue;
        }

        if (!token.readInt(intInput))
        {
            token.readChar(charInput);

            switch (charInput)
            {
            case 'q':
            case 'Q':

                std::cout << "TODO: Create Game summary log function/cout << playerNode -- Congrats on finally getting far enough to test this part lol" << std::endl;
                continue;
                break;

            case 'r':
            case 'R':

                if (Gamblers->p1HasNoBets())
                {
                    std::cout << "You haven't made any bets yet... you can't roll without bets" << std::endl;
                    break;
                }

                this->dice->rollDice();
                this->dice->printDice();

                break; // Do post roll logic

            default:
                std::cout
                    << "Invalid input..."
                    << std::endl;
                break;
            }

            token.isDone();
            continue;
        }

        // switch (intInput)
        // {
        // case 1:
        // case 2:
        // case 3:
        // case 4:
        // default:
        // }
    }

    std::cout << "Congrats sailor, you made it to the end" << std::endl;
}