/*
  ---------------------
  TTNANS:
  TTNREPRT.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Report (Session)
  Generation.
  ---------------------

*/

#ifndef TTNREPRT
#define TTNREPRT

extern BOOL sessionenabled;
extern FHANDLE sessionfile;
extern char sessionfilename[FILENAMELENGTH];

extern void StartReporting(void);
extern void StopReporting(void);
extern void ReportToSessionFile(char * x);
extern void ReportTime(void);

#endif

