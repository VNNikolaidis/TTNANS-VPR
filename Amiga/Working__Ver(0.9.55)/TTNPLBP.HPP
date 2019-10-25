/*
  ---------------------
  TTNANS:
  TTNPLBP.C  ver.0.02
  ---------------------
  Vasilis.N.Nikolaidis
  -----------------------------
  Plain Vanilla BackPropagation
  (Simpson ANS p114)
  -----------------------------

*/

#ifndef TTNPLBP
#define TTNPLBP

extern DATA linktransferfunctionPLBP(LINK * cp);
extern DATA sigmoid(NODE * np, int stmid);
extern DATA discrepancy(DATA c1,DATA c2);
extern DATA weightmodifierPLBP(LINK * cp);
extern ANS * setupPLBP(int numofhidden, int hiddensize,
		       int ins, int outs, DATA learningrate);
extern void encodePLBP(DATA * d, DATA * o, ANS * ap);
extern int decodePLBP(DATA * d, ANS * ap, DATA * Outstore);
extern void closePLBP(ANS * ap);
extern void mainPLBP(int mp,int z,int numofhidden,int hiddensize,DATA errorlevel,
		     DATA learningrate,int ins,int outs,DATA ** Trainset,
		     DATA ** Desired,int Trainsetsize, DATA ** Testset,
		     DATA ** Output,int Testsetsize,DATA * Classif);
extern void mainPLBP_p(int * mp, int  * z, int * noh, int * hsz,
		       DATA * erl, DATA * lr);
extern BOOL mainPLBP_i(BOOL GetParameters,BOOL RunAlgorithm,
		      int WeightInitializationMode,
		      int Inputsize,
		      int Outputsize,
		      DATA ** Trainset,
		      DATA ** Desired,
		      int Trainsetsize,
		      DATA ** Testset,
		      DATA ** Output,
		      int Testsetsize,
		      DATA * Classif);

#endif

