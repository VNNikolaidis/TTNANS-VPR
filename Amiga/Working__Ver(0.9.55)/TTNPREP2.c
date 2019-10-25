/*
  ---------------------
  TTNANS:
  TTNPREP2.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Data Preprocessing 2
  Reorder Algorithms
  ---------------------

*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include <time.h>
#include <stdlib.h>

#include "TTNMEMOR.HPP"
#include "TTNMATH.HPP"

/* All Order.... Algorithms return if number of possible combinations     */
/* and actually perform an ordering only if takeaction == TRUE.           */
/*------------------------------------------------------------------------*/
/* dataset: 2-d Array (rows x cols) to be ordered. ordering: 1-d array of */
/* nfirst items, stores indexes of (first,second,...,nfirst-th) dataset   */
/* items accoding to order. Note: Both arrays are NOT malloced here. No   */
/* change takes place in dataset here.                                    */

int OrderByDistance(BOOL takeaction,
                    DATA **dataset,
                    int rows,
                    int cols,
                    int ordering[], int nfirst)
{
int k,i,j;
DATA dist,maxdist;
DATA ** Distance;

int maxdistitem1,maxdistitem2;
BOOL * ordered;

static BOOL show_info_obd = TRUE;

if(no_error)
 {
 if(takeaction)
  {
  if(show_info_obd)
   {
   mprintf("Order By Distance:\n");
   mprintf("__________________\n");
   mprintf("\n");
   mprintf("This algorithm determines an ordering of items in a\n");
   mprintf("(n x m) dataset according to the following scheme.\n");
   mprintf("\n");
   mprintf("a. The first two items in the ordering are those with\n");
   mprintf("   maximum Euclidean Distance.\n");
   mprintf("b. The k-th item is the one with max Euclidean Distance\n");
   mprintf("   from all (k-1) items already ordered.\n");
   mprintf("\n");
   mprintf("Note: If all items are colinear only the first two are \n");
   mprintf("      ordered in a non-ambiguous way.\n");
   mprintf("\n");
   show_info_obd=FALSE;
   }

  if((nfirst>rows)||
     (rows<1)||
     (nfirst<1)||
     (cols<1))
   {
   mprintf("Warning: Request for %d-first items invalid. (%d x %d).\n",nfirst,rows,cols);
   return 0;
   }

  if((nfirst==1)&&(rows==1))
   {
   ordering[0]=0;
   return 1;
   }

  mprintf("Now ordering %d-most distant items in a %dx%d array.\n",nfirst,rows,cols);
  mprintf("(Required memory: %lu K (aprox.)).\n",
           (((long unsigned int)rows*rows*sizeof(DATA))/1024));

/* at this point we know rows >= 2. */

  mprintf("Ordering...\n");

/* First Calculate All Distances */


  Distance=MMalloc2dDATA(rows,rows);
  if(no_error)
   {
   for(i=0;i<rows;i++)
    {
    Distance[i][i]=0;
    for(j=i;j<rows;j++)
     Distance[i][j]=Distance[j][i]=EuclideanDistance(dataset[i],dataset[j],cols);
    }

/* Then do it */

   maxdist=0;

   for(i=0;i<rows;i++)
   for(j=i+1;j<rows;j++)
    {
    if(Distance[i][j]>maxdist)
     {
     maxdist=Distance[i][j];
     maxdistitem1=i;
     maxdistitem2=j;
     }
    }

   if(nfirst==1)
    {
    mprintf("Note: 1-first item in a %d-row array is ambigious.\n",rows);
    ordering[0]=maxdistitem1;
    return 1;
    }

/* at this point we know nfirst >= 2 */

   ordering[0]=maxdistitem1;
   ordering[1]=maxdistitem2;

   ordered=(BOOL *)MMalloc(rows*sizeof(BOOL)); /* Keeps track of items already */
                                               /* ordered, to avoid conflicts  */
   if(no_error)                                /* when all points are colinear */
    {
    for(i=0;i<rows;i++) ordered[i]=FALSE;
     ordered[ordering[0]]=TRUE;
    ordered[ordering[1]]=TRUE;

    for(k=2;k<nfirst;k++)
     {
     maxdist=0;
     maxdistitem1=-1;
      for(i=0;i<rows;i++)
       {
       if(ordered[i]==FALSE)
        {
        dist=0;
        for(j=0;j<k;j++)
         {
         dist+=Distance[i][ordering[j]];
         if(dist>=maxdist)
          {
          maxdist=dist;
          maxdistitem1=i;
          }
         }
        }
       }
     if((maxdistitem1==-1)||(ordered[maxdistitem1]))
      mprintf("Conflict!! Check Algorithm.\n");
     else
      {
      ordering[k]=maxdistitem1;
      ordered[maxdistitem1]=TRUE;
      }
     }
    MFree(ordered);
    }
   MFree2dDATA(Distance,rows);
   mprintf("Done.\n");
   return 1;
   }
  return 0;
  }
 return 1;  /* One possible combination */
 }
return 0;
}

/*------------------------------------------------------------------------*/
/* dataset: 2-d Array (rows x cols) to be ordered. ordering: 1-d array of */
/* nfirst items, stores indexes of (first,second,...,nfirst-th) dataset   */
/* items accoding to order. Note: Both arrays are NOT malloced here. No   */
/* change takes place in dataset here.                                    */

int OrderByDistanceLowMemory
                   (BOOL takeaction,
                    DATA **dataset,
                    int rows,
                    int cols,
                    int ordering[], int nfirst)
{
int k,i,j;
DATA dist,maxdist;

int maxdistitem1,maxdistitem2;
BOOL * ordered;

static BOOL show_info_obd = TRUE;

if(no_error)
 {
 if(takeaction)
  {
  if(show_info_obd)
   {
   mprintf("Order By Distance Low Memory Version:\n");
   mprintf("_____________________________________\n");
   mprintf("\n");
   mprintf("This algorithm determines an ordering of items in a\n");
   mprintf("(n x m) dataset according to the following scheme.\n");
   mprintf("\n");
   mprintf("a. The first two items in the ordering are those with\n");
   mprintf("   maximum Euclidean Distance.\n");
   mprintf("b. The k-th item is the one with max Euclidean Distance\n");
   mprintf("   from all (k-1) items already ordered.\n");
   mprintf("\n");
   mprintf("Note: If all items are colinear only the first two are \n");
   mprintf("      ordered in a non-ambiguous way.\n");
   mprintf("\n");
   show_info_obd=FALSE;
   }

  if((nfirst>rows)||
     (rows<1)||
     (nfirst<1)||
     (cols<1))
   {
   mprintf("Warning: Request for %d-first items invalid. (%d x %d).\n",nfirst,rows,cols);
   return 0;
   }

  if((nfirst==1)&&(rows==1))
   {
   ordering[0]=0;
   return 1;
   }

  mprintf("Now ordering %d-most distant items in a %dx%d array.\n",nfirst,rows,cols);

/* at this point we know rows >= 2. */

  mprintf("Ordering...\n");

  if(no_error)
   {

/* Do it */

   mstarttick("<Ordering first 2 items>");
   maxdist=0;
   for(i=0;i<rows;i++)
    {
    for(j=i+1;j<rows;j++)
     {
     if((dist=EuclideanDistance(dataset[i],dataset[j],cols))>maxdist)
      {
      maxdist=dist;
      maxdistitem1=i;
      maxdistitem2=j;
      }
     }
    mtick(i,rows);
    }
   mendtick();

   if(nfirst==1)
    {
    mprintf("Note: 1-first item in a %d-row array is ambigious.\n",rows);
    ordering[0]=maxdistitem1;
    return 1;
    }

/* at this point we know nfirst >= 2 */

   ordering[0]=maxdistitem1;
   ordering[1]=maxdistitem2;

   ordered=(BOOL *)MMalloc(rows*sizeof(BOOL)); /* Keeps track of items already */
                                               /* ordered, to avoid conflicts  */
   if(no_error)                                /* when all points are colinear */
    {
    for(i=0;i<rows;i++) ordered[i]=FALSE;
     ordered[ordering[0]]=TRUE;
    ordered[ordering[1]]=TRUE;

    mstarttick("<Ordering next items>");
    for(k=2;k<nfirst;k++)
     {
     mtick(k,nfirst);
     maxdist=0;
     maxdistitem1=-1;
      for(i=0;i<rows;i++)
       {
       if(ordered[i]==FALSE)
        {
        dist=0;
        for(j=0;j<k;j++)
         {
         dist+=EuclideanDistance(dataset[i],dataset[ordering[j]],cols);
         if(dist>=maxdist)
          {
          maxdist=dist;
          maxdistitem1=i;
          }
         }
        }
       }
     if((maxdistitem1==-1)||(ordered[maxdistitem1]))
      mprintf("Conflict!! Check Algorithm.\n");
     else
      {
      ordering[k]=maxdistitem1;
      ordered[maxdistitem1]=TRUE;
      }
     }
    mendtick();
    MFree(ordered);
    }

   mprintf("Done.\n");
   return 1;
   }
  return 0;
  }
 return 1;  /* One possible combination */
 }
return 0;
}


/*------------------------------------------------------------------------*/
/* dataset: 2-d Array (rows x cols) to be ordered. ordering: 1-d array of */
/* nfirst items, stores indexes of (first,second,...,nfirst-th) dataset   */
/* items accoding to order. Note: Both arrays are NOT malloced here. No   */
/* change takes place in dataset here.                                    */

int OrderDistanceFromCenter(BOOL takeaction,
			    DATA **dataset,
                            int rows,
                            int cols,
                            int ordering[])

{
static BOOL closestfirst=UNDEFINED;
DATA * Distance;
DATA * Zero;
BOOL * Ordered;
int i,j;
DATA dist;
int  item;
static BOOL show_info_obd = TRUE;

if(no_error)
 {
 if(takeaction)
  {
  if(show_info_obd)
   {
   mprintf("Order By Distance from Center:\n");
   mprintf("______________________________\n");
   mprintf("\n");
   mprintf("This algorithm determines an ordering of items in a\n");
   mprintf("(n x m) dataset according to their distance from the.\n");
   mprintf("center (0,0,...,0) in the %d dimentional space",cols);
   mprintf("\n");
   show_info_obd=FALSE;
   }

  if((rows<1)||
     (cols<1))
   {
   mprintf("Warning: Invalid ordering parameters.\n");
   return 0;
   }

  if(rows==1)
   {
   ordering[0]=0;
   return 1;
   }

  mprintf("Ready to order items in a %dx%d array.\n",rows,cols);

  if(closestfirst==UNDEFINED)
   closestfirst=mrequest_yn("Place items closest to center first?");

  mprintf("Items closest to the center (0,0,...,0) are ordered ");
  if(closestfirst)
   mprintf("first.\n");
  else
   mprintf("last.\n");

/* at this point we know rows >= 2. */

  mprintf("Ordering...\n");

/* First Calculate All Distances */

  Zero=(DATA *)MMalloc(cols*sizeof(DATA));
  Distance=(DATA *)MMalloc(rows*sizeof(DATA));
  Ordered=(int *)MMalloc(rows*sizeof(BOOL));

  if(no_error)
   {
   for(i=0;i<cols;i++) Zero[i]=0.0;
   for(i=0;i<rows;i++)
    {
    Distance[i]=EuclideanDistance(dataset[i],Zero,cols);
    Ordered[i]=FALSE;
    }

/* Then do it */

   for(i=0;i<rows;i++)
    {
    item=-1;
    if(closestfirst) dist=LARGEDATA;
    else             dist=0;

    for(j=0;j<rows;j++)
     {
     if(closestfirst)
      {
      if((Ordered[j]==FALSE)&&(Distance[j]<=dist))
       {
       dist=Distance[j];
       item=j;
       }
      }
     else
      {
      if((!Ordered[j])&&(Distance[j]>=dist))
       {
       dist=Distance[j];
       item=j;
       }
      }
     }
    if(item==-1)
     mprintf("Warning: No Item found.\n");
    else
     {
     ordering[i]=item;
     Ordered[item]=TRUE;
     }
    }
 
   MFree(Ordered);
   MFree(Distance);
   MFree(Zero);
   mprintf("Done.\n");
   return 1;
   }
  return 0;
  }
 return 1;  /* One possible combination */
 }
return 0;
}

/*------------------------------------------------------------------------*/
/* dataset: 2-d Array (rows x cols) to be ordered. ordering: 1-d array of */
/* nfirst items, stores indexes of (first,second,...,nfirst-th) dataset   */
/* items accoding to order. Note: Both arrays are NOT malloced here. No   */
/* change takes place in dataset here.                                    */

int OrderDistanceFromMean(BOOL takeaction,
			    DATA **dataset,
			    int rows,
			    int cols,
			    int ordering[])
{
static BOOL closestfirst=UNDEFINED;
DATA * Distance;
DATA * mean;
DATA * transposedcol;
BOOL * Ordered;
int i,j;
DATA dist;
int  item;
static BOOL show_info_obd = TRUE;

if(no_error)
 {
 if(takeaction)
  {
  if(show_info_obd)
   {
   mprintf("Order By Distance from Mean:\n");
   mprintf("____________________________\n");
   mprintf("\n");
   mprintf("This algorithm determines an ordering of items in a\n");
   mprintf("(n x m) dataset according to their distance from the.\n");
   mprintf("mean in the %d dimentional space",cols);
   mprintf("\n");
   show_info_obd=FALSE;
   }

  if((rows<1)||
     (cols<1))
   {
   mprintf("Warning: Invalid ordering parameters.\n");
   return 0;
   }

  if(rows==1)
   {
   ordering[0]=0;
   return 1;
   }

  mprintf("Ready to order items in a %dx%d array.\n",rows,cols);

  if(closestfirst==UNDEFINED)
   closestfirst=mrequest_yn("Place items closest to mean first?");

  mprintf("Items closest to the mean are ordered ");
  if(closestfirst)
   mprintf("first.\n");
  else
   mprintf("last.\n");

/* at this point we know rows >= 2. */

  mprintf("Ordering...\n");

/* First Calculate All Distances */

  mean=MMalloc1dDATA(cols);
  Distance=MMalloc1dDATA(rows);
  Ordered=(BOOL *)MMalloc(rows*sizeof(BOOL));
  transposedcol=MMalloc1dDATA(rows);

  if(no_error)
   {
   for(i=0;i<cols;i++)
    {
    for(j=0;j<rows;j++)
     transposedcol[j]=dataset[j][i];
    mean[i]=Mean(transposedcol,rows);
    }

   mprintf("Mean = [ ");
   for(i=0;i<cols;i++)
    {
    mprintf(DATAFORMAT,mean[i]);
    mprintf(" ");
    }
   mprintf("].\n");

   for(i=0;i<rows;i++)
    {
    Distance[i]=EuclideanDistance(dataset[i],mean,cols);
    Ordered[i]=FALSE;
    }

/* Then do it */

   for(i=0;i<rows;i++)
    {
    item=-1;
    if(closestfirst) dist=LARGEDATA;
    else             dist=0;

    for(j=0;j<rows;j++)
     {
     if(closestfirst)
      {
      if((Ordered[j]==FALSE)&&(Distance[j]<=dist))
       {
       dist=Distance[j];
       item=j;
       }
      }
     else
      {
      if((!Ordered[j])&&(Distance[j]>=dist))
       {
       dist=Distance[j];
       item=j;
       }
      }
     }
    if(item==-1)
     mprintf("Warning: No Item found.\n");
    else
     {
     ordering[i]=item;
     Ordered[item]=TRUE;
     }
    }

   MFree(Ordered);
   MFree(Distance);
   MFree(mean);
   MFree(transposedcol);

   mprintf("Done.\n");
   return 1;
   }
  return 0;
  }
 return 1;  /* One possible combination */
 }
return 0;
}

/*------------------------------------------------------------------------*/
/* This just makes an ordering from 0 to r.                               */

int OrderNoChange(BOOL takeaction,int r, int ordering[])
{
int i;

if(takeaction) for(i=0;i<r;i++) ordering[i]=i;
return 1;
}

/*-----------------------------------------------------------------------*/

int OrderArbitrary(BOOL takeaction,int r, int ordering[])
{
int i,j;
BOOL * ordered;

if(takeaction)
 {
 ordered=(BOOL *)MMalloc(r*sizeof(BOOL)); /* Keeps track of items already */
                                          /* ordered, to avoid conflicts. */
 for(j=0;j<r;j++)
  ordered[j]=FALSE;

 for(i=0;i<r;i++)
  {
  do
   {
   mprintf("Select item to be placed in n-th position (n=%d).\n",i);
   j=mrequest_int("Enter item number");
   if((j<0)||(j>=r)||(ordered[j])) mprintf("Item already placed or out of range. Re-select.\n");
   }
  while((j<0)||(j>=r)||(ordered[j]));
  ordering[i]=j;
  ordered[j]=TRUE;
  }

 MFree(ordered);
 }
return 1;
}

/*------------------------------------------------------------------------*/
int OrderRandom(BOOL takeaction,int r, int ordering[], BOOL get_num_combs)
{
static int times = -1;
int i,j;
BOOL * ordered;

if(get_num_combs)
  {
  if(times==-1)
   {
   mprintf("Number of random runs to be performed is not set.\n");
   mprintf("Please select number of runs to be perfomed whenever\n");
   mprintf("the random order option is called.\n");
   mprintf("Note: number of random runs remains constant once defined.\n");
   times=mrequest_int("Number of random runs ");
   }
  else
   return times;
  }

if(takeaction)
 {
 ordered=(BOOL *)MMalloc(r*sizeof(BOOL)); /* Keeps track of items already */
                                          /* ordered, to avoid conflicts. */
 for(j=0;j<r;j++)
  ordered[j]=FALSE;
 randomize();

 for(i=0;i<r;i++)
  {
  do
   {
   j=random(r);                           /* ok, this is cruel,I know!!.  */
   }
  while(ordered[j]);
  ordering[i]=j;
  ordered[j]=TRUE;
  }
 MFree(ordered);
 }
return times;
}

/*------------------------------------------------------------------------*/

int OrderSort(BOOL takeaction,DATA **dataset,int rows,int cols,
              int ordering[],BOOL direction, int selection,
              BOOL get_num_combs)

{
static int sel;
static int times;
int i,j,tp,otp;
DATA tv;
BOOL * ordered;

if(get_num_combs==TRUE)
 {
 if(mrequest_yn("Repeat sort on all descriptors?"))
  {
  times=cols;
  if(times==1)sel=0;
  }
 else
  {
  times=1;
  sel=-1;
  mprintf("Available colums : 0 to %d.\n",cols-1);
  while((sel<0)||(sel>=cols))sel=mrequest_int("Enter sort-key column)");
  }
 }

if(takeaction==TRUE)
 {
 ordered=(BOOL *)MMalloc(rows*sizeof(BOOL));

 for(j=0;j<rows;j++)
  ordered[j]=FALSE;

 if(times!=1)sel=selection;

 mprintf("Sorting...(selected %d).\n",sel);

 for(i=0;i<rows;i++)
  {
  if(direction)
   tv=LARGEDATA;
  else
   tv=SMALLDATA;

  otp=tp=-1;

  for(j=0;j<rows;j++)
   {
   switch(direction)
    {
    case TRUE : if((!ordered[j])&&(dataset[j][sel]<tv))
                 {
                 tv=dataset[j][sel];
                 tp=j;
                 }
                break;
    case FALSE: if((!ordered[j])&&(dataset[j][sel]>tv))
                 {
                 tv=dataset[j][sel];
                 tp=j;
                 }
                break;
    default   : mprintf("From Sort: WARNING! something is wrong.\n");
                break;
    }
   }

  if(otp==tp) tp=i;

  ordering[i]=tp;
  ordered[tp]=TRUE;
  }
 MFree(ordered);
 }
return times;
}

/*------------------------------------------------------------------------*/

int OrderAllCombinations(BOOL takeaction,int rows, int ordering [], int selection)
{
unsigned long ul;

ul=Factorial((unsigned long)rows);

if(takeaction)
 {
 if(selection>=ul)
  mprintf("All combinations: Selection of %d invalid.\n",selection);
 mprintf("There are many (%lu) combinations, I refuse to do them!\n",ul);
 mprintf("Note: No Reordering.\n");
 OrderNoChange(takeaction,rows,ordering);
 }
return (int) 1;
}

/*------------------------------------------------------------------------*/

