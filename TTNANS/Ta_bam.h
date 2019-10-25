#ifndef TA_BAM_H
#define TA_BAM_H

#include "ta_conec.h"
#include "ta_pe.h"
#include "ta_ans.h"
#include "ta_envir.h"

#include "ttnui.h"

#define BAM_RIG CTa_BAM_connection,CTa_BAM_pe

/*------- BAM Connections ---------------------------------*/


class CTa_BAM_connection : public CTa_connection
{
public:

CTa_BAM_connection() : CTa_connection() {};
CTa_BAM_connection(	void PTR p_ans, void PTR p_layer,
					unsigned sl, unsigned sp,unsigned dl, unsigned dp)
					: CTa_connection(p_ans,p_layer,sl,sp,dl,dp) {}

bool Encode ()  {  m_weight = m_weight + m_input; return true; }
};

/*------- BAM Processing Elements -------------------------*/

class CTa_BAM_ans;

class CTa_BAM_pe : public CTa_pe
{
DATA m_oldoutput;

public:
bool Encode ()  { PassThru(); return true; }

void PassThru()  { m_output=m_oldoutput=m_input; m_input = 0; }

bool Decode ()
 {
 bool r;
 DATA j = m_oldoutput;
 if(m_input > 0) j = 1;
 if(m_input < 0) j = -1;
 r = (j EQL m_oldoutput);
 m_oldoutput = m_output = j;
 m_input = 0;
 return r;
 }

CTa_BAM_pe() : CTa_pe() {m_oldoutput=LARGEDATA;}
};

/*------- BAM Artificial Neural System---------------------*/

class CTa_BAM_ans : public CTa_ans <BAM_RIG>
{
private:

unsigned m_max_iteration;

public:

CTa_BAM_ans (unsigned input_dimention,unsigned output_dimention)
 : CTa_ans<BAM_RIG> ("BAM - Discrete Bidirectional Associative Memory")
 {
 m_max_iteration = 10;
 Initialize(input_dimention,output_dimention,0);
 FullyConnect(0,1);
 FullyConnect(1,0);
 };

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void ShowDescription()
 {
 mhintclear();
 mhintf(true,"The Discrete Bidirectional Associative Memory (BAM) is a two \n");
 mhintf(true,"layer ANS that encodes bipolar (preferably -1,1) data vector \n");
 mhintf(true,"pairs in an heteroassociative (supervised) manner.           \n");
 mhintf(true,"(for more details see Simpson: Artificial Neural Systems.    \n");
 mhintf(true,"\n");
 mhintf(true,"This a CTa_ans (Class ANS) library-based emulation.          \n");
 mhintf(true,"\n");
 mhintf(true,"BAM is using the following PE threshold (on decode - recall phase):\n");
 mhintf(true,"\n");
 mhintf(true,"                                            \n");
 mhintf(true,"                                            \n");
 mhintf(true,"                 1             if input > 0 \n");
 mhintf(true,"  output(t) =  { output(t-1)   if input = 0 \n");
 mhintf(true,"                -1             if input < 0 \n");
 mhintf(true,"                                            \n");
 mhintf(true,"\n");
 }

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool GetParameters()
 {
 m_max_iteration = (unsigned) mrequest_int("Please enter maximum iteration limit (for decode phase)");
 return true;
 };

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool Encode(CTvector <DATA> REF input, CTvector <DATA> REF output)
 {
 unsigned p,c;

 /* Encode forwards */

 Layer(0).Input(input);
 Layer(1).Input(output);

 for(p=0;p<Layer(0).Dimention();p++) Layer(0).PE(p).Encode();
 for(p=0;p<Layer(1).Dimention();p++) Layer(1).PE(p).Encode();

 for(c=0;c<Layer(0).NumberOfConnections();c++)
  {
  CTa_BAM_connection REF    link = Layer(0).Connection(c);
  CTa_BAM_pe REF			s_pe = Layer(link.Source_Layer()).PE(link.Source_PE());
  CTa_BAM_pe REF			d_pe = Layer(link.Destin_Layer()).PE(link.Destin_PE());

  link.Input(s_pe.Output() * d_pe.Output());
  link.Encode();
  }

 /* Encode backwards */

 Layer(0).Input(input);
 Layer(1).Input(output);

 for(p=0;p<Layer(0).Dimention();p++) Layer(0).PE(p).Encode();
 for(p=0;p<Layer(1).Dimention();p++) Layer(1).PE(p).Encode();

 for(c=0;c<Layer(1).NumberOfConnections();c++)
  {
  CTa_BAM_connection REF    link = Layer(1).Connection(c);
  CTa_BAM_pe REF			s_pe = Layer(link.Source_Layer()).PE(link.Source_PE());
  CTa_BAM_pe REF			d_pe = Layer(link.Destin_Layer()).PE(link.Destin_PE());

  link.Input(s_pe.Output() * d_pe.Output());
  link.Encode();
  }

 return true;
 }

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool Decode(unsigned inlayer_in, CTvector <DATA> REF input, CTvector <DATA> REF output)
 {
 bool resonation = false;

 unsigned i,t;
 unsigned inlayer = inlayer_in;
 unsigned original_outlayer, outlayer = 2;

 if(inlayer  EQL 0) outlayer = 1;
 if(inlayer  EQL 1) outlayer = 0;
 if(outlayer EQL 2) { runerror(ANSINTERR,"BAM decode: Layer error"); return false; }
 original_outlayer = outlayer;

 Layer(inlayer).Input(input);
 Layer(outlayer).Input(0);

 i=0;

 while((NOT resonation) AND (i<m_max_iteration))
  {
  Layer(inlayer).FeedFwdDecode(true);
  resonation=Layer(outlayer).FeedFwdDecode();
  t=outlayer;
  outlayer=inlayer;
  inlayer=t;
  i++;
  }
 
 if(NOT resonation) mprintf("BAM decode reached maximum iteration limit (%d) with no resonation.\n",m_max_iteration);

 Layer(original_outlayer).FeedFwdDecode();   
 Layer(original_outlayer).FormOutput(output); 

 return true;
 }

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

bool Run(CTa_environment REF envir)
 {
 if(envir.Type() NEQL CTAENV_SUPERVISED)
  {
  runerror (PRBDEFERR,"BAM needs supervised environment with defined desired output set");
  return false;
  }
  
 ShowDescription();
 ShowAll();

 mprintf("BAM Encoding...\n");

 while(NOT envir.EndOfTrainingItemsReached())
  {
  Encode(envir.GetTrainingItem(),envir.GetOutputPrototype());
  envir.NextTrainingItem();
  }

 SetStatus(READY_TO_USE);
 ShowAll();
 mprintf("BAM Decoding...\n");

 while(NOT envir.EndOfUsageItemsReached())
  {
  Decode(0,envir.GetUsageItem(),envir.GetOutputVector());
  envir.StoreOutput();
  envir.NextUsageItem();
  }

 mprintf("BAM Done...\n");
 ShowAll();

 return true;
 }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

};

#endif // TA_BAM_H
