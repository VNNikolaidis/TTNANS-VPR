// VSPcright.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSPcright.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VSPcright property page

IMPLEMENT_DYNCREATE(CVSPcright, CPropertyPage)

CVSPcright::CVSPcright() : CPropertyPage(CVSPcright::IDD)
{
	//{{AFX_DATA_INIT(CVSPcright)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CVSPcright::~CVSPcright()
{
}

void CVSPcright::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSPcright)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSPcright, CPropertyPage)
	//{{AFX_MSG_MAP(CVSPcright)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSPcright message handlers
