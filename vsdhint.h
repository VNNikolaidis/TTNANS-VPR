#if !defined(AFX_VSDhint_H__0F7780E1_E9CA_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_VSDhint_H__0F7780E1_E9CA_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDhint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDhint dialog

class CVSDhint : public CDialog
{
// Construction
public:
	CVSDhint(CWnd* pParent = NULL);   // standard constructor
	~CVSDhint();
 
    BOOL Create(CWnd* pParent = NULL);
    void InsertText(CString text);
    void InsertTextWrap(CString text);
	void ClearText(bool optaddline = true);
    void Move(int x,int y,int dx,int dy);	// Move at...
    void Move(int x,int y);					// Move relative to old pos...
    void OnMiscWwrap(); 
    void OnMiscSelectfont(); 
    void SetClearDelay();

// Dialog Data
	//{{AFX_DATA(CVSDhint)
	enum { IDD = IDD_SD_HINT };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDhint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    unsigned m_list_limit;
    bool m_word_wrap;
    time_t m_last_update_time;    
    static int m_last_update_time_delay;    

// Implementation
protected:
	
    // Generated message map functions
	//{{AFX_MSG(CVSDhint)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDhint_H__0F7780E1_E9CA_11D0_9AD5_F97634048723__INCLUDED_)
