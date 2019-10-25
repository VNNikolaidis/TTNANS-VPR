// VPRView.h : interface of the CVPRView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VPRVIEW_H__8D6F94CD_E424_11D0_9AD4_F97634048723__INCLUDED_)
#define AFX_VPRVIEW_H__8D6F94CD_E424_11D0_9AD4_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VPR_TIMER_5_SEC 5000

class CVPRView : public CEditView
{
protected: // create from serialization only
	bool m_cls_mode;
    bool m_output_enabled;
    bool m_modal_dialogs;
    bool m_show_data_sets_in_window;
    bool m_old_style_file_requesters;

	CVPRView();
	DECLARE_DYNCREATE(CVPRView)

// Attributes
public:
	CVPRDoc* GetDocument();

// Operations
public:
    bool OldStyleFileRequesters () {return m_old_style_file_requesters;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVPRView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVPRView();
    void Update();
    void ClearText(bool check_cls_mode = true);
	void InsertText(CString);
	void Enable();
	void Disable();
    bool ModalDialogs();
    bool ShowDataSetsInWindow();
    void HintBoxClear();
    void InsertHintText(CString text);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVPRView)
	afx_msg void OnMiscClearscreenOn();
	afx_msg void OnMiscClearscreenOff();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnMiscClearscreenNow();
	afx_msg void OnMiscTextoutputon();
	afx_msg void OnMiscTextoutputoff();
	afx_msg void OnMiscModaldlgs();
	afx_msg void OnUpdateMiscModaldlgs(CCmdUI* pCmdUI);
	afx_msg void OnMiscSetsinwin();
	afx_msg void OnUpdateMiscSetsinwin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMiscClearscreenOn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMiscClearscreenOff(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMiscTextoutputoff(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMiscTextoutputon(CCmdUI* pCmdUI);
	afx_msg void OnMiscOldfilereq();
	afx_msg void OnUpdateMiscOldfilereq(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private: 
	UINT m_charsinbuffer;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in VPRView.cpp
inline CVPRDoc* CVPRView::GetDocument()
   { return (CVPRDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VPRVIEW_H__8D6F94CD_E424_11D0_9AD4_F97634048723__INCLUDED_)
