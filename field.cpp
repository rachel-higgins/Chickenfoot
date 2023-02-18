/*****************************************************************************
File: field.cpp
Class: Field
*****************************************************************************/ 
#include "field.h"

// Name: Field
// Description: Constructor for the Field class
// Input: int range - the range for the player
// Output: None
Field::Field(int range) : size(1), playerRange(range), currNodePos(0)
{
   board.resize(size);
}

// Name: ~Field
// Description: Destructor for the Field class
// Input: None
// Output: None
Field::~Field()
{
   destroy(board[0]);
   board.erase(board.begin(), board.end());
}

// Name: destroy
// Description: Recursive function to delete all nodes in the field
// Input: Node *&curr - a pointer to the current node being deleted
// Output: None
void Field::destroy(Node *&curr)
{
   if (!curr)
      return;

   destroy(curr->left);
   destroy(curr->right);
   destroy(curr->front);
   destroy(curr->back);

   delete curr;
   curr = nullptr;
}

// Name: displayField
// Description: Displays the field by traversing the linked list of nodes and displaying the data of each node
// Input: None
// Output: None
void Field::displayField() const
{
   cout << "\nDisplaying Field: \n";
   if (board[0])
   {
      cout << "\nDOUBLE: " << board[0]->data;
      displayField(board[0]->left, "  LEFT: ");
      cout << "\nDOUBLE: " << board[0]->data;
      displayField(board[0]->front, "  FRONT: ");
      cout << "\nDOUBLE: " << board[0]->data;
      displayField(board[0]->right, "  RIGHT: ");
      cout << "\nDOUBLE: " << board[0]->data;
      if (board[0]->back)
      {
         displayField(board[0]->back, "  BACK: ");
      }
   }
   cout << "\n\nDOUBLE BEING PLAYED: " << board[currNodePos]->data << endl;
}

// Name: displayField
// Description: Displays the field in a specified format.
// Input: Node *curr - pointer to the current node, string direction - the direction to display the current node.
// Output: None (displays the field information on the console)
void Field::displayField(Node *curr, string direction) const
{
   if (curr && curr->data.isDouble())
   {
      // cout << "---> ";
      direction = "---> DOUBLE: ";
   }
   if (curr)
   {
      cout << direction << curr->data << "  ";
      if (curr->front)
         displayField(curr->front, "FRONT: ");
      if (curr->right)
         displayField(curr->right, "RIGHT: ");

      if (curr->left)
         displayField(curr->left, "LEFT: ");
   }
}

// Name: displayCurrDouble
// Description: Displays the current double being played.
// Input: None
// Output: None (displays the current double being played on the console)
void Field::displayCurrDouble() const
{
   cout << "CURRENT DOUBLE BEING PLAYED: " << board[currNodePos]->data << endl;
}

// Name: insert
// Description: Inserts a bone into the board.
// Input: ChickenYard &yard - reference to the Chicken Yard, Player *&player - reference to the player, int turn - the current turn.
// Output: Returns true if the insertion was successful, false otherwise.
bool Field::insert(ChickenYard &yard, Player *&player, int turn)
{
   if (!board[0])
   {
      return init_board(yard, player);
   }

   if (!board[currNodePos]->complete)
   {
      return init_freeSide(yard, player, turn);
   }

   if (board[currNodePos]->complete)
   {
      if (completedFootInsert(yard, player, board[0]->front, turn))
         return true;
      if (completedFootInsert(yard, player, board[0]->left, turn))
         return true;
      if (completedFootInsert(yard, player, board[0]->right, turn))
         return true;
      if (completedFootInsert(yard, player, board[0]->back, turn))
         return true;
   }
   return false;
}

// Name: init_board
// Description: Initializes the board by finding the highest double and starting the game.
// Input: ChickenYard &srcYard - reference to the Chicken Yard, Player *&srcPlayer - reference to the player.
// Output: Returns true if the board was initialized successfully, false otherwise.
bool Field::init_board(ChickenYard &srcYard, Player *&srcPlayer)
{
   int index = 0, playerNum = 0;
   Bone playedCard;
   while (!findHighestDouble(playerNum, index, srcPlayer))
   {
      for (int i = 0; i < playerRange; i++)
      {
         cout << "Player " << i + 1 << " is drawing a new card... " << endl;
         srcPlayer[i].draw(srcYard);
      }
   }
   playedCard = srcPlayer[playerNum].playCard(index);
   board[0] = new Node(playedCard);
   cout << "Player " << playerNum + 1 << " has played the first double: "
        << playedCard << "\n";
   return true;
}

// Name: init_freeSide
// Description: The function initializes the free side of a field.
// Input: ChickenYard srcYard, Player *srcPlayer, int turn
// Output: bool
bool Field::init_freeSide(ChickenYard &srcYard, Player *&srcPlayer, int turn)
{
   int pos = 0;
   int val = board[currNodePos]->data.getVal1();
   if (srcPlayer[turn].find(val, pos))
   {
      Bone playedCard = srcPlayer[turn].playCard(pos);
      playedCard = reorderValues(playedCard, val);
      cout << "Player " << turn + 1 << " has played: " << playedCard << "\n";
      if (currNodePos == 0)
      {
         if (!board[currNodePos]->back)
         {
            board[currNodePos]->back = new Node(playedCard);
            return true;
         }
      }

      if (!board[currNodePos]->left)
      {
         board[currNodePos]->left = new Node(playedCard);
      }
      else if (!board[currNodePos]->front)
      {
         board[currNodePos]->front = new Node(playedCard);
      }
      else if (!board[currNodePos]->right)
      {
         board[currNodePos]->right = new Node(playedCard);
         board[currNodePos]->complete = true;
         size++;
         board.resize(size);
         // board[currNodePos + 1] = new Node;
      }
      return true;
   }
   return false;
}

// Name: completedFootInsert
// Description: The function inserts the completed foot of a field.
// Input: ChickenYard srcYard, Player *srcPlayer, Node *srcBoard, int turn
// Output: bool
bool Field::completedFootInsert(ChickenYard &srcYard, Player *&srcPlayer, Node *&srcBoard, int turn)
{
   if (srcBoard && !srcBoard->left && !srcBoard->right && srcBoard->front)
   {
      return completedFootInsert(srcYard, srcPlayer, srcBoard->front, turn);
   }
   if (srcBoard && srcBoard->left)
   {
      return completedFootInsert(srcYard, srcPlayer, srcBoard->left, turn);
   }
   if (srcBoard && srcBoard->right)
   {
      return completedFootInsert(srcYard, srcPlayer, srcBoard->left, turn);
   }
   if (srcBoard && srcBoard->front)
   {
      return completedFootInsert(srcYard, srcPlayer, srcBoard->front, turn);
   }

   int pos = 0;
   int freeVal = 0;
   int val = srcBoard->data.getVal2();
   if (srcPlayer[turn].find(val, pos) || srcPlayer[turn].find(freeVal, pos))
   {
      Bone playedCard = srcPlayer[turn].playCard(pos);
      playedCard = reorderValues(playedCard, val);
      if (playedCard.isDouble())
      {
         currNodePos++;
         board[currNodePos] = new Node(playedCard);
         srcBoard->front = board[currNodePos];
         cout << "Player " << turn + 1 << " has played: " << playedCard << "\n";
         return true;
      }
      srcBoard->front = new Node(playedCard);
      cout << "Player " << turn + 1 << " has played: " << playedCard << "\n";
      return true;
   }
   else
      return false;
}

// Name: findHighestDouble
// Description: The function finds the highest double card in a set of players.
// Input: int &player, int &index, Player *playerSrc
// Output: bool
bool Field::findHighestDouble(int &player, int &index, Player *playerSrc)
{
   Bone highestDouble;
   Bone temp;
   bool flag = false;
   int i = 0;

   for (int j = 0; j < playerRange; j++)
   {
      if (playerSrc[j].findHighestDouble(temp, i) && temp > highestDouble)
      {
         highestDouble = temp;
         player = j;
         index = i;
         flag = true;
      }
   }
   return flag;
}

// Name: reorderValues
// Description: The function reorders the values of a card.
// Input: Bone aBone, int val
// Output: Bone
Bone Field::reorderValues(Bone aBone, int val)
{
   int val1 = aBone.getVal1();
   int val2 = aBone.getVal2();

   if (val1 == val)
      return aBone;
   if (val1 == 0)
      return aBone;
   if (val2 == 0)
   {
      aBone.setVal1(val2);
      aBone.setVal2(val1);
      return aBone;
   }
   aBone.setVal1(val);
   aBone.setVal2(val1);

   return aBone;
}