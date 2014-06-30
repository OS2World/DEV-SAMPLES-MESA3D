#include "basis.h"

#define POKA 0

int maininit(int argc, char** argv);
void GLUTCALLBACK display(void);
void GLUTCALLBACK Reshape(int width,int height);


void Init(void );

GLint windW, windH;
GLfloat params[4];

void Init(void)
{
  glClearColor(1.0f, 0.96f, 0.866f, 1.0f);
//  glBlendFunc(GL_SRC_ALPHA_SATURATE,GL_ONE);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void  GLUTCALLBACK Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}

void  DrawBorder(int left)
{
  GLint x;
  GLushort pattern;

  glColor3f(0.0f, 0.0f, 0.0f);
  if(!left){
    pattern = 0x1C47;
    x = windW/4;
  }
  else{
    pattern = 0x471C;
    x = -windW/4;
  }
  glPushMatrix();
    glGetFloatv(GL_LINE_WIDTH, &params[0]);
    glLineWidth(2.0f);
    glLineStipple(2, pattern);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
      glVertex2i(x, -windH/2);
      glVertex2i(x,  windH/2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(params[0]);
  glPopMatrix();
}

void  InitViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-windW/4, windW/4, -windH/2, windH/2);
  glMatrixMode(GL_MODELVIEW);
}

void  DrawScene(void)
{
  int i;
  GLint aVertex[6][2];

  // Определяем координаты вершин для треугольников
  aVertex[0][0] = -windW/32*7;  aVertex[0][1] =  windH/3;
  aVertex[1][0] = -windW/16;    aVertex[1][1] =  windH/24*11;
  aVertex[2][0] =  windW/8;     aVertex[2][1] =  windH/24*10;
  aVertex[3][0] =  windW/32*7;  aVertex[3][1] =  windH/3;
  aVertex[4][0] =  windW/8;     aVertex[4][1] =  windH/24*7;
  aVertex[5][0] = -windW/16;    aVertex[5][1] =  windH/24*5;

  // Здесь вызываются команды рисования
  // ...

  glGetFloatv(GL_CURRENT_COLOR, params);

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_TRIANGLES);
    for (i = 0; i < 6; i++) {
      glVertex2iv(aVertex[i]);
    }
  glEnd();


  for(i = 0; i < 6; i++){
    aVertex[i][1] -= windH/3;
  }

  glColor3f(0.0f, 1.f, 0.0f);
  glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i < 6; i++) {
      glVertex2iv(aVertex[i]);
    }
  glEnd();


  for(i = 0; i < 6; i++){
    aVertex[i][1] -= windH/3;
  }

  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < 6; i++) {
      glVertex2iv(aVertex[i]);
    }
  glEnd();
  glColor3f(params[0], params[1], params[2]);
}

void GLUTCALLBACK  display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  InitViewport(0,0, windW/2, windH);
  DrawBorder(0);

  glColor3f(1.0, 0.0, 1.0);
  DrawScene();

  InitViewport(windW/2, 0, windW/2, windH);
  DrawBorder(1);

  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_BLEND);
  glColor3f(1.0, 0.0, 1.0);
  DrawScene();
  glDisable(GL_BLEND);
  glDisable(GL_POLYGON_SMOOTH);

  glFinish();
  glutSwapBuffers();
}

void GLUTCALLBACK keyboard(unsigned char key, int x, int y)
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

int maininit(int argc, char **argv)
{
    windW = 500;
    windH = 300;
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (windW, windH);
   glutInitWindowPosition (150, 100);
   glutCreateWindow ("Треугольники, треугольники ...");
   Init ();
    glutReshapeFunc(Reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc (keyboard);
#if USE_MESA
   glutCommandFunc (command);
#endif
  return 0;   /* ANSI C requires main to return int. */

}
