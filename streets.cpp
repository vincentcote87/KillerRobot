//vertical lane of the street

#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int start=0;
//Form street
int streetDivTopMost = 0;
int streetDivTop = 0;
int streetDivMdl = 0;
int streetDivBtm = 0;
char s[30];

void renderBitmapString(float x, float y, void *font,const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) 
	{
        glutBitmapCharacter(font, *c);
    }
}
void firstlaneDesign()
{
        //street Background
        glColor3f(0.000, 0.392, 0.000);
        glBegin(GL_POLYGON);
        glVertex2f(0,55);
        glVertex2f(100,55);
        glColor3f(0.604, 0.804, 0.196);
        glVertex2f(100,50-50);
        glVertex2f(0,50-50);
        glEnd();

        //street Design In Front 
        glColor3f(00, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex2f(32-2+21,55);
        glVertex2f(32+58,50-50);
        glVertex2f(32-22,50-50);
        glEnd();
        
        //street Midlle
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLES);
        glVertex2f(32-2+21,55);
        glVertex2f(50+2,50-50);
        glVertex2f(50-2,50-50);
        glEnd();

         //street up
        glColor3f(0.000, 0.749, 1.000);
        glBegin(GL_POLYGON);
        glVertex2f(100,100);
        glVertex2f(0,100);
        glColor3f(0.686, 0.933, 0.933);
        glVertex2f(0,55);
        glVertex2f(100,55);
        glEnd();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(start==1)
	{
        glClearColor(0.000, 0.392, 0.000,1);
    }
    else
	{
        firstlaneDesign();
    }
    glFlush();
    glutSwapBuffers();
}
void processedKeys(unsigned char key, int x, int y) 
{
      switch (key)
            {
                case ' ':
            if(start==0)
			{
                start = 1;
                streetDivTopMost = 0;
                streetDivTop = 0;
                streetDivMdl = 0;
                streetDivBtm = 0;               
            }
             break;
             case 27:
                 exit(0);
             break;
             default:
                break;
        }
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,650);
    glutInitWindowPosition(200,20);
    glutCreateWindow("Street");
    glutDisplayFunc(display);
    glutKeyboardFunc(processedKeys );
    glOrtho(0,100,0,100,-1,1);
    glClearColor(0.184, 0.310, 0.310,1);
    glutMainLoop();
    return 0;
}
