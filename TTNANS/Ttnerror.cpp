#include <stdlib.h>
#include <string.h>

#include "ttndef.h"
#include "ttndef_s.h"
#include "ttndef_o.h"
#include "ttnui.h"
#include "ttnmain.h"
#include "ttnmemor.h"
#include "ttnfile.h"

/*-----------------------------------------------------------------------*/

void mexit(bool normal)
 {
 static int mfreeallcalls=0;

 if(mfreeallcalls<1)          /* this is to exit even if MFreeAll causes */
  {                           /* extra errors.                           */
  mfreeallcalls++;
  MFreeAll();
  }

 file_guard_end();

 mprintf("End of execution, module session exiting with ");
 if(TGBL no_error)	mprintf("no errors ");
 else				mprintf("errors ");
 if(normal)			mprintf("(normal exit).\n");
 else				mprintf("(abnormal exit).\n");
 mforcedisplay();
 
 if(NOT normal) reset_or_exit();
 }

/*-----------------------------------------------------------------------*/

void warning(char * message)
 {
 mprintf("TTNANS Warning: %s \n",message);
 #ifndef _CONSOLE
 if((TGBL p_theWnd)->ModalDialogs())
  { 
  AfxMessageBox(message,MB_APPLMODAL|MB_ICONWARNING); 
  }
 else
  {
  (TGBL p_theWnd)->Disable();
  MessageBox(NULL,message,"Warning",MB_ICONWARNING);
  (TGBL p_theWnd)->Enable();
  } 
 #endif
 }

/*-----------------------------------------------------------------------*/

bool runerror(int i,char * message)
{
int severity;

char m1 [180];
char * m2;

strcpy (m1,"From TTNANS : ");
strcat(m1,message);

switch(i)
 {
 case MEMORYERR :
		  m2 =("Allocate Memory Error");
		  severity=5;
		  break;

 case INPUTFERR :
		  m2 =("Input file Error");
		  severity=5;
		  break;

 case OUTPUFERR :
		  m2 =("Output file Error");
		  severity=5;
		  break;

 case READWRERR :
		  m2 =("File read/write Error");
		  severity=1;
		  break;

 case SYSTEMERR :
		  m2 =("System-related Error");
		  severity=5;
		  break;

 case ANSINTERR :
		  m2 =("ANS-integrity violation Error");
		  severity=4;
		  break;

 case EOFILEERR :
		  m2 =("End-Of-File (EOF) reached Error");
		  severity=1;
		  break;

 case MEMGRDERR :
		  m2 =("MemoryGuard Error");
		  severity=4;
		  break;

 case NULPTRERR :
		  m2 =("Null Pointer Error");
		  severity=4;
		  break;

 case PRBDEFERR :
		  m2 =("Problem definition Error");
		  severity=1;
		  break;

 case DATASTERR :
		  m2 =("Data Set Error");
		  severity=1;
		  break;

 case ARITHMERR :
		  m2 =("Arithmetic Error");
		  severity=6;
		  break;

 case USRABRERR :
		  m2 =("User Abort Error");
		  severity=1;
		  break;

 default: m2 =("Unknown Error");
		  severity=1;
		  break;
 }


#ifndef _CONSOLE
if((TGBL p_theWnd)->ModalDialogs())
 { 
 strcat(m1," ( ");
 strcat(m1,m2);
 strcat(m1," ).");
 AfxMessageBox(m1,MB_APPLMODAL|MB_ICONERROR); 
 }
else
 {
 (TGBL p_theWnd)->Disable();
 MessageBox(NULL,m1,m2,MB_ICONERROR);
 (TGBL p_theWnd)->Enable();
 } 
#endif

mprintf("TTNANS Error: Run-time %s (error id = %d, severity = %d).\n",m2,i,severity);
mprintf("Error Message is : %s.\n",message);

if(severity<5)
 {
 mwait();
 return (TGBL no_error=false);
 }

if(mrequest_yn("TTNANS error with severity > 4. Exit?"))
 {
 mexit(false);
 return (TGBL no_error=false);
 }
else
 return (TGBL no_error=false);
}
