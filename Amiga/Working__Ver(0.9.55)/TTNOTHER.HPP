/*
   -------------------
   TTNANS:
   TTNOTHER.C ver.0.01
   -------------------
   V.N.Nikolaidis
   ------------------------
   Non-ANS clustering/PR
   algorithms added for
   performance comparisons.
   ------------------------
*/

#ifndef TTNOTHER
#define TTNOTHER

extern int select_initial_center_type(int rows,int cols);

void NNC_call (DATA ** Dataset,
	       int rows,
	       int cols,
	       DATA ** Prototypes,
	       int numprototypes,
	       DATA * Classification);

void move_prototypes_to_means
	      (DATA ** Dataset,
	       int rows,
	       int cols,
	       DATA ** Prototypes,      /* must be numprototypes x cols. */
		   int numprototypes,       /* overwrites Prototypes.        */
		   DATA * Classification);

extern int Split_Set(BOOL RunAlgorithm,
			 int splits,
					 int rows,
					 DATA * split_index);

extern BOOL K_Means(BOOL GetParameters, BOOL RunAlgorithm,
					int  inputdim, int  numclasses,
					DATA **Trainset,int  Trainsetsize,
					DATA **Testset, int  Testsetsize,
					DATA **Unused,  DATA *Classif);

extern BOOL Krazy_K_Means(BOOL GetParameters, BOOL RunAlgorithm,
					int  inputdim, int  numclasses,
					DATA **Trainset,int  Trainsetsize,
					DATA **Testset, int  Testsetsize,
					DATA **Unused,  DATA *Classif);

extern BOOL MaxMin_Distance
		(BOOL GetParameters,
		 BOOL RunAlgorithm,
		 int  inputdim,                     /* input size (dim).     */
		 int  maxnumclasses,                /* max output classes.   */
		 DATA **Trainset,
		 int  Trainsetsize,
		 DATA **Testset,
		 int  Testsetsize,
		 DATA **Unused,                     /* (unused)              */
		 DATA *Classif);

extern BOOL MaxMin_Distance_with_Tm_Estimation
			(BOOL GetParameters,
			 BOOL RunAlgorithm,
			 int  inputdim,                     /* input size (dim).     */
			 int  classes,                      /* output classes.       */
			 DATA **Trainset,
			 int  Trainsetsize,
			 DATA **Testset,
			 int  Testsetsize,
			 DATA **Unused,                     /* (unused)              */
			 DATA *Classif);

extern int non_ans_menu(int preselect,BOOL take_action,
                        BOOL get_algo_parameters,BOOL run_it,
                        int Unused);

extern void non_ans_module(void);

#endif

