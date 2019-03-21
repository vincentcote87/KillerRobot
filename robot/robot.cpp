//Author: Zachary Nelson 001196795
//Date: March 19, 2019
//This file is a function definition file for the Robot class.

#include <stdlib.h>
#include <iostream>
#include "robot.h"

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

//Default constructor
Robot::Robot()
{
   centerX = 0.0;
   centerZ = 0.0;
   Y_Speed = 0.0;
   Y_Rot = 0.0;
}

//Draw function, draws the robot to the screen

void Robot::Draw()
{
   Y_Speed += 1;

   glPushMatrix();
   glBegin(GL_QUADS); 

   // Far face
   glNormal3f( 0.0f, 0.0f,-1.0f);
   glColor4f(0.42f,0.42f,0.42f,1.0); 

   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.5f, 0.0f, -1.5f);
   glTexCoord2f(2.995f, 2.995f); glVertex3f(-1.5f,  3.0f, -1.5f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.5f,  3.0f, -1.5f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( 1.5f, 0.0f, -1.5f);

   // Right face
   glNormal3f( 1.0f, 0.0f, 0.0f);
   glColor4f(0.35f,0.35f,0.35f,1.0);

   glTexCoord2f(0.995f, 0.005f); glVertex3f( 1.5f, 0.0f, -1.5f); 
   glTexCoord2f(0.995f, 0.995f); glVertex3f( 1.5f,  3.0f, -1.5f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.5f,  3.0f,  1.5f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( 1.5f, 0.0f,  1.5f);

   // Front face
   glNormal3f( 0.0f, 0.0f, 1.0f);
   glColor4f( 0.42f, 0.42f, 0.42f, 1.0);
   
   glTexCoord2f( 0.005f, 0.005f); glVertex3f(-1.5f, 0.0f,  1.5f);
   glTexCoord2f( 0.995f, 0.005f); glVertex3f( 1.5f, 0.0f,  1.5f);
   glTexCoord2f( 0.995f, 0.995f); glVertex3f( 1.5f,  3.0f,  1.5f); 
   glTexCoord2f( 0.005f, 0.995f); glVertex3f(-1.5f,  3.0f,  1.5f);

   // Left Face
   glNormal3f(-1.0f, 0.0f, 0.0f);  
   glColor4f(0.35,0.35,0.35,1.0);
   
   glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.5f, 0.0f, -1.5f); 
   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.5f, 0.0f,  1.5f);
   glTexCoord2f(0.995f, 0.995f); glVertex3f(-1.5f,  3.0f,  1.5f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.5f,  3.0f, -1.5f);

   // Bottom face
   glNormal3f(0.0f, 1.0f, 0.0f);
   glColor4f(0.15,0.15,0.15,1);

   glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.5f, 0.0f, 1.5f);
   glTexCoord2f(0.995f, 0.005f); glVertex3f( 1.5f, 0.0f, 1.5f);
   glTexCoord2f(0.995f, 0.995f); glVertex3f( 1.5f, 0.0f,-1.5f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.5f, 0.0f,-1.5f);

   // Top Face
   glNormal3f(0.0f, 1.0f, 0.0f);
   glColor4f(0.15,0.15,0.15,1);

   glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.5f, 3.0f, 1.5f);
   glTexCoord2f(0.995f, 0.005f); glVertex3f( 1.5f, 3.0f, 1.5f);
   glTexCoord2f(0.995f, 0.995f); glVertex3f( 1.5f, 3.0f,-1.5f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.5f, 3.0f,-1.5f);

   glEnd();
   glPopMatrix();

   ////////////////////////////////////////////////////
   //Drawing head
      
   glPushMatrix();
   glBegin(GL_QUADS); 

   // Far face
   glNormal3f( 0.0f, 0.0f,-1.0f);
   glColor4f(0.42f,0.42f,0.42f,1.0); 

   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, 3.5f, -1.0f);
   glTexCoord2f(2.995f, 2.995f); glVertex3f(-1.0f,  5.5f, -1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.0f,  5.5f, -1.0f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( 1.0f, 3.5f, -1.0f);

   // Right face
   glNormal3f( 1.0f, 0.0f, 0.0f);
   glColor4f(0.35f,0.35f,0.35f,1.0);

   glTexCoord2f(0.995f, 0.005f); glVertex3f( 1.0f, 3.5f, -1.0f); 
   glTexCoord2f(0.995f, 0.995f); glVertex3f( 1.0f,  5.5f, -1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.0f,  5.5f,  1.0f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( 1.0f, 3.5f,  1.0f);

   // Front face
   glNormal3f( 0.0f, 0.0f, 1.0f);
   glColor4f( 0.42f, 0.42f, 0.42f, 1.0);
   
   glTexCoord2f( 0.005f, 0.005f); glVertex3f(-1.0f, 3.5f,  1.0f);
   glTexCoord2f( 0.995f, 0.005f); glVertex3f( 1.0f, 3.5f,  1.0f);
   glTexCoord2f( 0.995f, 0.995f); glVertex3f( 1.0f,  5.5f,  1.0f); 
   glTexCoord2f( 0.005f, 0.995f); glVertex3f(-1.0f,  5.5f,  1.0f);

   // Left Face
   glNormal3f(-1.0f, 0.0f, 0.0f);  
   glColor4f(0.35,0.35,0.35,1.0);
   
   glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, 3.5f, -1.0f); 
   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, 3.5f,  1.0f);
   glTexCoord2f(0.995f, 0.995f); glVertex3f(-1.0f,  5.5f,  1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f,  5.5f, -1.0f);

   // Bottom face
   glNormal3f(0.0f, 1.0f, 0.0f);
   glColor4f(0.15,0.15,0.15,1);

   glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, 3.5f, 1.0f);
   glTexCoord2f(0.995f, 0.005f); glVertex3f( 1.0f, 3.5f, 1.0f);
   glTexCoord2f(0.995f, 0.995f); glVertex3f( 1.0f, 3.5f,-1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 3.5f,-1.0f);

   // Top Face
   glNormal3f(0.0f, 1.0f, 0.0f);
   glColor4f(0.15,0.15,0.15,1);

   glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, 5.5f, 1.0f);
   glTexCoord2f(0.995f, 0.005f); glVertex3f( 1.0f, 5.5f, 1.0f);
   glTexCoord2f(0.995f, 0.995f); glVertex3f( 1.0f, 5.5f,-1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f, 5.5f,-1.0f);

   glEnd();
   glPopMatrix();

   ///////////////////////////////////////////////////

   //Drawing Neck

   glPushMatrix();

   glColor4f(1.0,1.0,1.0,1);
   GLUquadricObj *p = gluNewQuadric();
   glTranslatef(0.0f, 3.5f, 0.0f);
   glRotatef(90, 1.0f, 0.0f, 0.0f);
   gluCylinder(p, 0.7, 0.7, 0.5, 30, 30);

   glPopMatrix();
   
   ////////////////////////////////////////////////////

   //Drawing Antenna

   glPushMatrix();

   glRotatef(Y_Rot, 0.0f, 1.0f, 0.0f);
   glColor4f(1.0,1.0,1.0,1);
   GLUquadricObj *d = gluNewQuadric();
   glTranslatef(0.0f, 6.5f, 0.3f);
   glRotatef(90, 1.0f, 0.0f, 0.0f);
   gluCylinder(d, 0.2, 0.2, 1.5, 30, 30);

   glPopMatrix();

   ////////////////////////////////////////////////////////////

   //Drawing Eyes

   glPushMatrix();

   glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
   glTranslatef(0.5f, 4.7f, 1.0f);
   glutSolidSphere(0.4, 50, 50);

   glPopMatrix();

   glPushMatrix();
   
   glTranslatef(-0.5f, 4.7f, 1.0f);
   glutSolidSphere(0.4f, 50, 50);

   glPopMatrix();

   ////////////////////////////////////////////////////////////

   //Drawing Front Square

   glPushMatrix();
   glBegin(GL_QUADS);

   glNormal3f( 0.0f, 0.0f,-1.0f);
   glColor4f(0.1f,1.0f,0.0f,1.0); 

   glTexCoord2f( 0.005f, 0.005f); glVertex3f(-1.0f, 0.3f,  1.55f);
   glTexCoord2f( 0.995f, 0.005f); glVertex3f( 1.0f, 0.3f,  1.55f);
   glTexCoord2f( 0.995f, 0.995f); glVertex3f( 1.0f,  2.7f,  1.55f); 
   glTexCoord2f( 0.005f, 0.995f); glVertex3f(-1.0f,  2.7f,  1.55f);

   glEnd();
   glPopMatrix();

   ////////////////////////////////////////////////////////////

   //Drawing back triangles

   glPushMatrix();
   glColor4f(1.0f, 1.0f, 1.0f, 1.0);

   glBegin(GL_TRIANGLES);
   glVertex3f(-1.0f, 0.2f, -1.55f);
   glVertex3f(1.0f, 0.2f, -1.55f);
   glVertex3f(0.0f, 1.5f, -1.55f);

   glVertex3f(-1.0f, 1.5f, -1.55f);
   glVertex3f(1.0f, 1.5f, -1.55f);
   glVertex3f(0.0f, 2.8f, -1.55f);

   glEnd();
   glPopMatrix();


   if(Y_Speed % 5 == 0){
      Y_Rot+=30;
   }

}




   
