#include <stdlib.h>
#include <iostream>
#include "./robot/robot.h"

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

int Y_Rot = 0;

float eye_x = 0.0;
float eye_y = 5.0;
float eye_z = -15.0;
float at_x = 0.0;
float at_y = 3.0;
float at_z = 0.0;

Robot *r = new Robot();

void display(void) {
   // Add display functions here
  
   //Initialization
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   gluLookAt(eye_x,eye_y,eye_z,
             at_x,at_y,at_z,
             0.0,1.0,0.0);

   //Drawing robot here
   r->Draw();
   

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

   gluPerspective(60.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   window_width  = w;
   window_height = h;
   
}

void init(void) {
  // Add init functions here
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y) {
  // Add regular keyboard functions here
  switch (key) {
    case 97: // a
      break;
     case 112: // p
      break;
     case 113: // q
      break;
    case 114: // r
      break;
    case 122: //z
      r->MoveForward();
      break;
    default:
      break;
  }
}

void specialKeyboard(int key, int x, int y) {
  // Add special keyboard functions here
  switch (key) {
    case GLUT_KEY_F1:
      break;
     case GLUT_KEY_F2:
	r->TurnHead("Right");
	break;
     case GLUT_KEY_F3:
	r->TurnHead("Left");
      break;
     case GLUT_KEY_F4:
      break;
    case GLUT_KEY_F5:
      break;
    case GLUT_KEY_F6:
      break;
    case GLUT_KEY_F7:
      break;
    case GLUT_KEY_F8:
      break;
    case GLUT_KEY_F9:
      break;
    case GLUT_KEY_F10:
      break;
    case GLUT_KEY_F11:
      break;
    case GLUT_KEY_F12:
      break;
    default:
      break;
  }
}

void keySpecialUp(int key, int x, int y) {
  // Add special keyboard functions here
  switch (key) {
    case GLUT_KEY_F1:
      break;
     case GLUT_KEY_F2:
	r->TurnHead("");
	break;
     case GLUT_KEY_F3:
	r->TurnHead("");
      break;
     case GLUT_KEY_F4:
      break;
    case GLUT_KEY_F5:
      break;
    case GLUT_KEY_F6:
      break;
    case GLUT_KEY_F7:
      break;
    case GLUT_KEY_F8:
      break;
    case GLUT_KEY_F9:
      break;
    case GLUT_KEY_F10:
      break;
    case GLUT_KEY_F11:
      break;
    case GLUT_KEY_F12:
      break;
    default:
      break;
  }
}

void mouse(int button, int state, int x, int y) {
  // Add mouse functions here
}

int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (window_width, window_height);
  glutInitWindowPosition (window_position_x, window_position_y);
  glutCreateWindow ("Killer Robot");
  init ();
  // glutDisplayFunc(&display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);
  glutSpecialUpFunc(keySpecialUp);
  glutMouseFunc(mouse);
  glutMainLoop();

  return 0;
}
