#if !defined(AFX_CVSPCRIGHT_H__3180E0C2_E8EC_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_CVSPCRIGHT_H__3180E0C2_E8EC_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CVSPcright.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSPcright dialog

class CVSPcright : public CPropertyPage
{
	DECLARE_DYNCREATE(CVSPcright)

// Construction
public:
	CVSPcright();
	~CVSPcright();

// Dialog Data
	//{{AFX_DATA(CVSPcright)
	enum { IDD = IDD_SP_COPYRIGHT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CVSPcright)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVSPcright)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVSPCRIGHT_H__3180E0C2_E8EC_11D0_9AD5_F97634048723__INCLUDED_)
