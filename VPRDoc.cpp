// VPRDoc.cpp : implementation of the CVPRDoc class
//

#include "stdafx.h"
#include "VPR.h"

#include "VPRDoc.h"
#include "VPRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void ttnans_main(CVPRView *,int preselect = -1,bool start_rec = false);

/////////////////////////////////////////////////////////////////////////////
// CVPRDoc

IMPLEMENT_DYNCREATE(CVPRDoc, CDocument)

BEGIN_MESSAGE_MAP(CVPRDoc, CDocument)
	//{{AFX_MSG_MAP(CVPRDoc)
	ON_COMMAND(ID_RUN_TTNMENU1, OnRunTtnmenu1)
	ON_COMMAND(ID_RUN_TTNMENU2, OnRunTtnmenu2)
	ON_COMMAND(ID_RUN_TTNMENU3, OnRunTtnmenu3)
	ON_COMMAND(ID_RUN_TTNMENU4, OnRunTtnmenu4)
	ON_COMMAND(ID_RUN_TTNMENU5, OnRunTtnmenu5)
	ON_COMMAND(ID_RUN_TTNMENU6, OnRunTtnmenu6)
	ON_COMMAND(ID_RUN_TTNMENU7, OnRunTtnmenu7)
	ON_COMMAND(ID_RUN_TTNANS, OnRunTtnans)
	ON_COMMAND(ID_RUN_TTNANS_REC, OnRunTtnansRec)
	ON_COMMAND(ID_RUN_TTNMENU8, OnRunTtnmenu8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVPRDoc construction/destruction

CVPRDoc::CVPRDoc()
{
	// TODO: add one-time construction code here

}

CVPRDoc::~CVPRDoc()
{
}


BOOL CVPRDoc::OnNewDocument()
{

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	POSITION pos = GetFirstViewPosition();
	if(pos != NULL)
	 {
	 m_pView=((CVPRView*)(GetNextView(pos)));
     m_pView->ClearText(false);
	 }	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVPRDoc serialization


void CVPRDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
 	// TODO: add storing code here
    m_pView->SerializeRaw(ar);
 	}
	else
	{
 	// TODO: add loading code here
    m_pView->SerializeRaw(ar);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CVPRDoc diagnostics

#ifdef _DEBUG
void CVPRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVPRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVPRDoc commands

#include "ttnans\ttnmain.h"

void CVPRDoc::OnRunTtnmenu1() 
{
ttnans_main(m_pView,1);
}

void CVPRDoc::OnRunTtnmenu2() 
{
ttnans_main(m_pView,2);
}

void CVPRDoc::OnRunTtnmenu3() 
{
ttnans_main(m_pView,3);
}

void CVPRDoc::OnRunTtnmenu4() 
{
ttnans_main(m_pView,4);
}

void CVPRDoc::OnRunTtnmenu5() 
{
ttnans_main(m_pView,5);
}

void CVPRDoc::OnRunTtnmenu6() 
{
ttnans_main(m_pView,6);
}

void CVPRDoc::OnRunTtnmenu7() 
{
ttnans_main(m_pView,7);
}

void CVPRDoc::OnRunTtnmenu8() 
{
ttnans_main(m_pView,8);
}

void CVPRDoc::OnRunTtnans() 
{
ttnans_main(m_pView);	
}

void CVPRDoc::OnRunTtnansRec() 
{
ttnans_main(m_pView,-1,true);
}

