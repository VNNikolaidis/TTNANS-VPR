/*
  ---------------------
  TTNANS:
  TTNSETTI.C  ver.0.04
  ---------------------
  Vasilis.N.Nikolaidis
  --------------------------
  Settings.
  Module for Experimentation
  on Algorithm Parameters.
  --------------------------

*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"
#include "ttnsets.hpp"

#include "TTNMEMOR.HPP"
#include "TTNDATA1.HPP"
#include "TTNPREP2.HPP"

#define INITIALWEIGHTSET struct InitialWeightSet

/*---------------------------------------------- Globals ------------------*/

int InitialWeightFlag = IW_NOT_SET;

INITIALWEIGHTSET
 {
 DATA ** WeightSet;         /* Initial Weights, where WeightSet[j][k] is   */
                            /* initial value for LINK from NODE j to k in  */
                            /* the next layer of a fully connected layer   */
                            /* pair.                                       */

 int SourceDim;
 int DestinDim;
 INITIALWEIGHTSET * next;
 };

INITIALWEIGHTSET * InitialWeightSetList = NULL;

DATA IW_LowerRangeLimit,IW_UpperRangeLimit; /* If a range is used instead. */

/*-------------------------------------------------------------------------*/
/* Initial Weight Selection Experimentation Section -----------------------*/
/*-------------------------------------------------------------------------*/

int CreateInitialWeightSet(int sourcelayersize,int destlayersize)
{
INITIALWEIGHTSET * TargetSet = InitialWeightSetList;
INITIALWEIGHTSET * NewSet;

int j=0;

if(no_error)
 {
 mprintf("Creating Initial Weight Set %d x %d.\n",sourcelayersize,destlayersize);
 NewSet=(INITIALWEIGHTSET*)MMalloc(sizeof(INITIALWEIGHTSET));
 NewSet->WeightSet=MMalloc2dDATA(sourcelayersize,destlayersize);
 if(no_error)
  {
  NewSet->SourceDim=sourcelayersize;
  NewSet->DestinDim=destlayersize;
  NewSet->next=NULL;
  if(TargetSet==NULL)
   InitialWeightSetList=NewSet;
  else
   {
   while(TargetSet->next!=NULL)
    {
    TargetSet=TargetSet->next;
    j++;
    }
   TargetSet->next=NewSet;
   }
  mprintf("Initial Weight Set (#%d) Creation Call Completed.\n",j);
  return j;
  }
 }
return -1;
}

/*-------------------------------------------------------------------------*/

void FreeAllInitialWeightSets(void)
{
INITIALWEIGHTSET * p1, * p2;
int j=0;

p1=InitialWeightSetList;

if(p1==NULL) return;

do
 {
 p2=p1->next;
 MFree2dDATA(p1->WeightSet,p1->SourceDim);
 MFree(p1);
 p1=p2;
 mprintf("Initial Weight Set (#%d) deleted.\n",j);
 j++;
 }
while(p1!=NULL);

InitialWeightSetList=NULL;
}

/*-------------------------------------------------------------------------*/

DATA ** WeightSet(int i)
{
INITIALWEIGHTSET * p=InitialWeightSetList;

int j=0;

while(j<i)
 {
 if(p!=NULL)p=p->next;
 j++;
 }

if(p==NULL)
 {
 mprintf("Warning:Initial weight set %d does not exist.\n",i);
 return NULL;
 }
else
 return p->WeightSet;
}
/*-----------------------------------------------------------------------*/

void WeightSetDims(int i,int *s,int *d)
{
INITIALWEIGHTSET * p=InitialWeightSetList;

int j=0;

while(j<i)
 {
 if(p!=NULL)p=p->next;
 j++;
 }

if(p==NULL)
 {
 mprintf("Warning:Initial weight set %d does not exist.\n",i);
 *s=0;
 *d=0;
 }
else
 *s=p->SourceDim;
 *d=p->DestinDim;
}

/*-----------------------------------------------------------------------*/
/* The next Function called when an initial weight is assigned to a LINK */
/*-----------------------------------------------------------------------*/
/* The WeightMatrix is a 2-d array used to specify initial weights for   */
/* all connections from a layer to the next in a fully connected pair.   */
/* WeightMatrix[i][j] should be the initial value for connection from    */
/* NODE i to NODE j.  It is used when UseWeightMatrix is TRUE. Otherwise */
/* a random number in specified range is generated and used instead.     */

DATA InitialWeightValue(NODE * source,          /* if set is used.       */
                        NODE * dest,            /* if set is used.       */
                        int  WeightSetId)       /* if set is used        */
{
DATA rv;

int s,d;

switch(InitialWeightFlag)
 {
 case IW_USE_PREDEFINED_WEIGHT_SET:
 case IW_USE_WEIGHT_SET     : WeightSetDims(WeightSetId,&s,&d);
                              if((source->id>s)||(dest->id>d))
                               {
                               mprintf("Warning: Initial Weight Entry (%d->%d) does not exist\n",source->id,dest->id);
                               rv=(DATA)0;
                               }
                              else
                               rv=WeightSet(WeightSetId)[source->id][dest->id];
                              break;

 case IW_ZERO_TO_ONE        : rv=RandomDATA((DATA)0,(DATA)1);
                              break;

 case IW_MINUS_ONE_TO_ONE   : rv=RandomDATA((DATA)-1,(DATA)1);
                              break;

 case IW_USD_RANGE          : rv=RandomDATA(IW_LowerRangeLimit,IW_UpperRangeLimit);
                              break;

 default                    : mprintf("Warning: Weight initialization unknown.\n");
                              mprintf("(Returning initial weight = 0).\n");
                              rv=(DATA)0;
                              break;
 }

/*
mprintf("Link Weight: (NODE id %d)----> ",source->id);
mprintf(DATAFORMAT,rv);
mprintf("---> NODE id %d)\n",dest->id);
*/

return rv;
}

/*-------------------------------------------------------------------------*/


void doSetInitialWeightMode(int NumOfSets,       /* How many weight sets?  */
                            int * SourceDims,    /* if one give pointers to*/
                            int * DestDims)      /* sizes, else arrays.    */
{
int n,i,j;
int * ordering;


BOOL show_info;
static int OldInitialWeightFlag=IW_NOT_SET;

if(OldInitialWeightFlag!=InitialWeightFlag) show_info=TRUE;
else show_info=FALSE;

 switch(InitialWeightFlag)
  {
  case IW_ZERO_TO_ONE:

          IW_LowerRangeLimit=0;       /* ???? is this needed ???? */
          IW_UpperRangeLimit=1;       /* ???? is this needed ???? */
          break;

  case IW_MINUS_ONE_TO_ONE:

          IW_LowerRangeLimit=-1;      /* ???? is this needed ???? */
          IW_UpperRangeLimit=1;       /* ???? is this needed ???? */
          break;

  case IW_USD_RANGE:

          IW_LowerRangeLimit=1;
          IW_UpperRangeLimit=0;
          while(IW_LowerRangeLimit>IW_UpperRangeLimit)
           {
           IW_LowerRangeLimit=mrequest_DATA("Enter lower range limit");
           IW_UpperRangeLimit=mrequest_DATA("Enter upper range limit");
           }
          break;

  case IW_USE_WEIGHT_SET:

          for(n=0;n<NumOfSets;n++)
           {
           mprintf("Initial Weights of Set %d (Assumed to be for layer %d to %d).\n",n,n,n+1);
           if(n!=CreateInitialWeightSet(SourceDims[n],DestDims[n]))
            mprintf("Warning: Initial Weight Set id mismatch; older sets exist?.\n");
           for(i=0;i<SourceDims[n];i++)
            for(j=0;j<DestDims[n];j++)
            {
            mprintf("Set initial weight of node %d to (next layer) node %d connection.\n",i,j);
            WeightSet(n)[i][j]=mrequest_DATA("Enter Weight");
	    }
           }
          break;

  case IW_DISTANT_TRAIN_ITEMS:
  case IW_DISTANT_TRAIN_ITEMS_LOW_RAM:
          if(show_info)
          {
          mprintf("Most Distant Training Set Items\n");
          mprintf("-------------------------------\n");
          mprintf("This method evolved for use in one layer pair ANSs such as\n");
          mprintf("the LVQ, where each input connection weight is directly   \n");
          mprintf("compared to the corresponing value in the input vector.   \n");
          mprintf("For x a P.E. (node) of the destination layer (presumably  \n");
          mprintf("representing a class in LVQ,KCN etc) it initializes each  \n");
          mprintf("connection to x with a corresponding value from the most  \n");
          mprintf("distant training set items.                                  \n");
          mprintf("In order to work properly the number of destination nodes \n");
          mprintf("(classes) must be less or equal to the training set size. \n");
          mprintf("\n");
          }
          if((NumOfSets<1)||(trainset==NULL))
	   {
           mprintf("Warning: Number of Sets is zero or No Problem Loaded.\n");
           InitialWeightFlag=IW_NOT_SET;
           return;
           }

          ordering=(int*)MMalloc(trainsetsize*sizeof(int));

          /* now order (this is definetly not the best way to speed things up) */
          if(no_error)
           {
           if(InitialWeightFlag==IW_DISTANT_TRAIN_ITEMS)
            {
            if(NumOfSets>1)
             OrderByDistance(TRUE,trainset,trainsetsize,inputdim,ordering,trainsetsize);
            else
             OrderByDistance(TRUE,trainset,trainsetsize,inputdim,ordering,DestDims[0]);
            }
           else
            {
            if(NumOfSets>1)
             OrderByDistanceLowMemory(TRUE,trainset,trainsetsize,inputdim,ordering,trainsetsize);
	    else
             OrderByDistanceLowMemory(TRUE,trainset,trainsetsize,inputdim,ordering,DestDims[0]);
            }

           for(n=0;n<NumOfSets;n++)
            {
            mprintf("Setting Initial Weights of Set %d (Assumed to be for layer %d to %d).\n",n,n,n+1);

            if(DestDims[n]>trainsetsize)
             {
             mprintf("Warning: Training Set contains less than %d items.\n",DestDims[n]);
             InitialWeightFlag=IW_NOT_SET;
             }
            else
             {
             if(n!=CreateInitialWeightSet(SourceDims[n],DestDims[n]))
              mprintf("Warning: Initial Weight Set id mismatch; older sets exist?.\n");
             for(i=0;i<SourceDims[n];i++)
              for(j=0;j<DestDims[n];j++)
               WeightSet(n)[i][j]=trainset[ordering[j]][i];
             OldInitialWeightFlag=InitialWeightFlag;
             InitialWeightFlag=IW_USE_WEIGHT_SET;
	     }
            }
           MFree(ordering);
           }
          else
           InitialWeightFlag=IW_NOT_SET;
          break;


  case IW_RANDOM_IN_TRAINING_SET_RANGE:
          if(show_info)
          {
          mprintf("Random number in Training set values' range.\n");
          mprintf("--------------------------------------------\n");
          mprintf("This method finds the min,max values in the entire \n");
          mprintf("training set and uses the for setting the random number\n");
          mprintf("range used in initializing weights.\n");
          mprintf("\n");
          }
          IW_LowerRangeLimit=LARGEDATA;
          IW_UpperRangeLimit=SMALLDATA;
          if(trainset==NULL)
	   {
           mprintf("Warning: No Problem Loaded\n");
           InitialWeightFlag=IW_NOT_SET;
           return;
	   }

	  for(i=0;i<trainsetsize;i++)
	   for(j=0;j<inputdim;j++)
	    {
	    if(trainset[i][j]<IW_LowerRangeLimit)IW_LowerRangeLimit=trainset[i][j];
	    if(trainset[i][j]>IW_UpperRangeLimit)IW_UpperRangeLimit=trainset[i][j];
	    }
	  mprintf("Initial Weight Range ");
	  mprintf(DATAFORMAT,IW_LowerRangeLimit);
	  mprintf(",");
	  mprintf(DATAFORMAT,IW_UpperRangeLimit);
	  mprintf("\n\n");
	  InitialWeightFlag=IW_USD_RANGE;
	  OldInitialWeightFlag=InitialWeightFlag;

  case IW_RANDOM_TRAINING_SET_ITEM:
	  if(show_info)
	  {
	  mprintf("Random Training Set Item.\n");
	  mprintf("-------------------------\n");
	  mprintf("This method evolved for use in one layer pair ANSs such as\n");
	  mprintf("the LVQ, where each input connection weight is compared   \n");
	  mprintf("directly to the corresponing value in the input vector.   \n");
	  mprintf("(connection weights represent cluster center coordinates.)\n");
	  mprintf("For x a P.E. (node) of the destination layer (presumably  \n");
	  mprintf("representing a class in LVQ,KCN etc) it initializes each  \n");
	  mprintf("connection to x with a corresponding value from a\n");
	  mprintf("randomly picked training set item.\n");
	  mprintf("\n");
	  }
	  if(trainset==NULL)
	   {
	   mprintf("Warning: No Problem Loaded\n");
	   InitialWeightFlag=IW_NOT_SET;
	   return;
	   }

	  ordering=(int*)MMalloc(trainsetsize*sizeof(int));
	  OrderRandom(TRUE,trainsetsize,ordering,FALSE);

	  if(no_error)
	   {
	   for(n=0;n<NumOfSets;n++)
	    {
	    mprintf("Setting Initial Weights of Set %d (Assumed to be for layer %d to %d).\n",n,n,n+1);

	    if(DestDims[n]>trainsetsize)
	     {
	     mprintf("Warning: Training Set contains less than %d items.\n",DestDims[n]);
	     InitialWeightFlag=IW_NOT_SET;
	     break;
	     }

	    if(n!=CreateInitialWeightSet(SourceDims[n],DestDims[n]))
	     mprintf("Warning: Initial Weight Set id mismatch; older sets exist?.\n");
	    for(i=0;i<SourceDims[n];i++)
	     for(j=0;j<DestDims[n];j++)
	      WeightSet(n)[i][j]=trainset[ordering[j]][i];
	    }
	   MFree(ordering);
	   OldInitialWeightFlag=InitialWeightFlag;
	   InitialWeightFlag=IW_USE_WEIGHT_SET;
	   }
	  else
	   InitialWeightFlag=IW_NOT_SET;
	  break;

  case IW_FIRST_TRAINING_SET_ITEM:
	  if(show_info)
	  {
	  mprintf("First Training Set Items.\n");
	  mprintf("-------------------------\n");
	  mprintf("This method can be used in one layer pair ANSs such as    \n");
	  mprintf("the LVQ, where connection weights represent cluster center\n");
	  mprintf("coordinates.)\n");
	  mprintf("\n");
	  }
	  if(trainset==NULL)
	   {
	   mprintf("Warning: No Problem Loaded\n");
	   InitialWeightFlag=IW_NOT_SET;
	   return;
	   }

	  ordering=(int*)MMalloc(trainsetsize*sizeof(int));
	  OrderNoChange(TRUE,trainsetsize,ordering);

	  if(no_error)
	   {
	   for(n=0;n<NumOfSets;n++)
	    {
	    mprintf("Setting Initial Weights of Set %d (Assumed to be for layer %d to %d).\n",n,n,n+1);

	    if(DestDims[n]>trainsetsize)
	     {
	     mprintf("Warning: Training Set contains less than %d items.\n",DestDims[n]);
	     InitialWeightFlag=IW_NOT_SET;
	     break;
	     }

	    if(n!=CreateInitialWeightSet(SourceDims[n],DestDims[n]))
	     mprintf("Warning: Initial Weight Set id mismatch; older sets exist?.\n");
	    for(i=0;i<SourceDims[n];i++)
	     for(j=0;j<DestDims[n];j++)
	      WeightSet(n)[i][j]=trainset[ordering[j]][i];
	    }
	   MFree(ordering);
	   OldInitialWeightFlag=InitialWeightFlag;
	   InitialWeightFlag=IW_USE_WEIGHT_SET;
	   }
	  else
	   InitialWeightFlag=IW_NOT_SET;
	  break;


  default:mprintf("Warning:Initial Weight Mode (%d) unknown or not Implemented.\n",InitialWeightFlag);
          InitialWeightFlag=IW_NOT_SET;
          break;

  }
}

/*-------------------------------------------------------------------------*/


void SetInitialWeightMode(int PreSelectedMode,
                          int NumOfSets,       /* How many weight sets?    */
			  int * SourceDims,    /* if one give pointers to  */
                          int * DestDims)      /* sizes, else arrays.      */
{
int msel;
char *menu[]={"Please select connection weight ",
              "initialization method. ",
              "--------------------------------",
              "Select initialization:                 ",
              "0...Random numbers in 0..1 range.      ",
              "1...Random numbers in -1..1 range.     ",
              "2...Random numbers in some other range.",
              "3...Numbers manually selected by you.   "
             };


if(PreSelectedMode==IW_NOT_SET)
 {
 msel=mmenu(menu,8,4,0,3);
 switch(msel)
  {
  case 0: InitialWeightFlag=IW_ZERO_TO_ONE;
          break;
  case 1: InitialWeightFlag=IW_MINUS_ONE_TO_ONE;
          break;
  case 2: InitialWeightFlag=IW_USD_RANGE;
          break;
  case 3: InitialWeightFlag=IW_USE_WEIGHT_SET;
          break;
  }
 }
else
 InitialWeightFlag=PreSelectedMode;

doSetInitialWeightMode(NumOfSets,SourceDims,DestDims);
}

/*-------------------------------------------------------------------------*/

void ClearInitialWeightMode(void)
{
FreeAllInitialWeightSets();
InitialWeightFlag=IW_NOT_SET;
IW_LowerRangeLimit=IW_UpperRangeLimit=0;
}
