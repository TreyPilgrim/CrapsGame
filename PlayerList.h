#pragma once
#include <iostream>
#include <memory>
#include "PlayerNode.h"
#include <string>

class PlayerList
{
private:
    using ptr = std::shared_ptr<PlayerNode>; // For tmp pointers to head/tail

    ptr head;
    ptr tail;

    bool validName(const string name);
    bool peek();

public:
    PlayerList() : head{nullptr}, tail{nullptr} {}
    ~PlayerList() = default;

    bool pushPlayer(std::string name, int &playerBalance);
    void pushWager(std::string name, int wageType, int wage);

    ptr find(const std::string name); // find a specific node, return it (brute force as of now)
    bool pop(std::string name);       // remove node via name

    void displayPlayers();
    void displaySelf();
};