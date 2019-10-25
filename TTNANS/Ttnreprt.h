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

extern bool sessionenabled;
extern FHANDLE sessionfile;
extern char sessionfilename[FILENAMELENGTH];

void StartReporting(void);
void StopReporting(void);
void ReportToSessionFile(const char * x);
void ReportTime(void);

#endif

