
/* --------------------
   TTNANS:
   TTNCLAFI.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ---------------------
   Class (Cluster) Files
   (.x*,.f*) additionals
   ---------------------

*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"
#include "ttnprb.hpp"

#include <string.h>

#include "TTNFILE.HPP"
#include "TTNFNAME.HPP"
#include "TTNMEMOR.HPP"
#include "TTNPREPR.HPP"
#include "TTNBANDX.HPP"
#include "TTNSETS.HPP"
#include "TTNDATA1.HPP"
#include "TTNDATA2.HPP"

/*--------------------------------------------------------------------------------------------*/
/* Check if file (fname) is a *.f* or *.x* file                                               */

BOOL is_class_file(char * fname)
{
int i;

if((fname==NULL)||(strcmp(fname,"")==0))
 {
 mprintf("Warning: No Filename.\n");
 return FALSE;
 }

i=strlen(fname)-1;
while((i>0)&&(fname[i]!='.')) i--;

if((i<=0)||
   ((fname[i+1]!='f')&&
    (fname[i+1]!='F')&&
    (fname[i+1]!='x')&&
    (fname[i+1]!='X')))
 {
 mprintf("Warning: invalid filename (%s) (not *.f* or *.x*)\n",fname);
 return FALSE;
 }

if(!FileExists(fname))
 {
 mprintf("Warning: File %s does not exist.\n",fname);
 return FALSE;
 }

return TRUE;
}


/*--------------------------------------------------------------------------------------------*/

void do_classification_filename(char * original, char * target)
{
strcpy(target,original);
RemoveFilenameExtention(target);
strcat(target,".cla");
}

/*--------------------------------------------------------------------------------------------*/
/* Avoid calling this, call class_n_filename (below) instead.                                 */

void do_class_n_filename(char * original,int n, char * nthfname)
{
int i;
char numbuffer[5];

strcpy(nthfname,original);
i=strlen(nthfname);

while((i>=0)&&(nthfname[i]!='.'))i--;
nthfname[i+2]='\0';
itoa(n,numbuffer,10);
strcat(nthfname,numbuffer);
}

/*--------------------------------------------------------------------------------------------*/
/* original must be a cluster file.  if original="test.f2", n=5, nthfname becomes "test.f5".  */

void class_n_filename(char * original, int n, char * nthfname)
{
if(no_error&&is_class_file(original))
 do_class_n_filename(original,n,nthfname);
}

/*--------------------------------------------------------------------------------------------*/

int class_number_of_class_filename(char * fname)
{
int i;
int num;
char numbuf[10];

if(!is_class_file(fname)) return -1;
strcpy(numbuf,"");
i=strlen(fname);
while((i>=0)&&(fname[i]!='.'))i--;
i=i+2;
strncpy(numbuf,fname+i,10);
sscanf(numbuf,"%d",&num);
return num;
}

/*--------------------------------------------------------------------------------------------*/
/* returns number of nonempty class files.                                                    */

int number_of_nonempty_class_files(char * fname)
{
int n=0;
int c=0;
char buf[FILENAMELENGTH];

class_n_filename(fname,c,buf);
while(FileExists(buf))
 {
 c++;
 if(!IsEmptyFile(buf)) n++;
 class_n_filename(fname,c,buf);
 }
return n;
}

/*--------------------------------------------------------------------------------------------*/
/* returns number (n) of nonempty class files, assosiates each of the n nonempty files with   */
/* its file-name class number and puts result in n-sized array index.It does NOT malloc index.*/

int index_nonempty_class_files(char * fname,int index[],int indexsize)
{
int n=0;
int c=0;
char buf[FILENAMELENGTH];

class_n_filename(fname,c,buf);
while(FileExists(buf))
 {
 c++;
 if(!IsEmptyFile(buf))
  {
  if(n<indexsize)index[n]=class_number_of_class_filename(buf);
  n++;
  }
 class_n_filename(fname,c,buf);
 }
return n;
}

/*---------------------------------------------------------------------------------------------*/

BOOL is_full_descriptor_class_filename(char *fname)
{
int i;

i=strlen(fname);
while((i>-1)&&(fname[i]!='.'))i--;
i++;
if ((fname[i]=='f')||(fname[i]=='F'))return TRUE;
return FALSE;
}

/*---------------------------------------------------------------------------------------------*/

void reconstruct_testset_sizes_from_class_files(char *fname,int *r,int *c)
{
char buffer[FILENAMELENGTH];
int br,bc,oldbc,set=0;

*r=0;
*c=0;
bc=0;
oldbc=0;

if(!is_class_file(fname))
 {
 mprintf("Bad Filename. Returning 0,0.\n");
 return;
 }

class_n_filename(fname,set,buffer);
while(FileExists(buffer))
 {
 GetDataFileDims(buffer,&br,&bc);
 *r=*r+br;
 *c=max(*c,bc);
 if((bc>0)&&(oldbc>0)&&(oldbc!=bc))
  {
  mprintf("Warning: Number of descriptors not constant. Returning 0,0.\n");
  *r=0;
  *c=0;
  return;
  }
 oldbc=bc;
 set++;
 class_n_filename(fname,set,buffer);
 }
mprintf("(%s,%d classes,%dx%d test set.)\n",fname,set,*r,*c);
}


/*---------------------------------------------------------------------------------------------*/
/* Refills classification rclass array (size r) and testset rtestset (size rxc) with data as   */
/* found in cluster files with base name fname. Note: it does NOT malloc rclass, rtestset.     */
/* Returns number of cluster files found (incuding empty ones).                                */

int reconstruct_classification_and_testset_from_class_files(char * fname,
							    int * rclass,
							    DATA ** rtestset,
							    int r,
							    int c)
{
int lr,lc,fr,fc,set=0,rpos=0,i,j;
char buffer[FILENAMELENGTH];
FHANDLE f;

mprintf("Reconstructing classification and test sets from selected class files.\n");

if(no_error)
{
reconstruct_testset_sizes_from_class_files(fname,&lr,&lc);
if((lr!=r)||(lc!=c))
 {
 mprintf("Warning: Sizes do not match. No Action taken.\n");
 return 0;
 }

class_n_filename(fname,set,buffer);
while(FileExists(buffer))
 {
 GetDataFileDims(buffer,&fr,&fc);
 f=OpenInFile(buffer);
 for(i=0;i<fr;i++)
  {
  for(j=0;j<fc;j++)
   rtestset[rpos][j]=ReadDATA(f);
  rclass[rpos]=set;
  rpos++;
  }
 CloseFile(f);
 set++;
 class_n_filename(fname,set,buffer);
 }
}
return set;
}

/*-------------------------------------------------------------------------*/

void scaled_class_n_filename(char * original, int n, char *scaled)
{
char buffer[FILENAMELENGTH];

strcpy(scaled,"_");
class_n_filename(original,n,buffer);
strcat(scaled,buffer);
}



/*-------------------------------------------------------------------------*/

void create_scaled_classification_files(char * fname,int get_scale_type)
{
int r,c;
DATA ** data;
int * clf;                                               /*classification */
int i,j,s;
int sets;
static int scale_method=-1;

FHANDLE f;
char outfname[FILENAMELENGTH];

if(is_class_file(fname))
 {
 reconstruct_testset_sizes_from_class_files(fname,&r,&c);
 data=MMalloc2dDATA(r,c);
 clf=(int *)MMalloc(r*sizeof(int));
 for(i=0;i<r;i++)clf[i]=-1;
 sets=reconstruct_classification_and_testset_from_class_files(fname,clf,data,r,c);

 mprintf("Current scaling method selected is <");
 if(scale_method==-1)mprintf("none");
 else mprintf("%d",scale_method);
 mprintf(">.\n");

 if(get_scale_type)
  scale_method=preprocess(-1,"(Scale)",data,r,c);
 else
  scale_method=preprocess(scale_method,"(Scale)",data,r,c);

 if(sets>0)
  {
  mprintf("Creating scaled copies of class (cluster) files (temp).\n");

  s=0;                                           /* save file for class s. */

  while(s<sets)
   {
   scaled_class_n_filename(fname,s,outfname);

   f=OpenOutFile(outfname);
   if(FileOpenOK(f))
    {
    for(i=0;i<r;i++)
     {
     if(clf[i]==s)
      {                                 /*  how worse can programming get? */
      for(j=0;j<c;j++)                  /* just add pressure on programmer */
       WriteDATA(f,data[i][j]);
      WriteString(f,"\n");
      }
     }
     CloseFile(f);
    }
   s++;
   scaled_class_n_filename(fname,s,outfname);         /* go to next class now. */
   }
  }
 MFree2dDATA(data,r);
 MFree(clf);
 }
}

/*-------------------------------------------------------------------------*/

void remove_scaled_classification_files(char * fname)
{
char buf[FILENAMELENGTH];

int s=0;

if(is_class_file(fname))
 {
 scaled_class_n_filename(fname,s,buf);

 while(FileExists(buf))
  {
  DeleteFile(buf);
  s++;
  scaled_class_n_filename(fname,s,buf);
  }
 }
}

/*-------------------------------------------------------------------------*/
/* loads all non empty class files with one of them specified in fname,and */
/* indexes the actual filename number. Returns number of class files       */
/* succesfully loaded. Note: Mallocs are done here!!  Pass Addresses!      */

int load_all_nonempty_class_files(
                                 char * fname,  /* name (one file in set)*/
				 DATA **** data,/* store data here       */
                                 int **r,       /* store class sizes here*/
                                 int *c,        /* (unique) vector size  */
				 int ** index   /* Assoc. class w/ file  */
                                 )
{
int N,n,i;
char fnamebuf[FILENAMELENGTH];
FHANDLE f;

N=number_of_nonempty_class_files(fname);
n=0;

if(N>0)
 {
 (*data) =(DATA ***)MMalloc(N*sizeof(DATA **));
 (*r)    =(int *)   MMalloc(N*sizeof(int));
 (*index)=(int *)   MMalloc(N*sizeof(int));

 if(no_error)
  {
  if(N!=index_nonempty_class_files(fname,*index,N))
   mprintf("Warning: File count differs.\n");
  else
   {
   /* load all non-empty class files in memory. */
   for(i=0;i<N;i++)
    {
    class_n_filename(fname,(*index)[i],fnamebuf);
    GetDataFileDims(fnamebuf,&((*r)[i]),c);
    (*data)[i]=MMalloc2dDATA((*r)[i],*c);
    f=OpenInFile(fnamebuf);
    if(no_error&&FileOpenOK(f))
     {
     mprintf("Loading Class File %s (%d x %d, indexed @%d)...",fnamebuf,(*r)[i],*c,i);
     Read2dDATA(f,(*data)[i],(*r)[i],*c);
     n++;
     mprintf("done.\n");
     CloseFile(f);
     }
    }
   }
  }
 }
return n;
}

/*-------------------------------------------------------------------------*/
/* frees memory from load_all_nonempty_class_files function (above).       */

void unload_class_files(int N,                 /* number of classes loaded */
                        DATA **** data,
                        int **r,
                        int ** index)
{
int i;
for(i=0;i<N;i++)
 MFree2dDATA((*data)[i],(*r)[i]);
MFree(*index);
MFree(*r);
MFree(*data);
}

/*-------------------------------------------------------------------------*/
/* (Returns DATA (runnum) to be compatible with batch_result_evaluation... */

DATA make_alternative_descriptor_class_files(char * fname,int runnum)
{
int r,c;
DATA ** data;
int * clf;                                               /* classification */
int i,j,k,s;
int sets;
BOOL is_in_new_des_set;
PRBFILEINFO * altprbinfo;
FHANDLE f;

static BOOL showinfo=TRUE;
static char prbfname[FILENAMELENGTH];
static char outfbase[FILENAMELENGTH];

char outfname[FILENAMELENGTH];
char outexten[FILENAMELENGTH];

mprintf("\n");
mprintf("Creating class files using alternative descriptor set. (run #%d)\n",runnum);
mprintf("\n");
if(showinfo)
 {
 mprintf("This option allows you to make class files (*.f,*.x) using   \n");
 mprintf("a descriptor set (defined in a .PRB file) other than the one \n");
 mprintf("with which the originals were created. For example, if some  \n");
 mprintf("clustering method A used to produce class files (A.x*,A.f*)  \n");
 mprintf("with the descriptor set Aset, needs to be compared with      \n");
 mprintf("clustering B (applied to the same data sets and using Bset)  \n");
 mprintf("then this method can convert A.f* full descriptor class files\n");
 mprintf("to ones where only Bset descriptors are used.                \n");
 mprintf("\n");
 mprintf("Notes:- Class numbering may change.                          \n");
 mprintf("      - Multiple entries of the same descriptor in Bset are  \n");
 mprintf("        ignored and skipped.                                 \n");
 mprintf("      - Relative order between decriptors (cols) in original \n");
 mprintf("        files is preserved (no re-ordering).                 \n");
 mprintf("\n");
 showinfo=FALSE;
 }

if((runnum<=0)||
   (strcmp(prbfname,"")==0)||
   (strcmp(outfbase,"")==0))
 {
 GetFilename("Select *.prb with desired descriptor set.",prbfname,"*.prb",TRUE);
 GetFilename("Select name for output class files.",outfbase,"*.x0",TRUE);
 }

GetFileExtention(outfbase,outexten);
batch_n_filename(outfbase,runnum,outfname,outexten);

altprbinfo=GetPrbInfo(prbfname);

if((no_error)&&(is_class_file(fname)))
 {
 mprintf("Using descriptors [ ");
 for(i=0;i<altprbinfo->descriptor_dim;i++)
  mprintf("%d ",altprbinfo->descriptors[i]);
 mprintf("].\n");

 reconstruct_testset_sizes_from_class_files(fname,&r,&c);
 data=MMalloc2dDATA(r,c);
 clf=(int *)MMalloc(r*sizeof(int));

 for(i=0;i<r;i++)clf[i]=-1;

 sets=reconstruct_classification_and_testset_from_class_files(fname,clf,data,r,c);

 if(sets>0)
  {
  mprintf("Creating alternative copies of class (cluster) files (temp).\n");

  s=0;                                        /* save file id for class s. */
					      /* Start with class 0.       */
  while(s<sets)                               /* for each set...           */
   {
   do_class_n_filename(outfname,s,outfname);  /* make output file name...  */

   f=OpenOutFile(outfname);
   if(FileOpenOK(f))
    {
    for(i=0;i<r;i++)                    /* for each row in the data set... */
     {
     if(clf[i]==s)                      /* that is of current class s...   */
      {
      for(j=0;j<c;j++)                  /* check each column...            */
       {
       is_in_new_des_set=FALSE;         /* is it in the new descriptor set?*/
       for(k=0;
           ((k<altprbinfo->descriptor_dim)&&(!is_in_new_des_set));
	   k++)
        {
        if(j==altprbinfo->descriptors[k])
         {
         is_in_new_des_set=TRUE;
	 WriteDATA(f,data[i][j]);
         }
        }
       }
      WriteString(f,"\n");
      }
     }
     CloseFile(f);
    }
   s++;
   do_class_n_filename(outfname,s,outfname);      /* go to next class now. */
   }
  }
 MFree2dDATA(data,r);
 MFree(clf);
 FreePrbInfo(altprbinfo);
 }
return (DATA)runnum;
}

/*-------------------------------------------------------------------------*/
/* (Returns DATA (runnum) to be compatible with batch_result_evaluation... */
/* Note: runnum=-1 asks for file names.                                    */
/* Note: prbfname,clafname must be alloced big enough for FILENAMELENGTH,  */
/*       do NOT pass "" in them.                                           */

DATA make_class_files_from_classification_file(char * prbfname,
					       char * clafname,int runnum)
{
int rows,cols;
int i;
FHANDLE f;

static BOOL showinfo=TRUE;
char clafbase[FILENAMELENGTH];

PRBFILEINFO * prbinfo;
DATA maxclass=-1;

mprintf("\n");
mprintf("Creating class files from classification (*.cla) file.(run #%d)\n",runnum);
mprintf("\n");

if(showinfo)
 {
 mprintf("This routine restores class files (*.f,*.x) using the\n");
 mprintf("information stored in the classifation (*.CLA) file.\n");
 mprintf("Note: Sets currently in memory will be erased.\n");
 mprintf("\n");
 showinfo=FALSE;
 }

if(runnum<0)
 {
 strcpy(prbfname,"");
 strcpy(clafbase,"");
 strcpy(clafname,"");
 }

if(strcmp(prbfname,"")==0)
 GetFilename("Select problem description file.",prbfname,"*.prb",TRUE);

if(strcmp(clafname,"")==0)
 GetFilename("Select classification to restore.",clafname,"*.cla",TRUE);

do_classification_filename(clafname,clafname);
strcpy(clafbase,clafname);
RemoveFilenameExtention(clafbase);

if(!FileExists(prbfname))
 {
 mprintf("File %s does not exist.\n",prbfname);
 return -1;
 }

if(!FileExists(clafname))
 {
 mprintf("File %s does not exist.\n",clafname);
 return -1;
 }

mprintf("Checking file %s.\n",clafname);
GetDataFileDims(clafname,&rows,&cols);
mprintf("Done.\n");
mprintf("\n");

FreeAllData();

prbinfo=GetPrbInfo(prbfname);

if(no_error)
 {
 if(prbinfo->problem_type==PT_CLUSTERING)       /* Get pseudo-testset size.*/
  GetDataFileDims(prbinfo->trn_file,            /* if PT_CLUSTERING, check */
		  &testsetsize,&inputdim);
 else                                           /* original trainset sizes */
  GetDataFileDims(prbinfo->tst_file,
		  &testsetsize,&inputdim);      /* else testset sizes.     */
 if((no_error)&&
    (cols==1)&&
    (rows==testsetsize))
  {
  inputdim=prbinfo->descriptor_dim;
  CreateClassif();

  if(no_error)
   {
   f=OpenInFile(clafname);
   if(FileOpenOK(f))
    {
    SeekFirstDATAinFile(f,FALSE);
    for(i=0;(i<rows)&&no_error;i++)
     {
     classif[i]=ReadDATA(f);                        /* this is not elegant */
     if(classif[i]>maxclass) maxclass=classif[i];   /* but we need it to   */
     }                                              /* make outputdim for  */
    CloseFile(f);                                   /* SaveClasses() call. */
    outputdim=(int)maxclass+1;
    SaveClasses(prbfname,clafbase,FALSE);
    }
   }
  }
 else
  {
  mprintf("Can't continue.(Possible cause: bad *.cla sizes: %s (%d x %d)).\n",clafname,rows,cols);
  }
 }
FreePrbInfo(prbinfo);
FreeAllData();
return (DATA)runnum;
}

/*-------------------------------------------------------------------------*/


