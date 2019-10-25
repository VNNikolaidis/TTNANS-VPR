#if !defined(AFX_VSDMENU_H__F1422BC1_E72B_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_VSDMENU_H__F1422BC1_E72B_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDmenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDmenu dialog

class CVSDmenu : public CDialog
{
// Construction
public:
	CVSDmenu(CWnd* pParent = NULL);   // standard constructor

	CVSDmenu(char * mtitle, char ** mlist, int mitems, int maxsel,
			 int * p_int, CWnd * pParent=NULL);

    int Create(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CVSDmenu)
	enum { IDD = IDD_SD_MENU };
	CButton	m_check_rsession;
	CListBox	m_list1;
	CString		m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDmenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	char ** m_mlist;
    int m_mitems;
    const int m_minsel;
	int m_maxsel;
	int * m_pRetInt;

	void OnCancel();
	void OnOK();
	
	// Generated message map functions
	//{{AFX_MSG(CVSDmenu)
    afx_msg void OnLbnDblclk( );
	afx_msg void OnMiscProperties();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckRsession();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDMENU_H__F1422BC1_E72B_11D0_9AD5_F97634048723__INCLUDED_)
