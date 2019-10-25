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


#ifndef TA_CONEC_CPP
#define TA_CONEC_CPP


#include "ttnui.h"
#include "ta_conec.h"
#include "ta_ans.h"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

CTa_connection::CTa_connection()
 {
 m_valid=false;
 m_weight=0;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

CTa_connection::CTa_connection
				(void PTR p_parent_ans, void PTR p_parent_layer,
				 unsigned source_layer_id, unsigned source_pe_id,
				 unsigned destin_layer_id, unsigned destin_pe_id)
 {
 Initialize(p_parent_ans,p_parent_layer,source_layer_id,source_pe_id,destin_layer_id,destin_pe_id);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

CTa_connection::~CTa_connection()
 {
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_connection::Initialize
			   (void PTR p_parent_ans, void PTR p_parent_layer,
				unsigned source_layer_id, unsigned source_pe_id,
				unsigned destin_layer_id, unsigned destin_pe_id)
 {
 m_valid = true;
 m_source_layer_id	= source_layer_id;
 m_source_pe_id	= source_pe_id;
 m_destination_layer_id = destin_layer_id;
 m_destination_pe_id = destin_pe_id;
 m_input = 0;
 m_weight = 0;
 m_output = 0;
 m_p_parent_layer = p_parent_layer;
 m_p_parent_ans = p_parent_ans;
 return m_valid;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_connection::Equals (CTa_connection REF c)
 {
 IsValid();
 return   (	(m_valid == true ) AND
			(c.m_valid == true ) AND
            (m_source_layer_id == c.m_source_layer_id) AND
			(m_source_pe_id == c.m_source_pe_id) AND
			(m_destination_layer_id == c.m_destination_layer_id) AND
			(m_destination_pe_id == c.m_destination_pe_id) );
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// this is optional, compiler would generate it anyways... */

bool CTa_connection::operator == (CTa_connection REF c)
 {
 return Equals(c);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_connection::IsValid()
 {
 if(NOT (m_valid))
  mprintf("Warning: Uninitialized connection.\n");
 return m_valid;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void CTa_connection::Show()
 {
 IsValid();
 mprintf("\tConnection:\n");
 mprintf("\t> Initialization : ");
 if(m_valid) mprintf("OK.\n");
 else mprintf ("NOT INITIALIZED!\n");
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void CTa_connection::ShowAll()
 {
 if(IsValid())
  {
  Show();
  mprintf("\t> From :layer %d PE %d, To :layer %d PE %d.\n",m_source_layer_id,m_source_pe_id,m_destination_layer_id,m_destination_pe_id);
  mprintf("\t> Input: %f, Weight: %f, Output: %f \n",m_input,m_weight,m_output);
  mprintf("\t<End-of-connection>.\n\n");
  }
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_connection::Encode()
 {
 mprintf("Generic Connection encode NOT implemented.\n");
 return false;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_connection::Decode()
 {
 if(IsValid()) m_output = m_input * m_weight;
 return true;  
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

DATA CTa_connection::Output()
 {
 return m_output;  
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void CTa_connection::Input(DATA value)
 {
 m_input = value;  
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

unsigned CTa_connection::Source_PE ()
 {
 return m_source_pe_id;
 }

unsigned CTa_connection::Source_Layer ()
 {
 return m_source_layer_id;
 }

unsigned CTa_connection::Destin_PE ()
 {
 return m_destination_pe_id;
 }

unsigned CTa_connection::Destin_Layer ()
 {
 return m_destination_layer_id; 
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#endif // TA_CONEC_CPP

