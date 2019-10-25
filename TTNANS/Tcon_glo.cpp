#include "ttndef.h"

#ifdef _CONSOLE

#include <string.h>
#include "tglobal.h"

extern void FreeAllData(void);

// Class CTglobal
// Global Properties of a TTNANS run */
// Most member variables are intentionaly left public for easy transfer of the TTNANS pure C code

// Constructor

CTglobal::CTglobal(void)
{
  strcpy(prbfname,"no problem loaded");

  prb_loaded=false;
  ANS_run_success=false;
  LinkLogDebugMode = false;

  inputdim =0;					/* dimention (width) of train,test set.*/
  outputdim=0;					/* dimention (width) of desired output.*/	

  trainsetsize=0;				/* number of train-set records.        */
  testsetsize=0;				/* number of test-set records.         */

  trainset=NULL;				/* train set records.                  */
  desired =NULL;				/* desired outputs for train set.      */
  testset =NULL;
  output  =NULL;				/* actual ANS output.                  */
  classif =NULL;				/* winner-takes-all etc output.        */

  no_error = true;
}

// Destructor

CTglobal::~CTglobal(void)
{
  strcpy(prbfname,"no problem loaded");

  prb_loaded=false;
  ANS_run_success=false;
  LinkLogDebugMode = false;

  inputdim =0;					/* dimention (width) of train,test set.*/
  outputdim=0;					/* dimention (width) of desired output.*/	

  trainsetsize=0;				/* number of train-set records.        */
  testsetsize=0;				/* number of test-set records.         */
  
  FreeAllData();

  no_error = true;
}

#endif // def _CONSOLE
