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

#include "ttndef.h"
#include "ttnpros.h"

#include "ttnprep2.h"
#include "ttnmemor.h"

#include "ttnui.h"

/*------------------------------------------------------------------------*/

int ordering_info(int preset,int * numofcombinations,
		  int reordersetsize,
		  int reordersetcols,
		  bool flag)
{
int msel=preset;
char mtitle [] = "Ordering Method for Set";
char * menu [] =
        {
          "00...None (original ordering).",
		  "01...Arbitrary.",
		  "02...Random.",
		  "03...Sort.",
		  "04...Reverse Sort.",
		  "05...Most Distant.",
		  "06...Most Distant (Low Ram).",
          "07...Most Distant starting from mean.",
		  "08...Distance from center.",
		  "09...Distance from mean.",
		  "10...All Combinations."
		 };

if(msel==SRE_NOT_SET)
 {
 msel=mmenu(mtitle,menu,11,10);
 }

switch(msel)
 {
  case 0: *numofcombinations=OrderNoChange(false,reordersetsize,NULL);
	  return SRE_NO_CHANGE;

  case 1: *numofcombinations=OrderArbitrary(false,reordersetsize,NULL);
	  return SRE_ARBITRARY;

  case 2: *numofcombinations=OrderRandom(false,reordersetsize,NULL,flag);
	  return SRE_RANDOM;

  case 3: *numofcombinations=OrderSort(false,NULL,reordersetsize,reordersetcols,NULL,true,0,flag);
	  return SRE_SORT;

  case 4: *numofcombinations=OrderSort(false,NULL,reordersetsize,reordersetcols,NULL,true,0,flag);
	  return SRE_REVERSE_SORT;

  case 5: *numofcombinations=OrderByDistance(false,NULL,reordersetsize,0,NULL,0);;
	  return SRE_ON_DISTANCE;

  case 6: *numofcombinations=OrderByDistanceLowMemory(false,NULL,reordersetsize,0,NULL,0);;
	  return SRE_ON_DISTANCE_LOW_RAM;
	
  case 7: *numofcombinations=OrderByDistanceStartingMeanLowMemory(false,NULL,reordersetsize,0,NULL,0);;
	  return SRE_ON_DISTANCE_START_MEAN;

  case 8: *numofcombinations=OrderDistanceFromCenter(false,NULL,reordersetsize,0,NULL);
	  return SRE_DISTANCE_CENTER;

  case 9: *numofcombinations=OrderDistanceFromMean(false,NULL,reordersetsize,0,NULL);
	  return SRE_DISTANCE_MEAN;

  case 10: *numofcombinations=OrderAllCombinations(false,reordersetsize,NULL,0);
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

ordering_info(reorder_type,&combinations,rows,cols,false);

if(reorder_type==SRE_NOT_SET)
 mprintf("Invoke ordering: no method selected.\n");

if(selection>=combinations)
 {
 mprintf("Invoke ordering: selection >= ordering combinations (%d>=%d)).\n",selection,combinations);
 reorder_type=SRE_NOT_SET;
 }

temp_ordering=(int *)MMalloc(rows*sizeof(int));  /* not all check nfirst. */

if(TGBL no_error)
 {
 switch(reorder_type)
  {
  case SRE_NO_CHANGE				:	OrderNoChange(true,rows,temp_ordering);
										break;
  case SRE_ARBITRARY				:	OrderArbitrary(true,rows,temp_ordering);
										break;
  case SRE_RANDOM					:	OrderRandom(true,rows,temp_ordering,false);
										break;
  case SRE_SORT						:	OrderSort(true,dataset,rows,cols,temp_ordering,true,selection,false);
										break;
  case SRE_REVERSE_SORT				:	OrderSort(true,dataset,rows,cols,temp_ordering,false,selection,false);
										break;
  case SRE_ON_DISTANCE				:	OrderByDistance(true,dataset,rows,cols,temp_ordering,nfirst);
										break;
  case SRE_ON_DISTANCE_LOW_RAM		:	OrderByDistanceLowMemory(true,dataset,rows,cols,temp_ordering,nfirst);
										break;
  case SRE_ON_DISTANCE_START_MEAN	:	OrderByDistanceStartingMeanLowMemory(true,dataset,rows,cols,temp_ordering,nfirst);
										break;
  case SRE_DISTANCE_CENTER			:	OrderDistanceFromCenter(true,dataset,rows,cols,temp_ordering);
										break;
  case SRE_DISTANCE_MEAN			:	OrderDistanceFromMean(true,dataset,rows,cols,temp_ordering);
										break;
  case SRE_ALL_COMBINATIONS			:	OrderAllCombinations(true,rows,temp_ordering,selection);
										break;
  case SRE_NOT_SET					:
  default							:	mprintf("Invoke ordering: Reordering method invalid.\n");
										mprintf("                 Returning original order.\n");
										OrderNoChange(true,rows,temp_ordering);
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

if(TGBL no_error)
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

