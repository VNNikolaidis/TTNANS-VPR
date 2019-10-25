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

 DATA linktransferfunctionPLBP(LINK * cp);
 DATA sigmoid(NODE * np, int stmid);
 DATA discrepancy(DATA c1,DATA c2);
 DATA weightmodifierPLBP(LINK * cp);
 ANS * setupPLBP(int numofhidden, int hiddensize,
		       int ins, int outs, DATA learningrate);
 void encodePLBP(DATA * d, DATA * o, ANS * ap);
 int decodePLBP(DATA * d, ANS * ap, DATA * Outstore);
 void closePLBP(ANS * ap);
 void mainPLBP(int mp,int z,int numofhidden,int hiddensize,DATA errorlevel,
		     DATA learningrate,int ins,int outs,DATA ** Trainset,
		     DATA ** Desired,int Trainsetsize, DATA ** Testset,
		     DATA ** Output,int Testsetsize,DATA * Classif);
 void mainPLBP_p(int * mp, int  * z, int * noh, int * hsz,
		       DATA * erl, DATA * lr);
 bool mainPLBP_i(bool GetParameters,bool RunAlgorithm,
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

