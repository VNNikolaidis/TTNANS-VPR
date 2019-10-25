// VSDsplash.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDsplash.h"
#include "VPRrevision.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDsplash dialog


CVSDsplash::CVSDsplash(CWnd* pParent /*=NULL*/)
	: CDialog(CVSDsplash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSDsplash)
	m_static_revision = VPR_REVISION;
	//}}AFX_DATA_INIT
}


void CVSDsplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDsplash)
	DDX_Text(pDX, IDC_STATIC_REV, m_static_revision);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSDsplash, CDialog)
	//{{AFX_MSG_MAP(CVSDsplash)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDsplash message handlers

void CVSDsplash::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialog::OnOK();	
	//	CDialog::OnTimer(nIDEvent);
}


BOOL CVSDsplash::Create(CWnd* pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(CDialog::Create(IDD, pParentWnd))
     {
     SetTimer(1,5000,NULL);
	 return TRUE;
     }
 return FALSE;
}
