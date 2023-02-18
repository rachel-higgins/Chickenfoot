/*****************************************************************************
File: bone.cpp
Class: Bone
*****************************************************************************/
#include "bone.h"

// name: Bone::Bone()
// description: default constructor that initializes the values val1 and val2 to 0
// input: none
// output: none
Bone::Bone() : played(false)
{
   val1 = 0;
   val2 = 0;
}

// name: Bone::Bone(int val1, int val2)
// description: constructor that initializes the values val1 and val2 to the input parameters
// input: val1 (int), val2 (int)
// output: none
Bone::Bone(int val1, int val2) : played(false)
{
   this->val1 = val1;
   this->val2 = val2;
}

// name: Bone::Bone(const Bone &aBone)
// description: copy constructor that initializes the values val1 and val2 to the values of the input Bone object
// input: aBone (const Bone &)
// output: none
Bone::Bone(const Bone &aBone)
{
   val1 = aBone.val1;
   val2 = aBone.val2;
}

// name: const Bone &Bone::operator=(const Bone &boneSrc)
// description: assignment operator that assigns the values of the input Bone object to the current object
// input: boneSrc (const Bone &)
// output: *this (const Bone &)
const Bone &Bone::operator=(const Bone &boneSrc)
{
   val1 = boneSrc.val1;
   val2 = boneSrc.val2;
   return *this;
}

// name: const bool Bone::operator>(const Bone &boneSrc)
// description: overload of the ">" operator that compares two Bone objects and returns true if the current Bone object is greater than the input Bone object
// input: boneSrc (const Bone &)
// output: true if the current Bone object is greater than the input Bone object, false otherwise (bool)
const bool Bone::operator>(const Bone &boneSrc)
{
   if (!isDouble() || !boneSrc.isDouble())
   {
      cerr << "Error! Cannot compare non-doubles." << endl;
      return false;
   }
   return val1 > boneSrc.val1;
}

// name: const bool Bone::operator<(const Bone &boneSrc)
// description: overload of the "<" operator that compares two Bone objects and returns true if the current Bone object is less than the input Bone object
// input: boneSrc (const Bone &)
// output: true if the current Bone object is less than the input Bone object, false otherwise (bool)
const bool Bone::operator<(const Bone &boneSrc)
{
   if (!isDouble() || !boneSrc.isDouble())
   {
      cerr << "Error! Cannot compare non-doubles." << endl;
      return false;
   }
   return val1 < boneSrc.val1;
}

// name: ostream &operator<<(ostream &out, const Bone &aBone)
// description: overload of the output stream operator that allows Bone objects to be printed
// input: out (ostream &), aBone (const Bone &)
// output: out (ostream &)
ostream &operator<<(ostream &out, const Bone &aBone)
{
   out << "[" << aBone.val1 << "|" << aBone.val2 << "]";
   return out;
}

// name: int Bone::getVal1() const
// description: returns the value of val1
// input: none
// output: val1 (int)
int Bone::getVal1() const
{
   return val1;
}

// name: int Bone::getVal2() const
// description: returns the value of val2
// input: none
// output: val2 (int)
int Bone::getVal2() const
{
   return val2;
}

// name: void Bone::setValues(int val1, int val2, bool played)
// description: sets the values of val1, val2, and played to the input parameters
// input: val1 (int), val2 (int), played (bool)
// output: none
void Bone::setValues(int val1, int val2, bool played)
{
   this->val1 = val1;
   this->val2 = val2;
   this->played = played;
}

// name: void Bone::setVal1(int val1)
// description: sets the value of val1 to the input parameter
// input: val1 (int)
// output: none
void Bone::setVal1(int val1)
{
   this->val1 = val1;
}

// name: void Bone::setVal2(int val2)
// description: sets the value of val2 to the input parameter
// input: val2 (int)
// output: none
void Bone::setVal2(int val2)
{
   this->val2 = val2;
}

// name: void Bone::setPlayed(bool played)
// description: sets the value of played to the input parameter
// input: played (bool)
// output: none
void Bone::setPlayed(bool played)
{
   this->played = played;
}

// name: bool Bone::isPlayed() const
// description: returns the value of the member variable played
// input: none
// output: played (bool)
bool Bone::isPlayed() const
{
   return played;
}

// name: int Bone::getLargerNum() const
// description: returns the larger of the two values val1 and val2
// input: none
// output: larger value (int)
int Bone::getLargerNum() const
{
   if (val1 > val2)
      return val1;
   return val2;
}

// name: int Bone::getSmallerNum() const
// description: returns the smaller of the two values val1 and val2
// input: none
// output: smaller value (int)
int Bone::getSmallerNum() const
{
   if (val1 < val2)
      return val1;
   return val2;
}

// name: bool Bone::isDouble() const
// description: checks if val1 and val2 are equal
// input: none
// output: true if val1 and val2 are equal, false otherwise (bool)
bool Bone::isDouble() const
{
   return (val1 == val2);
}
