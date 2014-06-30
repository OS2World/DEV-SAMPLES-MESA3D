/*
 Hi Jah is all but proud to present :
    Lk 5.3/ux intro : and the code now is really ugly

 Thanks to NeHe great tutorials
 Thanks to vm18 for his script , without it , this intro won't exist
 Thanks to DPY,sorrow,IcsAcsel,paride,sef,dem0n,aleJa and other #under18 people
 Thanks to Jah (or Tao , or Allah , or Yahve , or Vishnu , or a-name-you want to give to him , a rose is always a rose even if you change his name isn't it :?
 Thanks to the gimp , to blender and other graphic programs i use
 Thanks to Nvidia for the TnT chipset and his relative glx driver
 Thanks to Linux to be such a good os , graphics and programming enviroment even for me , a complete graphics and programming failure :o*
 Thanks to all
 Thanks to you , who reads the source code before compile and execute him
 Thanks to the authors of OpenGL and MesaGL
 Thanks to the authors of mikmodlib
 Thanks to the author of loadbmp.h

This is not an Hi-Graphics-Oh-My-God-It-Seems-Real intro, it is only a fun
experiment to test if "i could make a At-Least-Compilable openGl program" .
the result as you see is pretty negative , but it was lots of fun and i have
learned something totally new , so there is nothing to complain on , it was
only fun , this not pretends to be a real great optimized full featured
demo you can see on www.hornet.org , they are totally another planet ,
but at least is runnable , or not :?
*/
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "loadbmp.h"
//#include "modplayer.c"
//#warning this is a pre alpha version , so the code is pre alpha quality :|
//(well , what a quote , i've just touched the highest peak of philosophy isn't it?)
float intposx,l2,l3,scrolleft;
GLUquadricObj *sfera,*sfera2;
int loop;
int finestra;
GLuint texture[1];
GLuint texture2[1];
GLuint texture3[1];
GLuint texture4[2];
GLuint text[1];
GLuint text1[1];
GLuint text2[1];
GLuint text3[1];
GLuint text4[1];
GLfloat ambient[] = { 1.5f, 1.5f, 1.5f, 1.0f };
GLfloat diffuse[] = { 2.0f, 2.0f, 2.0f, 2.0f };
GLfloat posxyzl[] = { 0.0f, 0.0f, -3.5f, 0.0f };
GLfloat deospin2;

//pthread_t cartadoro;
// this demo is multithreading and pre alpha quality , do the addition , it's more secure to do rm -rf / instead of compile all this crap :(
//void *mm_playerupdate(){playmodulo();}
/* hi , i'm a cube man ! */
void cubo(void)
{
   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
   glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
   glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
   glEnd();
}
/* end of cube */
/* hi man , i'm a flat panel , a square in poor words :( */
void panneLLo(void)
{
   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
   glEnd();
}
/* every good square got to end */

// texture loading function (thanks NeHe)
void texLoad1(char *immagine)
{
   Image *load1;
   load1 = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load1);
   glGenTextures(3, &texture2[0]);
   glBindTexture(GL_TEXTURE_2D, texture2[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load1->sizeX, load1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load1->data);
}

void texLoad2(char *immagine)
{
   Image *load1;
   load1 = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load1);
   glGenTextures(3, &texture3[0]);
   glBindTexture(GL_TEXTURE_2D, texture3[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load1->sizeX, load1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load1->data);
}

void texLoad3(char *immagine)
{
   Image *load1;
   load1 = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load1);
   glGenTextures(3, &texture4[0]);
   glBindTexture(GL_TEXTURE_2D, texture4[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load1->sizeX, load1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load1->data);
}

void texLoad4(char *immagine)
{
   Image *load;
   load = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load);
   glGenTextures(1, &text[0]); // if you put a value superior to one , he screw up whole thing , and i don't know why , this is the worst thing of all
   glBindTexture(GL_TEXTURE_2D, text[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // linear filtering
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load->sizeX, load->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load->data);
}


void texLoad5(char *immagine)
{
   Image *load;
   load = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load);
   glGenTextures(1, &text1[0]); // look comment over me
   glBindTexture(GL_TEXTURE_2D, text1[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load->sizeX, load->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load->data);
}

void texLoad6(char *immagine)
{
   Image *load;
   load = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load);
   glGenTextures(1, &text2[0]); // idem
   glBindTexture(GL_TEXTURE_2D, text2[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load->sizeX, load->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load->data);
}

void texLoad7(char *immagine)
{
   Image *load;
   load = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load);
   glGenTextures(1, &text3[0]);
   glBindTexture(GL_TEXTURE_2D, text3[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load->sizeX, load->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load->data);
}

void texLoad8(char *immagine)
{
   Image *load;
   load = (Image *) malloc(sizeof(Image));
   ImageLoad(immagine, load);
   glGenTextures(1, &text4[0]);
   glBindTexture(GL_TEXTURE_2D, text4[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, load->sizeX, load->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, load->data);
}

void inizializzare (int Width, int Height)
{
   texLoad1("matte.bmp"); // oh yes ! here i am , loads only 256x256@24bit textures until i find a better loader (or i code one , but remember , even me is pre alpha quality , in other words , i'm a lame coder :(
   texLoad2("matte2.bmp");
   texLoad3("matte3.bmp");
   texLoad4("matte4.bmp");
   texLoad5("matte5.bmp");
   texLoad6("matte6.bmp");
   texLoad7("matte7.bmp");
   texLoad8("matte8.bmp");

   glEnable(GL_TEXTURE_2D); // well , self explaining ?
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background , thats good
   glClearDepth(1.0);
   glDepthFunc(GL_LESS);
   glDisable(GL_DEPTH_TEST); // needed to use Blending
   glShadeModel(GL_SMOOTH);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
   glMatrixMode(GL_MODELVIEW);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE); // hi , i'm blending
   glLightfv(GL_LIGHT1, GL_AMBIENT,ambient); // diffuse lighting
   glLightfv(GL_LIGHT1, GL_DIFFUSE,diffuse);  // ambient lighting
   glLightfv(GL_LIGHT1, GL_POSITION,posxyzl);  // light position
   glEnable(GL_LIGHT1);
}

void GLUTCALLBACK reinizializzare (int Width,int Height) // re initializing function
{
   if (Height==0) {Height=1;} // height 0 is bad , destroy height 0
   glViewport(0, 0, Width, Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
   glMatrixMode(GL_MODELVIEW);
}
void GLUTCALLBACK draw (void)
{
   float zoom3tot,s2,x,x2,zoomsomma2,zoomtot,zoom2tot;
static float y=0.,zoomsomma=0.5,l32=0.;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // don't use it , and you gl window will screw up
   glEnable(GL_LIGHTING);
   glEnable(GL_BLEND);
   glLoadIdentity(); // this function is used to reinitalize positions and others
   intposx-=0.035;
   l2+=2.1;
   s2=2.1;

   glBindTexture(GL_TEXTURE_2D, texture2[0]);
   glTranslatef(0.0,0.0,intposx);
   glRotatef(l2,0.0f,0.0f,1.5f);
   panneLLo();

   glBindTexture(GL_TEXTURE_2D, texture3[0]);
   glTranslatef(0.0,0.0,intposx);
   glRotatef(l2,0.0f,0.0f,1.5f);
   glScalef(3.1,3.1,3.1);
   panneLLo();

   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D, texture4[0]);
   scrolleft+=0.009;
   glTranslatef((scrolleft + (-2.0)),0.0,-6.0);
   glScalef(2.1,1.8,2.1);
   glRotatef(1.0,5.0f,1.5f,1.5);
   panneLLo();

   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D, text4[0]);
   glTranslatef((scrolleft + (-10.0)),0.0,-6.0);
   glScalef(2.1,1.8,2.1);
   glRotatef(1.0,5.0f,1.5f,1.5);
   panneLLo();

   glLoadIdentity();
   sfera = gluNewQuadric();
   gluQuadricTexture(sfera, GL_TRUE); // must use it to texturemap a quadric object
   glBindTexture(GL_TEXTURE_2D, text[0]);
   glTranslatef(0.0,0.0,0.0);
   glScalef(6.0,6.0,10.0);
   x=0.5;
   l3+=1.001;
   y+=10.3;
   glRotatef(l3,x++,x++,x++);
   gluSphere(sfera,9.0, 40, 10);

   glLoadIdentity();
   sfera2 = gluNewQuadric();
   gluQuadricTexture(sfera2, GL_TRUE);
   glBindTexture(GL_TEXTURE_2D, text3[0]);
   zoomsomma+=0.09;
   zoom3tot=zoomsomma - 8.0;
   if (zoom3tot>-5.0) { zoom3tot=-5.0; }
   glTranslatef(0.0,0.0,zoom3tot);
   glRotatef(l3,y++,y++,y++);
   glScalef(0.9,0.9,0.9);
   gluSphere(sfera2,2.0, 40, 10);

   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D, text1[0]);
   zoomtot=zoomsomma - 20.0;
   printf ("%f\n",zoomtot);
   if (zoomtot>-3.5) { zoomtot=-3.5; }
   glTranslatef(0.0,-0.3,zoomtot);
   panneLLo();

   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D, text2[0]);
   zoom2tot=zoomsomma - 20.0;
   printf ("%f\n",zoom2tot);
   if (zoom2tot>-3.0) { zoom2tot=-3.0; }
   x2=-3.5;
   l32+=1.001;
   glTranslatef(0.0,0.0,zoom2tot);
   glRotatef(l32,x2++,x2++,x2++);
   cubo();
   glutSwapBuffers();
}

void GLUTCALLBACK  eventi(unsigned char tasto, int x, int y)
{
   if (tasto==27)
       { exit(0); }  // 27 is ESC key
}

int maininit(int argc, char** argv)
{
   glutInit(&argc, argv); // needed
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
   glutInitWindowSize(640, 480); // our win size
   glutInitWindowPosition(0, 0);
   finestra = glutCreateWindow("Demo1");
   glutDisplayFunc(&draw);
//glutFullScreen(); // uncomment to get fullscreen ( it will slow the demo a bit )
   glutIdleFunc(&draw); // if you don't use it , you have to use a kind of glutPostRedisplay(); loop to redraw the scene , so , use it :|
   glutReshapeFunc(&reinizializzare);
   glutKeyboardFunc(&eventi);
   inizializzare(640, 480);
//   pthread_create(&cartadoro,NULL,mm_playerupdate,NULL); // playing the soundtrack man !
   glutMainLoop();
return 1;
}










