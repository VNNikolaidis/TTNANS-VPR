/*
  ---------------------
  TTNANS:
  TTNREPRT.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Report (Session)
  Generation.
  ---------------------

*/

#include "ttndef.h"
#include "ttnpros.h"

#include <time.h>

#include "ttnfname.h"
#include "ttnfile.h"

#include "ttnui.h"

FHANDLE sessionfile;
char sessionfilename[FILENAMELENGTH];
bool sessionenabled=false;						// record session to file?
bool reporttimeenabled=true;

/*-----------------------------------------------------------------------*/

void StartReporting(void)
{
time_t t;

if(sessionenabled)
 {
 mbeep();
 mprintf("Report Already Enabled (Report File = %s).\n",sessionfilename);
 mbeep();
 mwait();
 }
else
 {
 if(mrequest_yn("Record session to file?"))
  {
  GetFilename("Select new session file.",sessionfilename,"*.txt",true);
  sessionfile=OpenOutFile(sessionfilename);
  if(FileOpenOK(sessionfile))
   {
   reporttimeenabled = mrequest_yn("Enable time stamps in session file?");

   sessionenabled=true;
   mprintf(" \n");
   mprintf("----> Session File generation (program ");
   mprintf(VERSION);
   mprintf(").\n");
   time(&t);
   mprintf("----> Report session log date : %s \n",ctime(&t));
   }
  else
   {
   mprintf(" \n");
   mprintf("----> Report file could not be created. \n");
   sessionenabled=false;
   }
  }
 }
}

/*-----------------------------------------------------------------------*/

void StopReporting(void)
{
time_t t;

if(sessionenabled)
 {
 time(&t);
 mprintf(" \n");
 mprintf("----> End of session log on : %s \n",ctime(&t));
 mprintf(" \n");
 CloseFile(sessionfile);
 sessionenabled=false;
 }
}

/*-----------------------------------------------------------------------*/

void ReportToSessionFile(const char * x)
{
if(sessionenabled)
 {
 WriteString(sessionfile,x);
 }
}

/*-----------------------------------------------------------------------*/

void ReportTime(void)
{
time_t t;

if(sessionenabled AND reporttimeenabled)
 {
 time(&t);
 WriteString(sessionfile,"\n");
 WriteString(sessionfile,"\n =O=      Time Stamped at ");
 WriteString(sessionfile,ctime(&t));
 WriteString(sessionfile,"\n");
 }
}

/*-----------------------------------------------------------------------*/
