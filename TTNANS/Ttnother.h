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

int select_initial_center_type(int rows,int cols);

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

bool Split_Set(bool RunAlgorithm,
			 int splits,
			 int rows,
			 DATA * split_index);

bool K_Means(bool GetParameters, bool RunAlgorithm,
			int  inputdim, int  numclasses,
			DATA **Trainset,int  Trainsetsize,
			DATA **Testset, int  Testsetsize,
			DATA **Unused,  DATA *Classif);

bool Krazy_K_Means(bool GetParameters, bool RunAlgorithm,
					int  inputdim, int  numclasses,
					DATA **Trainset,int  Trainsetsize,
					DATA **Testset, int  Testsetsize,
					DATA **Unused,  DATA *Classif);

bool MaxMin_Distance
		(bool GetParameters,
		 bool RunAlgorithm,
		 int  inputdim,                     /* input size (dim).     */
		 int  maxnumclasses,                /* max output classes.   */
		 DATA **Trainset,
		 int  Trainsetsize,
		 DATA **Testset,
		 int  Testsetsize,
		 DATA **Unused,                     /* (unused)              */
		 DATA *Classif);

bool MaxMin_Distance_with_Tm_Estimation
			(bool GetParameters,
			 bool RunAlgorithm,
			 int  inputdim,                     /* input size (dim).     */
			 int  classes,                      /* output classes.       */
			 DATA **Trainset,
			 int  Trainsetsize,
			 DATA **Testset,
			 int  Testsetsize,
			 DATA **Unused,                     /* (unused)              */
			 DATA *Classif);

int non_ans_menu(int preselect,bool take_action,
				bool get_algo_parameters,bool run_it,int Unused);

void non_ans_module(void);

#endif

