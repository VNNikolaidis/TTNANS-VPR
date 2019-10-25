/* --------------------
   System Defs. ver.0.8
   --------------------
   Vasilis.N.Nikolaidis
   -------------------- */

#ifndef TTNDEF
#define TTNDEF

/*-----------------------------------------------------------------------*

Notes:

Quote of the day: For a definition of recursion, see recursion.

For multiple editors, tab size is shown below:

....X (no tab,X)
    X (tab,X)

Code starts here:
-------------------------------------------------------------------------*/

#define VERSION "TTNANS Version 0.9.55"

/*-----------------------------------------------------------------------*/
/* Must choose one computer port and memory allocation type by either    */
/* doing it here or using the compiler (-d) options.                     */

/* Choose ONE of the options below:                                      */

/* #define _AMIGA_     */
/* #define _MSDOS_     */  /* any text-based IBMPC system, OS2 & EasyWin */
/* #define _PURETEXT_  */
/* #define _MSWINDOWS_ */  /* ms-windows ttnans.                         */
/*-----------------------------------------------------------------------*/
/* Choose ONE of the options below:                                      */

/* #define MEMORY_NORMAL     */          /* all systems, malloc.         */
/* #define MEMORY_FARHEAP    */          /* IBM PC large model, faralloc.*/
/* #define MEMORY_GLOBALHEAP */          /* MS-windows, GlobalAlloc      */
/*-----------------------------------------------------------------------*/
/* #define MEMORYGUARDFLAG   */
/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSWINDOWS_
 #define FHANDLE FILE *
 #define MMAIN mmain
#else
 #include "ttnbool.hpp"
 #define FHANDLE FILE *
 #define MMAIN main
#endif

#ifdef _AMIGA_
 #include <float.h>
 #define LARGEDATA  FLT_MAX
 #define SMALLDATA -FLT_MAX
 #define max(x,y) ((x)>(y)?(x):(y))
 extern void randomize (void);
 extern int random (int);
 extern void itoa (int,char *,int);
#endif

/*-----------------------------------------------------------------------*/

#ifdef MEMORY_NORMAL
 #define MSIZE_T size_t
 #define MEMORY_QUOTE "Classic C/C++ Malloc"
#endif

#ifdef MEMORY_FARHEAP
 #define MSIZE_T unsigned long
 #define MEMORY_QUOTE "Borland C/C++ Far Heap"
#endif

#ifdef MEMORY_GLOBALHEAP
 #define MSIZE_T unsigned long  /* DWORD  */
 #define MEMORY_QUOTE "Win 16 Global Heap"
#endif

/*-----------------------------------------------------------------------*/
/* choose DATA type here: (uncomment ONE option below)                   */

/*-- (option float) -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  --*/


#define DATA float
#define DATAFORMAT "%f"
#define DATADESCRI "float"
#ifndef LARGEDATA
 #define LARGEDATA  (float)(+34000000000000000000000000000000.0)
 #define SMALLDATA  (float)(-34000000000000000000000000000000.0)
#endif

/*-- (option double)-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  --*/

/*
#define DATA double
#define DATAFORMAT   "%lf"
#define DATADESCRI   "double"
#ifndef LARGEDATA
 #define LARGEDATA  (double)(+34000000000000000000000000000000.0)
 #define SMALLDATA  (double)(-34000000000000000000000000000000.0)
#endif
*/

/*-- (option long double) -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  --*/

/*
#define DATA long double
#define DATAFORMAT   "%Lf"
#define DATADESCRI   "long double"
#ifndef LARGEDATA
 #define LARGEDATA  (long double)(+34000000000000000000000000000000.0)
 #define SMALLDATA  (long double)(-34000000000000000000000000000000.0)
#endif
*/

/*-- (option interval) -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  --*/

/*
#include "interval/interval.hpp"
#define DATA interval - not yet implemented
*/

/*-----------------------------------------------------------------------*/

#include "ttndef_s.hpp"
#include "ttndef_n.hpp"
#include "ttnui.hpp"

#endif

/*---------------------------------------------------- NotePad ------------
TTNANS source and program are NOT Public Domain.
TTNANS (c) 1994-1995 Vasilios N. Nikolaidis.
-------------------------------------------------------------------------*/
