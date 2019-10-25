#if !defined(AFX_VSDSPLASH_H__2BF19201_E7F5_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_VSDSPLASH_H__2BF19201_E7F5_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDsplash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDsplash dialog

class CVSDsplash : public CDialog
{
// Construction
public:
	CVSDsplash(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVSDsplash)
	enum { IDD = IDD_SD_SPLASH };
	CString	m_static_revision;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDsplash)
	public:
	virtual BOOL Create(CWnd* pParentWnd = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVSDsplash)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDSPLASH_H__2BF19201_E7F5_11D0_9AD5_F97634048723__INCLUDED_)
