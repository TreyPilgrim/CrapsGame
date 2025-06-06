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
  std::map<int, std::function<std::shared_ptr<BetNode>(int, int)>> BetTypes = {
      {1, [](int wage, int)
       { return std::make_shared<PassLineBet>(wage); }},
      {2, [](int wage, int)
       { return std::make_shared<DontPassLineBet>(wage); }},
      {3, [](int wage, int)
       { return std::make_shared<ComeBet>(wage); }},
      {4, [](int wage, int)
       { return std::make_shared<DontComeBet>(wage); }},
      {5, [](int wage, int point)
       { return std::make_shared<OddsOnPassBet>(wage, point); }},
      {6, [](int wage, int point)
       { return std::make_shared<OddsOnDontPassBet>(wage, point); }},
      {7, [](int wage, int point)
       { return std::make_shared<OddsOnComeBet>(wage, point); }},
      {8, [](int wage, int point)
       { return std::make_shared<OddsOnDontComeBet>(wage, point); }},
      {9, [](int wage, int point)
       { return std::make_shared<PlaceToWinBet>(wage, point); }},
      {10, [](int wage, int point)
       { return std::make_shared<PlaceToLoseBet>(wage, point); }},
      {11, [](int wage, int point)
       { return std::make_shared<BuyBet>(wage, point); }},
      {12, [](int wage, int point)
       { return std::make_shared<LayBet>(wage, point); }},
      {13, [](int wage, int)
       { return std::make_shared<Big6Bet>(wage); }},
      {14, [](int wage, int)
       { return std::make_shared<Big8Bet>(wage); }},
      {15, [](int wage, int)
       { return std::make_shared<FieldBet>(wage); }},
      {16, [](int wage, int)
       { return std::make_shared<AnyCrapsBet>(wage); }},
      {17, [](int wage, int)
       { return std::make_shared<AnySevenBet>(wage); }},
      {18, [](int wage, int)
       { return std::make_shared<YoBet>(wage); }},
      {19, [](int wage, int)
       { return std::make_shared<AceDeuceBet>(wage); }},
      {20, [](int wage, int)
       { return std::make_shared<SnakeEyesBet>(wage); }},
      {21, [](int wage, int)
       { return std::make_shared<BoxCarsBet>(wage); }},
      {22, [](int wage, int)
       { return std::make_shared<WorldBet>(wage); }},
      {23, [](int wage, int)
       { return std::make_shared<HornBet>(wage); }},
      {24, [](int wage, int highNum)
       { return std::make_shared<HornHighBet>(wage, highNum); }},
      {25, [](int wage, int)
       { return std::make_shared<AllSmallBet>(wage); }},
      {26, [](int wage, int)
       { return std::make_shared<AllTallBet>(wage); }},
      {27, [](int wage, int point)
       { return std::make_shared<HardwayBet>(wage, point); }},
      {28, [](int wage, int)
       { return std::make_shared<FireBet>(wage); }}

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
  // Destructor
  ~BetAVL() = default;

  // Insert
  bool insert(int wageType, int wage, int point = 0);

  // Removal
  bool remove();

  // Cashout
  int cashOutCheck(betNodePtr &node, int const *theDie[]);

  // Traversals
  void inOrder();
  void preOrder();
  void postOrder();
};
std::ostream &operator<<(std::ostream &os, const betNodePtr &betNode); // Operator overload for cout