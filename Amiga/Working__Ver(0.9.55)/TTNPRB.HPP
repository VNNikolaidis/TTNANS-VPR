
/* --------------------
   TTNANS:
   TTNPRB.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   Problem Description File
   ------------------------ */

#ifndef TTNPRB
#define TTNPRB

#include "ttndef_s.hpp"
#define PRBFILEINFO  struct PRBFILEINFO_

PRBFILEINFO
 {
 int  problem_type;               /* Clustering,Supervised etc*/
 char prb_file [FILENAMELENGTH];  /* Actual problem filename. */
 char trn_file [FILENAMELENGTH];  /* Train set filename.      */
 char tst_file [FILENAMELENGTH];  /* Test set filename.       */
 char dsr_file [FILENAMELENGTH];  /* Desired output filename. */
 int descriptor_dim;              /* Number of descriptors    */
 int * descriptors;               /* Actual descripror list.  */
 };

extern void ShowPrbFormat(void);
extern void CreatePrbFile(void);
extern void FreePrbInfo(PRBFILEINFO * prbinfo);
extern PRBFILEINFO * GetPrbInfo(char * fnamein);
extern void ShowPrbInfo(PRBFILEINFO * p);
extern void LoadAllData(char * fnamein);      /* Load a *.prb */

#endif
