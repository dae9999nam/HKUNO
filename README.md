# //////////////////////////////////////////////
# //////// Welcome to HKUNO ////////
# //////////////////////////////////////////////
ENGG1340 / COMP 2113 Group Project 2023/2024 - Group #21
## Team members
- Baek Seunghyeon (3035821659)
- Fan Zihan (3035948471)
- Fu Wenqi (3036098053)
- Wei Jianfeng (3036094899)
- Tong Cheuk Yin (3036068503)

## Description
UNO is a classic card game that is played with a specially printed deck. The objective of the game is to be the first player to get rid of all your cards. Players take turns matching a card in their hand with the current card shown on top of the deck either by color or number. The game also includes special action cards that can change the course of the game. With this idea, we designed text-based UNO game called HKUNO based on C++. This UNO game supports saving and loading options for players for convenience.  

This UNO game implementation provides a command-line interface to play the game against computer opponents.

## Features
- Play against computer opponents.
- Interactive command-line interface.
- Special action cards: Draw 2, Reverse, Skip, and Wild cards(Wild and Wild Draw 4).
- The first card is randomly gernerated for the equality by the function "randomSingleUNO()". **(Generation of random game sets or events)**
- Array data structure is used for storing the player's cards and AIs' cards. **(Data structures for storing game status)** 
- Dynamic memory allocation is used for storing players and players' cards. **(Dynamic Memory Management)**
- Player has an option called "wq" for storing and quit the current game or loading game status in the beginning of the game. **(File Input/Output)**
- Each critical function (e.g. AI behavior, card effect, etc) is stored in different files rather than main program. **(Program codes in multiple files)**
- Each functions and variable used are in proper name style with correct indentation. **(Proper indentation and naming style)**
- Each blocks or lines of code includes explanation for its role. **(In-code documentation)**

## Compliation & Installation
1. Clone the repository: `git clone "https://github.com/NaClts/CLI-UNO.git"`
2. Navigate to the project directory: `cd CLI-UNO-main`
3. Compile the source code: `make`
4. Run the game: `./main`

## Controls & Instructions (How to play)
If you run the game, there are 4 options for you:

1. start a new game
2. Load a game
3. About this game
4. Exit the game

Based on your choice, you can start a new game or load a game if you have previously played this game. Rather than that, you can choose to get brief information about this game or leave this game.

**Here comes the Rule of the HKUNO game:**

1. Starting the Game: 
You will be prompted to enter the number of AI opponents and the number of cards for each player to start with. The remaining deck is placed in the center and the random top card is revealed to start the discard pile.

2. During Your Turn: 
During your turn, you have to make a decision, to put valid card or draw on card from the deck and finish the turn. To put the valid card, you need to check the color or number of the current card. When you type the card you need to type "color""number" without any space between color and number.

3. Special Cards: 
There are special cards in the game like 'Skip', 'Reverse', 'Draw Two', 'Wild', and 'Wild Draw Four' which have unique effects on the gameplay.
- Skip : Skip card makes a jump so that original next player cannot play for his/her turn.
- Reverse: Reverse card changes the direction of the turns and it can be overlapped.
- Draw Two: Draw Two card makes next player to get two extra cards from the deck.
- Wild: When you put wild card, you can choose which color of card the next player should put. This can be a critical card if you use when everyone get small number of cards!
- Wild Draw Four: This card makes next player take FOUR cards from the deck. If you consider the objective of this game, this is a really strong card!! 

5. AI Players: 
You are going to play against as many AI players as you want! If you want to know about their behavior, you may refer to AI_requestAI.cpp.

6. Saving and Loading Game Progress: 
You can save and load game progress. The functionality for this is defined in SaveAndLoad.cpp.


7. Winning the Game: 
The first player who puts all his/her cards in hand is going to be the winner. Make a good decision so that you can win the game !

NOTE: Please note that the game assumes valid inputs from the user for the seamless gaming experience.



## Credits
- UNO game rules and concept by group#21

