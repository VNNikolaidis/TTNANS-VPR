// VSDoptions.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDoptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDoptions dialog


CVSDoptions::CVSDoptions(CWnd* pParent /*=NULL*/)
	: CDialog(CVSDoptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSDoptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVSDoptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDoptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSDoptions, CDialog)
	//{{AFX_MSG_MAP(CVSDoptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDoptions message handlers

BOOL CVSDoptions::Create(CWnd* pParentWnd) 
{
return CDialog::Create(IDD, pParentWnd);
}
