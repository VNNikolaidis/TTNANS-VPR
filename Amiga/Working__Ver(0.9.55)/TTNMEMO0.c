/*
   -------------------
   TTNANS:
   TTNMEMOR.C ver.0.01
   -------------------
   V.Nikolaidis
   --------------------------
   MSWindows Memory Utilities
   --------------------------
*/

#include "ttndef.hpp"

#ifdef _MSWINDOWS_
 #include <windows.h>
 #include <windowsx.h>
#else
 #include "ttnbool.hpp"
#endif

#include "ttnpros.hpp"

/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

#ifdef MEMORY_GLOBALHEAP
#ifdef MEMORYGUARDFLAG

#define MRec struct MREC

MRec
 {
 HGLOBAL mhandle;
 void * mallocp;
 int  id;
 MRec * prev;
 MRec * next;
 };

MRec * MRecLIST = NULL;
int countmalloc=0;
int countfree=0;

/*--------------------------------------------------------------------*/

void * MMalloc (MSIZE_T s)
{
void * p=NULL;
HGLOBAL ph;
MRec *m,*m1,*m2;

if(no_error)
 {
 if((ph=GlobalAlloc(GPTR,s))==NULL)
   {
   runerror(MEMORYERR,"Cannot allocate global heap memory.");
   return (void *)NULL;
   }

 if((m=(MRec *)malloc(sizeof(MRec)))==NULL)
   {
   runerror(MEMORYERR,"Cannot allocate heap memory.");
   GlobalFree(ph);
   return (void *)NULL;
   }

 p=(void *)GlobalLock(ph);
 if(p==NULL)
   {
   runerror(MEMORYERR,"Cannot lock global heap memory.");
   free(m);
   GlobalFree(ph);
   return (void *)NULL;
   }

 m->mallocp=p;
 m->mhandle=ph;
 m->id=countmalloc;
 m->prev=NULL;
 m->next=NULL;

 if(MRecLIST==NULL)
  MRecLIST=m;
 else
  {
  m1=m2=MRecLIST;
  while(m2!=NULL)
   {
   m1=m2;
   m2=m2->next;
   }
  m1->next=m;
  m->prev=m1;
  }

 countmalloc++;
 }

return (void *)p;
}

/*--------------------------------------------------------------------*/

void MFree (void * p)  
{
BOOL found=FALSE;
MRec * m1;

if(p==NULL)
 {
 runerror(NULPTRERR,"Cannot free NULL pointer.");
 return;
 }

m1=MRecLIST;

if(m1==NULL)
 {
 runerror(NULPTRERR,"Cannot free. Memory list is empty.");
 return;
 }

while((!found)&&(m1!=NULL))
 {
 if(p==(void *)(m1->mallocp))
  {
  found=TRUE;
  if(m1==MRecLIST)
   MRecLIST=m1->next;
  if(m1->prev!=NULL)
   m1->prev->next=m1->next;
  if(m1->next!=NULL)
   m1->next->prev=m1->prev;

  GlobalUnlock(m1->mhandle);
  GlobalFree(m1->mhandle);
  /* mprintf("Free id_%d\n",m1->id); */
  free(m1);
  countfree++;
  }
 m1=m1->next;
 }

if(!found) runerror(MEMGRDERR,"Cannot free. Memory is not registered.");
}

/*--------------------------------------------------------------------*/

void MFreeAll(void)
{
MRec *m1,*m2;

mprintf(" \n\n");
mprintf("------------------------------------------------\n");
mprintf("Number of MMallocs=%d, Number of MFrees=%d.\n",
         countmalloc,countfree);
mprintf("Freeing any remaining memory allocations.\n");
mprintf("A MemoryGuard Error now indicates that   \n");
mprintf("some memory was not properly freed.      \n");
mprintf("------------------------------------------------\n");

m2=MRecLIST;
while(m2!=NULL)
  {
   m1=m2;
   m2=m1->next;
   mprintf("@MMalloc_id_%d.\n",m1->id);
   runerror(MEMGRDERR,"Found memory not properly freed");
   GlobalUnlock(m1->mhandle);
   GlobalFree(m1->mhandle);
   free(m1);
  }

mprintf("------------------------------------------------\n");
mprintf("Done, all MemoryGuard registered memory is free.\n");
mprintf("------------------------------------------------\n");
}


/*--------------------------------------------------------------------*/

#endif /* MEMORYGUARDFLAG */

/*--------------------------------------------------------------------*/

unsigned long mm=0;
int moperation=0;

void * MMalloc (MSIZE_T s)
{
void * p=NULL;
HGLOBAL ph;

if(no_error)
 {
 if((ph=GlobalAlloc(GPTR,s))==NULL)
   {
   mprintf("Attempt to allocate %lu bytes failed.(Free Global:%lu bytes)",mm,GetFreeSpace((UINT)0));
   runerror(MEMORYERR,"Cannot allocate global heap memory.");
   return (void *)NULL;
   }

 p=(void *)GlobalLock(ph);
 if(p==NULL)
   {
   mprintf("Attempt to allocate %lu bytes failed, memory operation #%d.\n",mm,moperation);
   runerror(MEMORYERR,"Cannot lock global heap memory.");
   GlobalFree(ph);
   return (void *)NULL;
   }
 mm=mm+GlobalSize(ph);
 moperation++;
 }
return p;
}

/*--------------------------------------------------------------------*/

void MFree (void * p)
{
HGLOBAL hp;

if(p==NULL)
 {
 runerror(NULPTRERR,"Cannot free NULL pointer.");
 return;
 }

if((hp=GlobalPtrHandle(p))==NULL)
 {
 runerror(NULPTRERR,"Cannot free, handle does not exist.");
 return;
 }

mm=mm-GlobalSize(hp);
mprintf("Freed (%lu)\n",mm);

GlobalUnlock(hp);
GlobalFree(hp);
moperation--;
}

/*--------------------------------------------------------------------*/

void MFreeAll(void)
{
if(moperation)
 runerror(MEMORYERR,"Non-zero memory allocation count.");
}

/*--------------------------------------------------------------------*/

#endif /* MEMORY_GLOBALHEAP */

#ifdef MEMORY_FARHEAP

/*--------------------------------------------------------------------*/

#include <alloc.h>

unsigned long int mcount=0;

/*--------------------------------------------------------------------*/

void * MMalloc (MSIZE_T s)
{
void * p;

/* mprintf("Allocating %ld bytes (%ldK).\n",s,s/1024);                */

if(no_error)
 {
 if(s>=65535UL)
  mprintf("MMalloc Warning: requested allocation memory block > 64K.\n");

/*  note: in BC 4.0, size_t is defined as unsigned (0..65535).        */

 if((p=(void *)farmalloc(s))==NULL)
   {
    runerror(MEMORYERR,"Cannot allocate (far heap) memory.");
    return NULL;
   }
 mcount++;
 }
return p;
}
/*--------------------------------------------------------------------*/

void MFree (void * p)
{
if(p!=NULL)
 {
 farfree(p);
 mcount--;
 }
}
/*--------------------------------------------------------------------*/

void MFreeAll(void)
{
if(mcount) runerror(MEMORYERR,"Non-Zero memory allocation count.");
}

/*--------------------------------------------------------------------*/
#endif  /* MEMORY_FARHEAP */
/*--------------------------------------------------------------------*/

