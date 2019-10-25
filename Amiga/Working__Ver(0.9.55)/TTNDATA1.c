/*
  ---------------------
  TTNANS:
  TTNDATA1.C   ver.0.03
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  alloc/input/free Data
  ---------------------
  Also: RandomDATA
  ---------------------

*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"
#include "ttnsets.hpp"

#include "string.h"

#include "time.h"                                    /* for randomize    */

#include "TTNMEMOR.HPP"
#include "TTNFILE.HPP"
#include "TTNFNAME.HPP"

/*-----------------------------------------------------------------------*/

void CreateTrainset(void)
{
if(no_error)
 trainset=MMalloc2dDATA(trainsetsize,inputdim);
}

/*-----------------------------------------------------------------------*/

void CreateDesired(void)
{
if(no_error)
 desired=MMalloc2dDATA(trainsetsize,outputdim);
}

/*-----------------------------------------------------------------------*/

void CreateTestset(void)
{
if(no_error)
 testset=MMalloc2dDATA(testsetsize,inputdim);
}

/*-----------------------------------------------------------------------*/

void CreateOutput(void)
{
if(no_error)
 output=MMalloc2dDATA(testsetsize,outputdim);     /* full output vectors */
}

/*-----------------------------------------------------------------------*/

void CreateClassif(void)
{

if(no_error)
 classif=MMalloc1dDATA(testsetsize);          /* 1 number (class index). */
}

/*-----------------------------------------------------------------------*/

void FreeTrainset(void)
{
if(trainset!=NULL)
 {
 mprintf("Freeing current training set.\n");
 MFree2dDATA(trainset,trainsetsize);
 if(trainset==testset) testset=NULL;
 trainset=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeDesired(void)
{
if(desired!=NULL)
 {
 mprintf("Freeing current desired output set.\n");
 MFree2dDATA(desired,trainsetsize);
 desired=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeTestset(void)
{
if((testset!=trainset)&&(testset!=NULL))
 {
 mprintf("Freeing current test set.\n");
 MFree2dDATA(testset,testsetsize);
 if(trainset==testset) trainset=NULL;
 testset=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeClassif(void)
{
if(classif!=NULL)
 {
 mprintf("Freeing current classification buffer.\n");
 MFree(classif);
 classif=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeOutput(void)
{
if(output!=NULL)
 {
 mprintf("Freeing current output buffer.\n");
 MFree2dDATA(output,testsetsize);
 output=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeAllData(void)
{
FreeTrainset();
FreeDesired();
FreeTestset();
FreeClassif();
FreeOutput();

inputdim =0;                 /* dimention (width) of train,test set.*/
outputdim=0;                 /* dimention (width) of desired output.*/
trainsetsize=0;              /* number of train-set records.        */
testsetsize=0;               /* number of test-set records.         */
}

/*-----------------------------------------------------------------------*/

void Show2dDataSet(DATA ** Set, int rows, int cols)
{
int i,j;

if((no_error)&&(Set!=NULL))
for(i=0;i<rows;i++)
 {
 mprintf("%d : ",i);
 for(j=0;j<cols;j++)
  {
  mprintf(DATAFORMAT,Set[i][j]);
  mprintf(" ");
  }
 mprintf(" .\n");
 }
mwait();
mprintf(" \n");
}

/*-----------------------------------------------------------------------*/

void ShowTrainset(void)
{
if((no_error)&&(trainset!=NULL))
 if(mrequest_yn("Show Training Set?"))
  {
  mprintf("*** Current Training Set: ***\n");
  Show2dDataSet(trainset,trainsetsize,inputdim);
  }
}

/*-----------------------------------------------------------------------*/

void ShowDesired(void)
{
if((no_error)&&(desired!=NULL))
 if(mrequest_yn("Show Desired Output Set?"))
  {
  mprintf("*** Current Desired-Output Set: ***\n");
  Show2dDataSet(desired,trainsetsize,outputdim);
  }
}

/*-----------------------------------------------------------------------*/

void ShowTestset(void)
{
if((no_error)&&(testset!=NULL))
if(mrequest_yn("Show Testing Set?"))
 {
 mprintf("*** Current Testing Set: ***\n");
 Show2dDataSet(testset,testsetsize,inputdim);
 }
}

/*-----------------------------------------------------------------------*/

void ShowClassif(void)
{
int i;

if((no_error)&&(classif!=NULL))
if(mrequest_yn("Show current (last) classification?"))
{
mprintf("*** Current (last) Classification: ***\n");
for(i=0;i<testsetsize;i++)
 {
 mprintf("Item %d classified/decoded in ",i);
 mprintf(DATAFORMAT,classif[i]);
 mprintf(" \n");
 }
mwait();
}
mprintf(" \n");
}

/*-----------------------------------------------------------------------*/

void ShowOutput(void)
{
if((no_error)&&(output!=NULL))
 if(mrequest_yn("Show Current Output?"))
  {
  mprintf("*** Current ANS Output (for corresponding test set item): ***\n");
  Show2dDataSet(output,testsetsize,outputdim);
  }
}

/*-----------------------------------------------------------------------*/

BOOL ValidatedDescriptors(int * deslist, int deslistsize, int deslimit)
{
int i,j;

BOOL ok=TRUE;
BOOL warn=FALSE;

int biggestfound=-1;

if(no_error)
 {
 mprintf("Checking Descriptors ... \n");

 for(i=0;i<deslistsize;i++)
  {
  for(j=0;j<i;j++)
   if(deslist[i]==deslist[j])
    {
    mprintf("> Multiple entries for descriptor %d, only one will be saved in *.X files.\n",
             deslist[i]);
    warn=TRUE;
    }

  if(deslist[i]<biggestfound)
   {
   mprintf("> Descriptor %d misplaced, will be saved in original order.\n",
            deslist[i]);
   warn=TRUE;
   }
  else
   biggestfound=deslist[i];

  if((deslist[i]>=deslimit)||           /* (numbering starts with zero) */
     (deslist[i]<0))
   {
   mprintf("> Warning : Descriptor %d cannot be found in file.(max=%d).\n",
            deslist[i],deslimit-1);
   ok=FALSE;
   }
  }
 if(ok)
  {
  mprintf("Descriptors ");
  if(warn) mprintf ("fairly ");
  mprintf("Ok.\n");
  }
 else
  runerror(PRBDEFERR,"Bad descriptor number in .PRB file");
 }
return ok;
}

/*-----------------------------------------------------------------------*/

BOOL LoadDataSetWithSelectedColumns(FHANDLE f,          /* input file w/ */
                                    int frows,          /* assumed size  */
                                    int fcols,          /* frows X fcols.*/
				    DATA ** TargetSet,  /* Put here.     */
                                    int  *  colist,     /* Selected Cols.*/
                                    int  colistsize)    /* num of cols.  */
{
DATA ** EntireFile;
int r,c,i;
BOOL ok=FALSE;

if(no_error&&FileOpenOK(f))
 {
 EntireFile=MMalloc2dDATA(frows,fcols);/* Read entire frows X fcols file */
 if(no_error)                          /* so that any sequence of cols   */
  {                                    /* (including duplicate copies of */ 
  for(r=0;r<frows;r++)                 /* the same col or unsorted cols) */
   for(c=0;c<fcols;c++)                /* can be copied from EntireFile. */
    EntireFile[r][c]=ReadDATA(f);

  if(no_error)                         /* EntireFile read ok.            */
   {
   for(i=0;i<colistsize;i++)
    if(colist[i]<fcols)
     for(r=0;r<frows;r++)
      TargetSet[r][i]=EntireFile[r][colist[i]];   /* We ASSUME TargetSet */
   ok=TRUE;                                       /* is big enough!      */
   }
  MFree2dDATA(EntireFile,frows);
  }
 }

if(!ok)
 runerror(INPUTFERR,"Input file not accessed");
return ok;
}

/*-----------------------------------------------------------------------*/


void LoadTrainset(char * fnamein,int desnum, int * deslist) 
{
char fname[256];
int  f_rows,
     f_cols;

FHANDLE f;

if(no_error)
{
if (strcmp(fnamein,"")==0)                                      /* Null? */
 GetFilename("Please select Train Set filename",fname,"*.dat",TRUE);
else
 strcpy(fname,fnamein);

FreeTrainset();

GetDataFileDims(fname,&f_rows,&f_cols);
if(ValidatedDescriptors(deslist,desnum,f_cols))
 f=OpenInFile(fname);

if(FileOpenOK(f)&&no_error)
 {
 if(f_rows!=trainsetsize)
  {
  mprintf("Warning: Train set size changed.\n");
  mprintf("(old %d, new %d).\n",trainsetsize,f_rows);
  trainsetsize=f_rows;
  }

 if(desnum!=inputdim)
  {
  mprintf("Warning: Input dimension changed.\n");
  mprintf("(old %d, new %d).\n",inputdim,desnum);
  inputdim=desnum;
  }

 CreateTrainset();
 LoadDataSetWithSelectedColumns(f,f_rows,f_cols,
                                trainset,deslist,desnum);

 CloseFile(f);
 }
}
}

/*-----------------------------------------------------------------------*/

void LoadDesired(char * fnamein)
{
char fname[256];
FHANDLE f;
int i,j,tsize,odim;

if(no_error)
{
if (strcmp(fnamein,"")==0)                                      /* Null? */
  GetFilename("Please select Desired Output Set filename",fname,"*.dat",TRUE);
else
  strcpy(fname,fnamein);

FreeDesired();

GetDataFileDims(fname,&tsize,&odim);
f=OpenInFile(fname);

if(f!=NULL)
 {
 if(tsize!=trainsetsize)
  {
  mprintf("Warning: Train set size changed (old %d, new %d).\n",trainsetsize,tsize);
  trainsetsize=tsize;
  }

 if(odim!=outputdim)
  {
  mprintf("Warning: Output dimension changed (old %d, new %d).\n",outputdim,odim);
  outputdim=odim;
  }

 CreateDesired();

 if(no_error)
  {
  for(i=0;i<tsize;i++)
   for(j=0;j<odim;j++)
    desired[i][j]=ReadDATA(f);
  }
 CloseFile(f);
 }
}
}

/*-----------------------------------------------------------------------*/

void LoadTestset(char * fnamein,int desnum, int * deslist)
{
char fname[256];
int  f_rows,f_cols;
FHANDLE f;

if(no_error)
{
if (strcmp(fnamein,"")==0)                                      /* Null? */
 GetFilename("Please select Test Set filename",fname,"*.dat",TRUE);
else
 strcpy(fname,fnamein);

FreeTestset();

GetDataFileDims(fname,&f_rows,&f_cols);

if(ValidatedDescriptors(deslist,desnum,f_cols))
 f=OpenInFile(fname);

if(FileOpenOK(f)&&no_error)
 {
 if(f_rows!=testsetsize)
  {
  mprintf("Warning: Test set size changed.\n");
  mprintf("(old %d, new %d).\n",testsetsize,f_rows);
  testsetsize=f_rows;
  }

 if(desnum!=inputdim)
  {
  mprintf("Warning: Input dimension changed.\n");
  mprintf("(old %d, new %d).\n",inputdim,desnum);
  inputdim=desnum;
  }

 CreateTestset();

 LoadDataSetWithSelectedColumns(f,f_rows,f_cols,
                                testset,deslist,desnum);

 CloseFile(f);
 }
}
}

/*-----------------------------------------------------------------------*/

void SaveClassif(char * fnamein, char * comment, BOOL askfirst)
{
char fname[256];
FHANDLE f;
int i;
BOOL saveit;

if(no_error)
{
if(askfirst) saveit=mrequest_yn("Save classification results?");
else         saveit=TRUE;

if(saveit)
 {
 if (strcmp(fnamein,"")==0)
  GetFilename("Select output filename.",fname,"*.cla",TRUE);
 else
  strcpy(fname,fnamein);

 f=OpenOutFile(fname);

 if(f!=NULL)
  {
  WriteString(f,comment);
  WriteString(f,"\n");
  for(i=0;i<testsetsize;i++)
        {
        WriteDATA(f,classif[i]);
        WriteString(f,"\n");
	}
  CloseFile(f);
  }
 }
}
}

/*-----------------------------------------------------------------------*/

void SaveOutput(char * fnamein, char * comment, BOOL askfirst)
{
char fname[256];
FHANDLE f;
int i,j;
BOOL saveit;

if(no_error)
{
if(askfirst) saveit=mrequest_yn("Save actual output values?");
else         saveit=TRUE;

if(saveit)
 {
 if (strcmp(fnamein,"")==0)
  GetFilename("Select ANS output filename.",fname,"*.out",TRUE);
 else
  strcpy(fname,fnamein);

 f=OpenOutFile(fname);

 if(f!=NULL)
  {
  WriteString(f,comment);
  WriteString(f,"\n");
  for(i=0;i<testsetsize;i++)
   {
   for(j=0;j<outputdim;j++) WriteDATA(f,output[i][j]);
   WriteString(f,"\n");
   }
  CloseFile(f);
  }
 }
}
}

/*-----------------------------------------------------------------------*/

DATA RandomDATA(DATA low,DATA hi)
{
if (low==hi) return hi;
if (low>hi)  return 0;
return (DATA)(low + (((DATA)rand()/RAND_MAX)*(hi-low)));
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
