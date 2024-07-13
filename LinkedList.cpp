#include "LinkedList.h"

void LinkedList::push()
{
    ptr tmp = make_shared<Node>();

    if (this->head == nullptr)
        head = tmp;
    else
    {
        tail->next = tmp;
        tmp->prev = tail;
    }

    tail = tmp;
}

// bool LinkedList::pop()
// {
//     if (head == nullptr)
//         return false;

//     ptr tmp = tail;
//     tail = tail->prev;
//     tail->next = nullptr;

//     std::cout << tmp.use_count();
//     return true;
// }