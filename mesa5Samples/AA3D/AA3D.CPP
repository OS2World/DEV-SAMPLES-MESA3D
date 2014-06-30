/*
 *  AA3D.C
 *  This program draws filled polygons with antialiased
 *  edges.  The special GL_SRC_ALPHA_SATURATE blending
 *  function is used.
 *  Pressing the 't' key turns the antialiasing on and off.
 */
#include "basis.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

GLboolean polySmooth = GL_TRUE;
static long int T0,T1, raz,razI=360;


void init(void)
{
    float base, height;
    float aspect, x, y;
    int i;

    float top_y = 1.0;
    float bottom_y = 0.0;
    float top_z = 0.15;
    float bottom_z = 0.69;
    float spacing = 2.5;
    static float lmodel_ambient[] = {0.0, 0.0, 0.0, 0.0};
    static float lmodel_twoside[] = {GL_FALSE};
    static float lmodel_local[] = {GL_FALSE};
    static float light0_ambient[] = {0.1, 0.1, 0.1, 1.0};
    static float light0_diffuse[] = {1.0, 1.0, 1.0, 0.0};
    static float light0_position[] = {0.8660254, 0.5, 1, 0};
    static float light0_specular[] = {1.0, 1.0, 1.0, 0.0};
    static float bevel_mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    static float bevel_mat_shininess[] = {40.0};
    static float bevel_mat_specular[] = {1.0, 1.0, 1.0, 0.0};
    static float bevel_mat_diffuse[] = {1.0, 0.0, 0.0, 0.0};

    base = 2.0;
    height = 2.0;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

   glClearColor(0.5, 0.5, 0.5, 0.0);
   glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
   glEnable(GL_LIGHT0);

   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lmodel_local);
   glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glEnable(GL_LIGHTING);

   glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
   glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
   glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);

   glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, 1.33, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

//   glCullFace (GL_BACK);
//   glEnable (GL_CULL_FACE);
//   glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);
}


int SetMaterial(GLfloat ambr,GLfloat ambg, GLfloat ambb)
{ float mat[4];
  mat[0] = ambr;
  mat[1] = ambg;
  mat[2] = ambb;
  mat[3] = 1.0;
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat);
  mat[0] = 0.8;
  mat[1] = 0.9;
  mat[2] = 0.3;
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat);

}

#define NFACE 6
#define NVERT 8
void drawCube(GLdouble x0, GLdouble x1, GLdouble y0, GLdouble y1,
        GLdouble z0, GLdouble z1)
{
   static GLfloat v[8][3];
   static GLfloat c[8][4] = {
      {0.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 0.95},
      {0.0, 1.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 0.90},
      {0.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 0.80},
      {0.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 0.70}
   };

/*  indices of front, top, left, bottom, right, back faces  */
   static GLubyte indices[NFACE][4] = {
      {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3},
      {0, 1, 5, 4}, {1, 5, 6, 2}, {0, 3, 2, 1}
   };

   v[0][0] = v[3][0] = v[4][0] = v[7][0] = x0;
   v[1][0] = v[2][0] = v[5][0] = v[6][0] = x1;
   v[0][1] = v[1][1] = v[4][1] = v[5][1] = y0;
   v[2][1] = v[3][1] = v[6][1] = v[7][1] = y1;
   v[0][2] = v[1][2] = v[2][2] = v[3][2] = z0;
   v[4][2] = v[5][2] = v[6][2] = v[7][2] = z1;

#ifdef GL_VERSION_1_1
   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);
   glVertexPointer (3, GL_FLOAT, 0, v);
   glColorPointer (4, GL_FLOAT, 0, c);
   glDrawElements (GL_QUADS, NFACE*4, GL_UNSIGNED_BYTE, indices);
   glDisableClientState (GL_VERTEX_ARRAY);
   glDisableClientState (GL_COLOR_ARRAY);
#else
   printf ("If this is GL Version 1.0, ");
   printf ("vertex arrays are not supported.\n");
   exit(1);
#endif
}
void drawCube__(GLdouble x0, GLdouble x1, GLdouble y0, GLdouble y1,
        GLdouble z0, GLdouble z1)
{
   static GLfloat v[8][3];
   static GLfloat c[8][4] = {
      {0.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.},
      {0.0, 1.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 1.},
      {0.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 1.},
      {0.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.}
//      {0.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 0.95},
//      {0.0, 1.0, 0.0, 1.0}, {1.0, 1.0, 0.0, 0.90},
//      {0.0, 0.0, 1.0, 1.0}, {1.0, 0.0, 1.0, 0.80},
//      {0.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 0.70}
   };

/*  indices of front, top, left, bottom, right, back faces  */
   static GLubyte indices[NFACE][4] = {
      {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3},
      {0, 1, 5, 4}, {1, 5, 6, 2}, {0, 3, 2, 1}
   };
   int i,j;
   GLfloat normal[3];

   v[0][0] = v[3][0] = v[4][0] = v[7][0] = x0;
   v[1][0] = v[2][0] = v[5][0] = v[6][0] = x1;
   v[0][1] = v[1][1] = v[4][1] = v[5][1] = y0;
   v[2][1] = v[3][1] = v[6][1] = v[7][1] = y1;
   v[0][2] = v[1][2] = v[2][2] = v[3][2] = z0;
   v[4][2] = v[5][2] = v[6][2] = v[7][2] = z1;
/*
   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);
   glVertexPointer (3, GL_FLOAT, 0, v);
   glColorPointer (4, GL_FLOAT, 0, c);
   glDrawElements (GL_QUADS, NFACE*4, GL_UNSIGNED_BYTE, indices);
   glDisableClientState (GL_VERTEX_ARRAY);
   glDisableClientState (GL_COLOR_ARRAY);
*/
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    gluLookAt(0,0,10, 0,0,0, 0,1,0);

   glColor3f(0.8,0.75,1.);
//   glEnable (GL_COLOR_MATERIAL);
//   SetMaterial(0.3,0.1,0.1);
   glBegin(GL_TRIANGLES);
   normal[0]=normal[1]=0.;
   normal[2] = -1.;
   glNormal3fv(normal);
   glVertex3fv(v[0]);
   glVertex3fv(v[2]);
   glVertex3fv(v[1]);

   glVertex3fv(v[0]);
   glVertex3fv(v[3]);
   glVertex3fv(v[2]);
   normal[2] = 1.;
   glVertex3fv(v[4]);
   glVertex3fv(v[5]);
   glVertex3fv(v[6]);

   glVertex3fv(v[4]);
   glVertex3fv(v[6]);
   glVertex3fv(v[7]);

   normal[1]=normal[2]=0.;
   normal[0] = -1.;
   glVertex3fv(v[0]);
   glVertex3fv(v[4]);
   glVertex3fv(v[3]);

   glVertex3fv(v[3]);
   glVertex3fv(v[4]);
   glVertex3fv(v[7]);
   normal[0] = 1.;
   glVertex3fv(v[1]);
   glVertex3fv(v[2]);
   glVertex3fv(v[5]);

   glVertex3fv(v[2]);
   glVertex3fv(v[6]);
   glVertex3fv(v[5]);

   normal[2]=normal[0]=0.;
   normal[1] = 1.;
   glVertex3fv(v[2]);
   glVertex3fv(v[7]);
   glVertex3fv(v[6]);

   glVertex3fv(v[2]);
   glVertex3fv(v[3]);
   glVertex3fv(v[7]);

   normal[2]=normal[0]=0.;
   normal[1] = -1.;
   glVertex3fv(v[0]);
   glVertex3fv(v[1]);
   glVertex3fv(v[5]);

   glVertex3fv(v[0]);
   glVertex3fv(v[5]);
   glVertex3fv(v[4]);

   glEnd();

}

/*  Note:  polygons must be drawn from front to back
 *  for proper blending.
 */
void GLUTCALLBACK display(void)
{
   T0 = clock();
for(raz=0;raz<=razI;raz++)
  {
   if (polySmooth) {
      glClear (GL_COLOR_BUFFER_BIT);
      glEnable (GL_BLEND);
      glEnable (GL_POLYGON_SMOOTH);
      glDisable (GL_DEPTH_TEST);
   }
   else {
      glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDisable (GL_BLEND);
      glDisable (GL_POLYGON_SMOOTH);
      glEnable (GL_DEPTH_TEST);
   }

   glPushMatrix ();
      glTranslatef (0.0, 0.0, -8.0);
      glRotatef (30.0, 1.0, 0.0, 0.0);
      glRotatef (60.0+raz, 0.0, 1.0, 0.0);
      drawCube(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
   glPopMatrix ();

   glFlush ();

   glutSwapBuffers();

 }
  T1 = clock();
  printf("dT=%i\n",T1-T0);

}

void GLUTCALLBACK reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void GLUTCALLBACK keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 't':
      case 'T':
         polySmooth = !polySmooth;
         if(polySmooth)  glEnable (GL_BLEND);
         else            glDisable(GL_BLEND);
         glutPostRedisplay();
         break;
      case 27:
         exit(0);  /*  Escape key  */
         break;
      default:
         break;
   }
}

#if USE_MESA

void GLUTCALLBACK command(HWND hwnd,  MPARAM mp1, MPARAM mp2 )
{  int ncom;

    ncom = SHORT1FROMMP( mp1 );
    switch ( ncom )
    {
        case IDM_EXITPROG:
          /* Post a close message.*/
            WinPostMsg( hwnd, WM_CLOSE, NULL, NULL );
         break;
    }
}
#endif


/*  Main  */
int maininit(int argc, char** argv)
{
   glutInit(&argc, argv);
#if USE_MESA
    printf("Press T or Esc or F3\n"); fflush(stdout);
#else
    printf("Press T or Esc\n"); fflush(stdout);
#endif
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB
                        | GLUT_ALPHA | GLUT_DEPTH);
   glutInitWindowSize(200, 200);
   glutInitWindowPosition(100, 50);
   glutCreateWindow(argv[0]);
   init ();
   glutReshapeFunc (reshape);
   glutKeyboardFunc (keyboard);
   glutDisplayFunc (display);
#if USE_MESA
   glutCommandFunc (command);
#endif
   glutMainLoop();
   return 0;
}

