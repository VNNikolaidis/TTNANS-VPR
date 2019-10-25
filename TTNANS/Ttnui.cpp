/*
  ---------------------
  TTNANS:
  TTNUI.C      ver.0.02
  ---------------------
  Vasilis.N.Nikolaidis
  ----------------------------------
  User Interface.
  Modified for VPR Version of TTNANS
  ----------------------------------

*/

#define TTNUI                                   /* don't include TTNUI.H */

#include "ttndef.h"

#ifndef _CONSOLE								/* VPR compilation		 */
//#include "VPRiface.h"
#include "..\stdafx.h"
#include "..\vpr.h"
#include "..\vsdrqstr.h"
#include "..\vsdmenu.h"
#include "..\vsdprogress.h"

#include "ttndef.h"
#include "ttnpros.h"

#include "ttnreprt.h"
#include "ttnmemor.h"


/*-----------------------------------------------------------------------*/

#include "ttnpros.h"
#include <stdarg.h>
#define BELL 7

/*-----------------------------------------------------------------------*/

//#define _LEADING_SPACE_
#define _MPRINTF_LIMIT_  400


int mprintf(const char * __format,...)
{
char buf1[_MPRINTF_LIMIT_];
char buf2[_MPRINTF_LIMIT_];

va_list ap;

va_start(ap,__format);
vsprintf(buf1,__format, ap);
va_end(ap);
 
// Convert newline to return-newline for ms-windows and output it.
 {
 int i1=0;
 int i2=0;
 int l=strlen(buf1);

 #ifdef _LEADING_SPACE_
 buf2[i2++]='_';
 #endif _LEADING_SPACE_
 
 while((i1<l)AND(i2<_MPRINTF_LIMIT_-5))
  {
  if(buf1[i1]=='\n') { buf2[i2++]='\r'; buf2[i2]  ='\n'; }
  else buf2[i2]=buf1[i1];
  i1++;
  i2++;
  } 
 buf2[i2]='\0';
 (TGBL p_theWnd)->InsertText(buf2);
 }


ReportToSessionFile(buf1);
return 1;
}

/*-----------------------------------------------------------------------*/

int mprint_(const char * text)
{
(TGBL p_theWnd)->InsertText(text);
ReportToSessionFile(text);
return 1;
}

/*-----------------------------------------------------------------------*/
/* mhintf calls should be for one-liners only...						 */

int mhintf(bool addtosessionfile, const char * __format,...)
{
char buf1[255];
char buf2[255];

va_list ap;

va_start(ap,__format);
vsprintf(buf1,__format, ap);
va_end(ap);
 
// Remove newlines

 {
 int i1=0;
 int i2=0;
 int l=strlen(buf1);
 
 while((i1<l)AND(i2<254))
  {
  if(buf1[i1]=='\n') buf2[i2]=' ';
  else buf2[i2]=buf1[i1];
  i1++;
  i2++;
  } 
 buf2[i2]='\0';
 TGBL p_theWnd->InsertHintText(buf2);
 }

if(addtosessionfile)
{
ReportToSessionFile(buf1);
}
return 1;
}

/*-----------------------------------------------------------------------*/

void mhintclear()
{
TGBL p_theWnd->HintBoxClear();
}

/*-----------------------------------------------------------------------*/

void mforcedisplay(void)
{
/* mprintf("<End_Of_Paragraph>\n");  */
}

void mcls(void)
{
(TGBL p_theWnd)->ClearText();
}

void mbeep(void)
{
//MessageBeep(MB_ICONEXCLAMATION);
}

void mwait(void)
{
if((TGBL p_theWnd)->ModalDialogs())
 { 
 AfxMessageBox("Continue?",MB_APPLMODAL|MB_OK|MB_ICONQUESTION); 
 }
else
 {
 (TGBL p_theWnd)->Disable();
 MessageBox(NULL,"Continue?","VPR waits...",MB_OK|MB_ICONQUESTION);
 (TGBL p_theWnd)->Enable();
 } 
}

/*-----------------------------------------------------------------------*/

void mmessage(char * tx)				/* MessageBox-type output if UI. */
{
mprintf("%s",tx);

if((TGBL p_theWnd)->ModalDialogs())
 { 
 AfxMessageBox(tx, MB_OK|MB_APPLMODAL);
 }
else
 {
 (TGBL p_theWnd)->Disable();
 MessageBox(NULL,tx,"VPR message:",MB_OK);
 (TGBL p_theWnd)->Enable();
 } 
}

/*-----------------------------------------------------------------------*/

bool mrequest_yn(char * tx)             /* a basic yes/no request can be */
{                                       /* replaced by GUI one.          */
bool r = FALSE;
mprintf("%s",tx);
mprintf(" (Y/N)? ");

if((TGBL p_theWnd)->ModalDialogs())
 { 
 if (AfxMessageBox(tx, MB_YESNO|MB_ICONQUESTION|MB_APPLMODAL)==IDYES)
  r=TRUE;
 }
else
 {
 (TGBL p_theWnd)->Disable();
 if (MessageBox(NULL,tx,"VPR asks...",MB_YESNO|MB_ICONQUESTION)==IDYES)
  r=TRUE;
 (TGBL p_theWnd)->Enable();
 } 

if(r) mprintf(" Yes.\n");
else  mprintf(" No. \n");

return r;
}

/*-----------------------------------------------------------------------*/

int mrequest_int(char * tx)             
{                                      

int c;
BOOL ok=FALSE;
CString buffer;
CVSDrqstr sd (tx, &buffer);

mprintf("%s (integer) : ",tx);

while(NOT ok)
 {
 sd.DoModal();

 if(sscanf(buffer,"%d",&c)>0) ok=TRUE;
 else mprintf("(Not an integer,Retry)\n");
 }

mprintf("(%d)\n",c);
return c;
}

/*-----------------------------------------------------------------------*/


DATA mrequest_DATA(char * tx)             
{                                      
DATA c;
BOOL ok=FALSE;
CString buffer;
CVSDrqstr sd (tx, &buffer);

mprintf("%s (",tx);
mprintf(DATADESCRI);
mprintf(") : ");

while(NOT ok)
 {
 sd.DoModal();

 if(sscanf(buffer,DATAFORMAT,&c)>0) ok=TRUE;
 else mprintf("(Invalid,Retry)\n");
 }

mprintf("(");
mprintf(DATAFORMAT,c);
mprintf(")\n");
return c;
}

/*-----------------------------------------------------------------------*/
// in this MMENU version we deleted parameter minsel since it was always 0

int mmenu(char * mtitle, char ** mlist,int mitems, int maxsel)
{

int s=-1;

if(NOT(TGBL no_error)) return 0;		// On error select 0 - exit.

CVSDmenu sd (mtitle, mlist, mitems, maxsel, &s);

sd.DoModal();
mprintf("\nOn %s.\nSelected : %s\n\n",mtitle, mlist[s]);
mcls();

return s;
}

/*-----------------------------------------------------------------------*/
/* simple bar plot (using text) can be replaced by GUI one.              */

#define PLOTBARMAX 50

void mplot_bar(DATA data[],                           /* Data to plot.   */
               int  dsize,                            /* Number of items.*/
               DATA max)                              /* Max data (100%) */
{
int * p;
int i,j;

if((NOT(TGBL no_error))||(dsize>99))
 {
 mprintf("MPLOTBAT: Cannot plot (more than 100 items?).\n");
 }
else
 {
 p=(int *)MMalloc(dsize*sizeof(int));

 if(TGBL no_error)
  {
  for(i=0;i<dsize;i++)
   p[i]=(int)((data[i]/max)*PLOTBARMAX);

  for(i=0;i<dsize;i++)
   {
   mprintf("%9.3f",(float)data[i]);
   mprintf("\t\t");

   if(i<10)mprintf("0");
   mprintf("%d : ",i);

   for(j=0;j<PLOTBARMAX;j++)
    if(j<=p[i])
     mprintf("X");
    else
     mprintf(" ");
   mprintf("\n");
   }
  mprintf(" \n");
  }
 MFree(p);
 }
mwait();
}


/*-----------------------------------------------------------------------*/
/* Display a progress report.                                            */


int currtick;
BOOL mticking=FALSE;
CVSDprogress * psdp = NULL;

void mendtick(void)
{
if(mticking)
 {
 mticking=FALSE;
 ReportToSessionFile("Done.\n");
 ReportTime();
 if (psdp!=NULL) delete(psdp);
 psdp=NULL;
 }
}

void mstarttick(char * message)
{
if(mticking==TRUE) mendtick();

currtick=0;
mticking=TRUE;

ReportTime();
ReportToSessionFile(message);
ReportToSessionFile("\n");

psdp = new CVSDprogress (message);
if (psdp!=NULL) psdp->Create();
}

void mtick(int cur,int max)
{
int i,steps,percent;
if(mticking)
 {
 if(max!=0)
  {
  mcls();
  percent=(int)(100*((float)cur/max));
  steps=percent-currtick; 
  for(i=0;i<steps;i++) 
   if (psdp!=NULL) psdp->Tick();
// if(steps>0) TGBL p_theWnd->Update();
  currtick=percent;
  }
 }
}

/*-----------------------------------------------------------------------*/

#endif // ndef _CONSOLE

extern int mprintf(const char * __format,...);

void mprintauthor()
 {
 char Author [50] = "weVtr.bgNdf.trNerighkhgoseltrantiytdrtiytsrt yt";
 for(int i=2;i<46;i=i+3) mprintf("%c",Author[i]);
 }