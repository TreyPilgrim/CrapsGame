#pragma once
#include <iostream>
#include <unordered_set>
#include <memory>
#include <map>
#include <string>
#include <list>

// BetNode CLass
class BetNode;
// Type Alias
using betNodePtr = std::shared_ptr<BetNode>;

/*
    TODO
    create a "toWin" value to provide quick
    - setters
    - getters
*/

class BetNode
{
private:
    // Tree Attributes
    int bf{0}, height{0};

    std::string betId{"void"};

    int wage{0};
    int toWin{0};
    int point{0};
    std::list<int> hits; // certain bets need multiple rolls to win. tracker of winning hits/rolls

    // Generate prefix
public:
    // Tree Attributes
    betNodePtr lChild{nullptr};
    betNodePtr rChild{nullptr};

    // Constructord
    BetNode()
    {
        std::cout << "BetNode Initialized: Default Constructor" << std::endl;
    }

    BetNode(int wage, int point = 0)
    {
        this->setWager(wage);
        this->setPoint(point);
        std::cout << "BetNode Initialized\n";
        std::cout << "Wage: " << this->getWager() << std::endl;

        if (this->getPoint() != 0)
            std::cout << "Point: " << this->getPoint() << std::endl;

        std::cout << "=============================================================" << std::endl;
    }

    // // Checkers
    // bool validBet(int);

    // Setters
    void setID(std::string str);
    void setBF(int balFact);
    void setHeight(int h);
    void setBetType(int betNum);
    void setPoint(int point);
    // Wager - and helpers related
    bool validWage(int wage);
    void setWager(int wage);

    // Getters
    std::string getID();
    int getBF();
    int getHeight();
    int getPoint();
    int getWager();
    char getBetType();
    int const childSupport();
};

//-----------------------------------------------------------------------------------------
// Come Out Roll Bets -- Add pointer to
// Pass Line Bet - 1:1 payout
class PassLineBet : public BetNode
{
private:
    bool firstRoll{true};
    int point{0};
    const std::unordered_set<int> winningVals{7, 11};
    const std::unordered_set<int> losingVals{2, 3, 12};
    betNodePtr oddsOnPassPtr;

public:
    PassLineBet()
    {
        std::cout << "Pass Line Bet Node Initialized: Default" << std::endl;
    }

    PassLineBet(int wage, int point = 0) : BetNode(wage, point)
    {
        std::cout << "Pass Line Bet Initializer" << std::endl;
    }
    // Possible virutal function tbd
    void notFirstRoll();

    // TODO (5/3/25) --- make these functions virtual
    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Don't Pass Line Bet - 1:1 payout
class DontPassLineBet : public BetNode
{
private:
    bool firstRoll{true};
    int point{0};
    betNodePtr oddsOnDontPassPtr;

    const std::unordered_set<int> winningVals{2, 3, 12};
    const std::unordered_set<int> losingVals{7, 11};

public:
    DontPassLineBet() : BetNode()
    {
        std::cout << "Dont Pass Line Bet Node Initialized: Default" << std::endl;
    }
    DontPassLineBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Don't Pass Line Bet Node Initialized" << std::endl;
    }
    void notFirstRoll();

    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Post Come Out Roll Bets

// Come Bet - 1:1 payout
class ComeBet : public BetNode
{
private:
    bool firstRoll{true};
    int point{0};
    const std::unordered_set<int> winningVals{7, 11};
    const std::unordered_set<int> losingVals{2, 3, 12};
    betNodePtr oddsOnComePtr;

public:
    ComeBet() : BetNode()
    {
        std::cout << "Come Bet Initialized: Default" << std::endl;
    }
    ComeBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Come Bet Initialized\n"
                  << std::endl;
    }
    // Possible virutal function tbd
    void notFirstRoll();

    // TODO (5/3/25) --- make these functions virtual
    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Don't Come Bet - 1:1 payout
class DontComeBet : public BetNode
{
private:
    bool firstRoll{true};
    int point{0};

    const std::unordered_set<int> winningVals{2, 3, 12};
    const std::unordered_set<int> losingVals{7, 11};
    betNodePtr oddsOnDontComePtr;

public:
    DontComeBet() : BetNode()
    {
        std::cout << "Don't Come Bet Initialized: Default" << std::endl;
    }
    DontComeBet(int wage, int point)
    {
        std::cout << "Dont Come Bet Initialized\n"
                  << std::endl;
    }
    void notFirstRoll();

    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

/*
    Be Mindful
    - Odds on ____ Bets can only be made if line/come bet exists already
        -> Point must be established
    - Odds on [Dont] Pass Bets can only be made once -> [Dont] Come can be made once per come bet

    TODO 5/4/25
        - Add pointer to one of these nodes in [Dont] Pass/Come bets
            -> ensure that each [Dont] Pass/Come bet has 1 corresponding  Odds bet
        Completed:

        - Add functionality to

*/
// Odds on Pass Bet
class OddsOnPassBet : public BetNode
{
private:
    int point{};
    std::map<int, double> payoutOdds{
        {4, 2.0},
        {5, 3 / 2},
        {6, 6 / 5},
        {8, 6 / 5},
        {9, 3 / 2},
        {10, 2.0}};

public:
    OddsOnPassBet() : BetNode()
    {
        std::cout << "Odds on Pass Bet Initialized: Default" << std::endl;
    }
    OddsOnPassBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Odds on Pass Bet Initialized\n"
                  << std::endl;
    }
};

// Odds on Don't Pass Bet
class OddsOnDontPassBet : public BetNode
{
private:
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 1 / 2},
        {5, 2 / 3},
        {6, 5 / 6},
        {8, 5 / 6},
        {9, 2 / 3},
        {10, 1 / 2}};

public:
    OddsOnDontPassBet() : BetNode()
    {
        std::cout << "Odds On Dont Pass Bet: Default" << std::endl;
    }

    OddsOnDontPassBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Odds On Dont Pass Bet\n"
                  << std::endl;
    }
};

// Odds on Come Bet
class OddsOnComeBet : public BetNode
{
private:
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 2.0},
        {5, 3 / 2},
        {6, 6 / 5},
        {8, 6 / 5},
        {9, 3 / 2},
        {10, 2.0}};

public:
    OddsOnComeBet() : BetNode()
    {
        std::cout << "Odds On Come Bet Initialized: Default" << std::endl;
    }

    OddsOnComeBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Odds On Come Bet Initialized\n"
                  << std::endl;
    }
};

// Odds on Don't Come Bet
class OddsOnDontComeBet : public BetNode
{
private:
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 1 / 2},
        {5, 2 / 3},
        {6, 5 / 6},
        {8, 5 / 6},
        {9, 2 / 3},
        {10, 1 / 2}};

public:
    OddsOnDontComeBet() : BetNode()
    {
        std::cout << "Odds On Dont Come Bet Initialized: Default\n"
                  << std::endl;
    }

    OddsOnDontComeBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Odds On Dont Come Bet Initialized\n"
                  << std::endl;
    }
};

// Place Bets - Made any time after come out roll

// Place to Win Bet
class PlaceToWinBet : public BetNode
{
private:
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 9 / 5},
        {5, 7 / 5},
        {6, 7 / 6},
        {8, 7 / 6},
        {9, 7 / 5},
        {10, 9 / 5}};

public:
    PlaceToWinBet() : BetNode()
    {
        std::cout << "Place To Win Bet Initialized: Default\n"
                  << std::endl;
    }

    PlaceToWinBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Place To Win Bet Initialized\n"
                  << std::endl;
    }
};

// Place to Lose Bet
class PlaceToLoseBet : BetNode
{
private:
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 5 / 11},
        {5, 5 / 8},
        {6, 4 / 5},
        {8, 4 / 5},
        {9, 5 / 8},
        {10, 5 / 11}};

public:
    PlaceToLoseBet() : BetNode()
    {
        std::cout << "Place To Lose Bet Initialized: Default\n"
                  << std::endl;
    }

    PlaceToLoseBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Place To Lose Bet Initialized\n"
                  << std::endl;
    }
};

// Buy Bet - 5% Commission
class BuyBet : public BetNode
{
private:
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 2.0},
        {5, 3 / 2},
        {6, 6 / 5},
        {8, 6 / 5},
        {9, 3 / 2},
        {10, 2.0}};

public:
    BuyBet() : BetNode()
    {
        std::cout << "Buy Bet Initialized: Default\n"
                  << std::endl;
    }

    BuyBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Buy Bet Initialized\n"
                  << std::endl;
    }
};

// Lay Bet - 5% Commission
class LayBet : public BetNode
{
private:
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 1 / 2},
        {5, 2 / 3},
        {6, 5 / 6},
        {8, 5 / 6},
        {9, 2 / 3},
        {10, 1 / 2}};

public:
    LayBet() : BetNode()
    {
        std::cout << "Lay Bet Initialized: Default\n"
                  << std::endl;
    }

    LayBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Lay Bet Initialized\n"
                  << std::endl;
    }
};

// Big 6 Bet
class Big6Bet : public BetNode
{
private:
    // int point{6};
    std::map<int, double> payoutOdds{
        {6, 1.0}};

public:
    Big6Bet() : BetNode()
    {
        std::cout << "Big 6 Bet Initialized: Default\n"
                  << std::endl;
    }

    Big6Bet(int wage) : BetNode(wage, 6)
    {
        std::cout << "Big 6 Bet Initialized\n"
                  << std::endl;
    }
};

// Big 8 Bet
class Big8Bet : public BetNode
{
private:
    // int point{8};
    std::map<int, double> payoutOdds{
        {8, 1.0}};

public:
    Big8Bet() : BetNode()
    {
        std::cout << "Big 8 Bet Initialized: Default\n"
                  << std::endl;
    }

    Big8Bet(int wage) : BetNode(wage, 8)
    {
        std::cout << "Big 8 Bet Initialized\n"
                  << std::endl;
    }
};

// Single-Roll Proposition Bets - Any Time

// Field Bet
class FieldBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 2.0},
        {3, 1.0},
        {4, 1.0},
        {9, 1.0},
        {10, 1.0},
        {11, 1.0},
        {12, 2.0}};

public:
    FieldBet() : BetNode()
    {
        std::cout << "Field Bet Initialized: Default\n"
                  << std::endl;
    }

    FieldBet(int wage) : BetNode(wage)
    {
        std::cout << "Field Bet Initialized\n"
                  << std::endl;
    }
};

// Any Craps Bet
class AnyCrapsBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 7.0},
        {3, 7.0},
        {12, 7.0}};

public:
    AnyCrapsBet() : BetNode()
    {
        std::cout << "Any Craps Bet Initialized: Default\n"
                  << std::endl;
    }

    AnyCrapsBet(int wage) : BetNode(wage)
    {
        std::cout << "Any Craps Bet Initialized\n"
                  << std::endl;
    }
};

// Any Seven Bet
class AnySevenBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {7, 4.0}};

public:
    AnySevenBet() : BetNode()
    {
        std::cout << "Any Seven Bet Initialized: Default\n"
                  << std::endl;
    }

    AnySevenBet(int wage) : BetNode(wage, 7)
    {
        std::cout << "Any Seven Bet Initialized\n"
                  << std::endl;
    }
};

// Yo Bet
class YoBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {11, 15.0}};

public:
    YoBet() : BetNode()
    {
        std::cout << "Yo Bet Initialized: Default" << std::endl;
    }

    YoBet(int wage) : BetNode(wage, 11)
    {
        std::cout << "Yo Bet Initialized\n"
                  << std::endl;
    }
};

// Ace Deuce Bet
class AceDeuceBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {3, 15.0}};

public:
    AceDeuceBet() : BetNode()
    {
        std::cout << "Ace Deuce Bet Initialized\n"
                  << std::endl;
    }

    AceDeuceBet(int wage) : BetNode(wage, 3)
    {
        std::cout << "Ace Deuce Bet Initialized\n"
                  << std::endl;
    }
};

// Snake Eyes Bet
class SnakeEyesBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 30.0}};

public:
    SnakeEyesBet() : BetNode()
    {
        std::cout << "Snake Eyes Bet Initialized: Default\n"
                  << std::endl;
    }

    SnakeEyesBet(int wage) : BetNode(wage, 2)
    {
        std::cout << "Snake Eyes Bet Initialized\n"
                  << std::endl;
    }
};

// Box Cars Bet
class BoxCarsBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {12, 30.0}};

public:
    BoxCarsBet() : BetNode()
    {
        std::cout << "Box Cars Bet Initialized\n"
                  << std::endl;
    }

    BoxCarsBet(int wage) : BetNode(wage, 12)
    {

        std::cout << "Box Cars Bet Initialized\n"
                  << std::endl;
    }
};

// World Bet - Wage mus be divisible by 5
class WorldBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 30.0},
        {3, 15.0},
        {7, 4.0},
        {11, 15.0},
        {12, 30.0}};

public:
    WorldBet() : BetNode()
    {
        std::cout << "World Bet Initialized: Default\n"
                  << std::endl;
    }

    WorldBet(int wage) : BetNode(wage)
    {
        std::cout << "World Bet Initialized\n"
                  << std::endl;
    }
};

// Horn Bet
// Wage is divided by 4 (evenly placed on 2, 3, 11, 12) depending on whats rolled determines payout
// Dividing each payout by 4 to account for the
// When adding returning winnings - don't forget to accomodate for divding 4 *******
class HornBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 30 / 4},
        {3, 15 / 4},
        {11, 15 / 4},
        {12, 30 / 4}};

public:
    HornBet() : BetNode()
    {
        std::cout << "Horn Bet Initialized: Default\n"
                  << std::endl;
    }

    HornBet(int wage) : BetNode(wage)
    {
        std::cout << "Horn Bet Initialized\n"
                  << std::endl;
    }
};

// Horn High Bet
// Wage must be an increment of 5
// High # payout is (wage/5 * 30(or 15, depends what hits) + (wage/5) ? -- double check later
// Other Payouts are (wage/5)
class HornHighBet : public HornBet
{
private:
    int highNumber{};

public:
    HornHighBet() : HornBet()
    {
        std::cout << "Horn High Bet Initialized: Default\n"
                  << std::endl;
    }

    HornHighBet(int wage, int highNum) : HornBet(wage)
    {
        std::cout << "Horn High Bet Initialized" << std::endl;
        std::cout << "High Number: " << this->highNumber << std::endl
                  << std::endl;
    }
};

// All Small Bet
class AllSmallBet : public BetNode
{
private:
    std::unordered_set<int> rolledVals{};
    const int winningNumbers[5] = {2, 3, 4, 5, 6};
    const int payoutOdds{30};

public:
    AllSmallBet() : BetNode()
    {
        std::cout << "All Small Bet Initialized: Default\n"
                  << std::endl;
    }

    AllSmallBet(int wage) : BetNode(wage)
    {
        std::cout << "All Small Bet Initialized\n"
                  << std::endl;
    }
};

// All Tall Bet
class AllTallBet : public BetNode
{
private:
    std::unordered_set<int> rolledVals{};
    int winningNumbers[5] = {8, 9, 10, 11, 12};
    const int payoutOdds{30};

public:
    AllTallBet() : BetNode()
    {
        std::cout << "All Tall Bet Initialized: Default\n"
                  << std::endl;
    }

    AllTallBet(int wage) : BetNode(wage)
    {
        std::cout << "All Tall Bet Initialzied\n"
                  << std::endl;
    }
};

// Multi-Roll Proposition Bets - Any Time

// Hardway Bet
class HardwayBet : public BetNode
{
private:
    int hardNum{0};
    std::map<int, double> payoutOdds{
        {4, 7.0},
        {6, 9.0},
        {8, 9.0},
        {10, 7.0}};

public:
    HardwayBet() : BetNode()
    {
        std::cout << "Hardway Bet Initialized: Default\n"
                  << std::endl;
    }

    HardwayBet(int wage) : BetNode(wage)
    {
        std::cout << "Hardway Bet Initialized\n"
                  << std::endl;
    }
};

// Fire Bet -- Only can be made during come-out roll
class FireBet : public BetNode
{
private:
    std::unordered_set<int> hits{};
    std::map<int, double> payoutOdds{
        {4, 25.0},
        {5, 250.0},
        {6, 1000.0}};

public:
    FireBet() : BetNode()
    {
        std::cout << "Fire Bet Initialized\n"
                  << std::endl;
    }

    FireBet(int wage) : BetNode(wage)
    {
        std::cout << "Fire Bet Initialized\n"
                  << std::endl;
    }
};
