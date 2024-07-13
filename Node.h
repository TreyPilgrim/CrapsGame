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

    Node() : next{nullptr}, prev{nullptr} {};
};

class PlayerNode : public Node
{
public:
    string gamblerName;

    PlayerNode() : gamblerName{"Default"} {};
    bool setName(string name);
};

class BetNode : public Node
{
public:
};