/*****************************************************************************
File: chickenyard.h
Class: ChickenYard
Description: This class defines a chickenyard object, which represents a
collection of bones (i.e. a 2D array of Bone objects) and can deal,
shuffle, and display the bones. It also has a destructor to deallocate
dynamically allocated memory. This class is a part of a larger program that
simulates the game of Chicken Foot Dominoes.
*****************************************************************************/
#ifndef CHICKENYARD_H
#define CHICKENYARD_H
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include "bone.h"

const int MAX_VAL = 9;
const int INIT_DECK = 45;

class ChickenYard
{
public:
   ChickenYard();
   ChickenYard(int);
   ~ChickenYard();
   friend ostream &operator<<(ostream &, const ChickenYard &);
   bool deal(int &, int &);
   void shuffle();

private:
   struct yard
   {
      yard() : taken(false), init(false) {}
      Bone bone;
      bool taken;
      bool init;
   };
   vector<yard> boneYard;
   int init_size;
   void newYard();
   void destroy();
   int generateSeed();
   void init_bones(int, int, int);
   int calculateIndex(int, int, int) const;
   int isPrimeNumber(int);
};

#endif