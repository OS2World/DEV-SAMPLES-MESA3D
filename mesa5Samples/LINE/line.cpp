/* line.c v 1.0 EK */
/* based on line.c by (c) Silicon Graphics, Inc. */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "basis.h"

#define CI_OFFSET 16


GLenum rgb, doubleBuffer, windType;

GLenum mode1, mode2;
GLint size;
float pntA[3] = {
    -160.0, 0.0, 0.0
};
float pntB[3] = {
    -130.0, 0.0, 0.0
};
float pntC[3] = {
    -40.0, -50.0, 0.0
};
float pntD[3] = {
    30.0, 60.0, 0.0
};


#include "tkmap.c"

static void Init(void)
{
    GLint i;

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glLineStipple(1, 0xF0E0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    if (!rgb) {
       for (i = 0; i < 16; i++) {
           glutSetColor(i+CI_OFFSET, i/15.0, i/15.0, 0.0);
       }
    }

    mode1 = GL_FALSE;
    mode2 = GL_FALSE;
    size = 1;
}

static void GLUTCALLBACK  Reshape(int width, int height)
{

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-175, 175, -175, 175);
    glMatrixMode(GL_MODELVIEW);
}

static void GLUTCALLBACK  Key(unsigned char key, int x, int y)
{
    switch (key) {
      case 27:
       exit(1);
      case '1':
       mode1 = !mode1;
       break;
      case '2':
       mode2 = !mode2;
       break;
      case 'W':
       size++;
       break;
      case 'w':
       size--;
       if (size < 1) {
           size = 1;
       }
       break;
      default:
       return;
    }

    glutPostRedisplay();
}

static void GLUTCALLBACK  Draw(void)
{
    GLint ci, i;

    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(size);

    if (mode1) {
       glEnable(GL_LINE_STIPPLE);
    } else {
       glDisable(GL_LINE_STIPPLE);
    }

    if (mode2) {
       ci = CI_OFFSET;
       glEnable(GL_LINE_SMOOTH);
       glEnable(GL_POINT_SMOOTH);
       glEnable(GL_BLEND);
    } else {
       ci = COLOR_YELLOW;
       glDisable(GL_LINE_SMOOTH);
       glDisable(GL_POINT_SMOOTH);
       glDisable(GL_BLEND);
    }

    glPushMatrix();

    glShadeModel( GL_FLAT );

    for (i = 0; i < 360; i += 5) {
       glRotatef(5.0, 0,0,1);

       (rgb) ? glColor3f(1.0, 1.0, 0.0) : glIndexi(ci);
       glBegin(GL_LINE_STRIP);
           glVertex3fv(pntA);
           glVertex3fv(pntB);
       glEnd();

       glPointSize(1+i/36);

       SetColor(COLOR_GREEN);
       glBegin(GL_POINTS);
           glVertex3fv(pntA);
           glVertex3fv(pntB);
       glEnd();
    }

    glPopMatrix();

    glFlush();

    if (doubleBuffer) {
       glutSwapBuffers();
    }
}

static GLenum Args(int argc, char **argv)
{
    GLint i;

    rgb = GL_TRUE;
    doubleBuffer = GL_TRUE;

    for (i = 1; i < argc; i++) {
       if (strcmp(argv[i], "-ci") == 0) {
           rgb = GL_FALSE;
       } else if (strcmp(argv[i], "-rgb") == 0) {
           rgb = GL_TRUE;
       } else if (strcmp(argv[i], "-sb") == 0) {
           doubleBuffer = GL_FALSE;
       } else if (strcmp(argv[i], "-db") == 0) {
           doubleBuffer = GL_TRUE;
       } else {
           printf("%s (Bad option).\n", argv[i]);
           return GL_FALSE;
       }
    }
    return GL_TRUE;
}

//int main(int argc, char **argv)
int maininit(int argc, char** argv)
{
    printf("Press Esc, 1,2, W or w\n"); fflush(stdout);

    glutInit(&argc, argv);

    if (Args(argc, argv) == GL_FALSE) {
       exit(1);
    }

    glutInitWindowPosition(0, 0); glutInitWindowSize( 300, 300);

    windType = (rgb) ? GLUT_RGB : GLUT_INDEX;
    windType |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(windType);

    if (glutCreateWindow("Line Test") == GL_FALSE) {
       exit(1);
    }

    InitMap();

    Init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutMainLoop();
       return 0;
}
