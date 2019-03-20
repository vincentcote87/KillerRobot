//Author: Zachary Nelson 001196795
//Date: March 19th, 2019
//This is a header file for the robot class, which defines the player character

#ifndef ROBOT_H
#define ROBOT_H

class Robot {
   float centerX, centerZ;

  public:
   Robot();

   void Draw();

  private:
   int Y_Speed;
   float Y_Rot;

};

#endif
