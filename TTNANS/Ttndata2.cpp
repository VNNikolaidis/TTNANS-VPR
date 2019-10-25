/*
  ---------------------
  TTNANS:
  TTNDATA2.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Additional I/O Data
  routines.
  ---------------------

*/

#include "ttndef.h"
#include "ttnpros.h"
#include "ttnmain.h"
#include "ttnsets.h"
#include "ttnui.h"

#include "string.h"

#include "ttnfname.h"
#include "ttnfile.h"
#include "ttnmemor.h"
#include "ttndata1.h"

/*-----------------------------------------------------------------------*/

void SavePreprocessedClasses (char outfnameinbase[], bool askfirst)
{
char fname [FILENAMELENGTH];
char fnam0 [FILENAMELENGTH];
char fext  [50];

FHANDLE f;

bool save=true;
bool classfilesopenok=true;

if(TGBL no_error)
 {

 mhintclear();
 mhintf(false,"Save preprocessed classes:\n");
 mhintf(false,"Creates class files based on the same set that was used by the \n");
 mhintf(false,"(presumably clustering) algorithm to produce the classification results. \n");
 mhintf(false,"(the 'testing' set if exists, the 'training' set otherwise).\n");
 mhintf(false,"Note: These class files preserve any preprocessing performed on the set.\n");
 mhintf(false,"\n");

 if(askfirst)
  if(!mrequest_yn("Save preprocessed individual class files?"))
   save=false;

 if(save)
  {
  strcpy(fnam0,outfnameinbase);

  if(askfirst)
   {
   mprintf("You are about to save class files using file base names %s.Sn (n=class).\n",outfnameinbase);
   if(mrequest_yn("Change Filename?"))
    {
    mprintf("Changing Name...\n");
    GetFilename("Select new class filename base.",fname,"*",true);
    RemoveFilenameExtension(fname);
    if((fname!=NULL)&&(strcmp(fname,"")!=0)) strcpy(fnam0,fname);
    strcpy(fname,"");
    }
   }

  mprintf("Spliting test set in class (cluster) files and saving.\n");
  mprintf("Saving preprocessed Class files (*.s*)...\n");

  for(int cluster=0;(cluster<(TGBL outputdim))&&classfilesopenok;cluster++)
   {
   itoa(cluster,fext,10);
   strcpy(fname,fnam0);
   strcat(fname,".s");
   strcat(fname,fext);
   f=OpenOutFile(fname);

   if(!FileOpenOK(f))classfilesopenok=false;

   for(int i=0;i<(TGBL testsetsize)&&classfilesopenok;i++)
	{
	if(cluster==(int)(TGBL classif)[i])
	{
	for(int j=0;j<TGBL inputdim;j++)
	 WriteDATA(f,TGBL testset[i][j]);
	WriteString(f,"\n");
	}
   }
   CloseFile(f);
   }

  if(!classfilesopenok)
   mprintf("Warning:One or more class files were not created.\n");
  }
 }
}

/*-----------------------------------------------------------------------*/

void SaveClasses(char prblmfnamein[], char outfnameinbase[], bool askfirst)
{
char fname [FILENAMELENGTH];
char fname0[FILENAMELENGTH];
char string[FILENAMELENGTH];

FHANDLE f0;

int  deslistsize;                               /* descriptor list size. */
int  * deslist;                                 /* descriptor list.      */
int  prbtype;                                   /* problem type (0,1,2). */
int  pass,buff;
int  f_tsize,f_desnum;
DATA Dbuff;
int  i,h,j,k,cluster;
bool save=true;
bool classfilesopenok=true;

struct fileinforec
{
int  cluster;
char fname[FILENAMELENGTH];
FHANDLE f;
};

struct fileinforec * frecf;
struct fileinforec * frecx;

if(TGBL no_error)
{

mhintclear();
mhintf(false,"Save classes:\n");
mhintf(false,"Creates class files based on the original data file of the problem.\n");
mhintf(false,"(the 'testing' data file if exists, the 'training' data file otherwise).\n");
mhintf(false,"Note: The classes created here do NOT preserve any preprocessing.\n");
mhintf(false,"\n");

if(askfirst)if(!mrequest_yn("Create individual class files?"))save=false;

if(save)
 {
 mprintf("Saving Class (cluster) files.\n");
 mprintf("Opening .PRB File.\n");

 if (strcmp(prblmfnamein,"")==0)
  GetFilename("Please select current problem filename.",fname,"*.PRB",true);
 else
  strcpy(fname,prblmfnamein);

 deslistsize=0;

 f0=OpenInFile(fname);

 if((TGBL no_error)&&(FileOpenOK(f0)))
  {
  for(pass=0;pass<=1;pass++)
		{
		mprintf("Reading .PRB file, pass %d.\n",pass);

		prbtype=(int)ReadDATA(f0);

		switch(prbtype)
		 {
		 case 0 :/* supervised */
								if(
								(fscanf(f0,"%s",fname0)<1)||
								(fscanf(f0,"%s",fname0)<1)||
								(fscanf(f0,"%s",fname0)<1)         /* we only care for last. */
								)
								runerror(PRBDEFERR,"");
								break;
		 case 1 :/* unsupervised */
								if(
								(fscanf(f0,"%s",fname0)<1)||
								(fscanf(f0,"%s",fname0)<1)
								)
								runerror(PRBDEFERR,"");
								break;
		 case 2 :/* clustering */
								if(fscanf(f0,"%s",fname0)<1)
								runerror(PRBDEFERR,"");
								break;
		 default:runerror(PRBDEFERR,"");
								break;
		 }

		if(pass==0)
		 {
		 while(fscanf(f0,"%d",&buff)!=EOF)deslistsize++; /*just count descrps.*/
		 RewindFile(f0);
		 }
		else
		 {
		 buff=0;
		 deslist=(int *)MMalloc(deslistsize*sizeof(int));
		 while(
			  (fscanf(f0,"%d",&deslist[buff])!=EOF)&&
			  (buff<deslistsize)
			  )
			  buff++;
		 if(buff!=deslistsize) runerror(PRBDEFERR,"");
		 }
		}

  CloseFile(f0);

  mprintf("Problem %s requests processing of file %s,\n",fname,fname0);
  mprintf("using descriptors [");
  for(buff=0;buff<deslistsize;buff++) mprintf("%d ",deslist[buff]);
  mprintf("] in %d classes. \n",(TGBL outputdim));

  GetDataFileDims(fname0,&f_tsize,&f_desnum);
  ValidatedDescriptors(deslist,deslistsize,f_desnum);

  char outfnamebase [FILENAMELENGTH];
  strcpy(outfnamebase,outfnameinbase);

  if(askfirst)
   {
   mprintf("You are about to save class files using file\n");
   mprintf("base names %s.Fn, %s.Xn (n=class).\n",outfnamebase,outfnamebase);
   if(mrequest_yn("Change Filename?"))
	{
	mprintf("Changing Name...\n");
	GetFilename("Select new class filename base.",string,"*",true);
	RemoveFilenameExtension(string);
	if((string!=NULL)&&(strcmp(string,"")!=0))
	 strcpy(outfnamebase,string);
	strcpy(string,"");
	}
   }

  mprintf("Saving Class files...\n");
  mprintf("(Full Descriptor *.f*, Selected Descriptor *.x*).\n");

  frecf=(struct fileinforec *)MMalloc(sizeof(struct fileinforec));
  frecx=(struct fileinforec *)MMalloc(sizeof(struct fileinforec));
  if(TGBL no_error)
   {
   f0=OpenInFile(fname0);

   for(cluster=0;(cluster<(TGBL outputdim))&&classfilesopenok;cluster++)
	{
	itoa(cluster,string,10);
	frecf->cluster=cluster;
	strcpy(frecf->fname,outfnamebase);
	strcat(frecf->fname,".f");
	strcat(frecf->fname,string);
	frecf->f=OpenOutFile(frecf->fname);
	frecx->cluster=cluster;
	strcpy(frecx->fname,outfnamebase);
	strcat(frecx->fname,".x");
	strcat(frecx->fname,string);
	frecx->f=OpenOutFile(frecx->fname);

	if((!FileOpenOK(frecf->f))||
	   (!FileOpenOK(frecx->f)))
	 classfilesopenok=false;

	for(i=0;i<(TGBL testsetsize)&&classfilesopenok;i++)
	 {
	 if(frecf->cluster==(int)(TGBL classif)[i])
	  {
	  for(j=0;j<f_desnum;j++)
	   {
	   Dbuff=ReadDATA(f0);
	   WriteDATA(frecf->f,Dbuff);

	   h=0;
	   for(k=0;k<deslistsize;k++)
		{
		if(deslist[k]==j)
		 {
		 if(h>=(TGBL inputdim))runerror(PRBDEFERR,"");
		 WriteDATA(frecx->f,Dbuff);
		 h++;
		 k=deslistsize;
		 }
		}
	   }
	  WriteString(frecf->f,"\n");
	  WriteString(frecx->f,"\n");
	  }
	 else
	  for(j=0;j<f_desnum;j++)ReadDATA(f0);
	 }
	RewindFile(f0);
	CloseFile(frecf->f);
	CloseFile(frecx->f);
	}

   if(!classfilesopenok)
	mprintf("Warning:One or more class files were not created.\n");

   CloseFile(f0);
   MFree(frecf);
   MFree(frecx);
   }
  MFree(deslist);
  }
 }
}
}

/*-----------------------------------------------------------------------*/
