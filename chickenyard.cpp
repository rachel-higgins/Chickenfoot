/*****************************************************************************
File: chickenyard.cpp
Class: ChickenYard
*****************************************************************************/
#include "chickenyard.h"

// name: ChickenYard::ChickenYard()
// description: Default constructor for the ChickenYard class
// input: None
// output: None
ChickenYard::ChickenYard() : init_size(INIT_DECK)
{
   boneYard.resize(init_size);
   newYard();
}

// name: ChickenYard::ChickenYard(int deckSize)
// description: Constructor for the ChickenYard class that takes an integer argument for the deck size
// input: deckSize (int)
// output: None
ChickenYard::ChickenYard(int players) : init_size(INIT_DECK)
{
   if (players <= 3)
      boneYard.resize(init_size);
   else if (players <= 5)
   {
      init_size *= 2;
      boneYard.resize(init_size);
   }
   else if (players <= 7)
   {
      init_size *= 3;
      boneYard.resize(init_size);
   }
   newYard();
}

// name: ChickenYard::~ChickenYard()
// description: Destructor for the ChickenYard class
// input: None
// output: None
ChickenYard::~ChickenYard()
{
   destroy();
}

// name: destroy
// description: This function clears all the bones from the chicken yard
// input: None
// output: None
void ChickenYard::destroy()
{
   boneYard.clear();
}

// name: operator<<
// description: This function is the overload operator "<<", it is used to display the deck.
// input: ostream &out, const ChickenYard &aDeck
// output: ostream & (the output stream)
ostream &operator<<(ostream &out, const ChickenYard &aDeck)
{
   // ChickenYard::yard *aBoneYard = aDeck.boneYard;
   for (long unsigned int i = 0; i < aDeck.boneYard.size(); i++)
   {
      out << "-------------------\n";
      out << "Index #" << i << ": "
          << aDeck.boneYard[i].bone << endl;
   }
   return out;
}

// name: ChickenYard::newGame
// description: This function is used to start a new game by resetting the deck.
// input: none
// output: void (reset the deck)
void ChickenYard::newYard()
{
   int seed = generateSeed();
   mt19937 random_engine(seed);
   int random = uniform_int_distribution<int>(200, 900)(random_engine);
   init_bones(random, 0, MAX_VAL);
   shuffle();
}

// name: ChickenYard::generateSeed()
// description: This function is used to generate a random seed for shuffling the deck.
// input: int deckSize
// output: int (the generated seed)
int ChickenYard::generateSeed()
{
   random_device rd;
   return rd();
}

// name: ChickenYard::init_bones
// description: This function is used to initialize the bones in the deck.
// input: int seed, int count, int maxVal, Node **&aDeck
// output: void (initialize the bones in the deck)
void ChickenYard::init_bones(int seed, int count, int maxVal)
{
   if (maxVal < 0)
      return;
   int i = maxVal;

   for (int j = 0; j <= maxVal && count < boneYard.size(); j++)
   {
      int index = calculateIndex(i, j, seed);
      boneYard[index].bone.setValues(i, j);
      boneYard[index].init = true;
      count++;
   }
   if (maxVal == 0)
      maxVal = MAX_VAL;
   if (count < boneYard.size())
      init_bones(seed, count, maxVal - 1);
}

// name: ChickenYard::deal
// description: This function is used to deal a bone to a player.
// input: Bone *&aBone
// output: void (deal a bone to a player)
bool ChickenYard::deal(int &num1, int &num2)
{
   int currSize = boneYard.size();
   if (currSize > 0)
   {
      num1 = boneYard[currSize - 1].bone.getVal1();
      num2 = boneYard[currSize - 1].bone.getVal2();
      // boneYard[size - 1]->taken = true;
      boneYard.pop_back();
      boneYard.shrink_to_fit();
      // cout << size << " bone(s) left in the deck.\n";
      return true;
   }
   else
   {
      cerr << "Error: Deck is empty" << endl;
   }
   return false;
}

// name: ChickenYard::shuffle
// description: This function is used to shuffle the bones in the deck.
// input: none
// output: void (shuffle the bones in the deck)
void ChickenYard::shuffle()
{
   // create a random number generator
   int seed = generateSeed();
   mt19937 random_engine(seed);

   // iterate through the deck and swap each element with a randomly selected element
   for (int i = 0; i < boneYard.size(); i++)
   {
      int random_index = uniform_int_distribution<int>(i, boneYard.size() - 1)(random_engine);
      yard temp = boneYard[i];
      boneYard[i] = boneYard[random_index];
      boneYard[random_index] = temp;
   }
}

// name: ChickenYard::calculateIndex
// description: This function is used to calculate the index of the bone in the deck.
// input: int key1, int key2, int seed, Node **aDeck
// output: int (the index of the bone in the deck)
int ChickenYard::calculateIndex(int key1, int key2, int seed) const
{
   int hashResults = ((key1 + key2) * seed) % boneYard.size();
   while (boneYard[hashResults].init)
   {
      hashResults = (hashResults + 1) % boneYard.size();
   }
   return hashResults;
}

// name: ChickenYard::isPrimeNumber
// description: This function is used to check if a number is prime.
// input: int num
// output: int (1 if prime, 0 if not prime)
int ChickenYard::isPrimeNumber(int num)
{
   if (num == 1)
      return 0;

   for (int i = 2; i <= sqrt(num); i++)
   {
      if (num % i == 0)
      {
         // not prime
         return 0;
      }
   }
   // prime
   return 1;
}