/*
   --------------------
   TTNANS:
   TTNMATH.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   Math and Statistics
   --------------------
*/

#ifndef TTNMATH
#define TTNMATH

#define squared(x) ((x)*(x))

 bool AreEqualVectors(DATA * v1, DATA * v2, int d);
 DATA square_root(DATA x);
 DATA AbsoluteValue(DATA x);
 void VectorTimesNumber(DATA * v, int dim, DATA num);
 unsigned long Factorial(unsigned long x);
 DATA ColMaxValue(DATA ** target,int r,int c,int tc);
 DATA Mean (DATA * data, int n);
 DATA Variance (DATA * data, int n, DATA mean);
 DATA StandardDeviation (DATA * data, int n, DATA mean);
 DATA EuclideanDistance(DATA * v1, DATA * v2, int d);
 void MeanVector(DATA ** table, int r, int c, DATA * mean);
 DATA dispersion_metric_Rij(DATA ** data,int r,int c,DATA q);
 DATA Minkowski_Metric(DATA ** S1,int r1,DATA ** S2,int r2,int c,DATA r);
 int simpleprecisiontest(void);
 void TestRandom(void);

#endif


