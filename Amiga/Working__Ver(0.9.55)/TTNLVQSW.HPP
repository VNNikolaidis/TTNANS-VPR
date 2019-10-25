/*
  ---------------------
  TTNANS:
  TTNLVQSWU.C  ver.0.3
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  LVQ Learning Vector
    Quantizer Single
  Winner Unsupervised.
  Kohonen,(Simpson p87)
  ---------------------

*/

#ifndef TTNLVQSW
#define TTNLVQSW
extern void mainLVQSWU(int ins, int outs, int z,DATA a, DATA ** Trainset,int Trainsetsize,
			   DATA ** Testset,int Testsetsize,DATA ** Output,DATA * Classif);
extern void mainLVQSWU_p(int  * z, DATA *a);
extern BOOL mainLVQSWU_i(BOOL GetParameters,BOOL RunAlgorithm,int WeightInitializationMode,
			 int ins,int outs,DATA ** Trainset,int Trainsetsize,
			 DATA ** Testset,int Testsetsize,DATA ** Output,DATA * Classif);

#endif
