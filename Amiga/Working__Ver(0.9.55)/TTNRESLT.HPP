/*
   --------------------
   TTNANS:
   TTNRESLT.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   Result Evaluation Module
   ------------------------
*/

#ifndef TTNRESLT
#define TTNRESLT

/*-------------------------------------------------------------------------*/

extern DATA sum_of_squared_errors_on_set(char * fname,int runnum);
extern DATA sum_of_squared_errors_on_set_scaled(char *fname,int runnum);
extern DATA Rij_on_set(char * fname, int runnum);
extern DATA Rij_on_set_scaled(char *fname,int runnum);
extern DATA all_criteria_scaled_with_quick_report(char *fname,int runnum);
extern void result_evaluation_menu(void);

#endif

