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

extern void batch_n_filename(char * infname,int runnum,
			     char * outfname,char * ext);
extern void batch_show_and_save(BOOL interactive,int curstep,BOOL saveclasses);
extern void batch_run_using_classes
		(char * fname,DATA (*workfunction)(char *,int));
extern void batch_run_using_classification
		(char * prbfname,DATA (*workfunction)(char *,char *,int));
extern int  vary_initial_weights_menu(void);
extern void show_reordering_warning(void);
void get_bandx_output_ranges(int * min,int *max, int * step, int * repeats);
extern void one_ans_one_problem_menu(int preselect,
				     int algo_launcher(int,BOOL,BOOL,BOOL,int));
extern void batch_experiment_menu(void);

#endif
