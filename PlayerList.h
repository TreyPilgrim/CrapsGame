#pragma once
#include <iostream>
#include <memory>
#include "PlayerNode.h"
#include <string>

class PlayerList
{
private:
    playerNodePtr head;
    playerNodePtr tail;
    playerNodePtr shooter;

    bool validName(const string name);
    bool isEmpty();

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

    playerNodePtr find(const std::string name); // find a specific node, return it (brute force as of now)
    bool pop(std::string name);                 // remove node via name
    std::string peek();                         // peek at the head node's name

    void displayPlayers();
    void displaySelf();

    void comeOutWin();
};