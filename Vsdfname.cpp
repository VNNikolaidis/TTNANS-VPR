// VSDfname.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDfname.h"
#include "ttnans\ttnpros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDfname

IMPLEMENT_DYNAMIC(CVSDfname, CFileDialog)

CVSDfname::CVSDfname(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

CVSDfname::CVSDfname(LPSTR pTitle, LPSTR pFilter, LPSTR pRetStr, int * pFileOffset,
        BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{

if((TGBL p_theWnd)->ModalDialogs())
 { 
 AfxMessageBox(pTitle,MB_APPLMODAL|MB_OK);
 }
else
 {
 (TGBL p_theWnd)->Disable();
 MessageBox(pTitle,"Filename requested:",MB_OK);
 (TGBL p_theWnd)->Enable();
 } 

strcpy(pRetStr,"");
m_ofn.lpstrFile=pRetStr;
m_ofn.lpstrFilter ="All Files. (*.*)\0*.*\0"
				   "Problem Description Files. (*.prb)\0*.prb\0"
                   "Descriptor Files. (*.des)\0*.des\0"
				   "Full Descriptor Class Files. (*.f*)\0*.f*\0"
				   "Selected Descriptor Class Files. (*.x*)\0*.x*\0"
				   "Scaled Descriptor Class Files. (*.s*)\0*.s*\0"
                   "EPA Data Files. (*.epa)\0*.epa\0"
                   "Text Files. (*.txt)\0*.txt\0"
                   "Data Files. (*.dat)\0*.dat\0\0";

// Create a suggested file filter prompt.
strcpy(m_csFilter,"Suggested Files. (");
strncat(m_csFilter,pFilter,5);
strcat(m_csFilter,")");
int i=strlen(m_csFilter);
int j=strlen(pFilter);
strcpy(m_csFilter+i+1,pFilter);
m_ofn.lpstrCustomFilter = m_csFilter;
m_ofn.nMaxCustFilter = i+j+1;
//

m_pFileOffset=pFileOffset;
}

BOOL CVSDfname::OnFileNameOK( )
{
if(m_pFileOffset!=NULL)
 * m_pFileOffset = m_ofn.nFileOffset;
return(CFileDialog::OnFileNameOK( ));
}


BEGIN_MESSAGE_MAP(CVSDfname, CFileDialog)
	//{{AFX_MSG_MAP(CVSDfname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

