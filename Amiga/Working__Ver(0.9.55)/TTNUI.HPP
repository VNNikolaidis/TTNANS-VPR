/*
  ---------------------
  TTNANS:
  TTNUI.H      ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  -----------------------
  User Interface protos
  defined in TTNUI.C
  -----------------------
*/

#ifndef TTNUI
#define TTNUI

#include "ttndef.hpp"
#include "ttnbool.hpp"

extern int  mprintf(const char * __format,...);
extern void mforcedisplay(void);
extern void mcls(void);
extern void mbeep(void);
extern void mwait(void);
extern void mstarttick(char * message);
extern void mtick(int cur,int max);
extern void mendtick(void);
extern BOOL mrequest_yn(char * tx);
extern int  mrequest_int(char * tx);
extern DATA mrequest_DATA(char * tx);
extern int  mmenu(char ** mlist,int mitems,int firstmline,int minsel,int maxsel);
extern void mplot_bar(DATA data[],int datasize,DATA maxindata);                              /* Max data (100%) */

#endif  /* TNNUI */
