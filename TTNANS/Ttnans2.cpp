
/*
  ---------------------
  TTNANS:
  TTNANS2.C    ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Additional ANS handl.
  ---------------------

*/

#include "ttndef.h"
#include "ttnpros.h"
#include "ttnsets.h"
#include "ttnui.h"

#include"ttnans1.h"
#include"ttnsetti.h"

/*-----------------------------------------------------------------------*/

void FullyConnect1DLAYERs(LAYER * src,             /* Source Layer.      */
			  LAYER * dst,             			   /* Destination Layer. */
			  int LINKbuffersize,      			   /* cbuff size.        */
			  DATA(*pf)(LINK *),			       /* process function.  */
			  DATA (*lf)(LINK *),  				   /* learning function. */
			  ANS * ap)  			               /* this ANS.          */
{
NODE * np1;
NODE * np2;
LINK * cp;

if(TGBL no_error)
 {
 if((src->dim!=1)||(dst->dim!=1))
  {
  mprintf("FullyConnect1DLAYERs:A layer is not 1-D.\n");
  }
 else
  {
  np1=src->nodes;
  while(np1 != NULL)
   {
   np2=dst->nodes;
   while(np2!=NULL)
	{
	cp=NewLINK(ap,LINKbuffersize);
	cp=SetLINKWeight(InitialWeightValue(np1,np2,src->id),cp);
	cp=SetLINKFunctions(pf,lf,cp);
	cp=DoLINK(np1,np2,cp);
	AppendLINK(cp,src);
	np2=np2->next;
	}
   np1=np1->next;
   }
  }
 }
}

/*-----------------------------------------------------------------------*/

void PresentInputToLayer(DATA * dp,        /* copy each item of input    */
						 LAYER * lp,       /* data vector(dp)to stm[sid] */
						 int sid)          /* at correspond. node in lp. */
{
int i;
NODE * np;

np=lp->nodes;
i=0;

while(np!=NULL)                             /* make sure number of nodes */
 {                                          /* <= size of dp !!!!!!!!!!! */
 if(i>=(TGBL inputdim))
  mprintf("Warning: Original (problem) input dimension exceeded.\n");
 if(np->stmsize>sid)
  np->stm[sid]=dp[i];
 else
  runerror(ANSINTERR,"PresentInput:Invalid node memory.");
 np=np->next;
 i++;
 }
}

/*------------------------------------------------------------------------*/
/* Transfer data through links of layer &lp, modifing data accordingly.   */
/* Note that links of layer &lp are all links that START at an &lp PE     */
/* (NODE), and that this should not modify each link's weight.            */
/* IMPORTANT: this function ADDS the tranfered data to the old stm[0]     */
/* values of destination PEs.                                             */

void AddLinkTransferedDataToSTM(LAYER * lp,int stmnum)
{
LINK * cp;
DATA d;

cp=lp->links;

while(cp!=NULL)
 {
 if(cp->processfunction!=NULL)
  {
  d=cp->processfunction(cp);
  if(cp->destin!=NULL)
   if(cp->destin->stmsize>stmnum)
	cp->destin->stm[stmnum]=cp->destin->stm[stmnum]+d;
   else
	runerror(ANSINTERR,"AddLinkData:Invalid dest.node memory.");
  else
   runerror(ANSINTERR,"AddLinkData:Invalid dest.node.");
  }
 else
  runerror(ANSINTERR,"AddLinkData:No process function.");
 cp=cp->next;
 }
}
/*-----------------------------------------------------------------------*/
/* Modify weights of one link cp according to the learning scheme.       */
/* Note: the link's learnfunction is ADDED to current link's weight.     */

void UpdateSingleLinkWeight(LINK * cp)
{
if(cp!=NULL)
 if(cp->learnfunction!=NULL)
  cp->weight=cp->weight+cp->learnfunction(cp);
 else
  runerror(ANSINTERR,"UpdateWeight:Learn scheme undefined.");
else
 runerror(ANSINTERR,"UpdateWeight, connection pointer invalid.");
}

/*-----------------------------------------------------------------------*/
/* For each link leaving layer sourcelp copy its weight to its lm[lmid]. */

bool SnapshotAllLinkWeightsToLinkMems(LAYER * sourcelp, int lmid)
{
LINK * cp;
if(sourcelp==NULL)            {runerror(ANSINTERR,"Null Layer");return false;}
if((cp=sourcelp->links)==NULL){runerror(ANSINTERR,"No links. ");return false;}
while(cp!=NULL)
 {
 if((cp->cbuffsize)<=lmid)
  {
  runerror(ANSINTERR,"Non-Existent Link memory (cbuff).");
  return false;
  }
 cp->cbuff[lmid]=cp->weight;
 cp=cp->next;
 }
return true;
}

/*-----------------------------------------------------------------------*/
/* Modify weights of all links starting at layer &lp according to the    */
/* learning scheme.                                                      */

void UpdateLinkWeightsAtLayer(LAYER * lp)
{
LINK * cp;
cp=lp->links;
while(cp!=NULL)
 {
 UpdateSingleLinkWeight(cp);
 cp=cp->next;
 }
}

/*-----------------------------------------------------------------------*/
/* make all stm's of all NODES in lp layer contain data 0.               */

void ResetAllNodeStmsTo0(LAYER * lp)
{
NODE * np;
int i;

np=lp->nodes;
while(np!=NULL)
 {
 for(i=0;i<np->stmsize;i++)
  np->stm[i]=0;
 np=np->next;
 }
}
/*-----------------------------------------------------------------------*/

bool SetAllNodeSpecStm(LAYER * lp, int stmid, DATA value)
{
NODE * np;

np=lp->nodes;
while(np!=NULL)
 {
 if(stmid>=(np->stmsize))
  {
  runerror(ANSINTERR,"Specified node (PE) memory does not exist.");
  return false;
  }
 np->stm[stmid]=value;
 np=np->next;
 }
return true;
}

/*-----------------------------------------------------------------------*/

void ThresholdLayerNodes(LAYER * lp,int from_stm, int to_stm)
{
NODE * np;

np=lp->nodes;

while(np!=NULL)
 {
 if (np->outfunction==NULL)
  {
  runerror(ANSINTERR,"Threshold:No Node threshold function.");
  return;
  }
 if ((from_stm>=np->stmsize)||(to_stm>=np->stmsize))
  {
  runerror(ANSINTERR,"Threshold:Invalid node memory specification.");
  return;
  }
 np->stm[to_stm]=np->outfunction(np,from_stm);
 np=np->next;
 }
}

/*-----------------------------------------------------------------------*/
/* add bias to specified stm                                             */

void AddNodeBiases(LAYER * lp,int deststm)
{
NODE * np;

np=lp->nodes;
while(np!=NULL)
 {
 if (deststm>=np->stmsize)
  {
  runerror(ANSINTERR,"AddBias:Invalid node memory specification.");
  return;
  }
 np->stm[deststm]+=np->bias;
 np=np->next;
 }
}

/*-----------------------------------------------------------------------*/
/* Sort node ids for layer lp according to value at stm stmid            */
/* node id's must be sequential with step 1.                             */
/* Good,Old,Slow Bubblesort.                                             */

void SortLayerNodeIdsOnStm(LAYER * lp, int stmid)
{
NODE * np;

NODE * minidnp;            /* pointer to node with minimum id in layer. */
int minid;                 /* minimum id in layer.                      */
int maxid;                 /* maximum id in layer.                      */

NODE * cminvaluenp;        /* pointer to node with current min value in */
DATA cminvalue;            /* stm[stmid] of all which are considered.   */
                           /* This is not always the layer's min value. */
NODE * cminidnp;           /* Pointer to current minimum id for which   */
int cminid;                /* we want to find current minimum value.    */

int idbuff;                /* used in swapping ids bet/ minimum value   */
                           /* and minimum id nodes.                     */
if(lp==NULL)
 {
 runerror(ANSINTERR,"Invalid layer");
 return;
 }

np=lp->nodes;
if(np==NULL)
 {
 runerror(ANSINTERR,"Can not sort ids, layer is empty");
 return;
 }

while(np!=NULL)
 {
 if((np->stmsize)<=stmid)
  {
  runerror(ANSINTERR,"Node memory (stm) does not exist");
  return;
  }
 np=np->next;
 }

/* find min & max node ids in layer */

np=lp->nodes;
minidnp=np;
minid=maxid=np->id;
while(np!=NULL)
 {
 if(minid>np->id)
  {
  minid=np->id;
  minidnp=np;
  }
 if(maxid<np->id)
  {
  maxid=np->id;
  }
 np=np->next;
 }

/* find min value on nodes with id > current min id cminid */

cminid=minid;
cminidnp=minidnp;

while(cminid<maxid)
 {
 cminvalue=LARGEDATA;
 cminvaluenp=NULL;

 np=lp->nodes;
 while(np!=NULL)
  {
  if
   (
   ((np->id)>=cminid)&&
   ((np->stm[stmid])<cminvalue)
   )
   {
   cminvalue=np->stm[stmid];
   cminvaluenp=np;
   }
  np=np->next;
  }

 /* swap min value node's id with min id */
 
 if(cminvaluenp==NULL)
  {
  mprintf("Sort:CURRENT_MIN_VALUE node pointer NULL.(value out of range?)\n");
  return;
  }

 idbuff=cminvaluenp->id;
 cminvaluenp->id=cminid;
 cminidnp->id=idbuff;
  
 cminid++;
 cminidnp=NODEwithId(cminid,lp);
 if(cminidnp==NULL)
  {
  mprintf("Sort: Node with id %d not found.\n");
  mprintf("Are id's sequential with step 1?\n");
  return;
  }
 }
}


/*-----------------------------------------------------------------------*/

void ShowLayerStms(LAYER * lp, int stmid)
{
NODE * np;

if(lp!=NULL)
 {
 mprintf("Layer %d node memories (stm[%d]):\n",lp->id,stmid);

 np=lp->nodes;
 while(np!=NULL)
  {
  if(np->stmsize>stmid)
    {
    mprintf("NodeID_%d:",np->id);
    mprintf(DATAFORMAT,np->stm[stmid]);
    mprintf(".\n");
    }
  np=np->next;
  }
 }
else
 {
 mprintf("Show STMS: Layer does not exist.\n");
 }
}
/*-----------------------------------------------------------------------*/
/* Store specified stms to savevector. NOTE: this is one sad procedure,  */
/* it assumes node ids are sequential starting @ 0 (0,1,..n) and that    */
/* savestore is malloced big enough for all nodes stms (n DATA elements).*/

void Snapshot1dLayerStms(LAYER * lp, int stmid,DATA * savevector)
{
NODE * np;

if(lp!=NULL)
 {
 if(lp->dim==1)
  {
  np=lp->nodes;
  while(np!=NULL)
   {
   if(np->stmsize>stmid) savevector[np->id]=np->stm[stmid];
   else mprintf("Snapshot STM: STM %d does not exist.\n",stmid);
   np=np->next;
   }
  }
 else mprintf("Snapshot STM: Layer is not 1-dimentional.\n");
 }
else mprintf("Snapshot STM: Layer does not exist.\n");
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

int Winner1dLayerNodeId(LAYER * lp, int stmid, bool findbigger)
{
NODE * np;

DATA pvalue;
int  pid=-1;

if(findbigger) pvalue=SMALLDATA;
else           pvalue=LARGEDATA;

if(lp!=NULL)
 {
 if(lp->dim==1)
  {
  np=lp->nodes;
  while(np!=NULL)
   {
   if(np->stmsize>stmid)
    {
    if(((findbigger)  && (np->stm[stmid]>pvalue))||
       ((!findbigger) && (np->stm[stmid]<pvalue)))
     {
     pvalue=np->stm[stmid];
     pid   =np->id;
     }
    }
   else mprintf("Winner: STM %d does not exist.\n",stmid);
   np=np->next;
   }
  }
 else mprintf("Winner: Layer is not 1-dimentional.\n");
 }
else mprintf("Winner: Layer does not exist.\n");
return pid;
}


/*-----------------------------------------------------------------------*/

NODE * Winner1dLayerNode(LAYER * lp, int stmid, bool findbigger)
{
NODE * np;

DATA pvalue;
NODE * p=NULL;

if(findbigger) pvalue=SMALLDATA;
else           pvalue=LARGEDATA;

if(lp!=NULL)
 {
 if(lp->dim==1)
  {
  np=lp->nodes;
  while(np!=NULL)
   {
   if(np->stmsize>stmid)
    {
    if(((findbigger)  && (np->stm[stmid]>pvalue))||
       ((!findbigger) && (np->stm[stmid]<pvalue)))
     {
     pvalue=np->stm[stmid];
     p=np;
     }
    }
   else mprintf("Winner: STM %d does not exist.\n",stmid);
   np=np->next;
   }
  }
 else mprintf("Winner: Layer is not 1-dimentional.\n");
 }
else mprintf("Winner: Layer does not exist.\n");

if(p==NULL) mprintf("Winner: None found, NODE pointer is NULL!\n");
return p;
}



