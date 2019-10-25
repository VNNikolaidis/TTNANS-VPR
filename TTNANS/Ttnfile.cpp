/*
  ---------------------
  TTNANS:
  TTNFILE.C    ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  ANSI File Utilities.
  ---------------------

*/

#include "ttndef.h"
#include "ttnpros.h"
#include "ttnui.h"

#include <ctype.h>
#include <errno.h>

/*-----------------------------------------------------------------------*/

#define MAX_NUM_FILES_ALLOWED_OPEN 1000
FHANDLE file_guard_file_open_handles[MAX_NUM_FILES_ALLOWED_OPEN];

static int file_open_counter=0;
static bool file_guard_init_already_done = false;

/*-----------------------------------------------------------------------*/

int get_file_open_counter()
{
return file_open_counter;
}

/*-----------------------------------------------------------------------*/

void file_guard_mark_open(FHANDLE f)
{
if(f==NULL) return;
bool saved = false;
for(int i=0;(i<MAX_NUM_FILES_ALLOWED_OPEN) AND NOT saved;i++)
 if(file_guard_file_open_handles[i]==NULL)
 {
	 file_guard_file_open_handles[i]=f;
	 saved=true;
 }
file_open_counter++;
}

void file_guard_mark_closed(FHANDLE f)
{
if(f==NULL) return;
bool cleared = false;
for(int i=0;(i<MAX_NUM_FILES_ALLOWED_OPEN) AND NOT cleared;i++)
 if(file_guard_file_open_handles[i]==f)
 {
	 file_guard_file_open_handles[i]=NULL;
	 cleared=true;
 }
file_open_counter--;
}

void file_guard_init()
{
if(NOT file_guard_init_already_done)
	{
	for(int i=0;i<MAX_NUM_FILES_ALLOWED_OPEN;i++)file_guard_file_open_handles[i]=NULL;
	file_guard_init_already_done=true;
	}
}

void file_guard_end()
{
mprintf("Closing any files marked open(%d):",file_open_counter);
for(int i=0;i<MAX_NUM_FILES_ALLOWED_OPEN;i++)
 if(file_guard_file_open_handles[i]!=NULL)
  {
  fclose(file_guard_file_open_handles[i]);
  file_guard_mark_closed(file_guard_file_open_handles[i]);
  mprintf(".");
  }
for(int i=0;i<MAX_NUM_FILES_ALLOWED_OPEN;i++)
 file_guard_file_open_handles[i]=NULL;
mprintf("Done!\n");
}

/*-----------------------------------------------------------------------*/

void RewindFile(FHANDLE f)
{
rewind(f);
}

/*-----------------------------------------------------------------------*/

void DeleteFile(char * fname)
{
remove(fname);
}

/*-----------------------------------------------------------------------*/

bool FileExists(char * sourcefile)
{
bool r;
rename(sourcefile,sourcefile);
switch(errno)
 {
 case EIO   : r=false;                           /* I/O Error (Amiga)   */
              break;
 case EEXIST: r=true;                            /* File Exists         */
              break;
 case ENOENT: r=false;                           /* No entity (DOS/WIN) */
              break;
 default    : r=true;
              break;
 }
errno=0;
return r;
}

/*-----------------------------------------------------------------------*/

FHANDLE OpenInFile(char * sourcefile)
{
FHANDLE handle;

if((handle=fopen(sourcefile,"rt"))==NULL)
 {
 runerror(INPUTFERR,"");
 return NULL;
 }

file_guard_mark_open(handle);

return handle;
}

/*-----------------------------------------------------------------------*/

FHANDLE OpenOutFile(char * destfile)
{
FHANDLE handle=NULL;
bool oktowrite=true;

if(NOT (TGBL no_error)) return NULL;

mprintf("Opening %s for Output.\n",destfile);

if(FileExists(destfile))
 oktowrite=mrequest_yn("File Exists,Overwrite?");

if(oktowrite)
 {
 if((handle=fopen(destfile,"wt"))==NULL)
  {
  runerror(OUTPUFERR,"");
  return NULL;
  }
 else 
  {
  file_guard_mark_open(handle);
  }
 }
else
 return NULL;

return handle;
}

/*-----------------------------------------------------------------------*/

void CloseFile(FHANDLE handle)
{
if(handle!=NULL)
 {
 fclose(handle);
 file_guard_mark_closed(handle);
 handle=NULL;
 }
else
 mprintf("CloseFile: File is not open (File pointer is NULL).\n");
}

/*-----------------------------------------------------------------------*/

bool FileOpenOK (FHANDLE f)
{
return (bool)(f!=NULL);
}

/*-----------------------------------------------------------------------*/

bool FileEOF (FHANDLE f)
{
if(feof(f)==0) return false;
return true;
}

/*-----------------------------------------------------------------------*/

bool IsEmptyFile(char * fname)
{
bool r=false;
FHANDLE f;

f=OpenInFile(fname);
if(FileOpenOK(f))
 {
 if (FileEOF(f))
  r=true;
 else
  {
  fgetc(f);
  if (FileEOF(f)) r=true;
  }
 CloseFile(f);
 }
return r;
}

/*-----------------------------------------------------------------------*/

bool IsDelimiter(char c)
 {
 if((unsigned)(c + 1) > 256) return false;
 return (isspace(c)) OR (c=='\t') OR (c==',');
 }

bool IsDigit(char c)
 {
 if((unsigned)(c + 1) > 256) return false;
 return (isdigit(c));
 }

/*-----------------------------------------------------------------------*/
/* Skip to first DATA item in file (a valid & open text file). Returns   */
/* position of last isalpha character in file (in chars). -1 if no DATA. */

int SeekFirstDATAinFile(FHANDLE f,bool show)
{
char l;
int t=0,r=0;

if(FileOpenOK(f))
 {
 RewindFile(f);

 bool is_mantissa = false;

 while(!FileEOF(f))
  {
  l=(char)fgetc(f);
  if(NOT((IsDigit(l)) OR
		 (IsDelimiter(l)) OR
		 (l=='+') OR
		 (l=='-') OR
		 (l=='.') OR
		 (l==EOF)))
   {
   is_mantissa = false;
   if((l=='E')OR(l=='e'))
	{
    l=(char)fgetc(f);
    if((l=='+') OR (l=='-'))
     is_mantissa=true;
	else 
     ungetc(l,f);
  	}
   if(!is_mantissa) t=r;            /* last alpha in file */
   }
  r++;
  }

 RewindFile(f);

 if(t!=0)
  {
  l='\n';

  if(show)
   {
   mprintf(" \n");
   mprintf("Skipping header.\n");
   mprintf(" \n");
   }

  /* go to last alpha in file */

  for(r=0;r<=t;r++) l=(char)fgetc(f);			

  /* go to the end of line after the last alpha */

  while((!FileEOF(f))AND(l!='\n')) l=(char)fgetc(f);
 
  /* skip spaces */

  while(!(FileEOF(f) OR isspace(l))) l=(char)fgetc(f);
  }

 if(FileEOF(f))
  return -1;

 }
return t;
}

/*-----------------------------------------------------------------------*/
/* Skip to first DATA item in file (a valid opened text file). Returns   */
/* position of last isalpha character in file (in chars). -1 if no DATA. */

int SeekFirstDATAinFile_old_version (FHANDLE f,bool show)
{
char l;
int t=0,r=0;

if(TGBL no_error&&FileOpenOK(f))
 {
 RewindFile(f);

 while(!FileEOF(f))
  {
  l=(char)fgetc(f);
  if(isalpha(l))
   t=r;            // last alpha in file 
  r++;
  }

 RewindFile(f);

 if(t!=0)
  {
  if(show)
   {
   mprintf(" \n");
   mprintf("Skipping header. Header contents:\n");
   mprintf(" \n");
   }

  l='\n';
  for(r=0;(r<t);r++)
   {
   if(show)mprintf("%c",l);
   l=(char)fgetc(f);
   }

  while(!(FileEOF(f)||IsDigit(l)))
   {
   if(show)mprintf("%c",l);
   l=(char)fgetc(f);
   }
  if(show)mprintf(" \n");
  }

 if(FileEOF(f))
  return -1;

 if(IsDigit(l)||(l=='.'))
  ungetc(l,f);
 }
return t;
}

/*-----------------------------------------------------------------------*/

DATA ReadDATA(FHANDLE handle)
{
DATA buf;

if((FileOpenOK(handle))&&(!FileEOF(handle)))
 if(fscanf(handle,DATAFORMAT,&buf))
  return(buf);
 else
  {
  buf=(DATA)0;
  runerror(INPUTFERR,"");
  }
else
 {
 buf=(DATA)0;
 runerror(EOFILEERR,"");
 }
return buf;
}

/*-----------------------------------------------------------------------*/

bool Read2dDATA(FHANDLE f, DATA ** Array, int rows, int cols)
{
int i,j;

if(FileOpenOK(f))
 {
 SeekFirstDATAinFile(f,false);

 for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
   Array[i][j]=ReadDATA(f);
 return true;
 }
return false;
}

/*-----------------------------------------------------------------------*/

bool ReadString(FHANDLE handle,char * s)
{
if((FileOpenOK)&&
   (fscanf(handle,"%s",s)>=1)) return true;
return false;
}

/*-----------------------------------------------------------------------*/

int ReadInt(FHANDLE handle)
{
int buf;

if((FileOpenOK(handle))&&(!FileEOF(handle)))
 if(fscanf(handle,"%d",&buf))
  return(buf);
 else
  {
  buf=(int)0;
  runerror(INPUTFERR,"");
  }
else
 {
 buf=(int)0;
 runerror(EOFILEERR,"");
 }
return buf;
}

/*-----------------------------------------------------------------------*/

void WriteDATA(FHANDLE handle,DATA data)
{
fprintf(handle,DATAFORMAT,data);
fprintf(handle," \t");
}

/*-----------------------------------------------------------------------*/

void WriteString(FHANDLE handle,const char * s)
{
fprintf(handle,"%s",s);
}

void WriteStringNL(FHANDLE handle,const char * s)
{
fprintf(handle,"%s\n",s);
}

/*-----------------------------------------------------------------------*/

void WriteInt(FHANDLE handle,int i)
{
fprintf(handle,"%d",i);
}

void WriteIntNL(FHANDLE handle,int i)
{
fprintf(handle,"%d\n",i);
}

/*-----------------------------------------------------------------------*/

bool Write2dDATA(FHANDLE f, DATA ** Array, int rows, int cols)
{
int i,j;

if(FileOpenOK(f))
 {
 for(i=0;i<rows;i++)
  {
  for(j=0;j<cols;j++)
   WriteDATA(f,Array[i][j]);
  WriteString(f,"\n");
  }
 return true;
 }
return false;
}

/*-----------------------------------------------------------------------*/
/* returns number of rows and collumns is a pure data file (assumes that */
/* the file is formed as a 2-d array (num of colls is same for all rows).*/
/* Ok this needs optimizing but who has the time...                      */

void GetDataFileDims(char * fname, int * rownum, int * colnum)
{
long int r=0,t=0,c;
DATA d;
int pl,l;
bool nonemptyline;
FHANDLE f;

mhintclear();
mhintf(false,"Estimating data file dimentions:\n");
mhintf(false,"\n");
mhintf(false,"Valid data files are space-tab delimited text files containing n x m data items \n");
mhintf(false,"(integers, floats etc). For best results remove any text headers from the data file.\n");
mhintf(false,"\n");
mhintf(false,"Also, make sure that the last data item in the input file is followed by a NEWLINE,\n");
mhintf(false,"or the size estimation may be incorrect.\n");

if(TGBL no_error)
 {
 if(IsEmptyFile(fname))
  {
  *rownum=0;
  *colnum=0;
  return;
  }

 f=OpenInFile(fname);

 if(FileOpenOK(f))
  {
  SeekFirstDATAinFile(f,true);

  /* Start reading */

  r=0;
  t=0;

  while(fscanf(f,DATAFORMAT,&d)!=EOF)t++;           /* Count Data Items  */

  SeekFirstDATAinFile(f,false);
  													/* Count valid lines */
  nonemptyline=false;
  while(!FileEOF(f))
   {
   l=fgetc(f);
   if(IsDigit(l)||ispunct(l)) nonemptyline=true;
   pl=l;
   if((nonemptyline)&&(l=='\n'))
    {
    r++;
    nonemptyline=false;
    }
   }
  if(IsDigit(pl))r++;						/* case : EOF but no final \n */

  CloseFile(f);

  if((r==0)&&(nonemptyline))r=1;
  if(r!=0) c=t/r;
  else c=0;
  *rownum=(int)r;
  *colnum=(int)c;
  return;
  }
 }
*rownum=0;
*colnum=0;
}

/*
void GetDataFileDims(char * fname, int * rownum, int * colnum)
{
GetDataFileDims_(fname,rownum,colnum);
mprintf("(File %s, size: %d rows x %d columns.)\n",fname,*rownum,*colnum);
}
*/

/*-----------------------------------------------------------------------*/

