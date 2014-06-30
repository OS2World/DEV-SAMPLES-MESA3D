// BASIS.H

// 0 - work with traditional IBM OpenGL
// 1 - work with WarpMesa
#define USE_MESA 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#if USE_MESA
/* commented to satisfy VAC3 @#$% build smarts */

     #include "..\GL\gl.h"
     #include "..\GL\glut.h"
     #include "GL_TEST.H"

#else
  #include <GL\gl.h>
  #include <GL\glut.h>

#endif


