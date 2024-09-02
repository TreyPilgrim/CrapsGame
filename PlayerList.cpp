#include "PlayerList.h"

/*-----------------------------------------------------
    PlayerList PRIVATE Functions
-------------------------------------------------------*/
bool PlayerList::validName(const string name)
{
    ptr tmp = nullptr;
    tmp = head;

    while (tmp != nullptr)
    {
        if (name == tmp->gamblerName)
            return false; // Case that name found in list already

        tmp = tmp->next;
    }

    return true;
}

bool PlayerList::peek()
{
    if (this->head == nullptr)
        return false;

    return true;
}

/*-----------------------------------------------------
    PlayerList Public Functions
-------------------------------------------------------*/
// Add a new player to linked list
bool PlayerList::pushPlayer(string name, int &playerBalance)
{
    // Make sure name is unique
    if (!this->validName(name))
    {
        std::cout << "The name \"" << name << "\" is already in use by another player..." << std::endl;
        return false;
    }

    // Push to tail
    ptr tmp = std::make_shared<PlayerNode>(name, playerBalance);
    if (!this->peek()) // Update head on empty list
        this->head = tmp;
    else
    {
        this->tail->next = tmp;
        tmp->prev = this->tail;
    }

    this->tail = tmp; // Update tail
    return true;      // Return true after successful push
}

void PlayerList::pushWager(std::string name, int wageType, int wage)
{
    // ptr tmp = find(name);

    // if (tmp == nullptr)
    //     return false; // Player not found
    ptr tmp = nullptr;
    tmp = PlayerList::head;

    tmp->playerBets->pushBet(wageType, wage);
}

// Because ptr is a specific alias, gotta specify which class
// Function to return specific players by name
ptr PlayerList::find(const string name)
{
    ptr tmp = nullptr;
    tmp = head;

    // Brute force to search for name
    // TODO: When AI is implemented.. Add more effecient search algorithm
    while (tmp != nullptr)
    {
        if (tmp->gamblerName == name)
            return tmp;

        tmp = tmp->next;
    }

    return nullptr;
}

// Remove player from list
// Shared pointers auto delete when nothing is looking at it
bool PlayerList::pop(string name)
{
    ptr tmp = nullptr;
    tmp = this->find(name);

    // Return false on empty list or name not found
    if (head == nullptr || tmp == nullptr)
        return false;

    if (tmp == this->head) // in the event removing head
    {
        tmp->next->prev = nullptr;
        this->head = tmp->next;
    }
    else if (tmp == this->tail) // event removing tail
    {
        tmp->prev->next = nullptr;
        this->tail = tmp->prev;
    }
    else // event removing part of the body
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }

    return true;
}

void PlayerList::displaySelf()
{
    ptr tmp = nullptr;
    tmp = this->head;

    std::cout << "Player Name: " << tmp->gamblerName << std::endl;
    std::cout << "Player Wages: " << tmp->balance << std::endl;
}