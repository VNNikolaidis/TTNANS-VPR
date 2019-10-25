#include "ttndef.hpp"
#ifdef _MSWINDOWS_

#include "ttngui0.hpp"

/* --------------------
   TTNANS:
   TTNGUIW1.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   -----------------------------
   MS-Win p3  requests (BOOL,about)
   -----------------------------

*/

#include <stdlib.h>
#include <string.h>
#include "ttnident.hpp"


extern char outputtitle[TEXTTITLESIZE];
BOOL Boolresultbuffer;

/*---- about --------------------------------------------------------------*/

LONG FAR PASCAL aboutProc(HWND hDlg, unsigned message,
                          WORD wParam, LONG Unused)
{
switch(message)
 {
 case WM_COMMAND:    switch(wParam)
                          {
                          case IDOK: EndDialog(hDlg,NULL);
                                     return(FALSE);
                          default   :return (TRUE);
                          }
 case WM_DESTROY :   EndDialog(hDlg,NULL);
                     return(TRUE);

 }
return(FALSE);
}

void gui0_ttn_about()
{
FARPROC lp_aboutProc;

lp_aboutProc=MakeProcInstance((FARPROC)aboutProc,glb_hInst);
if(lp_aboutProc!=NULL)
 {
 DialogBox(glb_hInst,"ttn_about_DIALOG",GetFocus(),(DLGPROC)lp_aboutProc);
 FreeProcInstance(lp_aboutProc);
 }
}

/* End: "About" Dialog Box ------------------------------------------------*/


/* Begin: Request Boolean--------------------------------------------------*/

LONG FAR PASCAL reqboolProc(HWND hDlg, unsigned message,
                            WORD wParam, LONG Unused)
{
 switch (message)
  {
  case WM_INITDIALOG:
  case WM_PAINT: SendDlgItemMessage(hDlg,DI_OUTPUTTITLE_BOOL,LB_ADDSTRING,0,(LONG)(LPSTR)(outputtitle));
                 break;

  case WM_COMMAND:switch(wParam)
                 {
                 case DI_YES:
                            Boolresultbuffer=1;
                            EndDialog(hDlg,NULL);
                            return(TRUE);
                 case DI_NO:
                            Boolresultbuffer=0;
                            EndDialog(hDlg,NULL);
                            return(TRUE);
                 default   :break;
                 }
  }
return(FALSE);
}

BOOL gui0_input_BOOL(void)
{
FARPROC lp_dialogProc;

lp_dialogProc=MakeProcInstance((FARPROC)reqboolProc,glb_hInst);
if(lp_dialogProc!=NULL)
 {
 DialogBox(glb_hInst,"ttn_getbool_DIALOG",glb_hWnd,(DLGPROC)lp_dialogProc);
 FreeProcInstance(lp_dialogProc);
 }
return Boolresultbuffer;
}

/* End: bool Dialog Box -----------------------------------------------*/

void gui0_wait(void)
{
MessageBox(GetFocus(),"Continue?","",MB_ICONQUESTION|MB_OK);
}


#endif
