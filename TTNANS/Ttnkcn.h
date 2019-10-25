
/*
  ----------------------------
  TTNANS:
  TTNKCN.C           ver.0.02
  ----------------------------
  Vasilis.N.Nikolaidis
  ---------------------------------
  Kohonen Clustering Net.
  An 1-D modification of LVQ,
  Multiple Winner Unsupervised,
  See (E.C.K.Thao et al.):
  Fuzzy Kohonen Clustering Networks
  ---------------------------------

*/

#ifndef TTNKCN
#define TTNKCN

#include "ttndef_n.h"

 DATA euclidiandistsquaredKCN(LINK * lp);
 DATA _a_KCN(DATA a,int t,DATA max_t);
 DATA weightmodifierKCN(LINK * cp);
 ANS * setupKCN(int ins,int outs,int max_t,DATA a);
 void encodeKCN(DATA * d,ANS * ap);
 int decodeKCN(DATA * d, ANS * ap, DATA * OutStore);
 void closeKCN(ANS * ap);
 DATA compute_Et(ANS * ap);
 void mainKCN(int ins, int outs,int max_t, int z, DATA e, DATA a,
		    int n, DATA nstep,DATA ** Trainset, int Trainsetsize,
		    DATA ** Testset, int Testsetsize,DATA ** Output,
		    DATA * Classif);
 void mainKCN_p(int outs, DATA *e, DATA *a, int *max_t, int *z,
		      int *n, DATA *nstep);
 bool mainKCN_i(bool GetParameters,bool RunAlgorithm,
		      int WeightInitializationMode,int ins,int outs,
		      DATA ** Trainset,int Trainsetsize,DATA ** Testset,
		      int Testsetsize,DATA ** Output,DATA * Classif);

#endif
