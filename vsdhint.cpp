// VSDhint.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDhint.h"
#include "VSDrqstr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CLTIMERVAL 30000
#define DEFAULTDELAY 0

#define LB_x		10
#define LB_y		10
#define LBdx	   -10
#define LBdy	   -30
#define LB_char_w	8

/////////////////////////////////////////////////////////////////////////////
// CVSDhint dialog

int CVSDhint::m_last_update_time_delay = DEFAULTDELAY;

CVSDhint::CVSDhint(CWnd* pParent /*=NULL*/)
	: CDialog(CVSDhint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSDhint)
	//}}AFX_DATA_INIT
m_list_limit = 0;
m_word_wrap = false;
}

CVSDhint::~CVSDhint()
{
KillTimer(2);
}

void CVSDhint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDhint)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSDhint, CDialog)
	//{{AFX_MSG_MAP(CVSDhint)
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDhint message handlers

BOOL CVSDhint::Create(CWnd* pParent)
{
if(CDialog::Create(IDD, pParent))
     {
     SetTimer(2,CLTIMERVAL,NULL);
     time( &m_last_update_time);
	 return TRUE;
     }
 return FALSE;
}

void CVSDhint::OnMiscWwrap() 
{
if(m_word_wrap)
 {
 MessageBox("Word wrap disabled","Hint Box Option",MB_OK);
 m_word_wrap=false;
 }
else
 {
 MessageBox("Word wrap enabled","Hint Box Option",MB_OK);
 m_word_wrap=true;
 }
}

void CVSDhint::OnMiscSelectfont() 
{
	// TODO: Add your control notification handler code here
	
LOGFONT lf;
lf.lfHeight = 8;
lf.lfWidth = 8;
lf.lfEscapement = 0;
lf.lfOrientation = 0;
lf.lfWeight = FW_BOLD;
lf.lfItalic = FALSE;
lf.lfUnderline = FALSE;
lf.lfStrikeOut = FALSE;
lf.lfCharSet = ANSI_CHARSET ;
lf.lfOutPrecision = OUT_CHARACTER_PRECIS;
lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;
lf.lfQuality = DEFAULT_QUALITY;
lf.lfPitchAndFamily = FIXED_PITCH;
//lf.lfFaceName = "Times New Roman";
CFontDialog cfd(&lf);
cfd.DoModal();
//CEdit & rCEdit=GetEditCtrl();
CFont font;
if(font.CreateFont( (int)lf.lfHeight, (int)lf.lfWidth, (int)lf.lfEscapement,
					(int)lf.lfOrientation, (int)lf.lfWeight, lf.lfItalic,
					lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision,
					lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily,
					lf.lfFaceName)) 
 SetFont(&font,TRUE);    
 m_list.SetFont(&font,TRUE);    
}

void CVSDhint::InsertText(CString text)
 {
 if(m_word_wrap) InsertTextWrap(text);
 else
  {
  KillTimer(2);
  m_list.AddString(text);
  RedrawWindow();
  SetTimer(2,CLTIMERVAL,NULL);
  time( &m_last_update_time);
  }
 }

void CVSDhint::InsertTextWrap(CString text)
 {
 CString buf;
 unsigned i,l,bl;

 KillTimer(2);
 
 l=text.GetLength();
 if(l<=m_list_limit)
  m_list.AddString(text);
 else
  {
  i = 0;
  while(i<l)
   { 
   buf = text.Mid(i,m_list_limit);
   bl= buf.GetLength();
// if((bl==m_list_limit)&&(!isspace(buf.GetAt(m_list_limit-1)))) buf = buf + "-";
   m_list.AddString(buf);
   i=i+m_list_limit;
   }
  }
 RedrawWindow();
 SetTimer(2,CLTIMERVAL,NULL);
 time( &m_last_update_time);
 }

void CVSDhint::Move(int x,int y,int dx,int dy)
 {
 MoveWindow( x, y, dx, dy, true );

 m_list.MoveWindow( x+LB_x, y+LB_y, dx+LBdx, dy+LBdy, true );
 m_list.CenterWindow();
 m_list.UpdateWindow();
 }

void CVSDhint::Move(int x,int y)
 {
 RECT Rect;
 GetWindowRect(&Rect);
 int nx=Rect.left+x;
 int ny=Rect.top+y;
 int ndx=Rect.right-Rect.left;
 int ndy=Rect.bottom-Rect.top;
 MoveWindow(nx,ny,ndx,ndy,true );

 m_list.MoveWindow( nx+LB_x, ny+LB_y, ndx+LBdx, ndy+LBdy, true );
 m_list.CenterWindow();
 m_list.UpdateWindow();
 }

void CVSDhint::ClearText(bool optaddline)
{
    time_t ltime;    

    time( &ltime );
    if ( (int)(ltime - m_last_update_time) >= m_last_update_time_delay )	// if some text was inserted during the past "m_last_update_time_delay" secs, dont clear.... 
     {
	 KillTimer(2);
	 m_list.ResetContent();
     SetTimer(2,CLTIMERVAL,NULL);
     time( &m_last_update_time);
     }
    else												// if no clear took place ...
     if(optaddline)										// and the optaddline is true ...
      {
      m_list.AddString(" ");
      }

}     

void CVSDhint::OnTimer(UINT nIDEvent) 
{
	ClearText();
}

void CVSDhint::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
  
    RECT Rect;
    GetWindowRect(&Rect);

    m_list.MoveWindow(Rect.left+LB_x, Rect.top+LB_y, Rect.right-Rect.left+LBdx, Rect.bottom-Rect.top+LBdy, true );
    m_list.CenterWindow();
    m_list.UpdateWindow();
    m_list_limit = cx / LB_char_w;
}

void CVSDhint::SetClearDelay() 
{
 int c;
 bool ok=false;
 CString buffer;
 CString outbuffer;

 outbuffer.Format("Enter delay time for Hint Pad clears (now %d sec(s))",m_last_update_time_delay);
 CVSDrqstr sd (outbuffer, &buffer);

 while(ok==false)
  {
  sd.DoModal();
  if(sscanf(buffer,"%d",&c)>0) ok=true;
  }
if(c<0) c=0;
if(c>1000) c=1000;
m_last_update_time_delay = c;
}