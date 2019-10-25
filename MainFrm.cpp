// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VPR.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MISC_HINT, OnMiscHint)
	ON_UPDATE_COMMAND_UI(ID_MISC_HINT, OnUpdateMiscHint)
	ON_WM_MOVE()
	ON_COMMAND(ID_MISC_OPTIONS, OnMiscOptions)
	ON_COMMAND(ID_MISC_WWRAP, OnMiscWwrap)
	ON_COMMAND(ID_MISC_SELECTFONT, OnMiscSelectfont)
	ON_COMMAND(ID_MISC_SETHCDELAY, OnMiscSethcdelay)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
mp_HintBox = NULL;
}

CMainFrame::~CMainFrame()
{
HintBoxOff();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    m_wndSplash.Create(this);
 	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/*------------------------------------------------------------------------*/

bool CMainFrame::HintBoxOn()
{
if(mp_HintBox == NULL)
 {
 mp_HintBox = new CVSDhint (/*this*/);
 mp_HintBox->Create();
 }
if(mp_HintBox == NULL)
 return FALSE;

 {
 RECT Rect;
 GetClientRect(&Rect);
 ClientToScreen(&Rect);
/*
 mp_HintBox->Move( Rect.right -((Rect.right-Rect.left)/3),
                   Rect.top+31, // Rect.bottom-((Rect.bottom-Rect.top)/2),
                   (Rect.right-Rect.left)/3,
                   (Rect.bottom-Rect.top)/3 );
*/

 mp_HintBox->Move( Rect.left,
                   Rect.top + 31, 
                   (Rect.right-Rect.left),
                   (Rect.bottom-Rect.top) / 5 );
 }

#ifdef _DEBUG
for(int i=0;i<6;i++)
 {
 HintBoxClear();
 for(int j=i;j<5;j++) InsertHintText(" ");
 InsertHintText("   OOO       OOO  OOOOOO    OOOOOOO  ");
 InsertHintText("    OOO     OOO  OOO  OOO  OOO  OOO  ");
 InsertHintText("     OOO   OOO  OOO  OOO  OOO  OOO   ");
 InsertHintText("      OOO OOO  OOOOOOO   OOOOOOO     ");
 InsertHintText("       OOOOO  OOO       OOO OOO      ");
 InsertHintText("        OOO  OOO       OOO   OOO     ");
 Sleep(50);
 }
Sleep(1000);
HintBoxClear();
#endif

return TRUE;
}

void CMainFrame::HintBoxOff()
{
if(mp_HintBox != NULL) 
 {
 delete (mp_HintBox);
 mp_HintBox = NULL;
 }
}

void CMainFrame::TongleHintBox()
{
if(mp_HintBox == NULL)
 HintBoxOn();
else
 HintBoxOff();
}

void CMainFrame::HintBoxClear(bool optaddline)
{
if(mp_HintBox != NULL) 
 mp_HintBox->ClearText(optaddline);
}


void CMainFrame::InsertHintText(CString text)
{
if(mp_HintBox != NULL) 
 mp_HintBox->InsertText(text);
}

void CMainFrame::OnMiscHint() 
{
if(mp_HintBox == NULL)
 HintBoxOn();
else HintBoxOff();
	
}

void CMainFrame::OnUpdateMiscHint(CCmdUI* pCmdUI) 
{
if(mp_HintBox == NULL)
 pCmdUI->SetCheck(0);
else 
 pCmdUI->SetCheck(1);
}

/*------------------------------------------------------------------------*/

void CMainFrame::OnMove(int x, int y) 
{
CFrameWnd::OnMove(x, y);

if(mp_HintBox != NULL)
 mp_HintBox->Move(x-m_oldX,y-m_oldY);	// OnMove gets called before user can start HintBox.

m_oldX=x;		
m_oldY=y;
}

/*------------------------------------------------------------------------*/

void CMainFrame::OnMiscOptions() 
{
m_wndOptions.Create(this);
}

void CMainFrame::OnMiscWwrap() 
{
if(mp_HintBox != NULL)
 mp_HintBox->OnMiscWwrap();
}

void CMainFrame::OnMiscSelectfont() 
{
if(mp_HintBox != NULL)
 mp_HintBox->OnMiscSelectfont();
}

/*------------------------------------------------------------------------*/

void CMainFrame::OnMiscSethcdelay() 
{
if(mp_HintBox != NULL)
 mp_HintBox->SetClearDelay();
}

/*------------------------------------------------------------------------*/
