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
    BetNode() {}

    BetNode(int wageType, int wage, int point = 0)
    {
        this->setWager(wage);
        this->setPoint(point);
        std::cout << "BetNode Initialized\n";
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

    // Update First Roll status
    bool isFirstRoll();
    void secondRoll();
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

public:
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

    const std::unordered_set<int> winningVals{2, 3, 12};
    const std::unordered_set<int> losingVals{7, 11};

public:
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

public:
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

public:
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
};

// Place to Lose Bet
class PlaceToLoseBet : BetNode
{
    int point{0};
    std::map<int, double> payoutOdds{
        {4, 5 / 11},
        {5, 5 / 8},
        {6, 4 / 5},
        {8, 4 / 5},
        {9, 5 / 8},
        {10, 5 / 11}};
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
};

// Big 6 Bet
class Big6Bet : public BetNode
{
private:
    int point{6};
    std::map<int, double> payoutOdds{
        {6, 1.0}};

public:
};

// Big 8 Bet
class Big8Bet : public BetNode
{
private:
    int point{8};
    std::map<int, double> payoutOdds{
        {8, 1.0}};

public:
};

// Single-Roll Proposition Bets - Any Time

// Field Bet
class FieldBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {2, 2.0},
        {3, 1.0},
        {4, 1.0},
        {9, 1.0},
        {10, 1.0},
        {11, 1.0},
        {12, 2.0}};
};

// Any Craps Bet
class AnyCrapsBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {2, 7.0},
        {3, 7.0},
        {12, 7.0}};
};

// Any Seven Bet
class AnySevenBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {7, 4.0}};
};

// Yo Bet
class YoBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {11, 15.0}};
};

// Ace Deuce Bet
class AceDeuceBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {3, 15.0}};
};

// Snake Eyes Bet
class SnakeEyesBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {2, 30.0}};
};

// Box Cars Bet
class BoxCarsBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {12, 30.0}};
};

// World Bet
class WorldBet : public BetNode
{
};

// Horn Bet
// Wage is divided by 4 (evenly placed on 2, 3, 11, 12) depending on whats rolled determines payout
// Dividing each payout by 4 to account for the
// When adding returning winnings - don't forget to accomodate for divding 4 *******
class HornBet : public BetNode
{
    std::map<int, double> payoutOdds{
        {2, 30 / 4},
        {3, 15 / 4},
        {11, 15 / 4},
        {12, 30 / 4}};
};

// Horn High Bet
// Wage must be an increment of 5
// High # payout is (wage/5 * 30(or 15, depends what hits) + (wage/5) ? -- double check later
// Other Payouts are (wage/5)
class HornHighBet : public BetNode
{
    int highNumber{};
};

// All Small Bet
class AllSmallBet : public BetNode
{
    std::unordered_set<int> rolledVals{};

    const int winningNumbers[5] = {2, 3, 4, 5, 6};
    const int payoutOdds{30};
};

// All Tall Bet
class AllTallBet : public BetNode
{
    std::unordered_set<int> rolledVals{};
    int winningNumbers[5] = {8, 9, 10, 11, 12};
    const int payoutOdds{30};
};

// Multi-Roll Proposition Bets - Any Time

// Hardway Bet
class HardwayBet : public BetNode
{
};

// Fire Bet -- Only can be made during come-out roll
class FireBet : public BetNode
{
};
