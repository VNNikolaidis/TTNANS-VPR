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

 void CreateTrainset(void);
 void CreateDesired(void);
 void CreateTestset(void);
 void CreateOutput(void);
 void CreateClassif(void);
 DATA ** AdjustedColumns2dDataSet(char * targetname, DATA ** source, int r, int REF c, int newcolsin);
 void adjust_columns_all_data_sets();
 void Show2dDataSet(DATA ** Set, int rows, int cols, char * title);
 void ShowTrainset(void);
 void ShowDesired(void);
 void ShowTestset(void);
 void ShowClassif(void);
 void ShowOutput(void);
 bool ValidatedDescriptors(int * deslist, int deslistsize, int deslimit);
 bool LoadDataSetWithSelectedColumns(FHANDLE f,   /* input file w/ */
                                    int frows,          /* assumed size  */
                                    int fcols,          /* frows X fcols.*/
                                    DATA ** TargetSet,  /* Put here.     */
                                    int  *  colist,     /* Selected Cols.*/
                                    int  colistsize);   /* num of cols.  */

/*  the next load functions also allocate memory for corresponding sets. */

 void LoadTrainset(char * fnamein,int desnum, int * deslist);
 void LoadDesired(char * fnamein);
 void LoadTestset(char * fnamein,int desnum, int * deslist);

 void SaveClassif(char * fnamein, char * comment, bool askfirst);
 void SaveOutput(char * fnamein, char * comment, bool askfirst);
 void FreeTrainset(void);
 void FreeDesired(void);
 void FreeTestset(void);
 void FreeClassif(void);
 void FreeOutput(void);
 void FreeAllData(void);
 DATA RandomDATA(DATA low,DATA hi);

#endif
