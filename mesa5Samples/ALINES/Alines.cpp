/* alines.c */

#include "basis.h"

static void Init(void );
static void GLUTCALLBACK Reshape(int width,int height);
static void GLUTCALLBACK Draw(void );

GLint windW, windH;

static void Init(void)
{
//     glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);
//     glEnable (GL_BLEND);
  glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
}

static void GLUTCALLBACK Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}

static void DrawAxies(int left)
{
  GLint x;
  GLushort pattern;
  GLfloat width;

  glColor3f(0.0f, 0.0f, 0.0f);
  if(!left){
    pattern = 0x1C47;
    x = windW/4;
  }
  else{
    pattern = 0x471C;
    x = -windW/4+1;
  }
  glPushMatrix();
    glGetFloatv(GL_LINE_WIDTH, &width);
    glLineWidth(2.0f);
    glLineStipple(2, pattern);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
      glVertex2i(x, -windH/2);
      glVertex2i(x,  windH/2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(width);

    glBegin(GL_LINES);
      glVertex2i(-windW/4 + 10, 0);
      glVertex2i( windW/4 - 10, 0);
      glVertex2i(0, -windH/2 + 10);
      glVertex2i(0,  windH/2 - 10);
    glEnd();
  glPopMatrix();
}

static void InitViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-windW/4, windW/4, -windH/2, windH/2);
  glMatrixMode(GL_MODELVIEW);
}

static void DrawScene(GLenum mode)
{
  // Здесь вызываются команды рисования
  // ...

  glBegin(mode);
    glVertex2f(-windW/4 + windW/20, -windH/2 + windH/10);
    glVertex2f( windW/4 - windW/20, -windH/2 + windH/10);
    glVertex2f( windW/4 - windW/20,  windH/2 - windH/10);
  glEnd();
}

static void  DrawLine(void)
{
  glLineWidth(20.0f);
  glBegin(GL_LINES);
    glVertex2f(-windW/4 + windW/20, -windH/2 + windH/5);
    glVertex2f( 0, windH/2 - windH/10);
    glVertex2f(-windW/4 + windW/20 + 30, -windH/2 + windH/5);
    glVertex2f( 30, windH/2 - windH/10);
  glEnd();
  glLineWidth(1.0f);
}

static void GLUTCALLBACK Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  InitViewport(0,0, windW/2, windH);
  DrawAxies(0);

  glColor3f(0.0, 0.0, 1.0);
  DrawScene(GL_LINE_STRIP);
  glColor3f(1.0, 0.0, 1.0);
  DrawLine();

  InitViewport(windW/2, 0, windW/2, windH);
  DrawAxies(1);

  glColor3f(1.0, 0.0, 0.0);
  DrawScene(GL_LINE_LOOP);

  glEnable(GL_LINE_SMOOTH);
  glColor3f(1.0, 0.0, 1.0);
  DrawLine();
  glDisable(GL_LINE_SMOOTH);

  glFinish();
   glutSwapBuffers();
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

/*  Main */

int maininit(int argc, char** argv)
{
   glutInit(&argc, argv);
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB
                        | GLUT_ALPHA | GLUT_DEPTH);
//                        | GLUT_DEPTH);

    windW = 400;
    windH = 300;
   glutInitWindowSize(windW,windH);
   glutInitWindowPosition(100, 50);

   glutCreateWindow("Lines, lines, lines...");
   Init ();
   glutReshapeFunc (Reshape);
//   glutKeyboardFunc (keyboard);
   glutDisplayFunc (Draw);
#if USE_MESA
   glutCommandFunc (command);
#endif
   glutMainLoop();
   return 0;
}
