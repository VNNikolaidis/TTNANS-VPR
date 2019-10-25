#include "VPR.h"
#include "VSPpage1.h"
#include "VSPcright.h"

class CVSDprop : public CPropertySheet
{
	DECLARE_DYNAMIC(CVSDprop)

// Construction
public:
	CVSDprop(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CVSDprop(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

	CVSPpage1		m_page1 ;
	CVSPcright		m_page2 ;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDprop)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVSDprop();
	virtual BOOL OnInitDialog();

	// Generated message map functions
protected:

	HICON m_hIcon;

	//{{AFX_MSG(CVSDprop)
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
