// VsdRqStr.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDrqstr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDrqstr dialog


CVSDrqstr::CVSDrqstr(CWnd* pParent /*=NULL*/)
	: CDialog(CVSDrqstr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSDrqstr)
	m_title = _T("");
	//}}AFX_DATA_INIT
	m_pRetString = NULL;
}


CVSDrqstr::CVSDrqstr(CString cs_title, CString * r_str, CWnd * pParent)
	: CDialog(CVSDrqstr::IDD, pParent)
{
m_title = cs_title;
m_pRetString = r_str;
}

void CVSDrqstr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDrqstr)
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSDrqstr, CDialog)
	//{{AFX_MSG_MAP(CVSDrqstr)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDrqstr message handlers

void CVSDrqstr::OnOK() 
{
if(	m_pRetString != NULL)
 m_edit1.GetWindowText(* m_pRetString);
CDialog::OnOK();
}

void CVSDrqstr::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_edit1.SetFocus();

	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CVSDrqstr::Create(CWnd* pParent /*=NULL*/)
{
if(CDialog::Create(IDD, pParent))
     {
	 return TRUE;
     }
 return FALSE;
}

