#pragma once
#include "PlayerNode.h"

class PlayerList
{
private:
    playerNodePtr head;
    playerNodePtr tail;
    playerNodePtr shooter;

    bool isEmpty();
    playerNodePtr find(const std::string name); // find a specific node - by name, return it (brute force as of now)

    // Unique Name finder
    bool sameName(const string name1, const string name2);
    bool sameNameFromNode(const string userName, playerNodePtr comparison);

public:
    PlayerList() : head{nullptr}, tail{nullptr}, shooter{nullptr} {}
    ~PlayerList() = default;

    // Get Player1
    playerNodePtr getP1();

    // Checker
    bool validWinAmount(char betType, int betAmount);
    bool pushPlayer(std::string name, int &playerBalance);
    bool pushWager(std::string name, int wageType, int wage);
    bool setShooter();
    bool p1Shooter();

    bool pop(std::string name); // remove node via name
    std::string peek();         // peek at the head node's name

    void displayPlayers();
    void displaySelf();

    void comeOutWin();

    // Public Unique Name alg.
    bool uniqueName(const string userName);
};