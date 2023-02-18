/*****************************************************************************
File: field.h
Class: Field
Description: The class represents a field of bones in a game of Dominoes. It provides functionality to display the field, insert bones into the field, and determine if the field is complete.
*****************************************************************************/
#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <vector>
#include "bone.h"
#include "player.h"

class Field
{
public:
   Field(int);
   ~Field();
   void displayField() const;
   void displayCurrDouble() const;
   bool insert(ChickenYard &, Player *&, int turn);

private:
   struct Node
   {
      Node() : front(nullptr), back(nullptr), left(nullptr), right(nullptr) {}
      Node(Bone srcBone) : front(nullptr), back(nullptr), left(nullptr), right(nullptr)
      {
         data = srcBone;
      }
      Bone data;
      Node *left;
      Node *right;
      Node *front;
      Node *back;
      bool complete = false;
   };
   vector<Node *> board;
   int playerRange;
   int size;
   int currNodePos;
   void destroy(Node *&);
   void displayField(Node *, string) const;
   bool init_board(ChickenYard &, Player *&);
   bool init_freeSide(ChickenYard &, Player *&, int);
   bool completedFootInsert(ChickenYard &, Player *&, Node *&, int);
   bool findHighestDouble(int &, int &, Player *);
   Bone reorderValues(Bone, int);
};

#endif