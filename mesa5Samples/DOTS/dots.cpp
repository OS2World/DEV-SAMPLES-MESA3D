/* Dots.c */

#include "basis.h"

static void Init(void );
void GLUTCALLBACK Reshape(int width,int height);
void GLUTCALLBACK Draw(void );

GLint windW, windH;

static void Init(void)
{
  glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
}

void GLUTCALLBACK  Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}

static void DrawAxies(int left)
{
  GLint x;

  glColor3f(0.0f, 0.0f, 0.0f);
  if(!left)
    x = windW/4;
  else
    x = -windW/4;
  glPushMatrix();
    glBegin(GL_LINES);
      glVertex2i(x, -windH/2);
      glVertex2i(x,  windH/2);
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

static void DrawScene(void)
{
  // Здесь вызываются команды рисования
  // ...

  int i;
  for(i = 0; i < 10; i++){
    glPointSize((i+1) * 2);
    glBegin(GL_POINTS);
      glVertex2f(-windW/4 + (GLfloat)i * windW/20,
                 -windH/2 + (GLfloat)i * windH/10);
    glEnd();
  }
}

void  GLUTCALLBACK Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  InitViewport(0,0, windW/2, windH);
  DrawAxies(0);

  glColor3f(0.0, 0.0, 1.0);
  DrawScene();

  InitViewport(windW/2, 0, windW/2, windH);
  DrawAxies(1);

  glEnable(GL_POINT_SMOOTH);
  glColor3f(1.0, 0.0, 0.0);
  DrawScene();
  glDisable(GL_POINT_SMOOTH);

  glColor3f(1.0, 0.0, 0.0);
  glFinish();


   glutSwapBuffers();
}

void GLUTCALLBACK  keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);  /*  Escape key  */
         break;
      default:
         break;
   }
}

#if USE_MESA

void GLUTCALLBACK  command(HWND hwnd,  MPARAM mp1, MPARAM mp2 )
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

/*  Main Loop
 */
int maininit(int argc, char** argv)
{
   glutInit(&argc, argv);
#if USE_MESA
    printf("Press  Esc\n"); fflush(stdout);
#endif
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
//                        | GLUT_ALPHA | GLUT_DEPTH);
//                        | GLUT_DEPTH);
   glutInitWindowSize(300, 200);
   glutInitWindowPosition(100, 50);

   glutCreateWindow("Dots, dots, dots...");
   Init ();
   glutReshapeFunc (Reshape);
   glutKeyboardFunc (keyboard);
   glutDisplayFunc (Draw);

#if USE_MESA
   glutCommandFunc (command);
#endif

   glutMainLoop();
   return 0;
}


