
/*
  ----------------------------
  TTNANS:
  TTNFKCN.C           ver.0.01
  ----------------------------
  Vasilis.N.Nikolaidis
  ----------------------------
  Kohonen Clustering Net.
  An 1-D modification of LVQ,
  Multiple Winner Unsupervised,
  See (E.C.K.Thao et al.)
  ----------------------------

*/

#include "TTNDEFS.h"
#include "TTNPROS.h"
#include "math.h"

#define _FKCN_ANS_
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

extern int  mrequest_int(char *);
extern DATA mrequest_DATA(char *);

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/* This is what data each layer(0(input)) FKCN node tranfers to next.  */

DATA euclidiandistsquaredFKCN(LINK * cp)
{
DATA diff;

diff=(cp->source->stm[0])-(cp->weight);
diff=diff*diff;

return diff;
}

/*-----------------------------------------------------------------------*/

DATA _a_FKCN(int t)
{
return (DATA)(0.2*(1-(t/10000.0)));
}

/*-----------------------------------------------------------------------*/

DATA weightmodifierFKCN(LINK * cp)
{
return _a_FKCN((int)(cp->ans->buff[0]))*((cp->source->stm[0])-(cp->weight));
}

/*-----------------------------------------------------------------------*/

ANS * setupFKCN(int ins,int outs,DATA a)
{
ANS   * ap;
LAYER * lp;
LAYER * lp2;
LINK  * cp;
NODE  * np;
NODE  * np2;
int i;

ap=NewANS(ins,outs,3);                      /* Yes, we need a new ANS.   */
                                            /* ANS buffers used:         */
                                            /* buff[0] for t,            */
                                            /* buff[1] for neighbrd size,*/
                                            /* buff[2] for Et.           */

lp=NewLAYER(0,1);                           /* Create 1D input layer(0). */
for(i=0;i<ap->inputdim;i++)                 /* Create input layer nodes. */
 {
 np=NewNODE(i,1,ap);
 AppendNODE(np,lp);
 lp->dims[0]++;
 }
AppendLAYER(lp,ap);
ap->inputlayer=lp;

lp=NewLAYER(1,1);                           /* Create 1D output layer(1).*/
for(i=0;i<ap->outputdim;i++)                /* Create output layer nodes.*/
 {                                          
 np=NewNODE(i,1,ap);
 AppendNODE(np,lp);
 lp->dims[0]++;
 }
AppendLAYER(lp,ap);
ap->outputlayer=lp;
                                            /* fully connect layers.     */
lp =NthLAYER(0,ap);
lp2=NthLAYER(1,ap);

np =lp->nodes;
while(np!=NULL)
 {
 np2=lp2->nodes;
 while(np2!=NULL)
  {
  cp=NewLINK(ap,1);                        /* We need a local memory to  */
  cp->lm[0]=a;                             /* store local learning rate. */
                                           /* !!!!!! STILL UNUSED !!!!!! */

  cp=SetLINKWeight(RandomDATA((DATA)0,(DATA)1),cp);
  cp=SetLINKFunctions(euclidiandistsquaredFKCN,weightmodifierFKCN,cp);
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
/* FKCN encoding of ONE pattern d.                                        */

void encodeFKCN(DATA * d,ANS * ap)
{
LAYER * lp1, * lp2;
NODE  * np1, * np2;
LINK  * cp;
DATA  dd;
int dist;
DATA vt,vtm1;

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
/* as well as nodes that are in np2's neighborhood (ans->buff[1] holds n)*/ 
/* Note: we use ans->buff[0] for t.                                      */

/*!! new faster vers. uses NODE.ids (assumes sequential id numbering)  !!*/

cp=lp1->links;
ap->buff[2]=(DATA)0;                       /* we compute Et squared here */
while(cp!=NULL)
 {
 dist=(np2->id)-(cp->destin->id);
 dist=abs(dist);
 vtm1=cp->weight;
 if(dist<=ap->buff[1]) UpdateSingleLinkWeight(cp);
 vt=cp->weight;
 ap->buff[2]=ap->buff[2]+squared(vt-vtm1);
 cp=cp->next;
 }
}


/*-----------------------------------------------------------------------*/

int decodeFKCN(DATA * d, ANS * ap)
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

void closeFKCN(ANS * ap)
{
EndANS(ap);
}

/*-----------------------------------------------------------------------*/
/* Note: c is number of classes, z is maximum t (times).                 */

void mainFKCN(int ins, int c, int z, DATA e, DATA a, int n)
{
ANS * FKCN;
int i;

if(no_error)
 {
 FKCN=setupFKCN(ins,c,a);
 e=squared(e);                        /* (FKCN->buff[2] holds Et squared.)*/

 mprintf("<encoding>\n");

 if(no_error)
  {                                   /* ENCODE!!!                       */
  FKCN->buff[0]=(DATA)1;               /* t=1 (see Simpson p88).          */
  FKCN->buff[2]=LARGEDATA;             /* Et=big! (Et stored here.)       */

  while((FKCN->buff[2]>e)&&(FKCN->buff[0]<z))
   {
   /* mprintf("Et squared = %f, t = %f\n",FKCN->buff[2],FKCN->buff[0]);    */
   FKCN->buff[1]=(DATA)n;
   FKCN->buff[2]=(DATA)0;
   for(i=0;i<trainsetsize;i++)
     encodeFKCN(trainset[i],FKCN);
   if(n>0)n=n-1;
   FKCN->buff[0]=FKCN->buff[0]+1;
   /* ???? adjust a here ???? */
   }

  mprintf("<decoding>\n");

  mprintf("\n\n");
  for(i=0;i<testsetsize;i++)          /* DECODE!!!                       */
   mprintf("Example %d decoded in class %d.\n",i,decodeFKCN(testset[i],FKCN));
 
  closeFKCN(FKCN);
  }
 }
}

/*-----------------------------------------------------------------------*/

void mainFKCN_i(int ins, int outs)
{
DATA e;
DATA a;
int z;
int n;


if(no_error)
 {
 mprintf("\n\nFKCN --> request for additional parameters :\n");

 z=0;
 while((z<500)||(z>10000))
 z=mrequest_int("Please select z (max_t) (500=<z=<10000)");

 e=0.0;
 while(e<=0.0)
 e=mrequest_DATA("Please select e (small,used in: if (Et<e) stop) (e>0)");

 a=0.0;
 while((a<=0.0)||(a>=1))
 a=mrequest_DATA("Please select a (init.learning rate) (0<a<1)");

 n=0;
 while((n<1)||(n>outs))
 n=mrequest_int("Please select n (neighbourhood size)");

 mprintf("\n **** Calling: FKCN ANS ****\n");
 mainFKCN(ins,outs,z,e,a,n);
 mprintf("\n **** Done.            ****\n");
 }
}
