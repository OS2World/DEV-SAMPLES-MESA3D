#include "basis.h"

static void Init(void );
static void GLUTCALLBACK  Reshape(int width,int height);
static void GLUTCALLBACK  Draw(void );

GLint windW, windH;
GLenum blend, order, depth, color;

static void Init(void)
{
  glClearColor(0.66f, 0.66f, 0.66f, 1.0f);

  glNewList(1, GL_COMPILE);
    glColor3f(0.9f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
      glVertex3i(-windW/4 + 30,  windH/2 - 20, 0);
      glVertex3i( windW/4 - 10,            0,  0);
      glVertex3i(-windW/4 + 30, -windH/2 + 20, 0);
    glEnd();
  glEndList();

  glNewList(2, GL_COMPILE);
    glColor3f(0.0f, 0.0f, 0.9f);
    glBegin(GL_TRIANGLES);
      glVertex3i( windW/4 - 30,  windH/2 - 20, -50);
      glVertex3i( windW/4 - 30, -windH/2 + 20, -10);
      glVertex3i(-windW/4 + 10,             0,  75);
    glEnd();
  glEndList();

  blend = GL_TRUE;
  order = GL_TRUE;
  depth = GL_TRUE;
  color = GL_TRUE;
}

static void GLUTCALLBACK  Reshape(int width, int height)
{
  windW = (GLint)width;
  windH = (GLint)height;
}


static void DrawBorder(int left)
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

static void  InitViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-windW/4, windW/4, -windH/2, windH/2, -100, 100);
  glMatrixMode(GL_MODELVIEW);
}

static void GLUTCALLBACK  DrawScene(GLenum mode)
{
  // Здесь вызываются команды рисования
  // ...

  if(!depth)
    glDepthMask(GL_FALSE);
  else
    glDepthMask(GL_TRUE);

  if(!color)
    glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
  else
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  if(mode == GL_TRUE){
    glEnable(GL_DEPTH_TEST);
    if(blend)
      glEnable(GL_BLEND);
    else
      glDisable(GL_BLEND);
  }
  else{
    glDisable(GL_DEPTH_TEST);
  }

  if(order){
    glCallList(1);
    glCallList(2);
  }
  else{
    glCallList(2);
    glCallList(1);
  }

  glDisable(GL_BLEND);
}

static void GLUTCALLBACK  Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  
  InitViewport(0,0, windW/2, windH);
  DrawBorder(0);
  DrawScene(GL_FALSE);

  InitViewport(windW/2, 0, windW/2, windH);
  DrawBorder(1);
  DrawScene(GL_TRUE);

  glFinish();

  printf("blend %i, order %i, depth %i, color %i\n", blend,order,depth,color);
  fflush(stdout);
//??  glFlush ();
  glutSwapBuffers();
}

int polySmooth=0;
void  GLUTCALLBACK keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 't':
      case 'T':
         polySmooth = !polySmooth;
         if(polySmooth)  glEnable (GL_BLEND);
         else            glDisable(GL_BLEND);
         glutPostRedisplay();
         break;
      case '1':
  blend = !blend;
         break;
      case '2':
  order = !order;
         break;
      case '3':
  depth = !depth;
         break;
      case '4':
  color = !color;
         break;
      case 27:
         exit(0);  /*  Escape key  */
         break;
      default:
         break;
   }
   glutPostRedisplay();
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


int maininit(int argc, char** argv)
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB
//    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB
                        | GLUT_ALPHA | GLUT_DEPTH);
  printf("Press 1,2,3,4, or Esc/F3");

   windW = 400;
   windH = 300;
   glutInitWindowSize(windW,windH);
   glutInitWindowPosition(200, 100);

   glutCreateWindow("Work with depth buffer (z-buffer) ...");

    Init();

   glutReshapeFunc (Reshape);
   glutDisplayFunc (Draw);

   glutKeyboardFunc (keyboard);
#if USE_MESA
   glutCommandFunc (command);
#endif

}


