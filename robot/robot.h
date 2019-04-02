//Author: Zachary Nelson 001196795
//Date: March 19th, 2019
//This is a header file for the robot class, which defines the player character

#ifndef ROBOT_H
#define ROBOT_H

#include<stdlib.h>
#include<string>

class Robot {
   float centerX, centerZ;

  public:
   Robot();

   void Draw();
   void TurnHead(std::string);

  private:
   int Y_Speed;
   float Y_Rot;
   float headRot;
   bool rotateHead;

};

#endif
