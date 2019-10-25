// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__8D6F94C9_E424_11D0_9AD4_F97634048723__INCLUDED_)
#define AFX_MAINFRM_H__8D6F94C9_E424_11D0_9AD4_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "VSDsplash.h"
#include "VSDHint.h"
#include "VSDoptions.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    bool HintBoxOn();
    void HintBoxOff();
    void TongleHintBox();
    void HintBoxClear(bool optaddline = true);
    void InsertHintText(CString text);

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CVSDsplash  m_wndSplash;
    CVSDoptions m_wndOptions;    
    CVSDhint * mp_HintBox;
	int m_oldX;
	int m_oldY;
      
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMiscHint();
	afx_msg void OnUpdateMiscHint(CCmdUI* pCmdUI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMiscOptions();
	afx_msg void OnMiscWwrap();
	afx_msg void OnMiscSelectfont();
	afx_msg void OnMiscSethcdelay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8D6F94C9_E424_11D0_9AD4_F97634048723__INCLUDED_)
