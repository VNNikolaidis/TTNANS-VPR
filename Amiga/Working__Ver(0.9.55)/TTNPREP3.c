/*
  ---------------------
  TTNANS:
  TTNPREP2.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Data Preprocessing 3
  (ReOrdering)
  ---------------------

*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include "TTNPREP2.HPP"
#include "TTNMEMOR.HPP"

/*------------------------------------------------------------------------*/

int ordering_info(int preset,int * numofcombinations,
		  int reordersetsize,
		  int reordersetcols,
		  BOOL flag)
{
int msel=preset;
char * menu [] = {"Set ordering method:",
		  "0...None (original ordering).",
		  "1...Arbitrary.",
		  "2...Random.",
		  "3...Sort.",
		  "4...Reverse Sort.",
		  "5...Most Distant.",
		  "6...Most Distant (Low Ram).",
		  "7...Distance from center.",
		  "8...Distance from mean.",
		  "9...All Combinations."
		 };

if(msel==SRE_NOT_SET)
 {
 msel=mmenu(menu,11,1,0,9);
 }

switch(msel)
 {
  case 0: *numofcombinations=OrderNoChange(FALSE,reordersetsize,NULL);
	  return SRE_NO_CHANGE;

  case 1: *numofcombinations=OrderArbitrary(FALSE,reordersetsize,NULL);
	  return SRE_ARBITRARY;

  case 2: *numofcombinations=OrderRandom(FALSE,reordersetsize,NULL,flag);
	  return SRE_RANDOM;

  case 3: *numofcombinations=OrderSort(FALSE,NULL,reordersetsize,reordersetcols,NULL,TRUE,0,flag);
	  return SRE_SORT;

  case 4: *numofcombinations=OrderSort(FALSE,NULL,reordersetsize,reordersetcols,NULL,TRUE,0,flag);
	  return SRE_REVERSE_SORT;

  case 5: *numofcombinations=OrderByDistance(FALSE,NULL,reordersetsize,0,NULL,0);;
	  return SRE_ON_DISTANCE;

  case 6: *numofcombinations=OrderByDistanceLowMemory(FALSE,NULL,reordersetsize,0,NULL,0);;
	  return SRE_ON_DISTANCE_LOW_RAM;

  case 7: *numofcombinations=OrderDistanceFromCenter(FALSE,NULL,reordersetsize,0,NULL);
	  return SRE_DISTANCE_CENTER;

  case 8: *numofcombinations=OrderDistanceFromMean(FALSE,NULL,reordersetsize,0,NULL);
	  return SRE_DISTANCE_MEAN;

  case 9: *numofcombinations=OrderAllCombinations(FALSE,reordersetsize,NULL,0);
	  return SRE_ALL_COMBINATIONS;

 default: mprintf("Unknown Selection, returning NO CHANGE.\n");
	  return SRE_NO_CHANGE;
 }
}

/*------------------------------------------------------------------------*/
/* This does not reorder, just updates the index list 'ordering' which    */
/* must be of 'nfirst' size.                                              */

void ordering(int reorder_type_in,  /* preselected (SRE_NOT_SET for menu).*/
	      int selection,        /* combination selector (if >1 combs).*/
	      DATA ** dataset,
	      int rows,             /* in dataset.                        */
	      int cols,             /* in dataset.                        */
	      int * ordering,       /* ordering indexes put here. Must    */
	      int nfirst)           /* at least be 'nfirst' size big.     */
{
int reorder_type=reorder_type_in;
int combinations;
int * temp_ordering;
int i;

ordering_info(reorder_type,&combinations,rows,cols,FALSE);

if(reorder_type==SRE_NOT_SET)
 mprintf("Invoke ordering: no method selected.\n");

if(selection>=combinations)
 {
 mprintf("Invoke ordering: selection >= ordering combinations (%d>=%d)).\n",selection,combinations);
 reorder_type=SRE_NOT_SET;
 }

temp_ordering=(int *)MMalloc(rows*sizeof(int));  /* not all check nfirst. */

if(no_error)
 {
 switch(reorder_type)
  {
  case SRE_NO_CHANGE           : OrderNoChange(TRUE,rows,temp_ordering);
				 break;
  case SRE_ARBITRARY           : OrderArbitrary(TRUE,rows,temp_ordering);
				 break;
  case SRE_RANDOM              : OrderRandom(TRUE,rows,temp_ordering,FALSE);
				 break;
  case SRE_SORT                : OrderSort(TRUE,dataset,rows,cols,temp_ordering,TRUE,selection,FALSE);
				 break;
  case SRE_REVERSE_SORT        : OrderSort(TRUE,dataset,rows,cols,temp_ordering,FALSE,selection,FALSE);
				 break;
  case SRE_ON_DISTANCE         : OrderByDistance(TRUE,dataset,rows,cols,temp_ordering,nfirst);
				 break;
  case SRE_ON_DISTANCE_LOW_RAM : OrderByDistanceLowMemory(TRUE,dataset,rows,cols,temp_ordering,nfirst);
				 break;
  case SRE_DISTANCE_CENTER     : OrderDistanceFromCenter(TRUE,dataset,rows,cols,temp_ordering);
				 break;
  case SRE_DISTANCE_MEAN       : OrderDistanceFromMean(TRUE,dataset,rows,cols,temp_ordering);
				 break;
  case SRE_ALL_COMBINATIONS    : OrderAllCombinations(TRUE,rows,temp_ordering,selection);
				 break;
  case SRE_NOT_SET             :
  default                      : mprintf("Invoke ordering: Reordering method invalid.\n");
				 mprintf("                 Returning original order.\n");
				 OrderNoChange(TRUE,rows,temp_ordering);
				 break;
  }
 for(i=0;i<nfirst;i++) ordering[i]=temp_ordering[i];
 MFree(temp_ordering);
 }
}

/*------------------------------------------------------------------------*/

void reorder_set(int reorder_type,
		 int selection,
		 DATA ** dataset,
		 int rows,
		 int cols)
{
int i,j;
DATA ** buffer;
int * order;

order=(int *)MMalloc(rows*sizeof(int));
buffer=MMalloc2dDATA(rows,cols);

if(no_error)
 {
 ordering(reorder_type,selection,dataset,rows,cols,order,rows);
 for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
   buffer[i][j]=dataset[order[i]][j];
 for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
   dataset[i][j]=buffer[i][j];

 MFree2dDATA(buffer,rows);
 MFree(order);
 }
}

/*------------------------------------------------------------------------*/

