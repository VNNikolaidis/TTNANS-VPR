
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

extern DATA euclidiandistsquaredKCN(LINK * lp);
extern DATA _a_KCN(DATA a,int t,DATA max_t);
extern DATA weightmodifierKCN(LINK * cp);
extern ANS * setupKCN(int ins,int outs,int max_t,DATA a);
extern void encodeKCN(DATA * d,ANS * ap);
extern int decodeKCN(DATA * d, ANS * ap, DATA * OutStore);
extern void closeKCN(ANS * ap);
extern DATA compute_Et(ANS * ap);
extern void mainKCN(int ins, int outs,int max_t, int z, DATA e, DATA a,
		    int n, DATA nstep,DATA ** Trainset, int Trainsetsize,
		    DATA ** Testset, int Testsetsize,DATA ** Output,
		    DATA * Classif);
extern void mainKCN_p(int outs, DATA *e, DATA *a, int *max_t, int *z,
		      int *n, DATA *nstep);
extern BOOL mainKCN_i(BOOL GetParameters,BOOL RunAlgorithm,
		      int WeightInitializationMode,int ins,int outs,
		      DATA ** Trainset,int Trainsetsize,DATA ** Testset,
		      int Testsetsize,DATA ** Output,DATA * Classif);

#endif
