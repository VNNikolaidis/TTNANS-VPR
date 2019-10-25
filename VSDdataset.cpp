// VSDdataset.cpp : implementation file
//

#include "stdafx.h"
#include "VPR.h"
#include "VSDdataset.h"

#include "ttnans\ttnprepr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSDdataset dialog


CVSDdataset::CVSDdataset(DATA ** data, unsigned rows, unsigned cols, char * title, CWnd* pParent /* = NULL */)
	: CDialog(CVSDdataset::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSDdataset)
	m_cols_out = _T("");
	m_rows_out = _T("");
	//}}AFX_DATA_INIT

m_data=data;
m_rows=rows;
m_cols=cols;
m_title=title;
}


void CVSDdataset::DoDataExchange(CDataExchange* pDX)
{
	m_cols_out.Format("%d",m_cols);
	m_rows_out.Format("%d",m_rows);

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSDdataset)
	DDX_Control(pDX, IDC_DATASET_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_flexgrid);
	DDX_Text(pDX, IDC_EDIT_COLS, m_cols_out);
	DDX_Text(pDX, IDC_EDIT_ROWS, m_rows_out);
	//}}AFX_DATA_MAP

	unsigned r,c;
    char buf [100];
    
    m_progress.SetPos(0);

	m_flexgrid.SetCols(max(m_cols+1,10));
	m_flexgrid.SetRows(max(m_rows+1,30));

    sprintf(buf,":%dx%d",m_rows,m_cols);
    m_flexgrid.SetTextMatrix(0, 0, buf);
     
    for(c=1;c<m_cols+1;c++)
     {
     sprintf(buf,"Col:%d",c-1);
     m_flexgrid.SetTextMatrix(0, c, buf);
     }

    for(r=1;r<m_rows+1;r++)
     {
     sprintf(buf,"Row:%d",r-1);
     m_flexgrid.SetTextMatrix(r, 0, buf);
     }
    
	for(r=1;r<m_rows+1;r++)
     {
     m_progress.SetPos(r*100/m_rows);
     for(c=1;c<m_cols+1;c++)
      {
      sprintf(buf,DATAFORMAT,m_data[r-1][c-1]);
	  m_flexgrid.SetTextMatrix(r, c, buf);
      }
     }

	SetWindowText(m_title);
}


BEGIN_MESSAGE_MAP(CVSDdataset, CDialog)
	//{{AFX_MSG_MAP(CVSDdataset)
	ON_BN_CLICKED(ID_DATASET_SCALE, OnDatasetScale)
	ON_BN_CLICKED(ID_DATASET_SAVE, OnDatasetSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSDdataset message handlers


void CVSDdataset::OnDatasetScale() 
{
char local_title [100];

m_progress.SetPos(0);

char * patch;
patch = strstr(m_title,("Set"));
if(patch==NULL)
 patch = strstr(m_title,("set"));
if(patch!=NULL)
 *patch = '\0';

strncpy(local_title,m_title,80);
strcat (local_title," (displayed)");
preprocess(-1,local_title,m_data,m_rows,m_cols);
UpdateData();
}

#include "ttnans\tmatrix.h"

void CVSDdataset::OnDatasetSave() 
{
CTmatrix <DATA> temp (m_data,m_rows,m_cols,m_title,false);
temp.save();
}
