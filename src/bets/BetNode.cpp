#include "BetNode.h"
#include <ctime>
const int ARR_SIZE = 7;
const int MIN_WAGE = 15;
const double epsilon = 1e-6; // 0.000001

/*-----------------------------------------------------------------------------------------
   BetNode Functions
*/
/*
    Private Functions
*/

// Random number 0-9 Generator
int BetNode::randNum()
{
    return rand() % 10;
}

/*
    Protected Functions
*/
// Fail Safe
void BetNode::failIf(const std::string &errorMsg, int condition)
{
    if (condition == -1)
    {
        std::cerr << "Error: " << errorMsg << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

bool BetNode::validInt() // CHECK
{
    if (std::cin.fail())
    {
        std::cin.clear();                                                   // clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input

        return false;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any trailing input
    return true;
}

bool BetNode::validPayout(const int wage, const int balance)
{

    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    auto it = payoutOdds.find(this->getPoint());
    if (it == payoutOdds.end()) // Does not exist
        return false;

    double odds = it->second;
    double payout = odds * wage;

    /*

        std::fabs
        - checks the absolute value
            * the true decimal value without rounding up/down - i.e. 0.999...9 or 0.000..1

        std::rounds(payout)
        - rounds payout to nearest whole number

        payout - std::rounds(payout)
        - How far is payout from the closest whole number

        < epsilon
        - checks if difference is smaller than the threshold
            * # is close enough to a whole number

        gonna return true on whole number; false otherwise

    */
    return std::fabs(payout - std::round(payout)) < epsilon;
}

int BetNode::getNorthVal(int wage, const int balance)
{
    if (wage > balance)
        return -1;

    while (!this->validPayout(wage, balance))
    {
        if (wage == balance)
            return 0;

        wage++;
    }

    return wage;
}

int BetNode::getSouthVal(int wage, const int balance)
{
    if (wage > balance) // Run With max bet if wage is over balance
        return this->getSouthVal(balance, balance);

    while (!this->validPayout(wage, balance) && wage >= MIN_WAGE) // Go until a valid payout is found
        wage--;

    if (wage < MIN_WAGE) // Make sure it is above the minimum wage amount
        return 0;

    return wage;
}

int BetNode::evaluateNextVal(const arr wageArr, const int &balance)
{

    // Error
    (wageArr[0] == 0 && wageArr[1] == 0) ? this->failIf("BetNode::setTheWagePhase - check logging for getNextValues()") : (void)0; // (void)0 - do nothing

    if (wageArr[0] > balance) // Too poor for a north
    {
        std::cout << "Broke-Boi, not enough bread to bet the next valid wager... \nConsider adding more wages, the ATM isn't too far from here..." << std::endl;

        if (wageArr[1] == 0)
        {
            std::cout << "There smallest valid wager amount is less than the table's minimum ($" << MIN_WAGE << ")\nOnly option is to add more wages" << std::endl;

            return -1;
        }

        return 0;
    }

    if (wageArr[1] == 0) // No valid south above MIN_Wage
    {
        std::cout << wageArr[0] << " is the next valid wage amount... the next minimum value is below the minimum wager amount ($" << MIN_WAGE << ")\n"
                  << std::endl;

        return 0;
    }

    return 1;
}

arr BetNode::getNextValues(int wage, const int balance)
{
    arr tmp = std::shared_ptr<int[]>(new int[2]);

    tmp[0] = this->getNorthVal(wage, balance); // Next
    tmp[1] = this->getSouthVal(wage, balance); // Previous

    return tmp;
}

// Make sure wage entered is >= MINBET
int BetNode::setTheWagePhasePointIndependent(const int balance)
{
    double dubVal{0.0};
    int wage{0};
    bool validWage{false};

    while (!validWage)
    {
        std::cout << "How much are we waging today?" << std::endl;

        // User entered a decimal value
        if (token.readDouble(dubVal))
        {
            std::cout << "We don't deal with coins here... \nBig Money™️ only" << std::endl;

            token.isDone();
            continue;
        }
        else if (!token.readInt(wage)) // invalid input
        {
            std::cout << "Invalid input..." << std::endl;

            token.isDone();
            continue;
        }
        else if (wage < MIN_WAGE) // Wage is below minimum wage value
        {
            std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;

            token.isDone();
            continue;
        }

        // Checking validity of the payout
        if (!validPayout(wage, balance)) // Wage entered produces invalid payout (decimal)
        {
            arr validWages = this->getNextValues(wage, balance);

            if (this->evaluateNextVal(validWages, balance) == -1) // Invalid Funds for a valid bet - user must add funds first
            {
                std::cout << "No valid funds for any bet... User must add Funds" << std::endl;

                token.isDone();
                return -1;
            }

            token.isDone();
            continue;
        }

        // set condition to true
        validWage = true;
    }

    return wage;
}

arr BetNode::randomArr()
{
    arr tmp = std::shared_ptr<int[]>(new int[ARR_SIZE]);

    for (int i = 0; i < ARR_SIZE; i++)
    {
        tmp[i] = randNum();
    }

    return tmp;
}

// Converting array of random #s into strings so ID can be made
std::string BetNode::arrToString(arr tmp)
{
    std::string str;

    for (int i = 0; i < ARR_SIZE; i++)
    {
        str += std::to_string(tmp[i]);
    }

    return str;
}

// ID Generator
std::string BetNode::generateID() // User Input is the type of bet
{
    std::string prefix, numString, ID;

    prefix = "0";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Public Functions
*/

void BetNode::generateNewID()
{
    this->setID(this->generateID());
}

// Set ID
void BetNode::setID(std::string str)
{
    this->betId = std::move(str);
    std::cout << "Node's ID: " << this->betId << std::endl;
}

// balance factor
void BetNode::setBF(int balFact)
{
    this->bf = std::move(balFact);
}

// height
void BetNode::setHeight(int h)
{
    this->height = std::move(h);
}

void BetNode::setPoint(int point)
{
    this->point = std::move(point);
}

// Set the wager
void BetNode::setWage(const int wage)
{
    this->wager = wage;
}

//-----------------------------------------------------------------------------------------
// Getters

// id getter
std::string BetNode::getID()
{
    return this->betId;
}

// balance factor
int BetNode::getBF()
{
    return this->bf;
}

// height
int BetNode::getHeight()
{
    return this->height;
}

// Get Point
int BetNode::getPoint()
{
    return this->point;
}

// wage amount
int BetNode::getWager()
{
    return this->wager;
}

// bet type
char BetNode::getBetType()
{
    return this->betId[0];
}

// How many kids does the node have?
int const BetNode::childSupport()
{
    return (this->lChild != nullptr && this->rChild != nullptr)   ? 2
           : (this->lChild != nullptr || this->rChild != nullptr) ? 1
                                                                  : 0;
}

//==============================================================================================================================================
// Polymorphism Function Definitions

/*
    Pass Line Bet
*/
//----------------------------------------------------------------------------------------
/// Private

// Generate Unique ID
std::string PassLineBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "A";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool PassLineBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ 1:1
}

//----------------------------------------------------------------------------------------
/// Public

// Update the first roll value - point needs to be establish
void PassLineBet::notFirstRoll()
{
    this->firstRoll = false;
}

// // Winning Ticket Checker
// bool PassLineBet::winningTicket(const int diceVal)
// {
//     if (this->firstRoll)
//     {
//         // iterator for searching
//         auto it = payoutOdds.find(diceVal);

//         // return false if value not found - does not always mean it is a loser... don't assume
//         return (it == winningVals.end()) ? false : true;
//     }

//     // Point Established
//     return (diceVal == this->getPoint()) ? true : false;
// }

// Losing Ticket Checker
bool PassLineBet::losingTicket(const int diceVal)
{
    if (this->firstRoll)
    {
        // Iterator for searching
        auto it = losingVals.find(diceVal);

        // Return false if value not found - does not always mean winner... don't assume
        return (it == losingVals.end()) ? false : true;
    }

    // Point Established
    return (diceVal == 7) ? true : false;
}

/*
    Don't Pass Line Bet
*/

// ID Generator
std::string DontPassLineBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "B";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool DontPassLineBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

// Update the first roll value - point needs to be establish
void DontPassLineBet::notFirstRoll()
{
    this->firstRoll = false;
}

// // Winning Ticket Checker
// bool DontPassLineBet::winningTicket(const int diceVal)
// {
//     if (this->firstRoll)
//     {
//         // iterator for searching
//         auto it = winningVals.find(diceVal);

//         // return false if value not found - does not always mean it is a loser... don't assume
//         return (it == winningVals.end()) ? false : true;
//     }

//     // Point Established
//     return (diceVal == 7) ? true : false;
// }

// // Losing Ticket Checker
// bool DontPassLineBet::losingTicket(const int diceVal)
// {
//     if (this->firstRoll)
//     {
//         // Iterator for searching
//         auto it = losingVals.find(diceVal);

//         // Return false if value not found - does not always mean winner... don't assume
//         return (it == losingVals.end()) ? false : true;
//     }

//     // Point Established
//     return (diceVal == this->point) ? true : false;
// }

//-----------------------------------------------------------------------------------------
/*
    Post-Come Out Roll Bets
*/

/*
    Come Bet
*/

std::string ComeBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "C";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool ComeBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

// Update the first roll value - point needs to be establish
void ComeBet::notFirstRoll()
{
    this->firstRoll = false;
}

// // Winning Ticket Checker
// bool ComeBet::winningTicket(const int diceVal)
// {
//     if (this->firstRoll)
//     {
//         // iterator for searching
//         auto it = winningVals.find(diceVal);

//         // return false if value not found - does not always mean it is a loser... don't assume
//         return (it == winningVals.end()) ? false : true;
//     }

//     // Point Established
//     return (diceVal == this->point) ? true : false;
// }

// // Losing Ticket Checker
// bool ComeBet::losingTicket(const int diceVal)
// {
//     if (this->firstRoll)
//     {
//         // Iterator for searching
//         auto it = losingVals.find(diceVal);

//         // Return false if value not found - does not always mean winner... don't assume
//         return (it == losingVals.end()) ? false : true;
//     }

//     // Point Established
//     return (diceVal == 7) ? true : false;
// }

//-----------------------------------------------------------------------------------------
// Derived Class : Dont Come Bet

// ID Generator
std::string DontComeBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "D";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}
// Update the first roll value - point needs to be establish
void DontComeBet::notFirstRoll()
{
    this->firstRoll = false;
}

// // Winning Ticket Checker
// bool DontComeBet::winningTicket(const int diceVal)
// {
//     if (this->firstRoll)
//     {
//         // iterator for searching
//         auto it = winningVals.find(diceVal);

//         // return false if value not found - does not always mean it is a loser... don't assume
//         return (it == winningVals.end()) ? false : true;
//     }

//     // Point Established
//     return (diceVal == 7) ? true : false;
// }

bool DontComeBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

// // Losing Ticket Checker
// bool DontComeBet::losingTicket(const int diceVal)
// {
//     if (this->firstRoll)
//     {
//         // Iterator for searching
//         auto it = losingVals.find(diceVal);

//         // Return false if value not found - does not always mean winner... don't assume
//         return (it == losingVals.end()) ? false : true;
//     }

//     // Point Established
//     return (diceVal == this->point) ? true : false;
// }

/*
    Odds On Pass Bet
*/

// Private

std::string OddsOnPassBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "E";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Odds On Don't Pass Bet
*/
std::string OddsOnDontPassBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "F";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Odds On Come Bet
*/
std::string OddsOnComeBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "G";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Odds On Don't Come Bet
*/

std::string OddsOnDontComeBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "H";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Place To Win bet
*/
std::string PlaceToWinBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "I";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Place To Lose Bet
*/
std::string PlaceToLoseBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "J";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Buy Bet
*/
std::string BuyBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "K";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Lay Bet
*/
std::string LayBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "L";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Big 6 Bet
*/
std::string Big6Bet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "M";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool Big6Bet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Big 8 Bet
*/
std::string Big8Bet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "N";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool Big8Bet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Field Bet
*/
std::string FieldBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "O";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool FieldBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Any Craps Bet
*/

std::string AnyCrapsBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "P";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool AnyCrapsBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Any Seven Bet
*/
std::string AnySevenBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "Q";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool AnySevenBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Yo Bet
*/

std::string YoBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "R";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool YoBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Ace Deuce Bet
*/
std::string AceDeuceBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "S";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool AceDeuceBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Snake Eyes
*/
std::string SnakeEyesBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "T";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool SnakeEyesBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Box Car Bet
*/
std::string BoxCarsBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "U";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool BoxCarsBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    World Bet
*/
std::string WorldBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "V";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool WorldBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Horn Bet
*/
std::string HornBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "W";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    Horn High Bet
*/
std::string HornHighBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "X";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

/*
    All Small Bet
*/
std::string AllSmallBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "Y";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}
bool AllSmallBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    All Tall Bet
*/
std::string AllTallBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "Z";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool AllTallBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Hardways Bet
*/

std::string HardwayBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "a";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool HardwayBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}

/*
    Fire Bet
*/
std::string FireBet::generateID()
{
    std::string prefix, numString, ID;

    prefix = "b";

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

bool FireBet::validPayout(const int wage, const int balance)
{
    if (balance < wage)
    {
        std::cout << "Aspirations bigger than you britches... \nYou don't have that kinda loot for those kinda wagers" << std::endl;

        return false;
    }

    else if (wage < MIN_WAGE)
    {
        std::cout << "Value entered is below the minimum wage limit ($" << MIN_WAGE << ")" << std::endl;
        return false;
    }

    return true; // all payouts work w/ whole number odds
}
