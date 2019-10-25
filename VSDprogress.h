#if !defined(AFX_VSDPROGRESS_H__2AAFD221_E814_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_VSDPROGRESS_H__2AAFD221_E814_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDprogress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDprogress dialog

class CVSDprogress : public CDialog
{
// Construction
public:
	CVSDprogress(CString title, CWnd* pParent = NULL);   // standard constructor
	void Tick();

// Dialog Data
	//{{AFX_DATA(CVSDprogress)
	enum { IDD = IDD_SD_PROGRESS };
	CProgressCtrl	m_progressctrl;
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDprogress)
	public:
	virtual BOOL Create(CWnd* pParent = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	int m_percent;
	// Generated message map functions
	//{{AFX_MSG(CVSDprogress)
	afx_msg void OnMiscPause();
	afx_msg void OnMiscAbort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDPROGRESS_H__2AAFD221_E814_11D0_9AD5_F97634048723__INCLUDED_)
