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


#ifndef TA_ENVIR
#define TA_ENVIR

/*---------------------- Environment ----------------------*/

#include "tmatrix.h"

#define CTAENV_SUPERVISED							0
#define CTAENV_UNSUPERVISED_WITH_SEPATATE_USAGE		1
#define CTAENV_UNSUPERVISED							2
#define CTAENV_INVALID								999

class CTa_environment
{
private:

CTmatrix <DATA> * training_data_set;
CTmatrix <DATA> * output_prototypes_set;
CTmatrix <DATA> * usage_data_set;
CTmatrix <DATA> * output;
CTvector <DATA> * output_vector;

unsigned		m_currently_training;							// current training item , output prototype
unsigned		m_currently_decoding;							// current usage item , output

unsigned		m_environment_type;

void initialize(DATA ** tr_set, unsigned tr_r, unsigned tr_c,	// training set
				unsigned op_r, unsigned op_c)					// output size
 {
 training_data_set		= NULL;
 output_prototypes_set	= NULL;
 usage_data_set			= NULL;
 output					= NULL;

 output_vector			= NULL;

 m_currently_training	= 0;
 m_currently_decoding   = 0;

 if((tr_set==NULL) OR (tr_r==0) OR (tr_c==0) OR (op_c==0)) Warn();
 else
  {
  training_data_set = new CTmatrix <DATA> (tr_set, tr_r, tr_c, "Training Data", true);
  output = new CTmatrix <DATA> (op_r, op_c, 0, "Output", true);
  output_vector = new CTvector <DATA> (op_c, 0);
  }
 }

void initialize(DATA ** tr_set, unsigned tr_r, unsigned tr_c,			// training set
				DATA ** us_set, unsigned us_r, unsigned us_c,			// usage set (testing set)
				unsigned op_c)											// output size in columns
 {
 if((us_set==NULL) OR (us_r==0) OR (us_c==0) OR (us_c==0) OR (us_c NEQL tr_c))  Warn();
 else
  {
  initialize(tr_set,tr_r,tr_c,us_r,op_c);
  usage_data_set = new CTmatrix <DATA> (us_set, us_r, us_c, "Usage (Testing) Data", true);
  }
 }

void initialize(DATA ** tr_set, unsigned tr_r, unsigned tr_c,			// training set
				DATA ** us_set, unsigned us_r, unsigned us_c,			// usage set (testing set)
				DATA ** op_set, unsigned op_r, unsigned op_c)			// output prototypes (desired output)

 {
 if((op_set==NULL) OR (op_r==0) OR (op_c==0) OR (op_r NEQL tr_r))  Warn();
 else
  {
  initialize(tr_set,tr_r,tr_c,us_set,us_r,us_c,op_c);
  output_prototypes_set = new CTmatrix <DATA> (op_set, op_r, op_c, "Output Prototypes", true);
  }
 }

public:

~CTa_environment()
 {
 delete (training_data_set);
 delete (output_prototypes_set);
 delete (usage_data_set);
 delete (output);
 delete (output_vector);
 }

// Unsupervised (clustering) Environment:

CTa_environment()														// Uninitialized
 {
 training_data_set		= NULL;
 output_prototypes_set	= NULL;
 usage_data_set			= NULL;
 output					= NULL;
 output_vector			= NULL;
 m_currently_training	= 0;
 m_currently_decoding   = 0;
 m_environment_type		= CTAENV_INVALID;
 }

unsigned Type() {return m_environment_type;}

void Show()
 {
 if(training_data_set NEQL NULL) training_data_set->show();
 if(output_prototypes_set NEQL NULL) output_prototypes_set->show();
 if(usage_data_set NEQL NULL) usage_data_set->show();
 if(output NEQL NULL) output->show();
 mprintf("Output vector is :");
 if(output_vector NEQL NULL) output_vector->show();
 mprintf(".\n");
 }

CTa_environment(DATA ** tr_set, unsigned tr_r, unsigned tr_c,			// training set
				unsigned op_c)											// output size in columns
 {
 Reset(tr_set,tr_r,tr_c,NULL,0,0,NULL,0,op_c);
 }

// Unsupervised Environment with separate usage file:

CTa_environment(DATA ** tr_set, unsigned tr_r, unsigned tr_c,			// training set
				DATA ** us_set, unsigned us_r, unsigned us_c,			// usage set (testing set)
				unsigned op_c)											// output size in columns
 {
 Reset(tr_set,tr_r,tr_c,us_set,us_r,us_c,NULL,0,op_c);
 }

// Supervised Environment:

CTa_environment(DATA ** tr_set, unsigned tr_r, unsigned tr_c,			// training set
				DATA ** us_set, unsigned us_r, unsigned us_c,			// usage set (testing set)
				DATA ** op_set, unsigned op_r, unsigned op_c)			// output prototypes (desired output)

 {
 Reset(tr_set,tr_r,tr_c,us_set,us_r,us_c,op_set,op_r,op_c);
 }


bool Reset(	DATA ** tr_set, unsigned tr_r, unsigned tr_c,				// training set
			DATA ** us_set, unsigned us_r, unsigned us_c,				// usage set (testing set)
			DATA ** op_set, unsigned op_r, unsigned op_c)				// output prototypes (desired output)

 {
 mprintf("Closing old environment (if any):");
 delete (training_data_set);
 delete (output_prototypes_set);
 delete (usage_data_set);
 delete (output);
 training_data_set		= NULL;
 output_prototypes_set	= NULL;
 usage_data_set			= NULL;
 output					= NULL;
 m_currently_training	= 0;
 m_currently_decoding   = 0;
 m_environment_type		= CTAENV_INVALID;
 mprintf("Done.\n");

 if( (tr_set NEQL NULL) AND (us_set NEQL NULL) AND (op_set NEQL NULL) )
  {
  mprintf("Creating supervised environment.\n");
  initialize(tr_set,tr_r,tr_c,us_set,us_r,us_c,op_set,op_r,op_c);
  m_environment_type = CTAENV_SUPERVISED;
  return true;
  }
 if( (tr_set NEQL NULL) AND (us_set NEQL NULL) )
  {
  mprintf("Creating clustering (separate testing set) environment.\n");
  initialize(tr_set,tr_r,tr_c,us_set,us_r,us_c,op_c);
  m_environment_type = CTAENV_UNSUPERVISED_WITH_SEPATATE_USAGE;
  return true;
  }
 if( tr_set NEQL NULL )
  {
  mprintf("Creating clustering (single set) environment.\n");
  initialize(tr_set,tr_r,tr_c,tr_r,op_c);
  m_environment_type = CTAENV_UNSUPERVISED;
  return true;
  }
 mprintf("CTa_environment: Cannot create new environment !\n");
 Warn();
 return false;
 }

void Warn()
 {
 mprintf("CTa_environment Warning: Inconcistent environment! Throwing memory error...\n");
 runerror(MEMORYERR,"Inconsistent environment");
 }


CTvector <DATA> GetTrainingItem()
 {
 if(training_data_set NEQL NULL)
  return CTvector <DATA> (training_data_set->row(m_currently_training),
						  training_data_set->cols());

 mprintf("CTa_environment Warning: Invalid Training Data Set! Throwing memory error...\n");
 runerror(MEMORYERR,"Invalid data set");
 return CTvector <DATA> (1,0);
 }

CTvector <DATA> GetOutputPrototype()
 {
 if(output_prototypes_set NEQL NULL)
  return CTvector <DATA> (output_prototypes_set->row(m_currently_training),
						  output_prototypes_set->cols());

 mprintf("CTa_environment Warning: Invalid Output Prototypes (desired output) Set! Returning Training Set Item...\n");
 return GetTrainingItem();
 }

void RestartTrainingFromTop ()
 {
 mprintf("(Restarting training item presentation from top.\n");
 m_currently_training = 0;
 }

bool EndOfTrainingItemsReached ()
 {
 if(training_data_set NEQL NULL)
  return (m_currently_training>=training_data_set->rows());

 mprintf("CTa_environment Warning: Invalid Training Data Set! Throwing memory error...\n");
 runerror(MEMORYERR,"Invalid data set");
 return true;
 }


void NextTrainingItem(bool restart = false)
 {
 m_currently_training ++;
 if( EndOfTrainingItemsReached() AND restart)
  RestartTrainingFromTop ();
 }

CTvector <DATA> GetUsageItem()
 {
 if(usage_data_set NEQL NULL)
  return CTvector <DATA> (usage_data_set->row(m_currently_decoding),
						  usage_data_set->cols());

 mprintf("CTa_environment Warning: Invalid Usage (testing) Set! Returning Training Set Item...\n");
 return GetTrainingItem();
 }

// NOTE: GetOutputItem is for accessimg output read-only,
// use GetOutputVector and StoreOutput to "write" to output.

CTvector <DATA> GetOutputItem()
 {
 return CTvector <DATA> (output->row(m_currently_decoding),
						 output->cols());
 }

CTvector <DATA> REF GetOutputVector()
 {
 return * output_vector;
 }

void StoreOutput()
 {
 for(unsigned c=0;c<output_vector->cols();c++)
  output->at(m_currently_decoding,c)=output_vector->at(c);
 }

void RestartUsageFromTop ()
 {
 mprintf("(Restarting Usage (testing) item presentation from top.)\n");
 m_currently_decoding = 0;
 }

bool EndOfUsageItemsReached ()
 {
 if(usage_data_set NEQL NULL)
  return (m_currently_decoding>=usage_data_set->rows());
 return (m_currently_decoding>training_data_set->rows());
 }


void NextUsageItem(bool restart = false)
 {
 m_currently_decoding ++;
 if( EndOfUsageItemsReached() AND restart)
  RestartUsageFromTop ();
 }

};

/*---------------------------------------------------------*/

#endif // TA_ENVIR
