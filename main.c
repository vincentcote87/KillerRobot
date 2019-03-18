#include <stdlib.h>

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

void display(void) {
  // Add display functions here
}

void reshape(int w, int h) {
  // Add reshape functions here
}

void init(void) {
  // Add init functions here
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
  // Add regular keyboard functions here
}

void specialKeyboard(int key, int x, int y) {
  // Add special keyboard functions here
}

void mouse(int button, int state, int x, int y) {
  // Add mouse functions here
}

int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (window_width, window_height);
  glutInitWindowPosition (window_position_x, window_position_y);
  glutCreateWindow ("Killer Robot");
  init ();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);
  glutMouseFunc(mouse);
  glutMainLoop();

  return 0;
}
