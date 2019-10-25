/*
  ---------------------
  TTNANS:
  TTNPREPR.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ----------------------------
  Data Preprocessing (Scaling)
  ----------------------------

*/

#ifndef TTNPREPR
#define TTNPREPR

void ScaleOnDesMaxValue
	       (char * targetname,
			DATA ** target,
			int r,
			int c,
			DATA xin);

void ScaleOnDesAverage
	      (char * targetname,
	       DATA ** target,
	       int r,
	       int c);

void ScaleWithMeanAndSD
		(char * targetname,
		 DATA ** target,
		 int r,
		 int c);

void MultiplyByNumber (DATA ** target,int rows, int cols, bool asknum, DATA numin);
int ReduceColumns(char * targetname, DATA ** target, int r, int REF c, int newcolsin);
int FunctionalExpansion(char * targetname, DATA ** target, int r, int c);
int preprocess(int preselection,char * targetname,DATA ** target, int rows,int cols);
void preprocess_all_data_sets();

#endif

