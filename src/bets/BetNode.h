#pragma once
#include <iostream>
#include <memory>
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
    int bf, height;
    std::string betId{"void"};

    int wager;
    int toWin;
    int point;
    bool firstRoll{true};
    std::list<int> hits; // certain bets need multiple rolls to win. tracker of winning hits/rolls

    // Generate prefix
public:
    betNodePtr lChild;
    betNodePtr rChild;

    // Constructord
    BetNode() : lChild(nullptr),
                rChild(nullptr),
                bf{0},
                height{0},
                wager{0},
                point{0}

    {
    }

    BetNode(int wageType, int wage, int point = 0) : lChild{nullptr},
                                                     rChild{nullptr},
                                                     bf{0}
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