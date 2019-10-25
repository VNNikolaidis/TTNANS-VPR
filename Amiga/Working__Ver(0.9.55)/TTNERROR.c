#include "ttndef.hpp"
#include "ttnbool.hpp"

#include "TTNMEMOR.HPP"

/*-----------------------------------------------------------------------*/

BOOL no_error;

/*-----------------------------------------------------------------------*/

void mexit(BOOL normal)
 {
 static int mfreeallcalls=0;

 if(mfreeallcalls<1)          /* this is to exit even if MFreeAll causes */
  {                           /* extra errors.                           */
  mfreeallcalls++;
  MFreeAll();
  }

 mprintf("End of execution, module exiting with ");
 if(no_error) mprintf("no errors.\n");
 else         mprintf("errors.\n");
 mforcedisplay();

 if(normal)
  {
  #ifndef _MSWINDOWS_
  exit(EXIT_SUCCESS);
  #endif
  }
else
  {
  #ifndef _MSWINDOWS_
  exit(EXIT_FAILURE);
  #else
  abort();
  #endif
  }
}

/*-----------------------------------------------------------------------*/

BOOL runerror(int i,char * message)
{
int severity;

mcls();
mbeep();

mprintf("\n");
mprintf("> From TTNANS : %s \n",message);
mprintf("> ");

switch(i)
 {
 case MEMORYERR :
          mprintf("Allocate Memory");
          severity=5;
          break;

 case INPUTFERR :
          mprintf("Input file");
          severity=1;
          break;

 case OUTPUFERR :
          mprintf("Output file");
          severity=5;
          break;

 case READWRERR :
          mprintf("File read/write");
          severity=1;
          break;

 case SYSTEMERR :
          mprintf("System-related");
          severity=5;
          break;

 case ANSINTERR :
          mprintf("ANS-integrity violation");
          severity=4;
          break;

 case EOFILEERR :
          mprintf("End-Of-File (EOF) reached");
          severity=1;
          break;

 case MEMGRDERR :
          mprintf("MemoryGuard");
          severity=4;
          break;

 case NULPTRERR :
          mprintf("Null Pointer");
          severity=4;
          break;

 case PRBDEFERR :
          mprintf("Problem definition");
          severity=1;
          break;

 case DATASTERR :
          mprintf("Data Set");
          severity=1;
          break;

 case ARITHMERR :
          mprintf("Arithmetic");
          severity=6;
          break;

 default: mprintf("Unknown");
          severity=1;
          break;
 }
mprintf(" run-time error (error id = %d, severity = %d).\n",i,severity);
mprintf("\n");

if(severity<5)
 {
 mwait();
 return (no_error=FALSE);
 }

if(mrequest_yn("TTNANS error with severity > 4. Proceed?"))
 return (no_error=FALSE);
else
 mexit(FALSE);
 return (no_error=FALSE);
}
