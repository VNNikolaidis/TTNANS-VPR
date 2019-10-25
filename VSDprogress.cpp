// VSDprogress.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDprogress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDprogress dialog


CVSDprogress::CVSDprogress(CString Title, CWnd* pParent /*=NULL*/)
	: CDialog(CVSDprogress::IDD, pParent)
{
     m_percent = 0;
	 //{{AFX_DATA_INIT(CVSDprogress)
	m_title = Title;
	//}}AFX_DATA_INIT
}


void CVSDprogress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDprogress)
	DDX_Control(pDX, IDC_PROGRESS1, m_progressctrl);
	DDX_Text(pDX, IDC_STATIC1, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSDprogress, CDialog)
	//{{AFX_MSG_MAP(CVSDprogress)
	ON_BN_CLICKED(ID_MISC_PAUSE, OnMiscPause)
	ON_BN_CLICKED(ID_MISC_ABORT, OnMiscAbort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDprogress message handlers

BOOL CVSDprogress::Create(CWnd* pParent)
{
if(CDialog::Create(IDD, pParent))
     {
	 m_progressctrl.SetRange(0,100);
	 return TRUE;
     }
 return FALSE;
}

void CVSDprogress::Tick()
 {
 CWnd * pparent = GetParent();

 if(m_percent<100) 
  {
  m_percent++;
  m_progressctrl.SetPos(m_percent);
  pparent->UpdateWindow();
  UpdateWindow();
//Default();
   {
   MSG message;
// GetMessage(&message,NULL,0,0);
   while(PeekMessage(&message,m_hWnd,0,0,PM_REMOVE)!=0)
    {
    TranslateMessage(&message);
    DispatchMessage(&message); 
    }
   }
  }
 }

void CVSDprogress::OnMiscPause() 
{
MessageBox("Processing Paused.\nPress OK to continue.","VPR Paused",MB_OK|MB_ICONEXCLAMATION);	
}

#include "ttnans/ttnerror.h"

void CVSDprogress::OnMiscAbort() 
{
if(MessageBox("This raises the error flag, causing\nthe method to abort as soon as possible.\nAre you sure you want to abort?","VPR Abort",MB_YESNO|MB_ICONSTOP)==IDYES)
 runerror(USRABRERR,"Abort condition raised"); 
}
