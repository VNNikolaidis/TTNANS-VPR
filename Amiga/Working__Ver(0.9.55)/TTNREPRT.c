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

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include <time.h>

#include "TTNFNAME.HPP"
#include "TTNFILE.HPP"

BOOL sessionenabled=FALSE;
FHANDLE sessionfile;
char sessionfilename[FILENAMELENGTH];

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
 if(mrequest_yn("Enable session file reporting?"))
  {
  GetFilename("Select new session file.",sessionfilename,"*.rep",TRUE);
  sessionfile=OpenOutFile(sessionfilename);
  if(FileOpenOK(sessionfile))
   {
   sessionenabled=TRUE;
   mprintf("\n");
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
   sessionenabled=FALSE;
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
 mprintf("\n");
 mprintf("----> End of session log on : %s \n",ctime(&t));
 mprintf("\n");
 CloseFile(sessionfile);
 sessionenabled=FALSE;
 }
}

/*-----------------------------------------------------------------------*/

void ReportToSessionFile(char * x)
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

if(sessionenabled)
 {
 time(&t);
 WriteString(sessionfile,"\n");
 WriteString(sessionfile,"\n =O=      Time Stamped at ");
 WriteString(sessionfile,ctime(&t));
 WriteString(sessionfile,"\n");
 }
}

/*-----------------------------------------------------------------------*/
