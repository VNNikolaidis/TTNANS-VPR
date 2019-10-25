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

#include "ttndef.h"
#include "ttnpros.h"

#include <time.h>
#include <stdlib.h>

#include "ttnmemor.h"
#include "ttnmath.h"

#include "ttnui.h"

extern void randomize (void);
extern int random (int);

/* All Order.... Algorithms return if number of possible combinations     */
/* and actually perform an ordering only if takeaction == true.           */
/*------------------------------------------------------------------------*/
/* dataset: 2-d Array (rows x cols) to be ordered. ordering: 1-d array of */
/* nfirst items, stores indexes of (first,second,...,nfirst-th) dataset   */
/* items accoding to order. Note: Both arrays are NOT malloced here. No   */
/* change takes place in dataset here.                                    */

int OrderByDistance(bool takeaction,
                    DATA **dataset,
                    int rows,
                    int cols,
                    int ordering[], int nfirst)
{
int k,i,j;
DATA dist,maxdist;
DATA ** Distance;

int maxdistitem1,maxdistitem2;
bool * ordered;

static bool showinfo = true;

if(TGBL no_error)
 {
 if(takeaction)
  {
  mprintf("Ordering: Most Distant.\n");
  mprintf(" \n");
  mhintclear();
  mhintf(showinfo,"This algorithm determines an ordering of items in a\n");
  mhintf(showinfo,"(n x m) dataset according to the following scheme:\n");
  mhintf(showinfo," \n");
  mhintf(showinfo,"a. The first two items in the ordering are those with\n");
  mhintf(showinfo,"   maximum Euclidean Distance.\n");
  mhintf(showinfo,"b. The k-th item is the one with max Euclidean Distance\n");
  mhintf(showinfo,"   from all (k-1) items already ordered.\n");
  mhintf(showinfo," \n");
  mhintf(showinfo,"Note: If all items are colinear only the first two are \n");
  mhintf(showinfo,"      ordered in a non-ambiguous way.\n");
  mhintf(showinfo," \n");
  showinfo=false;
  
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
  if(TGBL no_error)
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

   ordered=(bool *)MMalloc(rows*sizeof(bool)); /* Keeps track of items already */
                                               /* ordered, to avoid conflicts  */
   if((TGBL no_error))                                /* when all points are colinear */
    {
    for(i=0;i<rows;i++) ordered[i]=false;
     ordered[ordering[0]]=true;
    ordered[ordering[1]]=true;

    for(k=2;k<nfirst;k++)
     {
     maxdist=0;
     maxdistitem1=-1;
      for(i=0;i<rows;i++)
       {
       if(ordered[i]==false)
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
      ordered[maxdistitem1]=true;
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
                   (bool takeaction,
                    DATA **dataset,
                    int rows,
                    int cols,
                    int ordering[], int nfirst)
{
int k,i,j;
DATA dist,maxdist;

int maxdistitem1,maxdistitem2;
bool * ordered;

static bool showinfo = true;

if((TGBL no_error))
 {
 if(takeaction)
  {
  mprintf("Ordering: Most Distant (Low Memory Version).\n");
  mprintf(" \n");
  mhintclear();
  mhintf(showinfo,"This algorithm determines an ordering of items in a\n");
  mhintf(showinfo,"(n x m) dataset according to the following scheme:\n");
  mhintf(showinfo," \n");
  mhintf(showinfo,"a. The first two items in the ordering are those with\n");
  mhintf(showinfo,"   maximum Euclidean Distance.\n");
  mhintf(showinfo,"b. The k-th item is the one with max Euclidean Distance\n");
  mhintf(showinfo,"   from all (k-1) items already ordered.\n");
  mhintf(showinfo," \n");
  mhintf(showinfo,"Note: If all items are colinear only the first two are \n");
  mhintf(showinfo,"      ordered in a non-ambiguous way.\n");
  mhintf(showinfo," \n");
  showinfo=false;

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

  if((TGBL no_error))
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

   ordered=(bool *)MMalloc(rows*sizeof(bool)); /* Keeps track of items already */
                                               /* ordered, to avoid conflicts  */
   if((TGBL no_error))                                /* when all points are colinear */
    {
    for(i=0;i<rows;i++) ordered[i]=false;
     ordered[ordering[0]]=true;
    ordered[ordering[1]]=true;

    mstarttick("<Ordering next items>");
    for(k=2;k<nfirst;k++)
     {
     mtick(k,nfirst);
     maxdist=0;
     maxdistitem1=-1;
      for(i=0;i<rows;i++)
       {
       if(ordered[i]==false)
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
      ordered[maxdistitem1]=true;
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

int OrderByDistanceStartingMeanLowMemory
                   (bool takeaction,
                    DATA **dataset,
                    int rows,
                    int cols,
                    int ordering[], int nfirst)
{
int k,i,j;
DATA dist,maxdist,mindist;

int maxdistitem1,maxdistitem2,closesttomeanitem;
bool * ordered;

static bool showinfo = true;

DATA * mean;

if((TGBL no_error))
 {
 if(takeaction)
  {
  mprintf("Ordering: Most Distant Starting with Closest to Mean (Low Memory Version).\n");
  mprintf(" \n");
  mhintclear();
  mhintf(showinfo,"This algorithm determines an ordering of items in a\n");
  mhintf(showinfo,"(n x m) dataset according to the following scheme:\n");
  mhintf(showinfo," \n");
  mhintf(showinfo,"a. The first item is the one closest to mean.\n");
  mhintf(showinfo," \n");
  mhintf(showinfo,"b. The k-th item is the one with max Euclidean Distance\n");
  mhintf(showinfo,"   from all (k-1) items already ordered.\n");
  mhintf(showinfo," \n");
  showinfo=false;

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

  mprintf("Now ordering %d-most distant items starting with closest to mean in a %dx%d array.\n",nfirst,rows,cols);

/* at this point we know rows >= 2. */

  mprintf("Ordering...\n");

  if((TGBL no_error))
   {

/* Do it */

   mean = MMalloc1dDATA(cols);
   if((TGBL no_error))
    {
    mstarttick("<Finding record closest to mean>");
    MeanVector(dataset, rows, cols, mean);
    mindist = LARGEDATA;
    closesttomeanitem=-1; 
    for(i=0;i<rows;i++)
     {
	 dist = EuclideanDistance(dataset[i], mean, cols);
     if(dist < mindist)
	  {
      mindist = dist;
	  closesttomeanitem = i; 
      }
     mtick(i,rows);
     }
    mendtick();
    }

   MFree(mean);   

   if((NOT (TGBL no_error)) OR (closesttomeanitem==-1)) 
    {
    mprintf("Can't continue.\n");
    return 0;
    }

   mprintf("Record closest to mean is row # %d.\n",closesttomeanitem);
   maxdistitem1 = closesttomeanitem;

   mstarttick("<Finding 2nd (most distant) item>");
   maxdist=0;
   for(i=0;i<rows;i++)
    {
    if((dist=EuclideanDistance(dataset[maxdistitem1],dataset[i],cols))>maxdist)
     {
     maxdist=dist;
     maxdistitem2=i;
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

   ordered=(bool *)MMalloc(rows*sizeof(bool)); /* Keeps track of items already */
                                               /* ordered, to avoid conflicts  */
   if((TGBL no_error))						   /* when all points are colinear */
    {
    for(i=0;i<rows;i++) ordered[i]=false;
     ordered[ordering[0]]=true;
    ordered[ordering[1]]=true;

    mstarttick("<Ordering next items>");
    for(k=2;k<nfirst;k++)
     {
     mtick(k,nfirst);
     maxdist=0;
     maxdistitem1=-1;
      for(i=0;i<rows;i++)
       {
       if(ordered[i]==false)
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
      ordered[maxdistitem1]=true;
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

int OrderDistanceFromCenter(bool takeaction,
							DATA **dataset,
							int rows,
							int cols,
							int ordering[])

{
static TRISTATE closestfirst = UNDEFINED;
DATA * Distance;
DATA * Zero;
bool * Ordered;
int i,j;
DATA dist;
int  item;
static bool showinfo = true;

if((TGBL no_error))
 {
 if(takeaction)
  {
  mprintf("Ordering: Distance from Center.\n");
  mprintf(" \n");
  mhintclear();
  mhintf(showinfo,"This algorithm determines an ordering of items in a\n");
  mhintf(showinfo,"(n x m) dataset according to their distance from the.\n");
  mhintf(showinfo,"center (0,0,...,0) in the %d dimentional space",cols);
  mhintf(showinfo," \n");

  showinfo=false;
 
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
   closestfirst=(int)mrequest_yn("Place items closest to center first?");

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
  Ordered=(bool *)MMalloc(rows*sizeof(bool));

  if((TGBL no_error))
   {
   for(i=0;i<cols;i++) Zero[i]=0.0;
   for(i=0;i<rows;i++)
    {
    Distance[i]=EuclideanDistance(dataset[i],Zero,cols);
    Ordered[i]=false;
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
      if((Ordered[j]==false)&&(Distance[j]<=dist))
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
     Ordered[item]=true;
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

int OrderDistanceFromMean(bool takeaction,
			    DATA **dataset,
			    int rows,
			    int cols,
			    int ordering[])
{
static TRISTATE closestfirst=UNDEFINED;
DATA * Distance;
DATA * mean;
DATA * transposedcol;
bool * Ordered;
int i,j;
DATA dist;
int  item;
static bool showinfo = true;

if((TGBL no_error))
 {
 if(takeaction)
  {
  mprintf("Ordering: Distance from Mean.\n");
  mprintf(" \n");
  mhintclear();
  mhintf(showinfo,"This algorithm determines an ordering of items in a\n");
  mhintf(showinfo,"(n x m) dataset according to their distance from the\n");
  mhintf(showinfo,"mean in the %d dimentional space.\n",cols);
  showinfo=false;

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
  Ordered=(bool *)MMalloc(rows*sizeof(bool));
  transposedcol=MMalloc1dDATA(rows);

  if((TGBL no_error))
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
    Ordered[i]=false;
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
      if((Ordered[j]==false)&&(Distance[j]<=dist))
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
     Ordered[item]=true;
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

int OrderNoChange(bool takeaction,int r, int ordering[])
{
int i;

if(takeaction) for(i=0;i<r;i++) ordering[i]=i;
return 1;
}

/*-----------------------------------------------------------------------*/

int OrderArbitrary(bool takeaction,int r, int ordering[])
{
int i,j;
bool * ordered;

if(takeaction)
 {
 ordered=(bool *)MMalloc(r*sizeof(bool)); /* Keeps track of items already */
                                          /* ordered, to avoid conflicts. */
 for(j=0;j<r;j++)
  ordered[j]=false;

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
  ordered[j]=true;
  }

 MFree(ordered);
 }
return 1;
}

/*------------------------------------------------------------------------*/

int OrderRandomOldVersion(bool takeaction,int r, int ordering[], bool get_num_combs)
{
static int times = -1;
int i,j;
bool * ordered;

if(get_num_combs)
  {
  if(times==-1)
   {
   mprintf("Number of random runs to be performed is not set.\n");
   mprintf("Please select number of runs to be performed whenever\n");
   mprintf("the random order option is called.\n");
   mprintf("Note: number of random runs remains constant once defined.\n");
   times=mrequest_int("Number of random runs ");
   }
  else
   return times;
  }

if(takeaction)
 {
 ordered=(bool *)MMalloc(r*sizeof(bool)); /* Keeps track of items already */
                                          /* ordered, to avoid conflicts. */
 for(j=0;j<r;j++)
  ordered[j]=false;
 randomize();

 for(i=0;i<r;i++)
  {
  do
   {
   j=random(r);                           /* ok, this is cruel,I know!!.  */
   }
  while(ordered[j]);
  ordering[i]=j;
  ordered[j]=true;
  }
 MFree(ordered);
 }
return times;
}

/*------------------------------------------------------------------------*/

int OrderRandom(bool takeaction,int r, int ordering[], bool get_num_combs)
{
static int times = -1;
static bool ask_for_old_version = true;
static bool use_old_version = false;

if(ask_for_old_version)
 {
 use_old_version = mrequest_yn("Use original (old) version of Random ordering (select No to used new faster version - you will not be asked again)?");
 ask_for_old_version = false;
 }

if(use_old_version) return OrderRandomOldVersion(takeaction,r,ordering,get_num_combs);

int i,j;
bool * ordered;

if(get_num_combs)
  {
  if(times==-1)
   {
   mprintf("Number of random runs to be performed is not set.\n");
   mprintf("Please select number of runs to be performed whenever\n");
   mprintf("the random order option is called.\n");
   mprintf("Note: number of random runs remains constant once defined.\n");
   times=mrequest_int("Number of random runs ");
   }
  else
   return times;
  }

if(takeaction)
 {
 ordered=(bool *)MMalloc(r*sizeof(bool)); /* Keeps track of items already */
                                          /* ordered, to avoid conflicts. */
 for(j=0;j<r;j++)  ordered[j]=false;
 randomize();

 int remainingunordered = r;
 int x=0;

 while(remainingunordered>0)
	{
    bool found = false;
    int unorderedpick = (random(5*remainingunordered)%remainingunordered)+1;
	int unorderedfound=0;
	for(int i=0;(i<r)&&(!found);i++)
	   {
	   if(!ordered[i])unorderedfound++;
	   if(unorderedfound==unorderedpick)
		{
		found = true;
		j=i;
		}
	   }

	if(!found) 
		mprintf("Warning: Random ordering failed!\n");

    if(ordered[j]) 
	 {
     mprintf("Warning: Unexpected condition when random ordering!\n");
	 }
	else
     {
	 ordering[x]=j;
	 x++;
	 ordered[j]=true;
	 remainingunordered--;
	 }
	}
 MFree(ordered);
 }
return times;
}

/*------------------------------------------------------------------------*/

int OrderSort(bool takeaction,DATA **dataset,int rows,int cols,
              int ordering[],bool direction, int selection,
              bool get_num_combs)

{
static int sel;
static int times;
int i,j,tp,otp;
DATA tv;
bool * ordered;

if(get_num_combs==true)
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

if(takeaction==true)
 {
 ordered=(bool *)MMalloc(rows*sizeof(bool));

 for(j=0;j<rows;j++)
  ordered[j]=false;

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
    case true : if((!ordered[j])&&(dataset[j][sel]<tv))
                 {
                 tv=dataset[j][sel];
                 tp=j;
                 }
                break;
    case false: if((!ordered[j])&&(dataset[j][sel]>tv))
                 {
                 tv=dataset[j][sel];
                 tp=j;
                 }
                break;
    }
   }

  if(otp==tp) tp=i;

  ordering[i]=tp;
  ordered[tp]=true;
  }
 MFree(ordered);
 }
return times;
}

/*------------------------------------------------------------------------*/

int OrderAllCombinations(bool takeaction,int rows, int ordering [], int selection)
{
unsigned long ul;

ul=Factorial((unsigned long)rows);

if(takeaction)
 {
 if(selection>=ul)
  mprintf("All combinations: Selection of %d invalid.\n",selection);

 mprintf("There are many (%ld) combinations, I refuse to do them!\n",ul);
 mprintf("Note: No Reordering.\n");
 OrderNoChange(takeaction,rows,ordering);
 }
return (int) 1;
}

/*------------------------------------------------------------------------*/

