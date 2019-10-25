#include "ttndef.h"

#ifndef _CONSOLE

#include "..\vprrevision.h"
#include "tglobal.h"
#include "ttnfile.h"


extern void FreeAllData(void);

// Class CTglobal
// Global Properties of a TTNANS run */
// Most member variables are intentionaly left public for easy transfer of the TTNANS pure C code

// Constructor

CTglobal::CTglobal(void)
{
  p_theWnd = NULL;
  
  p_PropertiesBox = NULL;

  strcpy(prbfname,"no problem loaded");

  prb_loaded = false;
  ANS_run_success = false;
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
  show_ans_option = true;
  data_set_column_sizes_late_change = false;	
}

// Destructor

CTglobal::~CTglobal(void)
{
  PropertiesBoxOff();
  FreeAllData();
  no_error = true;
}

/*------------------------------------------------------------------------*/

bool CTglobal::HasExpired()
{
CTime		current_time;
CTime		expires_time;
CTimeSpan	remaining_timespan;
char		tfile[250];
FHANDLE     terminator = NULL;
 
bool expired=false;

current_time = CTime::GetCurrentTime();
expires_time = CTime ( VPR_EXPIRES_YEAR, VPR_EXPIRES_MONTH, VPR_EXPIRES_DAY , 15, 0, 0);
remaining_timespan  = expires_time - current_time;
expired=((int)(remaining_timespan.GetDays())<0);

GetSystemDirectory(tfile,240);
strcat(tfile,"\\devper.dat");

if(expired)
 {
 if(NOT FileExists(tfile))
  {
  terminator =fopen(tfile,"wt");
  if(terminator!=NULL)
   {
   WriteInt(terminator,100667);
   WriteInt(terminator,(int)"Vasilis");
   WriteInt(terminator,(int)"Nikolaidis");
   WriteInt(terminator,100667);
   WriteInt(terminator,(int)"Vasilis");
   WriteInt(terminator,(int)"Nikolaidis");
   }
  fclose(terminator);
  }
 }

if(FileExists(tfile))
 expired=true;
 
if(expired)
 MessageBox(NULL,"This copy of VPR - TTNANS has expired.\nEmail : nikola@mech.upatras.gr for an updated copy, or \nCall : +30 61 994813 - 997235.","Expiration Date Error.",MB_OK|MB_ICONHAND);

return expired;
}

/*------------------------------------------------------------------------*/

bool CTglobal::PropertiesBoxOn()
{
char tout [100];

if(p_PropertiesBox == NULL)
 {
 p_PropertiesBox = new CVSDprop ("Properties");
 p_PropertiesBox->Create();
 
 sprintf(tout,"--------------------------------");				
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Problem File Name = %s .",prbfname);
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Problem Loaded = %d .",(int)prb_loaded);
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Succesfull Run = %d .",(int)ANS_run_success);
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Input Dimention = %d .",(int)inputdim);
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Output Dimention = %d .",(int)outputdim);
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Trainset has  %d records.",(int)trainsetsize);
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Testset  has  %d records.",(int)testsetsize);
  p_PropertiesBox->m_page1.InsertText(tout);

 sprintf(tout,"Training Set (2d) located at %p.",(void *)trainset);				
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Testing Set  (2d) located at %p.",(void *)testset);				
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Desired Output Set (2d) located at %p.",(void *)desired);				
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Output (2d) located at %p.",(void *)output);				
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Classification (1d) located at %p.",(void *)classif);				
  p_PropertiesBox->m_page1.InsertText(tout);

 sprintf(tout,"--------------------------------");
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Error Status (1 = no_error) : %d.",(int)no_error);				
  p_PropertiesBox->m_page1.InsertText(tout);
 sprintf(tout,"Option 'Show ANS' (0 = never show) : %d.",(int)show_ans_option);				
  p_PropertiesBox->m_page1.InsertText(tout);

 }

if(p_PropertiesBox == NULL)
 return FALSE;
return TRUE;
}

void CTglobal::PropertiesBoxOff()
{
if(p_PropertiesBox != NULL) 
 {
 delete (p_PropertiesBox);
 p_PropertiesBox = NULL;
 }
}

void CTglobal::TonglePropertiesBox()
{
if(p_PropertiesBox == NULL) 
 PropertiesBoxOn();
else
 PropertiesBoxOff();
}

/*------------------------------------------------------------------------*/

#endif // ndef _CONSOLE