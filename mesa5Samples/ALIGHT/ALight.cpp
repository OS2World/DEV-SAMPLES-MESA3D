// Alight.c

/*************************************************************************
This example is a modification Polygons_List.c to use lighting.  The
three sided sphere was changed to a four-sided sphere to make
calculating the normal vectors easier.

Notice in the source code the order in which normals are defined for
GL_QUAD_STRIP.  In the GL_QUAD_STRIP section, Normal A applies to
vertices 1, 2, 3, and 4; Normal B applies to vertices 3, 4, 5, and 6;
Normal C applies to vertices 5, 6, 7, and 8; and Normal D applies to
vertices 7, 8, 9, and 10.  Due to the way that OpenGL renders objects,
the correct normal value must be set before the last vertex in the
current object is specified so that the correct normal value is
assigned to that object.
*************************************************************************/

// gcc -o Light  Light.c -lX11 -lMesaGL -lMesaGLU -lMesatk -lm

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "basis.h"

#define SPHERE 1
#define CUBE 2

int polySmooth=0;

void GLUTCALLBACK reshape(int width, int height) {

       // Set the new viewport size
       glViewport(0, 0, (GLint)width, (GLint)height);

       // Choose the projection matrix to be the matrix
       // manipulated by the following calls
       glMatrixMode(GL_PROJECTION);

       // Set the projection matrix to be the identity matrix
       glLoadIdentity();

       // Define the dimensions of the Orthographic Viewing Volume
       glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);

       // Choose the modelview matrix to be the matrix
       // manipulated by further calls
       glMatrixMode(GL_MODELVIEW);
}

void GLUTCALLBACK keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 't':
      case 'T':
         polySmooth = !polySmooth;
         if(polySmooth)  glEnable (GL_BLEND);
         else            glDisable(GL_BLEND);
         glutPostRedisplay();
         printf("polySmooth =%i",polySmooth); fflush(stdout);
         break;
      case 27:
         exit(0);  /*  Escape key  */
         break;
      default:
         break;
   }

}

void GLUTCALLBACK draw(void)
{

   if (polySmooth) {
      glClear (GL_COLOR_BUFFER_BIT);
      glEnable (GL_BLEND);
      glEnable (GL_POLYGON_SMOOTH);
      glDisable (GL_DEPTH_TEST);
      glEnable (GL_DEPTH_TEST);
   }
   else {
      glDisable (GL_BLEND);
      glDisable(GL_POLYGON_SMOOTH);
      glEnable (GL_DEPTH_TEST);
   }
       // Clear the RGB buffer and the depth buffer
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // Set the modelview matrix to be the identity matrix
       glLoadIdentity();
       // Translate and rotate the object
       glTranslatef(-2.5, 0.0, 0.0);

       // Draw sphere
       glCallList(SPHERE);

       glLoadIdentity();
       glTranslatef(2.5, 0.0, 0.0);
       glRotatef(45, 1.0, 0.0, 0.0);
       glRotatef(45, 0.0, 1.0, 0.0);
       glRotatef(45, 0.0, 0.0, 1.0);

       // Draw cube
       glCallList(CUBE);

       // Flush the buffer to force drawing of all objects thus far
       glFlush();
   glutSwapBuffers();
}

void make_sphere(void)
{

       GLint slices, stacks;
       GLUquadricObj *quadObj;

       quadObj = gluNewQuadric();
       slices = 64;
       stacks = 40;

       glNewList(SPHERE, GL_COMPILE);

               glColor4f(1.0, 0.0, 1.0, 0.2);
               gluSphere(quadObj, 4.0, slices, stacks);

       glEndList();
}


void make_cube(void)
{

       glNewList(CUBE, GL_COMPILE);

               glColor4f(0.0, 1.0, 0.0, 0.8);

               // Draw the sides of the cube
               glBegin(GL_QUAD_STRIP);

                        // Normal A
                       glNormal3d(0.0, 0.0, -1.0);

                        // Vertex 1
                       glVertex3d(3, 3, -3);
                        // Vertex 2
                       glVertex3d(3, -3, -3);

                        // Vertex 3
                       glVertex3d(-3, 3, -3);
                        // Vertex 4
                       glVertex3d(-3, -3, -3);

                        // Normal B
                       glNormal3d(-1.0, 0.0, 0.0);

                        // Vertex 5
                       glVertex3d(-3, 3, 3);
                        // Vertex 6
                       glVertex3d(-3, -3, 3);

                        // Normal C
                       glNormal3d(0.0, 0.0, 1.0);

                        // Vertex 7
                       glVertex3d(3, 3, 3);
                        // Vertex 8
                       glVertex3d(3, -3, 3);

                        // Normal D
                       glNormal3d(1.0, 0.0, 0.0);

                        // Vertex 9
                       glVertex3d(3, 3, -3);
                        // Vertex 10
                       glVertex3d(3, -3, -3);
               glEnd();

               glColor3f(0.0, 0.0, 1.0);

               // Draw the top and bottom of the cube
               glBegin(GL_QUADS);

                       glNormal3d(0.0, 1.0, 0.0);
                       glVertex3d(-3, -3, -3);
                       glVertex3d(3, -3, -3);
                       glVertex3d(3, -3, 3);
                       glVertex3d(-3, -3, 3);

                       glNormal3d(0.0, 1.0, 0.0);
                       glVertex3d(-3, 3, -3);
                       glVertex3d(3, 3, -3);
                       glVertex3d(3, 3, 3);
                       glVertex3d(-3, 3, 3);
               glEnd();

       glEndList();
}

void maininit(int argc, char **argv)
{

       GLfloat specular [] = { 1.0, 1.0, 1.0, 1.0 };
       GLfloat shininess [] = { 100.0 };
       GLfloat position [] = { 1.0, 1.0, 1.0, 0.0 };

 printf("Press T or Esc\n"); fflush(stdout);
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB
                        | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Light");

  glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);

       // Set the clear color to black
       glClearColor(0.5, 0.4, 0.3, 0.2);

       // Set the shading model
       glShadeModel(GL_SMOOTH);

       // Set the polygon mode to fill
//       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       glPolygonMode(GL_FRONT, GL_FILL);

       // Enable depth testing for hidden line removal
       glEnable(GL_DEPTH_TEST);

       // Define material properties of specular color and degree of
       // shininess.  Since this is only done once in this particular
       // example, it applies to all objects.  Material properties can
       // be set for individual objects, individual faces of the objects,
       // individual vertices of the faces, etc...
//      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
       glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//       glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
       glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

       // Set the GL_AMBIENT_AND_DIFFUSE color state variable to be the
       // one referred to by all following calls to glColor
//       glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
       glEnable(GL_COLOR_MATERIAL);

       // Create a Directional Light Source
       glLightfv(GL_LIGHT0, GL_POSITION, position);
       glEnable(GL_LIGHTING);
       glEnable(GL_LIGHT0);

       // Create the display lists
       make_sphere();
       make_cube();

       // Assign reshape() to be the function called whenever
       // an expose event occurs
//     tkExposeFunc(reshape);
   glutReshapeFunc (reshape);

       // Assign reshape() to be the function called whenever
       // a reshape event occurs
//??   tkReshapeFunc(reshape);

       // Assign key_down() to be the function called whenever
       // a key is pressed
   glutKeyboardFunc (keyboard);

       // Assign draw() to be the function called whenever a display
       // event occurs, generally after a resize or expose event
//     tkDisplayFunc(draw);
   glutDisplayFunc (draw);

       // Pass program control to tk's event handling code
       // In other words, loop forever
//     tkExec();
   glutMainLoop();
}
