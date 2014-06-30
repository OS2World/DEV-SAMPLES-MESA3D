#include "basis.h"

void GLUTCALLBACK Init(void );
void GLUTCALLBACK Reshape(int width,int height);
void GLUTCALLBACK keyboard(unsigned char key, int x, int y);

void GLUTCALLBACK Draw(void );
void  Key_0(void );
void  Key_1(void );
void  Key_2(void );
void  Key_3(void );
void  Key_4(void );
void  Key_5(void );
void  Key_6(void );
void  Key_7(void );
void  Key_8(void );
void  Key_9(void );

GLint  windW, windH;
GLenum typePrim;
GLint blendSrc, blendDst, alphaFunc;

void Init(void)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  typePrim  = GL_FALSE;
  blendSrc = GL_SRC_ALPHA;
  blendDst = GL_ONE_MINUS_SRC_ALPHA;
  alphaFunc = GL_LESS;
}

void GLUTCALLBACK Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}


void GLUTCALLBACK keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);  /*  Escape key  */
         break;
      case '0': Key_0();
         break;
      case '1': Key_1();
         break;
      case '2': Key_2();
         break;
      case '3': Key_3();
         break;
      case '4': Key_4();
         break;
      case '5': Key_5();
         break;
      case '6': Key_6();
         break;
      case '7': Key_7();
         break;
      case '8': Key_8();
         break;
      case '9': Key_9();
         break;

      default: return;
         break;
   }
   Draw();
}

void  Key_0(void)
{
  if(alphaFunc == GL_LESS)
    alphaFunc = GL_GREATER;
  else
    alphaFunc = GL_LESS;
}

void  Key_1(void)
{
  blendSrc = GL_SRC_ALPHA;
  blendDst = GL_ONE_MINUS_SRC_ALPHA;
}

void  Key_2(void)
{
  blendSrc = GL_DST_ALPHA;
  blendDst = GL_ONE_MINUS_DST_ALPHA;
}

void  Key_3(void)
{
  blendSrc = GL_SRC_ALPHA;
  blendDst = GL_ONE_MINUS_DST_ALPHA;
}

void  Key_4(void)
{
  blendSrc = GL_DST_ALPHA;
  blendDst = GL_ONE_MINUS_SRC_ALPHA;
}

void  Key_5(void)
{
  blendSrc = GL_SRC_ALPHA_SATURATE;
  blendDst = GL_ONE_MINUS_SRC_ALPHA;
}

void  Key_6(void)
{
  blendSrc = GL_SRC_ALPHA_SATURATE;
  blendDst = GL_SRC_COLOR;
}

void  Key_7(void)
{
  blendSrc = GL_SRC_ALPHA_SATURATE;
  blendDst = GL_ONE;
}

void  Key_8(void)
{
  blendSrc = GL_SRC_ALPHA_SATURATE;
  blendDst = GL_SRC_ALPHA;
}

void  Key_9(void)
{
  blendSrc = GL_SRC_ALPHA;
  blendDst = GL_DST_ALPHA;
}

void  DrawBorder(int left)
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

void  DrawScene(GLint mode)
{
  // Здесь вызываются команды рисования
  // ...

  glColor4f(1.0f, 0.0f, 0.0f, 0.75f);
  glRecti(-windW/4 + 20, -windH/2 + 20,
           windW/4 - 20,  20);

  if(mode){
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
  }

  glColor4f(0.0f, 0.0f, 1.0f, 0.25f);
  glRecti( 20, -windH/2 + 20,
           windW/4 - 10, windH/2 - 20);

  glDisable(GL_ALPHA_TEST);

  glColor4f(0.0f, 0.0f, 1.0f, 0.75f);
  glRecti(-windW/4 + 10, -windH/2 + 20,
          - 20, windH/2 - 20);
  glDisable(GL_BLEND);
}

void GLUTCALLBACK Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(blendSrc, blendDst);
  glAlphaFunc(alphaFunc, 0.5f);

  InitViewport(0,0, windW/2, windH);
  DrawBorder(0);

  glColor3f(0.0, 0.0, 1.0);
  DrawScene(0);

  InitViewport(windW/2, 0, windW/2, windH);
  DrawBorder(1);

  glColor3f(1.0, 0.0, 0.0);
  DrawScene(1);

  glFinish();
  glutSwapBuffers();
}

int maininit(int argc, char** argv)
{
 printf("Press 1,2,3,4,5,6,7,7,8,9,0 or Esc\n"); fflush(stdout);
    windW = 400;
    windH = 300;
   
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB );

    glutInitWindowSize(windW, windH);
    glutInitWindowPosition(0, 0);


    if (glutCreateWindow("Alpha test") == GL_FALSE) {
       exit(1);
    }

    Init();

   glutReshapeFunc (Reshape);
   glutKeyboardFunc (keyboard);
   glutDisplayFunc (Draw);

}
