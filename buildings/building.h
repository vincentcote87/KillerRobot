//Author: Darsh Thanki (001182949)
//Date: March 15, 2019
//This file is a header file for the Building class

#ifndef BUILDING_H
#define BUILDING_H

class Building  {
  float centerX,
        centerZ,
        base,
        width,
        height;
  int hitCount;

  char shape;

  public:
    int buildingID;
    //default constructor
    //Building();
    //Paramaterized Constructor
    Building(char bShape, float bCenterX, float bCenterZ, float bBase, float bWidth, float bHeight, int bHit, int bID);

    //Draw Function which houses the "schematics" for each building
    void Draw();

    void Destroy();

};

#endif
