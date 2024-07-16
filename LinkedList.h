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
protected:
    ptr head = make_shared<Node>();
    ptr tail = make_shared<Node>();

public:
    LinkedList() : head{make_shared<PlayerNode>()}, tail{make_shared<PlayerNode>()} { cout << "Link List initialized w/ PlayerNode pointers" << endl; }
    ~LinkedList() {}
};