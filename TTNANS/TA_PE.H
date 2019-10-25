/**************************************************************

Class-TTN-ANS (CTa_xxx) is a C++ object oriented version of
the C code used to emulate ANSs, Layers PEs, and Connections
within the TTNANS engine.

This code is oriented towards flexibility, not speed.
If you want speed, use the TTNANS C ANS emulation library, which
goes along the same principles. This code makes minimal use of
pointers (attempt for Java-like code).

This is a complete library, not a wrapper class!

Copyright (c) 1995-98 Vasilis N. Nikolaidis
***************************************************************/


#ifndef TA_PE
#define TA_PE

#include "ttndef_o.h"

/*---------------------- Processing Elements --------------*/

class CTa_pe
{
private:

protected:

unsigned	  	m_id;
bool		 	m_valid;
DATA			m_input;
DATA			m_activation;
DATA			m_output;
void PTR		m_p_parent_layer;	   // needs typecasting to CTa_layer<..> to be used
void PTR		m_p_parent_ans;        // needs typecasting to CTa_ans<..> to be used

public:

CTa_pe  ();
~CTa_pe ();
bool Initialize(void PTR p_parent_ans,void PTR p_parent_layer,unsigned id);
bool operator == (CTa_pe REF c);
bool IsValid();
void Show();
void ShowAll();
void Input (DATA value);
void SetInput (DATA value);
virtual bool Encode();
virtual bool Decode();
virtual void PassThru ();
DATA Output ();
};

#endif // TA_PE
