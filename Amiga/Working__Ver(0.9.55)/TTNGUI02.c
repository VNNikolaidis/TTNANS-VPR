#include "ttndef.hpp"
#ifdef _MSWINDOWS_

/* --------------------
   TTNANS:
   TTNGUIW1.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   MS-Win p2 requests  (STRING,DATA,INT)
   --------------------

*/

#include "ttngui0.hpp"
#include <stdlib.h>
#include <ctype.h>
#include "ttnident.hpp"

 extern char outputtitle[TEXTTITLESIZE];

 char tbuff[INPUTTEXTSIZE];

/* Begin: Request string --------------------------------------------------*/

LONG FAR PASCAL reqstringProc(HWND hDlg, unsigned message,
                              WORD wParam, LONG Unused)
{
 switch (message)
  {
  case WM_INITDIALOG:
  case WM_PAINT: SendDlgItemMessage(hDlg,DI_OUTPUTTITLE_STR,LB_ADDSTRING,0,(LONG)(LPSTR)(outputtitle));
                 SetFocus(GetDlgItem(hDlg,DI_NUMEDIT));
                 break;

  case WM_COMMAND:switch(wParam)
                 {
                 case IDOK:
                            GetWindowText(GetDlgItem(hDlg,DI_NUMEDIT),(LPSTR)tbuff,INPUTTEXTSIZE);
                            EndDialog(hDlg,NULL);
                            return(TRUE);
                 default   :break;
                 }
  }
return(FALSE);
}

void gui0_input_string(void)
{
FARPROC lp_dialogProc;
int i;

for(i=0;i<INPUTTEXTSIZE;i++) tbuff[i]='\0';

lp_dialogProc=MakeProcInstance((FARPROC)reqstringProc,glb_hInst);
if(lp_dialogProc!=NULL)
 {
 DialogBox(glb_hInst,"ttn_string_DIALOG",glb_hWnd,(DLGPROC)lp_dialogProc);
 FreeProcInstance(lp_dialogProc);
 }
}

/* End: string Dialog Box -----------------------------------------------*/

int gui0_input_int(void)
{
BOOL ok=FALSE;
int i;

while(!ok)
 {
 gui0_input_string();
 i=0;
 ok=TRUE;

 while(i<INPUTTEXTSIZE)
  {
  if((isdigit(tbuff[i]))||
     (tbuff[i]=='+')||
     (tbuff[i]=='-')||
     (tbuff[i]=='\0')) ok=ok&&TRUE;
  else
    ok=FALSE;
  i++;
  }
 }
 return atoi(tbuff);
}


DATA gui0_input_DATA(void)
{
BOOL ok=FALSE;
int i;

while(!ok)
 {
 gui0_input_string();
 i=0;
 ok=TRUE;
 while(i<INPUTTEXTSIZE)
  {
  if((isdigit(tbuff[i]))||
     (tbuff[i]=='+')||
     (tbuff[i]=='-')||
     (tbuff[i]=='.')||
     (tbuff[i]=='\0')) ok=ok&&TRUE;
  else
    ok=FALSE;
  i++;
  }
 }
 return (DATA)_atold(tbuff);
}

#endif
