#if !defined(AFX_VSPPAGE1_H__6BADC0A1_E9A1_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_VSPPAGE1_H__6BADC0A1_E9A1_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSPpage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSPpage1 dialog

class CVSPpage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CVSPpage1)

// Construction
public:
	CVSPpage1();
	~CVSPpage1();

   void InsertText(CString text);

// Dialog Data
	//{{AFX_DATA(CVSPpage1)
	enum { IDD = IDD_SP_PAGE_1 };
	CListBox	m_listbox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CVSPpage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVSPpage1)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSPPAGE1_H__6BADC0A1_E9A1_11D0_9AD5_F97634048723__INCLUDED_)
