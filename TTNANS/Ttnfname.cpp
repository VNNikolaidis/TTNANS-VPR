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

#include "ttnmain.h"

#include "ttndef.h"
#include "ttndef_o.h"
#include "ttndef_s.h"
#include "ttnui.h"
#include "ttnerror.h"
#include <string.h>

#ifndef _CONSOLE			// VPR compilation
#include "..\vsdfname.h"

/*---------------- Return last position of t in s. ----------------------*/

int strrpos (char * s, char t)
{
unsigned int l;
int last=-1;
for(l=0;l<strlen(s);l++) if(s[l]==t)last=l;
return last;
}

/*--------- remove (last) extension in filename s.-----------------------*/

void RemoveFilenameExtension(char * s)
{
int l=strrpos(s,'.');

if(l<0) return;
s[l]='\0';
}


void GetFileExtension(char * source, char * returned)
{
char * s  = NULL;
char * os = NULL;
BOOL found = FALSE;

s=strchr(source,'.');
if(s==NULL)
 strcpy(returned,"");
else
 {
 while(s!=NULL)
  {
  os = s;
  s=strchr(s,'.');
  }
 strcpy(returned,os);
 }
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

#define  _ALTERNATIVE_WIN31_REQUESTER
#ifdef   _ALTERNATIVE_WIN31_REQUESTER

#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <ctype.h>
#include <direct.h>

void CdAndRemovePathInfo(char * pathfile) 
{                                         
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
 _chdir(pathfile);

 strcpy(pathfile,buffer);
 }


i=0;
while((isalnum(pathfile[i]))||
      (pathfile[i]=='_')||
      (pathfile[i]=='.'))i++;
pathfile[i]='\0';

}

/* Get file name */
#define _INVALID_FILENAME_OR_CANCEL_ "INVALID_FILENAME_OR_CANCEL"

void GetFilename_win31_(char name[FILENAMELENGTH], char * ext)
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
  ofn.hwndOwner=(TGBL p_theWnd)->m_hWnd;
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
    mprintf("Canceled, returning empty.\n");
/* If return is false then might just be a cancel
    CommDlgExtendedError returns 0 if it was a cancel */
    strcpy(name,_INVALID_FILENAME_OR_CANCEL_);
    }
   else
    strcpy(name,fn);
  }


void GetFilename_win31(char * title,char * fname,char * filter,bool nopath)
{
char buff[FILENAMELENGTH];

MessageBox(GetFocus(),title,"Filename Request",MB_OK);
GetFilename_win31_(buff,filter);
if((buff!=NULL)&&
   (strcmp(buff,"")!=0)&&
   (nopath))
 CdAndRemovePathInfo(buff);
strcpy(fname,buff);
}

#endif //_ALTERNATIVE_WIN31_REQUESTER

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

//--------------------------------------------
//note: vc++ defines FILENAME_MAX

void GetFilename(char * title,char * fname,char * filter,bool nopath)
{
if((TGBL p_theWnd)->OldStyleFileRequesters())
 {
 mhintf(false,"Note: Using old-style file requester call.\n");
 GetFilename_win31(title,fname,filter,nopath);
 mprintf("Filename Selected : %s. \n",fname);
 if(strcmp(fname,_INVALID_FILENAME_OR_CANCEL_)==0)
  runerror(READWRERR, "No Filename Selected");
 }
else
/*
 {
 char buffer[FILENAMELENGTH];
 int fileoffset = 0;

 mhintclear();
 mhintf(false,"Selecting filenames:\n");
 mhintf(false,"\n");
 mhintf(false,"Long filenames are OK, but avoid spaces.\n");
 mhintf(false,"When in doubt enter the complete file name + extension.\n");
 mhintf(false,"\n");
 if(nopath)
  mhintf(false,"Note: Requested filename without path.\n");
 mhintf(false,"\n");

 strcpy(buffer,"");

 mprintf("Filename Requested : %s (filter = %s).\n",title,filter);
 CVSDfname sdf (title,filter,buffer,&fileoffset);
 sdf.DoModal();

 if(strlen(buffer)>0)
  mprintf("Filename Selected : %s. \n",buffer);
 else
  runerror(READWRERR, "No Filename Selected");

 if(NOT (TGBL no_error))
  {
  strcpy(fname,"Invalid_Filename");
  return;
  }

 // replace extension based on filter.
 
 bool filehasextension=false;
 int dotpos = strrpos(filter,'.');

 if((dotpos >= 0) AND (filter[dotpos+1]!='*'))
  {
  for(unsigned i=0;i<strlen(buffer);i++)
   {
   if(buffer[i]=='.')  filehasextension=true;
   if(buffer[i]=='\\') filehasextension=false;
   }

  if(NOT filehasextension)
   {
   strcat(buffer,filter+dotpos);
   mprintf("Filename Extended to %s.\n",buffer);
   }
  }

 if (nopath)
  strcpy(fname,buffer+fileoffset);
 else
  strcpy(fname,buffer);
 }
}
*/
 {
 char buffer[FILENAME_MAX];
 char type[FILENAME_MAX];
 int fileoffset = 0;

 CString strTitle, strFilter, strExtension, strDefaultName;
 
 strcpy(type,"Files with extension: (");
 strcat(type,filter);
 strcat(type,")|");
 strcat(type,filter);
 strcat(type,"|All Files (*.*)|*.*||");
 
 strTitle=title;
 strFilter=type;
//strExtension=filter;
 strExtension="";
 strDefaultName=filter;
	
 CFileDialog dlg(
		TRUE,										// Open File Dialog
		strExtension,								// Default extension
		strDefaultName,								// Default filename
		OFN_HIDEREADONLY,							// OPENFILENAME flags
		strFilter);									// Filter strings
	dlg.m_ofn.lpstrTitle = strTitle;
  //dlg.SetHelpID(IDR_MAINFRAME);

 int retval = dlg.DoModal();
 
 if (retval == IDCANCEL)  {
						  runerror(READWRERR, "No Filename Selected");
						  strcpy(fname,"Invalid_Filename");
						  return;
						  }

 if (retval == IDOK)		strncpy(buffer,dlg.GetPathName(),FILENAME_MAX-1);

 if(strlen(buffer)<=0)
  {
  runerror(READWRERR, "No Filename Selected");
  strcpy(fname,"Invalid_Filename");
  return;
  }

 // replace extension based on filter.
 
 bool filehasextension=false;
 int dotpos = strrpos(filter,'.');
 unsigned i;

 if((dotpos >= 0) AND (filter[dotpos+1]!='*'))
  {
  for(i=0;i<strlen(buffer);i++)
   {
   if(buffer[i]=='.')  filehasextension=true;
   if(buffer[i]=='\\') filehasextension=false;
   }
  if(NOT filehasextension) strcat(buffer,filter+dotpos);
  }
  
 for(i=0;i<strlen(buffer);i++)
   {
   if(buffer[i]=='\\') fileoffset=i+1;
   }
 
 if (nopath)
  strcpy(fname,buffer+fileoffset);
 else
  strcpy(fname,buffer);
 }
}
#endif // ndef _CONSOLE
