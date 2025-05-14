#pragma once
#include <memory>
#include "BetNode.h" // Do not have to redeclare type alias because it is brought over
#include <list>
#include <algorithm>
#include <map>
class BetAVL;

// Type Alias
using arr = std::shared_ptr<int[]>;
class BetAVL
{
private:
  std::map<int, char> numberToChar =
      {
          {1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'}, {5, 'E'}, {6, 'F'}, {7, 'G'}, {8, 'H'}, {9, 'I'}, {10, 'J'}, {11, 'K'}, {12, 'L'}, {13, 'M'}, {14, 'N'}, {15, 'O'}, {16, 'P'}, {17, 'R'}, {18, 'S'}, {19, 'T'}, {20, 'U'}, {21, 'V'}, {22, 'W'}, {23, 'X'}, {24, 'Y'}, {25, 'Z'}, {26, 'a'}, {27, 'b'}, {28, 'c'}, {29, 'd'}};

  std::map<char, int> intToChar =
      {
          {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5}, {'F', 6}, {'G', 7}, {'H', 8}, {'I', 9}, {'J', 10}, {'K', 11}, {'L', 12}, {'M', 13}, {'N', 14}, {'O', 15}, {'P', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}, {'d', 29}};

  // std::map<BetAVL::betTypes, std::map<int, double>> betToPayout = // BetType->Roll->PayoutRatio
  //     {

  //         {BetAVL::betTypes::passBet,
  //          {{7, 1.0},
  //           {11, 1.0}}},
  //         {BetAVL::betTypes::dontPassBet,
  //          {{2, 1.0},
  //           {3, 1.0}}},

  //         {BetAVL::betTypes::comeBet,
  //          {{7, 1.0},
  //           {11, 1.0}}},
  //         {BetAVL::betTypes::dontComeBet,
  //          {{2, 1.0},
  //           {3, 1.0}}},
  //         {BetAVL::betTypes::oddsOnPassBet,
  //          {{4, 2.0},
  //           {5, 3 / 2},
  //           {6, 6 / 5},
  //           {8, 6 / 5},
  //           {9, 3 / 2},
  //           {10, 2.0}}},
  //         {BetAVL::betTypes::oddsOnDontPassBet,
  //          {{4, 1 / 2},
  //           {5, 2 / 3},
  //           {6, 5 / 6},
  //           {8, 5 / 6},
  //           {9, 2 / 3},
  //           {10, 1 / 2}}},
  //         {BetAVL::betTypes::oddsOnComeBet,
  //          {{4, 2.0},
  //           {5, 3 / 2},
  //           {6, 6 / 5},
  //           {8, 6 / 5},
  //           {9, 3 / 2},
  //           {10, 2.0}}},
  //         {BetAVL::betTypes::oddsOnDontComeBet,
  //          {{4, 1 / 2},
  //           {5, 2 / 3},
  //           {6, 5 / 6},
  //           {8, 5 / 6},
  //           {9, 2 / 3},
  //           {10, 1 / 2}}},
  //         {BetAVL::betTypes::placeToWinBet,
  //          {{4, 9 / 5},
  //           {5, 7 / 5},
  //           {6, 7 / 6},
  //           {8, 7 / 6},
  //           {9, 7 / 5},
  //           {10, 9 / 5}}},
  //         {BetAVL::betTypes::placeToLoseBet,
  //          {{4, 5 / 11},
  //           {5, 5 / 8},
  //           {6, 4 / 5},
  //           {8, 4 / 5},
  //           {9, 5 / 8},
  //           {10, 5 / 11}}},

  //         {BetAVL::betTypes::buyBet, // 5% commission
  //          {{4, 2.0},
  //           {5, 3 / 2},
  //           {6, 6 / 5},
  //           {8, 6 / 5},
  //           {9, 3 / 2},
  //           {10, 2.0}}},
  //         {BetAVL::betTypes::layBet, // 5% commission
  //          {{4, 1 / 2},
  //           {5, 2 / 3},
  //           {6, 5 / 6},
  //           {8, 5 / 6},
  //           {9, 2 / 3},
  //           {10, 1 / 2}}},
  //         {BetAVL::betTypes::big6Bet,
  //          {{6, 1.0}}},
  //         {BetAVL::betTypes::big8Bet,
  //          {{8, 1.0}}},

  //         {BetAVL::betTypes::fieldBet,
  //          {{2, 2.0},
  //           {3, 1.0},
  //           {4, 1.0},
  //           {9, 1.0},
  //           {10, 1.0},
  //           {11, 1.0},
  //           {12, 2.0}}},
  //         {BetAVL::betTypes::anyCrapsBet,
  //          {{2, 7.0},
  //           {3, 7.0},
  //           {12, 7.0}}},
  //         {BetAVL::betTypes::anySevenBet,
  //          {{7, 4.0}}},
  //         {BetAVL::betTypes::yoBet,
  //          {{11, 15.0}}},
  //         {BetAVL::betTypes::aceDeuceBet,
  //          {{3, 15.0}}},
  //         {BetAVL::betTypes::snakeEyesBet,
  //          {{2, 30.0}}},
  //         {BetAVL::betTypes::boxCarsBet,
  //          {{12, 30.0}}},
  //         {BetAVL::betTypes::crapsAndElevenBet,
  //          {{2, 7.0},
  //           {3, 7.0},
  //           {11, 15.0},
  //           {12, 7.0}}},
  //         {BetAVL::betTypes::whirlBet,
  //          {{2, 30.0},
  //           {3, 15.0},
  //           {7, 0.0},
  //           {11, 15.0},
  //           {12, 30.0}}},
  //         {BetAVL::betTypes::hornBet,
  //          {{2, 30.0},
  //           {3, 15.0},
  //           {11, 15.0},
  //           {12, 30.0}}},
  //         {BetAVL::betTypes::hornHighBet,
  //          {{2, 15.0},
  //           {3, 15.0},
  //           {11, 15.0},
  //           {12, 30.0}}},
  //         {BetAVL::betTypes::allSmallBet, // All rolled before 7
  //          {{2, 30.0},
  //           {3, 30.0},
  //           {4, 30.0},
  //           {5, 30.0},
  //           {6, 30.0}}},
  //         {BetAVL::betTypes::allTallBet, // All rolled before 7
  //          {{8, 30.0},
  //           {9, 30.0},
  //           {10, 30.0},
  //           {11, 30.0},
  //           {12, 30.0}}},

  //         {BetAVL::betTypes::hardwaysBet, // Bet on specific value - loses on easy  way or 7
  //          {{4, 7.0},
  //           {6, 9.0},
  //           {8, 9.0},
  //           {10, 7.0}}},
  //         {BetAVL::betTypes::fireBet, // Shooter must HIT on 4,5,6+ points
  //          {{4, 25.0},
  //           {5, 250.0},
  //           {6, 1000.0}}}};

  // Tree Attributes
  betNodePtr root;
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
      Insert Helpers
  */
  // ID Generating
  int randNum();
  arr randomArr();
  std::string arrToString(arr tmp);
  std::string generateID(int userInput);
  bool sameID(const betNodePtr node, const betNodePtr betNode);
  bool validWagerAmount();
  bool insert(betNodePtr &node, betNodePtr &betNode);

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
  BetAVL() : root(nullptr) {}
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