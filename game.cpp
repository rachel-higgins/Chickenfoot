/*****************************************************************************
File: game.cpp
Class: Game
*****************************************************************************/
#include "game.h"

// Name: Game class constructor
// Description: Initializes the game by setting the size of the player array, the field, and the yard. Also sets the player pointer to nullptr.
// Input: An integer representing the size of the game.
// Output: None.
Game::Game(int size) : myYard(size), playerSize(size), player(nullptr), field(size) {}

// Name: Game class destructor
// Description: Deletes the player array and sets the player pointer to nullptr. Calls the 'destroy' function to destroy the linked list of turns.
// Input: None.
// Output: None.
Game::~Game()
{
   delete[] player;
   player = nullptr;
   destroy(turn, playerSize);
}

// Name: void Game::destroy(Turn *&src, int range)
// Description: A function to destroy the linked list of turns.
// Input: A reference to a pointer to a Turn object and an integer representing the range.
// Output: None.
void Game::destroy(Turn *&src, int range)
{
   if (range > 0)
   {
      // Recursively call the function to destroy the next turn
      destroy(src->next, range - 1);
      delete src;
      src = nullptr;
   }
}

// Name: void Game::init()
// Description: Initializes the game.
// Input: None.
// Output: None.
void Game::init()
{
   cout << FORMAT;
   displayDeck();
   shuffleDeck();
   // Allocates memory for the player array
   player = new Player[playerSize];
   // Deals new hands to each player
   for (int i = 0; i < playerSize; i++)
   {
      player[i].newHand(myYard);
   }
}

// Name: void Game::initTurn(int i, int players, Turn *&head)
// Description: Initializes the linked list of turns.
// Input: An integer representing the starting position (i), an integer representing the number of players (players), and a reference to a pointer to a Turn object (head).
// Output: None.
void Game::initTurn(int i, int players, Turn *&head)
{
   if (players > 0)
   {
      // Allocates memory for the current turn
      head = new Turn;
      // Sets the position of the current turn
      head->pos = i;
      // Recursively call the function to initialize the next turn
      initTurn(i + 1, players - 1, head->next);
   }
   // Sets the head of the linked list to the 'turn' member of the Game class
   if (players == 0)
   {
      head = this->turn;
   }
}

// Name: void Game::playGame()
// Description: Plays the game.
// Input: None.
// Output: None.
void Game::playGame()
{
   int winnerPos = 0;

   // Initializes the game
   init();
   // Initializes the linked list of turns
   initTurn(0, playerSize, this->turn);
   displayAllHands();
   cout << FORMAT;
   // Calls insert to initialize the first double in the field
   field.insert(myYard, player, turn->pos);
   cout << FORMAT;
   displayField();
   displayScores();
   cout << FORMAT;
   // Calls the 'playGame' function to play the game and gets the winner position
   winnerPos = playGame(this->turn);

   if (winnerPos < 0) // If no winners by the time the deck runs out of bones
   {
      // Displays the hands of all players
      for (int i = 0; i < playerSize; i++)
      {
         displayPlayerHand(i);
      }
      cout << FORMAT;
      cout << "End of Game. Sorry, No winners this round!\n";
   }
   else // Displays the winning player
   {
      cout << "Player " << winnerPos + 1 << " is the winner!!\n";
   }
   field.displayField();
   cout << endl;
}

// Name: int Game::playGame(Turn *turn)
// Description: The function implements the main game loop. It allows players to take turns playing their cards and checking if a winner has been determined.
// Input: A pointer to a Turn object that contains information about the current player's turn.
// Output: An integer representing the winning player's position, or -100 if the game has ended with a draw.
int Game::playGame(Turn *turn)
{
   int pos = 0;

   if (field.insert(myYard, player, turn->pos))
   {
      cout << FORMAT << FORMAT;
      field.displayCurrDouble();
      cout << FORMAT;
      for (int i = 0; i < playerSize; i++)
         displayPlayerHand(i);
      cout << FORMAT;
   }
   else
   {
      cout << "Player " << turn->pos + 1 << " is drawing a new card... " << endl;
      if (!player[turn->pos].draw(myYard))
      {
         cout << FORMAT;
         return -100;
      }
   }

   if (winner(pos))
      return pos;

   myYard.shuffle();
   return playGame(turn->next);
}

// Name: void Game::shuffleDeck()
// Description: Shuffles the deck.
// Input: None.
// Output: None.
void Game::shuffleDeck()
{
   myYard.shuffle();
   cout << FORMAT;
   cout << "Deck after shuffle: " << endl
        << myYard;
   cout << FORMAT;
}

// Name: void Game::displayDeck() const
// Description: Displays the deck.
// Input: None.
// Output: None.
void Game::displayDeck() const
{
   cout << FORMAT;
   cout << "Printing out the deck..." << endl
        << myYard;
   cout << FORMAT;
}

// Name: void Game::displayPlayerHand(int i) const
// Description: This function displays a specific player's hand and score.
// Input: An integer representing the index of the player whose hand and score is to be displayed.
// Output: None, but displays the player's hand and score.
void Game::displayPlayerHand(int i) const
{
   cout << FORMAT;
   cout << "Player " << i + 1 << "'s hand: " << endl
        << player[i] << endl
        << endl;
   cout << "Player " << i + 1 << "'s score: " << player[i].getScore() << endl;
   cout << FORMAT;
}

// Name: void Game::displayAllHands() const
// Description: This function displays the hand and score of all players.
// Input: None.
// Output: None, but displays the hand and score of all players.
void Game::displayAllHands() const
{
   for (int i = 0; i < playerSize; i++)
   {
      cout << FORMAT;
      cout << "Player " << i + 1 << "'s hand after drawing: " << endl;
      cout << player[i] << endl;
      cout << "Player " << i + 1 << "'s score: " << player[i].getScore() << endl;
      cout << FORMAT;
   }
}

// Name: void Game::displayField() const
// Description: This function displays the current state of the field.
// Input: None.
// Output: None, but displays the current state of the field.
void Game::displayField() const
{
   cout << FORMAT;
   field.displayField();
   cout << endl
        << FORMAT;
}

// Name: void Game::displayScores() const
// Description: This function displays the scores of all players.
// Input: None.
// Output: None, but displays the scores of all players.
void Game::displayScores() const
{
   cout << FORMAT;
   for (int i = 0; i < playerSize; i++)
      cout << "Player " << i + 1 << "'s score: " << player[i].getScore() << endl;
   cout << FORMAT;
}

// Name: bool Game::winner(int &pos) const
// Description: This function checks if there is a winner, i.e., if a player has a score of 0.
// Input: An integer reference, pos, that will hold the position of the winning player.
// Output: Returns a boolean indicating if there is a winner or not, and the position of the winning player is stored in the input parameter, pos.
bool Game::winner(int &pos) const
{
   int score;
   for (int i = 0; i < playerSize; i++)
   {
      score = player[i].getScore();
      if (score == 0)
      {
         pos = i;
         return true;
      }
   }
   return false;
}