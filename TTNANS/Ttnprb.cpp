
/* --------------------
   TTNANS:
   TTNPRB.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   Problem Description File
   ------------------------ */

#include "ttndef.h"
#include "ttnmain.h"
#include "ttnpros.h"
#include "ttnsets.h"
#include "ttnprb.h"

#include "string.h"

#include "ttnfname.h"
#include "ttnfile.h"
#include "ttnmemor.h"
#include "ttndata1.h"

#include "ttnui.h"

void ShowPrbFormat(void)
{
mhintclear();
mhintf(false,"Problem Description (.PRB) File Format:\n");
mhintf(false,"---------------------------------------\n");
mhintf(false,"Supervised             : integer (0=supervised)\n");
mhintf(false,"                                 (1=unsupervised)\n");
mhintf(false,"                                 (2=clustering)\n");
mhintf(false,"Training Set Filename  : string  (all problem types (0,1,2))\n");
mhintf(false,"Desired-Output Filename: string  (opt.:supervised       (0))\n");
mhintf(false,"Test Set Filename      : string  (opt.:non-clustering (0,1))\n");
mhintf(false,"Descriptor 0           : integer \n");
mhintf(false,"Descriptor 1           : integer \n");
mhintf(false,"  ...                            \n");
mhintf(false,"Descriptor n           : integer \n");
mhintf(false,"---------------------------------------\n");
mhintf(false," \n");
}

/*-----------------------------------------------------------------------*/
void CreatePrbFile(void)
{
int msel;
int des=0;
int tr_r,tr_c;
FHANDLE f;
char fname[255];

char mtitle[]="Problem type selection";
char *menu[]={"0...Supervised  (Training,Desired Output,Test Sets)",
			  "1...Unsupervised(Training,Test Sets)",
			  "2...Clustering  (Training Set Only)"
			  };

mprintf("Creating a Problem Description .PRB File.\n");

ShowPrbFormat();

GetFilename("Please enter target filename.",fname,"*.PRB",true);

f=OpenOutFile(fname);

if(FileOpenOK(f))
 {
 mprintf("New .prb File Opened.\n");
 msel=mmenu(mtitle,menu,3,2);
 WriteInt(f,msel);
 WriteString(f,"\n");

 mhintclear();
 mhintf(false,"Note: Avoid using text data files with complex headers or mantissa notation \n");
 mhintf(false,"Keeping text data files in a simple format (containing columns of numbers)  \n");
 mhintf(false,"solves many many VPR problems ! \n");
 mhintf(false,"\n");
 mhintf(false,"If problems persist, try using shorter file or path names with no spaces etc.\n");
 mhintf(false,"\n");
 
 switch(msel)
  {
  case PT_SUPERVISED:
		   strcpy(fname,"");
	   GetFilename("Select Training Set File.",fname,"*.*",false);
		   if(fname[0]!='\0')
			{
			GetDataFileDims(fname, &tr_r, &tr_c);
			WriteString(f,fname);
			WriteString(f,"\n");
			strcpy(fname,"");
		GetFilename("Select Desired Output Set File.",fname,"*.*",false);
			if(fname[0]!='\0')
			 {
			 WriteString(f,fname);
			 WriteString(f,"\n");
			 strcpy(fname,"");
		 GetFilename("Select Test Set File.",fname,"*.*",false);
			 if(fname[0]!='\0')
			  {
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
	   GetFilename("Select Training Set File.",fname,"*.*",false);
		   if(fname[0]!='\0')
			{
			GetDataFileDims(fname, &tr_r, &tr_c);
			WriteString(f,fname);
			WriteString(f,"\n");
			strcpy(fname,"");
		GetFilename("Select Test Set File.",fname,"*.*",false);
			if(fname[0]!='\0')
			 {
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
	   GetFilename("Select Training Set File.",fname,"*.*",false);
		   if(fname[0]!='\0')
			{
			GetDataFileDims(fname, &tr_r, &tr_c);
			WriteString(f,fname);
			WriteString(f,"\n");
			}
		   else
			des=-1;
		   break;
  }

 if(des>=0)
  {
  mhintclear();
  mhintf(true,"Select desired descriptors to use in problem.\n");
  mhintf(true,"Descriptor numbering starts with 0.\n");
  mhintf(true,"(First descriptor column in file is 0.)\n");
  mhintf(true,"(Last descriptor column (in training set file) is %d.)\n",tr_c-1);

  while(des>=0)
   {
   des=mrequest_int("Select Descriptor (first=0, negative to exit)");
   if(des>=0)
	{
	if(des<tr_c)
	 {
	 WriteInt(f,des);
	 WriteString(f,"\n");
	 }
	else
	 mprintf("Valid descriptor numbers are 0..%d (did not store %d).\n",tr_c-1,des);
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

if(TGBL no_error)
 {
 mprintf("Parsing *.PRB file.\n");

 if (strcmp(fnamein,"")==0)
  GetFilename("Please select problem filename.",fname,"*.PRB",true);
 else
  strcpy(fname,fnamein);

 f=OpenInFile(fname);

 if(FileOpenOK(f))                              /* PRB file opened OK.  */
  {
  prbinfo=(PRBFILEINFO*)MMalloc(sizeof(PRBFILEINFO));  /* allocate INFO.*/

  if(TGBL no_error)
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
 mprintf(" \n");
 mprintf("File %s is ",p->prb_file);

 switch(p->problem_type)
  {
  case PT_SUPERVISED:
           mprintf("a supervised problem with ");
           mprintf("train set in file %s, ",			p->trn_file);
		   mprintf("\n");
		   mprintf("desired output set in file %s, ",	p->dsr_file);
           mprintf("test set in file %s, ",				p->tst_file);
		   mprintf("\n");
           break;
  case PT_UNSUPERVISED:
           mprintf("an unsupervised problem with ");
           mprintf("train set in file %s, ",			p->trn_file);
		   mprintf("\n");
           mprintf("test set in file %s, ",				p->tst_file);
           break;
  case PT_CLUSTERING:
           mprintf("a clustering problem with ");
           mprintf("train set in file %s, ",			p->trn_file);
		   mprintf("\n");
           break;
  default: runerror(PRBDEFERR,"");
           break;
  }

 mprintf("using descriptors [");
 for(i=0;i<(p->descriptor_dim);i++)
  mprintf("%d ",p->descriptors[i]);
 mprintf("] .\n\n");
 }
}

/*-----------------------------------------------------------------------*/

void LoadAllData(char * fnamein)                /* Load a problem(*.prb) */
{

PRBFILEINFO * p;

if((TGBL no_error))
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
            if((TGBL no_error))
			 {
             mhintclear();
             mhintf(false,"The requested number is used to form the array of 'output' vectors.\n");
			 mhintf(false,"Many methods (especialy in Batch and Experimentation mode) will\n");
             mhintf(false,"ignore or redefine this later.\n");
             mprintf("Unsupervised algorithm may need predefined number of classes.\n");
             (TGBL outputdim)=-1;
             while((TGBL outputdim)<1)
              (TGBL outputdim)=mrequest_int("Enter output size (number of classes)");
             }
            break;

   case PT_CLUSTERING:
            LoadTrainset(p->trn_file,p->descriptor_dim,p->descriptors);
            if((TGBL no_error))
             {
             (TGBL testsetsize)=(TGBL trainsetsize);
			 (TGBL testset)=(TGBL trainset);
             mhintclear();
             mhintf(false,"The requested number is used to form the array of 'output' vectors.\n");
			 mhintf(false,"Many methods (especialy in Batch and Experimentation mode) will\n");
             mhintf(false,"ignore or redefine this later.\n");
             mprintf("Clustering algorithm may need predefined number of classes.\n");
             (TGBL outputdim)=-1;
             while((TGBL outputdim)<1)
             (TGBL outputdim)=mrequest_int("Enter output size (number of classes)");
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
