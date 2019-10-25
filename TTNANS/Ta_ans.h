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


#ifndef TA_ANS
#define TA_ANS

#include <stdarg.h>								// ANSI-style variable arguments.

#define TA_LENGTH 100

#include "ta_conec.h"
#include "ta_pe.h"
#include "ta_layer.h"

#include "ta_envir.h"
#include "ta_store.h"

#include "tmatrix.h"

enum ans_status {NOT_TRAINED,TRAINING,READY_TO_USE};

/*----------------- Artificial Neural Systems -------------*/

template <class CONNECTION_TYPE, class PE_TYPE>
class CTa_ans
{
private:

bool														m_valid;
ans_status													m_status;
char														m_name [TA_LENGTH];
unsigned													m_number_of_layers;
unsigned													m_input_layer;
unsigned													m_output_layer;
CTa_vector_storage < CTa_layer <CONNECTION_TYPE, PE_TYPE> >	m_layers;
bool														m_show;

protected:

public:

CTa_ans (char * name = NULL);
~CTa_ans();
bool Initialize (unsigned first_layer_dimention,...);						// list of layer dimentions...
CTa_layer <CONNECTION_TYPE, PE_TYPE> REF Layer (unsigned layer_id);
void SetStatus(ans_status s){ m_status = s; };
bool Has_A_Layer (unsigned layer_id);
bool Connect(unsigned source_layer_id, unsigned source_pe_id, unsigned destin_layer_id, unsigned destin_pe_id);
bool FullyConnect(unsigned source_layer_id,unsigned destin_layer_id);
unsigned SetInputLayer (unsigned lid);
unsigned SetOutputLayer(unsigned lid);
void PassInputThru(CTvector <DATA> REF input, unsigned layer_id); 
bool IsValid();
void Show();
void ShowAll();
char PTR Name();
bool IsTrained();
virtual bool GetParameters() {return false;};
virtual void ShowDescription() {};
virtual bool FeedFwdEncode (const CTvector <DATA> REF input, const CTvector <DATA> REF output);		// for supervised training...
virtual bool FeedFwdDecode (const CTvector <DATA> REF input, CTvector <DATA> REF output) ;
virtual bool Run(CTa_environment REF envir) {return false;};
};

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* -------------------------------  */
/* --- IMPLEMENTATION follows: ---  */
/* -------------------------------  */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#include "ttndef.h"
#include "ttndef_o.h"
#include "ttndef_s.h"
#include "ttnerror.h"
#include "ttnmemor.h"
#include "ttnui.h"

#include "ta_store.h"

#include <stdarg.h>								// ANSI-style variable arguments.
#include <string.h>


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
CTa_ans<CONNECTION_TYPE,PE_TYPE>::CTa_ans(char * name)
 {
 if(name EQL NULL)
  strncpy(m_name,"-Unnamed-",TA_LENGTH);
 else
  strncpy(m_name,name,TA_LENGTH);
// mprintf("Constructing ANS : %s.\n",m_name);
 m_valid=false;
 m_show = true;
 m_status=NOT_TRAINED;
 };

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
CTa_ans<CONNECTION_TYPE,PE_TYPE>::~CTa_ans()
 {
// mprintf("Destructing ANS : %s.\n",m_name);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::Initialize (unsigned first_layer_dimention,...)		// list of layer dimentions...
 {
 unsigned j , i = first_layer_dimention;
 va_list marker;

 m_valid=true;
 m_number_of_layers = 0;

 mprintf("Initializing ANS, layer sizes : ");

 va_start(marker, first_layer_dimention);				// Initialize variable arguments.
 while(i NEQL 0)
  {
  mprintf("%d",i);
  m_number_of_layers++;
  i = va_arg( marker, unsigned);
  if(i NEQL 0) mprintf (" x ");
  }
 va_end(marker);
 mprintf(" (%d layers).\n",m_number_of_layers);

 m_valid = m_layers.Initialize(m_number_of_layers);

 if(m_valid)
  {
  m_input_layer = j = 0;
  m_output_layer = m_number_of_layers - 1;

  i = first_layer_dimention;
  va_start(marker, first_layer_dimention);				// Initialize variable arguments.
  while((i NEQL 0) AND m_valid)
   {
   m_valid = m_valid AND 
    m_layers[j].Initialize(this,j,i);					// Create layers.
   j++;
   i = va_arg( marker, unsigned);
   }
  va_end(marker);
  }
 return m_valid;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
CTa_layer <CONNECTION_TYPE , PE_TYPE> REF CTa_ans<CONNECTION_TYPE,PE_TYPE>::Layer (unsigned layer_id)
 {
 IsValid();
 return m_layers[layer_id];
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::Has_A_Layer (unsigned layer_id)
 {
 IsValid();
 return m_layers.HasA(layer_id);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::Connect(unsigned source_layer_id, unsigned source_pe_id,
					  unsigned destin_layer_id, unsigned destin_pe_id)
 {
 bool ok=false;

 IsValid();
 if(m_layers.HasA(source_layer_id))
  ok=Layer(source_layer_id).Connect(source_pe_id,destin_layer_id,destin_pe_id);

 return ok;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::FullyConnect(unsigned source_layer_id,unsigned destin_layer_id)
 {
 bool ok=false;
 unsigned i,j;

 IsValid();

 if((m_layers.HasA(source_layer_id)) AND (m_layers.HasA(destin_layer_id)))
  for(j=0;j<Layer(destin_layer_id).Dimention();j++)								// Connect in this order groups connections according to destination
  for(i=0;i<Layer(source_layer_id).Dimention();i++)								// which can be usefull since the connection weights often represent
   ok=Connect(source_layer_id,i,destin_layer_id,j) AND ok;						// (cluster center) coordinates related to the destination (class).
 return ok;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::IsValid()
 {
 if(NOT m_valid)
  mprintf("Warning: Uninitialized ANS.\n");
 return m_valid;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::IsTrained()
{
return (m_status>=TRAINING);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
void CTa_ans<CONNECTION_TYPE,PE_TYPE>::Show()
 {
 if(IsValid())
  mprintf("ANS : %s.\n",m_name);
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
void CTa_ans<CONNECTION_TYPE,PE_TYPE>::ShowAll()
 {
 if(IsValid() AND m_show)
  {
  if(TGBL show_ans_option)
  if(m_show = mrequest_yn("Show ANS structure?"))
   {
   Show();
   mprintf("(This ANS has ");
   if(NOT IsTrained()) mprintf("not");
   mprintf(" completed its training.)\n");
   
   mprintf("With layers :\n");
   for(unsigned i=0;i<m_layers.Items();i++)
    {
    mprintf("ANS layer %d :",i);
    m_layers[i].ShowAll();
    }
   mprintf("<End-of-ANS>.\n\n");
   }
  }
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
char * CTa_ans<CONNECTION_TYPE,PE_TYPE>::Name()
 {return(m_name);}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
unsigned CTa_ans<CONNECTION_TYPE,PE_TYPE>::SetInputLayer(unsigned lid)
 {
 unsigned old_input_layer = m_input_layer;
 
 IsValid();

 if(lid<m_layers.Items())
  m_input_layer = lid;
 else
  mprintf("CTa_ans: Warning! cannot change input layer, layer does not exist.\n");
 return old_input_layer;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
unsigned CTa_ans<CONNECTION_TYPE,PE_TYPE>::SetOutputLayer(unsigned lid)
 {
 unsigned old_output_layer = m_output_layer;

 IsValid();

 if(lid<m_layers.Items())
  m_output_layer = lid;
 else
  mprintf("CTa_ans: Warning! cannot change output layer, layer does not exist.\n");
 return old_output_layer;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

template <class CONNECTION_TYPE, class PE_TYPE>
void CTa_ans<CONNECTION_TYPE,PE_TYPE>::PassInputThru(CTvector <DATA> REF input, unsigned layer_id)
 {
 unsigned p,c;

 Layer(layer_id).Input(input);

 for(p=0;p<Layer(layer_id).Dimention();p++)
  Layer(0).PE(p).PassThru();

 for(c=0;c<Layer(layer_id).NumberOfConnections();c++)
  {
  CONNECTION_TYPE REF link = Layer(layer_id).Connection(c);
  link.Input( Layer(link.Source_Layer()).PE(link.Source_PE()).Output() );
  }
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// parameter output is not used here.

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::FeedFwdEncode
 (const CTvector <DATA> REF input,
  const CTvector <DATA> REF output)
 {
 unsigned i,step;

 #ifdef _DEBUG
 mprintf("Encoding Input:");input.show();
 mprintf("\n");
 mprintf("...with Output:");output.show();
 mprintf("\n");
 #endif

 // Present Input to input layer:

 Layer(m_input_layer).Input(input);

 step = ((m_input_layer<=m_output_layer)?1:-1);
 for(i=m_input_layer;i NEQL m_output_layer; i=i+step) Layer(i).FeedFwdEncode();

 Layer(m_output_layer).FeedFwdEncode();

 return true;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// parameter output is not used here.

template <class CONNECTION_TYPE, class PE_TYPE>
bool CTa_ans<CONNECTION_TYPE,PE_TYPE>::FeedFwdDecode
 (const CTvector <DATA> REF input,
  CTvector <DATA> REF output)
 {
 unsigned i,step;

 #ifdef _DEBUG
 mprintf("Decoding Input:");input.show();
 mprintf("\n");
 #endif

 // Present Input to input layer:

 for(i=0;i<input.cols();i++) Layer(m_input_layer).PE(i).Input(input[i]);

 step = ((m_input_layer<=m_output_layer)?1:-1);
 for(i=m_input_layer;i NEQL m_output_layer; i=i+step) Layer(i).FeedFwdDecode();

 Layer(m_output_layer).FeedFwdDecode();

 return true;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#endif // TA_ANS