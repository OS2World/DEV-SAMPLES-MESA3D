#include "basis.h"

#include <math.h>


void Init(void );

int maininit(int argc, char** argv);
void GLUTCALLBACK display(void);
void GLUTCALLBACK Reshape(int width,int height);

GLint windW, windH;
GLfloat params[4];
GLfloat aVertex[64][2], aColors[64][3];

void Init(void)
{
  int i;

  glClearColor(1.0f, 0.96f, 0.866f, 1.0f);

  for(i = 0; i < 64; i++)
  {
    aVertex[i][0] = windW/5*sin(0.1963495*i/2);
    aVertex[i][1] = windW/5*cos(0.1963495*i/2);
    aColors[i][0] = 0.01f + 0.015*i;
    aColors[i][1] = 0.01f + 0.015*i;
    aColors[i][1] = 0.01f + 0.015*i;
  }

  glVertexPointer(2, GL_FLOAT, 0, aVertex);
  glColorPointer(3, GL_FLOAT, 0, aColors);
}

void  GLUTCALLBACK Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}

void DrawBorder(int left)
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

void  InitViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-windW/4, windW/4, -windH/2, windH/2);
  glMatrixMode(GL_MODELVIEW);
}

void DrawScene(GLenum mode)
{
  GLfloat width;

  // Здесь вызываются команды рисования
  // ...

  glGetFloatv(GL_POINT_SIZE, &width);

  glGetFloatv(GL_CURRENT_COLOR, params);

  glPushAttrib(GL_POLYGON_BIT);
    if(mode == GL_TRUE){
      glPointSize(3.0f);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    glDrawArrays(GL_POLYGON, 0, 64);
  glPopAttrib();

  glPointSize(width);
  glColor3f(params[0], params[1], params[2]);
}

void GLUTCALLBACK  display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  InitViewport(0,0, windW/2, windH);
  DrawBorder(0);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  DrawScene(GL_FALSE);
  glDisableClientState(GL_COLOR_ARRAY);

  InitViewport(windW/2, 0, windW/2, windH);
  DrawBorder(1);

  DrawScene(GL_TRUE);

  glDisableClientState(GL_VERTEX_ARRAY);

  glFinish();
  glutSwapBuffers();
}

int maininit(int argc, char** argv)
{
    windW = 400;
    windH = 300;



   glutInit(&argc, argv);
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB| GLUT_ALPHA | GLUT_DEPTH);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_ALPHA | GLUT_DEPTH);
   glutInitWindowSize(400, 400);
   glutInitWindowPosition (50, 50);
   glutCreateWindow("Многоугольники, многоугольники ...");
   Init ();
   glutReshapeFunc(Reshape);
   glutDisplayFunc(display);


}
