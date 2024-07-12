#include <iostream>
#include <memory>
#include "Node.h"
class Bets;

using namespace std;

class Bets {
private:
    ptr head;
    ptr tail;

    int minBet;

public:

    Bets(): head{nullptr}, tail{nullptr}, minBet{15} {}
    ~Bets(){} 
    void push();
    bool display(); // temp installment
};