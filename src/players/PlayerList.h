#pragma once
#include "PlayerNode.h"

class PlayerList
{
private:
    playerNodePtr head;
    playerNodePtr tail;
    playerNodePtr shooter;

    void failIf(const std::string &errorMsg, int condition = -1);
    bool isEmpty();
    playerNodePtr find(const std::string name); // find a specific node - by name, return it (brute force as of now)

    // Unique Name finder
    bool sameName(const string name1, const string name2);
    bool sameNameFromNode(const string userName, playerNodePtr comparison);

    bool pushWagerP1Version(const int &wageType, const std::string &name);

public:
    PlayerList() : head{nullptr}, tail{nullptr}, shooter{nullptr} {}
    ~PlayerList() = default;

    // Checker
    bool validWinAmount(char betType, int betAmount);
    bool pushPlayer(std::string name, int &playerBalance);
    bool pushWagerP1Version(const int &wageType);

    bool setShooter();
    bool p1Shooter();
    bool p1HasNoBets();
    void p1PushWager(const int betChoice);

    bool pop(std::string name); // remove node via name
    std::string peek();         // peek at the head node's name

    void displayPlayers();
    void displaySelf();

    void comeOutWin();

    // Public Unique Name alg.
    bool uniqueName(const string userName);
};