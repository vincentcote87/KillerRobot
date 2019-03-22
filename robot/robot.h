//Author: Zachary Nelson 001196795
//Date: March 19th, 2019
//This is a header file for the robot class, which defines the player character

#ifndef ROBOT_H
#define ROBOT_H

#include<stdlib.h>

class Robot {
   float centerX, centerZ;

  public:
   Robot();

   void Draw();
   void MoveForward();
   void Turn(int);
   voidTurnHead(string);
   
  private:
   int direction; //0 for facing -z, 1 for facing -x, 2 for +z, 3 for +x
   int Y_Speed;
   float Y_Rot;

};

#endif
