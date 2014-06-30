#include "basis.h"
/* made on the basis of "Programming of 3D graphics" by Yu.Tikhomirov, */

#include <math.h>

static void Init(void );
static void GLUTCALLBACK Reshape(int width,int height);
static void GLUTCALLBACK Draw(void );

GLint windW, windH;
GLfloat params[4];
GLfloat aVertex[64][2], aColors[64][3];

static void Init(void)
{
  int i;

  glClearColor(1.0f, 0.96f, 0.866f, 1.0f);

  for(i = 0; i < 64; i++)
  {
    aVertex[i][0] = windW/5*sin(0.1963495*i/2);
    aVertex[i][1] = windW/5*cos(0.1963495*i/2);
    aColors[i][0] = 0.99f - 0.015*i;
    aColors[i][1] = fabs(0.99f - 0.02*i);
    aColors[i][2] = fabs(0.015*i);
  }

  glVertexPointer(2, GL_FLOAT, 0, aVertex);
  glColorPointer(3, GL_FLOAT, 0, aColors);

  glClearStencil(0x1);
  glStencilMask(0xFF);
}

static void GLUTCALLBACK Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}

static void DrawBorder(int left)
{
  GLint x;
  GLushort pattern;
  GLfloat width;

  if(!left){
    pattern = 0x1C47;
    x = windW/4;
  }
  else{
    pattern = 0x471C;
    x = -windW/4;
  }
  glPushMatrix();
    glGetFloatv(GL_LINE_WIDTH, &width);
    glLineWidth(2.0f);
    glLineStipple(2, pattern);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2i(x, -windH/2);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2i(x,  windH/2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(width);
  glPopMatrix();
}

static void CALLBACK InitViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-windW/4, windW/4, -windH/2, windH/2);
  glMatrixMode(GL_MODELVIEW);
}

static void  DrawScene(GLenum mode)
{
  // Здесь вызываются команды рисования
  // ...

  if(mode == GL_TRUE)
    glEnable(GL_STENCIL_TEST);

  glStencilFunc(GL_ALWAYS, 0x02, 0x02);
  glStencilOp(GL_REPLACE, GL_KEEP, GL_REPLACE);

  glDrawArrays(GL_POLYGON, 0, 64);

  glStencilFunc(GL_GEQUAL, 3, 2);
  glStencilOp(GL_DECR, GL_KEEP, GL_DECR);

  glColor3ub(0, 200, 200);
  glBegin(GL_POLYGON);
    glVertex2i( windW/8,  windH/6);
    glVertex2i(-windW/8,  windH/6);
    glVertex2i(-windW/8, -windH/6);
    glVertex2i( windW/8, -windH/6);
  glEnd();

  glStencilFunc(GL_EQUAL, 1, 1);
  glStencilOp(GL_INVERT, GL_KEEP, GL_KEEP);

  glShadeModel(GL_FLAT);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2i( 0, 0);
    glVertex2i(-windW/6 + 10,  windH/2 - 10);
    glColor3ub(255, 0, 0);
    glVertex2i( windW/6 - 10,  windH/2 - 10);
    glColor3ub(0, 255, 0);
    glVertex2i( windW/6 - 10, -windH/2 + 10);
    glColor3ub(200, 200, 200);
    glVertex2i(-windW/6 + 10, -windH/2 + 10);
    glColor3ub(0, 0, 255);
    glVertex2i(-windW/6 + 10,  windH/2 - 10);
  glEnd();
  glShadeModel(GL_SMOOTH);

  glDisable(GL_STENCIL_TEST);
}

static void GLUTCALLBACK Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  InitViewport(0,0, windW/2, windH);
  DrawBorder(0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  DrawScene(GL_FALSE);
  
  InitViewport(windW/2, 0, windW/2, windH);
  DrawBorder(1);
  
  glColor3f(0.5f, 0.0f, 0.5f);
  DrawScene(GL_TRUE);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  glFinish();

//??  glFlush ();
  glutSwapBuffers();
}
int polySmooth=0;
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


int maininit(int argc, char** argv)
{
#if USE_MESA
    printf("Press t,T or Esc\n"); fflush(stdout);
#endif
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB
//    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB
                        | GLUT_ALPHA | GLUT_DEPTH);
    windW = 500;
    windH = 300;
   glutInitWindowSize(windW,windH);
   glutInitWindowPosition(150, 100);

   glutCreateWindow("Work with stencil buffer...");

    Init();

   glutReshapeFunc (Reshape);
   glutDisplayFunc (Draw);

   glutKeyboardFunc (keyboard);
#if USE_MESA
   glutCommandFunc (command);
#endif

}

