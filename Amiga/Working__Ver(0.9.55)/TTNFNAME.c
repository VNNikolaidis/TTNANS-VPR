/*
    ---------------------
    TTN_ANS:
    TTNFNAME.C   ver.0.01
    ---------------------
    TTN V.Nikolaidis
    ---------------------
    Filename Utilities.
    ---------------------

*/

#include "ttndef.hpp"
#include <string.h>

/*---------------- Return last position of t in s. ----------------------*/

int strrpos (char * s, char t)
{
int l,last=-1;
for(l=0;l<strlen(s);l++) if(s[l]==t)last=l;
return last;
}

/*--------- remove (last) extention in filename s.-----------------------*/

void RemoveFilenameExtention(char * s)
{
int l=strrpos(s,'.');

if(l<0) return;
s[l]='\0';
}

/*-------------------- Amiga - ASL file requester code ------------------*/

#ifdef _AMIGA_


void CdAndRemovePathInfo(char * pathfile)
{
}


#undef BOOL
#include <exec/types.h>
#include <exec/libraries.h>
#include <libraries/asl.h>
#include <clib/asl_protos.h>
#include <clib/exec_protos.h>

struct Library * AslBase;

void GetFilename_(char * title, char * fname, char * filter,BOOL Unused)
{
struct FileRequester *fr;

if(!(AslBase=OpenLibrary("asl.library",37L)))
  {
  mprintf("Unable to open asl.library,V37.\n");
  return;
  }

if(fr=(struct FileRequester *)AllocAslRequestTags(ASL_FileRequest,
						  TAG_DONE))
  {
  if(AslRequestTags(fr, ASLFR_Flags1,FRB_FILTERFUNC,
			ASLFR_TitleText,title,
			ASLFR_PositiveText,"Select",
			ASLFR_NegativeText,"Cancel",
			ASLFR_InitialPattern,filter,
			TAG_DONE))
	{
	strcpy(fname,"");
	if (strlen(fr->rf_Dir)!=0)
	 {
	  strcat(fname,fr->rf_Dir);
	  if (strrpos(fr->rf_Dir,'/')!=(strlen(fr->rf_Dir)-1))
	   strcat(fname,"/");
	 }
	strcat(fname,fr->rf_File);
	}
	else
	{
	mprintf("Canceled, returning NULL\n");
	strcpy(fname,NULL);
	}
  }
else
  {
  mprintf("Unable to create requester.\n");
  return;
  }
CloseLibrary(AslBase);
}


#endif

/*-------------------- DOS - Text only requester code -------------------*/

#ifdef _MSDOS_
#include <dir.h>
#include <ctype.h>
#include <stdio.h>
#include <alloc.h>

void CdAndRemovePathInfo(char * pathfile) /* cd to target directory and replace */
{                                         /* path+file with filename only.      */
char buffer[FILENAMELENGTH];
int i,lpos,j;

i=0;
lpos=-1;

while(pathfile[i]!='\0')
 {
 if(pathfile[i]=='\\') lpos=i;
 i++;
 }

if(lpos!=-1)
 {
 j=lpos;
 i=0;
 do
  {
  j++;
  buffer[i]=pathfile[j];
  i++;
  }
 while(pathfile[j]!='\0');

 pathfile[lpos]='\0';
 mprintf("Changing Directory to %s.\n",pathfile);
 chdir(pathfile);

 strcpy(pathfile,buffer);
 }


i=0;
while((isalnum(pathfile[i]))||
      (pathfile[i]=='_')||
      (pathfile[i]=='.'))i++;
pathfile[i]='\0';

}

void GetFilename_(char * title,char * fname,char * filter,BOOL nopath)
{
char nfilter[10];
char buff[FILENAMELENGTH];
int i;
BOOL filehasextention;

for(i=1;i<=strlen(filter);i++)nfilter[i-1]=filter[i];
nfilter[i-1]='\0';

mprintf(" \n");
mprintf("%s (ext: %s): ",title,filter);
scanf("%s",buff);

if((buff!=NULL)&&
   (strcmp(buff,"")!=0)&&
   (nopath))
 CdAndRemovePathInfo(buff);
strcpy(fname,buff);

filehasextention=FALSE;
for(i=0;i<strlen(fname);i++)
 if(fname[i]=='.') filehasextention=TRUE;

if(!filehasextention)
strcat(fname,nfilter);
}

#endif

/*-------------------- MS-Windows (3.1) requester code ------------------*/

#ifdef _MSWINDOWS_

#include <windows.h>
#include "TTNpros.hpp"
#include <commdlg.h>
#include <stdio.h>
#include <dos.h>
#include <io.h>
#include "ttnident.hpp"
#include "ttngui0.hpp"
#include <dir.h>
#include <ctype.h>

void CdAndRemovePathInfo(char * pathfile) /* cd to target directory and replace */
{                                         /* path+file with filename only.      */
char buffer[FILENAMELENGTH];
int i,lpos,j;

i=0;
lpos=-1;

while(pathfile[i]!='\0')
 {
 if(pathfile[i]=='\\') lpos=i;
 i++;
 }

if(lpos!=-1)
 {
 j=lpos;
 i=0;
 do
  {
  j++;
  buffer[i]=pathfile[j];
  i++;
  }
 while(pathfile[j]!='\0');

 pathfile[lpos]='\0';
 mprintf("Changing Directory to %s.\n",pathfile);
 chdir(pathfile);

 strcpy(pathfile,buffer);
 }


i=0;
while((isalnum(pathfile[i]))||
      (pathfile[i]=='_')||
      (pathfile[i]=='.'))i++;
pathfile[i]='\0';

}


/* Get file name */
void GetFilename__(char name[FILENAMELENGTH], char * ext)
  {
  static OPENFILENAME ofn;
  static char fn[FILENAMELENGTH],ft[FILENAMELENGTH];
  /* Use common dialog to get file name */
  char mod_filter[25];

  strcpy(mod_filter,"");
  strcat(mod_filter,"Suggested Files. ");   /* length = 16 + 1 extra space */
  strncat(mod_filter,ext,5);
  mod_filter[16]='\0';
  mod_filter[22]='\0';

  memset(&ofn,0,sizeof(OPENFILENAME));
  *fn=*ft='\0';
  ofn.lStructSize=sizeof(OPENFILENAME);
  ofn.hwndOwner=glb_hWnd;
/* NOTE: this is one long string and the \0's are correct */
  ofn.lpstrFilter="Problem Files. (*.prb)\0*.prb\0"
		  "Descriptor Files. (*.des)\0*.des\0"
                  "EPA Files. (*.epa)\0*.epa\0"
                  "Text Files. (*.txt)\0*.txt\0"
                  "Data Files. (*.dat)\0*.dat\0"
                  "All Files. (*.*)\0*.*\0";
  ofn.lpstrCustomFilter=(LPSTR)mod_filter;
  ofn.nFilterIndex=0;
  ofn.lpstrFile=fn;
  ofn.nMaxFile=sizeof(fn);
  ofn.lpstrFileTitle=ft;
  ofn.nMaxFileTitle=sizeof(ft);
  ofn.Flags=OFN_HIDEREADONLY|OFN_PATHMUSTEXIST /*|OFN_FILEMUSTEXIST*/;
  if (!GetOpenFileName(&ofn))
    {
    mprintf("Canceled, returning NULL\n");
/* If return is FALSE then might just be a cancel
    CommDlgExtendedError returns 0 if it was a cancel */
    strcpy(name,"");
    }
   else
    strcpy(name,fn);
  }


void GetFilename_(char * title,char * fname,char * filter,BOOL nopath)
{
char buff[FILENAMELENGTH];

MessageBox(GetFocus(),title,"Filename Request",MB_OK);
GetFilename__(buff,filter);
if((buff!=NULL)&&
   (strcmp(buff,"")!=0)&&
   (nopath))
 CdAndRemovePathInfo(buff);
strcpy(fname,buff);
}

#endif


/*-----  Pure Textbased -------------------------------------------------*/

#ifdef _PURETEXT_

void CdAndRemovePathInfo(char * pathfile)
{
}

void GetFilename_(char * title,char * fname,char * filter)
{
char nfilter[10];
int i;
BOOL filehasextention;

for(i=1;i<=strlen(filter);i++)nfilter[i-1]=filter[i];
nfilter[i-1]='\0';

mprintf(" \n");
mprintf("%s (ext: %s): ",title,filter);

scanf("%s",fname);

filehasextention=FALSE;
for(i=0;i<strlen(fname);i++)
 if(fname[i]=='.') filehasextention=TRUE;

if(!filehasextention)
strcat(fname,nfilter);
}

#endif

/*-----  All Formats ----------------------------------------------------*/

void GetFilename(char * title,char * fname,char * filter,BOOL nopath)
{
if(nopath)
 {
 mprintf("\n");
 mprintf("Filename: Request for filename only; Path will not be stored.\n");
 mprintf("\n");
 }
 
GetFilename_(title,fname,filter,nopath);
mprintf("Filename Selected : %s \n",fname);
}

void GetFileExtention(char * source, char * returned)
{
char * s;
s=strchr(source,'.');
if(s==NULL)
 strcpy(returned,"");
else
 strcpy(returned,s);
}

/*-----------------------------------------------------------------------*/
