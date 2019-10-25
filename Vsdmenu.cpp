// VSDmenu.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDmenu.h"

#include "ttnans\ttndef_o.h"			// for reporttosessionfile check box
#include "ttnans\ttnreprt.h"			// for reporttosessionfile check box

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDmenu dialog


CVSDmenu::CVSDmenu(CWnd* pParent /*=NULL*/)
	: CDialog(CVSDmenu::IDD, pParent) , m_minsel(0)

{
	//{{AFX_DATA_INIT(CVSDmenu)
	m_title = _T("");
	//}}AFX_DATA_INIT

m_mlist=NULL;
m_mitems=0;
m_maxsel=0;
m_pRetInt=NULL;
m_title = "VPR Menu: Do not call this constructor!";
}

CVSDmenu::CVSDmenu(char * mtitle, char ** mlist, int mitems, int maxsel,
			 int * p_int, CWnd * pParent)
	: CDialog(CVSDmenu::IDD, pParent), m_minsel(0)
{
m_mlist=mlist;
m_mitems=mitems;
m_maxsel=maxsel;
m_pRetInt=p_int;

if(mtitle!=NULL)
 m_title=mtitle;
else 
 m_title=" - VPR Menu - ";
}

void CVSDmenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDmenu)
	DDX_Control(pDX, IDC_CHECK_RSESSION, m_check_rsession);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSDmenu, CDialog)
	//{{AFX_MSG_MAP(CVSDmenu)
    ON_LBN_DBLCLK(IDC_LIST1,OnLbnDblclk)
	ON_BN_CLICKED(ID_MISC_PROPERTIES, OnMiscProperties)
	ON_BN_CLICKED(IDC_CHECK_RSESSION, OnCheckRsession)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDmenu message handlers

BOOL CVSDmenu::Create(CWnd* pParent) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(CDialog::Create(IDD, pParent))
     return TRUE;
    return FALSE;
}


void CVSDmenu::OnLbnDblclk()
{
OnOK();
}

void CVSDmenu::OnOK()
{
int p = m_list1.GetCurSel();
if(m_pRetInt!=NULL)
 if (!((p<m_minsel)||(p>m_maxsel)))
  {
  * m_pRetInt = p;
  CDialog::OnOK();
  }
}

void CVSDmenu::OnCancel()
{
if(m_pRetInt!=NULL) *m_pRetInt = 0;
CDialog::OnCancel();
} 

/*-----------------------------------------*/
 
#include "ttnans\ttnmain.h"

void CVSDmenu::OnMiscProperties() 
{
if(ptg!=NULL) ptg->TonglePropertiesBox();
}

/*-----------------------------------------*/

BOOL CVSDmenu::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(sessionenabled)m_check_rsession.SetCheck(1);
	else m_check_rsession.SetCheck(0);

	m_list1.ResetContent();								// initialize it
    if(m_mlist != NULL)
	 {
     for(int i=0;i<m_mitems;i++)
      m_list1.AddString(m_mlist[i]);
	 }
	m_list1.SetFocus();
	
	return FALSE;  // return TRUE unless you set the focus to a control
	               // EXCEPTION: OCX Property Pages should return FALSE
}

void CVSDmenu::OnCheckRsession()    // NOTE! we #included "ttnans/ttnreprt.h" for this!!!
{
if(sessionenabled)
 StopReporting();
else
 StartReporting();

if(sessionenabled)m_check_rsession.SetCheck(1);
else m_check_rsession.SetCheck(0);
}
