/*--------------------------------------------------- NotePad -----------*/

/*
  ---------------------
  TTNANS:
  TTNANS1.C    ver.0.02
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Basic ANS handling
  ---------------------
*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include "TTNMEMOR.HPP"

/*-----------------------------------------------------------------------*/

LAYER * NthLAYER(int n,ANS * ap)
{                                     /* Returns pointer to 0th (0),     */
LAYER * lp;                           /* 1st (1), 2nd (2),... etc layer. */
int i,steps;

steps=n;

if(((lp=ap->layers)==NULL)||(n>=ap->numoflayers)||(n<0))
 {
 runerror(ANSINTERR,"Nth-Layer: No layers or n>number of layers");
 return NULL;
 }

for(i=0;i<steps;i++)
 {
 lp=lp->next;
 if(lp==NULL)
  {
  runerror(ANSINTERR,"Nth-Layer: Layer does not exist.");
  return NULL;
  }
 }
return lp;
}

/*-----------------------------------------------------------------------*/

LAYER * LAYERWithId(int id,ANS * ap)
{
LAYER * lp;

if((lp=ap->layers)==NULL)
 {
 runerror(ANSINTERR,"LayerWithID: No layers in ANS.");
 return NULL;
 }

while(lp->id!=id)
 {
 lp=lp->next;
 if(lp==NULL)
  {
  runerror(ANSINTERR,"LayerWithID: No Layer with this id.");
  return NULL;
  }
 }
return lp;
}

/*-----------------------------------------------------------------------*/

BOOL ExistsLAYERWithId(int id,ANS * ap)
{
LAYER * lp;

if((lp=ap->layers)==NULL) return FALSE;

while(lp->id!=id)
 {
 lp=lp->next;
 if(lp==NULL) return FALSE;
 }
return TRUE;
}

/*-----------------------------------------------------------------------*/

NODE * NODEwithId(int id, LAYER * lp)
{
NODE * np;

if(lp==NULL)
 {
 runerror(ANSINTERR,"NODEwithID: Bad layer pointer");
 return NULL;
 }

if((np=lp->nodes)==NULL)
 {
 runerror(ANSINTERR,"NODEwithID: Layer is empty");
 return NULL;
 }

while(np->id!=id)
 {
 np=np->next;
 if(np==NULL)
  {
  runerror(ANSINTERR,"NODEwithID: No Node with this id");
  return NULL;
  }
 }
return np;
}

/*-----------------------------------------------------------------------*/

LAYER * NODEsLAYER (ANS * ap,         /* Returns pointer to the layer    */
                    NODE * np)        /* that the node belongs to.       */
{
LAYER * lp1;
LAYER * lp2;
NODE  * np1;
BOOL found = FALSE;

lp1=ap->layers;
while(lp1!=NULL)
 {
 np1=lp1->nodes;
 while(np1!=NULL)
  {
  if(np1==np)
        {
        if (found==FALSE)
         {
         found=TRUE;
         lp2=lp1;
         }
        else runerror(ANSINTERR,"NODEsLAYER: Error");
        }                             /* Note: as a PRECAUTION, it       */
  np1=np1->next;                      /* continues search to see if node */
  }                                   /* is also found elsewhere.        */
 lp1=lp1->next;
 }
return lp2;
}

/*-----------------------------------------------------------------------*/

int NODEsLAYERId (ANS * ap,           /* Returns id of layer             */
                  NODE * np)          /* that node belongs to.           */
{
return (NODEsLAYER(ap,np))->id;
}

/*-----------------------------------------------------------------------*/

LAYER * LINKsLAYER (ANS * ap,         /* Returns pointer to the layer    */
                    LINK * lkp)       /* that the link starts from.      */
{
LAYER * lp1;
LAYER * lp2;
LINK  * lkp1;
BOOL found = FALSE;

lp1=ap->layers;
while(lp1!=NULL)
 {
 lkp1=lp1->links;
 while(lkp1!=NULL)
  {
  if(lkp1==lkp)
        {
        if (found==FALSE)
         {
         found=TRUE;
         lp2=lp1;
         }
        else runerror(ANSINTERR,"LINKsLAYER: Error");
        }                             /* Note: as a PRECAUTION, it       */
  lkp1=lkp1->next;                    /* continues search to see if node */
  }                                   /* is also found elsewhere.        */
 lp1=lp1->next;
 }
return lp2;
}

/*-----------------------------------------------------------------------*/

int LINKsLAYERId (ANS * ap,           /* Returns id of layer             */
                  LINK * lkp)         /* that node belongs to.           */
{
return (LINKsLAYER(ap,lkp))->id;
}

/*-----------------------------------------------------------------------*/

int NodesInLAYER(LAYER * lp)           /* expected number of nodes.      */
{
int i;
int s=1;
for(i=0;i<lp->dim;i++) s*=lp->dims[i]; /* s now contains number of NODEs.*/
return s;
}

/*-----------------------------------------------------------------------*/
/* set NODE's activation (threshold) function.                           */

NODE * SetNODEFunction(DATA(*funct)(NODE *,int), NODE * np)
{
if(no_error)
 np->outfunction=funct;
return np;
}

/*-----------------------------------------------------------------------*/

void AppendNODE (NODE * np,            /* Adds a NODE  to the end of the */
                 LAYER * lp)           /* LAYER's list of nodes.         */
{                                      /* Note:                          */
NODE * np1;                            /* It does not create NODEs,      */
NODE * np2;                            /* It does not create LINKs,      */
if(no_error)                           /* It does not change NODE.next . */
 {                                     /* It does change previous node's */
 np1=np2=lp->nodes;                    /* NODE.next.                     */

 if(np1==NULL)                         /* is the list empty?             */
  lp->nodes=np;
 else
  {
  while(np2!=NULL)
        {
        np1=np2;
        np2=np2->next;
        }
  np1->next=np;
  np->prev =np1;
  }
 }
}

/*-----------------------------------------------------------------------*/

void   AppendNODEto1DLAYER(NODE * np,LAYER * lp)
{
AppendNODE(np,lp);
lp->dims[0]++;
}

/*-----------------------------------------------------------------------*/

NODE * NewNODE(int id,int memorysize,ANS * ans)
{                                      /* Note:                          */
NODE * np;                             /* does not assign values,functs. */
                                                                                                        /* does not put it in LAYER list. */
if(no_error)
{
 np=(NODE *)MMalloc(sizeof(NODE));
 if(memorysize>0) np->stm=MMalloc1dDATA(memorysize);
 else             np->stm=NULL;

 if(no_error)
  {
  np->id         =id;
  np->stmsize    =memorysize;
  np->bias       =(DATA)0;
  np->outfunction=0;
  np->ans        =ans;
  /*
  np->in=NULL;
  np->out=NULL;
  */
  np->prev=NULL;                       /* node is NOT placed in a list   */
  np->next=NULL;                       /* of nodes yet.                  */
  }
 }
return np;
}

/*-----------------------------------------------------------------------*/

void EndNODE(NODE * np)
{
if(np!=NULL)
 {
 if(np->stmsize>0)MFree(np->stm);
 MFree(np);
 }
else
 runerror(ANSINTERR,"Node (PE) does not exist");
}

/*-----------------------------------------------------------------------*/
/* End NODE np from list of NODEs nl, while updating nl.                 */
/* returns np->next.                                                     */

NODE * RemoveNODEFromList(NODE * np, NODE ** nl)
{
NODE * next=NULL;

if(np!=NULL)
{
 next=np->next;
 if(np==*nl)
  *nl=np->next;
 else
  np->prev->next=np->next;
 if(np->next!=NULL)np->next->prev=np->prev;
 EndNODE(np);
}
return next;
}

/*-----------------------------------------------------------------------*/

void AppendLINK (LINK * cp,            /* Adds a LINK  to the end of the */
                 LAYER * lp)           /* LAYER's list of links.         */
{                                      /* Note:                          */
LINK * cp1;                            /* It does not create NODEs,      */
LINK * cp2;                            /* It does not create LINKs,      */
if(no_error)                           /* It does not change LINK.next . */
 {
 cp1=cp2=lp->links;

 if(cp1==NULL)                         /* is the list empty?             */
  lp->links=cp;
 else
  {
  while(cp2!=NULL)
   {
   cp1=cp2;
   cp2=cp2->next;
   }
  cp1->next=cp;
  cp->prev =cp1;
  }
 }
}

/*-----------------------------------------------------------------------*/
/* DoLink v1 */

LINK * DoLINK(NODE * np1,               /* this updates link information */
              NODE * np2,               /* to show connection from np1   */
              LINK * lp)                /* to np2. It does NOT create    */
                                        /* np1,np2 nor it creates lp.    */
{
if(no_error)
 {
 lp->source=np1;
 lp->destin=np2;
 }
return lp;
}

/*-----------------------------------------------------------------------*/

LINK * SetLINKWeight(DATA w, LINK * lp)
{
if(no_error)
 {
 lp->weight=w;
 }
return lp;
}

/*-----------------------------------------------------------------------*/

LINK * SetLINKFunctions(DATA (*pf)(LINK *), DATA (*lf)(LINK *), LINK * lp)
{
if(no_error)
 {
 lp->processfunction=pf;
 lp->learnfunction=lf;
 }
return lp;
}

/*-----------------------------------------------------------------------*/

LINK * NewLINK(ANS * ans, int lmsize)  /* Note: lmsize=local memory size.*/
                                       /* does not assign values,functs. */
{                                      /* does not put it in LAYER list. */
LINK * lp=NULL;

if(no_error)
{
lp=(LINK *)MMalloc(sizeof(LINK));
if(lmsize>0) lp->cbuff=MMalloc1dDATA(lmsize);
else         lp->cbuff=NULL;
if(no_error)
 {
 lp->cbuffsize=lmsize;
 lp->source=NULL;                      /* not assigned yet.              */
 lp->destin=NULL;
 lp->weight=(DATA)0;
 lp->processfunction=NULL;
 lp->learnfunction=NULL;
 lp->ans=ans;                          /* needed for access to buff(er). */
 lp->prev=NULL;                        /* link is NOT placed in a list   */
 lp->next=NULL;                        /* of links yet.                  */
 }
}
return lp;
}

/*-----------------------------------------------------------------------*/

void EndLINK(LINK * lp)
{
if(lp!=NULL)
 {
 if(lp->cbuffsize>0) MFree(lp->cbuff);
 MFree(lp);                        
 }
else
 runerror(ANSINTERR,"Link (connection) does not exist");
}

/*-----------------------------------------------------------------------*/
/* End LINK (connection) lp from list of LINKs ll, while updating ll.    */
/* Returns lp->next.                                                     */

LINK * RemoveLINKFromList(LINK * lp, LINK ** ll)
{
LINK * next=NULL;

if(lp!=NULL)
{
 next=lp->next;
 if(lp==*ll)
  *ll=lp->next;
 else
  lp->prev->next=lp->next;
 if(lp->next!=NULL)lp->next->prev=lp->prev;
 EndLINK(lp);
}
return next;
}

/*-----------------------------------------------------------------------*/

void AppendLAYER(LAYER * lp,           /* Adds a LAYER to the end of the */
                 ANS * ap)             /* ANS's list of layers.          */
{                                      /* Note:                          */
LAYER * lp1;                           /* It does not create LAYERs,     */
LAYER * lp2;                           /* It does not create LINKs,      */

if(no_error)                           /* It does not change LAYER.next. */
 {
 lp1=lp2=ap->layers;

 if(lp1==NULL)                          /* is the list empty?             */
  ap->layers=lp;
 else
  {
  while(lp2!=NULL)
   {
   lp1=lp2;
   lp2=lp2->next;
   }
  lp1->next=lp;
  lp->prev=lp1;
  }
 ap->numoflayers+=1;
 }
}

/*-----------------------------------------------------------------------*/

LAYER * NewLAYER(int id,int dim,int buffsize)
                                       /* Note:                          */
                                       /* It does not create LINKs.      */
{                                      /* It does not put it in ANS list.*/
LAYER * lp=NULL;
int i;

if(no_error)
{
lp=(LAYER *)MMalloc(sizeof(LAYER));

if(dim<1)
 runerror(ANSINTERR,"Can not create a 0-dimentional layer");

if(buffsize>0)
 {
 lp->lbuff=MMalloc1dDATA(buffsize);
 lp->lbuffsize=buffsize;
 }
else
 {
 lp->lbuff=NULL;
 lp->lbuffsize=0;
 }

if(no_error)
 {
 lp->id=id;
 lp->dim=dim;
 lp->dims=(int *)MMalloc(dim*sizeof(int));
 for(i=0;i<dim;i++)lp->dims[i]=0;
 lp->nodes=NULL;                       /* does not contain any nodes yet.*/
 lp->links=NULL;                       /* does not contain any links yet.*/
 lp->prev=NULL;                        /* layer is NOT placed in a list  */
 lp->next=NULL;                        /* of layers yet.                 */
 }
}
return lp;
}

/*-----------------------------------------------------------------------*/

LAYER * FullSetupNew1DLAYER(int dim,               /* Number of nodes.   */
                       int layerid,                /* Requested Layer ID.*/
                       int buffsize,               /* Layer buffer size. */
                       DATA(*outfunct)(NODE*,int), /* NODE threshold fnc.*/
                       int stmsize,                /* NODE stmemory size.*/
					   ANS * ap)                   /* add layer to this. */
{
int i;
LAYER * lp = NULL;
NODE * np;

if(no_error)
 {
 if(ExistsLAYERWithId(layerid,ap))
  {
  mprintf("SetupNew1DLAYER:Layer with id %d already exists\n",layerid);
  }
 else
  {
  lp=NewLAYER(layerid,1,buffsize);          /* Create 1D output layer.   */

  for(i=0;i<dim;i++)                        /* Create layer nodes.       */
   {
   np=NewNODE(i,stmsize,ap);
   SetNODEFunction(outfunct,np);            /* NODE threshold function.  */
   AppendNODEto1DLAYER(np,lp);
   }
  AppendLAYER(lp,ap);
  }
 }
return lp;
}

/*-----------------------------------------------------------------------*/

void EndLAYER(LAYER * lp)
{
NODE * np;
LINK * cp;
                                      /* redundant,see MFree definition. */
if(lp!=NULL)
{
 if(lp->lbuffsize>0) MFree(lp->lbuff);

 np=lp->nodes;
 while(np!=NULL)                               /* End all NODEs in Layer.*/
  np=RemoveNODEFromList(np,&(lp->nodes));      /* free and go to next.   */      

 cp=lp->links;                                 
 while(cp!=NULL)                               /* End LINKs from Layer.  */
  cp=RemoveLINKFromList(cp,&(lp->links));      /* free and go to next.   */

 MFree(lp->dims);
 MFree(lp);
 }
else
 runerror(ANSINTERR,"Layer does not exist");
}

/*-----------------------------------------------------------------------*/
/* End LAYER &lp from  list of LAYERs ll, while updating ll.             */
/* Returns lp->next.                                                     */

LAYER * RemoveLAYERFromList(LAYER * lp, LAYER ** ll)
{
LAYER * next=NULL;
if(lp!=NULL)
{
 next=lp->next;
 if(lp==*ll)
  *ll=lp->next;
 else
  lp->prev->next=lp->next;
 if(lp->next!=NULL)lp->next->prev=lp->prev;
 EndLAYER(lp);
}
return next;
}

/*-----------------------------------------------------------------------*/

void AppendANS(ANS * ap,               /* Adds a ANS ap to the end of    */
               ANS ** al)              /* ANS list al (of ans's).        */
{                                      /* Note:Use when more than one ans*/

ANS * ap1;
ANS * ap2;    

if(no_error)                           /* It does not change ANS.next.   */
 {
 ap1=ap2=*al;

 if(ap1==NULL)                         /* is the list empty?             */
  *al=ap;
 else
  {
  while(ap2!=NULL)
   {
   ap1=ap2;
   ap2=ap2->next;
   }
  ap1->next=ap;
  ap->prev=ap1;
  }
 }
}

/*-----------------------------------------------------------------------*/

ANS * NewANS(int ins,int outs,int buffsize)
{
ANS * ap=NULL;

if(no_error)
 {
 ap=(ANS *)MMalloc(sizeof(ANS));

 if(buffsize>0) ap->abuff=MMalloc1dDATA(buffsize);
 else           ap->abuff=NULL;

 if(no_error)
  {
  ap->inputdim=ins;
  ap->outputdim=outs;
  ap->numoflayers=0;
  ap->inputlayer=NULL;
  ap->outputlayer=NULL;
  ap->layers=NULL;                     /* does'nt contain any layers yet.*/
  ap->abuffsize=buffsize;
  ap->prev=NULL;
  ap->next=NULL;
  }
 }
return ap;
}

/*-----------------------------------------------------------------------*/

void EndANS(ANS * ap)
{
LAYER * lp;

if(ap!=NULL)
{                                     /* redundant,see MFree definition. */
 lp=ap->layers;

 while(lp!=NULL)
  lp=RemoveLAYERFromList(lp,&(ap->layers));
  
 if(ap->abuffsize>0) MFree(ap->abuff);
 MFree(ap);
 }
else
 runerror(ANSINTERR,"ANS does not exist");
}

/*-----------------------------------------------------------------------*/
/* End ANS ap from  list of ANSs al, while updating al. Returns ap->next.*/

ANS * RemoveANSFromList(ANS * ap, ANS ** al)
{
ANS * next=NULL;

if(ap!=NULL)
{
 next=ap->next;
 if(ap==*al)
  *al=ap->next;
 else
  ap->prev->next=ap->next;
 if(ap->next!=NULL) ap->next->prev=ap->prev;
 EndANS(ap);
}
return next;
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

void ShowLINK(LINK * cp, ANS * ap)
{
int i;

mprintf("...........Link (connection).\n");
mprintf("............from layer %d node %d.\n",
       NODEsLAYERId(ap,cp->source),cp->source->id);
mprintf("............to layer %d node %d.\n",
       NODEsLAYERId(ap,cp->destin),cp->destin->id);
mprintf("............Process function ");
if(cp->processfunction==NULL)mprintf("un");
mprintf("defined.\n");
mprintf("............Learn function ");
if(cp->learnfunction==NULL)mprintf("un");
mprintf("defined.\n");
mprintf("............ANS assignment ");
if(cp->ans!=ap) mprintf("in");
mprintf("correct.\n");
mprintf("............Weight ");
mprintf(DATAFORMAT,cp->weight);
mprintf(".\n");
mprintf("............Local Storage size %d.\n",cp->cbuffsize);
for(i=0;i<cp->cbuffsize;i++)
 {
 mprintf("............Local buffer %d contains ",i);
 mprintf(DATAFORMAT,cp->cbuff[i]);
 mprintf(".\n");
 }
}

/*-----------------------------------------------------------------------*/

void ShowNODE(NODE * np,LAYER * lp, ANS * ap)
{
LINK   * cp;

int i;

mprintf(".......Node (Processing Element PE) %d.\n",np->id);
mprintf("........With threshold function ");
if(np->outfunction==NULL) mprintf("un");
mprintf("defined.\n");
mprintf("........Bias (threshold value) ");
mprintf(DATAFORMAT,np->bias);
mprintf(".\n");
mprintf("........Local Storage (STM) size %d.\n",np->stmsize);
for(i=0;i<np->stmsize;i++)
 {
 mprintf("........Local STM %d contains ",i);
 mprintf(DATAFORMAT,np->stm[i]);
 mprintf(".\n");
 }
mprintf("........ANS assignment ");
if(np->ans!=ap) mprintf("in");
mprintf("correct.\n");

cp=lp->links;
while(cp!=NULL)
 {
 if(cp->source==np) ShowLINK(cp,ap);
 cp=cp->next;
 }
}

/*-----------------------------------------------------------------------*/

void ShowLAYER(LAYER * lp, ANS * ap)
{
NODE  * np;
int i;

mprintf("...Layer %d.\n",lp->id);
if(lp==ap->inputlayer)  mprintf("....(Currently set as the ANS's input layer).\n");
if(lp==ap->outputlayer) mprintf("....(Currently set as the ANS's output layer).\n");
mprintf("....Layer dimentionality %d.\n",lp->dim);
mprintf("....Actual Layer node dims ( ");
for(i=0;i<lp->dim;i++) mprintf("%d ",lp->dims[i]);
mprintf(").\n");
mprintf("....Local Storage size %d.\n",lp->lbuffsize);
for(i=0;i<lp->lbuffsize;i++)
 {
 mprintf("....Local buffer %d contains ",i);
 mprintf(DATAFORMAT,lp->lbuff[i]);
 mprintf(".\n");
 }

np=lp->nodes;
while(np!=NULL)
 {
 ShowNODE(np,lp,ap);
 np=np->next;
 }
}

/*-----------------------------------------------------------------------*/

void ShowANS(ANS * ap)
{

LAYER * lp;
int i;
static BOOL showans=TRUE;

if((no_error)&&(ap!=NULL)&&(showans))
 {
 if((showans=mrequest_yn("Show ANS structure?"))==TRUE)
  {
  mcls();
  mprintf("---------------------\n");
  mprintf("  A.N.S. Structure:\n");
  mprintf("---------------------\n");
  mprintf(" \n");

  mprintf(".ANS.\n");
  mprintf("..Input Dimention = %d.\n",ap->inputdim);
  mprintf("..Output Dimention = %d.\n",ap->outputdim);
  mprintf("..Number of layers = %d.\n",ap->numoflayers);
  mprintf("..Local Storage size ");
  mprintf(DATAFORMAT,ap->abuffsize);
  mprintf(".\n");
  for(i=0;i<ap->abuffsize;i++)
   {
   mprintf("..Local buffer %d contains ",i);
   mprintf(DATAFORMAT,ap->abuff[i]);
   mprintf(".\n");
   }

  lp=ap->layers;
  while(lp!=NULL)
   {
   ShowLAYER(lp,ap);
   lp=lp->next;
   }
  mprintf(".End-Of-ANS.\n");
  mwait();
  }
 mcls();
 }
}

/*-----------------------------------------------------------------------*/

extern BOOL LinkLogDebugMode;
extern ReportToSessionFile(char * x);

void LinkLog(LAYER * lp)
{
LINK * cp;

char s[255];

if(LinkLogDebugMode)
 {
 cp=lp->links;
 ReportToSessionFile("\n");
 while(cp!=NULL)
  {
  sprintf(s,"LNK(%d>%d)   %f",cp->source->id,cp->destin->id,(float)(cp->weight));
  ReportToSessionFile(s);
  if((cp->next)==NULL)
   ReportToSessionFile("  .  ");
  else
   ReportToSessionFile("  ,  ");
  cp=cp->next;
  }
 }
}

/*-----------------------------------------------------------------------*/

