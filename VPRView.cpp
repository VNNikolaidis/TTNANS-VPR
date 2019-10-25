// VPRView.cpp : implementation of the CVPRViewclass
//

#include "stdafx.h"
#include "VPR.h"

#include "VPRDoc.h"
#include "VPRView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVPRView

IMPLEMENT_DYNCREATE(CVPRView, CEditView)

BEGIN_MESSAGE_MAP(CVPRView, CEditView)
	//{{AFX_MSG_MAP(CVPRView)
	ON_COMMAND(ID_MISC_CLEARSCREEN_ON, OnMiscClearscreenOn)
	ON_COMMAND(ID_MISC_CLEARSCREEN_OFF, OnMiscClearscreenOff)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_MISC_CLEARSCREEN_NOW, OnMiscClearscreenNow)
	ON_COMMAND(ID_MISC_TEXTOUTPUTON, OnMiscTextoutputon)
	ON_COMMAND(ID_MISC_TEXTOUTPUTOFF, OnMiscTextoutputoff)
	ON_COMMAND(ID_MISC_MODALDLGS, OnMiscModaldlgs)
	ON_UPDATE_COMMAND_UI(ID_MISC_MODALDLGS, OnUpdateMiscModaldlgs)
	ON_COMMAND(ID_MISC_SETSINWIN, OnMiscSetsinwin)
	ON_UPDATE_COMMAND_UI(ID_MISC_SETSINWIN, OnUpdateMiscSetsinwin)
	ON_UPDATE_COMMAND_UI(ID_MISC_CLEARSCREEN_ON, OnUpdateMiscClearscreenOn)
	ON_UPDATE_COMMAND_UI(ID_MISC_CLEARSCREEN_OFF, OnUpdateMiscClearscreenOff)
	ON_UPDATE_COMMAND_UI(ID_MISC_TEXTOUTPUTOFF, OnUpdateMiscTextoutputoff)
	ON_UPDATE_COMMAND_UI(ID_MISC_TEXTOUTPUTON, OnUpdateMiscTextoutputon)
	ON_COMMAND(ID_MISC_OLDFILEREQ, OnMiscOldfilereq)
	ON_UPDATE_COMMAND_UI(ID_MISC_OLDFILEREQ, OnUpdateMiscOldfilereq)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVPRViewconstruction/destruction

CVPRView::CVPRView()
{
m_cls_mode = false;
m_output_enabled = true;
m_modal_dialogs = true;
m_show_data_sets_in_window = true;
m_old_style_file_requesters = false;
m_charsinbuffer=0;
}

CVPRView::~CVPRView()
{
}

BOOL CVPRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
 BOOL	ret = CEditView::PreCreateWindow(cs);
 return ret;
}

/////////////////////////////////////////////////////////////////////////////
// CVPRViewdrawing

void CVPRView::OnDraw(CDC* pDC)
{
	CVPRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/*------------------------------------------------------------------------*/

int CVPRView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetTimer(VPR_TIMER_5_SEC,5000,NULL);

	return 0;
}

/*------------------------------------------------------------------------*/
// ok this does not help, but it was a try...

void CVPRView::OnTimer(UINT_PTR nIDEvent)
{
CEditView::OnTimer(nIDEvent);
if(nIDEvent!=VPR_TIMER_5_SEC) return;
KillTimer(VPR_TIMER_5_SEC);
// InsertText("\r\n**Timer**\r\n");
Update();
SetTimer(VPR_TIMER_5_SEC,5000,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CVPRViewprinting

BOOL CVPRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVPRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVPRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVPRViewdiagnostics

#ifdef _DEBUG
void CVPRView::AssertValid() const
{
	CEditView::AssertValid();
}

void CVPRView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CVPRDoc* CVPRView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVPRDoc)));
	return (CVPRDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVPRViewmessage handlers

void CVPRView::Update()
 {
 MSG message;
 // GetMessage(&message,NULL,0,0);
 while(PeekMessage(&message,NULL,0,0,PM_REMOVE)!=0)
  {
  TranslateMessage(&message);
  DispatchMessage(&message); 
  }
 }

void CVPRView::ClearText(bool check_cls_mode)
{
bool cls = true;

if(check_cls_mode)
 if(m_cls_mode)
  cls = true;
 else
  cls = false;

if(cls)
 {
 CEdit & rCEdit=GetEditCtrl();
 rCEdit.SetTabStops(8*(GetDialogBaseUnits()&0x00FF));    // /4);
 rCEdit.SetSel(0,-1);
 rCEdit.Clear();
 m_charsinbuffer = 0;
 }
// HintBoxClear();
((CMainFrame *)GetParent())->HintBoxClear(false);
}

void CVPRView::InsertText(CString cs)
{
if(m_output_enabled)
 {
 CEdit & rCEdit=GetEditCtrl();

 m_charsinbuffer+=(strlen(cs)*3);
 m_charsinbuffer++;
 if(m_charsinbuffer > rCEdit.GetLimitText())
   {
   ClearText(false);
   rCEdit.ReplaceSel("<View Buffer Full, CLS called.>\r\n");
   }
 rCEdit.ReplaceSel(cs);
 }
}

void CVPRView::OnMiscClearscreenOn() 
{
if(!m_cls_mode)
 {
 m_cls_mode = true;
 AfxMessageBox("Auto Clear Screen Mode is now On.",MB_OK|MB_ICONEXCLAMATION);	
 }
}

void CVPRView::OnMiscClearscreenOff() 
{
if(m_cls_mode)
 {
 m_cls_mode = false;	
 AfxMessageBox("Auto Clear Screen Mode is now Off.",MB_OK|MB_ICONEXCLAMATION);	
 }
}

void CVPRView::OnFilePrintPreview() 
{
AfxMessageBox("Not yet implemented.",MB_OK|MB_ICONEXCLAMATION);	
}

void CVPRView::OnMiscClearscreenNow() 
{
ClearText(false);	
}

void CVPRView::OnMiscTextoutputon() 
{
if(!m_output_enabled)
 {
 m_output_enabled = true;
 AfxMessageBox("Text output is now enabled.",MB_OK|MB_ICONEXCLAMATION);	
 }
}

void CVPRView::OnMiscTextoutputoff() 
{
if(m_output_enabled)
 {
 m_output_enabled = false;
 AfxMessageBox("Text output is now disabled.",MB_OK|MB_ICONEXCLAMATION);	
 }
}

void CVPRView::Enable() 
{
CEdit & rCEdit=GetEditCtrl();
//rCEdit.EnableWindow(TRUE);
rCEdit.SetReadOnly(FALSE);
RedrawWindow();
}

void CVPRView::Disable()
{
CEdit & rCEdit=GetEditCtrl();
//rCEdit.EnableWindow(FALSE);
rCEdit.SetReadOnly(TRUE);
RedrawWindow();
}

bool CVPRView::ModalDialogs()
{
return m_modal_dialogs;
};

bool CVPRView::ShowDataSetsInWindow()
{
return m_show_data_sets_in_window;
}

void CVPRView::OnMiscModaldlgs() 
{
if(m_modal_dialogs) m_modal_dialogs=false;
else m_modal_dialogs=true;	
}

void CVPRView::OnUpdateMiscModaldlgs(CCmdUI* pCmdUI) 
{
if(m_modal_dialogs)
 pCmdUI->SetCheck(1);
else 
 pCmdUI->SetCheck(0);
}

void CVPRView::OnMiscSetsinwin() 
{
if(m_show_data_sets_in_window) m_show_data_sets_in_window=false;
else m_show_data_sets_in_window=true;	
}

void CVPRView::OnUpdateMiscSetsinwin(CCmdUI* pCmdUI) 
{
if(m_show_data_sets_in_window)
 pCmdUI->SetCheck(1);
else 
 pCmdUI->SetCheck(0);
}

/*------------------------------------------------------------------------*/

void CVPRView::HintBoxClear()
{
((CMainFrame *)GetParent())->HintBoxClear();
}


void CVPRView::InsertHintText(CString text)
{
((CMainFrame *)GetParent())->InsertHintText(text);
}


/*------------------------------------------------------------------------*/

void CVPRView::OnUpdateMiscClearscreenOn(CCmdUI* pCmdUI) 
{
if(m_cls_mode)
 pCmdUI->SetCheck(1);
else 
 pCmdUI->SetCheck(0);
}

void CVPRView::OnUpdateMiscClearscreenOff(CCmdUI* pCmdUI) 
{
if(!m_cls_mode)
 pCmdUI->SetCheck(1);
else 
 pCmdUI->SetCheck(0);
}

void CVPRView::OnUpdateMiscTextoutputoff(CCmdUI* pCmdUI) 
{
if(!m_output_enabled)
 pCmdUI->SetCheck(1);
else 
 pCmdUI->SetCheck(0);
}

void CVPRView::OnUpdateMiscTextoutputon(CCmdUI* pCmdUI) 
{
if(m_output_enabled)
 pCmdUI->SetCheck(1);
else 
 pCmdUI->SetCheck(0);
}


/*------------------------------------------------------------------------*/

void CVPRView::OnMiscOldfilereq() 
{
if (m_old_style_file_requesters)
 m_old_style_file_requesters=false;
else
 m_old_style_file_requesters=true;
}

/*------------------------------------------------------------------------*/

void CVPRView::OnUpdateMiscOldfilereq(CCmdUI* pCmdUI) 
{
if(m_old_style_file_requesters)
 pCmdUI->SetCheck(1);
else 
 pCmdUI->SetCheck(0);
}

/*------------------------------------------------------------------------*/
