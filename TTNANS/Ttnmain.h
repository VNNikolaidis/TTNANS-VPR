/*
   --------------------
   TTNANS:
   TTNMAIN.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   Global Definitions,
   main(),
   significant menus.
   --------------------
*/

#ifndef TTNMAIN
#define TTNMAIN

#include "tglobal.h"

#define TGBL ptg->
extern CTglobal * ptg;

void ANS_processing_menu(int preselect);
void startup_menu(int preselect);
void misc_menu(void);
void reset_or_exit();

// void ttnans_main();

#endif

