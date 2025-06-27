#include "BetAVL.h"

/*
    Private Methods
*/
//-----------------------------------------------------------------------------------------
// Tree Methods

// get node's height (recursively checks subtree)
int BetAVL::nodeHeight(betNodePtr node)
{
    // For the recursion
    if (node == nullptr)
        return -1; // error

    int lHeight = (node->lChild) ? nodeHeight(node->lChild) : -1;
    int rHeight = (node->rChild) ? nodeHeight(node->rChild) : -1;

    return std::max(lHeight, rHeight) + 1;
}

// Balance Factor (recursively checks subtree)
int BetAVL::balanceFactor(betNodePtr node)
{
    // For the recursion mainly
    if (node == nullptr)
        return -1; // empty case

    int lHeight = (node->lChild) ? this->nodeHeight(node->lChild) : 0;
    int rHeight = (node->rChild) ? this->nodeHeight(node->rChild) : 0;

    return lHeight - rHeight;
}

// Variadic templat allows me to pass however many betNodePtrs in order to updat height and balance
template <typename... Nodes>
void BetAVL::updateHeightAndBf(Nodes &...nodes)
{
    (nodes->setHeight(nodeHeight(nodes)), ...); // Set each node passed's height
    (nodes->setBF(balanceFactor(nodes)), ...);  // Update Balance factor next
}

//-----------------------------------------------------------------------------------------
// Rotations

// Left-Left Rotation (right rotation)
void BetAVL::LLRotation(betNodePtr &node)
{
    // Holder pointers
    betNodePtr lKid = node->lChild;
    betNodePtr lKidsLKid = lKid->lChild;
    betNodePtr nodeParent;

    if (node != root)
        nodeParent = getParent(node); // need to update parent's pointer

    // Right Rotation @ node
    node->lChild = lKid->rChild;
    lKid->rChild = node;

    // Update Root
    if (root == node)
        root = lKid;
    else // Update parent
    {
        if (nodeParent->getID() < node->getID())
            nodeParent->rChild = lKid;
        else
            nodeParent->lChild = lKid;
    }

    // update heights and BF of rotated nodes & subtree
    this->subTreeReBalance(lKid);

    // TODO: Update Ancestors
}
// Right-Right Rotation (left rotation)
void BetAVL::RRRotation(betNodePtr &node)
{
    // Holder pointers
    betNodePtr rKid = node->rChild;
    betNodePtr rKidsRKid = rKid->rChild;
    betNodePtr nodeParent;

    if (node != root)
        nodeParent = getParent(node); // need to update parent's pointer

    // Update Branches
    node->rChild = rKid->lChild;
    rKid->lChild = node;

    // Update Root
    if (root == node)
        root = rKid;
    else // Update parent
    {
        if (nodeParent->getID() < node->getID())
            nodeParent->rChild = rKid;
        else
            nodeParent->lChild = rKid;
    }

    // update heights and BF of rotated nodes
    this->subTreeReBalance(rKid);
}

// Left-Right Rotation
void BetAVL::LRRotation(betNodePtr &node)
{
    // Left Rotation @ node->lChild
    RRRotation(node->lChild);

    // Right Rotation @ node
    LLRotation(node);
}

// Right-Left Rotation
void BetAVL::RLRotation(betNodePtr &node)
{
    // Right Rotation @ node->rChild
    LLRotation(node->rChild);

    // Left Rotation @ node
    RRRotation(node);
}

//-----------------------------------------------------------------------------------------
// Balancing
// Is node being checked Balanced?
void BetAVL::rotationChecker(betNodePtr &node)
{
    if (node->getBF() == 1 || node->getBF() == 0) // don't waste time if already balanced
        return;

    if (node->getBF() == 2 && node->lChild->getBF() == 1)
        LLRotation(node);
    else if (node->getBF() == 2 && node->lChild->getBF() == -1)
        LRRotation(node);
    else if (node->getBF() == -2 && node->rChild->getBF() == -1)
        RRRotation(node);
    else if (node->getBF() == -2 && node->rChild->getBF() == 1)
        RLRotation(node);
}

// Update subtree to rebalance itself
void BetAVL::subTreeReBalance(betNodePtr &node)
{
    // Parse Subtree(s) first
    if (node->lChild != nullptr)
        subTreeReBalance(node->lChild);
    else if (node->rChild != nullptr)
        subTreeReBalance(node->rChild);
    else
        return;

    // Update Node's Height and BF
    updateHeightAndBf(node);

    // Check if a rotation is needed ~ func takes care of height updates
    rotationChecker(node);
}
//-----------------------------------------------------------------------------------------
// Insert
/*
    Random Generators
*/

// Insert
bool BetAVL::insert(betNodePtr &node, betNodePtr &betNode)
{

    if (this->root == nullptr && node == this->root) // New Game
    {
        this->root = betNode;
        return true;
    }

    if (node == nullptr) // Leaf
        node = betNode;
    else if (node->getID() > betNode->getID()) // Go left on tree
    {
        if (!insert(node->lChild, betNode)) // Duplicate ID
            return false;
    }
    else if (node->getID() < betNode->getID()) // Go right on tree
    {
        if (!insert(node->rChild, betNode)) // Duplicate ID
            return false;
    }
    else if (node->getID() == betNode->getID()) // Duplicate IDs
        return false;

    // Update Height and BF
    updateHeightAndBf(node);

    // Check for Imbalances
    rotationChecker(node);

    return true;
}

// Id checker
bool BetAVL::sameID(const betNodePtr node, const betNodePtr betNode)
{
    if (node->getID() == betNode->getID())
        return true;

    return false;
}

// Wager Checker

//-----------------------------------------------------------------------------------------
// Traversal

void BetAVL::inOrder(betNodePtr node)
{
    if (node)
    {
        inOrder(node->lChild);
        std::cout << "--------------------------------------------------------\n";
        std::cout << "Bet Type: " << node->getBetType() << std::endl;
        std::cout << "Wage: " << node->getWager() << std::endl;
        std::cout << "Point: " << node->getPoint() << std::endl;
        std::cout << "ID: " << node->getID() << std::endl;

        inOrder(node->rChild);
    }
}
//-----------------------------------------------------------------------------------------
// Winning & Losing Evaluation

// Update First Roll for all values
void BetAVL::updateFirstRoll(betNodePtr &node)
{
}
// inContainer
bool BetAVL::inContainer(const std::list<int> winnersCircle, const int point)
{
    return std::find(winnersCircle.begin(), winnersCircle.end(), point) != winnersCircle.end();
}
// isWinner
bool BetAVL::isWinner(const betNodePtr node, const int *theDie[])
{
}

// isLoser
bool BetAVL::isLoser(betNodePtr node, const int *theDie[])
{
}

// isTie
bool BetAVL::isTie(const betNodePtr node, const int *theDie[])
{
}

// Add tickets to their appropriate list
void BetAVL::winSomeLoseSome(betNodePtr &node, const int *theDie[])
{
    if (node == nullptr)
        return;

    winSomeLoseSome(node->lChild, theDie);
    winSomeLoseSome(node->rChild, theDie);

    if (isWinner(node, theDie))
        this->winningTickets.push_back(node);
    else if (isLoser(node, theDie))
        this->losingTickets.push_back(node);
    else if (isTie(node, theDie))
        this->washTickets.push_back(node);
}
//-----------------------------------------------------------------------------------------
// Removal Helpers

// return predecessor of any node
betNodePtr BetAVL::getPredecessor(betNodePtr &node)
{
    // No Left Subtree
    if (node->lChild == nullptr)
        return nullptr;

    betNodePtr pre;

    pre = node->lChild;

    while (pre->rChild != nullptr)
        pre = pre->rChild;

    return pre;
}

// return postcessor of any node
betNodePtr BetAVL::getPostcessor(betNodePtr &node)
{
    // No Right Subtree
    if (node->rChild == nullptr)
        return nullptr;

    betNodePtr post;

    post = node->rChild;

    while (post->lChild != nullptr)
        post = post->lChild;

    return post;
}

// get the parent of any node
betNodePtr BetAVL::getParent(betNodePtr &node, betNodePtr &kid)
{
    if (node->lChild == kid || node->rChild == kid)
        return node;

    // Recurssively find parent
    if (node->getID() > kid->getID())
        return getParent(node->lChild, kid);
    else
        return getParent(node->rChild, kid);

    return nullptr; // error
}

// get the parent of any node - this is the main function that calls the other from the root
betNodePtr BetAVL::getParent(betNodePtr &kid)
{
    return getParent(this->root, kid);
}

// Remove any passed node
betNodePtr BetAVL::remove(betNodePtr &node, betNodePtr &removeNode)
{
    // Empty tree or leaf node
    if (this->root == nullptr || node == nullptr)
        return nullptr;

    // recursively find node in tree
    if (removeNode > node) // parse down right subtree
        return remove(node->rChild, removeNode);
    else if (removeNode < node) // parse down left subtree
        return remove(node->lChild, removeNode);

    // get predecessor
    betNodePtr pre = getPredecessor(removeNode);

    if (pre == nullptr) // In case left subtree is empty
        pre = getPostcessor(removeNode);

    // predecessor parent
    betNodePtr preParent = getParent(pre);

    betNodePtr removeNodeParent = nullptr;
    // TODO: logic for if removing head
    if (removeNode == this->root)
        root = pre; // Update Root
    else
        removeNodeParent = getParent(removeNode); // get the parent of node being removed

    // ReAssign the Predecessor's Child
    preParent->rChild = pre->lChild;

    // Update the Predecessor's Pointers
    pre->lChild = removeNode->lChild;
    pre->rChild = removeNode->rChild;

    if (root == pre)
        return removeNode;

    // relocate the Predecessor to removeNode's location
    if (removeNodeParent->lChild == removeNode)
        removeNodeParent->lChild = pre;
    else
        removeNodeParent->rChild = pre;

    return removeNode;
}

//-----------------------------------------------------------------------------------------
// Cashing Out

int BetAVL::settleLists(std::list<int> &winLoseList, int whichList)
{

    return 0;
}

/********************************************************************
    Public Functions
*********************************************************************/

// Insert
bool BetAVL::insert(int wageType, int wage, int point)
{
    betNodePtr betNode;

    // TODO: Add checking functionality for valid winnings

    // Point automatically passes as 0 if no point provided
    auto it = this->BetTypes.find(wageType);
    // betNode = it->second(wage, point); // Get appropriate Object to insert

    // Event of duplicate ID - TODO
    // while (!insert(this->root, betNode))      // Duplicate ID will return false
    //     betNode->setID(generateID(wageType)); // reset ID then loop again

    return true;
}

// Cashout --- Finish
int cashOutNode(betNodePtr &node, int const *theDie[])
{
}

int cashOutCheck(betNodePtr &node, int const *theDie[])
{
    int winnings{0};

    if (node)
    {
        cashOutCheck(node->lChild, theDie);

        cashOutCheck(node->rChild, theDie);
    }

    return 0;
}

// In Order Traversal
void BetAVL::inOrder()
{
    inOrder(this->root);
}

//-----------------------------------------------------------------------------------------
// Operator Overload for <<
/*
std::ostream &operator<<(std::ostream &os, const betNodePtr &node)
{

}
    */