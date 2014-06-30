#include "basis.h"

void Init(void );

int maininit(int argc, char** argv);
void GLUTCALLBACK display(void);
void GLUTCALLBACK Reshape(int width,int height);

GLint windW, windH;
GLfloat params[4];

void Init(void)
{
  glClearColor(1.0f, 0.96f, 0.866f, 1.0f);
}

void GLUTCALLBACK Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}

void DrawBorder(int left)
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
    x = -windW/4;
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
  glPopMatrix();
}

void InitViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-windW/4, windW/4, -windH/2, windH/2);
  glMatrixMode(GL_MODELVIEW);
}

void  DrawScene(GLenum mode)
{
  int i;
  GLint aVertex[8][2];

  // Определяем координаты вершин для треугольников
  aVertex[0][0] = -windW/4 + 10; aVertex[0][1] =  0;
  aVertex[1][0] = -windW/8;      aVertex[1][1] =  windH/8*3;
  aVertex[2][0] =  windW/20;     aVertex[2][1] =  0;
  aVertex[3][0] = -windW/8;      aVertex[3][1] = -windH/4;
  aVertex[4][0] =  windW/8;      aVertex[4][1] =  windH/8*3;
  aVertex[5][0] =  windW/4 - 10; aVertex[5][1] =  0;
  aVertex[6][0] =  windW/8;      aVertex[6][1] = -windH/8*3;
  aVertex[7][0] =  windW/20;     aVertex[7][1] = -windH/4;

  // Здесь вызываются команды рисования
  // ...

  glPushAttrib(GL_POLYGON_BIT);
  if(mode == GL_QUAD_STRIP)
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//FRONT_AND_
    glPolygonMode(GL_FRONT, GL_LINE);//FRONT_AND_

    glBegin(mode);
      for (i = 0; i < 8; i++) {
        glColor3f(1.0f - 0.1*(GLfloat)i,
                  0.2f + 0.1*(GLfloat)i,
                  0.6f + 0.05*(GLfloat)i);
        glVertex2iv(aVertex[i]);
      }
    glEnd();
  glPopAttrib();
}

void GLUTCALLBACK display(void)
{
  GLubyte pattern[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
    0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
    0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
    0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
    0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
    0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
    0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
    0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
    0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
    0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
    0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
    0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08
  };

  glClear(GL_COLOR_BUFFER_BIT);

  glPolygonStipple(pattern);
  glEnable(GL_POLYGON_STIPPLE);

  InitViewport(0,0, windW/2, windH);
  DrawBorder(0);

  glColor3f(1.0f, 0.3f, 0.5f);
  DrawScene(GL_QUADS);

  InitViewport(windW/2, 0, windW/2, windH);
  DrawBorder(1);

  glLineWidth(2.0f);
  glColor3f(0.5f, 0.0f, 0.5f);
  glEnable(GL_POLYGON_SMOOTH);
  DrawScene(GL_QUAD_STRIP);

  glDisable(GL_POLYGON_SMOOTH);
  glDisable(GL_POLYGON_STIPPLE);

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
   glutCreateWindow("Quadra");
   Init ();
   glutReshapeFunc(Reshape);
   glutDisplayFunc(display);

}
