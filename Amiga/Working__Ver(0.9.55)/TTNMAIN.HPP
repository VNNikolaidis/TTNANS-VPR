/*
   --------------------
   TTNANS:
   TTNMAIN.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   Definitions, main(),
   significant menus.
   --------------------

*/

#ifndef TTNMAIN
#define TTNMAIN

extern char prbfname[FILENAMELENGTH];
extern BOOL prb_loaded;
extern BOOL ANS_run_success;
extern BOOL LinkLogDebugMode;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

extern int  inputdim;             /* dimention (width) of train,test set.*/
extern int  outputdim;            /* dimention (width) of desired output.*/

extern int  trainsetsize;         /* number of train-set records.        */
extern int  testsetsize;          /* number of test-set records.         */

extern DATA ** trainset;          /* train set records.                  */
extern DATA ** desired;           /* desired outputs for train set.      */
extern DATA ** testset;
extern DATA ** output;            /* actual ANS output.                  */
extern DATA *  classif;           /* winner-takes-all etc output.        */

/*-----------------------------------------------------------------------*/

extern void problem_menu(int preselect);
extern void startup_menu(int preselect);
extern void misc_menu(void);

extern void MMAIN();

#endif

