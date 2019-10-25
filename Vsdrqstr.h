#if !defined(AFX_CVSDrqstr_H__D2C4DC21_E685_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_CVSDrqstr_H__D2C4DC21_E685_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// VSDRqStr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDrqstr dialog

class CVSDrqstr : public CDialog
{
// Construction
public:
	CVSDrqstr(CWnd* pParent = NULL);   // standard constructor
	CVSDrqstr(CString cs_title, CString * p_str, CWnd * pParent = NULL);   

// Dialog Data
	//{{AFX_DATA(CVSDrqstr)
	enum { IDD = IDD_SD_REQSTRING };
	CEdit	m_edit1;
	CString	m_title;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDrqstr)
	public:
	virtual BOOL Create(CWnd* pParent = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString * m_pRetString;

	// Generated message map functions
	//{{AFX_MSG(CVSDrqstr)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVSDrqstr_H__D2C4DC21_E685_11D0_9AD5_F97634048723__INCLUDED_)
