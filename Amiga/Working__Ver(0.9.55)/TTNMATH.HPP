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

extern DATA square_root(DATA x);
extern DATA AbsoluteValue(DATA x);
extern void VectorTimesNumber(DATA * v, int dim, DATA num);
extern unsigned long Factorial(unsigned long x);
extern DATA ColMaxValue(DATA ** target,int r,int c,int tc);
extern DATA Mean (DATA * data, int n);
extern DATA Variance (DATA * data, int n, DATA mean);
extern DATA StandardDeviation (DATA * data, int n, DATA mean);
extern DATA EuclideanDistance(DATA * v1, DATA * v2, int d);
extern void MeanVector(DATA ** table, int r, int c, DATA * mean);
extern DATA dispersion_metric_Rij(DATA ** data,int r,int c,DATA q);
extern DATA Minkowski_Metric(DATA ** S1,int r1,DATA ** S2,int r2,int c,DATA r);
extern int simpleprecisiontest(void);
extern void TestRandom(void);

#endif


