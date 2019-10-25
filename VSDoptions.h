#if !defined(AFX_VSDOPTIONS_H__27929A22_CFE3_11D1_8D65_E06217D7769D__INCLUDED_)
#define AFX_VSDOPTIONS_H__27929A22_CFE3_11D1_8D65_E06217D7769D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDoptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDoptions dialog

class CVSDoptions : public CDialog
{
// Construction
public:
	CVSDoptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVSDoptions)
	enum { IDD = IDD_SD_OPTIONS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDoptions)
	public:
	virtual BOOL Create(CWnd* pParentWnd = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVSDoptions)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDOPTIONS_H__27929A22_CFE3_11D1_8D65_E06217D7769D__INCLUDED_)
