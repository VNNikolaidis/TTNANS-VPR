// VPRDoc.h : interface of the CVPRDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VPRDOC_H__8D6F94CB_E424_11D0_9AD4_F97634048723__INCLUDED_)
#define AFX_VPRDOC_H__8D6F94CB_E424_11D0_9AD4_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CVPRView;

class CVPRDoc : public CDocument
{
private:
    CVPRView * m_pView;				// Points to the View (this is SDI)...
 
public:
	DECLARE_DYNCREATE(CVPRDoc)

    CVPRDoc();
    ~CVPRDoc();
    BOOL OnNewDocument();
	void Serialize(CArchive& ar);
	//{{AFX_MSG(CVPRDoc)
	afx_msg void OnRunTtnmenu1();
	afx_msg void OnRunTtnmenu2();
	afx_msg void OnRunTtnmenu3();
	afx_msg void OnRunTtnmenu4();
	afx_msg void OnRunTtnmenu5();
	afx_msg void OnRunTtnmenu6();
	afx_msg void OnRunTtnmenu7();
	afx_msg void OnRunTtnans();
	afx_msg void OnRunTtnansRec();
	afx_msg void OnRunTtnmenu8();
	//}}AFX_MSG

    #ifdef _DEBUG
    void AssertValid() const;
    void Dump(CDumpContext& dc) const;
    #endif //_DEBUG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VPRDOC_H__8D6F94CB_E424_11D0_9AD4_F97634048723__INCLUDED_)
