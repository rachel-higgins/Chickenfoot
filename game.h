/*****************************************************************************
File: game.h
Class: Game
Description: This class represents the game of Chicken Foot. It holds all the 
necessary data members and member functions to play the game and provides a 
user interface.
*****************************************************************************/
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "bone.h"
#include "chickenyard.h"
#include "player.h"
#include "field.h"

using namespace std;

const string FORMAT = "---------------------------------------------\n";

class Game
{
public:
   Game(int = 2);
   ~Game();
   void playGame();

private:
   struct Turn
   {
      int pos;
      Turn *next;
   };
   Turn *turn;
   ChickenYard myYard;
   Field field;
   Player *player;
   int playerSize;
   int playGame(Turn *);
   void destroy(Turn *&, int);
   void init();
   void initTurn(int, int, Turn *&);
   void shuffleDeck();
   void displayDeck() const;
   void displayPlayerHand(int) const;
   void displayAllHands() const;
   void displayField() const;
   void displayScores() const;
   bool winner(int &) const;
};

#endif