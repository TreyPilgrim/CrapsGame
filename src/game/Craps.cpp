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

    std::cout << "PLACE YOUR BETS!!" << std::endl;

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

        std::cout << "\nFinished Betting?" << std::endl;
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

        std::cout << "\nFinished Betting?" << std::endl;
        std::cout << "z. Return to Round Choices Menu" << std::endl;
    }
}

void Craps::roundChoices()
{
    int userInput{0};
    double badInput{0.0};
    char charInput{'t'};
    /*
        1 - Place Wager
        2 - View Bet
        3 - Remove Bet
        4 - Add Funds
        q - quit
        r - roll
    */

    while (charInput != 'q' || charInput != 'Q')
    {
        this->displayRoundChoices();

        if (!token.readInt(userInput))
        {
            token.readChar(charInput);

            switch (charInput)
            {
            case 'q':
            case 'Q':

                // Craps::quit() - Needs to send flag to end porogram and close out
                // Will break loop... consider making functionality on the outside of this function
                token.isDone(); // clear stream before breaking loop
                continue;
                break;

            case 'r':
            case 'R':
                // Craps::readyToRoll(const playerNode shooter)
                // Craps::roll()
                // Craps::EvaluateAVL(int arr* daDie)
                //  - Should output what is happening with user bets

                break;

            default:
                std::cout << "An invalid input..." << std::endl;
                token.isDone(); // clear stream
                break;
            }

            token.isDone(); // Clear stream before next iteration
            continue;
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
            std::cout << "Invalid input (1-4)" << std::endl;
            token.isDone();
            break;
        }

        token.isDone(); // clear stream before next iteration
    }

    std::cout << "Exiting: Craps::roundChoices" << std::endl;
}
void Craps::quit()
{
}
void Craps::displayRoundChoices()
{
    std::cout << "\nRound Choices \n------------------------------------------------" << std::endl;
    std::cout << "1. Place Wager" << std::endl;
    std::cout << "2. View Bets" << std::endl;
    std::cout << "3. Remove Bets" << std::endl;
    std::cout << "4. Add Funds" << std::endl;
    std::cout << "r. Roll" << std::endl;
    std::cout << "q. Quit" << std::endl;
}

void Craps::placeWager() // update
{
    double dubInput{0.0};
    int intInput{0};
    char charInput{'t'};
    bool wagerIsPlaced{false};

    while (!wagerIsPlaced)
    {
        this->placeWagerOptions(); // Display bet options - comeOutRoll Based

        if (!token.readInt(intInput))
        {
            token.readChar(charInput);

            switch (charInput)
            {
            case 'a':
            case 'A':
                this->viewBets(); // TODO
                break;

            case 'b':
            case 'B':
                this->removeBets(); // TODO
                break;

            case 'c':
            case 'C':
                this->addFunds(); // TODO
                break;

            case 'z': // Go back to main menu
            case 'Z':
                token.isDone(); // clear stream before returning
                return;
                break;

            default:
                std::cout << "Invalid Input chap..." << std::endl;
                break;
            }

            token.isDone(); // clear stream before returning
            continue;       // restart loop for next input
        }

        // Integer input was successful

        // Check input is withing proper bounds - ComeOutRoll sensitive
        if (!this->validBetTypeSelected(intInput))
        {
            std::cout << "Invalid Bet choice... " << intInput << " is not a valid input." << std::endl;
            token.isDone(); // clear stream before restarting loop
            continue;
        }

        int wageType = intInput;
        betPtr bet;

        /*
            TODO:
            - Create poly function that will allow me to call once and it will call the appropriate function that will return a BetNode of the appropriate type
            - pass the wageType into the function so it knows what function to use
        */
        switch (wageType)
        {
        case 1: // Pass - Place bet
            break;

        case 2: // Dont Pass - Place Bet
            break;

        case 3: // Come - Place Bet
            break;

        case 4: // Dont Come - Place Bet
            break;

            //  Odds On Bets ([dont] pass, [dont] come)

        case 5: // Odds On Pass - Needs to bet on existing Pass Bet

            /*
             * getPassBet(); - return into an vector
             * display options - for loop most likely
             * Get input
             * get point from the pass bet of choice
             */

        case 6: // Odds on Dont Pass - Needs to bet on existing Don't Pass Bet

            /*
             * getDontPassBet(); - return into an vector
             * display options - for loop most likely
             * Get input
             * get point from the dont pass bet of choice
             */
        case 7: // Odds on Come - Needs to bet on existing Come Bet

            /*
             * getComeBet(); - return into an vector
             * display options - for loop most likely
             * Get input
             * get point from the Come bet of choice
             */
        case 8: // Odds on Dont Come - Needs to bet on existing Don't Come Bet

            /*
             * getDontComeBet(); - return into an vector
             * display options - for loop most likely
             * Get input
             * get point from the Dont Come bet of choice
             */

            // oddsOnBet(const int betChoiceNum)
            break;

            // Placement Bets

        case 9: // Place to win - User picks point
            break;

        case 10: // Place to Lose - User Picks Point
            break;

        case 11: // Buy Bet - User picks point
            break;

        case 12: // Lay Bet - User Picks Point
            break;

        case 13: // Big 6 - Predetermined point
            break;

        case 14: // Big 8 - Predetermined point
            break;

        case 15: // Field - No point needed
            break;

        case 16: // Any Craps - No Point Needed
            break;

        case 17: // Any Seven - Place Bet
            break;

        case 18: // Yo - Predetermined Point; place bet
            break;

        case 19: // Ace Deuce - Predetermined Point; place bet
            break;

        case 20: // Snake Eyes - Predetermined Point; place bet
            break;

        case 21: // Box Car - Predetermined Point
            break;

        case 22: // World - Place Bet (?)
            break;

        case 23: // Horn - Place Bet
            break;

        case 24: // Horn High - Select High Number
            break;

        case 25: // All Small - Place Bet
            break;

        case 26: // All Tall - Place Bet
            break;

        case 27: // HardWay - User selects hardway type
            break;

        case 28: // Fire - Place Bet and vibe twin0..
            break;

        default:
            this->failIf("Invalid input for BetOptions - Craps::placeWager()");
        }
        /* Call PlayersList to push
            - need to determine if point is needed for the push
            * options: 5 6 7 8 9 10 11 12 24 27
        */

        // Have the Initializer handle point setting
        // Some require a point chosen, some chose based on other factors. too much to care about from here

        // Determine if Bet Type Needs a point
        if (this->isBetTypeThatNeedsPoint(wageType))
        {
            // Get Point
            /*
                - Decide if this matters
                - Do i want to just call the SetWager(int wageType) and let the initializer handle point setting or get it on the frontend?
                - Error handling is going to be an issue
            */
        }
    }
}

bool Craps::validBetTypeSelected(const int intInput)
{
    if (this->comeOutRoll)
    {
        // 1-2 & 9-28
        if ((intInput > 0 && intInput < 3) || (intInput > 8 && intInput < 29))
            return true;
    }
    else
    {
        // 3-28
        if (intInput > 2 && intInput < 29)
            return true;
    }

    return false; // False otherwise
}

bool Craps::isBetTypeThatNeedsPoint(const int intInput)
{
    int pointInputs[10] = {5, 6, 7, 8, 9, 10, 11, 12, 24, 27};

    for (auto val : pointInputs)
    {
        if (intInput == val)
            return true;
    }

    return false;
}

bool Craps::pushWager(const int &intInput) // UPDATE
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

p1Ptr Craps::setP1()
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
    this->p1 = setP1();

    // Player 1 is set, go about the game logic
    this->roundChoices();

    std::cout << "Congrats sailor, you made it to the end" << std::endl;
}