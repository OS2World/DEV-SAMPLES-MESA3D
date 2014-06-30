/*
 *  disk.c
 *  This program demonstrates the use of the quadrics
 *  Utility Library routines to draw circles and arcs.
 */
#include "basis.h"

GLint windW, windH;

GLUquadricObj * quadObj;

/*  Clear the screen.  For each triangle, set the current
 *  color and modify the modelview matrix.
 */
void GLUTCALLBACK display(void)
{   int i;
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
    glColor3f (1.0, 1.0, 1.0);
    glTranslatef (10.0, 10.0, 0.0);
    gluDisk (quadObj, 0.0, 5.0, 10, 2);
    glPopMatrix();

    glPushMatrix();
    glColor3f (1.0, 1.0, 0.0);
    glTranslatef (20.0, 20.0, 0.0);
    gluPartialDisk (quadObj, 0.0, 5.0, 10, 3, 30.0, 120.0);
    glPopMatrix();

    glPushMatrix();
    gluQuadricDrawStyle (quadObj, GLU_SILHOUETTE);
    glColor3f (0.0, 1.0, 1.0);
    glTranslatef (30.0, 30.0, 0.0);
    gluPartialDisk (quadObj, 0.0, 5.0, 10, 3, 135.0, 270.0);
    glPopMatrix();

    glPushMatrix();
    gluQuadricDrawStyle (quadObj, GLU_LINE);
    glColor3f (1.0, 0.0, 1.0);
    glTranslatef (40.0, 40.0, 0.0);
    gluDisk (quadObj, 2.0, 5.0, 10, 10);
    glPopMatrix();
    glFlush();

    for(i=0;i<10;i++)
    {  glPointSize(i+1);
        glBegin(GL_POINTS);
        glVertex2f((GLfloat)i*2,(GLfloat)i*3);
        glEnd();
    }

   glFlush ();
   glutSwapBuffers();
}

void myinit (void) {
    quadObj = gluNewQuadric ();
    glShadeModel(GL_FLAT);
}

void GLUTCALLBACK  myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
       glOrtho (0.0, 50.0,
           0.0, 50.0*(GLfloat)h/(GLfloat)w, -1.0, 1.0);
    else
       glOrtho (0.0, 50.0*(GLfloat)w/(GLfloat)h,
           0.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int maininit(int argc, char** argv)
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB
//    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB
                        | GLUT_ALPHA | GLUT_DEPTH);

    windW = 400;
    windH = 300;
   glutInitWindowSize(windW,windH);
   glutInitWindowPosition(100, 50);

   glutCreateWindow("Disk...");

    myinit ();
   glutReshapeFunc (myReshape);
   glutDisplayFunc (display);

}
