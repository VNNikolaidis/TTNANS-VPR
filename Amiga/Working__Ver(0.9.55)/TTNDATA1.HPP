/*
  ---------------------
  TTNANS:
  TTNDATA1.C   ver.0.03
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  alloc/input/free Data
  ---------------------
  Also: RandomDATA
  ---------------------

*/

#ifndef TTNDATA1
#define TTNDATA1

extern void CreateTrainset(void);
extern void CreateDesired(void);
extern void CreateTestset(void);
extern void CreateOutput(void);
extern void CreateClassif(void);
extern void Show2dDataSet(DATA ** Set, int rows, int cols);
extern void ShowTrainset(void);
extern void ShowDesired(void);
extern void ShowTestset(void);
extern void ShowClassif(void);
extern void ShowOutput(void);
extern BOOL ValidatedDescriptors(int * deslist, int deslistsize, int deslimit);
extern BOOL LoadDataSetWithSelectedColumns(FHANDLE f,   /* input file w/ */
                                    int frows,          /* assumed size  */
                                    int fcols,          /* frows X fcols.*/
                                    DATA ** TargetSet,  /* Put here.     */
                                    int  *  colist,     /* Selected Cols.*/
                                    int  colistsize);   /* num of cols.  */

/*  the next load functions also allocate memory for corresponding sets. */

extern void LoadTrainset(char * fnamein,int desnum, int * deslist);
extern void LoadDesired(char * fnamein);
extern void LoadTestset(char * fnamein,int desnum, int * deslist);

extern void SaveClassif(char * fnamein, char * comment, BOOL askfirst);
extern void SaveOutput(char * fnamein, char * comment, BOOL askfirst);
extern void FreeTrainset(void);
extern void FreeDesired(void);
extern void FreeTestset(void);
extern void FreeClassif(void);
extern void FreeOutput(void);
extern void FreeAllData(void);
extern DATA RandomDATA(DATA low,DATA hi);

#endif
