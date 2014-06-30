/*
 Hi Jah (Rastam0n) is all but proud to present :

              HiJah Intro

 Thanks to :
 All the people in #under18@ircnet (DPY,Vm18,sorrow-,par-,Cra|z,A|exia,sEf,iCs`Acsel,dem0n and others)
 The almighty god , vishnu , jah , allah , Madza ahura , Yahve or whatever name you want to give to him , for a rose is always a rose , whatever name you give at it , isn't it ?
 NeHe tutorials , principally the BASE of this demo , thanks NeHe , those tutorial are great
 The food , oh yes , the food and caffeinate drinks :I
 Linux , for being such a great developing platform and graphics enviroment , even for me , a complete failed-man in both the arts (programming and graphics)
 All the people on this planet :?
 You that pick my unknown demo and read the code before compile it
 Machintosh Graphing calculator , endless help in math

 Glory to the most high man , he loves us
 */
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "loadbmp.h"

void panneLLo(void);

int finestra;
GLuint texture1[1];
GLuint texture2[1];
GLuint texture3[1];
GLuint texture4[1];
float a,x,y,xx,yy,zz,zmul,xxx,yyy,zzz,zzmul,xxx2,yyy2,zzz2,zzmul2,d,pi,c;
GLUquadricObj *sfera,*sfera2;
GLfloat ambient[] = { 1.5f, 1.5f, 1.5f, 1.0f };
GLfloat diffuse[] = { 2.0f, 2.0f, 2.0f, 2.0f };
GLfloat posxyzl[] = { 0.0f, 0.0f, -5.0f, -5.0f }; // position into the screen (5 units)

/* first scene ! the background */
void palle(void)
{
   glLoadIdentity(); // reinizialize positions and all
   y-=0.6;
   x+=0.56;
   sfera = gluNewQuadric();
   gluQuadricTexture(sfera, GL_TRUE); // needed to texture up the quadratics
   glBindTexture(GL_TEXTURE_2D,texture2[0]);
   glTranslatef(0.0,0.0,0.0); // 0.0 == center
   glScalef(100.0,100.0,100.0); // enormous
   glRotatef(y,x,y,x);
   gluSphere(sfera,2.0, 50, 50); // increasing  50, 50 will increase the slices of the sphere and so the definition of it , and decrease the speed of demo :(
}
/* 2nd , bouncing happy logo */
void logo(void)
{
   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D,texture3[0]);
   xxx-=0.06;
   yyy+=0.06;
   zzmul+=0.01;
/* EEEk : one note about this formula , it was made using Mac Graphing calculator
   its : z=x*y/cos(x)*y*n , made the logo bounce up and down in z axis */
   zzz=xxx*yyy/(cos(xxx)*yyy*zzmul);
   glTranslatef(0.0,0.0,zzz+2.5); // the 2.5 is reaches the logo more near to the 0.0 center
   glRotatef(zzz+x,-zzz+x,0.0,-zzz+x); // wacky rotations make the logo better (used the same bouncing formula)
   panneLLo(); // our beloved square
}

/* 3rd , the same of the 2nd with some value changed , bouncing credits , anyway */
void by(void)
{
   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D,texture4[0]);
   d += 0.01;
   pi = 3.17;
   c = pi*d;
   xxx2 -= 0.06;
   yyy2 += 0.06;
   zzmul2 += 0.01;
   zzz2 = xxx2 * yyy2 / ( cos(xxx2) * yyy2 * zzmul2);
   glTranslatef(c/xxx2, 0.0, zzz2+3.0);
   glRotatef(zzz2-x, -zzz2+x, 0.0, -zzz+x);
   panneLLo();
}
/* 4th , distorting sphere */
void terra(void)
{
   a += 6.0f;
   zmul += 0.10f;
   xx -= 0.01;
   yy += 0.01;
/* EEEEEEEEEEEek one more note , this formula is more instable than the first , its speed increments always more
   the formula (always found using Graphing calc) is :
   z=cos(n)*x*y*sqrt(n/0.001)/1000; , originally it whas without 1000 and 0.001 , they are for make it more slow */
   zz = cos(zmul)*xx*yy*sqrt(zmul/0.001)/1000;
/* debugging use */
   printf ("Z AXIS effetto tunnel , cazoquantogodo:%f\n",zz);
   glLoadIdentity();
   sfera2 = gluNewQuadric();
   gluQuadricTexture(sfera2, GL_TRUE);
   glBindTexture(GL_TEXTURE_2D,texture1[0]);
   glTranslatef(0.0,0.0,0.0);
   glScalef(1.0,1.0,zz); /* using our formula */
   glRotatef(a,a,a,a);
   gluSphere(sfera2,1.0, 50, 50);
}
void panneLLo (void)
{
   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
   glEnd();
}

void texLoad1(char *immagine)
{
   Image *load1;
   load1 = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load1);
   glGenTextures(1, &texture1[0]);
   glBindTexture(GL_TEXTURE_2D, texture1[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load1->sizeX, load1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load1->data);
}

void texLoad2(char *immagine)
{
   Image *load1;
   load1 = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load1);
   glGenTextures(3, &texture2[0]);
   glBindTexture(GL_TEXTURE_2D, texture2[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load1->sizeX, load1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load1->data);
}

void texLoad3(char *immagine)
{
   Image *load1;
   load1 = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load1);
   glGenTextures(3, &texture3[0]);
   glBindTexture(GL_TEXTURE_2D, texture3[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load1->sizeX, load1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load1->data);
}

void texLoad4(char *immagine)
{
   Image *load1;
   load1 = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load1);
   glGenTextures(1, &texture4[0]);
   glBindTexture(GL_TEXTURE_2D, texture4[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load1->sizeX, load1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load1->data);
}

void inizializzare (int Width, int Height)
{
   texLoad1("terra.bmp");
   texLoad2("light.bmp");
   texLoad3("logo.bmp");
   texLoad4("by.bmp");
   glEnable(GL_TEXTURE_2D);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0);
   glDepthFunc(GL_LESS);
   glDisable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000000.0f); /* super mega depth */
   glMatrixMode(GL_MODELVIEW);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   glLightfv(GL_LIGHT1, GL_AMBIENT,ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE,diffuse);
   glLightfv(GL_LIGHT1, GL_POSITION,posxyzl);
   glEnable(GL_LIGHT1);
}

void GLUTCALLBACK reinizializzare (int Width,int Height)
{
   if (Height==0)
           Height=1;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000000.0f);
   glMatrixMode(GL_MODELVIEW);
}

void GLUTCALLBACK draw (void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_BLEND);
   glEnable(GL_LIGHTING);
   glLoadIdentity();
   palle(); // here we go
   terra();
   logo();
   by();
   glutSwapBuffers();
   DosSleep(10);
}

void GLUTCALLBACK eventi(unsigned char tasto, int x, int y)
{
   if (tasto==27)
       { exit(0); } // if esc key then go out this crap
}

int maininit(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(0, 0);
   finestra = glutCreateWindow("H i   J  a  h");
   glutDisplayFunc(&draw);
   glutIdleFunc(&draw);
   glutReshapeFunc(&reinizializzare);
   glutKeyboardFunc(&eventi);
   inizializzare(640, 480);
   glutMainLoop();
return 1;
}







