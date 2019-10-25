
/*
  ----------------------------
  TTNANS:
  TTNKCN.C           ver.0.02
  ----------------------------
  Vasilis.N.Nikolaidis
  ---------------------------------
  Kohonen Clustering Net.
  An 1-D modification of LVQ,
  Multiple Winner Unsupervised,
  See (E.C.K.Thao et al.):
  Fuzzy Kohonen Clustering Networks
  ---------------------------------

*/

#include "ttndef.h"
#include "ttnpros.h"
#include "ttnnets.h"

#include "ttnui.h"

#include "ttnmath.h"

#define _KCN_ANS_

#define ITERATION          abuff[0]
#define NEIG_SIZE          abuff[1]
#define ERROR_t            abuff[2]    /* (KCN->ERROR_t holds Et squared.)*/
#define MAX_ITERATION      abuff[3]

#define N_OUTPUT           stm[0]                 /* node's output memory */
#define N_OUTPUT_STM       0

#define C_LEARNRATE_FACTOR cbuff[0]
#define C_OLDWEIGHT        cbuff[1]
#define C_OLDWEIGHT_LM     1

/**************************************************************************/
/* IMPORTANT NOTE: Unlike LVQ, the output layer threshold function:       */
/* extern DATA th_square_root (NODE *, int);             (see ttnthres.c) */
/* is NOT used here.                                                      */
/**************************************************************************/

/*-----------------------------------------------------------------------*/
/* This is what data each layer(0(input)) KCN node tranfers to next.  */

DATA euclidiandistsquaredKCN(LINK * cp)
{
DATA diff;

diff=(cp->source->N_OUTPUT)-(cp->weight);
diff=diff*diff;
return diff;
}

/*-----------------------------------------------------------------------*/

DATA _a_KCN(DATA a,int t,DATA max_t)
{
return (DATA)(a*(1-((DATA)t/max_t)));
}

/*-----------------------------------------------------------------------*/

DATA weightmodifierKCN(LINK * cp)
{
return (DATA)(_a_KCN(cp->C_LEARNRATE_FACTOR,
                     (int)(cp->ans->ITERATION),
                     cp->ans->MAX_ITERATION)
              *((cp->source->N_OUTPUT)-(cp->weight))
             );
}

/*-----------------------------------------------------------------------*/

ANS * setupKCN(int ins,int outs,int max_t,DATA a)
{
ANS   * ap;
LAYER * lp1;
LAYER * lp2;
LINK  * cp;
NODE  * np1;
NODE  * np2;

ap=NewANS(ins,outs,4);                      /* Create a new ANS (4 bufs).*/
ap->MAX_ITERATION=max_t;

                                            /* INPUT LAYER.              */
lp1=FullSetupNew1DLAYER(ap->inputdim,       /* Number of nodes.          */
                       0,                   /* Requested Layer ID.       */
                       0,                   /* Layer buffer size.        */
                       NULL,                /* NODE outfunction.         */
                       1,                   /* NODE stmemory size.       */
                       ap);                 /* add layer to this.        */
ap->inputlayer=lp1;                         /* Set this as input layer.  */

                                            /* OUTPUT LAYER.             */
lp2=FullSetupNew1DLAYER(ap->outputdim,      /* Number of nodes.          */
                       1,                   /* Requested Layer ID.       */
                       0,                   /* Layer buffer size.        */
    /*th_square_root*/ NULL,                /* NODE outfunction.         */
                       1,                   /* NODE stmemory size.       */
                       ap);                 /* add layer to this.        */
ap->outputlayer=lp2;                        /* Set this as ANS's output. */

                                           /* fully connect layers.     */

np1=lp1->nodes;
while(np1!=NULL)
 {
 np2=lp2->nodes;
 while(np2!=NULL)
  {
  cp=NewLINK(ap,2);             /* We need a local memory to store local */
  cp->C_LEARNRATE_FACTOR=a;     /* learning rate factor used in _a_.     */
  cp->C_OLDWEIGHT=0;            /* and old (t-1) weight values for error.*/

  cp=SetLINKWeight(InitialWeightValue(np1,np2,lp1->id),cp);
  cp=SetLINKFunctions(euclidiandistsquaredKCN,weightmodifierKCN,cp);
  cp=DoLINK(np1,np2,cp);
  AppendLINK(cp,lp1);
  np2=np2->next;
  }
 np1=np1->next;
 }

if(TGBL no_error) return ap;
return NULL;
}

/*-----------------------------------------------------------------------*/
/* KCN encoding of ONE pattern d.                                        */

void encodeKCN(DATA * d,ANS * ap)
{
LAYER * lp1, * lp2;
LINK  * cp;
int nodedist;

lp1=NthLAYER(0,ap);
lp2=NthLAYER(1,ap);

ResetAllNodeStmsTo0(lp2);
PresentInputToLayer(d,lp1,N_OUTPUT_STM);
AddLinkTransferedDataToSTM(lp1,N_OUTPUT_STM);
SortLayerNodeIdsOnStm(lp2,N_OUTPUT_STM);  /*I Want My Connection Machine!*/

/* At this point winner (closest, smallest difference) node  has id 0.   */
/* and node ids are sorted according to euclidian distance squared of    */
/* distance between input and connection weights.                        */
/* Now update weights (Wg) closer to input d,for (minimum dif) node np1. */
/* as well as nodes that are in np1's neighborhood (ans->buff[1] holds n)*/
/* new faster version uses NODE.ids (assumes sequential id numbering)  !!*/

cp=lp1->links;                  /* Will go through all links...          */
while(cp!=NULL)                 /* For each link check if destin is in   */
 {                              /* neigb/hood of winner (node id=0) node.*/
 nodedist=cp->destin->id;       /* destination node's id distance from 0.*/
 if(nodedist<(int)ap->NEIG_SIZE)/* NEIG_SIZE==1 means update winner only.*/
  UpdateSingleLinkWeight(cp);
 cp=cp->next;
 }
}

/*-----------------------------------------------------------------------*/

int decodeKCN(DATA * d, ANS * ap, DATA * OutStore)
{
LAYER * lp1, * lp2;

lp1=NthLAYER(0,ap);
lp2=NthLAYER(1,ap);

ResetAllNodeStmsTo0(lp2);
PresentInputToLayer(d,lp1,N_OUTPUT_STM);
AddLinkTransferedDataToSTM(lp1,N_OUTPUT_STM);

/*ThresholdLayerNodes(lp2,0,0);*/       /* replace stm[0] with its sqrt. */

Snapshot1dLayerStms(lp2,N_OUTPUT_STM,OutStore);

										/* find node with smallest diff. */

return Winner1dLayerNodeId(lp2,N_OUTPUT_STM,false);
}

/*-----------------------------------------------------------------------*/

void closeKCN(ANS * ap)
{
EndANS(ap);
}


/*-----------------------------------------------------------------------*/

DATA compute_Et(ANS * ap)
{
LAYER * inlp;
LAYER * outlp;
NODE * np;

LINK  * cp;
DATA r;           /* distance of one cluster center  to its previous pos.*/
DATA sr=0;        /* sum of all distances r.                             */

inlp =NthLAYER(0,ap);                                    /* input layer  */
outlp=NthLAYER(1,ap);                                    /* output layer */

if((inlp!=NULL)&&(outlp!=NULL))
 {
 np=outlp->nodes;           /* find the movement of each cluster center  */
 while(np!=NULL)            /* for each output node(represents a cluster)*/
  {                         /* by adding the Eucl.distances of their     */
  r=0;                      /* previous positions with their current.    */
  cp=inlp->links;
  while(cp!=NULL)
		{
		if(cp->destin==np) r=r+squared((cp->weight)-(cp->C_OLDWEIGHT));
		cp=cp->next;
		}
  sr=sr+square_root(r);
  np=np->next;
  }
 }

/*mprintf(" sr=%f \n",sr);*/
return sr;
}

/*-----------------------------------------------------------------------*/

void mainKCN(int ins, int outs,int max_t, int z, DATA e, DATA a, int n, DATA nstep,
			 DATA ** Trainset, int Trainsetsize,
			 DATA ** Testset, int Testsetsize,
			 DATA ** Output,
			 DATA * Classif)
{
ANS * KCN;
int i;

if(TGBL no_error)
 {
 KCN=setupKCN(ins,outs,max_t,a);

 ShowANS(KCN);

 if((TGBL no_error))
  {                                   /* ENCODE!!!                       */
  mstarttick("<encoding>");
  LinkLog(KCN->inputlayer);

  KCN->NEIG_SIZE=(DATA)n;             /* initial neighborhood size.      */
  KCN->ITERATION=(DATA)1;             /* Iteration t=1 (see Simpson p88).*/
  KCN->ERROR_t=LARGEDATA;             /* Et=big to start loop.           */

  while (((KCN->ERROR_t)>e)&&((KCN->ITERATION)<z))
		{
		SnapshotAllLinkWeightsToLinkMems(NthLAYER(0,KCN),C_OLDWEIGHT_LM);
		for(i=0;i<Trainsetsize;i++) encodeKCN(Trainset[i],KCN);
		if(KCN->NEIG_SIZE>1) KCN->NEIG_SIZE-=nstep;
		if(KCN->NEIG_SIZE<1) KCN->NEIG_SIZE=1;
		KCN->ITERATION+=1;
		KCN->ERROR_t=compute_Et(KCN);
		/* adjust a? we currently use the LVQ method a=(0.2*(1-(t/10000.0))). */
		LinkLog(KCN->inputlayer);
		mtick((int)(KCN->ITERATION),z);
		}

  mendtick();

  ShowANS(KCN);

  mprintf("<decoding>\n");

  for(i=0;i<Testsetsize;i++)          /* DECODE!!!                       */
   Classif[i]=(DATA)decodeKCN(Testset[i],KCN,Output[i]);

  ShowANS(KCN);

  closeKCN(KCN);
  }
 }
}

/*-----------------------------------------------------------------------*/

void mainKCN_p(int outs, DATA *e, DATA *a, int *max_t, int *z, int *n, DATA *nstep)
{
 mprintf(" \n \n");
 mprintf("KCN --> request for additional parameters :\n");

 *max_t=0;
 while(*max_t<=0)
  {
  mhintclear();
  mhintf(true,"The iteration limit (max_t) of KCN is used as an upper limit\n");
  mhintf(true,"for the iteration to run ('z') parameter. The ratio i/max_t\n");
  mhintf(true,"also affects the learning (cluster adjustment) rate of\n");
  mhintf(true,"the argorithm at iteration i.\n");
  mhintf(true,"Originaly, max iteration limit was set equal to 10000.\n");
  *max_t=mrequest_int("Select max iteration limit (originaly 10000).");
  }

 *z=0;
 while((*z<=0)||(*z>*max_t))
  {
  mhintclear();
  mhintf(true,"The number of iterations to perform is denoted by 'z'.\n");
  mhintf(true,"'z' must be in the range 0 < z =< max_t.\n");
  mhintf(true,"'z' (max iteration to run), was originaly set to 500.\n");
  mhintf(true,"Here 'z' must be in (0 < z =< %d)).\n",*max_t);
  *z=mrequest_int("Select z (max iteration to run).");
  }

 *e=-1.0;
 while(*e<0.0)
  {
  mhintclear();
  mhintf(true,"Error level Et is defined as the difference in weight values\n");
  mhintf(true,"of connection weights (i.e. movement of cluster centers) after\n");
  mhintf(true,"a training cycle has been completed; it is used as a convergence\n");
  mhintf(true,"measure (i.e. to determine if training should continue).\n");
  mprintf("Select e ((small),(if (Et<e) stop),(e>=0))\n");
  *e=mrequest_DATA("Select e (error level limit).");
  }
 *a=0.0;
 while((*a<=0.0)||(*a>=1))
  {
  mhintclear();
  mhintf(true,"Parameter 'a' is a learning rate factor,(0<a<1),(originaly a=0.2).\n");
  mhintf(true,"The actual learning rate factor is affected by a*(iteration/max_t)");
  *a=mrequest_DATA("Select a (learning rate factor).");
  }

 *n=0;
 while((*n<1)||(*n>outs))
  {
  mhintclear();
  mhintf(true,"Parameter 'n' is the neighbourhood size (1=<n=<%d).\n",outs);
  *n=mrequest_int("Select n (neigb. size).");
  }

 *nstep=-1.0;
 while((*nstep<0)||(*nstep>(DATA)*n))
  {
  mhintclear();
  mhintf(true,"Parameter 'nstep' is the neighbourhood decreament step size.\n");
  *nstep=mrequest_DATA("Select nstep (neigb. size step.).");
  }
}

/*-------------------------------------------------------------------------*/

bool mainKCN_i(bool GetParameters,
               bool RunAlgorithm,
               int WeightInitializationMode,
               int ins,
               int outs,
               DATA ** Trainset,
               int Trainsetsize,
               DATA ** Testset,
               int Testsetsize,
               DATA ** Output,
               DATA * Classif)
{
static DATA e;
static DATA a;
static int  max_t;
static int  z;
static int  n;
static DATA nstep;

if((Trainset!=NULL)&&(Testset!=NULL)&&((TGBL no_error)))
 {
 if(GetParameters)mainKCN_p(outs,&e,&a,&max_t,&z,&n,&nstep);
 if(RunAlgorithm)
  {
  SetInitialWeightMode(WeightInitializationMode,1,&ins,&outs);

  mprintf("* Calling: KCN ANS * \n");
  mprintf("Parameters:\n");
  mprintf("Input Size %d.\n",ins);
  mprintf("Output Size %d.\n",outs);
  mprintf("Current Max Number of Iterations %d (out of %d).\n",z,(int) max_t);
  mprintf("Error Level ");
  mprintf(DATAFORMAT,e);
  mprintf(".\n");
  mprintf("Learning Rate Factor ");
  mprintf(DATAFORMAT,a);
  mprintf(".\n");
  mprintf("Neighb.Size %d.\n",n);
  mprintf("Neighb.Step -");
  mprintf(DATAFORMAT,nstep);
  mprintf(".\n");
  
  mainKCN(ins,outs,max_t,z,e,a,n,nstep,Trainset,Trainsetsize,Testset,Testsetsize,Output,Classif);

  mprintf("* Done. * \n");

  ClearInitialWeightMode();
  return true;
  }
 }
return false;
}
