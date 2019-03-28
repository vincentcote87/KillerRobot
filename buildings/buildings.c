//Author: Darsh Thanki (001182949)
//Date: March 15, 2019
//This file is a test file to visualize a created building.

#define PROGRAM_TITLE "Building Demo for Killer Robots"
#define DISPLAY_INFO "Rect Building Test"

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <cmath>
#include <string.h>  // For spring operations.
#include "building.h" //Include the building class
#include "../block/block.h"
#include "../robot/robot.h"

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

// Some global variables.
// Window IDs, window width and height.
int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

// Building position and rotation speed variables.
float X_Rot   = 0.9f;  // Initially only rotate around X-axix.
float Y_Rot   = 0.0f;  // Later on you can use control keys to change
float X_Speed = 0.0f;  // the rotation.
float Y_Speed = 0.05f;
float Z_Off   =-50.0f;

GLfloat robotRotate = 0.0f;
GLfloat antennaRotate = 0.0f;
GLfloat robot_Center_x = 0.5f;
GLfloat robot_Center_y = 0.0f;
GLfloat robot_Center_z = -30.0f;

GLdouble eye_x = 0.5;
GLdouble eye_y = 0.0;
GLdouble eye_z = -60.0;

int blockID;

//define city specifications
int blockDim = 10.0; //define block dimensions (square)
float streetWidth = 6.0; //define street width
int rowBlocks = 5;
int colBlocks = 5;

//Calculate city size
//City width and length's are the sum of the dimensions of the blocks and streets
const float cityW = (rowBlocks*blockDim) + (streetWidth*(rowBlocks-1));
const float cityH = (colBlocks*blockDim) + (streetWidth*(rowBlocks-1));

const int cityMin_x = 0 - (cityW/2);
const int cityMax_x = (cityW/2);
const int cityMin_z = 0 - (cityH/2);
const int cityMax_z = (cityH/2);

std::vector<Block*> blocks;
std::vector<Building*> buildings;
Robot *robot = new Robot();

//////////////////////////////////////////////////////////
// String rendering routine; leverages on GLUT routine. //
//////////////////////////////////////////////////////////
static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}


void drawGround()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor4f( 0.1f, 0.1f, 0.1f, 1.0f);
    glVertex3f( cityMin_x, 0.0f, cityMin_z );
    glVertex3f( cityMin_x, 0.0f, cityMax_z );
    glVertex3f( cityMax_x, 0.0f, cityMax_z );
    glVertex3f( cityMax_x, 0.0f, cityMin_z );
    glEnd();
    glPopMatrix();

}

void drawDottedLines(GLfloat start_x, GLfloat start_z, GLfloat end_x, GLfloat end_z)
{

    int16_t sixteen_bit_integer = 500;
    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(1, sixteen_bit_integer);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glNormal3f(0.0f,1.0f,0.0f);
    glVertex3f(start_x,0.001,start_z);
    glVertex3f(end_x,0.001,end_z);
    glEnd();
    glPopAttrib();

}

void drawRoadLines()
{
    for (GLint i = cityMin_x; i < cityMax_x+1; i++)
    {
        if(i%blockDim == 0)
            drawDottedLines(i+0.5, cityMin_z+0.5, i+0.5, cityMax_z+0.5);
    }
    for (GLint j = cityMin_z; j < cityMax_z+0.5; j++)
    {
        if(j%blockDim == 0)
            drawDottedLines(cityMin_x+0.5, j+0.5, cityMax_x+0.5, j+0.5);
    }
}

void drawGrass()
{
    glPushMatrix();
    for (GLint i = cityMin_x; i < cityMax_x; i+=3)
    {
        for (GLint j = cityMin_z; j < cityMax_z; j+=3)
        {
                /*
                glBegin(GL_QUADS);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glColor4f( 0.0f, 0.5f, 0.0f, 1.0f);
                glVertex3f( i+(blockDim/2), 0.01f, j+(blockDim/2));
                glVertex3f( i+(blockDim/2), 0.01f, j-(blockDim/2));
                glVertex3f( i-(blockDim/2), 0.01f, j-(blockDim/2));
                glVertex3f( i-(blockDim/2), 0.01f, j+(blockDim/2));
                glEnd();
                */
                blocks.push_back(new Block(i, j, 1));
                blockID++;
        }
    }
    glPopMatrix();
}

void drawCity()
{
/*
    for (int i = 0; i < buildings.size(); i++)
    {
      buildings[i]->Draw();
    }
    */
  drawGround();
  drawRoadLines();
  drawGrass();

}

/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  //glViewport(Window_Width * 0.2, 0, Window_Width*0.8, Window_Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0f,(GLfloat) Window_Width/(GLfloat) Window_Height,0.01f,50.0f);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(eye_x, eye_y, eye_z, robot_Center_x, robot_Center_y, robot_Center_z, 0.0, 15.0, 0.0);

  // Move the object back from the screen.
  glTranslatef(0.0f,0.0f,-cityW);

  // Rotate the calculated amount.
  glRotatef(X_Rot,1.0f,0.0f,0.0f);
  glRotatef(Y_Rot,0.0f,1.0f,0.0f);

  // draw the city
  drawCity();
  robot->Draw();
  glPopMatrix();
  //glViewport(0, 0, Window_Width*0.2, Window_Height);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  //glOrtho(0, Window_Width, 0, Window_Height, -1, 1);
  glColor4f(0.0f,1.0f,0.0f,1.0f);
  glMatrixMode(GL_MODELVIEW);
  glutSwapBuffers();

  X_Rot+=X_Speed;
  Y_Rot+=Y_Speed;

}

////////////////////////////////////////////////////////////
// Callback function called when a normal key is pressed. //
////////////////////////////////////////////////////////////
void CallBackKeyPressed(unsigned char key, int x, int y)
{
   switch (key) {
      case 113: // q
	 // Destroy the window and quit.
	 glutDestroyWindow(Window_ID);
	 exit(1);
	 break; // exit doesn't return, but anyway...
      case 102: // f
	 X_Speed=Y_Speed=0;
	 break;
      case 114: // r
         X_Speed=-X_Speed;
         Y_Speed=-Y_Speed;
      break;
   default:
      printf ("KP: No action for %d.\n", key);
      break;
    }
}

/////////////////////////////////////////////////////////////
// Callback Function called when a special key is pressed. //
/////////////////////////////////////////////////////////////
void CallBackSpecialKeyPressed(int key, int x, int y)
{
   switch (key) {
   case 122: // move the cube into the distance.
      Z_Off -= 0.05f;
      break;
   case 97: // move the cube closer.
      Z_Off += 0.05f;
      break;
   case GLUT_KEY_UP: // decrease x rotation speed;
      X_Speed -= 0.01f;
      break;
   case GLUT_KEY_DOWN: // increase x rotation speed;
      X_Speed += 0.01f;
      break;
   case GLUT_KEY_LEFT: // decrease y rotation speed;
      Y_Speed -= 0.01f;
      break;
   case GLUT_KEY_RIGHT: // increase y rotation speed;
      Y_Speed += 0.01f;
      break;
   default:
      printf ("SKP: No action for %d.\n", key);
      break;
    }
}

///////////////////////////////////////////////////////////////
// Callback routine executed whenever the window is resized. //
//////////////////////////////////////////////////////////////
void CallBackResizeScene(int Width, int Height)
{
   // Let's not core dump, no matter what.
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

void initializeBuildings()
{
    int buildingID = 0;
    for (int i = cityMin_x; i < cityMax_x; i++)
    {
        for (int j = cityMin_z; j < cityMax_z; j++)
        {
            if(i%blockDim != 0 && j%blockDim !=0)
            {
                // chance of a building being created is 74%
                double chanceOfBuilding = ((double) rand() / (RAND_MAX));
                if (chanceOfBuilding > 0.26)
                {
                    float randomHeight = 0.50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5-0.50)));
                    buildings.push_back(new Building('r',i+2.5, j+2.5, 0.0f, 5.0f, randomHeight, 3, buildingID));
                    buildingID +=1;
                }
            }

        }
      }
}

////////////////////////////////////////////////////////
//   Setup your program before passing the control    //
//   to the main OpenGL event loop.                   //
////////////////////////////////////////////////////////
void MyInit(int Width, int Height)
{
  glClearDepth(1.0);
  glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
  glShadeModel(GL_SMOOTH);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

   // Load up the correct perspective matrix; using a callback directly.
   CallBackResizeScene(Width,Height);
   initializeBuildings();
}

///////////////////////////////////////////////////
// main() function.                              //
//   There are general steps in making           //
//   an OpenGL application.                      //
//   Inits OpenGL.                               //
//   Calls our own init function                 //
//   then passes control onto OpenGL.            //
///////////////////////////////////////////////////
int main(int argc, char **argv)
{
   srand(time(0));
   glutInit(&argc, argv);

   // To see OpenGL drawing, take out the GLUT_DOUBLE request.
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // The following is for window creation.
   // Set Window size
   glutInitWindowSize(Window_Width, Window_Height);
   // Create and Open a window with its title.
   Window_ID = glutCreateWindow(PROGRAM_TITLE);

   // Register and install the callback function to do the drawing.
   glutDisplayFunc(&CallBackRenderScene);

   // If there's nothing to do, draw.
   glutIdleFunc(&CallBackRenderScene);

   // It's a good idea to know when our window's resized.
   glutReshapeFunc(&CallBackResizeScene);

   // Register and install the callback function for
   // Some keys and special keys.
   glutKeyboardFunc(&CallBackKeyPressed);
   glutSpecialFunc(&CallBackSpecialKeyPressed);

   // OK, OpenGL's ready to go.  Let's call our own init function.
   MyInit(Window_Width, Window_Height);

   // Print out a bit of help dialog.
   printf("\n%s\n\n", PROGRAM_TITLE);
   printf("Print out some helpful information here.\n");
   printf("When you program, you can also use\n");
   printf("printf to do debugging.\n\n");

   // Above functions represents those you will do to set up your
   // application program.
   // Now pass off control to OpenGL.
   glutMainLoop();
   // Never returns.
   return 1;
}
