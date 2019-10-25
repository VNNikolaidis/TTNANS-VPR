/* --------------------
   System Defs.
  (All major definitions)
   --------------------
   Vasilis.N.Nikolaidis
   -------------------- */

#ifndef TTNDEF
#define TTNDEF

/*-----------------------------------------------------------------------*

For multiple editors, tab size is shown below:

....X (no tab,X)
	X (tab,X)

Code starts here:
-------------------------------------------------------------------------*/

#define VERSION "TTNANS Engine Version 1.3.4.9.beta"

/*-----------------------------------------------------------------------*/
// User definable flags include the following:

// ** Text only TTNANS compilation (no VPR MS-Windows interface):

// #define _CONSOLE					// for MS-DOS
// #define _PURETEXT_				// even leaner text mode
// #define _AMIGA_					// some Workbench code

// ** Extra Debugging messages: 

// #define _DEBUG

// ** Axum (Graphics) program can be called from inside TTNANS:

// #define _AXUM_COMPATIBLE_

// ** Some attempt to have threads in VPR MS-Windows interface: 

// #define _USE_WIN32_VPR_THREAD_CODE_

// ** User defined random number generation routines:

// #define _MY_RANDOM_

// ** User defined min,max macros:

// #define _MY_MIN_AND_MAX_

// ** User defined itoa:

// #define _MY_ITOA_

// ** Memory access model:

   #define MEMORY_NORMAL                 /* all systems, malloc.         */

// ** Extra memory handling added by TTNANS memory functions:

//	#define MEMORYGUARDFLAG
//	#define MEMORYGUARDFLAG_DEBUG

/*-----------------------------------------------------------------------*/

#ifdef _PURETEXT_
#ifndef _CONSOLE
#define _CONSOLE
#endif
#endif

/*-----------------------------------------------------------------------*/

#ifdef _CONSOLE
#include "stdio.h"
#include "stdlib.h"
#undef _USE_WIN32_VPR_THREAD_CODE_
#endif

/*-----------------------------------------------------------------------*/

#ifdef _MY_MIN_AND_MAX_
#define max(x,y) ((x)>(y))?(x):(y)
#define min(x,y) ((x)<(y))?(x):(y)
#endif
/*-----------------------------------------------------------------------*/

#ifdef _MY_ITOA_
#include "ttngnu.h"
#endif

/*-----------------------------------------------------------------------*/

#ifdef MEMORY_NORMAL
 #define MSIZE_T size_t
 #define MEMORY_QUOTE "Classic C/C++ Malloc"
#endif

/*-----------------------------------------------------------------------*/

#endif

/*---------------------------------------------------- NotePad ------------
TTNANS source and program are NOT Public Domain.
TTNANS (c) 1994-1995 Vasilios N. Nikolaidis.
-------------------------------------------------------------------------*/






