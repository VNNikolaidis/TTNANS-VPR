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


#ifndef TA_CONEC
#define TA_CONEC

#include "ttndef_o.h"

//class CTa_ans;

/*------------------------ Connections --------------------*/

class CTa_connection
{
private:
protected:

bool		m_valid;

unsigned	m_source_layer_id;
unsigned	m_source_pe_id;
unsigned	m_destination_layer_id;
unsigned	m_destination_pe_id;

DATA		m_input;					// gets this...
DATA		m_weight;					// multiplies it by this...
DATA		m_output;					// and outputs it here.

void PTR 	m_p_parent_layer;	 		// needs typecasting to appropriate CTa_layer<..> to be used
void PTR 	m_p_parent_ans;        		// needs typecasting to appropriate CTa_ans<..> to be used

public:

CTa_connection();
CTa_connection(void PTR p_parent_ans, void PTR p_parent_layer, unsigned source_layer_id, unsigned source_pe_id,unsigned destin_layer_id, unsigned destin_pe_id);
~CTa_connection();
bool Initialize(void PTR p_parent_ans, void PTR p_parent_layer, unsigned source_layer_id, unsigned source_pe_id,unsigned destin_layer_id, unsigned destin_pe_id);
bool operator == (CTa_connection REF c);
bool Equals (CTa_connection REF c);
bool IsValid();
void Show();
void ShowAll();
void Input (DATA value);
virtual bool Encode();
virtual bool Decode();
DATA Output();
unsigned Source_PE ();
unsigned Source_Layer ();
unsigned Destin_PE ();
unsigned Destin_Layer ();
};

#endif // TA_CONEC
