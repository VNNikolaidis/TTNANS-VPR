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

extern void ScaleOnDesMaxValue
		       (char * targetname,
			DATA ** target,
			int r,
			int c,
			DATA xin);

extern void ScaleOnDesAverage
		      (char * targetname,
		       DATA ** target,
		       int r,
		       int c);

extern void ScaleWithMeanAndSD
			(char * targetname,
			 DATA ** target,
			 int r,
			 int c);

extern void MultiplyByNumber
			(DATA ** target,int rows,
			 int cols,BOOL asknum, DATA numin);

extern int preprocess
	       (int preselection,
		char * targetname,
		DATA ** target,
		int rows,
		int cols);

#endif

