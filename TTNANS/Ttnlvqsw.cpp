/*
  ---------------------
  TTNANS:
  TTNLVQSWU.C  ver.0.3
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  LVQ Learning Vector
	Quantizer Single
  Winner Unsupervised.
  Kohonen,(Simpson p87)
  ---------------------

*/

#include "ttndef.h"
#include "ttnpros.h"
#include "ttnnets.h"

#include "ttnui.h"

#include "ttnthres.h"

#define _LVQ_SWU_ANS_

#define INPUT_LAYER_ID  0
#define OUTPUT_LAYER_ID 1

#define INPUT           stm[0]   /* in this case, put stm = output stm,  */
#define INPUT_STM_ID    0        /*      i.e. memory contents are simply */
#define OUTPUT          stm[0]   /*                replaced by new data. */
#define OUTPUT_STM_ID   0

#define ITERATION       abuff[0]
#define LEARNRATE       abuff[1]

/*-----------------------------------------------------------------------*/
/* Define node (PE) output function for input layer (0) nodes.           */
/* This is the data that input layer LVQSWU nodes tranfer to next layer. */
/* In this case, it is the squared distance between input and weight.    */

DATA euclidiandistsquaredLVQSWU(LINK * cp)
{
DATA diff;

diff=(cp->source->INPUT)-(cp->weight);
return (DATA)(diff*diff);
}

/*-----------------------------------------------------------------------*/
/* a() function (learning rate) for LVQ. See Simpson text.               */

DATA _a_LVQSWU(DATA a,int t)
{
return (DATA)(a*(1-(t/10000.0)));
}

/*-----------------------------------------------------------------------*/
/* Connection weight modifier (learning function).                       */

DATA weightmodifierLVQSWU(LINK * cp)
{
return (DATA)(_a_LVQSWU(cp->ans->LEARNRATE,(int)(cp->ans->ITERATION))*
						((cp->source->INPUT)-(cp->weight)));
}

/*-----------------------------------------------------------------------*/

ANS * setupLVQSWU(int ins,int outs)
{
ANS   * ap;
LAYER * lp1;
LAYER * lp2;

ap=NewANS(ins,outs,2);                      /* Create new ANS.           */
lp1=FullSetupNew1DLAYER(ap->inputdim,       /* Number of nodes.          */
					   INPUT_LAYER_ID,      /* Requested Layer ID.       */
					   0,                   /* Layer buffer size.        */
					   NULL,                /* NODE outfunction.         */
					   1,                   /* NODE stmemory size.       */
					   ap);                 /* add layer to this.        */
ap->inputlayer=lp1;                         /* Set this as input layer.  */

lp2=FullSetupNew1DLAYER(ap->outputdim,      /* Number of nodes.          */
                       OUTPUT_LAYER_ID,     /* Requested Layer ID.       */
					   0,                   /* Layer buffer size.        */
					   th_square_root,      /* NODE outfunction.         */
					   1,                   /* NODE stmemory size.       */
					   ap);                 /* add layer to this.        */
ap->outputlayer=lp2;                        /* Set this as ANS's output. */

                                            /* fully connect layers.     */

FullyConnect1DLAYERs(lp1,                          /* Source Layer.      */
                     lp2,                          /* Destination Layer. */
                     0,                            /* cbuff size.        */
                     euclidiandistsquaredLVQSWU,   /* process function.  */
                     weightmodifierLVQSWU,         /* learning function. */
                     ap);

if(TGBL no_error) return ap;
return NULL;
}

/*-----------------------------------------------------------------------*/
/* Single Winner Unsupervised LVQ encoding of ONE pattern d.             */

void encodeLVQSWU(DATA * d,ANS * ap)
{
LAYER * lp1, * lp2;
NODE  * np2;
LINK  * cp;

lp1=LAYERWithId(INPUT_LAYER_ID,ap);
lp2=LAYERWithId(OUTPUT_LAYER_ID,ap);

ResetAllNodeStmsTo0(lp2);
PresentInputToLayer(d,lp1,INPUT_STM_ID);
AddLinkTransferedDataToSTM(lp1,INPUT_STM_ID);
ThresholdLayerNodes(lp2,INPUT_STM_ID,OUTPUT_STM_ID); /* replace  w/ sqrt.*/

np2=Winner1dLayerNode(lp2, OUTPUT_STM_ID, false);    /* find node with   */
													 /* closest distance.*/

/* now update weights (Wg) closer to input d,for (minimum dif) node np2. */
/* see Simpson's "Artificial Neural Systems" page 88. step b.            */

cp=lp1->links;
while(cp!=NULL)
 {
 if(cp->destin==np2)
  UpdateSingleLinkWeight(cp);
 cp=cp->next;
 }
}

/*-----------------------------------------------------------------------*/

int decodeLVQSWU(DATA * d, ANS * ap, DATA * OutStore)
{
LAYER * lp1, * lp2;

lp1=NthLAYER(INPUT_LAYER_ID,ap);
lp2=NthLAYER(OUTPUT_LAYER_ID,ap);

ResetAllNodeStmsTo0(lp2);
PresentInputToLayer(d,lp1,INPUT_STM_ID);
AddLinkTransferedDataToSTM(lp1,INPUT_STM_ID);
ThresholdLayerNodes(lp2,INPUT_STM_ID,OUTPUT_STM_ID);  /* replace w/ sqrt.*/

Snapshot1dLayerStms(lp2,OUTPUT_STM_ID,OutStore);

										/* find node with smallest diff. */

return Winner1dLayerNodeId(lp2,OUTPUT_STM_ID,false);
}

/*-----------------------------------------------------------------------*/

void closeLVQSWU(ANS * ap)
{
EndANS(ap);
}

/*-----------------------------------------------------------------------*/
/* Note: outs(ize) is number of classes, z is maximum t (times).         */

void mainLVQSWU(int ins, int outs, int z, DATA a,
				DATA ** Trainset,
				int Trainsetsize,
				DATA ** Testset,
				int Testsetsize,
				DATA ** Output,
				DATA * Classif)

{
ANS * LVQ;
int i;

if(TGBL no_error)
{
LVQ=setupLVQSWU(ins,outs);

LVQ->ITERATION=1;                     /* LVQ->buf[0]="t"(see Simpson p88)*/
LVQ->LEARNRATE=a;

ShowANS(LVQ);

if((TGBL no_error))
 {                                                          /* ENCODE!!! */

 mstarttick("<encoding>");
 LinkLog(LVQ->inputlayer);

  while((int)(LVQ->ITERATION)<z)
   {
   for(i=0;i<Trainsetsize;i++) encodeLVQSWU(Trainset[i],LVQ);
   LVQ->ITERATION=LVQ->ITERATION+1;

   LinkLog(LVQ->inputlayer);
   mtick((int)(LVQ->ITERATION),z);

   }
 mendtick();

 ShowANS(LVQ);

 mprintf("<decoding>\n");
 for(i=0;i<Testsetsize;i++)                                 /* DECODE!!! */
  Classif[i]=(DATA)decodeLVQSWU(Testset[i],LVQ,Output[i]);

 ShowANS(LVQ);

 closeLVQSWU(LVQ);
 }
}
}

/*-----------------------------------------------------------------------*/
/* Get Parameters needed for this ANS.                                   */


void mainLVQSWU_p(int  * z,     /* modifiable: max number of iterations. */
				  DATA * a)     /*             learn rate factor.        */
{
mprintf("LVQ SWU --> request for additional parameters :\n");

*z=0;
*a=(DATA)-1;


while((*z<500)||(*z>10000))
 {
 mhintclear();
 mhintf(true,"The number of iterations to perform is denoted by 'z'.\n");
 mhintf(true,"'z' (or max t) must be in the range 500=<z=<10000.\n");
 *z=mrequest_int("Select parameter z :");
 }

mprintf("Please select learning rate factor 'a'.\n");
mhintclear();
mhintf(true,"This is the maximum correction (occuring at t=1) that\n");
mhintf(true,"can be applied on a cluster center using the distance\n");
mhintf(true,"of this center to a given training set item.\n");
while((*a<0)||(*a>1))
 {
 mprintf("Suggested 'a' was 0.2; 0 <= a <= 1.\n");
 *a=mrequest_DATA("Select learning factor :");
 }
}

/*-----------------------------------------------------------------------*/
/* Interactive call, gets parameters then runs ANS.                      */

bool mainLVQSWU_i(bool GetParameters,
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
static int z;                /* must be static if we want to call again */
							 /* with GetParameters=false.               */

static DATA a;

if((Trainset!=NULL)&&(Testset!=NULL)&&((TGBL no_error)))
 {
 if(GetParameters)mainLVQSWU_p(&z,&a);
 if(RunAlgorithm)
  {
  SetInitialWeightMode(WeightInitializationMode,1,&ins,&outs);

  mprintf(" \n");
  mprintf("* Calling: LVQ SWU ANS. * \n");
  mprintf("Parameters:\n");
  mprintf("Input Size %d.\n",ins);
  mprintf("Output Size %d.\n",outs);
  mprintf("Max Number of Iterations %d.\n",z);
  mprintf("Learning rate factor ");
  mprintf(DATAFORMAT,a);
  mprintf(".\n");

  mainLVQSWU(ins,outs,z,a,Trainset,Trainsetsize,Testset,Testsetsize,Output,Classif);

  mprintf(" \n");
  mprintf("* Done. * \n");

  ClearInitialWeightMode();
  return true;
  }
 }
return false;
}
