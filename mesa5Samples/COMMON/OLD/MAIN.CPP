/* MAIN.C */

#include "basis.h"


#define POKA 0

int InitPM(int mode);
int TestPM(void);

int maininit(int argc, char** argv);

extern HAB   hab;      /* PM anchor block handle         */
extern HPS   hpsCurrent;
extern HDC XHDC;
extern HWND XHWND;

//extern static PWMC Current;
extern GLenum stereoCompile ;
extern GLenum stereoShowing ;
extern GLenum stereoBuffer;


/*
 * Declare initial window size, position, and display mode
 * (single buffer and RGBA).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */

int main(int argc, char** argv)
{

/**********************************************/
  PPIB pib;
  PTIB tib;

  printf("In console\n");

  DosGetInfoBlocks(&tib, &pib);
 /* Try morphing into a PM application. */
//  if(pib->pib_ultype == 2)          /* VIO */
    pib->pib_ultype = 3;
/**********************************************/

#if USE_MESA
//   if(InitPM(1))
   if(InitPM(0))
      return 1;
#endif

    maininit(argc, argv);
    glutMainLoop();

   return 0;   /* ANSI C requires main to return int. */
}

#if USE_MESA

HAB   mainhab = NULLHANDLE;      /* PM anchor block handle         */
HMQ   mainhmq = NULLHANDLE;      /* message queue handle           */
HPS   mainhpsCurrent;

int InitPM(int mode)
{
    if ( ( mainhab = WinInitialize( 0UL ) ) == NULLHANDLE )
                   return 1;
   if ( ( mainhmq = WinCreateMsgQueue( mainhab, 32UL ) ) == NULLHANDLE )
                   return 2;
   OS2_WMesaInitHab(mainhab,mode);

    return 0;
}

#endif
