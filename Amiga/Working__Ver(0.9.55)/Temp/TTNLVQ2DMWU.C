
/*
  ---------------------
  TTNANS:
  TTNLVQ2DMWU.C  ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  LVQ Learning Vector
  Quantizer, 2-diment.
  Output Layer,Multiple
  Winner Unsupervised.
  Kohonen,(Simpson p87)
  ---------------------

*/

#include "TTNDEFS.h"
#include "TTNPROS.h"
#include "math.h"

#define _LVQ_2D_MWU_ANS_

#define squared(x) ((x)*(x))


extern void * MMalloc (size_t);
extern DATA   RandomDATA(DATA lowlimit, DATA hilimit);

extern LAYER* NthLAYER(int,ANS *);
extern void   AppendLAYER(LAYER *,ANS *);
extern LAYER* NewLAYER(int,int);
extern void   AppendNODE(NODE *,LAYER *);
extern NODE * NewNODE(int,int,ANS *);

extern LINK * NewLINK(ANS *,int);
extern LINK * DoLINK(NODE *,NODE *,LINK *);
extern LINK * SetLINKWeight(DATA,LINK *);
extern LINK * SetLINKFunctions(DATA (*)(), DATA (*)(), LINK *);
extern void   AppendLINK(LINK *,LAYER *);

extern ANS  * NewANS(int,int,int);
extern void   EndANS(ANS *);

extern void PresentInputToLayer(DATA *, LAYER *);
extern void CopyLayersLinkTransferedDataToNewSTM0(LAYER *);
extern void UpdateSingleLinkWeight(LINK *);
extern void ResetAllNodeStmsTo0(LAYER *);

extern LAYER * NODEsLAYER(ANS *,NODE *);

extern int mrequest_int(char *);

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/* This is what data each layer(0(input)) LVQ2DMWU node tranfers to next.*/

DATA euclidiandistsquaredLVQ2DMWU(LINK * cp)
{
DATA diff;

diff=(cp->source->stm[0])-(cp->weight);
diff=diff*diff;

return diff;
}

/*-----------------------------------------------------------------------*/

DATA _a_LVQ2DMWU(int t)
{
return (DATA)(0.2*(1-(t/10000.0)));
}

/*-----------------------------------------------------------------------*/

DATA weightmodifierLVQ2DMWU(LINK * cp)
{
return _a_LVQ2DMWU((int)(cp->ans->buff[0]))*((cp->source->stm[0])-(cp->weight));
}

/*-----------------------------------------------------------------------*/
/* Note: sidesize is parameter z, side of 2d array of output nodes       */

ANS * setupLVQ2DMWU(int ins,int sidesize)
{
ANS   * ap;
LAYER * lp;
LAYER * lp2;
LINK  * cp;
NODE  * np;
NODE  * np2;
int i;

ap=NewANS(ins,
         (int)squared(sidesize),
         3);                                /* Yes, we need a new ANS.   */
                                            /* We use ANS buff for t,s,r.*/

lp=NewLAYER(0,1);                           /* Create 1D input layer(0). */
for(i=0;i<ap->inputdim;i++)                 /* Create input layer nodes. */
 {
 np=NewNODE(i,1,ap);
 AppendNODE(np,lp);
 lp->dims[0]++;
 }
AppendLAYER(lp,ap);
ap->inputlayer=lp;

lp=NewLAYER(1,2);                           /* Create 2D output layer(1).*/

for(i=0;i<ap->outputdim;i++)                /* Create output layer nodes.*/
 {                                          /* (in LVQ,outp.node = class)*/
 np=NewNODE(i,1,ap);
 AppendNODE(np,lp);
 }
lp->dims[0]=sidesize;
lp->dims[1]=sidesize;

AppendLAYER(lp,ap);
ap->outputlayer=lp;
                                            /* Now fully connect layers. */
lp =NthLAYER(0,ap);
lp2=NthLAYER(1,ap);

np =lp->nodes;
while(np!=NULL)
 {
 np2=lp2->nodes;
 while(np2!=NULL)
  {
  cp=NewLINK(ap,0);
  cp=SetLINKWeight(RandomDATA((DATA)0,(DATA)1),cp);
  cp=SetLINKFunctions(euclidiandistsquaredLVQ2DMWU,weightmodifierLVQ2DMWU,cp);
  cp=DoLINK(np,np2,cp);
  AppendLINK(cp,lp);
  np2=np2->next;
  }
 np=np->next;
 }

if(no_error) return ap;
return NULL;
}

/*-----------------------------------------------------------------------*/
BOOL neighborLVQ2DMWU(NODE * np1,NODE * np2,ANS * ap)
{
int np1x,np1y,np2x,np2y,s,r,d;

if(NODEsLAYER(ap,np1)!=NODEsLAYER(ap,np2))
 {
  mprintf("Neighbor:Nodes are not in the same layer.\n");
  runerror(ANSINTERR);
  return FALSE;
 }

if(np1==np2)  return TRUE;
 
s=ap->buff[1];
r=ap->buff[2];

np1x=np1->id%s;
np1y=np1->id/s;
np2x=np2->id%s;
np2y=np2->id/s;

d=(int)sqrt((double)(squared(np1x-np2x)+squared(np1y-np2y)));

/* what about wraparound??? */

if(d>r) return FALSE;
return TRUE;
}


/*-----------------------------------------------------------------------*/
/* Multiple Winner Unsupervised LVQ encoding of ONE pattern d.           */

void encodeLVQ2DMWU(DATA * d,ANS * ap)
{
LAYER * lp1, * lp2;
NODE  * np1, * np2;
LINK  * cp;
DATA  dd;

lp1=NthLAYER(0,ap);
lp2=NthLAYER(1,ap);

ResetAllNodeStmsTo0(lp2);
PresentInputToLayer(d,lp1);
CopyLayersLinkTransferedDataToNewSTM0(lp1);

dd=LARGEDATA;
np2=NULL;
np1=lp2->nodes;
while(np1!=NULL)
 {
 np1->stm[0]=sqrt(np1->stm[0]);         /* replace stm[0] with its sqrt. */
 if(np1->stm[0]<dd)                     /* find node with smallest diff. */
  {
  dd=np1->stm[0];
  np2=np1;                              /* np2 now points to that node.  */
  }
 np1=np1->next;
 }

/* now update weights (Wg) closer to input d,for (minimum dif) node np2. */
/* see Simpson's "Artificial Neural Systems" page 88. step b.            */
/* Note: we use ans->buff[0] for t.                                      */

cp=lp1->links;
while(cp!=NULL)
 {
 if(neighborLVQ2DMWU(cp->destin,np2,ap))
  UpdateSingleLinkWeight(cp);           
 cp=cp->next;
 }
}

/*-----------------------------------------------------------------------*/

int decodeLVQ2DMWU(DATA * d, ANS * ap)
{
LAYER * lp1, * lp2;
NODE  * np1, * np2;
DATA  dd;

lp1=NthLAYER(0,ap);
lp2=NthLAYER(1,ap);

ResetAllNodeStmsTo0(lp2);
PresentInputToLayer(d,lp1);
CopyLayersLinkTransferedDataToNewSTM0(lp1);

dd=LARGEDATA;
np2=NULL;
np1=lp2->nodes;
while(np1!=NULL)
 {
 if(np1->stm[0]<dd)                     /* find node with smallest diff. */
  {
  dd=np1->stm[0];
  np2=np1;                              /* np2 now points to that node.  */
  }
 np1=np1->next;
 }
return np2->id;
}

/*-----------------------------------------------------------------------*/

void closeLVQ2DMWU(ANS * ap)
{
EndANS(ap);
}

/*-----------------------------------------------------------------------*/
/* Note: outs(ize) is number of classes, z is maximum t (times),         */
/*       s is size for 2D array of output nodes (s x s),                 */
/*       r is neigbourhood radius (range).                               */

void mainLVQ2DMWU(int ins, int outs, int z,int s, int r)
{
ANS * LVQ;
int i;

if(no_error)
{
LVQ=setupLVQ2DMWU(ins,s);
if(no_error)
 {                                    /* ENCODE!!!                       */
 LVQ->buff[0]=1;                      /* LVQ->buf[0]="t"(see Simpson p88)*/
 LVQ->buff[1]=s;                      /* LVQ->buf[1]=size of output side.*/
 LVQ->buff[2]=r;                      /* LVQ->buf[2]=neigbourhood radius.*/

  while(LVQ->buff[0]<z)
   {
   for(i=0;i<trainsetsize;i++) encodeLVQ2DMWU(trainset[i],LVQ);
   LVQ->buff[0]=LVQ->buff[0]+1;
   }

 mprintf("\n\n");
 for(i=0;i<testsetsize;i++)           /* DECODE!!!                       */
   {
   mprintf("Example %d decoded in class %d.\n",i,decodeLVQ2DMWU(testset[i],LVQ));
   }
 closeLVQ2DMWU(LVQ);
 }
}
}

/*-----------------------------------------------------------------------*/
void mainLVQ2DMWU_i(int ins, int outs)
{
int z,s,r;

mprintf("\n\nLVQ 2-D MWU request for additional parameters :\n");

if(no_error)
{
 z=0;
 while((z<500)||(z>10000))
 z=mrequest_int("Please select z (max_t,500=<z=<10000)");

 s=0;
 while(s<1)
 s=mrequest_int("Please select s (2D-output-node array side,s>0)");

 r=-1;
 while(r<0)
 r=mrequest_int("Please select r (neighborhood radius,z>0)");

 mprintf("\n **** Calling: LVQ 2D MWU ANS ****\n");
 mainLVQ2DMWU(ins,outs,z,s,r);
 mprintf("\n **** Done.                ****\n");

 }
}