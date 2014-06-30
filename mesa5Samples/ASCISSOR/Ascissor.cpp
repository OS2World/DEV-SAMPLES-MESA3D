#include "basis.h"
/* made on the basis of "Programming of 3D graphics" by Yu.Tikhomirov, */
static void Init(void );
static void GLUTCALLBACK Reshape(int width,int height);
static void GLUTCALLBACK Draw(void );

GLint windW, windH;
GLenum typePrim;

static void Init(void)
{
  glClearColor(1.0f, 0.96f, 0.866f, 1.0f);

  typePrim = GL_FALSE;
}

static void GLUTCALLBACK  Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}

static void GLUTCALLBACK  Key(unsigned char key, int x, int y)
{
  typePrim = !typePrim;
    (void) y;
    switch (key) {
      case 27:
	exit(1);
	break;
      default:
	return;
    }
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

static void InitViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-windW/4, windW/4, -windH/2, windH/2);
  glMatrixMode(GL_MODELVIEW);
}

static void DrawScene(GLint mode)
{
  GLint prim;
  // Здесь вызываются команды рисования
  // ...

  if(mode){
    glScissor(5*windW/8-1, windH/4-1, windW/4+2, windH/2+2);
    glEnable(GL_SCISSOR_TEST);
    glShadeModel(GL_FLAT);
    glBegin(GL_LINE_LOOP);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2i(-windW/8, -windH/4);
      glVertex2i(-windW/8,  windH/4);
      glVertex2i( windW/8,  windH/4);
      glVertex2i( windW/8, -windH/4);
  glEnd();
  }
  else
    glShadeModel(GL_SMOOTH);

  if(typePrim == GL_FALSE)
    prim = GL_POLYGON;
  else
    prim = GL_QUADS;
  
  glBegin(prim);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(      0,  windH/3);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(windW/6,        0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(      0, -windH/3);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex2i(-windW/6,       0);
  glEnd();
  
  glDisable(GL_SCISSOR_TEST);
}

static void GLUTCALLBACK  Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
    
  InitViewport(0,0, windW/2, windH);
  DrawBorder(0);

  glColor3f(0.0, 0.0, 1.0);
  DrawScene(0);

  InitViewport(windW/2, 0, windW/2, windH);
  DrawBorder(1);
  
  glColor3f(1.0, 0.0, 0.0);
  DrawScene(1);

  glFinish();

    glFlush();

//    if (doubleBuffer) {
	glutSwapBuffers();
//    }
}

int maininit(int argc, char **argv)
{   int type;
    windW = 400;
    windH = 300;
    glutInitWindowPosition(20, 10);
    glutInitWindowSize( windW, windH);

    type = GLUT_RGB | GLUT_DOUBLE;
    glutInitDisplayMode(type);

    if (glutCreateWindow("Отсечение") == GL_FALSE) {
      exit(1);
    }

    Init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutMainLoop();

}
