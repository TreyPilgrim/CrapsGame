#include "BetsLinkedList.h"

/*
    Push to tail of list
    TODO::
    what data will be pushed?
    what will a basic bet look like?
*/
void Bets::push()
{
    ptr tmp = std::make_shared<Node>();

    if (head == nullptr)
        head = tmp;
    else
    {
        tail->next = tmp;
        tmp->prev = tail;
    }

    tail = tmp;
    std::cout << "pushed new node" << std::endl;
}

/*
    Display all bets in list
    TODO::
    Operator overload to define what will happen on
        cout << Bets
*/
bool Bets::display()
{
    if (head == nullptr)
        return false;

    ptr tmp = std::make_shared<Node>();
    tmp = head;

    cout << "Bets:" << endl;
    while (tmp != nullptr)
    {
        cout << "Point Number: " << tmp->pointNum << endl;
        cout << "Line Bet: " << tmp->lineBet << endl;
        cout << "Odds Bet: " << tmp->oddsBet << endl;
        cout << "-----------------------------------------\n";

        tmp = tmp->next;
    }

    return true;
}
