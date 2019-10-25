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

extern void *  MMalloc (MSIZE_T s);
extern void    MFree (void * p);        /* does not NULL p. */
extern void    MFreeAll(void);
extern DATA *  MMalloc1dDATA(int s);
extern DATA ** MMalloc2dDATA (int r, int c);
extern void    MFree2dDATA (DATA ** dp, int r);
extern void    Copy2dDATASet(DATA ** source,DATA **dest,int rows,int cols);
extern int **  MMalloc2dint (int r, int c);
extern void    MFree2dint (int ** dp, int r);

#endif
