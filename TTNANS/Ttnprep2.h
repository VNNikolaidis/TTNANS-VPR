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

 int OrderByDistance
		   (bool takeaction,
		    DATA **dataset,
		    int rows,
		    int cols,
		    int ordering[], int nfirst);

 int OrderByDistanceLowMemory
		   (bool takeaction,
		    DATA **dataset,
		    int rows,
		    int cols,
		    int ordering[], int nfirst);

 int OrderByDistanceStartingMeanLowMemory
		   (bool takeaction,
		    DATA **dataset,
		    int rows,
		    int cols,
		    int ordering[], int nfirst);

 int OrderDistanceFromCenter
			   (bool takeaction,
			    DATA **dataset,
			    int rows,
			    int cols,
			    int ordering[]);

 int OrderDistanceFromMean(bool takeaction,
			    DATA **dataset,
			    int rows,
			    int cols,
			    int ordering[]);

 int OrderNoChange(bool takeaction,int r, int ordering[]);

 int OrderArbitrary(bool takeaction,int r, int ordering[]);

 int OrderRandom(bool takeaction,int r, int ordering[], bool get_num_combs);

 int OrderSort(bool takeaction,DATA **dataset,int rows,int cols,
		     int ordering[],bool direction, int selection,
		     bool get_num_combs);

 int OrderAllCombinations(bool takeaction,int rows,
				int ordering [], int selection);

#endif
