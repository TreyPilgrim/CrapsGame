#pragma once
#include <iostream>
#include <memory>
#include "Node.h"
#include <string.h>
using namespace std;

using ptr = shared_ptr<Node>;
using betNode = shared_ptr<BetNode>;
using playerNode = shared_ptr<PlayerNode>;

class LinkedList;

class LinkedList
{
private:
    ptr head = make_shared<Node>();
    ptr tail = make_shared<Node>();

public:
    LinkedList() = default;
    ~LinkedList() {}
};