/*****************************************************************************
File: main.cpp
Description: This program simulates the game of Chicken Foot Dominoes. It 
uses classes Player, Bone, and ChickenYard to create a game where a player 
can draw bonesfrom a chickenyard, play bones from their hand, and keep 
track of their score.
 *****************************************************************************/
#include <iostream>
#include "game.h"

using namespace std;

int main()
{
   cout << "CS 261 - Assignment 02 - Rachel Higgins\n\n";
   Game myGame;
   myGame.playGame();
   return 0;
}
