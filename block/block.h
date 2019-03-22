//Author: Darsh Thanki (001182949)
//Date: March 15, 2019
//This file is a header file for the block class.

#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>
#include <vector>
#include <cmath>
#include <ctime>
#include "../buildings/building.h"


class Block  {
  float centerX,
        centerZ,
        width;
  int blockID; //This defines the block version

  public:
    //default constructor
    Block();

    std::vector<Building*> buildings;

    //Parameterized Constructor. We'll use this one.
    Block(float blCenterX, float blCenterZ, int blID);

    //Draw function.
    void Draw();
};

#endif
