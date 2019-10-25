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


#ifndef TA_PE_CPP
#define TA_PE_CPP

#include "ttnui.h"

#include "ta_pe.h"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

CTa_pe::CTa_pe ()
 {
// mprintf("Constructing PE.\n");
 m_id = 0;
 m_valid= false;
 m_input = 0;
 m_activation = 0;
 m_output = 0;
 m_p_parent_layer = NULL;
 m_p_parent_ans = NULL;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

CTa_pe::~CTa_pe ()
 {
// mprintf("Destructing PE.\n");
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_pe::Initialize(void PTR p_parent_ans,void PTR p_parent_layer,unsigned id)
 {
 m_id=id;
 m_valid = true;
 m_p_parent_layer = p_parent_layer;
 m_p_parent_ans = p_parent_ans;
 return m_valid;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_pe::operator == (CTa_pe REF c)
 {
 IsValid();
 return (m_id == c.m_id);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_pe::IsValid()
{
if(NOT m_valid)
 mprintf("Warning: Uninitialized processing element (PE).\n");
return m_valid;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void CTa_pe::Show()
 {
 IsValid();
 mprintf("Processing Element (PE) id=%d:\n",m_id);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void CTa_pe::ShowAll()
 {
 if(IsValid())
  {
  Show();
  mprintf("Input contains %f.\n",(float)m_input);
  mprintf("Activation contains %f.\n",(float)m_activation);
  mprintf("Output contains %f.\n",(float)m_output);
  mprintf("<End-of-PE>.\n\n");
  }
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* Classic συνάρτηση άθροισης (summation)				   */

void CTa_pe::Input (DATA value)
 {
 m_input=m_input+value;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void CTa_pe::SetInput (DATA value)
 {
 m_input=value;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

bool CTa_pe:: Encode()
 {
 mprintf("Generic PE encode NOT implemented.\n");
 m_input = 0;
 return false;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* This just filters data though, from input to output,    */
/* and resets input to 0(since 'output' has been produced).*/
/* Overloading functions should use output to produce new  */
/* value and replace output afterwards.					   */

bool CTa_pe::Decode()
 {
 PassThru();
 return true;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* This just filters data though, from input to output,    */
/* and resets input to 0(since 'output' has been produced).*/

void CTa_pe::PassThru()
 {
 m_output=m_input;
 m_input = 0;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

DATA CTa_pe::Output ()
 {
 return m_output;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#endif // TA_PE_CPP

