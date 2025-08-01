#pragma once
#include <memory>
#include "BetNode.h" // Do not have to redeclare type alias because it is brought over
#include <list>
#include <algorithm>
#include <map>
#include <functional>

class BetAVL;

class BetAVL
{
private:
  int balance{0};

  // [] - variables from scope
  // () - parameter list
  std::map<int, std::function<std::shared_ptr<BetNode>(const int, const int)>> BetTypes = {
      {1, [](int balance, int)
       { return std::make_shared<PassLineBet>(balance); }},
      {2, [](int balance, int)
       { return std::make_shared<DontPassLineBet>(balance); }},
      {3, [](int balance, int)
       { return std::make_shared<ComeBet>(balance); }},
      {4, [](int balance, int)
       { return std::make_shared<DontComeBet>(balance); }},
      {5, [](int balance, int point)
       { return std::make_shared<OddsOnPassBet>(balance, point); }},
      {6, [](int balance, int point)
       { return std::make_shared<OddsOnDontPassBet>(balance, point); }},
      {7, [](int balance, int point)
       { return std::make_shared<OddsOnComeBet>(balance, point); }},
      {8, [](int balance, int point)
       { return std::make_shared<OddsOnDontComeBet>(balance, point); }},
      {9, [](int balance, int point)
       { return std::make_shared<PlaceToWinBet>(balance, point); }},
      {10, [](int balance, int point)
       { return std::make_shared<PlaceToLoseBet>(balance, point); }},
      {11, [](int balance, int point)
       { return std::make_shared<BuyBet>(balance, point); }},
      {12, [](int balance, int point)
       { return std::make_shared<LayBet>(balance, point); }},
      {13, [](int balance, int)
       { return std::make_shared<Big6Bet>(balance); }},
      {14, [](int balance, int)
       { return std::make_shared<Big8Bet>(balance); }},
      {15, [](int balance, int)
       { return std::make_shared<FieldBet>(balance); }},
      {16, [](int balance, int)
       { return std::make_shared<AnyCrapsBet>(balance); }},
      {17, [](int balance, int)
       { return std::make_shared<AnySevenBet>(balance); }},
      {18, [](int balance, int)
       { return std::make_shared<YoBet>(balance); }},
      {19, [](int balance, int)
       { return std::make_shared<AceDeuceBet>(balance); }},
      {20, [](int balance, int)
       { return std::make_shared<SnakeEyesBet>(balance); }},
      {21, [](int balance, int)
       { return std::make_shared<BoxCarsBet>(balance); }},
      {22, [](int balance, int)
       { return std::make_shared<WorldBet>(balance); }},
      {23, [](int balance, int)
       { return std::make_shared<HornBet>(balance); }},
      {24, [](int balance, int point)
       { return std::make_shared<HornHighBet>(balance, point); }},
      {25, [](int balance, int)
       { return std::make_shared<AllSmallBet>(balance); }},
      {26, [](int balance, int)
       { return std::make_shared<AllTallBet>(balance); }},
      {27, [](int balance, int point)
       { return std::make_shared<HardwayBet>(balance, point); }},
      {28, [](int balance, int)
       { return std::make_shared<FireBet>(balance); }}

  };

  std::map<int, char> numberToChar =
      {
          {1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'}, {5, 'E'}, {6, 'F'}, {7, 'G'}, {8, 'H'}, {9, 'I'}, {10, 'J'}, {11, 'K'}, {12, 'L'}, {13, 'M'}, {14, 'N'}, {15, 'O'}, {16, 'P'}, {17, 'R'}, {18, 'S'}, {19, 'T'}, {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'}, {25, 'Z'}, {26, 'a'}, {27, 'b'}, {28, 'c'}};

  std::map<char, int> intToChar =
      {
          {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5}, {'F', 6}, {'G', 7}, {'H', 8}, {'I', 9}, {'J', 10}, {'K', 11}, {'L', 12}, {'M', 13}, {'N', 14}, {'O', 15}, {'P', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}};

  // Tree Attributes
  betNodePtr root{nullptr};
  std::list<betNodePtr> winningTickets{};
  std::list<betNodePtr> losingTickets{};
  std::list<betNodePtr> washTickets{};
  std::list<betNodePtr> newBets{}; // easy update for things like Point value/FirstRoll val

  // Tree Methods
  int nodeHeight(const betNodePtr node);
  int balanceFactor(const betNodePtr node);
  // void updateHeightRotation(betNodePtr &node, betNodePtr &kid, betNodePtr &kidsKid);

  // Variadic Template for Height and BF updates
  template <typename... Nodes>
  void updateHeightAndBf(Nodes &...nodes);

  // Rotations
  void LLRotation(betNodePtr &node); // Right Rotation @ node
  void RRRotation(betNodePtr &node); // Left Rotation @ node
  void LRRotation(betNodePtr &node);
  void RLRotation(betNodePtr &node);

  // Balancing
  void rotationChecker(betNodePtr &node);
  void subTreeReBalance(betNodePtr &node);

  /*
      Insert
  */
  // ID Generating
  bool insert(betNodePtr &node, betNodePtr &betNode);

  bool sameID(const betNodePtr node, const betNodePtr betNode);
  bool validWagerAmount();

  // Traversals
  void inOrder(betNodePtr node);
  void preOrder(betNodePtr node);
  void postOrder(betNodePtr node);

  // Winning & Losing Evaluation
  void updateFirstRoll(betNodePtr &node);
  bool inContainer(const std::list<int> winnersCircle, const int point);
  bool isWinner(const betNodePtr node, const int *theDie[]);   // not done
  bool isLoser(betNodePtr node, const int *theDie[]);          // not done
  bool isTie(const betNodePtr node, const int *theDie[]);      // not done
  void winSomeLoseSome(betNodePtr &node, const int *theDie[]); // Add winners, losers, scratches to lists

  // Removal Helpers
  betNodePtr getPredecessor(betNodePtr &node);
  betNodePtr getPostcessor(betNodePtr &node);
  betNodePtr getParent(betNodePtr &node, betNodePtr &kid);
  betNodePtr getParent(betNodePtr &kid); // public??

  // Remove
  betNodePtr remove(betNodePtr &removeNode, betNodePtr &node);

  // Cashing Out Helper ~ TODO
  /*
      3/1/2025 - Make these in PlayerNode.h so that the balance can be updated
                  Then make a helper function that returns winnings amount (here)
                  Call function until List.empty == 1
  */
  int settleLists(std::list<int> &winLoseList, int listNum); // TODO
  int cashOutNode(betNodePtr &node, int const *theDie[]);    // TODO

public:
  // Constructor
  BetAVL() = default;
  BetAVL(const int &balance) : balance{balance} {}

  // Destructor
  ~BetAVL() = default;

  // Insert
  void generateNewBet(const int &wageType, const int &balance);
  bool insert(int wageType, int wage, int point = 0);

  // Removal
  bool remove();

  // Cashout
  int cashOutCheck(betNodePtr &node, int const *theDie[]);

  // Traversals
  void inOrder();
  void preOrder();
  void postOrder();

  bool isEmpty();
};
std::ostream &operator<<(std::ostream &os, const betNodePtr &betNode); // Operator overload for cout