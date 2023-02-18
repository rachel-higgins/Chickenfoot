/*****************************************************************************
File: player.h
Class: Player
Description: This class defines a player object, which has a hand of bones
(i.e. a linked list of Bone objects) and can draw, play, and get the score
of bones. It also overloads the assignment and output operator and has a
destructor to deallocate dynamically allocated memory. This class is a part
of a larger program that simulates the game of Chicken Foot Dominoes.
*****************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H
#include "bone.h"
#include "chickenyard.h"
#include <iostream>
#include <fstream>

const int INIT_CAP = 7;
const int MAX_RANGE = 9;

class Player
{
public:
   Player();
   Player(const Player &);
   ~Player();
   const Player &operator=(const Player &);
   friend ostream &operator<<(ostream &, const Player &);
   void newHand(ChickenYard &);
   bool draw(ChickenYard &);
   Bone playCard(int);
   int getScore();
   bool findHighestDouble(Bone &, int &) const;
   bool find(int, int &) const;

private:
   struct Node
   {
      Node() : next(nullptr) {}
      Node(const Bone aBone) : next(nullptr)
      {
         data = aBone;
      }
      Node(int num1, int num2) : next(nullptr)
      {
         data.setValues(num1, num2);
      }
      Bone data;
      Node *next;
   };
   Node *head;
   Node *tail;
   void destroy(Node *&);
   bool draw(ChickenYard &, int);
   int getScore(const Node *) const;
};

#endif