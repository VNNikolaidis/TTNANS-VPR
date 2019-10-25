#ifndef TTNPROS
#define TTNPROS

#include "ttndef_s.hpp"
#include "ttnbool.hpp"
/*--------------------------------- extern Globals -------------------*/

/* defined in ttnmain.c: */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

extern char prbfname[FILENAMELENGTH];
                              /* Current Problem description filename.*/
extern BOOL prb_loaded;       /* True if a problem is loaded.         */
extern BOOL ANS_run_success;  /* True if an ANS has just completed    */
                              /* succesfully.                         */

extern BOOL ANS_run_success;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

extern BOOL no_error;
extern BOOL runerror(int,char *);

/*--------------------------------------------------------------------*/

#endif
