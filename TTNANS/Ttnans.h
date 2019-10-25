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

int ans_menu
   (int preselect,               /* -1 = Show menu              */
    bool take_action,            /* Don't just select an ANS.   */
    bool get_ans_parameters,     /* Ask for ANS parameters too. */
    bool run_ANS,                /* and run it                  */
    int wim);                    /* Weight Initialization Mode  */

#endif
