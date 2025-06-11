#include "PlayerList.h"

/*-----------------------------------------------------
    PlayerList PRIVATE Functions
-------------------------------------------------------*/

bool PlayerList::isEmpty()
{
    if (this->head == nullptr)
        return true;

    return false;
}

// string comparison for same name
bool PlayerList::sameName(const string name1, const string name2)
{
    return (name1 != name2) ? false : true;
}

// calling sameName using getName for node-name passing
bool PlayerList::sameNameFromNode(const string userName, playerNodePtr comparison)
{
    return this->sameName(userName, comparison->getName());
}

/*-----------------------------------------------------
    PlayerList Public Functions
-------------------------------------------------------*/

// Checkers

// Add a new player to linked list
bool PlayerList::pushPlayer(string name, int &playerBalance)
{
    // Make sure name is unique
    if (!this->uniqueName(name))
        return false;

    std::cout << "name is valid\n";

    // Push to tail
    playerNodePtr tmp = std::make_shared<PlayerNode>(name, playerBalance);
    if (this->isEmpty()) // Update head on empty list
        this->head = tmp;
    else
    {
        this->tail->next = tmp;
        tmp->prev = this->tail;
    }

    std::cout << "List updated\n";

    this->tail = tmp; // Update tail

    std::cout << "returning true from push\n";
    return true; // Return true after successful push
}

// Pushing a wager
bool PlayerList::pushWager(std::string name, int wageType, int wage)
{
    playerNodePtr tmp = find(name);

    if (tmp == nullptr)
        return false; // Player not found

    if (!tmp->validFunds(wage)) // Insuficient(?) funds
        return false;

    // Push the Bet into the List
    // tmp->playerBets->insert(wageType, wage);

    // Update the balance to show the funds are now on the boards
    tmp->setBalance(-wage);

    return true;
}

bool PlayerList::setShooter()
{
    playerNodePtr oldShooter;

    if (isEmpty())
        return false;

    if (shooter == nullptr)
    {
        shooter = head;
        shooter->newShooter();
    }
    else if (shooter->next == nullptr && shooter->prev == nullptr) // Only 1 player in queue
    {
        // Do nothing
    }
    else if (shooter->next == nullptr) // Event shooter is the tail
    {
        oldShooter = shooter;
        shooter = head;

        // unassign old shooter, assign new shooter
        oldShooter->newShooter();
        shooter->newShooter();
    }
    else // player is in middle of queue
    {
        oldShooter = shooter;
        shooter = shooter->next;

        // Unassign old shooter, assign new shooter
        oldShooter->newShooter();
        shooter->newShooter();
    }

    return true;
}

bool PlayerList::p1Shooter()
{
    return this->head->isShooter();
}

// Because playerNodePtr is a specific alias, gotta specify which class
// Function to return specific players by name
playerNodePtr PlayerList::find(const string name)
{
    playerNodePtr tmp = nullptr;
    tmp = head;

    // Brute force to search for name
    // TODO: When AI is implemented.. Add more effecient search algorithm
    while (tmp != nullptr)
    {
        if (tmp->getName() == name)
            return tmp;

        tmp = tmp->next;
    }

    return nullptr;
}

// Remove player from list
// Shared pointers auto delete when nothing is looking at it
bool PlayerList::pop(string name)
{
    playerNodePtr tmp = nullptr;
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

// Peek at the head node's name
std::string PlayerList::peek()
{
    return this->head->getName();
}

void PlayerList::displaySelf()
{
    playerNodePtr tmp = nullptr;
    tmp = this->head;

    std::cout << "Player Name: " << tmp->getName() << std::endl;
    std::cout << "Player Balance: " << tmp->getBalance() << std::endl;
}

// Public Unique Name Checker function
bool PlayerList::uniqueName(const string userName)
{

    if (this->isEmpty())
    {
        std::cout << "Empty list" << std::endl;
        return false;
    }

    bool uniqueName{true};
    playerNodePtr tmp = this->head;

    while (tmp != nullptr && uniqueName == true)
    {
        // sameName returns false on unique entries
        uniqueName = !this->sameNameFromNode(userName, tmp);

        tmp = tmp->next;
    }

    return uniqueName;
}