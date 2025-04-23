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

9/3/2024

- The goal for today is upgrade the BetList and PlayerList classes
  - Determine if BetNode is a winner (BetList)
    - Return winnings (+/-)
  - Function in PlayerList to parse every node's BetList function to get winnings/losings
    - Add to Player's wages

9/5/2024

- PlayerList function
  - parse every node's BetList
  - get Winnings/Losings
    - Add to Player Wages

9/7/2024

- The goal is to restructure all functions to only display/get/set information
  - Keep the task(s) simple
    -> anything like cin/case checking/etc save for main Craps Function

10/16/2024

- Felt discouraged by outside influences to finish this project. Will be the last time I allow something like that to happen.
- Spent yesterday refreshing myself with the code base.
- Spending today before work to knock out arithmetic for the dice rolling results.
  - Going to make a stack to hold the different types of bets
  - Had an epiphany that an AVL would be more optimal for searching. Going to start working on building the AVL this week.

12/29/2024

- Finally finished implementing the BetList as a tree
- Continuing production today for the rest of the game mechanics
- Adding shooter validation as well as updating.
  - Going to have a pointer constantly looking at the shooter to avoid searching all the time

TODO:: 12/29
Work on mechanics after a roll has been made

1/6/2025

TODO: Work on ID for added bets

1/15/2025

Glad with production... will be debugging...

1/27/2025

TODO: Revamp Remove and Insert (clean up code, finish coding remove)

- Insert has been beefed up and completed

TODO: Create a Stack for the winning/losing bets to make displaying easier

1/29/2025

- A lot of code had logic errors. Proof read all code pertaining to rotations and buffered it
- Buffed up the code for insertion
- Decided to use vectors to keep up with winning/losing tickets so that sorting can be easier // gotta do logic for this
- That i can think of; after implementing remove; i have to implement display features then finish implementing the Craps function and this game should be just about done... for now lol

1/31/2025

- For the remove logic; I want it to automatically find the post successor in the event that there is no left subtree (should only be 1 node because of AVL logic but still)

2/2/2025

- Found out there were numerous bets left out of the game... thanks chatgpt
  - will return to this.
- The main focus is getting the remove functionality finished today.
  - 2 big functions;
    -> 1 to add tickets to list (DONE)
    -> 1 to parse vector and remove nodes from tree
    -> update wages (may make a function) then clear vectors

2/3/2025

- Need to update insert and creation of betNodes to handle all bet types
- Thinking about turning the Craps game into a Object (OOP) will determine in coming days
- Where to Pick UP: first point ^^ then work on functions for determining if node is a winner

2/16/2025

- Make all bets that have a "First roll" work with the comeOut Roll operation (50% \*3/3)

2/18/2025

- Make nodes have a "firstRoll" bool value to track if the bet is in it's first roll phase (DONE)
  -> add functions to update bool value (DONE)

3/1/2025

- Add a "winnings"/"To Win" value in BetNode.h
- Update PlayerNode.h to call functions that clear out winning/losing/draw lists
- Finish winning/losing/draw function in BetAVL.h

3/3/2025

Todo:

- BetAVL::insert(int wageType, int wage, int point)

Completed:

3/15/2025

- make PlayerList::pushWager accept char values and determine what the bet type is from there -- possibly return an int (0 - 0 errors; 1 - invalid funds; 2 - invalid input for betType)

completed:

- Look into placing the enum values in BetAVL
  -> consider using a map to make assignment easier - currently makes an enum each time a node is made (uneccessary)
  -> UPDATE 4/2/25: chose not to go this route. Considering making a map in order to displaying a little easier but tbd

4/5/25

- Look into
  -> Making Craps quit after roller craps out. \* from there prompt if the user wants to keep playing

4/7/2025

- Working on reframing front end.

I didn't like how the user had case sensitive entries for choices. Craps is played in a Casino, people are drunk - off both booze and adrenaline - remembering to capitalize 'a' isn't something they should worry about. will make char a string to handle double digits and Roll and Quit can still be char inputs. betType is represented as a # in code so this will make comparison easier as well

4/8/2025

TODO (4/9/2025)

- Reconstruct BetAVL
  -> I want BetNode to be a shell that only holds information. I don't want any functions besides getters and setters in it
  Completed:

4/11/2025

            TODO:

            Look into "Make 'em All" bets
            175:1 odds

            Completed:
