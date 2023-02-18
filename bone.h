/*****************************************************************************
File: bones.h
Class: Bone
Description: This class defines a bone object, which has two values and can
be used in a game. It has methods to get the values, get the larger/smaller
value, check if it's a double, and overloads the assignment and output
operator. Thisclass is a part of a larger program that simulates the game of
Chicken Foot Dominoes.
*****************************************************************************/
#ifndef BONES_H
#define BONES_H
#include <iostream>
#include <fstream>

using namespace std;

class Bone
{
public:
   Bone();
   Bone(int, int);
   Bone(const Bone &aBone);
   const Bone &operator=(const Bone &);
   const bool operator>(const Bone &);
   const bool operator<(const Bone &);
   const bool operator==(const Bone &);
   friend ostream &operator<<(ostream &, const Bone &);
   int getVal1() const;
   int getVal2() const;
   void setValues(int, int, bool = false);
   void setVal1(int);
   void setVal2(int);
   void setPlayed(bool);
   bool isPlayed() const;
   int getLargerNum() const;
   int getSmallerNum() const;
   bool isDouble() const;

private:
   int val1;
   int val2;
   bool played;
};

#endif