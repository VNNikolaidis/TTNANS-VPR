// This code is part of VPR
// Copyright (c) 1997 Vasilios N. Nikolaidis


#ifndef TMATRIX_H
#define TMATRIX_H

#include <stdlib.h>
#include <string.h>

#include "ttndef.h"
#include "ttndef_o.h"
#include "ttndef_s.h"
#include "ttnmemor.h"
#include "ttnerror.h"
#include "ttnui.h"
#include "ttnmain.h"
#include "ttnfile.h"
#include "ttnfname.h"

#include "ttneigen.h"

template <class D> class CTvector;

// class CTmatrix (2-D Array)

template <class D>
class CTmatrix
 {
 private:

  char			m_title [100];
  char			m_filename [FILENAMELENGTH];
  D **			m_storage;
  bool			m_mute;			// true if we don't want any output during operations.

 bool initialize (unsigned rows_in, unsigned cols_in, D initial_value_in, char * title_in, bool mute_in);
 bool initialize (D ** sourcecopy, unsigned rows_in, unsigned cols_in, char * title_in, bool mute_in);
 void discard_data ();
 CTmatrix<D> operation_with_number (D f,unsigned op);

 protected:

 unsigned int	m_rows;
 unsigned int	m_cols;
 D				m_junk;

 void quicksort_rows_split(unsigned keycol, int first, int last, int REF splitpoint);
 void quicksort_rows_go   (unsigned keycol, int first, int last);
 void quicksort_cols_split(unsigned keyrow, int first, int last, int REF splitpoint);
 void quicksort_cols_go   (unsigned keyrow, int first, int last);

 D ** matrix_storage_direct();
 void CTmatrix_RESET();

 public:
// CTmatrix();
 CTmatrix(unsigned rows_in, unsigned cols_in, char * title_in, bool mute_in = false);
 CTmatrix(unsigned rows_in, unsigned cols_in, D initial_value_in, char * title_in, bool mute_in = false);
 CTmatrix(D ** initial, unsigned rows_in, unsigned cols_in, char * title_in, bool mute_in = false);
 CTmatrix(CTmatrix<D> & matrix_in);
~CTmatrix();
 D & at(unsigned row, unsigned col);
 D   at(unsigned row, unsigned col) const;
 void show();
 inline unsigned int rows () const {return m_rows;}
 inline unsigned int cols () const {return m_cols;}
 D * row (unsigned int row); 
 bool is_mute() {return m_mute;}
 char * title() {return m_title;}
 bool save(char * fnamein = NULL);
 bool load(char * fnamein = NULL, bool always = false);
 void quicksort_rows(unsigned keycol_in);
 void quicksort_cols(unsigned keyrow_in);
 void interchange_rows(unsigned r1, unsigned r2);
 void interchange_cols(unsigned c1, unsigned c2);
 void reset (D value);
 bool is_symmetric();
 bool eigen(CTvector <float> REF eigenvalues, CTmatrix <float> REF eigenvectors);
 bool transpose();
 CTmatrix<D> operator * (CTmatrix<D> & f);
 CTmatrix<D> operator + (D f);
 CTmatrix<D> operator - (D f);
 CTmatrix<D> operator * (D f);
 CTmatrix<D> operator / (D f);
 };


// implementation

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
bool CTmatrix<D>::initialize(unsigned rows_in, unsigned cols_in, D initial_value_in, char * title_in, bool mute_in)
 {
 unsigned r,c;
 bool ok = true;

#ifdef _DEBUG
 m_mute=false;
#else
 m_mute = mute_in;
#endif

 if(m_storage != NULL)
  mprintf("CTmatrix: Warning, initializing an non empty matrix (%s) !!!\n",m_title);

 if(strcmp(title_in,"")==0)
  strcpy(m_title,"Untitled Matrix");
 else
  strcpy(m_title,title_in);
 strcpy(m_filename,"No Filename");

 if(!m_mute)
  {
  double dispKsize = ((float)rows_in*cols_in*sizeof(D))/1024; 
  mprintf("(Allocating %s: %d x %d (%.2fKb, %.2fMb, %gGb, or %gTb).)\n",m_title,rows_in,cols_in,dispKsize,dispKsize/(1024),dispKsize/(1024*1024),dispKsize/(1024*1024*1024));
  }

 m_storage = (D **) MMalloc (rows_in * sizeof(D *));

 if(m_storage==NULL) ok=false;

 if(ok)
  {
  for (r=0;r<rows_in;r++)
   {
   m_storage[r]=(D *)MMalloc(cols_in * sizeof(D));
   if(m_storage[r]==NULL) ok=false;

   if(ok)
	for(c=0;c<cols_in;c++)
	 m_storage[r][c]=initial_value_in;
   }
  m_rows=rows_in;
  m_cols=cols_in;
  }
 else
  {
  m_rows=0;
  m_cols=0;
  }
 if(ok!=true) mprintf("Warning: Matrix initialization of %s failed (not enough memory?).\n",title_in);
 return ok;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
bool CTmatrix<D>::initialize (D ** sourcecopy, unsigned rows_in, unsigned cols_in, char * title_in, bool mute_in)
 {
 unsigned r,c;
 bool ok = true;

#ifdef _DEBUG
 m_mute=false;
#else
 m_mute = mute_in;
#endif

 if(m_storage != NULL)
  mprintf("CTmatrix: Warning, initializing an non empty matrix (%s) !!!\n",m_title);

 if(strcmp(title_in,"")==0)
  strcpy(m_title,"Untitled Matrix");
 else
  strcpy(m_title,title_in);
 strcpy(m_filename,"No Filename");

 if(!m_mute)
  mprintf("(Allocating %s: %d x %d (%dK).)\n",m_title,rows_in,cols_in,(rows_in*cols_in*(int)sizeof(D))/1024);

 m_storage = (D **) MMalloc (rows_in * sizeof(D *));

 if(m_storage==NULL) ok=false;

 if(ok)
  {
  for (r=0;r<rows_in;r++)
   {
   m_storage[r]=(D *)MMalloc(cols_in * sizeof(D));
   if(m_storage[r]==NULL) ok=false;

   if(ok)
	for(c=0;c<cols_in;c++)
	 m_storage[r][c]=sourcecopy[r][c];
   }
  m_rows=rows_in;
  m_cols=cols_in;
  }
 else
  {
  m_rows=0;
  m_cols=0;
  }
 if(ok!=true) mprintf("Warning: Matrix initialization of %s failed (not enough memory?).\n",title_in);
 return ok;
 }


/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
D ** CTmatrix<D>::matrix_storage_direct()
 {
 return m_storage;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
void CTmatrix<D>::discard_data ()
 {
 unsigned r;

 if(!m_mute) mprintf("(Freeing %s: %d x %d (%dK).)\n",m_title,m_rows,m_cols,(m_rows*m_cols*(int)sizeof(D))/1024);

 for (r=0;r<m_rows;r++) MFree(m_storage[r]);
 MFree(m_storage);
 m_storage=NULL;
 m_rows=0;
 m_cols=0;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

/* Only constructors should call this. DO NOT USE THIS DIRECTLY !!!!!!!  */

template <class D>
void CTmatrix<D>::CTmatrix_RESET()
 {
 strcpy (m_title,"Null Data Set");
 strcpy (m_filename,"No File Name");
 m_storage = NULL;
 m_junk = (D) 0;
 m_rows = 0;
 m_cols = 0;
 m_mute = false;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
bool CTmatrix<D>::load(char * fnamein, bool always)
 {
 char fname [FILENAMELENGTH];
 char buffer[130];
 FHANDLE f;
 unsigned i,j,r,c;
 int r1,c1;
 bool load = always;
 bool mute = m_mute;

 if(NOT always)
  {
  sprintf(buffer,"Matrix %s is not empty, load anyways?",m_title);
  if(m_storage NEQL NULL) load = mrequest_yn(buffer);
  }

 if(load)
  {
  if (fnamein EQL NULL)
   GetFilename("Select filename.",fname,"*.*",true);
  else
   strcpy(fname,fnamein);

  discard_data();
  GetDataFileDims(fname,&r1,&c1);
  r=(unsigned)r1;
  c=(unsigned)c1;

  f=OpenInFile(fname);

  if(f!=NULL)
   {
   if(initialize(r,c,0,"",mute))
    {
    for(i=0;i<m_rows;i++)
    for(j=0;j<m_cols;j++)
     m_storage[i][j]=ReadDATA(f);
    }
   CloseFile(f);
   return true;
   }
  }
 return false;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
bool CTmatrix<D>::save(char * fnamein)
 {
 char fname [FILENAMELENGTH];
 char buffer[130];
 FHANDLE f;
 unsigned i,j;

 if(m_storage NEQL NULL)
  {
  sprintf(buffer,"Save %s ?",m_title);
  if(mrequest_yn(buffer))
   {
   if (fnamein EQL NULL)
   GetFilename("Select filename.",fname,"*.*",true);
   else
   strcpy(fname,fnamein);

   f=OpenOutFile(fname);

   if(f!=NULL)
    {
    WriteString(f,m_title);
    WriteString(f,"\n");
    for(i=0;i<m_rows;i++)
     {
     for(j=0;j<m_cols;j++)
      WriteDATA(f,m_storage[i][j]);
     WriteString(f,"\n");
     }
    CloseFile(f);
    strcpy(m_filename,fname);
    return true;
    }
   }
  }
 return false;
 }


/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D>::CTmatrix(unsigned rows_in, unsigned cols_in, char * title_in, bool mute_in)
 {
 CTmatrix_RESET();
 initialize(rows_in,cols_in,0,title_in,mute_in);
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D>::CTmatrix(unsigned rows_in, unsigned cols_in, D initial_value_in, char * title_in, bool mute_in)
{
CTmatrix_RESET();
initialize(rows_in,cols_in,initial_value_in,title_in,mute_in);
}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D>::CTmatrix(D ** initial, unsigned rows_in, unsigned cols_in, char * title_in, bool mute_in)
{
CTmatrix_RESET();
initialize(initial,rows_in,cols_in,title_in,mute_in);
}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D>::CTmatrix(CTmatrix<D> & matrix_in)
{
char temp_title [100];
bool ok;
unsigned r,c;
CTmatrix_RESET();
strcpy(temp_title,"Copy of ");
strcat(temp_title,matrix_in.title());
if(matrix_in.is_mute()==false) mprintf("Matrix Copy Constructor Called.\n");
ok=initialize(matrix_in.rows(),matrix_in.cols(),0,temp_title,matrix_in.is_mute());
if(ok)
 for(r=0;r<m_rows;r++)
  for(c=0;c<m_cols;c++)
	at(r,c)=matrix_in.at(r,c);
}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D>::~CTmatrix()
 {
 discard_data();
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
D * CTmatrix<D>::row (unsigned int row)
 {
 if((m_storage!=NULL)&&(row<m_rows))
  return m_storage[row];
 runerror(DATASTERR,"Cannot access row");
 return & m_junk;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
D & CTmatrix<D>::at(unsigned row, unsigned col)
 {
 if((m_storage!=NULL)&&(row<m_rows)&&(col<m_cols))
  if(m_storage[row]!=NULL)
   return m_storage[row][col];

 // throw;

 #ifdef _DEBUG
 mprintf("CTmatrix error: %s (%dx%d) cannot access element at %d,%d.\n",
 m_title,m_rows,m_cols,row,col);
 #endif

 runerror(DATASTERR,"Cannot access element");
 return m_junk;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
D CTmatrix<D>::at(unsigned row, unsigned col) const
 {
 if((m_storage!=NULL)&&(row<m_rows)&&(col<m_cols))
  if(m_storage[row]!=NULL)
   return m_storage[row][col];

 // throw;

 #ifdef _DEBUG
 mprintf("CTmatrix error: %s (%dx%d) cannot access element at %d,%d.\n",
 m_title,m_rows,m_cols,row,col);
 #endif

 runerror(DATASTERR,"Cannot access element");
 return m_junk;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
extern void Show2dDataSet(DATA ** Set, int rows, int cols, char * title);
extern DATA ** MMalloc2dDATA (int r, int c);
extern void MFree2dDATA (DATA ** dp, int r);

template <class D>
void CTmatrix<D>::show ()
 {
 char t [110];
 unsigned r,c;
 DATA ** d;

 strcpy(t,"Show ");
 strcat(t,m_title);
 strcat(t,"?");

 if(mrequest_yn(t))
  {
  d=MMalloc2dDATA (m_rows,m_cols);
  if(TGBL no_error)
   {
   for(r=0;r<m_rows;r++)
    for(c=0;c<m_cols;c++)
     d[r][c] = (DATA)(at(r,c));
   
   mprintf("\n\n(%s (file:%s) BEGIN.)\n\n",m_title,m_filename);
   Show2dDataSet(d, m_rows, m_cols,m_title);
   mprintf("\n(%s (file:%s) END.)\n\n",m_title,m_filename);
   }
  MFree2dDATA (d, m_rows);
  }
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
void CTmatrix<D>::interchange_rows(unsigned r1, unsigned r2)
 {
 if((r1<m_rows)AND(r2<m_rows))
  {
  unsigned c;
  D * temp = (D *) MMalloc(m_cols*sizeof(D));
  for(c=0;c<m_cols;c++) temp[c]=at(r1,c);
  for(c=0;c<m_cols;c++) at(r1,c)=at(r2,c);
  for(c=0;c<m_cols;c++) at(r2,c)=temp[c];
  MFree(temp);
  }

 else
  runerror(DATASTERR,"Cannot interchange rows, invalid row numbers");
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>  
void CTmatrix<D>::quicksort_rows_split(unsigned keycol, int first, int last, int REF splitpoint)
 {
 D x;
 int unknown;

 x = at(first,keycol);
 splitpoint = first;

 for(unknown=first+1;unknown<=last;unknown++)
  {
  if(at(unknown,keycol)<x)
   {
   splitpoint = splitpoint + 1;
   interchange_rows(splitpoint,unknown);
   }
  }
 interchange_rows(first,splitpoint);
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
void CTmatrix<D>::quicksort_rows_go(unsigned keycol, int first, int last)
 {
 mtick((int)m_junk,m_rows);							// worst case n-1 calls.
 m_junk++;

 int splitpoint;

 if(TGBL no_error)
 if(first<last)
  {
  quicksort_rows_split(keycol, first, last, splitpoint);
  quicksort_rows_go	  (keycol, first, splitpoint-1);
  quicksort_rows_go	  (keycol, splitpoint+1, last);
  }
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
void CTmatrix<D>::quicksort_rows(unsigned keycol_in)
 {
 mhintclear();
 mhintf(true,"Matrix QuickSort Algorithm (non-increasing order) or rows:\n");
 mhintf(true,"see Computer Algorithms, by Sara Baase, 2nd Edition, p.53.\n");

 unsigned keycol=keycol_in;
 int temp;
 while(keycol>=m_cols)
  {
  temp = mrequest_int("Select Sort-key column (negative to skip sorting)");
  if(temp < 0) return;
  keycol=(unsigned) temp;
  }
 mprintf("Sorting matrix rows (on key column %u)...\n",keycol);
 mstarttick("Sorting...");
 m_junk=(D)0;
 quicksort_rows_go(keycol,0,m_rows-1);
 mendtick();
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
void CTmatrix<D>::interchange_cols(unsigned c1, unsigned c2)
 {
 if((c1<m_cols)AND(c2<m_cols))
  {
  unsigned c;
  D * temp = (D *) MMalloc(m_rows*sizeof(D));
  for(c=0;c<m_rows;c++) temp[c]=at(c,c1);
  for(c=0;c<m_rows;c++) at(c,c1)=at(c,c2);
  for(c=0;c<m_rows;c++) at(c,c2)=temp[c];
  MFree(temp);
  }

 else
  runerror(DATASTERR,"Cannot interchange columns, invalid column numbers");
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
template <class D>
void CTmatrix<D>::quicksort_cols_split(unsigned keyrow, int first, int last, int REF splitpoint)
 {
 D x;
 int unknown;

 x = at(keyrow,first);
 splitpoint = first;

 for(unknown=first+1;unknown<=last;unknown++)
  {
  if(at(keyrow,unknown)<x)
   {
   splitpoint = splitpoint + 1;
   interchange_cols(splitpoint,unknown);
   }
  }
 interchange_cols(first,splitpoint);
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>  
void CTmatrix<D>::quicksort_cols_go(unsigned keyrow, int first, int last)
 {
 mtick((int)m_junk,m_cols);							// worst case n-1 calls.
 m_junk++;

 int splitpoint;

 if(TGBL no_error)
 if(first<last)
  {
  quicksort_cols_split(keyrow, first, last, splitpoint);
  quicksort_cols_go	  (keyrow, first, splitpoint-1);
  quicksort_cols_go	  (keyrow, splitpoint+1, last);
  }
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>  
void CTmatrix<D>::quicksort_cols(unsigned keyrow_in)
 {
 mhintclear();
 mhintf(true,"Matrix QuickSort Algorithm (non-increasing order) on columns:\n");
 mhintf(true,"see Computer Algorithms, by Sara Baase, 2nd Edition, p.53.\n");

 unsigned keyrow=keyrow_in;
 int temp;
 while(keyrow>=m_rows)
  {
  temp = mrequest_int("Select Sort-key row (negative to skip sorting)");
  if(temp < 0) return;
  keyrow=(unsigned) temp;
  }
 mprintf("Sorting matrix columns (on key row %u)...\n",keyrow);
 mstarttick("Sorting...");
 m_junk=(D)0;
 quicksort_cols_go(keyrow,0,m_cols-1);
 mendtick();
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>  
void CTmatrix<D>::reset (D value)
 {
 for(unsigned i=0;i<m_rows;i++)
 for(unsigned j=0;j<m_cols;j++)
  m_storage[i][j]=value;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
bool CTmatrix<D>::is_symmetric()
 {
 unsigned r,c;
 bool chk,ret=true;

 if(m_rows != m_cols) return false;

 for(r=0;r<m_rows;r++)
  for(c=0;c<m_cols;c++)
   {
   chk=(at(r,c)==at(c,r));

#ifdef _DEBUG
   if(NOT chk)
    mprintf("Matrix is not symmetric (element %d,%d (%f) not equal to element %d,%d (%f)).\n",r,c,at(r,c),c,r,at(c,r));
#endif

   ret=ret AND chk;
   }
 return ret;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
bool CTmatrix<D>::eigen(CTvector <float> REF eigenvalues, CTmatrix <float> REF eigenvectors)
{
unsigned r,c;
CTmatrix<float> fmatrix(m_cols,m_cols,0.0,"temporary float matrix",true);

mprintf("Determining eigenvalues / normalized eigenvectors...\n");

if((eigenvalues.cols()  != m_cols) OR
   (eigenvectors.rows() != m_cols) OR
   (eigenvectors.cols() != m_cols))
 {
 mprintf("Error: Bad sizes for return structures (matrix.eigen() returns false).\n");
 return false;
 }

if(NOT is_symmetric())
 {
 mprintf("Error: Martix not n x n and symmetric (matrix.eigen() returns false).\n");
 return false;
 }

for(r=0;r<m_cols;r++)
 {
 eigenvalues.at(r)=-999;
 for(c=0;c<m_cols;c++)
  fmatrix.at(r,c)=(float)at(r,c);
 }

sorted_eigen(fmatrix,eigenvectors,eigenvalues,m_cols);

return true;
}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
bool CTmatrix<D>::transpose()
{
bool ok=true;
D ** new_storage;
unsigned int r,c;
unsigned int new_rows=m_cols;
unsigned int new_cols=m_rows;

new_storage =(D **) MMalloc (new_rows * sizeof(D *));
if(new_storage==NULL)ok=false;

if(ok)
 {
 for (r=0;r<new_rows;r++)
  {
  new_storage[r]=(D *)MMalloc(new_cols * sizeof(D));
  if(new_storage[r]==NULL) ok=false;

  if(ok)
   for(c=0;c<new_cols;c++)
	new_storage[r][c]=at(c,r);
  }
 }

if(ok)
 {
 discard_data();
 m_rows=new_rows;
 m_cols=new_cols;
 m_storage = new_storage;
 strcat(m_title," transposed");
 }
else
 {
 if(!m_mute) mprintf("Error: Can't traspose matrix (not enough memory).\n");
 for (r=0;r<new_rows;r++) MFree(new_storage[r]);
 MFree(new_storage);
 }
return ok;
}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>                             
CTmatrix<D> CTmatrix<D>::operator * (CTmatrix<D> & m)
 {

#ifdef _DEBUG
 mprintf("Multipling %s with %s (%d x %d) * (%d x %d).\n",m_title,m.title(),m_rows,m_cols,m.rows(),m.cols());
#endif

 unsigned res_rows = m_rows;
 unsigned res_cols = m.cols();
 unsigned r,c,rc;
 D buf;

 CTmatrix<D> res (res_rows, res_cols, "Matrix multiplication result",true);

 if(m_cols==m.rows())
  {
  for(r=0;r<res.rows();r++)
  for(c=0;c<res.cols();c++)
   {
   buf=0;
   for(rc=0;rc<m_cols;rc++)
 	buf=buf+( at(r,rc) * m.at(rc,c) );
   res.at(r,c)=buf;
   }
  }
 else
  {
  runerror(ARITHMERR,"Matrix Multiplication, invalid sizes");
  }
 return res;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

#define M_ADD 1
#define M_SUB 2
#define M_MLT 3
#define M_DIV 4

template <class D>
CTmatrix<D> CTmatrix<D>::operation_with_number (D f,unsigned op)
 {
 unsigned res_rows = m_rows;
 unsigned res_cols = m_cols;
 unsigned r,c;

 CTmatrix<D> res (res_rows, res_cols, "Matrix Number operation result",true);

 for(r=0;r<res_rows;r++)
  for(c=0;c<res_cols;c++)
   switch(op)
	{
	case M_ADD:  res.at(r,c)=at(r,c)+f; break;
	case M_SUB:  res.at(r,c)=at(r,c)-f; break;
	case M_MLT:  res.at(r,c)=at(r,c)*f; break;
	case M_DIV:  res.at(r,c)=at(r,c)/f; break;
	default:     mprintf("Unknown Operation!\n"); break;
	}
 return res;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D> CTmatrix<D>::operator + (D f)
{return operation_with_number(f,M_ADD);}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D> CTmatrix<D>::operator - (D f)
{return operation_with_number(f,M_SUB);}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D> CTmatrix<D>::operator * (D f)
{return operation_with_number(f,M_MLT);}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D>
CTmatrix<D> CTmatrix<D>::operator / (D f)
{return operation_with_number(f,M_DIV);}


/*-----------------------------------------------------------------------*/
/* Vector Class															 */
/*-----------------------------------------------------------------------*/

template <class D>
class CTvector : public CTmatrix <D>
{
public:
CTvector(unsigned cols_in, D initial_value_in);
CTvector(D * initial_in,unsigned cols_in);
D & at(unsigned col);
D & operator [](unsigned col);
D operator [] (unsigned col) const;
void show (char * separator = NULL) const;
};

template <class D>
CTvector<D>::CTvector(unsigned cols_in, D initial_value_in)
:CTmatrix<D>(1, cols_in, initial_value_in, "Vector", true)
{}

template <class D>
CTvector<D>::CTvector(D * initial_in,unsigned cols_in)
:CTmatrix<D>(1, cols_in, 0, "Vector", true)
{
for (unsigned i=0;i<cols_in;i++)
 at(i)=initial_in[i];
}

template <class D>
D & CTvector<D>::at(unsigned col)
{return CTmatrix<D>::at(0,col);}

template <class D>
D & CTvector<D>::operator[](unsigned col)
{return CTmatrix<D>::at(0,col);}

template <class D>
D CTvector<D>::operator [](unsigned col) const
{
D r = CTmatrix<D>::at(0,col);
return r;
}

template <class D>
void CTvector<D>::show(char * separator) const
{
DATA d;

mprintf(" [");
if(separator == NULL) mprintf(" ");
else mprintf("%s",separator);

for(unsigned i=0;i<cols();i++)
 {
 d = (DATA)CTmatrix<D>::at(0,i);
 if(d ==  LARGEDATA) mprintf("  (+oo) ");
 else
 if(d == -LARGEDATA) mprintf("  (-oo) ");
 else
 mprintf("%f",(float)d);
 if(separator == NULL) mprintf(" ");
 else mprintf("%s",separator);
 }

mprintf("]");
}

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

// other definitions

#define CTdataset CTmatrix<DATA>

#endif
