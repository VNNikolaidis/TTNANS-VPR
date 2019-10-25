#include "ttndef.hpp"
#ifdef _MSWINDOWS_

/* --------------------
   TTNANS:
   TTNGUIW1.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   -----------------------------
   MS-Win p4  (menu)
   -----------------------------

*/
#include "ttngui0.hpp"
#include "ttnident.hpp"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern char outputtitle[TEXTTITLESIZE];
int menuresultbuffer;

char mitem[MITEMNUM][MITEMLENGTH];

/*-----------------------------------------------------------------------*/

void gui0_beep(void)
{
MessageBeep(MB_OK);
}

/* Begin: Request MENU --------------------------------------------------*/


BOOL FAR PASCAL menuProc(HWND hDlg, unsigned message,
                         UINT wParam, LONG Unused)
{
int i;

switch (message)
 {
 case WM_INITDIALOG:
 case WM_PAINT:
  SendDlgItemMessage(hDlg,DI_OUTPUTTITLE,LB_ADDSTRING,0,(LONG)(LPSTR)(outputtitle));
  for(i=0;i<MITEMNUM;i++)
   SendDlgItemMessage(hDlg,DI_MENULIST,LB_ADDSTRING,0,(LONG)(LPSTR)(mitem[i]));
  return TRUE;

 case WM_COMMAND:
  switch(wParam)
   {
   case IDOK:
    menuresultbuffer=(int)SendDlgItemMessage(hDlg,DI_MENULIST,LB_GETCURSEL,0,0);
    EndDialog(hDlg,NULL);
    return(TRUE);
   case IDCANCEL:
    menuresultbuffer=(int)0;
    EndDialog(hDlg,NULL);
    return(TRUE);
   default   :break;
   }

 default:
  SetFocus(GetDlgItem(hDlg,DI_MENULIST));
  break;
 }
 return(FALSE);
}


int gui0_menu(void)
{
FARPROC lp_dialogProc;
int s;

s=-1;
SetFocus(glb_hWnd);
lp_dialogProc=MakeProcInstance((FARPROC)menuProc,glb_hInst);
if(lp_dialogProc!=NULL)
 {
 DialogBox(glb_hInst,(LPCSTR)"ttn_menu_DIALOG",glb_hWnd,(DLGPROC)lp_dialogProc);
 FreeProcInstance((FARPROC)lp_dialogProc);
 }
s=menuresultbuffer;
return s;
}

/* End: menu Dialog Box -----------------------------------------------*/

#endif
