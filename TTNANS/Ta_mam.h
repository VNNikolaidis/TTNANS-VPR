#ifndef TA_MAM_H
#define TA_MAM_H

#include "ta_conec.h"
#include "ta_pe.h"
#include "ta_ans.h"
#include "ta_envir.h"

#include "ttnui.h"

#define MAM_RIG CTa_MAM_connection,CTa_MAM_pe

/*------- MAM Connections ---------------------------------*/

class CTa_MAM_connection : public CTa_connection
{
public:

CTa_MAM_connection() : CTa_connection() {};
CTa_MAM_connection(	void PTR p_ans, void PTR p_layer,
					unsigned sl, unsigned sp,unsigned dl, unsigned dp)
					: CTa_connection(p_ans,p_layer,sl,sp,dl,dp) {}

bool Encode () { return CTa_connection::Encode(); }
bool Encode (DATA x)  {  m_weight = m_weight + x; return true; }
};

/*------- MAM Processing Elements -------------------------*/

class CTa_MAM_pe : public CTa_pe
{
public:
bool Encode ()  { PassThru(); return true; }
bool Decode (bool use_threshold = false)
 {
 if(use_threshold)
  {
  DATA j = 0;
  if(m_input > 0) j = 1;
  if(m_input < 0) j = -1;
  m_output = j;
  m_input = 0;
  }
 else 
  m_output = m_input;
 return true;
 }
};

/*------- MAM Artificial Neural System---------------------*/

class CTa_MAM_ans : public CTa_ans <MAM_RIG>
{
private:

unsigned m_max_iteration;
bool m_use_pe_threshold;

public:

CTa_MAM_ans (unsigned input_dimention,unsigned output_dimention)
 : CTa_ans<MAM_RIG> ("MAM - Discrete Bidirectional Associative Memory")
 {
 m_max_iteration = 10;
 Initialize(input_dimention,output_dimention,0);
 FullyConnect(0,1);
 };

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void ShowDescription()
 {
 mhintclear();
 mhintf(true,"The Matrix Associative Memory (MAM) is implemented as a two\n");
 mhintf(true,"layer heteroassociative ANS. For more information on MAM,\n");
 mhintf(true,"see Pao, Adaptive Pattern Recognition and Neural Networks.\n");
 mhintf(true,"\n");
 mhintf(true,"This a CTa_ans (Class ANS) library-based emulation.          \n");
 mhintf(true,"\n");
 }

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool GetParameters()
 {
 m_use_pe_threshold = mrequest_yn("Use threshold on output PEs?");
 if(m_use_pe_threshold)
  {
  mhintf(true,"\n");
  mhintf(true,"Using PE threshold (on decode - recall phase):\n");
  mhintf(true,"\n");
  mhintf(true,"                                           \n");
  mhintf(true,"                                           \n");
  mhintf(true,"               1      if input > 0         \n");
  mhintf(true,"   output =  { 0      if input = 0         \n");
  mhintf(true,"              -1      if input < 0         \n");
  mhintf(true,"                                           \n");
  }
  
 return true;
 };

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool Encode(CTvector <DATA> REF input, CTvector <DATA> REF output)
 {
 unsigned p,c;

 Layer(0).Input(input);
 Layer(1).Input(output);

 for(p=0;p<Layer(0).Dimention();p++) Layer(0).PE(p).Encode();
 for(p=0;p<Layer(1).Dimention();p++) Layer(1).PE(p).Encode();

 for(c=0;c<Layer(0).NumberOfConnections();c++)
  {
  CTa_MAM_connection REF    link = Layer(0).Connection(c);
  CTa_MAM_pe REF			s_pe = Layer(link.Source_Layer()).PE(link.Source_PE());
  CTa_MAM_pe REF			d_pe = Layer(link.Destin_Layer()).PE(link.Destin_PE());

  link.Encode(s_pe.Output() * d_pe.Output());
  }

 return true;
 }

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool Decode(CTvector <DATA> REF input, CTvector <DATA> REF output)
 {
 bool resonation = false;

 unsigned inlayer = 0;
 unsigned outlayer = 1;

 Layer(inlayer).Input(input);
 Layer(outlayer).Input(0);

 Layer(inlayer).FeedFwdDecode(true);
 for(unsigned p=0;p<Layer(1).Dimention();p++) Layer(outlayer).PE(p).Decode(m_use_pe_threshold);
 Layer(outlayer).FormOutput(output); 

 return true;
 }

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool Run(CTa_environment REF envir)
 {

 if(envir.Type() NEQL CTAENV_SUPERVISED)
  {
  runerror (PRBDEFERR,"MAM needs supervised environment with defined desired output set");
  return false;
  }
 
 ShowDescription();
 ShowAll();

 mprintf("MAM Encoding...\n");

 while(NOT envir.EndOfTrainingItemsReached())
  {
  Encode(envir.GetTrainingItem(),envir.GetOutputPrototype());
  envir.NextTrainingItem();
  }

 SetStatus(READY_TO_USE);
 ShowAll();
 mprintf("MAM Decoding...\n");

 while(NOT envir.EndOfUsageItemsReached())
  {
  Decode(envir.GetUsageItem(),envir.GetOutputVector());
  envir.StoreOutput();
  envir.NextUsageItem();
  }

 mprintf("MAM Done...\n");
 ShowAll();

 return true;
 }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

};

#endif // TA_MAM_H
