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

#include "ttndef.h"

#ifndef _CONSOLE
  #include "..\vprrevision.h"
#else
  #define VPR_REVISION "(Console Version)"
#endif

// TTNANS starts here

#include "tglobal.h"
#include "ttnui.h"

#include "ttnerror.h"
#include "ttndata1.h"
#include "ttndata2.h"
#include "ttnans.h"
#include "ttnreslt.h"
#include "ttnprepr.h"
#include "ttnfile.h"
#include "ttnprb.h"
#include "ttnother.h"
#include "ttnbandx.h"
#include "ttnfname.h"
#include "ttnreprt.h"
#include "ttnmath.h"
#include "ttndafi.h"
#include "ttngt.h"
#include "ttncustm.h"
#include "ttnimage.h"

/*------------------------------- Global definitions --------------------*/

#define TGBL ptg->
CTglobal * ptg = NULL;

/*-----------------------------------------------------------------------*/

void ANS_processing_menu(int preselect)
{
char mtitle[]="  A N S   P r o c e s s i n g   M e n u ";
char *menu[]={"0...No more processing - Go to previous menu.",
              "1...Load Problem Description File.",
              "2...Preprocess/Scale Sets.",
              "3...Show Available Data Sets.",
			  "4...Start Neural Network."
             };
int msel;

msel=preselect;                          /* -1 means no preset selection */

while((TGBL no_error)&&(msel!=0))
 {
 if(preselect<0)
  {
  if(TGBL prb_loaded)
   msel=mmenu(mtitle,menu,5,4);     /* Show ANS option only if problem loaded */
  else
   msel=mmenu(mtitle,menu,2,1);
  }

 switch(msel)
  {
  case 0: FreeAllData();
          TGBL prb_loaded=false;
          break;
  case 1: FreeAllData();
          TGBL prb_loaded=false;
          GetFilename("Please select problem filename.",TGBL prbfname,"*.PRB",true);
          LoadAllData(TGBL prbfname);
          CreateClassif();
		  CreateOutput();
		  if(TGBL no_error) TGBL prb_loaded=true;
          break;
  case 2: preprocess_all_data_sets();
          break;
  case 3: ShowTrainset();
          ShowDesired();
          if(TGBL testset!=TGBL trainset)ShowTestset();
          break;
  case 4: ans_menu(-1,true,true,true,IW_ANS_STANDARD);
          if(TGBL ANS_run_success)
		   {
           ShowClassif();
		   ShowOutput();
		   SaveClassif("","TTNANS Classification Results",true);
		   SavePreprocessedClasses ("testclass", true);
		   SaveClasses(TGBL prbfname,"ansclass",true);
		   SaveOutput("","ANS Output Layer values.\n",true);
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
char mtitle[]="      Misc. Utilities    ";
char * menu[]={"0...Go Back.  ",
               "1...Data File Utilities       ",
               "2...Enable log (session) file.",
               "3...Enable link weight log.",
               "4...Test Random() number generator.",
               "5...Raw Image Import/Export Utility."
               };

while((TGBL no_error)&&(msel!=0))
 {
 msel=mmenu(mtitle,menu,6,5);
 switch(msel)
  {
  case 0: break;
  case 1: DataFileUtility();
      break;
  case 2: StartReporting();
	  break;
  case 3: if(true==(TGBL LinkLogDebugMode =
             mrequest_yn("Enable link weight log and run?\n(debug - also enables log file)")))
           StartReporting();
          break;
  case 4: TestRandom();
          break;
  case 5: Image_Utility();
		  break;

  default:break;
  }
 }
}

/*-----------------------------------------------------------------------*/

void startup_menu(int preselect)
{
int msel=preselect;

char mtitle[]=" TTNANS Startup Menu ";
char *menu[]={"0...Go Back - Exit.",
              "1...Create a Problem Description File (.prb).",
              "2...Go to ANS Processing Module.",
              "3...Go to ANS Batch & Experimentation Module.",
              "4...Go to Conventional Algorithm Module.",
              "5...Go to Graph Theoretical Method Module.",
              "6...Go to Custom Algorithm Module.",
			  "7...Go to Result Evaluation Module.",
              "8...Misc Utilities.",
             };

while((TGBL no_error)&&(msel!=0))
 {
 if(preselect<0)msel=mmenu(mtitle,menu,9,8);
 switch(msel)
  {
  case 0: FreeAllData();
          break;
  case 1: CreatePrbFile();
          break;
  case 2: ANS_processing_menu(-1);
          break;
  case 3: batch_experiment_menu();
          break;
  case 4: non_ans_module();
          break;
  case 5: graph_theoretic_menu(-1);;
          break;
  case 6: custom_menu(-1);;
          break;
  case 7: result_evaluation_menu();
          break;
  case 8: misc_menu();
          break;
  default:break;
  }
 if(!(preselect<0))msel=0;
 }
}

/*-----------------------------------------------------------------------*/

void mmain(int preselect = -1,bool start_reporting = false)
 {
  mcls();
  mprintf("\n\n\n");
  file_guard_init();

#ifndef _CONSOLE

  mprintf("                                          ");
  mprintf("***     Welcome to ");
  mprintf(VERSION);
  mprintf("      ***\n\n");
  mprintf("                         ");
  mprintf("(Running under VPR Rev: ");
  mprintf(VPR_REVISION);
  mprintf(" Pattern Recognition - ANS Emulation Program.)\n\n\n\n");

#else

  mprintf("***     Welcome to ");
  mprintf(VERSION);
  mprintf("      ***\n\n");

#endif

  TGBL no_error=true;

  if(start_reporting) StartReporting();

  startup_menu(preselect);

  StopReporting();

  if(get_file_open_counter()!=0)
   mprintf("Warning: Non-zero file-open counter. (=%d) \n",get_file_open_counter());

  mprintf(" \n");
  mprintf(VERSION);
  mprintf(" (c) ");
  mprintauthor();
  mprintf(".\n");
  mprintf("(Last compiled on %s, %s.)\n", __DATE__, __TIME__);
  mprintf("This version uses ");
  mprintf(DATADESCRI);
  mprintf(" data items.\n");
  mprintf("Compilation Setup:\n");
  mprintf("- Memory Allocation method : %s.\n",MEMORY_QUOTE);
  #ifdef _DEBUG
   mprintf("- Configuration : Debug.\n");
  #else
   mprintf("- Configuration : Release.\n");
  #endif
  mprintf("- Intel MMX : ");
  #ifdef _MMX_
   mprintf("MMX instructions enabled.\n");
  #else
   mprintf("no MMX instructions.\n");
  #endif
  mprintf("- MemoryGuard : ");
  #ifdef MEMORYGUARDFLAG
   mprintf("Enabled.\n");
  #else
   mprintf("Disabled.\n");
  #endif
  mprintf("- Data item is ");
  mprintf(DATADESCRI);
  mprintf(" (see below).\n");
  mprintf("- Data item storage size is %d bytes each.\n",sizeof(DATA));
  mprintf("- Trivial test accuracy is (max) %d decimals.\n",simpleprecisiontest());
  mexit(true);
 }

/*-----------------------------------------------------------------------*/

#ifdef _CONSOLE

void main (void)
{
CTglobal tg; 
ptg = &tg;
mmain(-1);
}

#else // VPR CODE

#include "..\stdafx.h"

class CTthread : public CWinThread
 {
 protected:
 bool is_running;

 public:

 static int numthreads;
 CTglobal tg; 
 
 CTthread();
 ~CTthread();
 void go(CVPRView * p_ViewWnd,int preselect = -1, bool start_rec = false);
 void stop();
 };

int CTthread::numthreads = 0;

CTthread::CTthread()
 {
 is_running = false;
 }

CTthread::~CTthread()
 {
 stop();
 }

void CTthread::go(CVPRView * p_ViewWnd, int preselect, bool start_rec)
 {
 numthreads ++;

 ptg = &tg;

 if(p_ViewWnd != NULL)
  {
  tg.p_theWnd=p_ViewWnd;
  tg.p_theWnd->ClearText(false);

  if(NOT tg.HasExpired())
   {
   is_running = true;
   mmain(preselect,start_rec);
   is_running = false;
   }
  }
 numthreads --;
 }

void CTthread::stop()
 {
 if(is_running)
  {
  if(numthreads>0)numthreads --;
  is_running=false;
  }
 }

#ifdef _USE_WIN32_VPR_THREAD_CODE_

CTthread * p_global_main_thread = NULL;

void ttnans_main (CVPRView * p_ViewWnd, int preselect = -1, bool start_rec = false)
{
if(CTthread::numthreads==0)
  {
  p_global_main_thread = (CTthread *)AfxBeginThread(RUNTIME_CLASS( CTthread ));
  p_global_main_thread->SetThreadPriority(THREAD_PRIORITY_HIGHEST); 
  p_global_main_thread->go(p_ViewWnd, preselect, start_rec);

  /*
  p_global_main_thread = new CTthread();
  p_global_main_thread->CreateThread();
//p_global_main_thread->SetThreadPriority(THREAD_PRIORITY_HIGHEST); 
  p_global_main_thread->go(p_ViewWnd, preselect, start_rec);
  */

  }
else
  {
  MessageBox(NULL,"TTNANS multithread support is very limited.\nAnother TTNANS thread is currently running\nunder this VPR shell.","Unsafe condition: Is_Running.",MB_OK);
  }
}

#endif

#ifndef _USE_WIN32_VPR_THREAD_CODE_

void ttnans_main (CVPRView * p_ViewWnd, int preselect = -1, bool start_rec = false)
{
if(CTthread::numthreads==0)
 {
 CTthread dummy_thread;
 dummy_thread.go(p_ViewWnd, preselect, start_rec);
 }
else
 {
 MessageBox(NULL,"TTNANS multithread support is not enabled.\nAnother TTNANS thread is currently running under this VPR shell.","Unsafe condition: Is_Running.",MB_OK);
 }
}

#endif



#endif // _CONSOLE

/*-----------------------------------------------------------------------*/

#ifdef _CONSOLE

void reset_or_exit()
 {
 exit(1);
 }

#else // VPR CODE

#ifdef _USE_WIN32_VPR_THREAD_CODE_
 
void reset_or_exit()
 {
 if(p_global_main_thread==NULL) return;
 delete p_global_main_thread;
 p_global_main_thread = NULL;
 }

#endif

#ifndef _USE_WIN32_VPR_THREAD_CODE_

void reset_or_exit()
 {
 if(mrequest_yn("Are you sure you want to exit?"))
   {
   AfxEndThread(1);										// kills entire application
   }
 }

#endif

#endif

/*-----------------------------------------------------------------------*/
