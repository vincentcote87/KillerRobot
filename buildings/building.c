//Author: Darsh Thanki (001182949)
//Date: March 18, 2019
//This file is a function definition file for the Building class.

#include <stdlib.h>
#include "building.h"

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

/*
Building(): Default constructor that sets basic variables that haven't been defined by the user.
param[\in]: none
param[\out]: none
*/

Building::Building()
{
  width = 5.0;
  height = 20.0;
  base = 0.0;
  hitCount = 1;
}

/*
Building(): Parameterized constructor that sets class variables with values provided by the user.
param[\in]: char  bShape    : Shape of building. Could be rectangle, cylinder or pyramid.
            float bCenterX  : X-Coord Center position of the building relative to the position of the block.
            float bCenterZ  : Z-Coord Center position of the building relative to the position of the block.
            float bBase     : Base of the building. Should be 0 by default.
            float bWidth    : Width of the building.
            float bHeight   : Height of the building.
            int   bHit      : Number of times a user must click the building to destroy it.
param[\out]: none
*/
Building::Building(char bShape, float bCenterX, float bCenterZ, float bBase, float bWidth, float bHeight, int bHit)
{
  shape = bShape;
  width = bWidth;
  height = bHeight;
  base = bBase; //Should be 0 by default but providing flexibility
  centerX = bCenterX;
  centerZ = bCenterZ;
  hitCount = bHit;
}

/*
Draw(): Draw the building. Uses if-elseif-else statement to define the construction of the building.
        The function has a predefined "template" to construct the buildings.
        This includes rectangles, cylinders, and pyramids.
param[\in]: none
param[\out]: none
*/
void Building::Draw()
{
  if (shape == 'r')
  {
    glBegin(GL_QUADS);
    //bottom face
    glNormal3f( 0.0f, 0.0f,base);
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f(centerX-(width/2),base, centerZ-(width/2));
    glVertex3f(centerX+(width/2),base, centerZ-(width/2));
    glVertex3f(centerX+(width/2),base, centerZ+(width/2));
    glVertex3f(centerX-(width/2),base, centerZ+(width/2));

    //top face
    glNormal3f( 0.0f, 0.0f,base+height);
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f( centerX-(width/2), base+height, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base+height, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base+height, centerZ+(width/2));
    glVertex3f( centerX-(width/2), base+height, centerZ+(width/2));

    //Right face
    glNormal3f(centerX+(width/2), 0.0f, 0.0f);
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f( centerX+(width/2), base, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base+height, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base+height, centerZ+(width/2));
    glVertex3f( centerX+(width/2), base, centerZ+(width/2));

    //front face
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f(centerX-(width/2), base, centerZ+(width/2));
    glVertex3f( centerX+(width/2), base, centerZ+(width/2));
    glVertex3f( centerX+(width/2), base+height, centerZ+(width/2));
    glVertex3f(centerX-(width/2), base+height, centerZ+(width/2));

    //far face
    glNormal3f( 0.0f, 0.0f,centerZ-(width/2));
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f(centerX-(width/2), base, centerZ-(width/2));
    glVertex3f(centerX-(width/2), base+height, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base+height, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base, centerZ-(width/2));

    //left face
    glNormal3f(centerX-(width/2), 0.0f, 0.0f);
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f(centerX-(width/2), base+height, centerZ-(width/2));
    glVertex3f(centerX-(width/2), base+height, centerZ+(width/2));
    glVertex3f(centerX-(width/2), base, centerZ+(width/2));
    glVertex3f(centerX-(width/2), base, centerZ-(width/2));
    glEnd();
  }else if(shape == 'p'){
  //Add cylinder construction code here
    glBegin( GL_TRIANGLES );
    glColor4f(0.2,0.9,0.2,.5);
    glVertex3f( centerX, height, centerZ );
    glVertex3f( centerX-(width/2), base, centerZ+(width/2) );
    glVertex3f( centerX+(width/2), base, centerZ+(width/2));

    glColor4f(0.2,0.9,0.2,.5);
    glVertex3f( centerX, height, centerZ);
    glVertex3f( centerX-(width/2), base, centerZ+(width/2));
    glVertex3f( centerX-(width/2), base, centerZ-(width/2));

    glColor4f(0.2,0.9,0.2,.5);
    glVertex3f( centerX, height, centerZ);
    glVertex3f( centerX-(width/2), base, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base, centerZ+(width/2));

    glColor4f(0.2,0.9,0.2,.5);
    glVertex3f( centerX-(width/2), base, centerZ+(width/2));
    glVertex3f( centerX-(width/2), base, centerZ-(width/2));
    glVertex3f( centerX+(width/2), base, centerZ+(width/2));

    glEnd();
  }else{
    // Enter cylinder code here.
  }
}

/*
Destroy(): Destroy the building if click count has been met. This function pushes
           the building underneath the base to hide it.
param[\in]: none
param[\out]: none
*/
void Building::Destroy()
{
  if(hitCount == 0){
    base -= 100+height;
    hitCount--; //Simply redraw the building in the opposite direction. Essentially hiding the building.
  }else{
    hitCount--;
  }
}
