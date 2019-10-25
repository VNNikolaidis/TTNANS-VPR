/*
  ---------------------
  TTNANS:
  TTNPLBP.C  ver.0.02
  ---------------------
  Vasilis.N.Nikolaidis
  -----------------------------
  Plain Vanilla BackPropagation
  (Simpson ANS p114)
  -----------------------------

*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"
#include "ttnnets.hpp"

#include <math.h>

#include "TTNDATA1.HPP"
#include "TTNMATH.HPP"

#define _PLAIN_BP_ANS_

#define A_ITERATION      abuff[0]
#define A_ERROR          abuff[1]

#define L_LEARNRATE      lbuff[0]                                        /* layer's learning rate.  */

#define N_ACTIVATION     stm[0]                                          /* node's activation value */
#define N_ACTIVATION_ID  0
#define N_DISCREPANCY    stm[1]
#define N_DISCREPANCY_ID 1
#define N_THRESHOLD      bias

/*--------------------------------------------------------------------------------------------------*/
/* This is what data each node tranfers to next.                                                    */

DATA linktransferfunctionPLBP(LINK * cp)
{
return (DATA)((cp->source->N_ACTIVATION)*(cp->weight));
}

/*
DATA linktransferfunctionPLBP(LINK * cp)
{
DATA d1,d2;
d1=(DATA)(cp->source->N_ACTIVATION);
d2=(DATA)(cp->weight);

return d1*d2;
}
*/

/*--------------------------------------------------------------------------------------------------*/

DATA sigmoid(NODE * np, int stmid)
{
return (DATA)(1.0/(1+exp(-(np->stm[stmid]))));
}

/*--------------------------------------------------------------------------------------------------*/

DATA discrepancy(DATA c1,DATA c2)
{
return (DATA)(c1*(1-c1)*(c2-c1));
}

/*--------------------------------------------------------------------------------------------------*/

DATA weightmodifierPLBP(LINK * cp)
{
DATA lrate;

lrate=(NODEsLAYER(cp->ans,cp->destin)->L_LEARNRATE);
return (DATA)(lrate*(cp->source->N_ACTIVATION)*(cp->destin->N_DISCREPANCY));
}

/*--------------------------------------------------------------------------------------------------*/

ANS * setupPLBP(int numofhidden, int hiddensize,
                int ins, int outs, DATA learningrate)
{
ANS   * ap;
LAYER * lp;
LAYER * lp2;
LINK  * cp;
NODE  * np;
NODE  * np2;
int i,j;

ap=NewANS(ins,outs,2);                                                 /* Yes, we need a new ANS.   */
                                            
lp=NewLAYER(0,1,1);                                                    /* Create 1D input layer(0). */
lp->L_LEARNRATE=learningrate;
for(i=0;i<ap->inputdim;i++)                                            /* Create input layer nodes. */
 {
 np=NewNODE(i,1,ap);
 AppendNODE(np,lp);                                                    /* No threshold,Discrepancy. */
 lp->dims[0]++;
 }
AppendLAYER(lp,ap);
ap->inputlayer=lp;


for(j=1;j<=numofhidden;j++)                                            /* Create hidden layers.     */
 {
 lp=NewLAYER(j,1,1);                                                   /* Create 1D hidden layer(j).*/
 lp->L_LEARNRATE=learningrate;
 for(i=0;i<hiddensize;i++)                                             /* Create hidden layer nodes.*/
  {
  np=NewNODE(i,2,ap);
  np->outfunction=sigmoid;
  np->N_THRESHOLD=RandomDATA((DATA)-1,(DATA)1);
  AppendNODE(np,lp);
  lp->dims[0]++;
  }
 AppendLAYER(lp,ap);
 }

lp=NewLAYER(j,1,1);                                                    /* Create 1D output layer(1).*/
lp->L_LEARNRATE=learningrate;
for(i=0;i<ap->outputdim;i++)                                           /* Create output layer nodes.*/
 {                                          
 np=NewNODE(i,2,ap);
 np->outfunction=sigmoid;
 np->N_THRESHOLD=RandomDATA((DATA)-1,(DATA)1);
 AppendNODE(np,lp);
 lp->dims[0]++;
 }
AppendLAYER(lp,ap);
ap->outputlayer=lp;

for(j=0;j<(ap->numoflayers-1);j++)                                      /* Fully connect layers ... */
 {
 lp =LAYERWithId(j,ap);
 lp2=LAYERWithId(j+1,ap);

 np=lp->nodes;
 while(np!=NULL)
  {
  np2=lp2->nodes;
  while(np2!=NULL)
   {
   cp=NewLINK(ap,0);
   cp=SetLINKWeight(InitialWeightValue(np,np2,lp->id),cp);
   cp=SetLINKFunctions(linktransferfunctionPLBP,weightmodifierPLBP,cp);
   cp=DoLINK(np,np2,cp);
   AppendLINK(cp,lp);
   np2=np2->next;
   }
  np=np->next;
  }
 }

if(no_error) return ap;
return NULL;
}

/*--------------------------------------------------------------------------------------------------*/
/* Encoding of one pattern d.                                                                       */

void encodePLBP(DATA * d, DATA * o, ANS * ap)
{
LAYER * lp1, * lp2;
NODE  * np1;
LINK  * cp;
DATA  lrate;
int lid;                                                                                /* layer id */

lp1=LAYERWithId(0,ap);
PresentInputToLayer(d,lp1,N_ACTIVATION_ID);


for(lid=1;lid<(ap->numoflayers);lid++)
 {
 lp1=LAYERWithId(lid-1,ap);
 lp2=LAYERWithId(lid,ap);

 ResetAllNodeStmsTo0(lp2);                             /* Set Node activation and discrepancy to 0. */
 AddLinkTransferedDataToSTM(lp1,N_ACTIVATION_ID);      /* using linktransferfunction (process).     */
 AddNodeBiases(lp2,N_ACTIVATION_ID);
 ThresholdLayerNodes(lp2,N_ACTIVATION_ID,N_ACTIVATION_ID);               /* using sigmoid function. */
 }

                     /* Feed back step. (step c equation 5-162 Simpson "Artificial Neural Systems") */

np1=lp2->nodes;                                    /* Starting with the output layer (see above)... */
while(np1!=NULL)
 {
 np1->N_DISCREPANCY=discrepancy(np1->N_ACTIVATION,o[np1->id]);       /* Error. (compare w/desired). */
 np1=np1->next;
 }
                             /* Compute errors at each hidden node: (step d equation 5-163 Simpson) */

lp2=lp2->prev;                                              /* Go to previous layer...              */
while((lp2!=NULL)&&(lp2!=ap->inputlayer))                   /* and for all layers up to input do... */
 {
 cp=lp2->links;
 while(cp!=NULL)                                            /* first sum up all weight*discepancy...*/
  {
  cp->source->N_DISCREPANCY=(cp->source->N_DISCREPANCY)+((cp->weight)*(cp->destin->N_DISCREPANCY));
  cp=cp->next;
  }

 np1=lp2->nodes;
 while(np1!=NULL)                                /* then multiply by bi(1-bi) to complete eq. 5-163 */
  {
  np1->N_DISCREPANCY=(np1->N_ACTIVATION)*(1-(np1->N_ACTIVATION))*(np1->N_DISCREPANCY);
  np1=np1->next;
  }

 UpdateLinkWeightsAtLayer(lp2);     /* Adjust layer lp2-to-next-layer connections. (Equation 5-164) */

 np1=lp2->next->nodes;               /* Adjust destination (next) layer thresholds (Equation 5-165) */
 lrate=lp2->next->L_LEARNRATE;
 while(np1!=NULL)
  {
  np1->bias=(np1->bias)+(lrate*(np1->N_DISCREPANCY));
  np1=np1->next;
  }

 lp2=lp2->prev;
 }


lp2=ap->inputlayer;                                                 /* finaly, at input layer do... */
UpdateLinkWeightsAtLayer(lp2);      /* Adjust layer lp2-to-next-layer connections. (Equation 5-166) */
 
np1=lp2->next->nodes;                /* Adjust destination (next) layer thresholds (Equation 5-166) */
lrate=lp2->next->L_LEARNRATE;
while(np1!=NULL)
 {
 np1->bias=(np1->bias)+(lrate*(np1->N_DISCREPANCY));
 np1=np1->next;
 }

np1=ap->outputlayer->nodes;    /* done, compute the total error for the last feed-forward (?) step. */

while(np1!=NULL)
 {
 ap->A_ERROR=ap->A_ERROR+AbsoluteValue(np1->N_DISCREPANCY);
 np1=np1->next;
 }
}

/*--------------------------------------------------------------------------------------------------*/

int decodePLBP(DATA * d, ANS * ap, DATA * Outstore)
{
LAYER * lp1, * lp2;
int lid;                                                                                /* layer id */

lp1=LAYERWithId(0,ap);
PresentInputToLayer(d,lp1,N_ACTIVATION_ID);

for(lid=1;lid<(ap->numoflayers);lid++)
 {
 lp1=LAYERWithId(lid-1,ap);
 lp2=LAYERWithId(lid,ap);

 ResetAllNodeStmsTo0(lp2);                             /* Set Node activation and discrepancy to 0. */
 AddLinkTransferedDataToSTM(lp1,N_ACTIVATION_ID);      /* using linktransferfunction (process).     */
 AddNodeBiases(lp2,N_ACTIVATION_ID);
 ThresholdLayerNodes(lp2,N_ACTIVATION_ID,N_ACTIVATION_ID);               /* using sigmoid function. */
 }

Snapshot1dLayerStms(lp2,N_ACTIVATION_ID,Outstore);
return Winner1dLayerNodeId(lp2,N_ACTIVATION_ID,TRUE);
}

/*--------------------------------------------------------------------------------------------------*/

void closePLBP(ANS * ap)
{
EndANS(ap);
}

/*--------------------------------------------------------------------------------------------------*/
/* Note: outs(ize) is number of classes, z is maximum t (times).                                    */

void mainPLBP(int mp,
              int z,
              int numofhidden,
              int hiddensize,
              DATA errorlevel,
              DATA learningrate,
              int ins,
              int outs,
              DATA ** Trainset,
              DATA ** Desired,
              int Trainsetsize,
              DATA ** Testset,
              DATA ** Output,
              int Testsetsize,
              DATA * Classif)

{
ANS * BP;
int i;
int p=mp;
BOOL infinite_attempts=FALSE;
DATA last_error=0;
int  stable_error_times=0;

if(no_error)
{
BP=setupPLBP(numofhidden,hiddensize,ins,outs,learningrate);

ShowANS(BP);

if(no_error)
 {                                                                                    /* ENCODE!!!  */
 mprintf("<encoding>\n");

 BP->A_ITERATION=1;
 BP->A_ERROR=LARGEDATA;

 if(z==-1) infinite_attempts=TRUE;
 else mstarttick("<encoding>");

 while((infinite_attempts||((int)(BP->A_ITERATION)<z))&&
                 (BP->A_ERROR>errorlevel))
  {
  BP->A_ERROR=0;
  for(i=0;i<Trainsetsize;i++) encodePLBP(Trainset[i],Desired[i],BP);

  if(last_error==BP->A_ERROR) stable_error_times++;
  else stable_error_times=0;

  if(stable_error_times>1000)
        {
        mprintf("Error level stabilized at ");
        mprintf(DATAFORMAT,last_error);
        mprintf(" for the past 1000 iterations.\n");
        if(FALSE==mrequest_yn("Error level stable. Continue?"))
         BP->A_ERROR=errorlevel;                                                          /* force stop! */
        else
         stable_error_times=0;
        }

  last_error=BP->A_ERROR;

  if(!infinite_attempts)
        {
        BP->A_ITERATION++;
        mtick((int)BP->A_ITERATION,z);
        

        if((BP->A_ITERATION==z)&&(p>1))
         {
         mendtick();
         mprintf("Error level at ");
         mprintf(DATAFORMAT,BP->A_ERROR);
         mprintf(" after phase %d.\n\n",p);
         p--;
         BP->A_ITERATION=1;
         mprintf("Now starting phase %d.\n",p);
         mstarttick("<encoding next phase>");
         }
        }
  }

 mendtick();

 mprintf("Final error level: ");
 mprintf(DATAFORMAT,BP->A_ERROR);
 mprintf(".\n\n");

 mprintf("<decoding>\n");
 for(i=0;i<Testsetsize;i++)                                                          /* DECODE!!!   */
  Classif[i]=(DATA)decodePLBP(Testset[i],BP,Output[i]);

 closePLBP(BP);
 }
}
}

/*--------------------------------------------------------------------------------------------------*/
/* Get Parameters needed for this ANS.                                                              */

void mainPLBP_p(int * mp, int  * z, int * noh, int * hsz, DATA * erl, DATA * lr)
{
mprintf("PL BP --> request for additional parameters :\n");

mprintf("\n");
mprintf("Plain Backpropagation ANS is an iterative algorithm with long training\n");
mprintf("times. You are about to define the maximum number of iterations (z).\n");
mprintf("However, on machines with small maximum integer sizes, z may not be \n");
mprintf("large enough. To allow larger numbers of maximum iterations a second\n"); 
mprintf("parameter (training phase) is used.\n");
mprintf("The maximum number of iterations will be p*z, (where p = number of\n");
mprintf("training phases, z = iterations per training phase).\n");
mprintf("\n");
mprintf("Selecting p=-1 (or z=-1) will cause infinite training attempts\n"); 
mprintf("(the BP will stop only when the acceptable error level is reached).\n");
mprintf("\n");

*mp=-2;
while((*mp<1)&&(*mp!=-1))
 *mp=mrequest_int("Select # of training phases.");
if(*mp==-1)
 *z=-1;
else
 *z=-2;

while((*z<1)&&(*z!=-1))
 {
 mprintf("Select z (max training set presentations per phase,z>=1,-1 for infinite).\n");
 *z=mrequest_int("Select z (iterations per phase.)");
 }

*noh=-1;
while(*noh<0)
 {
 mprintf("Select number of hidden layers (0=<number).\n");
 *noh=mrequest_int("Select number of hidden layers.");
 }

*hsz=0;
if(*noh>0)
 while(*hsz<1)
  {
  mprintf("Select hidden layer size (1<=size).\n");
  *hsz=mrequest_int("Select hidden layer width.");
  }

*lr=-1;
while(*lr<=0)
 {
 mprintf("Select learning rate (>0).\n");
 *lr=mrequest_DATA("Select learning rate.");
 }

*erl=-1;
while(*erl<0)
 {
 mprintf("Select acceptable error level (>=0).\n");
 *erl=mrequest_DATA("Select acceptable error level.");
 }
}

/*-----------------------------------------------------------------------*/
/* Interactive call, gets parameters then runs ANS.                      */

BOOL mainPLBP_i(BOOL GetParameters,
                BOOL RunAlgorithm,
                int WeightInitializationMode,
                int Inputsize,
                int Outputsize,
                DATA ** Trainset,
                DATA ** Desired,
                int Trainsetsize,
                DATA ** Testset,
                DATA ** Output,
                int Testsetsize,
                DATA * Classif)
{
static int mp;                               /* training phases.        */
static int z;                                /* iterations per phase.   */
static int numofhidden;                      /* number of hidden layers */
static int hiddensize;                       /* width of hidden layers  */
static DATA errorlevel;                      /* error threshold (stops) */
static DATA learningrate;

if((Trainset!=NULL)&&
   (Desired!=NULL)&&
   (Testset!=NULL)&&
   (Output!=NULL)&&
   (no_error))
 {
 if(GetParameters)mainPLBP_p(&mp,&z,&numofhidden,&hiddensize,&errorlevel,&learningrate);


 if(RunAlgorithm)
  {
  SetInitialWeightMode(WeightInitializationMode,1,NULL,NULL);

  mprintf(" \n");
  mprintf("* Calling: Vanilla BP ANS. * \n");
  mprintf("Parameters:\n");
  mprintf("Input Size %d.\n",Inputsize);
  mprintf("Output Size %d.\n",Outputsize);
  mprintf("Training phases %d.\n",mp);
  mprintf("Iterations per phase %d.\n",z);
  mprintf("Number of hidden layers %d.\n",numofhidden);
  mprintf("Hidden layer size %d.\n",hiddensize);
  mprintf("Learning Rate ");
  mprintf(DATAFORMAT,learningrate);
  mprintf(".\n");
  mprintf("Acceptable error level ");
  mprintf(DATAFORMAT,errorlevel);
  mprintf(".\n");
  mprintf("                                            1      \n");
  mprintf("Node threshold function sigmoid (f(x) =  -------- .\n");
  mprintf("                                               -x  \n");
  mprintf("                                          1 + e    \n");
  mprintf("(f(x) in 0..1).\n");

  mainPLBP(mp,z,numofhidden,hiddensize,errorlevel,learningrate,
           Inputsize,Outputsize,Trainset,Desired,Trainsetsize,
           Testset,Output,Testsetsize,Classif);

  mprintf("* Done. * \n");

  ClearInitialWeightMode();
  return TRUE;
  }
 }

if(Desired==NULL)
 mprintf("BP exits: not a supervised problem definition.\n");

return FALSE;
}
