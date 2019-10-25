/* ---------------------
   ANS Other defs v.0.1
   ---------------------
   Vasilis.N.Nikolaidis
   --------------------- */

#ifndef TTNDEF_O
#define TTNDEF_O

/*-----------------------------------------------------------------------*/
#include <stdio.h>      //for FILE

#define FHANDLE FILE *
#define FILENAMELENGTH 2000

#define MAX_NUM_CLUSTERS 1000
#define MAX_CLUSTER_ID (MAX_NUM_CLUSTERS-1)

#define FLAG short

#define OR  ||
#define AND &&
#define NOT !

#define EQL  ==
#define NEQL !=

#define AT  *
#define REF &
#define PTR *
#define ADR &

#define TRISTATE  short
#define UNDEFINED -999

/*-----------------------------------------------------------------------*/
/* choose DATA type here: (uncomment ONE option below)                   */
/*-----------------------------------------------------------------------*/

/*-- (option float) -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  --*/


#define DATA float
#define DATAFORMAT   "%f"
#define DATAFORMAT_P "%7.4f"
#define DATADESCRI "float"
#ifndef LARGEDATA
 #define LARGEDATA  (float)(+34000000000000000000000000000000.0)
 #define SMALLDATA  (float)(-34000000000000000000000000000000.0)
#endif

/*-- (option double)-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  --*/

/*
#define DATA double
#define DATAFORMAT   "%lf"
#define DATAFORMAT_P "%7.6lf"
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
#define DATAFORMAT_P "%7.6Lf"
#define DATADESCRI   "long double"
#ifndef LARGEDATA
 #define LARGEDATA  (long double)(+34000000000000000000000000000000.0)
 #define SMALLDATA  (long double)(-34000000000000000000000000000000.0)
#endif
*/


#endif /* not defined TTNSDEF_O */

/*---------------------------------------------------- NotePad ------------
TTNANS source and program are NOT Public Domain.
TTNANS (c) 1994-1995 Vasilios N. Nikolaidis.
-------------------------------------------------------------------------*/
