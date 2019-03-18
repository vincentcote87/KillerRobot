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

Building::Building()
{
  width = 5.0;
  height = 20.0;
  base = 0.0;
  hitCount = 1;
}

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

void Building::Draw()
{
  if (shape == 'r')
  {
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
    glVertex3f( width/2, base, centerZ+(width/2));
    glVertex3f( width/2, base+height, centerZ+(width/2));
    glVertex3f(centerX-(width/2), base+height, centerZ+(width/2));

    //far face
    glNormal3f( 0.0f, 0.0f,centerZ-(width/2));
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f(centerX-(width/2), base, centerZ-(width/2));
    glVertex3f(centerX-(width/2), base+height, centerZ-(width/2));
    glVertex3f( width/2, base+height, centerZ-(width/2));
    glVertex3f( width/2, base, centerZ-(width/2));

    //left face
    glNormal3f(centerX-(width/2), 0.0f, 0.0f);
    glColor4f(0.2,0.9,0.2,.5);

    glVertex3f(centerX-(width/2), base+height, centerZ-(width/2));
    glVertex3f(centerX-(width/2), base+height, centerZ+(width/2));
    glVertex3f(centerX-(width/2), base, centerZ+(width/2));
    glVertex3f(centerX-(width/2), base, centerZ-(width/2));
  }else if(shape == 'c'){
  //Add cylinder construction code here
  }else{
  //Add pyramid construction code here.
  }
}

void Building::Destroy()
{
  base -= height; //Simply redraw the building in the opposite direction. Essentially hiding the building.
}
