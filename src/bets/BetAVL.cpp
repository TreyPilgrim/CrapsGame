#include "BetAVL.h"
int ARR_SIZE = 7;
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

// Random number 0-9 Generator
int BetAVL::randNum()
{
    return rand() % 10;
}

arr BetAVL::randomArr()
{
    arr tmp = std::shared_ptr<int[]>(new int[ARR_SIZE]);

    for (int i = 0; i < ARR_SIZE; i++)
    {
        tmp[i] = randNum();
    }

    return tmp;
}

// Converting array of random #s into strings so ID can be made
std::string BetAVL::arrToString(arr tmp)
{
    std::string str;

    for (int i = 0; i < ARR_SIZE; i++)
    {
        str += std::to_string(tmp[i]);
    }

    return str;
}

// ID Generator
std::string BetAVL::generateID(int userInput) // User Input is the type of bet
{
    std::string prefix, numString, ID;

    prefix = numberToChar[userInput];

    arr nums = randomArr();
    numString = arrToString(nums);

    ID = prefix + numString;

    return ID;
}

// Id checker
bool BetAVL::sameID(const betNodePtr node, const betNodePtr betNode)
{
    if (node->getID() == betNode->getID())
        return true;

    return false;
}

// Wager Checker

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
    if (node == nullptr)
        return;

    updateFirstRoll(node->lChild);
    updateFirstRoll(node->rChild);

    if (node->isFirstRoll())
        node->secondRoll();
}
// inContainer
bool BetAVL::inContainer(const std::list<int> winnersCircle, const int point)
{
    return std::find(winnersCircle.begin(), winnersCircle.end(), point) != winnersCircle.end();
}
// isWinner
bool BetAVL::isWinner(const betNodePtr node, const int *theDie[])
{
    char bet = node->getBetType();
    std::list<int> winners = {};

    switch (bet)
    {
    //-------------------------------------------------
    // Come out Roll Bets

    // Pass Bet
    case 'A': // Look into A and C having the same code and condensing
        if (node->isFirstRoll())
        {
            if (*theDie[2] == 7 || *theDie[2] == 11)
                return true;
        }

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Don't Pass
    case 'B':
        if (node->isFirstRoll())
        {
            if (*theDie[2] == 2 || *theDie[2] == 3)
                return true;
        }

        if (*theDie[2] == 7)
            return true;

        break;
    //-------------------------------------------------
    // Post Come Out

    // Come
    case 'C': // Logic for First Roll nonsense

        if (node->isFirstRoll())
        {
            if (*theDie[2] == 7 || *theDie[2] == 11)
                return true;
        }

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Don't Come
    case 'D':

        if (node->isFirstRoll())
        {
            if (*theDie[2] == 2 || *theDie[2] == 3)
                return true;
        }

        if (*theDie[2] == 7)
            return true;

        break;

    // Odds on Pass
    case 'E': // Bet on Pass
        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Odds on Don't Pass
    case 'F':

        if (*theDie[2] == 7)
            return true;
        break;

    // Odds on Come
    case 'G':
        if (node->getPoint() == *theDie[2])
            return true;

        break;

    // Odds on Don't Come
    case 'H':
        if (*theDie[2] == 7)
            return true;
        break;

    // Place to Win
    case 'I': // Place To Wine

        if (*theDie[2] == node->getPoint())
            return true;
        break;

    // Place to Lose
    case 'J':

        if (*theDie[2] == 7)
            return true;
        break;

    //-------------------------------------------------
    // Any-Time Place Bets - Any Time

    // Buy
    case 'K':

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Lay
    case 'L':

        if (*theDie[2] == 7)
            return true;

        break;

    // Big 6
    case 'M':

        if (*theDie[2] == 6)
            return true;
        break;

    // Big 8
    case 'N':

        if (*theDie[2] == 8)
            return true;

        break;
    //-------------------------------------------------
    // Single-Roll Proposition Bets - Any Time

    // Field  ****NEEDS TO INCORPORATE LOGIC FOR 2 & 12 WINS on the return
    case 'O':

        winners = {2, 3, 4, 9, 10, 11, 12};

        if (inContainer(winners, node->getPoint()))
            return true;

        break;

    // Any Craps
    case 'P':

        winners = {2, 3, 12};

        if (inContainer(winners, *theDie[2]))
            return true;

        break;

    // Any Seven - Big Red
    case 'R':

        if (*theDie[2] == 7)
            return true;

        break;

    // Yo
    case 'S':

        if (*theDie[2] == 11)
            return true;

        break;

    // Ace Deuce
    case 'T':

        if (*theDie[2] == 3)
            return true;

        break;

    // Snake Eyes
    case 'U':

        if (*theDie[2] == 2)
            return true;

        break;

    // Box Car
    case 'V':

        if (*theDie[2] == 12)
            return true;

        break;

    // Craps and Eleven
    case 'W':

        winners = {2, 3, 11, 12};

        if (inContainer(winners, *theDie[2]))
            return true;

        break;

    // Whirl
    case 'X':

        winners = {2, 3, 7, 11, 12};

        if (inContainer(winners, *theDie[2]))
            return true;

        break;

    // Horn
    case 'Y':

    // Horn High
    case 'Z':

    // All Small
    case 'a':

    // All Tall
    case 'b':

    //-------------------------------------------------
    // Multi-Roll Proposition Bets - Any Time

    // Hardways
    case 'c':
        winners = {4, 6, 8, 10};

        if (inContainer(winners, *theDie[2]) && *theDie[0] == *theDie[1])
            return true;

        break;

    // Fire
    case 'd':

    default:
        return false;
    }

    return false;
}

// isLoser
bool BetAVL::isLoser(betNodePtr node, const int *theDie[])
{
    char bet = node->getBetType();
    std::list<int> losers = {};
    std::list<int> winners = {};

    switch (bet)
    {

    //-------------------------------------------------
    // Come out Roll Bets

    // Pass
    case 'A': // Look into A and C having the same code and condensing
        losers = {2, 3, 12};
        if (node->isFirstRoll())
        {
            if (inContainer(losers, *theDie[2]))
                return true;
        }

        if (*theDie[2] == 7)
            return true;

    // Don't Pass
    case 'B':

        if (node->isFirstRoll())
        {
            if (*theDie[2] == 7 || *theDie[2] == 11)
                return true;
        }

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    //-------------------------------------------------
    // Post Come Out

    // Come
    case 'C':

        losers = {2, 3, 12};

        if (node->isFirstRoll())
        {
            if (inContainer(losers, *theDie[2]))
                return true;
        }

        if (*theDie[2] == 7)
            return true;

        break;

    // Don't Come
    case 'D':

        if (node->isFirstRoll())
        {
            if (*theDie[2] == 7 || *theDie[2] == 11)
                return true;
        }

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Odds on Pass
    case 'E':

        if (*theDie[2] == 7)
            return true;

        break;
    // Odds on Don't Pass
    case 'F':

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Odds on Come
    case 'G':

        if (*theDie[2] == 7)
            return true;

        break;

    // Odds on Don't Come
    case 'H':

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Place to Win
    case 'I':

        if (*theDie[2] == 7)
            return true;

        break;

    // Place to Lose
    case 'J':

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    //-------------------------------------------------
    // Any-Time Place Bets - Any Time
    // Buy
    case 'K':

        if (*theDie[2] == 7)
            return true;

        break;
    // Lay
    case 'L':

        if (*theDie[2] == node->getPoint())
            return true;

        break;

    // Big 6
    case 'M':

        if (*theDie[2] == 7)
            return true;

        break;

    // Big 8
    case 'N':

        if (*theDie[2] == 7)
            return true;

        break;

    //-------------------------------------------------
    // Single-Roll Proposition Bets - Any Time
    // Field
    case 'O':

        winners = {2, 3, 4, 9, 10, 11, 12};

        if (!inContainer(winners, *theDie[2]))
            return true;

        break;

    // Any Craps
    case 'P':

        winners = {2, 3, 12};

        if (!inContainer(winners, *theDie[2]))
            return true;

        break;

    // Any Seven
    case 'R':

        if (*theDie[2] != 7)
            return true;

        break;

    // Yo
    case 'S':

        if (*theDie[2] != 11)
            return true;

        break;

    // Ace Deuce
    case 'T':

        if (*theDie[2] != 3)
            return true;

        break;

    // Snake Eyes
    case 'U':

        if (*theDie[2] != 2)
            return true;

        break;

    // Box Cars
    case 'V':

        if (*theDie[2] != 12)
            return true;

        break;

    // Crap and Eleven
    case 'W':
        winners = {2, 3, 11, 12};

        if (!inContainer(winners, *theDie[2]))
            return true;

        break;

    // Whirl
    case 'X':
        winners = {2, 3, 7, 11, 12};

        if (!inContainer(winners, *theDie[2]))
            return true;

        break;

    // Horn
    case 'Y':
        break;
    // Horn High
    case 'Z':
        break;

    // All Small
    case 'a':
        break;

    // All Tall
    case 'b':
        break;
    //-------------------------------------------------
    // Multi-Roll Proposition Bets - Any Time
    // Hardways
    case 'c':
        winners = {4, 6, 8, 10};

        if (((inContainer(winners, *theDie[2]) && *theDie[0] != *theDie[1])) || !inContainer(winners, *theDie[2]))
            return true;

        break;

    // Fire
    case 'd':
        break;

    default:
        return false;
    }

    return false;
}

// isTie
bool BetAVL::isTie(const betNodePtr node, const int *theDie[])
{
    char bet = node->getBetType();

    switch (bet)
    {

    //-------------------------------------------------
    // Come out Roll Bets
    // Pass
    case 'A': // Look into A and C having the same code and condensing

    // Don't Pass
    case 'B':

    //-------------------------------------------------
    // Post Come Out
    // Come
    case 'C':

    // Don't Come
    case 'D':

    // Odds on Pass
    case 'E':

    // Odds on Don't Pass
    case 'F':

    // Odds on Come
    case 'G':

    // Odds on Don't Come
    case 'H':

    // Place to Win
    case 'I':

    // Place to Lose
    case 'J':

    //-------------------------------------------------
    // Any-Time Place Bets - Any Time
    // Buy
    case 'K':

    // Lay
    case 'L':

    // Big 6
    case 'M':

    // Big 8
    case 'N':

    //-------------------------------------------------
    // Single-Roll Proposition Bets - Any Time
    // Field
    case 'O':

    // Any Craps
    case 'P':

    // Any Seven
    case 'R':

    // Yo
    case 'S':

    // Ace Deuce
    case 'T':

    // Snake Eyes
    case 'U':

    // Box Cars
    case 'V':

    // Crap and Eleven
    case 'W':

    // Whirl
    case 'X':

    // Horn
    case 'Y':

    // Horn High
    case 'Z':

    // All Small
    case 'a':

    // All Tall
    case 'b':

    //-------------------------------------------------
    // Multi-Roll Proposition Bets - Any Time
    // Hardways
    case 'c':

    // Fire
    case 'd':
        break;
    }

    return false;
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
    betNode = std::make_shared<BetNode>(wageType, wage, point);

    while (!insert(this->root, betNode))      // Duplicate ID will return false
        betNode->setID(generateID(wageType)); // reset ID then loop again

    return true;
}

// Cashout --- Finish
int cashOutNode(betNodePtr &node, int const *theDie[])
{
    switch (node->getBetType())
    {
    case 1:
        break;
    }

    return 0;
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
    char bet = node->getBetType();

    os << "Bet Type: ";

    switch (bet)
    {
    //-------------------------------------------------
    // Come out Roll Bets
    // Pass
    case 'A': // Look into A and C having the same code and condensing

        os << "Pass Bet\n";

        if (!node->isFirstRoll())
            os << "Point: " << node->getPoint() << "\n";

        break;

    // Don't Pass
    case 'B':

        os << "Don't Pass Bet\n";

        if (!node->isFirstRoll())
            os << "Point: " << node->getPoint() << "\n";

        break;
    //-------------------------------------------------
    // Post Come Out
    // Come
    case 'C':

        os << "Come BetBet\n";

        if (!node->isFirstRoll())
            os << "Point: " << node->getPoint() << "\n";

        break;

    // Don't Come
    case 'D':

        os << "Don't Come Bet\n";

        if (!node->isFirstRoll())
            os << "Point: " << node->getPoint() << "\n";

        break;

    // Odds on Pass
    case 'E':

        os << "Odds on Pass Bet\n";
        os << "Point: " << node->getPoint() << "\n";

        break;

    // Odds on Don't Pass
    case 'F':

        os << "Odds on Don't Pass Bet\n";
        os << "Point: " << node->getPoint() << "\n";

        break;

    // Odds on Come
    case 'G':

        os << "Odds on Come Bet\n";
        os << "Point: " << node->getPoint() << "\n";

        break;

    // Odds on Don't Come
    case 'H':

        os << "Odds on Don't Come Bet\n";
        os << "Point: " << node->getPoint() << "\n";
        break;

    // Place to Win
    case 'I':

        os << "Place to Win Bet\n";
        os << "Point: " << node->getPoint() << "\n";

        break;

    // Place to Lose
    case 'J':

        os << "Place to Lose Bet\n";
        os << "Point: " << node->getPoint() << "\n";

        break;

    //-------------------------------------------------
    // Any-Time Place Bets - Any Time
    // Buy
    case 'K':

        os << "Buy Bet\n";
        os << "Point: " << node->getPoint() << "\n";

        break;

    // Lay
    case 'L':

        os << "Lay Bet\n";
        os << "Point: " << node->getPoint() << "\n";

        break;

    // Big 6
    case 'M':

        os << "Big 6 Bet\n";
        os << "Point: " << node->getPoint() << "\n"; // May Remove Line
        break;

    // Big 8
    case 'N':

        os << "Big 8 Bet\n";
        os << "Point: " << node->getPoint() << "\n"; // May Remove Line
        break;

    //-------------------------------------------------
    // Single-Roll Proposition Bets - Any Time
    // Field
    case 'O':

        os << "Field Bet\n";
        break;

    // Any Craps
    case 'P':

        os << "Any Craps Bet\n";
        break;

    // Any Seven
    case 'R':

        os << "Any Seven Bet\n";
        break;

    // Yo
    case 'S':

        os << "Yo Bet\n";
        break;

    // Ace Deuce
    case 'T':

        os << "Ace Deuce Bet\n";
        break;

    // Snake Eyes
    case 'U':

        os << "Snake Eyes Bet\n";
        break;

    // Box Cars
    case 'V':

        os << "Box Cars Bet\n";

    // Crap and Eleven
    case 'W':

        os << "Craps and Eleven Bet\n";

    // Whirl
    case 'X':

        os << "Whirl Bet\n";
        break;

    // Horn
    case 'Y':

        os << "Horn Bet\n";
        break;

    // Horn High
    case 'Z':

        os << "Horn High Bet\n";
        break;

    // All Small
    case 'a':

        os << "All Small Bet\n";
        break;

    // All Tall
    case 'b':

        os << "All Tall Bet\n";
        break;

    //-------------------------------------------------
    // Multi-Roll Proposition Bets - Any Time
    // Hardways
    case 'c':

        os << "Hardways Bet\n";
        break;

    // Fire
    case 'd':

        os << "Fire Bet\n";
        break;
    }

    os << "Bet Amount: $" << node->getWager() << "\n";
}
    */