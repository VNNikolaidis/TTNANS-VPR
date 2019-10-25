// VSPpage1.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSPpage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSPpage1 property page

IMPLEMENT_DYNCREATE(CVSPpage1, CPropertyPage)

CVSPpage1::CVSPpage1() : CPropertyPage(CVSPpage1::IDD)
{
	//{{AFX_DATA_INIT(CVSPpage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CVSPpage1::~CVSPpage1()
{
}

void CVSPpage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSPpage1)
	DDX_Control(pDX, IDC_LIST3, m_listbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSPpage1, CPropertyPage)
	//{{AFX_MSG_MAP(CVSPpage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSPpage1 message handlers

void CVSPpage1::InsertText(CString text)
 {
 m_listbox.AddString(text);
 }

