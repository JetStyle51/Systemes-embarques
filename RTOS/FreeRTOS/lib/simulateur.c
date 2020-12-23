// includes Standard 
#include <stdio.h>

// includes Kernel
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// includes Simulateur (redirection de la sortie printf)
#include "simulateur.h"

/* One array position is used for each task created by this demo.  The 
variables in this array are set and cleared by the trace macros within
FreeRTOS, and displayed on the logic analyzer window within the Keil IDE -
the result of which being that the logic analyzer shows which task is
running when. */
unsigned long ulTaskNumber[ configEXPECTED_NO_RUNNING_TASKS ];

int fputc( int iChar, FILE *pxNotUsed ) 
{
	/* Supprime les warnings du compilateur */
	( void ) pxNotUsed;
	if( mainDEMCR & mainTRCENA ) 
	{
		while( mainITM_Port32( 0 ) == 0 );
		mainITM_Port8( 0 ) = iChar;
  }
  return( iChar );
}
