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

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include <math.h>

#include "TTNMEMOR.HPP"

#define squared(x) ((x)*(x))

/*-----------------------------------------------------------------------*/
DATA square_root(DATA x)
{
return (DATA)sqrt((DATA)x);
}

/*-----------------------------------------------------------------------*/

DATA AbsoluteValue(DATA x)
{
if(x>=0)
 return x;
return (DATA) -x;
}

/*-----------------------------------------------------------------------*/
void VectorTimesNumber(DATA * v, int dim, DATA num)
{
int i;
for(i=0;i<dim;i++) v[i]=v[i]*num;
}

/*-----------------------------------------------------------------------*/

unsigned long Factorial(unsigned long x)
{
if(x<1) return 0;
if(x==1) return x;
return (x * Factorial (x-1));
}

/*-----------------------------------------------------------------------*/
/* Find max value of column tc on an r x c DATA array.                   */

DATA ColMaxValue(DATA ** target,
		 int r,
		 int c,
		 int tc)
{
DATA maxvalue=SMALLDATA;
int rr;

if(tc>=c)
 runerror(DATASTERR,"");
else
 {
 for(rr=0;rr<r;rr++)
  if(target[rr][tc]>maxvalue)maxvalue=target[rr][tc];
 }
return(maxvalue);
}

/*-----------------------------------------------------------------------*/
/* find mean value for "n" element DATA array "data".                    */

DATA Mean (DATA * data, int n)
{
int i;
DATA mean=0;

if(n!=0)
 {
 for(i=0;i<n;i++) mean+=data[i];
 mean=mean/n;
 return mean;
 }
else
 {
 runerror(ARITHMERR,"Mean:Division by 0 columns.Large value returned.\n");
 return LARGEDATA;
 }
}

/*-----------------------------------------------------------------------*/
/* find variance  for "n" element DATA array "data" with "mean"=mean.    */

DATA Variance (DATA * data, int n, DATA mean)
{
int i;
DATA V=0;

if(n!=0)
 {
 for(i=0;i<n;i++)
  V+=squared(data[i]-mean);

 V=V/n;
 return V;
 }
else
 {
 runerror(ARITHMERR,"Variance:Division by 0 items.Large value returned.\n");
 return LARGEDATA;
 }
}

/*-----------------------------------------------------------------------*/
/* find standard deviation for "n" element DATA "data" with "mean"=mean. */

DATA StandardDeviation (DATA * data, int n, DATA mean)
{return (DATA)sqrt((double)Variance(data,n,mean));}

/*-----------------------------------------------------------------------*/
/* Euclidian Distance of two vertices v1,v2 in d-dimentional space.      */

DATA EuclideanDistance(DATA * v1, DATA * v2, int d)
{
DATA r1=0.0;
int i;

for(i=0;i<d;i++)
 r1=r1+squared(v1[i]-v2[i]);

return(DATA)sqrt(r1);
}

/*------------------------------------------------------------------------*/
/* Mean vector in 2-D array table (size rxc) put in mean (size c).        */

void MeanVector(DATA ** table, int r, int c, DATA * mean)
{
int i,j;

if(r!=0)
 {
 for(j=0;j<c;j++)
  {
  mean[j]=(DATA)0;
  for(i=0;i<r;i++)
   mean[j]=mean[j]+table[i][j];
  mean[j]=mean[j]/r;
  }
 }
else
 runerror(ARITHMERR,"Mean Vector:Division by 0 rows.");
}

/*------------------------------------------------------------------------*/
/* if q=2 this is the Standard Deviation of vectors v1,v2 (of size s).     */

DATA dispersion_metric_Rij(DATA ** data,int r,int c,DATA q)
{
DATA d=0;
DATA *Mean;
int i;

if((r!=0)&&(q!=(DATA)0))
 {
 Mean=(DATA *)MMalloc(c*sizeof(DATA));
 MeanVector(data,r,c,Mean);

 for(i=0;i<r;i++)
  d=d+pow(EuclideanDistance(data[i],Mean,c),q);
 d=d/r;

 d=pow(d,1/q);

 MFree(Mean);
 }
else
 runerror(ARITHMERR,"Dispersion Metric:Division by 0 (rows or q).Returning 0.");

return d;
}

/*-------------------------------------------------------------------------*/
/* A metric of separation between 2 clusters, returns a "distance" (which  */
/* is eucledian if r=2) between the mean vectors of two sets S1 (r1 x c),  */
/* S2 (r2 x c).                                                            */


DATA Minkowski_Metric(DATA ** S1,int r1,DATA ** S2,int r2,int c,DATA r)
{
DATA * mean1;
DATA * mean2;

int a;
DATA m=0;

if(r!=(DATA)0)
 {
 mean1=(DATA *)MMalloc(c*sizeof(DATA));
 mean2=(DATA *)MMalloc(c*sizeof(DATA));

 MeanVector(S1,r1,c,mean1);
 MeanVector(S2,r2,c,mean2);

 for(a=0;a<c;a++)
  m=m+pow((mean1[a]-mean2[a]),r);

 m=pow(m,1/r);

 MFree(mean2);
 MFree(mean1);
 }
else
 runerror(ARITHMERR,"Minkowski Metric:Division by 0.Returning 0.");
return m;
}

/*-----------------------------------------------------------------------*/

int simpleprecisiontest(void)
{
int i=0;
DATA d=(DATA)1;
while(d!=(DATA)0)
 {
 i++;
 d=d/(DATA)10;
 }
return i;
}

/*-------------------------------------------------------------------------*/

#define CELLS   10

void TestRandom(void)
{
int runs=30000;

DATA ra[CELLS];
int r;
int i;

for(i=0;i<CELLS;i++)
 ra[i]=0;

for(i=0;i<runs;i++)
 {
 r=random(CELLS);
 ra[r]=ra[r]+(DATA)1;
 }

mprintf("\n");
mprintf("Test Hits (function:random(%d),Runs:%d,no randomize).\n",CELLS,runs);
mprintf("---------------------------------------------------------\n");
mprintf("\n");

mplot_bar(ra,CELLS,(DATA)runs);
}

/*-------------------------------------------------------------------------*/


