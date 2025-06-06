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

bool BetNode::validPayout(const int wage)
{

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

int BetNode::getNorthVal(int wage)
{
    while (!this->validPayout(wage))
    {
        wage++;
    }

    return wage;
}

int BetNode::getSouthVal(int wage)
{
    while (!this->validPayout(wage) && wage >= MIN_WAGE)
    {
        wage--;
    }

    if (wage < MIN_WAGE) // no valid South
        return 0;

    return wage;
}

arr BetNode::getNextValues(const int wage)
{
    arr tmp = std::shared_ptr<int[]>(new int[2]);

    tmp[0] = this->getNorthVal(wage); // Next
    tmp[1] = this->getSouthVal(wage); // Previous

    return tmp;
}

// Make sure wage entered is >= MINBET
int BetNode::setTheWagePhase()
{
    int wage;
    bool validInt{false};

    while (!validInt)
    {
        std::cout << "Enter a wage amount ($" << MIN_WAGE << "+): ";
        std::cin >> wage;

        if (!this->validInt()) // Invalid Input
        {
            std::cout << "Invalid Input... Please enter an integer" << std::endl;
            continue;
        }
        else if (wage < MIN_WAGE) // too small a wage
        {
            std::cout << "Invalid Input... Please enter a value greater than $" << MIN_WAGE << std::endl;
            continue;
        }
        else if (!this->validPayout(wage)) // Virtual part - payout == whole number
        {
            arr tmp;
            tmp = this->getNextValues(wage);

            if (tmp[0] == 0 && tmp[1] == 0) // no valid north nor south
            {
                throw std::runtime_error("ERROR BetNode::setTheWagePhase - check logging for getNextValues()");
                return -1;
            }
            else if (tmp[1] == 0) // No valid south
            {
                std::cout << tmp[0] << " is the next valid wage amount... the next minimum value is below the minimum wager amount ($" << MIN_WAGE << ")\n"
                          << std::endl;
                continue;
            }
            else if (tmp[0] == 0) // no valid north
            {
                std::cout << "Broke-Boi, not enough bread to bet the next valid wager... \nHow about the previous valid wager ($" << tmp[1] << ")?" << std::endl;
                continue;
            }

            throw std::runtime_error("BETNODE::setTheWagePhase -- unknown condition\n");
            return -1;
        }

        validInt = true;
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

// Wager - and helpers related
void BetNode::setWage()

{
    if (this->payoutOdds.empty())
    {
        std::cout << "Default payout odds initialized: BetNode\n"
                  << std::endl;
        return;
    }
    this->wager = std::move(this->setTheWagePhase());
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

bool PassLineBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

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

bool DontPassLineBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool ComeBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool DontComeBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool Big6Bet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool Big8Bet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool FieldBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool AnyCrapsBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool AnySevenBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool YoBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool AceDeuceBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool SnakeEyesBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool BoxCarsBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true; // all payouts work w/ 1:1
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

bool WorldBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true;
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
bool AllSmallBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true;
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

bool AllTallBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true;
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

bool HardwayBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true;
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

bool FireBet::validPayout(const int wage)
{
    if (wage < MIN_WAGE)
        return false;

    return true;
}