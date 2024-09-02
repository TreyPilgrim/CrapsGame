7/11/2024

- This is an implementation of the popular Casino Game "Craps." As of today, the game is under construction. There is no functionality.

7/13/2024

- A thought, What if I added a text analyzer? In the event of misspelling, it would use an algorithm to detect whats the closest spelt word and inquires about "is this what you meant?"
  - will implement it in the basic "enter 1- easy; 2 - med; 3 - hard" format for now

7/13/2024

- Next login, work on PlayerLinkedList and BetLinkedList

8/6/2024

- Grew frustrated and took a break from this project.
  - Had other things to worry about too lol
- Will use today to work on the LinkedList (BetList & PlayerList) functionality. (push, pop, peek/display)
- Goal of this week will be to get the Linked List working properly
  - Next week will be getting the bets to function properly (make a bet)

8/18/2024

- Make sure to update the [Playerlist] push function to handle an int value (balance)
- Linked List coming along nicely... keep progressing

8/23/2024

- Get up to date

8/28/2024

- Goal for today is to finish BetNode and BetList.
- Begin testing afterwards

9/2/2024

- Ran into an unexpected error:

  - The program wouldn't let me add bets to BetList
  - Found out this was because I was initializing the BetList variable to nullptr

  \*\* WHY this isn't proper

  - when initializing shared pointers like head/tail or next/prev, make_shared gets called
    for the tmp pointer and that pointer gets assigned to head/tail or next/prev.
    - that's why they can be initialized to nullptr
  - BetList needs to be initialized to a BetList so that it may be used.
    - Setting it to nullptr without ever initializing it to a BetList was the issue

  \*\* SOLUTION

  - Setting the BetList variable to make_shared<BetList> was the solution

- The goals for this week
  - Check that dice value rolled isn't/is a winner/craps
  - Code the logic for ongoing bets (come/dontCome)
  - Revamp the game with boolean checkers for the round being new/ongoing/quit
