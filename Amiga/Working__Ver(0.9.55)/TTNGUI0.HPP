#include <windows.h>
#include <bwcc.h>

/* prototypes */
BOOL init_app(HANDLE);
BOOL init_inst(HANDLE, int);
long WINAPI _export ttn_win_proc(HWND, UINT, UINT, LONG);
void menu(HWND,UINT);
int init(HANDLE,HANDLE,int);

extern HWND glb_hWnd;
extern HINSTANCE glb_hInst;

