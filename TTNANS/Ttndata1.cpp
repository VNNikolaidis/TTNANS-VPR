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

#include "ttndef.h"
#include "ttnpros.h"
#include "ttnsets.h"
#include "ttnui.h"
#include "ttnprepr.h"

#include "string.h"

#include "time.h"                                    /* for randomize    */

#include "ttnmemor.h"
#include "ttnfile.h"
#include "ttnfname.h"

/*-----------------------------------------------------------------------*/

void CreateTrainset(void)
{
if(TGBL no_error)
 (TGBL trainset)=MMalloc2dDATA((TGBL trainsetsize),(TGBL inputdim));
}

/*-----------------------------------------------------------------------*/

void CreateDesired(void)
{
if(TGBL no_error)
 (TGBL desired)=MMalloc2dDATA((TGBL trainsetsize),(TGBL outputdim));
}

/*-----------------------------------------------------------------------*/

void CreateTestset(void)
{
if(TGBL no_error)
 (TGBL testset)=MMalloc2dDATA((TGBL testsetsize),(TGBL inputdim));
}

/*-----------------------------------------------------------------------*/

void CreateOutput(void)
{
if(TGBL no_error)
 (TGBL output)=MMalloc2dDATA((TGBL testsetsize),(TGBL outputdim));     /* full output vectors */
}

/*-----------------------------------------------------------------------*/

void CreateClassif(void)
{

if((TGBL no_error))
 (TGBL classif)=MMalloc1dDATA((TGBL testsetsize));          /* 1 number (class index). */
}

/*-----------------------------------------------------------------------*/

void FreeTrainset(void)
{
if((TGBL trainset)!=NULL)
 {
 mprintf("Freeing current training set.\n");
 MFree2dDATA((TGBL trainset),(TGBL trainsetsize));
 if((TGBL trainset)==(TGBL testset)) (TGBL testset)=NULL;
 (TGBL trainset)=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeDesired(void)
{
if((TGBL desired)!=NULL)
 {
 mprintf("Freeing current desired-output set.\n");
 MFree2dDATA((TGBL desired),(TGBL trainsetsize));
 (TGBL desired)=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeTestset(void)
{
if(((TGBL testset)!=(TGBL trainset))&&((TGBL testset)!=NULL))
 {
 mprintf("Freeing current test set.\n");
 MFree2dDATA((TGBL testset),(TGBL testsetsize));
 if((TGBL trainset)==(TGBL testset)) (TGBL trainset)=NULL;
 (TGBL testset)=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeClassif(void)
{
if((TGBL classif)!=NULL)
 {
 mprintf("Freeing current classification buffer.\n");
 MFree((TGBL classif));
 (TGBL classif)=NULL;
 }
}

/*-----------------------------------------------------------------------*/

void FreeOutput(void)
{
if((TGBL output)!=NULL)
 {
 mprintf("Freeing current output buffer.\n");
 MFree2dDATA((TGBL output),(TGBL testsetsize));
 (TGBL output)=NULL;
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

(TGBL inputdim) =0;                 /* dimention (width) of train,test set.*/
(TGBL outputdim)=0;                 /* dimention (width) of desired output.*/
(TGBL trainsetsize)=0;              /* number of train-set records.        */
(TGBL testsetsize)=0;               /* number of test-set records.         */
}



/*-----------------------------------------------------------------------*/
/* note: newcolsin < 1 => request confirmation & column size. See hint.	 */


DATA ** AdjustedColumns2dDataSet(char * targetname, DATA ** source, int r, int REF c, int newcolsin)
 {
 char message [100];

 int old_c=c;
 int new_c=newcolsin;
 int i,j,k;

 DATA ** pd = source;

 bool doit = false;

 if(TGBL no_error)
  {
  strcpy(message,"Change the column (vector) size of ");
  strcat(message,targetname);
  strcat(message," set ?");

  mprintf("Adjust (Increase-Decrease) Columns: currently processing %s set, %d rows, %d columns.\n",targetname,r,c);
 
  if(new_c<1)
   {
   if(mrequest_yn(message)) doit=true;
   }
  else
   doit=true;

  if(doit)
   {
   while(new_c<1) new_c=mrequest_int("Please enter new column size.");
   if(new_c NEQL old_c)
	{
    mhintclear();
	mhintf(false,"You are attempting to change the column size of a data set.\n");
	mhintf(false,"If the same column size variable is used by other sets, you must\n");
	mhintf(false,"make sure the same column-change steps are applied to them as well,\n");
	mhintf(false,"or their columns will be in disagreement to the column size.\n");
	mhintf(false,"(In most cases this is done automatically, but this routine does not guarantee it).\n");
	mhintf(false,"Such is the case when a separate training and testing set exists and\n");
	mhintf(false,"the column size of one or the other is changed (these two sets share the\n");
	mhintf(false,"same column size (input dimention) variable).");

	mprintf("Changing %s set columns from %d to %d...\n",targetname,old_c,new_c);

    pd=NULL;
    pd=MMalloc2dDATA (r, new_c);

    if(TGBL no_error)
     {
     for(i=0;i<r;i++)
      for(j=0;j<new_c;j++)
       pd[i][j]=(DATA)0;
     
     k=min(c,new_c);
     mprintf("Copying %d columns from old %s set.\n",k,targetname);

     for(i=0;i<r;i++)
      for(j=0;j<k;j++)
	   pd[i][j]=source[i][j];

     MFree2dDATA(source,r);
     c=new_c;
	 }
    }
   }
  }
 mprintf("Done, size of %s set is %d rows, %d columns.\n",targetname,r,c);

 if(pd==NULL)
  runerror(NULPTRERR,"Could not change column sizes.");
 return pd;   /* on success, new */
 }

/*-----------------------------------------------------------------------*/

void adjust_columns_all_data_sets()
{
if(TGBL data_set_column_sizes_late_change == true)
 {

 mprintf("\n");

 bool testset_is_trainset = false;
 int traininputdim=TGBL inputdim;

 if(TGBL trainset!=NULL)
  {
  testset_is_trainset = (TGBL testset == TGBL trainset);
  TGBL trainset = AdjustedColumns2dDataSet("training",TGBL trainset,TGBL trainsetsize,traininputdim,-1);  // here we pass the local size.
  if(testset_is_trainset) TGBL testset = TGBL trainset;
  }

//ReduceColumns("training",TGBL trainset,TGBL trainsetsize,traininputdim,-1);  // here we pass the local size.

 if((TGBL testset!=NULL)&&(NOT testset_is_trainset))
  {
  TGBL testset = AdjustedColumns2dDataSet("testing",TGBL testset,TGBL testsetsize,TGBL inputdim,traininputdim);
//ReduceColumns("testing",TGBL testset,TGBL testsetsize,TGBL inputdim,traininputdim);
  if(TGBL inputdim != traininputdim)
   {
   mprintf("Warning: Set sizes are not the same, training is now %d columns wide, testing is %d columns wide.\n",traininputdim,TGBL inputdim);
   if(mrequest_yn("Critical warning. Throw error and exit?"))
    runerror(DATASTERR,"Testing and training sets are of incompatible column sizes");
   else 
    {
    mprintf("WARNING: This is an UNSAFE CONDITION.\n");
    return;
    }
   }
  }
 else
  TGBL inputdim = traininputdim;

// if(TGBL desired!=NULL)									// this is usualy not needed.
//  ReduceColumns("desired output",TGBL desired,TGBL trainsetsize,TGBL outputdim,-1);

 mprintf("\n");
 TGBL data_set_column_sizes_late_change = false;
 }
}


/*-----------------------------------------------------------------------*/

#ifndef _CONSOLE			// VPR compilation

#include "..\vsddataset.h"
#include "ttnreprt.h"

void Show2dDataSet(DATA ** Set, int rows, int cols, char * title)
 {
 if (NOT(((TGBL no_error))&&(Set!=NULL)))
  return;

 if(TGBL p_theWnd -> ShowDataSetsInWindow())
  {
  mhintclear();
  mhintf(false,"Note:\n");
  mhintf(false,"To show the data set in the main window or avoid problems with\n");
  mhintf(false,"older win95 based systems that fail to create the data set window,\n");
  mhintf(false,"unselect the 'Misc/Data Set Window' menu option.\n");
  mhintf(false," \n");

  // Record to session file:
 
  if(sessionenabled)
   {
   int i,j;
   CString lbuf,buf;

   lbuf.Format("\n --- %s --- \n\n",title);
   ReportToSessionFile(lbuf); 

   if(((TGBL no_error))&&(Set!=NULL))
    {
    lbuf="";
    for(i=0;i<rows;i++)
     {
     lbuf.Format("# %d : \t",i);
     buf=lbuf;
     for(j=0;j<cols;j++)
      {
      lbuf.Format(DATAFORMAT_P,Set[i][j]);
      lbuf += " \t";
      buf+=lbuf;
      }
     buf+="\r\n";
     ReportToSessionFile(buf);
     }
    ReportToSessionFile(" \r\n");
   }
  }
 
 // Show:

  CVSDdataset * p_DataSetWin;
  p_DataSetWin = new CVSDdataset(Set,(unsigned)rows,(unsigned)cols,title);
  p_DataSetWin->DoModal();
  delete (p_DataSetWin);
  }

 else

  {
  int i,j;
  CString lbuf,buf;

  mprintf("\n --- %s --- \n\n",title);

  if(((TGBL no_error))&&(Set!=NULL))
   {
   lbuf="";
   for(i=0;i<rows;i++)
    {
    lbuf.Format("# %d : \t",i);
    buf=lbuf;
    for(j=0;j<cols;j++)
     {
     lbuf.Format(DATAFORMAT_P,Set[i][j]);
     lbuf += " \t";
     buf+=lbuf;
     }
    buf+="\r\n";
    mprint_(buf);
    }
   mwait();
   mprint_(" \r\n");
   }
  }
 }

#else

void Show2dDataSet(DATA ** Set, int rows, int cols, char * title)
{
int i,j;

mprintf("\n --- %s --- \n\n",title);

if(((TGBL no_error))&&(Set!=NULL))
for(i=0;i<rows;i++)
 {
 mprintf("%d: \t",i);
 for(j=0;j<cols;j++)
  {
  mprintf(DATAFORMAT_P,Set[i][j]);
  mprintf(" \t");
  }
 mprintf(" .\n");
 }
mwait();
mprintf(" \n");
}

#endif

/*-----------------------------------------------------------------------*/

void ShowTrainset(void)
{
if(((TGBL no_error))&&((TGBL trainset)!=NULL))
 if(mrequest_yn("Show Training Set?"))
  {
  Show2dDataSet((TGBL trainset),(TGBL trainsetsize),(TGBL inputdim),"Current Training Set:");
  }
}

/*-----------------------------------------------------------------------*/

void ShowDesired(void)
{
if(((TGBL no_error))&&((TGBL desired)!=NULL))
 if(mrequest_yn("Show Desired-Output Set?"))
  {
  Show2dDataSet((TGBL desired),(TGBL trainsetsize),(TGBL outputdim),"Current Desired Output Set:");
  }
}

/*-----------------------------------------------------------------------*/

void ShowTestset(void)
{
if(((TGBL no_error))&&((TGBL testset)!=NULL))
if(mrequest_yn("Show Testing Set?"))
 {
 Show2dDataSet((TGBL testset),(TGBL testsetsize),(TGBL inputdim),"Current Testing Set:");
 }
}

/*-----------------------------------------------------------------------*/

void ShowClassif(void)
{
int i;

if(((TGBL no_error))&&((TGBL classif)!=NULL))
if(mrequest_yn("Show current (last) classification?"))
{
mprintf("--- Current (last) Classification: ---\n");
for(i=0;i<(TGBL testsetsize);i++)
 {
 mprintf("Item %d classified/decoded in ",i);
 mprintf(DATAFORMAT,(TGBL classif)[i]);
 mprintf(" \n");
 }
mwait();
}
mprintf(" \n");
}

/*-----------------------------------------------------------------------*/

void ShowOutput(void)
{
if(((TGBL no_error))&&((TGBL output)!=NULL))
 if(mrequest_yn("Show Current Output?"))
  {
  Show2dDataSet((TGBL output),(TGBL testsetsize),(TGBL outputdim),"Current ANS output (for corresponding test set item):");
  }
}

/*-----------------------------------------------------------------------*/

bool ValidatedDescriptors(int * deslist, int deslistsize, int deslimit)
{
int i,j;

bool ok=true;
bool warn=false;

int biggestfound=-1;

if((TGBL no_error))
 {
 mprintf("Checking Descriptors ... \n");

 for(i=0;i<deslistsize;i++)
  {
  for(j=0;j<i;j++)
   if(deslist[i]==deslist[j])
    {
    mprintf("> Multiple entries for descriptor %d, only one will be saved in *.X files.\n",
             deslist[i]);
    warn=true;
    }

  if(deslist[i]<biggestfound)
   {
   mprintf("> Descriptor %d misplaced, will be saved in original order.\n",
            deslist[i]);
   warn=true;
   }
  else
   biggestfound=deslist[i];

  if((deslist[i]>=deslimit)||           /* (numbering starts with zero) */
     (deslist[i]<0))
   {
   mprintf("> Warning : Descriptor %d cannot be found in file.(max=%d).\n",
            deslist[i],deslimit-1);
   ok=false;
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

bool LoadDataSetWithSelectedColumns(FHANDLE f,          /* input file w/ */
                                    int frows,          /* assumed size  */
                                    int fcols,          /* frows X fcols.*/
				                    DATA ** TargetSet,  /* Put here.     */
                                    int  *  colist,     /* Selected Cols.*/
                                    int  colistsize)    /* num of cols.  */
{
DATA ** EntireFile;
int r,c,i;
bool ok=false;

if((TGBL no_error)&&FileOpenOK(f))
 {
 SeekFirstDATAinFile(f,true);
 EntireFile=MMalloc2dDATA(frows,fcols);/* Read entire frows X fcols file */
 if((TGBL no_error))                   /* so that any sequence of cols   */
  {                                    /* (including duplicate copies of */ 
  for(r=0;r<frows;r++)                 /* the same col or unsorted cols) */
   for(c=0;c<fcols;c++)                /* can be copied from EntireFile. */
    EntireFile[r][c]=ReadDATA(f);

  if((TGBL no_error))                  /* EntireFile read ok.            */
   {
   for(i=0;i<colistsize;i++)
    if(colist[i]<fcols)
     for(r=0;r<frows;r++)
      TargetSet[r][i]=EntireFile[r][colist[i]];   /* We ASSUME TargetSet */
   ok=true;                                       /* is big enough!      */
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
char fname[FILENAMELENGTH];
int  f_rows,
     f_cols;

FHANDLE f;

if((TGBL no_error))
{
if (strcmp(fnamein,"")==0)                                      /* Null? */
 GetFilename("Please select Train Set filename",fname,"*.dat",true);
else
 strcpy(fname,fnamein);

FreeTrainset();

GetDataFileDims(fname,&f_rows,&f_cols);
if(ValidatedDescriptors(deslist,desnum,f_cols))
 f=OpenInFile(fname);

if(FileOpenOK(f)&&(TGBL no_error))
 {
 if(f_rows!=(TGBL trainsetsize))
  {
  mprintf("Warning: Train set size changed.\n");
  mprintf("(old %d, new %d).\n",(TGBL trainsetsize),f_rows);
  (TGBL trainsetsize)=f_rows;
  }

 if(desnum!=(TGBL inputdim))
  {
  mprintf("Warning: Input dimension changed.\n");
  mprintf("(old %d, new %d).\n",(TGBL inputdim),desnum);
  (TGBL inputdim)=desnum;
  }

 CreateTrainset();
 LoadDataSetWithSelectedColumns(f,f_rows,f_cols,
                                (TGBL trainset),deslist,desnum);

 CloseFile(f);
 }
}
}

/*-----------------------------------------------------------------------*/

void LoadDesired(char * fnamein)
{
char fname[FILENAMELENGTH];
FHANDLE f;
int i,j,tsize,odim;

if((TGBL no_error))
{
if (strcmp(fnamein,"")==0)                                      /* Null? */
  GetFilename("Please select desired output Set filename",fname,"*.dat",true);
else
  strcpy(fname,fnamein);

FreeDesired();

GetDataFileDims(fname,&tsize,&odim);
f=OpenInFile(fname);

if(f!=NULL)
 {
 if(tsize!=(TGBL trainsetsize))
  {
  mprintf("Warning: Train set size changed (old %d, new %d).\n",(TGBL trainsetsize),tsize);
  (TGBL trainsetsize)=tsize;
  }

 if(odim!=(TGBL outputdim))
  {
  mprintf("Warning: Output dimension changed (old %d, new %d).\n",(TGBL outputdim),odim);
  (TGBL outputdim)=odim;
  }

 CreateDesired();

 if((TGBL no_error))
  {
  for(i=0;i<tsize;i++)
   for(j=0;j<odim;j++)
    (TGBL desired)[i][j]=ReadDATA(f);
  }
 CloseFile(f);
 }
}
}

/*-----------------------------------------------------------------------*/

void LoadTestset(char * fnamein,int desnum, int * deslist)
{
char fname[FILENAMELENGTH];
int  f_rows,f_cols;
FHANDLE f;

if((TGBL no_error))
{
if (strcmp(fnamein,"")==0)                                      /* Null? */
 GetFilename("Please select Test Set filename",fname,"*.dat",true);
else
 strcpy(fname,fnamein);

FreeTestset();

GetDataFileDims(fname,&f_rows,&f_cols);

if(ValidatedDescriptors(deslist,desnum,f_cols))
 f=OpenInFile(fname);

if(FileOpenOK(f)&&(TGBL no_error))
 {
 if(f_rows!=(TGBL testsetsize))
  {
  mprintf("Warning: Test set size changed.\n");
  mprintf("(old %d, new %d).\n",(TGBL testsetsize),f_rows);
  (TGBL testsetsize)=f_rows;
  }

 if(desnum!=(TGBL inputdim))
  {
  mprintf("Warning: Input dimension changed.\n");
  mprintf("(old %d, new %d).\n",(TGBL inputdim),desnum);
  (TGBL inputdim)=desnum;
  }

 CreateTestset();

 LoadDataSetWithSelectedColumns(f,f_rows,f_cols,
                                (TGBL testset),deslist,desnum);

 CloseFile(f);
 }
}
}

//////////////////////////////////////////////////////////////////////

int recalculate_number_of_classes()
 {
 bool found [MAX_NUM_CLUSTERS];
 int new_number_of_classes = 0;
 int max_classification_id = 0;
 int i;

 for (i=0;i<MAX_NUM_CLUSTERS;i++) found[i]=false;

 for (i=0;i<(TGBL testsetsize);i++)
  {
  if(((TGBL classif)[i]<0) OR ((TGBL classif)[i]>MAX_CLUSTER_ID))
   {
   mprintf("Warning: Invalid classification ID");
   return 0;
   }
  else
   {
   found[(int)(TGBL classif)[i]]=true;
   if (max_classification_id < (TGBL classif)[i]) 
    max_classification_id = (int)(TGBL classif)[i];
   }
  }

 for (i=0;i<MAX_NUM_CLUSTERS;i++) 
  if(found[i]==true) new_number_of_classes++;				
 if((TGBL testsetsize)<=0) new_number_of_classes=1;				// handle case where no items.
 
 if(new_number_of_classes!=max_classification_id+1)			// numbering starts from 0;
  mprintf("Note: Empty classes found");
 
 return new_number_of_classes;
 }

//////////////////////////////////////////////////////////////////////
// similar to packs class assignments, returns number of classes

int remove_empty_classes()
 {

 int i,c;
 int max_classification_id = 0;

 // find biggest cluster id in classification

 for (i=0;i<(TGBL testsetsize);i++)
  {
  if((TGBL classif)[i]<0) 
   {
   mprintf("Warning: Invalid classification ID");
   return 0;
   }
  if((TGBL classif)[i]>max_classification_id) max_classification_id=(int)(TGBL classif)[i];
  }

 // count non empty classes

 int old_classes_found_including_empty = max_classification_id+1;
 int non_empty_classes_found = 0;

 for (c=0;c<old_classes_found_including_empty;c++)
  {
  bool class_is_empty = true;
  for (i=0;i<(TGBL testsetsize) AND class_is_empty;i++)
   if((TGBL classif)[i]==c) 
	class_is_empty = false;
  if(NOT class_is_empty) non_empty_classes_found++;
  }

 // if no empty class found, do nothing

 if(non_empty_classes_found==old_classes_found_including_empty)
  {
  return non_empty_classes_found;
  }

 // if too many non empty classes found, error!

 if(non_empty_classes_found>MAX_CLUSTER_ID)
  {
  mprintf("Warning: Too many classes");
  return 0;
  }

 // reassign class ids, skipping empty (slow!!!)

 mprintf("Note: empty classes will be removed...");

 for (c=0;c<old_classes_found_including_empty;c++)
  {
  bool class_is_empty = true;
  for (i=0;i<(TGBL testsetsize) AND class_is_empty;i++)
   if((TGBL classif)[i]==c) 
	class_is_empty = false;
  if(class_is_empty) 
   {
   for (i=0;i<(TGBL testsetsize);i++)
    if((TGBL classif)[i]>c) 
	 (TGBL classif)[i]=(TGBL classif)[i]-1;
   c--;
   old_classes_found_including_empty--;
   }
  }

 // done 

 return recalculate_number_of_classes();
 }

//--------------------------------------------------------------------
#ifndef _CONSOLE
//--------------------------------------------------------------------


CString fixed_length_string(int num_characters, CString in_string, char fill_char /*=' '*/)
 {
 int len = in_string.GetLength();
 if(len<num_characters)
  {
  int pad_len = num_characters-len;
  CString padding;
  for(int i=0;i<pad_len;i++) padding+=fill_char;
  return in_string+padding;
  }

 return in_string.Left(num_characters);
 }

//--------------------------------------------------------------------

void WriteIntNOE(FHANDLE handle,int i)
{
fprintf(handle,"%d\t",i);
}

void WriteIntNOENL(FHANDLE handle,int i)
{
fprintf(handle,"%d\n",i);
}

extern int random (int);
//--------------------------------------------------------------------
// save classification ids to text file (NOE compatible)

void SaveClassifNoeCompatible(char * fnamein, char * comment, bool askfirst)
 {
 int i;
 bool saveit;

 if(NOT(TGBL no_error)) return;

 CString fnamenoe = fnamein;
 if (NOT fnamenoe.IsEmpty()) fnamenoe = fnamenoe + ".noesis.cla";

 if(askfirst) saveit=mrequest_yn("Save classification indexes in NOE compatible file (*.cla file) ?\n(Note: process may need to remove empty classes)");
 else         saveit=true;
 if(NOT saveit) return;

 char fname [FILENAMELENGTH];
 FHANDLE fp;

 COleDateTime t;
 t = COleDateTime::GetCurrentTime();

 if (fnamenoe.IsEmpty())
  GetFilename("Select output filename.",fname,"*.cla",true);
 else
  strcpy(fname,fnamenoe.GetBuffer(0));
 
 fp = OpenOutFile(fname);
 if(FileOpenOK(fp))
  {
  WriteString(fp,"------------------------------------------------------------\n");
  WriteString(fp,"Noesis Classification IDs\n");
  WriteString(fp,"------------------------------------------------------------\n");
  WriteString(fp,"File Version: \n");
  WriteIntNOENL(fp,3);
  WriteString(fp,"------------------------------------------------------------\n");
  WriteString(fp,"Number of data files:\n");
  WriteIntNOENL(fp,1);
  WriteString(fp,"------------------------------------------------------------\n");
  WriteString(fp,"Data file(s):\n");
  WriteStringNL(fp,"unknown_VPR_data_file.txt");
  WriteIntNOE(fp,(int)(TGBL testsetsize));
  WriteString(fp," \t");
  WriteIntNOE(fp,(int)(TGBL testsetsize));
  WriteString(fp,"\n");
  WriteString(fp,"------------------------------------------------------------\n");
  WriteString(fp,"Misc.Info:\n");
  WriteString(fp,"Method	\n");
  WriteString(fp,"VPR_ALGORITHM");
  WriteString(fp,"\n");
  WriteString(fp,comment);
  WriteString(fp,"\nCreated on ");
  CString s = t.Format( "%A, %B %d, %Y\n" );
  WriteString(fp,s.GetBuffer(1));
  WriteString(fp,"------------------------------------------------------------\n");

  int classif_number_of_classes = remove_empty_classes();
  
  if(classif_number_of_classes>0)
  if(classif_number_of_classes<MAX_NUM_CLUSTERS)									// new stuff in version 3
   {
   WriteString(fp,"Classes: \n");
   WriteIntNOE(fp,classif_number_of_classes);
   WriteString(fp,"\n");
   WriteString(fp,"------------------------------------------------------------\n");
   WriteString(fp,"Class Display Info:\n");			
   for(i=0;i<classif_number_of_classes;i++)
	{
	CString s;
	WriteIntNOE(fp,i);
	WriteString(fp," \t");
	s.Format("%d",random(100000));
	WriteString(fp,fixed_length_string(15,s,' '));
	WriteString(fp," \t");
	s.Format("%d",i%10);
	WriteString(fp,fixed_length_string(5,s,' '));
	WriteString(fp," \t");
    WriteString(fp,"'");
	s.Format("VPR%d",i);
    WriteString(fp,s.GetBuffer(0));
    WriteString(fp,"'");
    WriteString(fp," \n");
	}
   }

  WriteString(fp,"------------------------------------------------------------\n");		// end of new stuff in version 3
  WriteString(fp,"Class IDs : (file,filtered_index,unfiltered_index,class_id)\n");

  for(i=0;i<(int)(TGBL testsetsize);i++)
   {
   WriteIntNOE(fp,0);
   WriteString(fp,"\t");
   WriteIntNOE(fp,i);
   WriteString(fp,"\t");
   WriteIntNOE(fp,i);
   WriteString(fp,"\t");
   WriteIntNOE(fp,(int)(TGBL classif)[i]);
   WriteString(fp,"\n");
   }
  CloseFile(fp);
  }
 }

//--------------------------------------------------------------------
#else
//--------------------------------------------------------------------

void SaveClassifNoeCompatible(char * fnamein, char * comment, bool askfirst)
 {
 }

//--------------------------------------------------------------------
#endif // _CONSOLE
//--------------------------------------------------------------------

void SaveClassif(char * fnamein, char * comment, bool askfirst)
{
char fname[FILENAMELENGTH];
FHANDLE f;
int i;
bool saveit;

if((TGBL no_error))
{
if(askfirst) saveit=mrequest_yn("Save classification indexes (*.cla file) ?");
else         saveit=true;

if(saveit)
 {
 if (strcmp(fnamein,"")==0)
  GetFilename("Select output filename.",fname,"*.cla",true);
 else
  strcpy(fname,fnamein);

 f=OpenOutFile(fname);

 if(f!=NULL)
  {
  WriteString(f,"REM  ");
  WriteString(f,VERSION);
  WriteString(f," Output\n");
  WriteString(f,"REM  ");
  WriteString(f,comment);
  WriteString(f,"\n");
  for(i=0;i<(TGBL testsetsize);i++)
		{
		//WriteInt (f,(int)((TGBL classif)[i]));
		WriteDATA(f,(TGBL classif)[i]);
		WriteString(f,"\n");
		}
  CloseFile(f);
  }
 }

SaveClassifNoeCompatible(fnamein, comment, askfirst);
}
}

/*-----------------------------------------------------------------------*/

void SaveOutput(char * fnamein, char * comment, bool askfirst)
{
char fname[FILENAMELENGTH];
FHANDLE f;
int i,j;
bool saveit;

if((TGBL no_error))
{
if(askfirst) saveit=mrequest_yn("Save actual output values?");
else         saveit=true;

if(saveit)
 {
 if (strcmp(fnamein,"")==0)
  GetFilename("Select ANS output filename.",fname,"*.out",true);
 else
  strcpy(fname,fnamein);

 f=OpenOutFile(fname);

 if(f!=NULL)
  {
  WriteString(f,comment);
  WriteString(f,"\n");
  for(i=0;i<(TGBL testsetsize);i++)
   {
   for(j=0;j<(TGBL outputdim);j++) WriteDATA(f,(TGBL output)[i][j]);
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
