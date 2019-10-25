
/* --------------------
   TTNANS:
   TTNPRB.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   Problem Description File
   ------------------------ */

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"
#include "ttnsets.hpp"
#include "ttnprb.hpp"

#include "string.h"

#include "TTNFNAME.HPP"
#include "TTNFILE.HPP"
#include "TTNMEMOR.HPP"
#include "TTNDATA1.HPP"

void ShowPrbFormat(void)
{
mprintf("Problem Description (.PRB) File Format:\n");
mprintf("---------------------------------------\n");
mprintf("Supervised             : integer (0=supervised)\n");
mprintf("                                 (1=unsupervised)\n");
mprintf("                                 (2=clustering)\n");
mprintf("Training Set Filename  : string  (all problem types (0,1,2))\n");
mprintf("Desired-Output Filename: string  (opt.:supervised       (0))\n");
mprintf("Test Set Filename      : string  (opt.:non-clustering (0,1))\n");
mprintf("Descriptor 0           : integer \n");
mprintf("Descriptor 1           : integer \n");
mprintf("  ...                            \n");
mprintf("Descriptor n           : integer \n");
mprintf("---------------------------------------\n");
mprintf(" \n");
mprintf(" \n");
mprintf("Note: This *.PRB file should be in one directory along   \n");
mprintf("      with the training/testing/desired output set files.\n");
mprintf(" \n");
mprintf("Suggested size for problem name is 4 characters.\n");
mprintf(" \n");
mprintf(" \n");
}

/*-----------------------------------------------------------------------*/
void CreatePrbFile(void)
{
int msel;
int des=0;
FHANDLE f;
char fname[255];

char *menu[]={"Select algorithm type for problem.",
              "0...Supervised  (Training,Desired Output,Test Sets)",
              "1...Unsupervised(Training,Test Sets)",
              "2...Clustering  (Training Set Only)"
              };

mprintf("Creating a Problem Description .PRB File.\n");

ShowPrbFormat();

GetFilename("Please enter target filename.",fname,"*.PRB",TRUE);

f=OpenOutFile(fname);

if(FileOpenOK(f))
 {
 mprintf("New .prb File Opened.\n");
 msel=mmenu(menu,4,1,0,2);
 WriteInt(f,msel);
 WriteString(f,"\n");

 switch(msel)
  {
  case PT_SUPERVISED:
           strcpy(fname,"");
	   GetFilename("Select Training Set File.",fname,"*.*",TRUE);
           if(fname[0]!='\0')
            {
            CdAndRemovePathInfo(fname);
            WriteString(f,fname);
            WriteString(f,"\n");
            strcpy(fname,"");
	    GetFilename("Select Desired Output Set File.",fname,"*.*",TRUE);
            if(fname[0]!='\0')
             {
             CdAndRemovePathInfo(fname);
             WriteString(f,fname);
             WriteString(f,"\n");
             strcpy(fname,"");
	     GetFilename("Select Test Set File.",fname,"*.*",TRUE);
             if(fname[0]!='\0')
              {
              CdAndRemovePathInfo(fname);
              WriteString(f,fname);
              WriteString(f,"\n");
              }
             else
              des=-1;
             }
            else
             des=-1;
            }
           else
            des=-1;
           break;

  case PT_UNSUPERVISED:
           strcpy(fname,"");
	   GetFilename("Select Training Set File.",fname,"*.*",TRUE);
           if(fname[0]!='\0')
            {
            CdAndRemovePathInfo(fname);
            WriteString(f,fname);
            WriteString(f,"\n");
            strcpy(fname,"");
	    GetFilename("Select Test Set File.",fname,"*.*",TRUE);
            if(fname[0]!='\0')
             {
             CdAndRemovePathInfo(fname);
             WriteString(f,fname);
             WriteString(f,"\n");
             }
            else
             des=-1;
            }
           else
            des=-1;
           break;

  case PT_CLUSTERING:
           strcpy(fname,"");
	   GetFilename("Select Training Set File.",fname,"*.*",TRUE);
           if(fname[0]!='\0')
            {
            CdAndRemovePathInfo(fname);
            WriteString(f,fname);
            WriteString(f,"\n");
            }
           else
            des=-1;
           break;
  }

 if(des>=0)
  {
  mprintf("Select desired descriptors to use in problem.\n");
  mprintf("Descriptor numbering starts with 0.\n");
  mprintf("(First descriptor column in file is 0.)\n");

  while(des>=0)
   {
   des=mrequest_int("Select Descriptor (first=0, exit=-1)");
   if(des!=-1)
    {
    WriteInt(f,des);
    WriteString(f,"\n");
    }
   }
  }
 CloseFile(f);
 }
}

/*-----------------------------------------------------------------------*/

void FreePrbInfo(PRBFILEINFO * prbinfo)
{
if((prbinfo->descriptors)!=NULL) MFree(prbinfo->descriptors);
MFree(prbinfo);
}

/*-----------------------------------------------------------------------*/
/* Mallocs,reads and returns a problem definition struct(see TTNPRB.H).  */

PRBFILEINFO * GetPrbInfo(char * fnamein)
{


PRBFILEINFO * prbinfo = NULL;
char fname[FILENAMELENGTH];
FHANDLE f;
int pass;
int temp;

if(no_error)
 {
 mprintf("Parsing *.PRB file.\n");

 if (strcmp(fnamein,"")==0)
  GetFilename("Please select problem filename.",fname,"*.PRB",TRUE);
 else
  strcpy(fname,fnamein);

 f=OpenInFile(fname);

 if(FileOpenOK(f))                              /* PRB file opened OK.  */
  {
  prbinfo=(PRBFILEINFO*)MMalloc(sizeof(PRBFILEINFO));  /* allocate INFO.*/

  if(no_error)
   {

   prbinfo->problem_type=-1;                    /* Initial = invalid.   */
   strcpy(prbinfo->prb_file,"");
   strcpy(prbinfo->trn_file,"");
   strcpy(prbinfo->dsr_file,"");
   strcpy(prbinfo->tst_file,"");
   prbinfo->descriptor_dim=-1;
   prbinfo->descriptors=NULL;

   for(pass=0;pass<=1;pass++)
    {
    mprintf("Reading .PRB file, pass %d.\n",pass);

    strcpy(prbinfo->prb_file,fname);
    prbinfo->problem_type = ReadInt(f);

    switch(prbinfo->problem_type)
     {
     case PT_SUPERVISED:  /* supervised */
             if(
               (!ReadString(f,prbinfo->trn_file))||
               (!ReadString(f,prbinfo->dsr_file))||
               (!ReadString(f,prbinfo->tst_file))
               )
              {
              runerror(PRBDEFERR,"");
              FreePrbInfo(prbinfo);
              CloseFile(f);
              return NULL;
              }
             break;

     case PT_UNSUPERVISED: /* unsupervised */
             if(
               (!ReadString(f,prbinfo->trn_file))||
               (!ReadString(f,prbinfo->tst_file))
               )
              {
              runerror(PRBDEFERR,"");
              FreePrbInfo(prbinfo);
              CloseFile(f);
              return NULL;
              }
             break;

     case PT_CLUSTERING: /* clustering */
             if(
               (!ReadString(f,prbinfo->trn_file))
               )
              {
              runerror(PRBDEFERR,"");
              FreePrbInfo(prbinfo);
              CloseFile(f);
              return NULL;
              }
             break;

     default:runerror(PRBDEFERR,"");
             FreePrbInfo(prbinfo);
             CloseFile(f);
             return NULL;
     }

    if(pass==0)
     {
     while(!FileEOF(f))
      {
	  temp=ReadInt(f);
	  (prbinfo->descriptor_dim)++;      /* just count descrps.*/
	  }
	 RewindFile(f);
	 }
	else
	 {
	 temp=0;
	 prbinfo->descriptors=(int *)MMalloc((prbinfo->descriptor_dim)*sizeof(int));
     while(
          (!FileEOF(f))&&
          (temp<prbinfo->descriptor_dim)
          )
      {
      prbinfo->descriptors[temp]=ReadInt(f);
      temp++;
      }
     if(temp!=(prbinfo->descriptor_dim))
      {
      mprintf("Warning, read %d items out of %d.\n",
              temp,prbinfo->descriptor_dim);
      runerror(PRBDEFERR,"");
      }
     }
    }
   }
  CloseFile(f);
  }
 }
return prbinfo;
}

/*-----------------------------------------------------------------------*/

void ShowPrbInfo(PRBFILEINFO * p)
{
int i;

if(p!=NULL)
 {
 mprintf("\n");
 mprintf("File %s is",p->prb_file);

 switch(p->problem_type)
  {
  case PT_SUPERVISED:
           mprintf(" a supervised problem with");
           mprintf(" train set in file %s,\n",       p->trn_file);
           mprintf(" desired output set in file %s,",p->dsr_file);
           mprintf(" test set in file %s,\n",        p->tst_file);
           break;
  case PT_UNSUPERVISED:
           mprintf(" an unsupervised problem with");
           mprintf(" train set in file %s\n,",       p->trn_file);
           mprintf(" test set in file %s,",          p->tst_file);
           break;
  case PT_CLUSTERING:
           mprintf(" a clustering problem with");
           mprintf(" train set in file %s,\n",       p->trn_file);
           break;
  default: runerror(PRBDEFERR,"");
           break;
  }

 mprintf(" and uses [");
 for(i=0;i<(p->descriptor_dim);i++)
  mprintf("%d ",p->descriptors[i]);
 mprintf("] descriptors. \n\n");
 }
}

/*-----------------------------------------------------------------------*/

void LoadAllData(char * fnamein)                /* Load a problem(*.prb) */
{

PRBFILEINFO * p;

if(no_error)
 {
 p = GetPrbInfo(fnamein);

 if(p!=NULL)
  {

  ShowPrbInfo(p);

  switch(p->problem_type)
   {
   case PT_SUPERVISED:
            LoadTrainset(p->trn_file,p->descriptor_dim,p->descriptors);
            LoadDesired (p->dsr_file);
            LoadTestset (p->tst_file,p->descriptor_dim,p->descriptors);
            break;

   case PT_UNSUPERVISED:
            LoadTrainset(p->trn_file,p->descriptor_dim,p->descriptors);
            LoadTestset (p->tst_file,p->descriptor_dim,p->descriptors);
            if(no_error)
             {
             mprintf("Unsupervised algorithm may need predefined number of classes.\n");
             outputdim=-1;
             while(outputdim<1)
             outputdim=mrequest_int("Enter output size (number of classes)");
             }
            break;

   case PT_CLUSTERING:
            LoadTrainset(p->trn_file,p->descriptor_dim,p->descriptors);
            if(no_error)
             {
             testsetsize=trainsetsize;
             testset=trainset;
             mprintf("Clustering algorithm may need predefined number of classes.\n");
             outputdim=-1;
             while(outputdim<1)
             outputdim=mrequest_int("Enter output size (number of classes)");
             }
            break;

   default: runerror(PRBDEFERR,"");
            break;
   }
  FreePrbInfo(p);
  }
 }
}

/*-----------------------------------------------------------------------*/
