/*
   -------------------
   TTNANS:
   TTNMEMOR.C &
   TTNMEMO0.C
   -------------------
   V.Nikolaidis
   ----------------------------------
   Memory Utilities
   ----------------------------------
*/

#ifndef TTNMEMORY
#define TTNMEMORY

 void *  MMalloc (MSIZE_T s);
 void    MFree (void * p);        /* does not NULL p. */
 void    MFreeAll(void);
 DATA *  MMalloc1dDATA(int s);
 DATA ** MMalloc2dDATA (int r, int c);
 void    MFree2dDATA (DATA ** dp, int r);
 void    Copy2dDATASet(DATA ** source,DATA **dest,int rows,int cols);
 int **  MMalloc2dint (int r, int c);
 void    MFree2dint (int ** dp, int r);

#endif
