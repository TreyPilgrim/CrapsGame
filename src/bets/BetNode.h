#pragma once
#include <iostream>
#include <limits>
#include <unordered_set>
#include <memory>
#include <map>
#include <string>
#include <list>
#include <stdexcept>

// BetNode CLass
class BetNode;
// Type Alias
using betNodePtr = std::shared_ptr<BetNode>;
using arr = std::shared_ptr<int[]>;

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

    // Bet Attributes
    std::string betId{"void"};
    int wager{0}, point{0};

    // Generate ID
    int randNum();

protected:
    std::map<int, double> payoutOdds{};

    // Wage Helpers - Set up to handle 1:1 payouts
    bool validInt();                          // Make sure input is an Int
    virtual bool validPayout(const int wage); // payout isn't a decimal
    virtual int getNorthVal(int wage);        // Get Next valid Wager amount
    virtual int getSouthVal(int wage);        // Get Previous valid Wager amount
    arr getNextValues(const int wage);        // function that's going to return an array to next and prev valid wager amounts
    int setTheWagePhase();                    // main function for getting wage information for node

    // ID Helpers
    arr randomArr();
    std::string arrToString(arr tmp);
    virtual std::string generateID();

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
        generateID();
        // this->setWager(wage);
        this->setPoint(point);
        std::cout << "BetNode Initialized\n";
        std::cout << "Bet ID: " << this->getID() << std::endl;
        std::cout << "Wage: " << this->getWager() << std::endl;

        if (this->getPoint() != 0)
            std::cout << "Point: " << this->getPoint() << std::endl;

        std::cout << "=============================================================" << std::endl;
    }
    virtual ~BetNode() = default;

    // Initializer Functions
    void generateNewID();
    virtual void setTheWager();

    // Setters
    void setID(std::string str);
    void setBF(int balFact);
    void setHeight(int h);
    void setPoint(int point);
    void setWage(); // Set the wage -- after being thoroughly checked

    // Getters
    std::string getID();
    int getBF();
    int getHeight();
    int getPoint();
    int getWager();
    char getBetType(); // ?
    int const childSupport();
};

//-----------------------------------------------------------------------------------------
// Come Out Roll Bets -- Add pointer to
// Pass Line Bet - A
class PassLineBet : public BetNode
{
private:
    bool firstRoll{true};
    std::map<int, double> payoutOdds{
        {7, 1.0},
        {11, 1.0}};

    const std::unordered_set<int> losingVals{2, 3, 12};
    betNodePtr oddsOnPassPtr;

    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    PassLineBet()
    {
        std::cout << "Pass Line Bet Node Initialized: Default" << std::endl;
        this->generateNewID(); // Automatic

        // User: Get Wager Amount
        this->setWage();
    }

    // Possible virutal function tbd
    void notFirstRoll();

    // TODO (5/3/25) --- make these functions virtual
    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Don't Pass Line Bet - B
class DontPassLineBet : public BetNode
{
private:
    bool firstRoll{true};
    std::map<int, double> payoutOdds{
        {2, 1.0},
        {3, 1.0},
        {12, 1.0}};

    const std::unordered_set<int> losingVals{7, 11};
    betNodePtr oddsOnDontPassPtr;

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;

public:
    DontPassLineBet()
    {
        this->generateNewID();
        std::cout << "Dont Pass Line Bet Node Initialized: Default" << std::endl;

        this->setWage();
    }

    void notFirstRoll();

    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Post Come Out Roll Bets

// Come Bet - C
class ComeBet : public BetNode
{
private:
    bool firstRoll{true};
    std::map<int, double> payoutOdds{
        {7, 1.0},
        {11, 1.0}};

    const std::unordered_set<int> losingVals{2, 3, 12};
    betNodePtr oddsOnComePtr;

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;

public:
    ComeBet()
    {
        std::cout << "Come Bet Initialized: Default" << std::endl;
        this->generateNewID();
        this->setWage();
    }

    // Possible virutal function tbd
    void notFirstRoll();

    // TODO (5/3/25) --- make these functions virtual
    bool winningTicket(const int diceVal);
    bool losingTicket(const int diceVal);
};

// Don't Come Bet - D
class DontComeBet : public BetNode
{
private:
    bool firstRoll{true};

    std::map<int, double> payoutOdds{
        {2, 1.0},
        {3, 1.0},
        {12, 1.0}};

    const std::unordered_set<int> losingVals{7, 11};
    betNodePtr oddsOnDontComePtr;

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;

public:
    DontComeBet()
    {
        std::cout << "Don't Come Bet Initialized: Default" << std::endl;
        this->generateNewID();
        this->setWage();
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
// Odds on Pass Bet - E
class OddsOnPassBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 2.0},
        {5, 3 / 2},
        {6, 6 / 5},
        {8, 6 / 5},
        {9, 3 / 2},
        {10, 2.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    OddsOnPassBet()
    {
        std::cout << "Odds on Pass Bet Initialized: Default" << std::endl;
        this->generateNewID();
        this->setPoint(5);

        this->setWage();
    }
};

// Odds on Don't Pass Bet - F
class OddsOnDontPassBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 1 / 2},
        {5, 2 / 3},
        {6, 5 / 6},
        {8, 5 / 6},
        {9, 2 / 3},
        {10, 1 / 2}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    OddsOnDontPassBet() : BetNode()
    {
        std::cout << "Odds On Dont Pass Bet: Default" << std::endl;
        this->generateNewID();
    }

    OddsOnDontPassBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Odds On Dont Pass Bet\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Odds on Come Bet - G
class OddsOnComeBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 2.0},
        {5, 3 / 2},
        {6, 6 / 5},
        {8, 6 / 5},
        {9, 3 / 2},
        {10, 2.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    OddsOnComeBet() : BetNode()
    {
        std::cout << "Odds On Come Bet Initialized: Default" << std::endl;
        this->generateNewID();
    }

    OddsOnComeBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Odds On Come Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Odds on Don't Come Bet - H
class OddsOnDontComeBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 1 / 2},
        {5, 2 / 3},
        {6, 5 / 6},
        {8, 5 / 6},
        {9, 2 / 3},
        {10, 1 / 2}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    OddsOnDontComeBet() : BetNode()
    {
        std::cout << "Odds On Dont Come Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    OddsOnDontComeBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Odds On Dont Come Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Place Bets - Made any time after come out roll

// Place to Win Bet - I
class PlaceToWinBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 9 / 5},
        {5, 7 / 5},
        {6, 7 / 6},
        {8, 7 / 6},
        {9, 7 / 5},
        {10, 9 / 5}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    PlaceToWinBet() : BetNode()
    {
        std::cout << "Place To Win Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    PlaceToWinBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Place To Win Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Place to Lose Bet - J
class PlaceToLoseBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 5 / 11},
        {5, 5 / 8},
        {6, 4 / 5},
        {8, 4 / 5},
        {9, 5 / 8},
        {10, 5 / 11}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    PlaceToLoseBet() : BetNode()
    {
        std::cout << "Place To Lose Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    PlaceToLoseBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Place To Lose Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Buy Bet - 5% Commission K
class BuyBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 2.0},
        {5, 3 / 2},
        {6, 6 / 5},
        {8, 6 / 5},
        {9, 3 / 2},
        {10, 2.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    BuyBet() : BetNode()
    {
        std::cout << "Buy Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    BuyBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Buy Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Lay Bet - 5% Commission L
class LayBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 1 / 2},
        {5, 2 / 3},
        {6, 5 / 6},
        {8, 5 / 6},
        {9, 2 / 3},
        {10, 1 / 2}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    LayBet() : BetNode()
    {
        std::cout << "Lay Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    LayBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Lay Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Big 6 Bet - M
class Big6Bet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {6, 1.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO  1:1 payout
    bool validPayout(const int wage) override;

public:
    Big6Bet() : BetNode()
    {
        std::cout << "Big 6 Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(6);
    }

    Big6Bet(int wage) : BetNode(wage, 6)
    {
        std::cout << "Big 6 Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Big 8 Bet - N
class Big8Bet : public BetNode
{
private:
    // int point{8};
    std::map<int, double> payoutOdds{
        {8, 1.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - 1:1 payout
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    Big8Bet() : BetNode()
    {
        std::cout << "Big 8 Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
        this->setPoint(8);
    }

    Big8Bet(int wage) : BetNode(wage, 8)
    {
        std::cout << "Big 8 Bet Initialized\n"
                  << std::endl;
        this->generateNewID();
    }
};

// Single-Roll Proposition Bets - Any Time

// Field Bet - O
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

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    FieldBet() : BetNode()
    {
        std::cout << "Field Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    FieldBet(int wage) : BetNode(wage)
    {
        std::cout << "Field Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Any Craps Bet - P
class AnyCrapsBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 7.0},
        {3, 7.0},
        {12, 7.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    AnyCrapsBet() : BetNode()
    {
        std::cout << "Any Craps Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    AnyCrapsBet(int wage) : BetNode(wage)
    {
        std::cout << "Any Craps Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Any Seven Bet - R
class AnySevenBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {7, 4.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    AnySevenBet() : BetNode()
    {
        std::cout << "Any Seven Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
        this->setPoint(7);
    }

    AnySevenBet(int wage) : BetNode(wage, 7)
    {
        std::cout << "Any Seven Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Yo Bet - S
class YoBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {11, 15.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    YoBet() : BetNode()
    {
        std::cout << "Yo Bet Initialized: Default" << std::endl;

        this->generateNewID();
        this->setPoint(11);
    }

    YoBet(int wage) : BetNode(wage, 11)
    {
        std::cout << "Yo Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Ace Deuce Bet - T
class AceDeuceBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {3, 15.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    AceDeuceBet() : BetNode()
    {
        std::cout << "Ace Deuce Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
        this->setPoint(3);
    }

    AceDeuceBet(int wage) : BetNode(wage, 3)
    {
        std::cout << "Ace Deuce Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Snake Eyes Bet - U
class SnakeEyesBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 30.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    SnakeEyesBet() : BetNode()
    {
        std::cout << "Snake Eyes Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
        this->setPoint(2);
    }

    SnakeEyesBet(int wage) : BetNode(wage, 2)
    {
        std::cout << "Snake Eyes Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Box Cars Bet - V
class BoxCarsBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {12, 30.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    BoxCarsBet() : BetNode()
    {
        std::cout << "Box Cars Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
        this->setPoint(12);
    }

    BoxCarsBet(int wage) : BetNode(wage, 12)
    {

        std::cout << "Box Cars Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// World Bet - Wage mus be divisible by 5 W
class WorldBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {2, 30.0},
        {3, 15.0},
        {7, 4.0},
        {11, 15.0},
        {12, 30.0}};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers
    bool validPayout(const int wage) override;
    // int getNorthVal(int wage) override;
    // int getSouthVal(int wage) override;

public:
    WorldBet() : BetNode()
    {
        std::cout << "World Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    WorldBet(int wage) : BetNode(wage)
    {
        std::cout << "World Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Horn Bet - X
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

    // ID Generator
    virtual std::string generateID();

public:
    HornBet() : BetNode()
    {
        std::cout << "Horn Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    HornBet(int wage) : BetNode(wage)
    {
        std::cout << "Horn Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Horn High Bet - Y
// Wage must be an increment of 5
// High # payout is (wage/5 * 30(or 15, depends what hits) + (wage/5) ? -- double check later
// Other Payouts are (wage/5)
class HornHighBet : public HornBet
{
private:
    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO (HIGH # HAS DIF PAYOUT)
    bool validPayout(const int wage) override;
    int getNorthVal(int wage) override;
    int getSouthVal(int wage) override;

public:
    HornHighBet() : HornBet()
    {
        std::cout << "Horn High Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    HornHighBet(int wage, int highNum) : HornBet(wage)
    {
        this->setPoint(highNum);

        std::cout << "Horn High Bet Initialized" << std::endl;
        std::cout << "High Number: " << this->getPoint() << std::endl
                  << std::endl;

        this->generateNewID();
    }
};

// All Small Bet - Z
class AllSmallBet : public BetNode
{
private:
    std::unordered_set<int> rolledVals{};
    const int winningNumbers[5] = {2, 3, 4, 5, 6};
    const int payoutOdds{30};

    // ID Generator
    virtual std::string generateID();

    // Wager Makers - TODO
    bool validPayout(const int wage) override;

public:
    AllSmallBet() : BetNode()
    {
        std::cout << "All Small Bet Initialized: Default\n"
                  << std::endl;
        this->generateNewID();
    }

    AllSmallBet(int wage) : BetNode(wage)
    {
        std::cout << "All Small Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// All Tall Bet - a
class AllTallBet : public BetNode
{
private:
    std::unordered_set<int> rolledVals{};
    int winningNumbers[5] = {8, 9, 10, 11, 12};
    const int payoutOdds{30};

    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage) override;

public:
    AllTallBet() : BetNode()
    {
        std::cout << "All Tall Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    AllTallBet(int wage) : BetNode(wage)
    {
        std::cout << "All Tall Bet Initialzied\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Multi-Roll Proposition Bets - Any Time

// Hardway Bet - b
class HardwayBet : public BetNode
{
private:
    std::map<int, double> payoutOdds{
        {4, 7.0},
        {6, 9.0},
        {8, 9.0},
        {10, 7.0}};

    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage) override;

public:
    HardwayBet() : BetNode()
    {
        std::cout << "Hardway Bet Initialized: Default\n"
                  << std::endl;

        this->generateNewID();
    }

    HardwayBet(int wage, int point) : BetNode(wage, point)
    {
        std::cout << "Hardway Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};

// Fire Bet -- Only can be made during come-out roll c
class FireBet : public BetNode
{
private:
    std::unordered_set<int> hits{};
    std::map<int, double> payoutOdds{
        {4, 25.0},
        {5, 250.0},
        {6, 1000.0}};

    // ID Generator
    virtual std::string generateID() override;

    // Wager Makers - TODO
    bool validPayout(const int wage) override;

public:
    FireBet() : BetNode()
    {
        std::cout << "Fire Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }

    FireBet(int wage) : BetNode(wage)
    {
        std::cout << "Fire Bet Initialized\n"
                  << std::endl;

        this->generateNewID();
    }
};
