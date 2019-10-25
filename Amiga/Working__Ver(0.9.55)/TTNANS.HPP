/*
   --------------------
   TTNANS:
   TTNANS.C    ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   ANS Launcher & menus.
   --------------------

*/

#ifndef TTNANS
#define TTNANS

extern int ans_menu
	    (int preselect,               /* -1 = Show menu              */
	     BOOL take_action,            /* Don't just select an ANS.   */
	     BOOL get_ans_parameters,     /* Ask for ANS parameters too. */
	     BOOL run_ANS,                /* and run it                  */
	     int wim);                    /* Weight Initialization Mode  */

#endif
