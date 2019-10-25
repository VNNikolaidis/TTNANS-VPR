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

#ifndef TA_LAYER	
#define TA_LAYER

#include "tmatrix.h"

#include "ta_pe.h"
#include "ta_conec.h"

#include "ta_store.h"

template<class CONNECTION_TYPE, class PE_TYPE> class CTa_ans;

/*------------------------ Layers -------------------------*/

template<class CONNECTION_TYPE, class PE_TYPE>
class CTa_layer
{
private:

CTa_ans <CONNECTION_TYPE,PE_TYPE>		PTR	m_p_parent_ans;
unsigned						   		m_id;
bool									m_valid;
CTa_vector_storage  <PE_TYPE>			m_pes;
CTa_stack_storage   <CONNECTION_TYPE>	m_connections;

protected:

public:

CTa_layer  ();
~CTa_layer ();
bool IsConnected(CONNECTION_TYPE REF connection);
bool Initialize(CTa_ans <CONNECTION_TYPE,PE_TYPE> PTR p_parent_ans, unsigned id, unsigned number_of_PEs);
bool operator == (CTa_layer REF c);
bool Has_A_PE (unsigned pe_id);
bool Has_A_Connection (unsigned connection_id);
unsigned Dimention ();
unsigned NumberOfConnections ();
bool Connect(unsigned source_pe_id,unsigned destin_layer_id, unsigned destin_pe_id);
bool IsValid();
void Show();
void ShowAll();
PE_TYPE REF PE (unsigned pe_id);
CONNECTION_TYPE REF Connection (unsigned connection_id);
void Input (const CTvector <DATA> REF input,bool replace_old_input=true);
void Input(DATA input,bool replace_old_input=true);
void OutputToInput (bool replace_old_input=true);
void FormOutput (CTvector <DATA> REF outputvector);
virtual bool FeedFwdEncode ();
virtual bool FeedFwdDecode (bool pass_thru_pes=false);
};


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* -------------------------------  */
/* --- IMPLEMENTATION follows: ---  */
/* -------------------------------  */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#include "ta_conec.h"
#include "ta_ans.h"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
CTa_layer <CONNECTION_TYPE,PE_TYPE>::CTa_layer ()
 {
// mprintf("Constructing Layer.\n");
 m_p_parent_ans = NULL;
 m_id = (unsigned) -1;
 m_valid=false;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
CTa_layer <CONNECTION_TYPE,PE_TYPE>::~CTa_layer ()
 {
// mprintf("Destructing Layer.\n");
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>::
Initialize(CTa_ans <CONNECTION_TYPE,PE_TYPE> PTR p_parent_ans, unsigned id, unsigned number_of_PEs)
 {
 unsigned i;

 m_p_parent_ans = p_parent_ans;
 m_id = id;
 m_valid = m_pes.Initialize(number_of_PEs);

 if(m_valid)
  {
  for (i=0;i<number_of_PEs;i++)
   m_valid = m_valid AND m_pes[i].Initialize(m_p_parent_ans,this,i);				// Initialize layer PEs.
  }
 return m_valid;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>::IsConnected(CONNECTION_TYPE REF connection)
 {
 IsValid();
 return m_connections.Contains(connection);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>::operator == (CTa_layer <CONNECTION_TYPE,PE_TYPE> REF c)
 {
 IsValid();
 return m_id==c.m_id;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>::Has_A_PE (unsigned pe_id)
 {
 IsValid();
 return m_pes.HasA(pe_id);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>::Has_A_Connection (unsigned connection_id)
 {
 IsValid();
 return (connection_id<m_connections.Items());
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
unsigned CTa_layer <CONNECTION_TYPE,PE_TYPE>::NumberOfConnections ()
 {
 IsValid();
 return m_connections.Items();
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
unsigned CTa_layer <CONNECTION_TYPE,PE_TYPE>::Dimention ()
 {
 IsValid();
 return m_pes.Items();
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>::Connect(unsigned source_pe_id,unsigned destin_layer_id, unsigned destin_pe_id)
 {
 bool ok=false;

 IsValid();
 CONNECTION_TYPE temp_c (m_p_parent_ans,this,m_id,source_pe_id,destin_layer_id,destin_pe_id);

 if (m_connections.Contains(temp_c))
  mprintf("Warning: Can not connect layer %d,PE %d to layer %d,PE %d.\n", m_id,source_pe_id,destin_layer_id,destin_pe_id);
 else
  {
  if( (m_p_parent_ans->Has_A_Layer(destin_layer_id)) AND
      (Has_A_PE(source_pe_id)) AND 
      (m_p_parent_ans->Layer(destin_layer_id).Has_A_PE(destin_pe_id)) )
   ok = m_connections.StackItem(temp_c);
  }
 return ok;
 }


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
void CTa_layer <CONNECTION_TYPE,PE_TYPE>::Input(const CTvector <DATA> REF input,bool replace_old_input)
 {
 for (unsigned i=0;i<Dimention();i++)
  if(replace_old_input)
   PE(i).SetInput(input[i]);
  else
   PE(i).Input(input[i]);
 }


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
void CTa_layer <CONNECTION_TYPE,PE_TYPE>::Input(DATA input,bool replace_old_input)
 {
 for (unsigned i=0;i<Dimention();i++)
  if(replace_old_input)
   PE(i).SetInput(input);
  else
   PE(i).Input(input);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* Generic feed-forward encode...						   */

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>:: FeedFwdEncode()
 {
 unsigned i;
 bool r =true;

 if(IsValid())
  {
  for(i=0;i<m_pes.Items();i++) r = m_pes[i].Encode() AND r;

  for(i=0;i<m_connections.Items();i++)
   {
   CONNECTION_TYPE REF link = m_connections[i];
   PE_TYPE REF s_pe = m_p_parent_ans->Layer(link.Source_Layer()).PE(link.Source_PE());
   PE_TYPE REF d_pe = m_p_parent_ans->Layer(link.Destin_Layer()).PE(link.Destin_PE());
   link.Input(s_pe.Output());
   r = link.Encode() AND r;
   d_pe.Input(link.Output());
   }
  }
 return r;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* Generic feed-forward decode (recall)...				   */

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>:: FeedFwdDecode(bool pass_thru_pes)
 {
 unsigned i;
 bool r =true;

 if(IsValid())
  {
  for(i=0;i<m_pes.Items();i++) 
   {
   if(pass_thru_pes) m_pes[i].PassThru();
   else r = m_pes[i].Decode() AND r;
   }

  for(i=0;i<m_connections.Items();i++)
   {
   CONNECTION_TYPE REF link = m_connections[i];
   PE_TYPE REF s_pe = m_p_parent_ans->Layer(link.Source_Layer()).PE(link.Source_PE());
   PE_TYPE REF d_pe = m_p_parent_ans->Layer(link.Destin_Layer()).PE(link.Destin_PE());
   link.Input(s_pe.Output());
   r = link.Decode() AND r;
   d_pe.Input(link.Output());
   }
  }
 return r;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
bool CTa_layer <CONNECTION_TYPE,PE_TYPE>::IsValid()
 {
 if((NOT m_valid)OR(m_p_parent_ans EQL NULL))
  mprintf("Warning: Uninitialized layer.\n");
 return m_valid;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
void CTa_layer <CONNECTION_TYPE,PE_TYPE>::Show()
 {
 if(IsValid())
  mprintf("Layer : id = %d.\n",m_id);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
void CTa_layer <CONNECTION_TYPE,PE_TYPE>::ShowAll()
 {
 unsigned i;
 if(IsValid())
  {
  Show();
  mprintf("With PEs :\n");
  for(i=0;i<m_pes.Items();i++)
   {
   mprintf("layer's PE %d :",i);
   m_pes[i].ShowAll();
   }
  mprintf("With Connections :\n");
  for(i=0;i<m_connections.Items();i++)
   {
   mprintf("layer's connection %d :",i);
   m_connections[i].ShowAll();
   }
  mprintf("<End-of-layer-%d>.\n\n",m_id);
  }
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
PE_TYPE REF CTa_layer <CONNECTION_TYPE,PE_TYPE>::PE (unsigned pe_id)
 {
 if(NOT(IsValid() OR Has_A_PE (pe_id)))
  runerror(ANSINTERR,"PE does not exist");
 return m_pes[pe_id];
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
CONNECTION_TYPE REF CTa_layer <CONNECTION_TYPE,PE_TYPE>::Connection (unsigned connection_id)
 {
 if(NOT Has_A_Connection (connection_id))
  runerror(ANSINTERR,"Connection does not exist");
 return m_connections[connection_id];
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
void CTa_layer <CONNECTION_TYPE,PE_TYPE>::OutputToInput(bool replace_old_input)
 {
 IsValid();
 for(unsigned i=0;i<m_pes.Items();i++)
  if(replace_old_input)
   PE(i).SetInput(PE(i).Output());
  else
   PE(i).Input(PE(i).Output());
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template<class CONNECTION_TYPE, class PE_TYPE>
void CTa_layer <CONNECTION_TYPE,PE_TYPE>::FormOutput(CTvector <DATA> REF outputvector)
 {
 unsigned i,j;

 IsValid();
 i=Dimention();
 if(outputvector.cols() NEQL i)
  mprintf("CTa_vector: Warning, cannot form output, size mismatch (layer %d, output %d).\n",i,outputvector.cols());
 else
  for(j=0;j<i;j++)
   outputvector[j]=PE(j).Output();
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#endif // TA_LAYER

