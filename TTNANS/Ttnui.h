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

#include "ttndef_o.h"

 int  mprintf(const char * __format,...);
 int  mprint_(const char * text);
 int  mhintf(bool addtosessionfile, const char * __format,...);
 void mhintclear();
 void mforcedisplay(void);
 void mcls(void);
 void mbeep(void);
 void mwait(void);
 void mstarttick(char * message);
 void mtick(int cur,int max);
 void mendtick(void);
 void mmessage(char * tx);
 bool mrequest_yn(char * tx);
 int  mrequest_int(char * tx);
 DATA mrequest_DATA(char * tx);
 int  mmenu(char * mtitle, char ** mlist,int mitems, int maxsel);
 void mplot_bar(DATA data[],int datasize,DATA maxindata);
 void mprintauthor();

#endif  /* TNNUI */
