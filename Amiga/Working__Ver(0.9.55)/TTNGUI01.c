#include "ttndef.hpp"
#ifdef _MSWINDOWS_

/* Basic text window for WTTNANS shell */

#include <string.h>
#include <dir.h>
#include "ttnmain.hpp"
#include "ttngui0.hpp"
#include "ttnident.hpp"
#include "ttnreprt.hpp"

#define FONTNAME "ttnans.fon"
PSTR pszFace = "TTNFont";

CATCHBUF exitbuf;
/* current instance */
HANDLE glb_hInst;
/* main window */
HWND glb_hWnd,edit_win;

int nFontload;

char startup_dir [255];
BOOL ttnans_running=FALSE;

int gui0_CLSflag=TRUE;

extern void main(void);
extern void gui0_ttn_about(void);

char outputtitle[TEXTTITLESIZE];

/* Main window function */
int PASCAL WinMain(HANDLE hInst, HANDLE prev,
				   LPSTR Unused, int show)
{
MSG msg;
if (!init(hInst,prev,show)) return FALSE;
/* Vanilla event loop */
if (Catch(exitbuf)) return 0;

while (GetMessage(&msg,NULL,NULL,NULL))
 {
 TranslateMessage(&msg);
 DispatchMessage(&msg);
 }

/* Exit program */
return (msg.wParam);
}

/* Start up stuff */
int init(HANDLE hInst, HANDLE prev,int show)
{
if (!prev)
 {
 if (!init_app(hInst))   /* Exit if unable to initialize */
  return FALSE;
        }
 /* Perform instance init */
 if (!init_inst(hInst,show))
  return FALSE;
 return TRUE;
 }

/* Create window class here */
BOOL init_app(HANDLE hInstance)
{
WNDCLASS  wc;
wc.style=NULL;
wc.lpfnWndProc=ttn_win_proc;
wc.cbClsExtra=0;
wc.cbWndExtra=0;
wc.hInstance=hInstance;
wc.hIcon=LoadIcon(hInstance,(LPCSTR)(UINT)ttn_ICON);
wc.hCursor=LoadCursor(hInstance,(LPCSTR)(UINT)ttn_CURSOR);
wc.hbrBackground=GetStockObject(GRAY_BRUSH);
wc.lpszMenuName=(LPCSTR)(UINT)ttn_MENU1;
wc.lpszClassName="WTTNANS_Class";
return (RegisterClass(&wc));
}

/* Create window here */
BOOL init_inst(HANDLE hInstance, int nCmdShow)
{
HWND hWnd;

getcwd(startup_dir,255);

/* Save the instance handle in global variable */
glb_hInst=hInstance;

/* Create a main window */
glb_hWnd=hWnd=CreateWindow("WTTNANS_Class",
                           "TTNANS For MS-Windows.",
                           WS_OVERLAPPEDWINDOW,
						   CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           CW_USEDEFAULT,
                           NULL,
                           NULL,
                           hInstance,
                           NULL
                           );

if (!hWnd)
 return FALSE;

/* Make the window visible, update its client area,and return "success" */

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);
return (TRUE);
}

/* Window procedure */

long WINAPI _export ttn_win_proc(HWND hWnd, UINT message,
								 UINT wParam, LONG lParam)
{
HFONT hFont;

switch (message)
 {
 RECT r;
 case WM_CREATE:

  GetClientRect(hWnd,&r);
  edit_win=CreateWindow("edit","",
                        WS_CHILD|
                        WS_THICKFRAME|
                        WS_HSCROLL|
                        WS_VSCROLL|
                        ES_AUTOHSCROLL|
						ES_AUTOVSCROLL|
                        ES_MULTILINE|
                        WS_VISIBLE|
                        ES_READONLY
                        ,0,0,r.right,r.bottom,hWnd,
                        (HMENU)1,glb_hInst,0);

/* Set fixed font */

  nFontload=AddFontResource(FONTNAME);
  if(!nFontload)
   {
   MessageBox(GetFocus(),FONTNAME,"Warning! Not found:",MB_ICONHAND|MB_OK);
   SendMessage(edit_win,WM_SETFONT,GetStockObject(OEM_FIXED_FONT),0);
   }
  else
   {
   SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
   hFont = CreateFont(0, 0, 0, 0, 0,                     /* specify pt size    */
                    0, 0, 0, 255, 0, 0, 0, 0, pszFace);  /* and face name only */

   SendMessage(edit_win,WM_SETFONT,hFont,0);
   }

/* Work with the font... */

/* Don't limit amount of text in control */
  SendMessage(edit_win,EM_LIMITTEXT,0,0);
  break;

 case WM_COMMAND:
  menu(hWnd,wParam);
  break;

 case WM_CLOSE:
  PostMessage(hWnd,WM_DESTROY,0,0);
  break;

 case WM_DESTROY:
  menu(hWnd,MI_LOGFILEOFF);
  if (RemoveFontResource(FONTNAME))
   SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
  PostQuitMessage(0);
  break;

/* Move edit window to match frame window */

 case WM_SIZE:
  {
  RECT r;
  DWORD  old;
  int height;
  if (wParam==SIZEICONIC) break;
  GetWindowRect(hWnd,&r);
  height=r.bottom-r.top;
  MoveWindow(edit_win,0,height/2,LOWORD(lParam),HIWORD(lParam)-(height/2),TRUE);
  old=SendMessage(edit_win,EM_GETSEL,0,0);
  SendMessage(edit_win,EM_SETSEL,0,0);
  SendMessage(edit_win,EM_SETSEL,0,old);
  }
  break;

 default:
  return (DefWindowProc(hWnd, message,wParam, lParam));
 }
return 0;
}

void gui0_cls(void);

/* Process menu choices */

void menu(HWND hWnd,UINT wParam)
{
switch (wParam)
 {
 case MI_START :
  gui0_cls();
  if(!ttnans_running)
   {
   ttnans_running=TRUE;
   MMAIN();
   ttnans_running=FALSE;
   }
  else MessageBox(GetFocus(),"TTNANS already running...","WinTTNANS",MB_ICONSTOP|MB_OK);
  break;

 case MI_STOP  :
  MessageBox(GetFocus(),"Thank you for using wTTNANS.","Quit",MB_ICONASTERISK|MB_OK);
  PostMessage(hWnd,WM_DESTROY,0,0);
  break;

 case MI_TEXTEDIT:
  if (WinExec("notepad.exe",SW_SHOW)<32)
   MessageBox(GetFocus(),"Cannot start editor.","Text Editor Error",MB_ICONSTOP|MB_OK);
  break;

 case MI_CLS   :
  if(gui0_CLSflag==1)
   {
   gui0_CLSflag=0;
   MessageBox(GetFocus(),"CLS is now off.","TTNANS",MB_ICONASTERISK|MB_OK);
   }
  else
   {
   gui0_CLSflag=1;
   MessageBox(GetFocus(),"CLS is now on.","TTNANS",MB_ICONASTERISK|MB_OK);
   }
 break;

 case MI_MEMORY :
   sprintf(outputtitle,"Free Global: %u Kb",GetFreeSpace((UINT)0)/1024);
   MessageBox(GetFocus(),outputtitle,"Memory Report:",MB_OK);
   break;

 case MI_ABOUT :
  gui0_ttn_about();
  break;

 case MI_LOGFILEON :
  StartReporting();
  break;

 case MI_LOGFILEOFF :
  StopReporting();
  break;

 default:
  break;
 }
}

/* Put string in window */

void gui0_puts(char *s)
{
SendMessage(edit_win,EM_SETSEL,0,MAKELONG(32767,32767));
SendMessage(edit_win,EM_REPLACESEL,0,(DWORD)s);
}

/* Allow other programs to process */

void yield()
{
MSG m;
if (InSendMessage()) return;
if (PeekMessage(&m,NULL,0,0,PM_NOREMOVE))
 {
 GetMessage(&m,NULL,0,0);
 TranslateMessage(&m);
 DispatchMessage(&m);
 if (m.message==WM_QUIT) Throw(exitbuf,1);
 }
}

/* Clear screen */

void gui0_cls(void)
{
SendMessage(edit_win,EM_SETREADONLY,0,0);
SendMessage(edit_win,EM_SETSEL,0,MAKELONG(0,-1));
SendMessage(edit_win,WM_CLEAR,0,0);
SendMessage(edit_win,EM_SETREADONLY,1,0);
SendMessage(edit_win,WM_PAINT,0,0);
}

#endif
