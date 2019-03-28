#include <stdlib.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include "./robot/robot.h"
#include "./buildings/building.h" //Include the building class

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

int window_width = 800;
int window_height = 600;
int window_position_x = 100;
int window_position_y = 100;

const float boundry = 170.0;

int Y_Rot = 0;

float eye_x = 0.0;
float eye_y = 2.5;
float eye_z = -6.0;
float at_x = 0.0;
float at_y = 2.0;
float at_z = 0.0;

float pos_x = 0.0;
float pos_z = 0.0;
float robotAngle = 0.0;
float moveDistance = 1.0;

bool isPaused = false;

//define city specifications
int blockDim = 4; //define block dimensions (square)
float streetWidth = 0.5; //define street width
int rowBlocks = 20; //Need to modify these to val 20.
int colBlocks = 20;

//Calculate city size
//City width and length's are the sum of the dimensions of the blocks and streets
const float cityW = (rowBlocks*blockDim) + (streetWidth*(rowBlocks-1));
const float cityH = (colBlocks*blockDim) + (streetWidth*(rowBlocks-1));

const int cityMin_x = 0 - (cityW/2);
const int cityMax_x = (cityW/2);
const int cityMin_z = 0 - (cityH/2);
const int cityMax_z = (cityH/2);

std::vector<Building*> buildings;
Robot *r = new Robot();

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

void drawDottedLines(float start_x, float start_z, float end_x, float end_z)
{

    int16_t sixteen_bit_integer = 500;
    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(1, sixteen_bit_integer);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glNormal3f(0.0f,1.0f,0.0f);
    glVertex3f(start_x,0.01,start_z);
    glVertex3f(end_x,0.01,end_z);
    glEnd();
    glPopAttrib();

}

void drawRoadLines()
{
    for (GLint i = cityMin_x; i < cityMax_x+1; i++)
    {
        if(i%blockDim == 0)
            drawDottedLines(i+streetWidth, cityMin_z+streetWidth, i+streetWidth, cityMax_z+streetWidth);
    }
    for (GLint j = cityMin_z; j < cityMax_z+streetWidth; j++)
    {
        if(j%blockDim == 0)
            drawDottedLines(cityMin_x+streetWidth, j+streetWidth, cityMax_x+streetWidth, j+streetWidth);
    }
}

void drawGrass()
{
    glPushMatrix();
    for (GLint i = cityMin_x; i < cityMax_x; i++)
    {
        for (GLint j = cityMin_z; j < cityMax_z; j++)
        {
            if(i%blockDim != 0 && j%blockDim !=0)
                glBegin(GL_QUADS);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glColor4f( 0.0f, 0.5f, 0.0f, 1.0f);
                glVertex3f( i+0.9+streetWidth, 0.01f, j+0.1-streetWidth);
                glVertex3f( i+0.1-streetWidth, 0.01f, j+0.1-streetWidth);
                glVertex3f( i+0.1-streetWidth, 0.01f, j+0.9+streetWidth);
                glVertex3f( i+0.9+streetWidth, 0.01f, j+0.9+streetWidth);
                glEnd();
        }
    }
    glPopMatrix();
}

void drawCity()
{

    for (int i = 0; i < buildings.size(); i++)
    {
      buildings[i]->Draw();
    }

  drawGround();
  // glPushMatrix();
  // glScalef(3.0, 3.0, 3.0);
  // glTranslatef(-4.0, 0.0, -4.0);
  // drawRoadLines();
  glPopMatrix();
  drawGrass();

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
                if (chanceOfBuilding > 0.36)
                {
                    float randomHeight = 5 + rand() % 20;
                    int randBuildType = rand() % 2;
                    int hits = -1 + rand() % 5;
                    if (hits == 0){
                      hits = 1;
                    }else if(hits == 2){
                      hits =3;
                    }
                    buildings.push_back(new Building(randBuildType,i+0.1, j+0.1, 0.0f, rand() % 2, randomHeight, hits, buildingID));
                    std::cout << hits << std::endl;
                    buildingID +=1;
                }
            }

        }
      }
}

void display(void) {
   // Add display functions here

   //Initialization
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (robotAngle == 0.0) {
    gluLookAt((eye_x + pos_x),eye_y,eye_z + pos_z,
              at_x + pos_x,at_y,at_z + pos_z,
              0.0,1.0,0.0);
  }
  else if(robotAngle == 90.0) {
    gluLookAt((eye_z + pos_x),eye_y,eye_x + pos_z,
              at_x + pos_x,at_y,at_z + pos_z,
               0.0,1.0,0.0);
  }
  else if(robotAngle == 180.0) {
    gluLookAt(eye_x + pos_x,eye_y,(-eye_z + pos_z),
              at_x + pos_x,at_y,at_z + pos_z,
               0.0,1.0,0.0);
  }
  else {
    gluLookAt((-eye_z + pos_x),eye_y,(eye_x + pos_z),
              at_x + pos_x,at_y,at_z + pos_z,
               0.0,1.0,0.0);
  }

  glPushMatrix();

   glTranslatef(pos_x, 0.0, pos_z);
   glRotatef(robotAngle, 0.0, 1.0, 0.0);
   glScalef(0.25, 0.25, 0.25);

   //Drawing robo here
   r->Draw();
   glPopMatrix();

  glPushMatrix();
  glTranslatef(-2.0, 0.0, -2.0);
  glScalef(4.0, 4.0, 4.0);
  drawCity();
  glPopMatrix();

   //Stuff here so that it will actually show the stuff which has been drawn
   glLoadIdentity();
   glMatrixMode(GL_PROJECTION);

   glutSwapBuffers();
}

void reshape(int w, int h) {
   // Add reshape functions here

   // Let's not core dump, no matter what.
   if (h == 0)
      h = 1;

   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(60.0f,(GLfloat)w/(GLfloat)h, 1.0f, 100.0f);

   glMatrixMode(GL_MODELVIEW);

   window_width  = w;
   window_height = h;

}

void init(void) {
  // Add init functions here
  glClearColor (0.10, 0.0, 0.40, 0.0);
  glEnable(GL_DEPTH_TEST);
  initializeBuildings();
}

void keyboard(unsigned char key, int x, int y) {
  // Add regular keyboard functions here
   if (!isPaused) {
    switch (key) {
    case 97: // a
      // r->Turn(3);
      if (static_cast<int>(pos_x) % 16 == 0.0 && static_cast<int>(pos_z) % 16 == 0) {
        robotAngle += 90.0;
        if (robotAngle >= 360.0)
          robotAngle = 0.0;
      }
      break;
    case 112: // p
      glutDisplayFunc(display);
      glutIdleFunc(NULL);
      isPaused = true;
      break;
    case 113: // q
      if (static_cast<int>(pos_x) % 16 == 0.0 && static_cast<int>(pos_z) % 16 == 0) {
        robotAngle -= 90.0;
        if (robotAngle < 0.0)
          robotAngle = 270.0;
      }
      break;
    case 114: // r
      pos_x = 0.0;
      pos_z = 0.0;
      robotAngle = 0.0;
      break;
    case 122: //z
      // r->MoveForward();
      if (pos_x < boundry && pos_x > -boundry && pos_z < boundry && pos_z > -boundry) {
        if (robotAngle == 270.0) {
          pos_x -= moveDistance;
        } else if (robotAngle == 90.0) {
          pos_x += moveDistance;
        } else if (robotAngle == 0.0) {
          pos_z += moveDistance;
        } else if (robotAngle == 180.0) {
          pos_z -= moveDistance;
        }
      }

      std::cout<<"x = "<<pos_x<<" z = "<<pos_z<<std::endl;
      break;
    default:
      break;
    }
  } else if (key == 112) {
      glutIdleFunc(display);
      isPaused = false;
  }

}

void specialKeyboard(int key, int x, int y) {
  // Add special keyboard functions here
  switch (key) {
    case GLUT_KEY_F1:
      r->TurnHead("Frw");
      break;
    case GLUT_KEY_F2:
      r->TurnHead("Right");
      break;
    case GLUT_KEY_F3:
      r->TurnHead("Left");
      break;
    case GLUT_KEY_F4:
      eye_x = 0.0;
      eye_y = 2.5;
      eye_z = -6.0;
      at_x = 0.0;
      at_y = 2.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F5:
      eye_x = 1.0;
      eye_y = 3.5;
      eye_z = -6.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F6:
      eye_x = -1.0;
      eye_y = 3.5;
      eye_z = -6.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F7:
      eye_x = -1.0;
      eye_y = 3.5;
      eye_z = 6.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F8:
      eye_x = 1.0;
      eye_y = 3.5;
      eye_z = 6.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F9:
      eye_x = 2.0;
      eye_y = 5.0;
      eye_z = -8.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F10:
      eye_x = -2.0;
      eye_y = 5.0;
      eye_z = -8.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F11:
      eye_x = -2.0;
      eye_y = 5.0;
      eye_z = 8.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    case GLUT_KEY_F12:
      eye_x = 2.0;
      eye_y = 5.0;
      eye_z = 8.0;
      at_x = 0.0;
      at_y = 1.0;
      at_z = 0.0;
      break;
    default:
      break;
  }
}

void keySpecialUp(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_F1:
      break;
     case GLUT_KEY_F2:
	r->TurnHead("");
	break;
     case GLUT_KEY_F3:
	r->TurnHead("");
	break;
  }
}

void mouse(int button, int state, int x, int y) {
  // Add mouse functions here
}

int main(int argc, char** argv) {

  srand(time(0));
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (window_width, window_height);
  glutInitWindowPosition (window_position_x, window_position_y);
  glutCreateWindow ("Killer Robot");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);
  glutSpecialUpFunc(keySpecialUp);
  glutMouseFunc(mouse);
  glutMainLoop();

  return 0;
}
