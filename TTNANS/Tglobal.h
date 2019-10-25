#ifndef TGLOBAL_H
#define TGLOBAL_H

#include "ttndef.h"

#ifndef _CONSOLE			// VPR compilation
  #include "..\stdafx.h"
  #include "..\vpr.h"
  #include "..\vprDoc.h"
  #include "..\vprView.h"
  #include "..\vsdprop.h"
#endif

#include "ttndef_o.h"

// the following is also defined in ttnmain.h
#define TGBL ptg->
#define TGBL_INVALID_SIZE  9999999999

// Class CTglobal
// Global Properties of a TTNANS run */
// Most member variables are intentionaly left public for easy transfer of the TTNANS pure C code
// (goal = aggregate (συναθροιστική) type class)

class CTglobal
{
public:

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

char prbfname[FILENAMELENGTH];
bool prb_loaded;
bool ANS_run_success;
bool LinkLogDebugMode;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

// These could have been defined "unsigned":

int inputdim;					/* dimention (width) of train,test set.	*/
int outputdim;					/* dimention (width) of desired output.	*/

int trainsetsize;				/* number of train-set records.			*/
int testsetsize;				/* number of test-set records.			*/

// The all-too-important, globaly accessible data sets:
	
DATA ** trainset;				/* train set records.					*/
DATA ** desired;				/* desired outputs for train set.		*/
DATA ** testset;				/* test set records.					*/
DATA ** output;					/* actual ANS output.					*/
DATA *  classif;				/* winner-takes-all etc output.			*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool no_error;					/* has an error occured?				*/

bool show_ans_option;			/* false => never stop to show ANS.		*/ 


bool data_set_column_sizes_late_change;

								/* after some preprocessing (like PCA)  */
								/* the user may want to change column   */
								/* sizes. If flag == true,preprocessing */
								/* calls for column size reduction.		*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

// message handler functions

CTglobal(void);
~CTglobal(void);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#ifndef _CONSOLE			// VPR compilation

CVPRView * p_theWnd;

CVSDprop * p_PropertiesBox;

bool PropertiesBoxOn();
void PropertiesBoxOff();
void TonglePropertiesBox();

bool HasExpired();

#endif

};

#endif // TGLOBAL_H
