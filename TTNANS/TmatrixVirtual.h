#pragma once
#include "tmatrix.h"


template <class D, DATA (*p_AccessFunction)(unsigned,unsigned)>
class CTmatrixVirtual :
	public CTmatrix<D>
{
private:

	unsigned m_rows_virtual_limit;
	unsigned m_cols_virtual_limit;
	DATA (* mp_AccessFunction)(unsigned row, unsigned col);

protected:
 
	void CTmatrix_RESET();

public:

	CTmatrixVirtual(unsigned rows_in, unsigned cols_in, char * title_in);
	~CTmatrixVirtual(void);
	 D & at(unsigned row, unsigned col);
	 D   at(unsigned row, unsigned col) const;

};


// implementation

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D, DATA (*p_AccessFunction)(unsigned,unsigned)>
CTmatrixVirtual<D,p_AccessFunction>::CTmatrixVirtual(unsigned rows_in, unsigned cols_in, char * title_in)
:CTmatrix<D>(0,0,title_in,false)
 {
 CTmatrix_RESET();
 m_rows = rows_in;
 m_rows_virtual_limit = rows_in;
 m_cols = cols_in;
 m_cols_virtual_limit = cols_in;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D, DATA (*p_AccessFunction)(unsigned,unsigned)>
CTmatrixVirtual<D,p_AccessFunction>::~CTmatrixVirtual()
 {
 CTmatrix_RESET();
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D, DATA (*p_AccessFunction)(unsigned,unsigned)>
void CTmatrixVirtual<D,p_AccessFunction>::CTmatrix_RESET()
 {
 CTmatrix::CTmatrix_RESET();
 m_rows_virtual_limit = 0;
 m_cols_virtual_limit = 0;
 mp_AccessFunction = NULL;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D, DATA (*p_AccessFunction)(unsigned,unsigned)>
D & CTmatrixVirtual<D,p_AccessFunction>::at(unsigned row, unsigned col)
 {
 runerror(DATASTERR,"Cannot access element - virtual matrix is read only");
 return m_junk;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

template <class D, DATA (*p_AccessFunction)(unsigned,unsigned)>
D CTmatrixVirtual<D,p_AccessFunction>::at(unsigned row, unsigned col) const
 {
 if((mp_AccessFunction!=NULL)&&(row<m_rows_virtual_limit)&&(col<m_cols_virtual_limit))
   return (*mp_AccessFunction)(row,col);

 runerror(DATASTERR,"Cannot access element");
 return m_junk;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
