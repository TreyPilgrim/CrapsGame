#pragma once
#include <iostream>
#include <memory>

class Node;

using ptr = std::shared_ptr<Node>;

class Node
{

public:
    ptr next;
    ptr prev;

    // true for Don't pass bar; false for Pass Line
    bool passBar;
    int pointNum;
    int lineBet;
    int oddsBet;

    Node() : next{nullptr}, prev{nullptr}, passBar{false}, pointNum{0}, lineBet{0}, oddsBet{0} {}
};