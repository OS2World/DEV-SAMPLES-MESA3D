/*
 * hello.c
 * This is a simple, introductory OpenGL program.
 */
#include <time.h>
#include <stdio.h>
#include "GL\gl.h"
#include "GL\glut.h"

int maininit(int argc, char** argv);
void  GLUTCALLBACK display(void);
void  GLUTCALLBACK Reshape(int width,int height);
static long int T0,T1, raz,razI=100;

void GLUTCALLBACK display(void)
{
   T0 = clock();
for(raz=0;raz<razI;raz++)
  {
/* clear all pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

/* draw white polygon (rectangle) with corners at
 * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
 */
//   glColor3f (1.0, 1.0, 1.0);
   glColor3f (raz * 1.0  /razI, 0.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.1, 0.2, 0.0);
      glVertex3f (0.4, 0.2, 0.0);
      glVertex3f (0.4, 0.3, 0.0);
      glVertex3f (0.2, 0.3, 0.0);
   glEnd();
   glColor3f (0.0, raz * 1.0  /razI, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.5, 0.2, 0.0);
      glVertex3f (0.7, 0.2, 0.0);
      glVertex3f (0.7, 0.6, 0.0);
      glVertex3f (0.5, 0.6, 0.0);
   glEnd();
   glColor3f (raz * .5  /razI, 0.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.2, 0.7, 0.0);
      glVertex3f (0.7, 0.7, 0.0);
      glVertex3f (0.7, 0.9, 0.0);
      glVertex3f (0.2, 0.9, 0.0);
   glEnd();

/* don't wait!
 * start processing buffered OpenGL routines
 */
  glFinish();
  glutSwapBuffers();
 }
  T1 = clock();
  printf("dT=%i\n",T1-T0);
}


void GLUTCALLBACK Reshape(int width, int height)
{
}


void init (void)
{
/* select clearing color       */
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/*
 * Declare initial window size, position, and display mode
 * (single buffer and RGBA).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int maininit(int argc, char** argv)
{
   glutInit(&argc, argv);
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

   glutInitWindowSize (256, 256);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   init ();

   glutReshapeFunc (Reshape);
//   glutKeyboardFunc (keyboard);
   glutDisplayFunc (display);

   return 0;   /* ANSI C requires main to return int. */
}
