//Author: Darsh Thanki (001182949)
//Date: March 15, 2019
//This file is a test file to visualize a city grid.

#define PROGRAM_TITLE "City Grid for Killer Robots"
#define DISPLAY_INFO "Test to show procedural generation of city blocks."

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <vector>
#include "../buildings/building.h"
#include "../block/block.h"
#include <cmath>
#include <ctime>
#include <stdint.h>

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
float Z_Off   =-20.0f;

//define city specifications
int blockDim = 5; //define block dimensions (square)
float streetWidth = 4.0; //define street width
int numBlocks = 20;
int rowBlocks = 20;
int colBlocks = 20;
int RenderMode = GL_RENDER;

//Calculate city size
//City width and length's are the sum of the dimensions of the blocks and streets
float cityW = (rowBlocks*blockDim) + (streetWidth*(rowBlocks-1));
float cityH = (colBlocks*blockDim) + (streetWidth*(rowBlocks-1));

int cityMin_x = 0 - (cityW/2);
int cityMax_x = cityW/2;
int cityMin_z = 0 - (cityH/2);
int cityMax_z = cityH/2;

std::vector<Building*> buildings;

Block a(50.0, 50.0, 1);

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
    glVertex3f( cityMin_x, 0.0f, cityMax_z+1 );
    glVertex3f( cityMax_x+1, 0.0f, cityMax_z+1 );
    glVertex3f( cityMax_x+1, 0.0f, cityMin_z );
    glEnd();
    glPopMatrix();

}

////////////////////////////////////////////////////////
//   Draw Grass.    //
////////////////////////////////////////////////////////

void drawGrass()
{
    glPushMatrix();
    for (GLint i = cityMin_x; i < cityMax_x; i++)
    {
        for (GLint j = cityMin_z; j < cityMin_z; j++)
        {
            if(i%blockDim != 0 && j%blockDim !=0)
                glBegin(GL_QUADS);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glColor4f( 0.0f, 0.5f, 0.0f, 1.0f);
                glVertex3f( i+0.9+0.5, 0.01f, j+0.1-0.5);
                glVertex3f( i+0.1-0.5, 0.01f, j+0.1-0.5);
                glVertex3f( i+0.1-0.5, 0.01f, j+0.9+0.5);
                glVertex3f( i+0.9+0.5, 0.01f, j+0.9+0.5);
                glEnd();
        }
    }
    glPopMatrix();
}

void drawCity()
{
    if (RenderMode == GL_SELECT)
    {
        glInitNames();
        glPushName(-1);
    }
    for (GLuint i = 0; i < buildings.size(); i++)
    {
            if (RenderMode == GL_SELECT)
            {
                glLoadName(buildings[i]->buildingID);
            }
            buildings[i]->Draw();
    }
    if (RenderMode == GL_RENDER)
    {
        drawGround();
        drawGrass();
    }
}


/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
   char buf[80]; // For our strings.

   // Need to manipulate the ModelView matrix to move our model around.
   glMatrixMode(GL_MODELVIEW);

   // Reset to 0,0,0; no rotation, no scaling.
   glLoadIdentity();

   // Move the object back from the screen.
   glTranslatef(0.0f,0.0f,-cityW);

   // Rotate the calculated amount.
   glRotatef(X_Rot,1.0f,0.0f,0.0f);
   glRotatef(Y_Rot,0.0f,1.0f,0.0f);

   // Clear the color and depth buffers.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // OK, let's start drawing our planer quads.
   //glBegin(GL_QUADS);

   //city base
/*
   glNormal3f( 0.0f, 0.0f,0.0f);
   glColor4f(0.0,0.0,0.0,1);

   glVertex3f(-(cityW/2),0.0f,-(cityW/2));
   glVertex3f(cityW/2,0.0f,-(cityW/2));
   glVertex3f(cityW/2,0.0f,cityW/2);
   glVertex3f(-(cityW/2),0.0f,cityW/2);
*/
    a.Draw();
   //drawCity();
   /*
   for(int i = 0; i < rowBlocks; i++){

     for(int j = 0; j < colBlocks; j++){

     }


     glNormal3f( 0.0f, 0.0f,0.01f);
     glColor4f(0.2,0.9,0.2,.5);

     glVertex3f(startPosX,0.10f,startPosZ);
     glVertex3f(startPosX+blockDim,0.10f,startPosZ);
     glVertex3f(startPosX+blockDim,0.10f,startPosZ+blockDim);
     glVertex3f(startPosX,0.10f,startPosZ+blockDim);

     startPosX = startPosX + streetWidth;

   }
   */

   // All polygons have been drawn.
   //glEnd();



   // Move back to the origin
   glLoadIdentity();


   // We need to change the projection matrix for the text rendering.
   glMatrixMode(GL_PROJECTION);

   // But we like our current view too; so we save it here.
   glPushMatrix();

   // Display a string
   // Now we set up a new projection for the text.
   glLoadIdentity();
   glOrtho(0,Window_Width,0,Window_Height,-100.0,100.0);
   glColor4f(0.6,1.0,0.6,1.00);
   sprintf(buf,"%s", DISPLAY_INFO); // Print the string into a buffer
   glRasterPos2i(2,2);                         // Set the coordinate
   PrintString(GLUT_BITMAP_HELVETICA_12, buf);  // Display the string.


   // To ease, simply translate up.  Note we're working in screen
   // pixels in this projection.
   glTranslatef(6.0f, Window_Height - 14, 0.0f);

   // Done with this special projection matrix.  Throw it away.
   glPopMatrix();
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   // We start with GL_DECAL mode.
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);


   // All done drawing.  Let's show it.
   glutSwapBuffers();

   // Now let's do the motion calculations.
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
/*
void initializeBuildings()
{
  int buildingID = 0;
  for (int i = cityMin_x; i < cityMax_x; i++)
  {
    for(int j = cityMin_z; i < cityMax_z; j++)
    {
      if(i%blockDim != 0 && j%blockDim != 0)
      {
        //The probability of a building being created is 70%
        double probBuilding = ((double) rand() / (RAND_MAX));
        if(probBuilding > 0.30)
        {
          float randHeight = 0.50 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(5-0.50)));
          buildings.push_back(new Building('r',i+5.0f, j+5.0f, 0.0f, 5.0f, randHeight, 3, buildingID));
          buildingID += 1;
        }
      }
    }
  }
}
*/

////////////////////////////////////////////////////////
//   Setup your program before passing the control    //
//   to the main OpenGL event loop.                   //
////////////////////////////////////////////////////////
void MyInit(int Width, int Height)
{
   // Color to clear color buffer to.
   glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

   // Depth to clear depth buffer to; type of test.
   glClearDepth(1.0);
   glDepthFunc(GL_LESS);

   // Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
   glShadeModel(GL_SMOOTH);

   RenderMode = GL_RENDER;
   // Load up the correct perspective matrix; using a callback directly.
   CallBackResizeScene(Width,Height);
   //initializeBuildings();
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
