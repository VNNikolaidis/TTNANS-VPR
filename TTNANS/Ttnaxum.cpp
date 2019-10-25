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

#include "ttndef.h"
#include "ttndef_o.h"
#include "ttnui.h"

#ifdef _AXUM_COMPATIBLE_

//#include <dir.h>

#include "ttnfile.h"
#include "ttnfname.h"
#include "ttnclafi.h"
#include "ttnerror.h"
#include "ttnmain.h"

#include <string.h>
#include <math.h>

#include <windows.h>	// winexec
#include <direct.h>		// _getcwd _chdir

char Axumlocation[FILENAMELENGTH];

void CallAxum_(char * axum,char * param)
{
char callthis[2*FILENAMELENGTH];
char axumdir[2*FILENAMELENGTH];
unsigned int i = 0;
int j = 0;

strcpy(axumdir,axum);

for(i=0;i<strlen(axumdir);i++) {  if(axumdir[i]=='\\') j = i; }
axumdir[j]='\0';

_chdir(axumdir);

strcpy(callthis,axum);
strcat(callthis," ");
strcat(callthis,param);
WinExec(callthis,SW_SHOW);
}

/*
. typical axum history lines:
.
. Import FileName = C:\AXUM\DATA\T02M2_X0., FileType = ASCII, DataSheet = T02M2_X0, StartCol = 1, EndCol = END, NameRow = 0, StartRow = 1, EndRow = END, Delimiters = { ,\t};
.
. CreateGraph Graph = MYGRAPH1, AxesType = "XY", Units = "AxesUnits";
.
.
. SetPlotItemSpecs  Graph = MYGRAPH1
.                  PlotNumber = 1,
.                  PlotType = "Scatter",
.                  Projection = No,
.                  DataSheet = "Class_0"
.                  xColumn = {1}
.                  yColumn = {2};
.
. ViewGraph;
*/

#define LAST_CHANCE "axum.exe"

void CallAxum(void)
{
bool ok=TRUE;
int r1,r2;
int i,j,cols;
FHANDLE historyfile;
bool view_graphs;

bool axumlocated=FALSE;
char Axumlocation2[FILENAMELENGTH];
char Axumscript[FILENAMELENGTH];
char Axumscriptfile[FILENAMELENGTH];
char Classfname[FILENAMELENGTH];
char ClassfnameBuffer[FILENAMELENGTH];
char Currentdir[FILENAMELENGTH];
char HistoryLine[400];
static int axum_version = -1;
static bool first_time_in = true;

char * Axumlocs_C[]={"C:\\axumw\\axum.exe",
                     "C:\\axum\\axum.exe",
					 "C:\\bin\\axum\\axum.exe",
					 "C:\\bin\\dos\\axum\\axum.exe",
					 "C:\\main\\bin\\dos\\axum\\axum.exe",
					 "C:\\main\\bin\\win\\math\\axumw\\axum.exe",
					 "C:\\progra~1\\axumw\\axum.exe",
		    	      LAST_CHANCE,
					};

char * Axumlocs_D[]={"D:\\axumw\\axum.exe",
                     "D:\\axum\\axum.exe",
					 "D:\\bin\\axum\\axum.exe",
					 "D:\\main\\bin\\dos\\axum\\axum.exe",
					 "D:\\bin\\dos\\axum\\axum.exe",
           			 LAST_CHANCE,
					};

i=0;

_getcwd(Currentdir,FILENAMELENGTH);

if(first_time_in == true)
 {
 strcpy(Axumlocation,"C:\\AXUM.EXE");
 first_time_in = false;
 }

if(!FileExists(Axumlocation))
 {
 while (NOT (strcmp(Axumlocs_C[i],LAST_CHANCE)==0) AND
		NOT FileExists(Axumlocs_C[i]))
		 {
		 mprintf("Failed locating Axum at %s.\n",Axumlocs_C[i]);
		 i++;
		 }

 strcpy(Axumlocation,Axumlocs_C[i]);
 i=0;

 if(!FileExists(Axumlocation))
 if(mrequest_yn("Is Axum located in drive D:?\n(Select No if D: is a CD-ROM Drive)"))
  { 
  while (NOT (strcmp(Axumlocs_D[i],LAST_CHANCE)==0) AND
		 NOT FileExists(Axumlocs_D[i]))
		  {
		  mprintf("Failed locating Axum at %s.\n",Axumlocs_D[i]);
		  i++;
		  }
  strcpy(Axumlocation,Axumlocs_D[i]);
  }
 }

while((!FileExists(Axumlocation))&&(ok))
 {
 axumlocated=FALSE;
 mprintf("Failed locating Axum at %s.\n",Axumlocation);
 ok=mrequest_yn("Retry locating Axum?");
 if(ok)
  GetFilename("Please locate axum.exe.",Axumlocation,"*.exe",false);
 }

if(ok)
 {
 axumlocated=TRUE;
 strcpy(Axumscript,Axumlocation);
 i=0;
 j=0;
 while(Axumscript[i]!='\0')
  {
  if(Axumscript[i]=='\\')
   j=i;
  i++;
  }
 Axumscript[j]='\0';
 strcat(Axumscript,"\\HISTORY");

 mprintf("Axum located at %s.\n",Axumlocation);
 mprintf("Assuming Axum history is at %s.\n\n",Axumscript);

 _chdir(Currentdir);
 GetFilename("Select first class file in set (*.f0,*.x0,*.s0).",Classfname,"*.*0",true);
 _getcwd(Currentdir,FILENAMELENGTH);

 if(!is_class_file(Classfname))
  {
  mprintf("Bad Filename. Returning.\n");
  return;
  }

// Get number of columns in class file

 mprintf("Determining number of columns (descriptors) in class file...\n");
  
 strcpy(ClassfnameBuffer,Classfname);
 i=0;

// find first non_empty class file

 while(FileExists(ClassfnameBuffer) AND IsEmptyFile(ClassfnameBuffer))
  {
  class_n_filename(ClassfnameBuffer,i,ClassfnameBuffer);
  i++;
  }

// i is used as a placeholder here

  GetDataFileDims(ClassfnameBuffer,&i,&cols);
  i=0;

 mprintf("Number of columns (in %s) = %d.\n\n",ClassfnameBuffer,cols);
 
// Done!

 mprintf("Creating Axum history (script) file named TTNANS.HST...\n");
 strcpy(Axumscriptfile,Axumscript);
 strcat(Axumscriptfile,"\\TTNANS.HST");
 historyfile=OpenOutFile(Axumscriptfile);
 if(FileOpenOK(historyfile))
  {
  if(TGBL no_error)
   {

// AXUM HISTORY (SCRIPT) FILE IS CREATED HERE.

// First import the datafiles (named Class_# in Axum)

   i=0;

   class_n_filename(Classfname,i,Classfname);

   while(FileExists(Classfname))
	{
    if(IsEmptyFile(Classfname))
     {
     mprintf("\n\n");
     mprintf("* Warning: Cannot make Axum import file %s.\n",Classfname);
     mprintf("* File %s contains no records.\n",Classfname);
	 mprintf("* You may encounter problems adding graphs since Axum Class_%d will not exist.\n\n",i);
     }
	else
     {
	 mprintf("Adding %s.\n",Classfname);
	 sprintf(HistoryLine,"Import FileName = %s\\%s, FileType = ASCII, DataSheet = Class_%d, StartCol = 1, EndCol = END, NameRow = 0, StartRow = 1, EndRow = END, Delimiters = { ,\\t};\n",Currentdir,Classfname,i);
	 WriteString(historyfile,HistoryLine);
     }
	i++;
	class_n_filename(Classfname,i,Classfname);
    }

// Done!

// Now you now you have i (0 to i-1) data sheets (some may be empty!)   
   
   j=0;
   for(r1=0;r1<cols;r1++) for(r2=r1+1;r2<cols;r2++) j++;
   sprintf(HistoryLine,"Add graphs to AXUM Script (%d graphs) ?",j);
   r1=r2=j=0;

   if(mrequest_yn(HistoryLine))
    {
    view_graphs=mrequest_yn("View graphs automatically after invoking Axum?");
     
    if(axum_version==-1)
     if(mrequest_yn("Are you using Axum for DOS (version 3 or less)?"))
      axum_version=3;
     else
      axum_version=4;
    
    for(r1=0;r1<cols;r1++)
	for(r2=r1+1;r2<cols;r2++)
     {
     mprintf("Adding 2-D Scatter Plot for columns %d, %d (as GR_%d_%d in Axum).\n",r1,r2,r1+1,r2+1);
      
	 sprintf(HistoryLine,"CreateGraph Graph = GR_%d_%d, AxesType = \"XY\";\n",r1+1,r2+1);
     WriteString(historyfile,HistoryLine);

     j=0;
     while(j<i)
      {

      switch(axum_version)
       {
       case 3:
        
        sprintf(HistoryLine,"SetPlotItemSpecs  PlotNumber = %d, PlotType = \"Scatter\", Projection = No, DataSheet = \"Class_%d\", xColumn = {%d}, yColumn = {%d};\n",
		j+1,j,r1+1,r2+1);
        WriteString(historyfile,HistoryLine);
        break;

	   case 4:

        sprintf(HistoryLine,"Create LinePlot Name = \\\\GR_%d_%d\\GR_%d_%d\\%d PlotNumber = %d DataSheet = CLASS_%d LineStyle = \"None\";\n",
		r1+1,r2+1,r1+1,r2+1,j+1,j+1,j);
        WriteString(historyfile,HistoryLine);
 
        sprintf(HistoryLine,"Modify LinePlot Name = \\\\GR_%d_%d\\GR_%d_%d\\%d xColumn = {%d} yColumn = {%d} Crop = No;\n",
        r1+1,r2+1,r1+1,r2+1,j+1,r1+1,r2+1);
        WriteString(historyfile,HistoryLine);
        break;
        
       default:
		break;
       }

      j++;
	  }

	 sprintf(HistoryLine,"SetXTitleSpecs Title = \"Column %d (file %d)\" ;",r1+1,r1);
     WriteString(historyfile,HistoryLine);

     sprintf(HistoryLine,"SetYTitleSpecs Title = \"Column %d (file %d)\" ;",r2+1,r2);
     WriteString(historyfile,HistoryLine);
     
     sprintf(HistoryLine,"SetTitleSpecs Title = \"VPR(ttnANS) %d-%d (file %d-%d)\";",r1+1,r2+1,r1,r2);
     WriteString(historyfile,HistoryLine);
	  
     if(view_graphs) WriteString(historyfile,"ViewGraph;\n");
	 }
    }
 
// END AXUM HISTORY (SCRIPT).
   }
  CloseFile(historyfile);

  strcpy(Axumlocation2,Axumlocation);
  mprintf("Calling Axum...\n");

  mhintclear();
  mhintf(true,"Reminder: Axum numbering starts with 1.\n");

  CallAxum_(Axumlocation,"TTNANS.HST");
  }

 _chdir(Currentdir);
 _getcwd(Currentdir,FILENAMELENGTH);
 mprintf("Back to current directory (%s).\n",Currentdir);
 }
}

#else

void CallAxum(void)
{
mprintf("* Sorry, this program has been compiled for an Axum incompatible environment.\n");
}

#endif

/*
example version 4.1 history:


Create LinePlot
	Name = \\GR_6_7\GR_6_7\1
	PlotNumber = 1
	DataSheet = CLASS_1
	RelativeAxisX = 1
	RelativeAxisY = 1
	RelativePlane = 1
	Hide = No
	Crop = Yes
	LineColor = "Red"
	LineWeight = "1"
	BreakForMissings = No
	BreakAtSymbols = Yes
	SymbolStyle = "Circle, Solid"
	SymbolColor = "Blue"
	SymbolHeight = 0.15
	SymbolLineWeight = "1/2"
	SymbolFreq = 1
	Rows = {ALL}
	SmoothingType = "None"
	NumOutputPoints = 100
	InitialSlope = "Auto"
	FinalSlope = "Auto"
	NumIterations = 0
	PcntPointsToUse = 50;

Modify LinePlot
	Name = \\GR_6_7\GR_6_7\1
	xColumn = {1}
	yColumn = {2}
	Crop = No;

*/