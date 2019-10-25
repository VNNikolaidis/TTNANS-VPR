/*
   -------------------
   TTNANS:
   TTNMEMOR.C ver.0.01
   -------------------
   V.Nikolaidis
   ----------------------------------
   Memory Utilities
   MMalloc,MFree (normal mode,malloc)
   and Malloc2dDATA etc.
   ----------------------------------
*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#ifdef MEMORY_NORMAL
#ifdef MEMORYGUARDFLAG

#define MGUARD struct MEMORYGUARD

MGUARD
 {
 void * malloced;
 int  id;
 MGUARD * prev;
 MGUARD * next;
 };

MGUARD * MGUARDLIST = NULL;
int countmalloc=0;                    /* may want to change to 'long' */
int countfree=0;

/*--------------------------------------------------------------------*/

void * MMalloc (MSIZE_T s)
{
void * p=NULL;
MGUARD *m,*m1,*m2;

if(no_error)   /* if error has already occured don't add more allocs;*/
 {             /* works best if 'no_error' is checked after MMalloc. */
 if(
   ((p=(void *)malloc(s))==NULL)||
   ((m=(MGUARD *)malloc(sizeof(MGUARD)))==NULL)
   )
  {
   runerror(MEMORYERR,"Cannot allocate memory");
   return NULL;
  }

/* mprintf("Allocating id %d.\n",countmalloc); */

 m->malloced=p;
 m->id=countmalloc;
 m->prev=NULL;
 m->next=NULL;

 if(MGUARDLIST==NULL)
  MGUARDLIST=m;
 else
  {
  m1=m2=MGUARDLIST;
  for(;m2!=NULL;m2=m2->next) m1=m2;
  m1->next=m;
  m->prev=m1;
  }
 countmalloc++;
 }

return p;
}

/*--------------------------------------------------------------------*/

void MFree (void * p)  /* This is a call-by-value,it does not NULL p. */
{
BOOL found=FALSE;
MGUARD *m1;

if(p!=NULL)
 {
 m1=MGUARDLIST;
 for(;m1!=NULL;m1=m1->next)
  {
  if(m1->malloced==p)
   {
   found=TRUE;
   if(m1==MGUARDLIST)
     MGUARDLIST=m1->next;
   else
     m1->prev->next=m1->next;
   if(m1->next!=NULL)
      m1->next->prev=m1->prev;
   countfree++;
/* mprintf("Freeing id %d.\n",m1->id); */
   free(p);
   free(m1);
   }
  }
 }
else
 runerror(NULPTRERR,"Cannot free a NULL pointer.");

if(found!=TRUE) runerror(MEMGRDERR,"Free: memory is not memoryguard registered");
}


/*--------------------------------------------------------------------*/

void MFreeAll(void)
{
MGUARD *m1,*m2;

mprintf("------------------------------------------------\n");
mprintf("Number of MMallocs = %d.\n",countmalloc);
mprintf("Number of MFrees   = %d.\n",countfree);
mprintf("Freeing any remaining memory allocations.\n");
mprintf("A MemoryGuard Error now indicates that   \n");
mprintf("some memory was not properly freed.      \n");
mprintf("------------------------------------------------\n");

m2=MGUARDLIST;
while(m2!=NULL)
  {
   m1=m2;
   m2=m1->next;
   mprintf("@MMalloc_id_%d.\n",m1->id);
   runerror(MEMGRDERR,"Found memory not properly freed");
   free(m1->malloced);
   free(m1);
  }

mprintf("------------------------------------------------\n");
mprintf("Done, all MemoryGuard registered memory is free.\n");
mprintf("------------------------------------------------\n");
}

/*--------------------------------------------------------------------*/
#else /* #ifndef MEMORYGUARDFLAG  */
/*--------------------------------------------------------------------*/

void * MMalloc (MSIZE_T s)
{
void * p=NULL;
if(no_error)
 {
 if((p=(void *)malloc(s))==NULL)
  {
   runerror(MEMORYERR,"Cannot allocate memory.");
   return NULL;
  }
 }
return p;
}

/*--------------------------------------------------------------------*/

void MFree (void * p)
{
if(p!=NULL)
 {
 free(p);
 }
}

/*--------------------------------------------------------------------*/

void MFreeAll(void)
{
}

/*--------------------------------------------------------------------*/
#endif /* defined MEMORYGUARD */
#else  /* #ifndef MEMORY_NORMAL */
/*--------------------------------------------------------------------*/
extern void * MMalloc(MSIZE_T);                /* found in TTNMEMO0.C */
extern void MFree(void *);
extern void MFreeALL(void);
#endif /* MEMORY_NORMAL */

/*--------------------------------------------------------------------*/
/* Functions below are common to all memory allocation methods.       */
/*--------------------------------------------------------------------*/

DATA * MMalloc1dDATA(int s)
{
DATA * dp;
int i;

if(no_error)
 {
 if((dp=(DATA*)MMalloc((MSIZE_T)(s*sizeof(DATA))))==NULL)
    runerror(MEMORYERR,"No memory for 1-D Data Array.");
   else
    for(i=0;i<s;i++)
     dp[i]=(DATA)0;
 }
return dp;
}

/*--------------------------------------------------------------------*/

DATA ** MMalloc2dDATA (int r, int c)
{
DATA ** dp;
int i,j;

if(no_error)
 {
 if((dp=(DATA**)MMalloc((MSIZE_T)(r*sizeof(DATA *))))==NULL)
  runerror(MEMORYERR,"No memory for pointers to rows.");
 else
  for(i=0;((i<r)&&no_error);i++)
   {
   if((dp[i]=(DATA*)MMalloc((MSIZE_T)(c*sizeof(DATA))))==NULL)
    runerror(MEMORYERR,"No memory for rows.");
   else
    for(j=0;j<c;j++)
     dp[i][j]=(DATA)0;
   }
 }
return dp;
}

/*--------------------------------------------------------------------*/

void MFree2dDATA (DATA ** dp, int r)
{
int i;

if(dp!=NULL)
 {
 for(i=0;i<r;i++) MFree(dp[i]);
 MFree(dp);
 }
 else
 runerror(NULPTRERR,"");
}

/*--------------------------------------------------------------------*/

void Copy2dDATASet(DATA ** source,DATA **dest,int rows,int cols)
{
int i,j;
for(i=0;i<rows;i++)
 for(j=0;j<cols;j++)
  dest[i][j]=source[i][j];
}

/*--------------------------------------------------------------------*/

int ** MMalloc2dint (int r, int c)
{
int ** dp;
int i,j;

if (no_error)
 {
 if((dp=(int**)MMalloc((MSIZE_T)(r*sizeof(int *))))==NULL)
  runerror(MEMORYERR,"");
 else
  for(i=0;((i<r)&&no_error);i++)
   {
   if((dp[i]=(int*)MMalloc((MSIZE_T)(c*sizeof(int))))==NULL)
    runerror(MEMORYERR,"");
   else
    for(j=0;j<c;j++)
     dp[i][j]=(int)0;
   }
 }

return dp;
}

/*--------------------------------------------------------------------*/

void MFree2dint (int ** dp, int r)
{
int i;

if(dp!=NULL)
 {
 for(i=0;i<r;i++) MFree(dp[i]);
 MFree(dp);
 }
 else
 runerror(NULPTRERR,"");
}

