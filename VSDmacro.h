#if !defined(AFX_VSDMACRO_H__6385D600_ED7F_11D1_8D65_DAEDF0C7108C__INCLUDED_)
#define AFX_VSDMACRO_H__6385D600_ED7F_11D1_8D65_DAEDF0C7108C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDmacro.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDmacro dialog

class CVSDmacro : public CDialog
{
// Construction
public:
	CVSDmacro(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVSDmacro)
	enum { IDD = IDD_SD_MACRO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDmacro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVSDmacro)
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonRec();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDMACRO_H__6385D600_ED7F_11D1_8D65_DAEDF0C7108C__INCLUDED_)
