#include "ttnans\ttndef_o.h"

//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_VSDDATASET_H__0CE27FE0_8904_11D1_8D65_F293211F675C__INCLUDED_)
#define AFX_VSDDATASET_H__0CE27FE0_8904_11D1_8D65_F293211F675C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDdataset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDdataset dialog

class CVSDdataset : public CDialog
{
// Construction
public:
	CVSDdataset(DATA ** data, unsigned rows, unsigned cols,char * title, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVSDdataset)
	enum { IDD = IDD_SD_DATASET };
	CProgressCtrl	m_progress;
	CMSFlexGrid	m_flexgrid;
	CString	m_cols_out;
	CString	m_rows_out;
	//}}AFX_DATA

    DATA ** m_data;
    unsigned m_rows;
    unsigned m_cols;
    char * m_title;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSDdataset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVSDdataset)
	afx_msg void OnDatasetScale();
	afx_msg void OnDatasetSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDDATASET_H__0CE27FE0_8904_11D1_8D65_F293211F675C__INCLUDED_)
