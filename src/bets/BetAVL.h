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

  std::map<int, std::function<std::shared_ptr<BetNode>()>> BetTypes = {
      {1, []()
       { return std::make_shared<PassLineBet>(); }},
      {2, []()
       { return std::make_shared<DontPassLineBet>(); }},
      {3, []()
       { return std::make_shared<ComeBet>(); }},
      {4, []()
       { return std::make_shared<DontComeBet>(); }},
      {5, []()
       { return std::make_shared<OddsOnPassBet>(); }},
      {6, []()
       { return std::make_shared<OddsOnDontPassBet>(); }},
      {7, []()
       { return std::make_shared<OddsOnComeBet>(); }},
      {8, []()
       { return std::make_shared<OddsOnDontComeBet>(); }},
      {9, []()
       { return std::make_shared<PlaceToWinBet>(); }},
      {10, []()
       { return std::make_shared<PlaceToLoseBet>(); }},
      {11, []()
       { return std::make_shared<BuyBet>(); }},
      {12, []()
       { return std::make_shared<LayBet>(); }},
      {13, []()
       { return std::make_shared<Big6Bet>(); }},
      {14, []()
       { return std::make_shared<Big8Bet>(); }},
      {15, []()
       { return std::make_shared<FieldBet>(); }},
      {16, []()
       { return std::make_shared<AnyCrapsBet>(); }},
      {17, []()
       { return std::make_shared<AnySevenBet>(); }},
      {18, []()
       { return std::make_shared<YoBet>(); }},
      {19, []()
       { return std::make_shared<AceDeuceBet>(); }},
      {20, []()
       { return std::make_shared<SnakeEyesBet>(); }},
      {21, []()
       { return std::make_shared<BoxCarsBet>(); }},
      {22, []()
       { return std::make_shared<WorldBet>(); }},
      {23, []()
       { return std::make_shared<HornBet>(); }},
      {24, []()
       { return std::make_shared<HornHighBet>(); }},
      {25, []()
       { return std::make_shared<AllSmallBet>(); }},
      {26, []()
       { return std::make_shared<AllTallBet>(); }},
      {27, []()
       { return std::make_shared<HardwayBet>(); }},
      {28, []()
       { return std::make_shared<FireBet>(); }}

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
  BetAVL(int balance) : balance{balance} {}

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