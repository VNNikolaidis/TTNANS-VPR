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

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include <ctype.h>
#include <errno.h>

int file_open_counter=0;

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

BOOL FileExists(char * sourcefile)
{
BOOL r;
rename(sourcefile,sourcefile);
switch(errno)
 {
 case EIO   : r=FALSE;                           /* I/O Error (Amiga)   */
              break;
 case EEXIST: r=TRUE;                            /* File Exists         */
              break;
 case ENOENT: r=FALSE;                           /* No entity (DOS/WIN) */
              break;
 default    : r=TRUE;
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

file_open_counter++;

return handle;
}

/*-----------------------------------------------------------------------*/

FHANDLE OpenOutFile(char * destfile)
{
FHANDLE handle=NULL;
BOOL oktowrite=TRUE;

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
 else file_open_counter++;
 }
return handle;
}

/*-----------------------------------------------------------------------*/

void CloseFile(FHANDLE handle)
{
if(handle!=NULL)
 {
 fclose(handle);
 handle=NULL;
 file_open_counter--;
 }
else
 mprintf("CloseFile: File is not open (File pointer is NULL).\n");
}

/*-----------------------------------------------------------------------*/

BOOL FileOpenOK (FHANDLE f)
{
return (BOOL)(f!=NULL);
}

/*-----------------------------------------------------------------------*/

BOOL FileEOF (FHANDLE f)
{
return feof(f);
}

/*-----------------------------------------------------------------------*/

BOOL IsEmptyFile(char * fname)
{
BOOL r=FALSE;
FHANDLE f;

f=OpenInFile(fname);
if(FileOpenOK(f))
 {
 if (FileEOF(f))
  r=TRUE;
 else
  {
  fgetc(f);
  if (FileEOF(f)) r=TRUE;
  }
 CloseFile(f);
 }
return r;
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

BOOL Read2dDATA(FHANDLE f, DATA ** Array, int rows, int cols)
{
int i,j;

if(FileOpenOK(f))
 {
 for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
   Array[i][j]=ReadDATA(f);
 return TRUE;
 }
return FALSE;
}

/*-----------------------------------------------------------------------*/

BOOL ReadString(FHANDLE handle,char * s)
{
if((FileOpenOK)&&
   (fscanf(handle,"%s",s)>=1)) return TRUE;
return FALSE;
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
fprintf(handle," ");
}

/*-----------------------------------------------------------------------*/

void WriteString(FHANDLE handle,char * s)
{
fprintf(handle,"%s",s);
}

/*-----------------------------------------------------------------------*/

void WriteInt(FHANDLE handle,int i)
{
fprintf(handle,"%d",i);
}

/*-----------------------------------------------------------------------*/

BOOL Write2dDATA(FHANDLE f, DATA ** Array, int rows, int cols)
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
 return TRUE;
 }
return FALSE;
}

/*-----------------------------------------------------------------------*/
/* Skip to first DATA item in file (a valid opened text file). Returns   */
/* position of last isalpha character in file (in chars). -1 if no DATA. */

int SeekFirstDATAinFile(FHANDLE f,BOOL show)
{
char l;
int t=0,r=0;

if(no_error&&FileOpenOK(f))
 {
 RewindFile(f);

 while(!FileEOF(f))
  {
  l=(char)fgetc(f);
  if(isalpha(l))
   t=r;            /* last alpha in file */
  r++;
  }

 RewindFile(f);

 if(t!=0)
  {
  if(show)
   {
   mprintf("\n");
   mprintf("Skipping header. Header contents:\n");
   mprintf("\n");
   }
  l=' ';
  for(r=0;(r<t);r++)
   {
   if(show)mprintf("%c",l);
   l=(char)fgetc(f);
   }

  while(!(FileEOF(f)||isdigit(l)))
   {
   if(show)mprintf("%c",l);
   l=(char)fgetc(f);
   }
  if(show)mprintf("\n");
  }

 if(FileEOF(f))
  return -1;

 if(isdigit(l)||(l=='.'))
  ungetc(l,f);
 }
return t;
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
BOOL nonemptyline;
FHANDLE f;

if(no_error)
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
  SeekFirstDATAinFile(f,TRUE);

  /* Start reading */

  r=0;
  t=0;

  while(fscanf(f,DATAFORMAT,&d)!=EOF)t++;           /* Count Data Items  */

  SeekFirstDATAinFile(f,FALSE);
						    /* Count valid lines */
  nonemptyline=FALSE;
  while(!FileEOF(f))
   {
   l=fgetc(f);
   if(isdigit(l)||ispunct(l)) nonemptyline=TRUE;
   pl=l;
   if((nonemptyline)&&(l=='\n'))
    {
    r++;
    nonemptyline=FALSE;
    }
   }
  if(isdigit(pl))r++;                      /* case : EOF but no final \n */

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

