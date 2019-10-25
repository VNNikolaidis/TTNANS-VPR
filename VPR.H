// VPR.h : main header file for the VPR application
//

#if !defined(AFX_VPR_H__8D6F94C5_E424_11D0_9AD4_F97634048723__INCLUDED_)
#define AFX_VPR_H__8D6F94C5_E424_11D0_9AD4_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVPRApp:
// See VPR.cpp for the implementation of this class
//

class CVPRApp : public CWinApp
{
public:
	CVPRApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVPRApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVPRApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VPR_H__8D6F94C5_E424_11D0_9AD4_F97634048723__INCLUDED_)
