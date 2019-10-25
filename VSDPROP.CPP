#include "stdafx.h"
#include "VSDprop.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDprop

IMPLEMENT_DYNAMIC(CVSDprop, CPropertySheet)

CVSDprop::CVSDprop(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddControlPages();

	// TODO :: Add the pages for the rest of the controls here.
}

CVSDprop::CVSDprop(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddControlPages();
}

CVSDprop::~CVSDprop()
{
}

void CVSDprop::AddControlPages()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psh.dwFlags |= PSP_USEHICON;
	m_psh.hIcon = m_hIcon;

	AddPage(&m_page1);
	AddPage(&m_page2);
	}

BEGIN_MESSAGE_MAP(CVSDprop, CPropertySheet)
	//{{AFX_MSG_MAP(CVSDprop)
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDprop message handlers

BOOL CVSDprop::OnInitDialog()
{
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	return CPropertySheet::OnInitDialog();
}
HCURSOR CVSDprop::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}
