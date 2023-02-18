/*****************************************************************************
File: player.cpp
Class: Player
*****************************************************************************/
#include "player.h"

// name: Player::Player()
// description: Default constructor, initializes head and tail to nullptr
// input: None
// output: None
Player::Player() : head(nullptr), tail(nullptr) {}

// name: Player::Player(const Player &aPlayer)
// description: Copy constructor
// input: aPlayer
// output: None
Player::Player(const Player &aPlayer) : head(nullptr), tail(nullptr) {}

// name: Player::~Player()
// description: Destructor, calls destroy function to deallocate memory
// input: None
// output: None
Player::~Player()
{
   destroy(head);
}

// name: Player::destroy(Node *&head)
// description: Recursively deallocates memory of linked list
// input: head (pointer to first node of list)
// output: None
void Player::destroy(Node *&head)
{
   while (head)
   {
      destroy(head->next);
      delete head;
      head = nullptr;
   }
}

// name: Player::operator=(const Player &playerSrc)
// description: Assignment operator overload
// input: playerSrc
// output: None
const Player &Player::operator=(const Player &playerSrc)
{
   if (this == &playerSrc)
      return *this;
   if (this->head)
      destroy(this->head);
   return *this;
}

// name: operator<<(ostream &out, const Player &srcPlayer)
// description: Overloads the output operator to allow for easy printing of a player's hand
// input: out, srcPlayer
// output: out
ostream &operator<<(ostream &out, const Player &srcPlayer)
{
   Player::Node *curr = srcPlayer.head;
   int count = 0;
   for (; curr; curr = curr->next)
   {
      out << "\nBone #" << ++count << ": " << curr->data;
   }
   return out;
}

// name: Player::newHand(ChickenYard &aYard)
// description: Draws new hand from ChickenYard object if player's hand is empty
// input: aYard (reference to ChickenYard object)
// output: None
void Player::newHand(ChickenYard &aYard)
{
   if (!head)
   {
      draw(aYard, INIT_CAP);
   }
}

// name: Player::draw(ChickenYard &aYard)
// description: Draws one card from ChickenYard object
// input: aYard (reference to ChickenYard object)
// output: None
bool Player::draw(ChickenYard &aYard)
{
   return draw(aYard, 1);
}

// name: Player::draw(ChickenYard &aYard, int size)
// description: Draws specified number of cards from ChickenYard object
// input: aYard (reference to ChickenYard object), size (number of cards to draw)
// output: None
bool Player::draw(ChickenYard &aYard, int size)
{
   if (size > 0)
   {
      int num1 = 0;
      int num2 = 0;
      if (aYard.deal(num1, num2))
      {
         Node *drawnCard = new Node(num1, num2);
         if (!head && !tail)
         {
            head = drawnCard;
            tail = drawnCard;
         }
         tail->next = drawnCard;
         tail = drawnCard;
         size--;
         draw(aYard, size);
         return true;
      }
   }
   return false;
}

// name: Player::playCard(int i)
// description: Removes and returns the ith card in the player's hand
// input: i (index of card to be played)
// output: pointer to played Bone object
Bone Player::playCard(int i)
{
   Bone playedCard;
   if (!head)
   {
      cout << "Error: Deck is empty" << endl;
      return playedCard;
   }

   Node *prev = nullptr;
   Node *curr = head;
   int count = 0;
   while (curr && count < i)
   {
      prev = curr;
      curr = curr->next;
      count++;
   }

   if (!curr)
   {
      cout << "Not a valid card!" << endl;
      return playedCard;
   }

   playedCard = curr->data;
   playedCard.setPlayed(true);
   if (prev)
      prev->next = curr->next;
   else
      head = curr->next;
   if (!curr->next)
      tail = prev;
   delete curr;
   curr = nullptr;
   return playedCard;
}

// name: Player::getScore()
// description: Returns the total score of the player's hand
// input: None
// output: integer value of total score
int Player::getScore()
{
   return getScore(head);
}

// name: Player::getScore(Node *head) const
// description: Recursive helper function to calculate total score of player's hand
// input: head (pointer to first node of player's hand)
// output: integer value of total score
int Player::getScore(const Node *head) const
{
   if (head)
   {
      return head->data.getVal1() + head->data.getVal2() + getScore(head->next);
   }
   return 0;
}

// description: This function finds the highest double in the player's hand.
// input: aBone - The bone to compare to the player's bones
// count - The number of the bone found
// output: flag - Returns true if a double was found, false otherwise.
bool Player::findHighestDouble(Bone &aBone, int &count) const
{
   bool flag = false;
   int index = 0;
   for (Node *curr = head; curr; curr = curr->next)
   {
      if (curr->data.isDouble() && curr->data > aBone)
      {
         aBone = curr->data;
         count = index;
         flag = true;
      }
      index++;
   }
   return flag;
}

// name: bool Player::find
// description: This function checks if the player's hand contains a specific value.
// input: val - The value to search for in the player's hand
// pos - The position of the bone with the value in the player's hand
// output: Returns true if the value was found in the player's hand, false otherwise.
bool Player::find(int val, int &pos) const
{
   for (Node *curr = head; curr; curr = curr->next)
   {
      if (curr->data.getVal1() == val)
         return true;

      if (curr->data.getVal2() == val)
         return true;
      pos++;
   }
   pos = 0;
   return false;
}