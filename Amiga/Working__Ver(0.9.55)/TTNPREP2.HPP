/*
  ---------------------
  TTNANS:
  TTNPREP2.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Data Preprocessing 2
  Reorder Algorithms
  ---------------------

*/

#ifndef TTNPREP2
#define TTNPREP2

extern int OrderByDistance
		   (BOOL takeaction,
		    DATA **dataset,
		    int rows,
		    int cols,
		    int ordering[], int nfirst);

extern int OrderByDistanceLowMemory
		   (BOOL takeaction,
		    DATA **dataset,
		    int rows,
		    int cols,
		    int ordering[], int nfirst);

extern int OrderDistanceFromCenter
			   (BOOL takeaction,
			    DATA **dataset,
			    int rows,
			    int cols,
			    int ordering[]);

int OrderDistanceFromMean(BOOL takeaction,
			    DATA **dataset,
			    int rows,
			    int cols,
			    int ordering[]);

extern int OrderNoChange(BOOL takeaction,int r, int ordering[]);

extern int OrderArbitrary(BOOL takeaction,int r, int ordering[]);

extern int OrderRandom(BOOL takeaction,int r, int ordering[], BOOL get_num_combs);

extern int OrderSort(BOOL takeaction,DATA **dataset,int rows,int cols,
		     int ordering[],BOOL direction, int selection,
		     BOOL get_num_combs);

extern int OrderAllCombinations(BOOL takeaction,int rows,
				int ordering [], int selection);

#endif
