/*
   --------------------
   TTNANS:
   TTNBANDX.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------------
   Batch + Experimentation Module
   ------------------------------

*/

#ifndef TTNBANDX
#define TTNBANDX

void batch_n_filename(char * infname,int runnum,
			     char * outfname,char * ext);
void batch_show_and_save(bool interactive,int curstep,bool saveclasses);
void batch_run_using_classes
		(char * fname,DATA (*workfunction)(char *,int));
void batch_run_using_classification
		(char * prbfname,DATA (*workfunction)(char *,char *,int));
int  vary_initial_weights_menu(void);
void show_reordering_warning(void);
void get_bandx_output_ranges(int * min,int *max, int * step, int * repeats);
void one_ans_one_problem_menu(int preselect,int  algo_launcher(int,bool,bool,bool,int));
void batch_experiment_menu(void);

#endif
