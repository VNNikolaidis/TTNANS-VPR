#ifndef TTNPROS
#define TTNPROS

#include "tglobal.h"
#include "ttndef_s.h"

/*--------------------------------- extern Globals -------------------*/

#define TGBL ptg->
extern CTglobal * ptg;							// defined in ttnmain.c

/*--------------------------------------------------------------------*/

bool runerror(int,char *);

#endif
