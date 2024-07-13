#pragma once
#include <iostream>
#include <memory>
#include <string.h>

using namespace std;
class Node;

using ptr = std::shared_ptr<Node>;

class Node
{

public:
    ptr next;
    ptr prev;

    Node() : next{nullptr}, prev{nullptr} {}
    ~Node() {}
};

// BetNode CLass
class BetNode : public Node
{
public:
    enum betTypes
    {
        defaultType,
        passBet,
        dontPassBet,
        fieldBelt,
        placeBelt,
        propositionBet
    };

    betTypes bet;
    int wager;
    int comeBet; // value for dontComeBets too

    BetNode() : bet{BetNode::defaultType}, wager{0}, comeBet{0} {};
    bool setBet(int betNum);
    void setWager(int wage);
    void setComeBet(int cb);
};

// PlayerNode Class
class PlayerNode : public Node
{
public:
    bool shooter;
    int balance;
    string gamblerName;

    PlayerNode() : shooter{false}, balance{0}, gamblerName{"Default"} {};

    bool setName(string name);
    void setBalance(int money);
};
