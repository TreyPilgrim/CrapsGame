#include "BetList.h"

bool BetList::peek()
{
    std::cout << "BetList peek called" << std::endl;

    if (BetList::head == nullptr)
    {
        std::cout << "Empty BetList" << std::endl;
        return false;
    }

    std::cout << "BetList not Empty" << std::endl;
    return true;
}
void BetList::pushBet(int wageType, int wage)
{
    betPtr tmp = std::make_shared<BetNode>(wageType, wage);
    std::cout << "PushBet: made a BetNode" << std::endl;

    if (!BetList::peek())
    {
        BetList::head = tmp;
        std::cout << "Head updated" << std::endl;
    }
    else
    {
        BetList::tail->next = tmp;
        tmp->prev = BetList::tail;
    }

    BetList::tail = tmp;

    std::cout << "Tail updated" << std::endl;
}