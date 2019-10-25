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

#ifndef TTNSETTI
#define TTNSETTI

#define INITIALWEIGHTSET struct InitialWeightSet

/*---------------------------------------------- Globals ------------------*/

extern int InitialWeightFlag;

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

extern INITIALWEIGHTSET * InitialWeightSetList;

extern DATA IW_LowerRangeLimit,IW_UpperRangeLimit;  /* If a range is used. */

/*-------------------------------------------------------------------------*/

int CreateInitialWeightSet(int sourcelayersize,int destlayersize);
void FreeAllInitialWeightSets(void);
DATA ** WeightSet(int i);
void WeightSetDims(int i,int *s,int *d);

DATA InitialWeightValue
	       (NODE * source,          /* if set is used.       */
			NODE * dest,            /* if set is used.       */
			int  WeightSetId);      /* if set is used        */

void doSetInitialWeightMode
			   (int NumOfSets,       /* How many weight sets?  */
			    int * SourceDims,    /* if one give pointers to*/
			    int * DestDims);     /* sizes, else arrays.    */

void SetInitialWeightMode
			 (int PreSelectedMode,
			  int NumOfSets,       /* How many weight sets?    */
			  int * SourceDims,    /* if one give pointers to  */
			  int * DestDims);     /* sizes, else arrays.      */

void ClearInitialWeightMode(void);

#endif
