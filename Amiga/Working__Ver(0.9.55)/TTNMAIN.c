/*----------------------------------------------- NotePad -----------*/

/* --------------------
   TTNANS:
   TTNMAIN.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   Definitions, main(),
   significant menus.
   --------------------

*/

#include "ttndef.hpp"
#include "ttnbool.hpp"

#include "TTNERROR.HPP"
#include "TTNDATA1.HPP"
#include "TTNDATA2.HPP"
#include "TTNANS.HPP"
#include "TTNRESLT.HPP"
#include "TTNPREPR.HPP"
#include "TTNFILE.HPP"
#include "TTNPRB.HPP"
#include "TTNOTHER.HPP"
#include "TTNBANDX.HPP"
#include "TTNFNAME.HPP"
#include "TTNREPRT.HPP"
#include "TTNMATH.HPP"
#include "TTNDAFI.HPP"

/*------------------------------- Global definitions --------------------*/

char prbfname[FILENAMELENGTH];   /* Current Problem description filename */
BOOL prb_loaded=FALSE;
BOOL ANS_run_success=FALSE;

BOOL LinkLogDebugMode = FALSE;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int  inputdim =0;                 /* dimention (width) of train,test set.*/
int  outputdim=0;                 /* dimention (width) of desired output.*/

int  trainsetsize=0;              /* number of train-set records.        */
int  testsetsize=0;               /* number of test-set records.         */

DATA ** trainset=NULL;            /* train set records.                  */
DATA ** desired =NULL;            /* desired outputs for train set.      */
DATA ** testset =NULL;
DATA ** output  =NULL;            /* actual ANS output.                  */
DATA *  classif =NULL;            /* wta etc output.                     */

/*-----------------------------------------------------------------------*/

void problem_menu(int preselect)
{

char *menu[]={"--------------------------",
              "  P r o b l e m   M e n u ",
              "--------------------------",
			  "Select:              ",
			  "0...No more processing - Go to previous menu.",
              "1...Load Problem Description File.",
			  "2...Preprocess/Scale Sets.",
              "3...Show Available Data Sets.",
	      "4...Start Neural Network."
             };
int msel;

msel=preselect;                          /* -1 means no preset selection */

while((no_error)&&(msel!=0))
 {
 if(preselect<0)
  {
  if(prb_loaded)
   msel=mmenu(menu,9,4,0,4);   /* Show ANS option only if problem loaded */
  else
   msel=mmenu(menu,6,4,0,1);
  }

 switch(msel)
  {
  case 0: FreeAllData();
          prb_loaded=FALSE;
          break;
  case 1: FreeAllData();
		  prb_loaded=FALSE;
		  GetFilename("Please select problem filename.",prbfname,"*.PRB",TRUE);
		  LoadAllData(prbfname);
		  CreateClassif();
		  CreateOutput();
		  if(no_error)prb_loaded=TRUE;
		  break;
  case 2: if(trainset!=NULL)
		   preprocess(-1,"training",trainset,trainsetsize,inputdim);
		  if(desired!=NULL)
		   preprocess(-1,"desired output",desired,trainsetsize,outputdim);
		  if((testset!=NULL)&&(testset!=trainset))
		   preprocess(-1,"testing",testset,testsetsize,inputdim);
		  break;
  case 3: ShowTrainset();
		  ShowDesired();
		  if(testset!=trainset)ShowTestset();
		  break;
  case 4: ans_menu(-1,TRUE,TRUE,TRUE,IW_ANS_STANDARD);
		  if(ANS_run_success)
		   {
		   ShowClassif();
	   ShowOutput();
		   SaveClassif("","ANS Classification Results.\n",TRUE);
		   SaveClasses(prbfname,"ansclass",TRUE);
		   SaveOutput("","ANS Output Layer values.\n",TRUE);
		   }
		  break;
  default:break;
  }
 if(!(preselect<0))msel=0;
 }
}

/*-----------------------------------------------------------------------*/

void misc_menu(void)
{
int msel=-1;
char * menu[]={"-------------------------",
			   "      Misc. Utilities    ",
			   "-------------------------",
			   "Select:            ",
			   "0...Return to previous menu.  ",
			   "1...Data File Utilities       ",
			   "2...Enable log (session) file.",
			   "3...Enable link weight log.",
			   "4...Test Random() number generator."
			   };

while((no_error)&&(msel!=0))
 {
 msel=mmenu(menu,9,4,0,4);
 switch(msel)
  {
  case 0: break;
  case 1: DataFileUtility();
	  break;
  case 2: StartReporting();
	  break;
  case 3: if(TRUE==(LinkLogDebugMode=
			 mrequest_yn("Enable link weight log? (debug - also enables log file)"))
			)
		   StartReporting();
		  break;
  case 4: TestRandom();
		  break;
  default:break;
  }
 }
}

/*-----------------------------------------------------------------------*/

void startup_menu(int preselect)
{
int msel=preselect;

char *menu[]={"---------------------",
              " TTNANS Startup Menu ",
              "---------------------",
              "Select:              ",
              "0...Exit module.",
              "1...Create a Problem Description File (.prb).",
              "2...Go to Problem Processing Menu.",
              "3...Go to Batch & Experimentation Module.",
              "4...Go to non-ANS Algorithm Module.",
              "5...Go to Result Evaluation Module.",
              "6...Misc Utilities.",
             };

while((no_error)&&(msel!=0))
 {
 msel=mmenu(menu,11,4,0,6);
 switch(msel)
  {
  case 0: FreeAllData();
          break;
  case 1: CreatePrbFile();
          break;
  case 2: problem_menu(-1);
          break;
  case 3: batch_experiment_menu();
          break;
  case 4: non_ans_module();
		  break;
  case 5: result_evaluation_menu();
          break;
  case 6: misc_menu();
          break;
  default:break;
  }
 }
}

/*-----------------------------------------------------------------------*/

void MMAIN()
{
mprintf("\n");
mprintf("**************************************************************\n");
mprintf("Welcome to ");
mprintf(VERSION);
mprintf(", an ANS Emulator.\n");
mprintf("**************************************************************\n");

no_error=TRUE;

startup_menu(-1);

StopReporting();

if(file_open_counter!=0)
 mprintf("Warning: Non-zero file-open counter. (=%d) \n",file_open_counter);

mprintf("\n");
mprintf(VERSION);
mprintf(" using ");
mprintf(DATADESCRI);
mprintf(" data items.\n");
mprintf("Memory Allocation method : %s.\n",MEMORY_QUOTE);
#ifdef MEMORYGUARDFLAG
mprintf("MemoryGuard : Enabled.\n");
#else
mprintf("MemoryGuard : Disabled.\n");
#endif
mprintf("Data item (");
mprintf(DATADESCRI);
mprintf(") information: \n");
mprintf("- Data item storage size is %d bytes each.\n",sizeof(DATA));
mprintf("- Trivial test accuracy is (max) %d decimals.\n",
	simpleprecisiontest());
mexit(TRUE);
}
