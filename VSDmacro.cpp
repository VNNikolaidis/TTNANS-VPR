// VSDmacro.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDmacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDmacro dialog


CVSDmacro::CVSDmacro(CWnd* pParent /*=NULL*/)
	: CDialog(CVSDmacro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSDmacro)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVSDmacro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDmacro)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSDmacro, CDialog)
	//{{AFX_MSG_MAP(CVSDmacro)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_REC, OnButtonRec)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDmacro message handlers

void CVSDmacro::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
	
}

void CVSDmacro::OnButtonRec() 
{
	// TODO: Add your control notification handler code here
	
}

void CVSDmacro::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	
}
