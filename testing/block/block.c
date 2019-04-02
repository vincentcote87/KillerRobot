//Author: Darsh Thanki (001182949)
//Date: March 18, 2019
//This file is a function definition file for the Building class.

#include <stdlib.h>
#include "block.h"
#include "../buildings/building.h"

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

int buildingID = 1;

Block::Block(){
  width = 20.0;
};

Block::Block(float blCenterX, float blCenterZ, int blID)
{
  centerX = blCenterX;
  centerZ = blCenterZ;
  blockID = blID;
  width = 20.0;
}

void Block::Draw()
{
  glBegin(GL_QUADS);
  //Grass
  glNormal3f(0.0f, 0.0f, 0.0f);
  glColor4f(0.2,0.9,0.2,.5);

  glVertex3f(centerX-(width/2),0.0f, centerZ-(width/2));
  glVertex3f(centerX+(width/2),0.0f, centerZ-(width/2));
  glVertex3f(centerX+(width/2),0.0f, centerZ+(width/2));
  glVertex3f(centerX-(width/2),0.0f, centerZ+(width/2));

  glEnd();

  switch (blockID) {
    case 1:
      buildings.push_back(new Building('r',centerX-5.0f, centerZ+5.0f, 0.0f, 5.0f, 20, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX-5.0f, centerZ-5.0f, 0.0f, 5.0f, 40, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('r',centerX+5.0f, centerZ+5.0f, 0.0f, 5.0f, 15, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX+5.0f, centerZ-5.0f, 0.0f, 5.0f, 30, 3, buildingID));
      buildingID++;
      break;
    case 2:
      buildings.push_back(new Building('r',centerX-5.0f, centerZ+5.0f, 0.0f, 5.0f, 21, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('r',centerX-5.0f, centerZ-5.0f, 0.0f, 5.0f, 32, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('r',centerX+5.0f, centerZ+5.0f, 0.0f, 5.0f, 16, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX+5.0f, centerZ-5.0f, 0.0f, 5.0f, 25, 3, buildingID));
      buildingID++;
      break;
    case 3:
      buildings.push_back(new Building('p',centerX-5.0f, centerZ+5.0f, 0.0f, 5.0f, 30, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX-5.0f, centerZ-5.0f, 0.0f, 5.0f, 25, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX+5.0f, centerZ+5.0f, 0.0f, 5.0f, 20, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('r',centerX+5.0f, centerZ-5.0f, 0.0f, 5.0f, 15, 3, buildingID));
      buildingID++;
      break;
    case 4:
      buildings.push_back(new Building('p',centerX-5.0f, centerZ+5.0f, 0.0f, 5.0f, 20, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('r',centerX-5.0f, centerZ-5.0f, 0.0f, 5.0f, 15, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX+5.0f, centerZ+5.0f, 0.0f, 5.0f, 20, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('r',centerX+5.0f, centerZ-5.0f, 0.0f, 5.0f, 15, 3, buildingID));
      buildingID++;
      break;
    case 5:
      buildings.push_back(new Building('p',centerX-5.0f, centerZ+5.0f, 0.0f, 5.0f, 30, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX-5.0f, centerZ-5.0f, 0.0f, 5.0f, 35, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX+5.0f, centerZ+5.0f, 0.0f, 5.0f, 20, 3, buildingID));
      buildingID++;
      buildings.push_back(new Building('p',centerX+5.0f, centerZ-5.0f, 0.0f, 5.0f, 25, 3, buildingID));
      buildingID++;
      break;
    }
    for (int i = 0; i < buildings.size(); i++)
    {
            buildings[i]->Draw();
    }
}
