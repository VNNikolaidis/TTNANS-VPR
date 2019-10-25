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

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"
#include "ttnsets.hpp"

#include "string.h"

#include "TTNFNAME.HPP"
#include "TTNFILE.HPP"
#include "TTNMEMOR.HPP"
#include "TTNDATA1.HPP"

/*-----------------------------------------------------------------------*/

void SaveClasses(char prblmfnamein[], char outfnameinbase[], BOOL askfirst)
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
BOOL save=TRUE;
BOOL classfilesopenok=TRUE;

struct fileinforec
{
int  cluster;
char fname[FILENAMELENGTH];
FHANDLE f;
};

struct fileinforec * frecf;
struct fileinforec * frecx;

if(no_error)
{
if(askfirst)if(!mrequest_yn("Create individual class files?"))save=FALSE;

if(save)
 {
 mprintf("Saving Class (cluster) files.\n");
 mprintf("Opening .PRB File.\n");

 if (strcmp(prblmfnamein,"")==0)
  GetFilename("Please select current problem filename.",fname,"*.PRB",TRUE);
 else
  strcpy(fname,prblmfnamein);

 deslistsize=0;

 f0=OpenInFile(fname);

 if((no_error)&&(FileOpenOK(f0)))
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
  mprintf("] in %d classes. \n",outputdim);

  GetDataFileDims(fname0,&f_tsize,&f_desnum);
  ValidatedDescriptors(deslist,deslistsize,f_desnum);

  if(askfirst)
   {
   mprintf("You are about to save class files using file\n");
   mprintf("base names %s.Fn, %s.Xn (n=class).\n",outfnameinbase,outfnameinbase);
   if(mrequest_yn("Change Filename?"))
    {
    mprintf("Changing Name...\n");
    GetFilename("Select new class filename base.",string,"*",TRUE);
    RemoveFilenameExtention(string);
    if((string!=NULL)&&(strcmp(string,"")!=0))
     strcpy(outfnameinbase,string);
    strcpy(string,"");
    }
   }

  mprintf("Saving Class files...\n");
  mprintf("(Full Descriptor *.f*, Selected Descriptor *.x*).\n");

  frecf=(struct fileinforec *)MMalloc(sizeof(struct fileinforec));
  frecx=(struct fileinforec *)MMalloc(sizeof(struct fileinforec));
  if(no_error)
   {
   f0=OpenInFile(fname0);

   for(cluster=0;(cluster<outputdim)&&classfilesopenok;cluster++)
    {
    itoa(cluster,string,10);
    frecf->cluster=cluster;
    strcpy(frecf->fname,outfnameinbase);
    strcat(frecf->fname,".f");
    strcat(frecf->fname,string);
    frecf->f=OpenOutFile(frecf->fname);
    frecx->cluster=cluster;
    strcpy(frecx->fname,outfnameinbase);
    strcat(frecx->fname,".x");
    strcat(frecx->fname,string);
    frecx->f=OpenOutFile(frecx->fname);

    if((!FileOpenOK(frecf->f))||
       (!FileOpenOK(frecx->f)))
     classfilesopenok=FALSE;

    for(i=0;i<testsetsize&&classfilesopenok;i++)
     {
     if(frecf->cluster==(int)classif[i])
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
         if(h>=inputdim)runerror(PRBDEFERR,"");
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
