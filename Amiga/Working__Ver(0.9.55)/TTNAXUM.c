/*
   --------------------
   TTNANS:
   TTNaxum.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   Axum interface
   ------------------------
*/

#include "ttndef.hpp"

#include <string.h>

#ifdef _MSWINDOWS_
#define _AXUM_COMPATIBLE_
void CallAxum_(char * axum,char * param)
{
char callthis[2*FILENAMELENGTH];
strcpy(callthis,axum);
strcat(callthis," ");
strcat(callthis,param);
WinExec(callthis,SW_SHOW);
}
#endif

#ifdef _MSDOS_
#define _AXUM_COMPATIBLE_  1
void CallAxum_(char * axum,char * param)
{
char callthis[2*FILENAMELENGTH];
strcpy(callthis,axum);
strcat(callthis," ");
strcat(callthis,param);
system(callthis);
}
#endif

/*
typical axum history line:"Import FileName = C:\AXUM\DATA\T02M2_X0., FileType = ASCII, DataSheet = T02M2_X0, StartCol = 1, EndCol = END, NameRow = 0, StartRow = 1, EndRow = END, Delimiters = { ,\t};"
*/

#ifdef _AXUM_COMPATIBLE_

#include <dir.h>

#include "TTNUI.HPP"
#include "TTNFILE.HPP"
#include "TTNFNAME.HPP"
#include "TTNCLAFI.HPP"
#include "TTNERROR.HPP"

void CallAxum(void)
{
BOOL ok=TRUE;
int i,j;
FHANDLE historyfile;

static BOOL axumlocated=FALSE;
static char Axumlocation[FILENAMELENGTH];
char Axumlocation2[FILENAMELENGTH];
char Axumhistory[FILENAMELENGTH];
char Axumhistoryfile[FILENAMELENGTH];
char Classfname[FILENAMELENGTH];
char Currentdir[FILENAMELENGTH];
char HistoryLine[255];

if(!axumlocated)strcpy(Axumlocation,"c:\\axum\\axum.exe");

while((!FileExists(Axumlocation))&&(ok))
 {
 axumlocated=FALSE;
 mprintf("Failed locating Axum at %s.\n",Axumlocation);
 ok=mrequest_yn("Retry locating Axum?");
 if(ok)
  GetFilename("Please locate axum.exe.",Axumlocation,"*.exe",FALSE);
 }

if(ok)
 {
 axumlocated=TRUE;
 strcpy(Axumhistory,Axumlocation);
 i=0;
 j=0;
 while(Axumhistory[i]!='\0')
  {
  if(Axumhistory[i]=='\\')
   j=i;
  i++;
  }
 Axumhistory[j]='\0';
 strcat(Axumhistory,"\\HISTORY");

 mprintf("Axum located at %s.\n",Axumlocation);
 mprintf("Assuming Axum history is at %s.\n",Axumhistory);

 GetFilename("Select first class file in set (*.f*,*.x*).",Classfname,"*.x0",TRUE);
 getcwd(Currentdir,FILENAMELENGTH);

 if(!is_class_file(Classfname))
  {
  mprintf("Bad Filename. Returning.\n");
  return;
  }

 mprintf("Creating Axum History...\n");
 strcpy(Axumhistoryfile,Axumhistory);
 strcat(Axumhistoryfile,"\\TTNANS.HST");
 historyfile=OpenOutFile(Axumhistoryfile);
 if(FileOpenOK(historyfile))
  {
  i=0;
  if(no_error)
   {
   class_n_filename(Classfname,i,Classfname);

   while(FileExists(Classfname))
	{
	mprintf("Adding %s.\n",Classfname);
	sprintf(HistoryLine,"Import FileName = %s\\%s, FileType = ASCII, DataSheet = Class_%d, StartCol = 1, EndCol = END, NameRow = 0, StartRow = 1, EndRow = END, Delimiters = { ,\\t};\n",Currentdir,Classfname,i);
	WriteString(historyfile,HistoryLine);
	i++;
	class_n_filename(Classfname,i,Classfname);
	}
   }
  CloseFile(historyfile);
  }

 strcpy(Axumlocation2,Axumlocation);
 CdAndRemovePathInfo(Axumlocation2);
 mprintf("Calling Axum...\n");
 mprintf("Reminder: Axum numbering starts with 1.\n");
 CallAxum_(Axumlocation,"TTNANS.HST");

 chdir(Currentdir);
 getcwd(Currentdir,FILENAMELENGTH);
 mprintf("Back to current directory (%s).\n",Currentdir);
 }
}

#else

void CallAxum(void)
{
mprintf("This machine can't run Axum.\n");
}

#endif
