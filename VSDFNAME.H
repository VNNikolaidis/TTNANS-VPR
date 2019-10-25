#if !defined(AFX_VSDFNAME_H__246392A1_E736_11D0_9AD5_F97634048723__INCLUDED_)
#define AFX_VSDFNAME_H__246392A1_E736_11D0_9AD5_F97634048723__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VSDfname.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSDfname dialog

class CVSDfname : public CFileDialog
{
	DECLARE_DYNAMIC(CVSDfname)

public:
	CVSDfname(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	CVSDfname(
        LPSTR pTitle,
        LPSTR pFilter,
        LPSTR pRetStr,
		int * pFileOffset,
        BOOL bOpenFileDialog = TRUE, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:

    int * m_pFileOffset;
	char m_csFilter [50];

    BOOL OnFileNameOK( );

	//{{AFX_MSG(CVSDfname)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSDFNAME_H__246392A1_E736_11D0_9AD5_F97634048723__INCLUDED_)
