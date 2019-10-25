/*---------------------------------------------------------------------------*/
/*------------------------ Eigenvectors - Eigenvalues -----------------------*/
/*          Selected "Numerical Recipes in C" Routines, Modified.            */
/*---------------------------------------------------------------------------*/

#include <math.h>

#include "ttndef_s.h"
#include "ttnerror.h"

#include "tmatrix.h"

/*
template <class D> class CTvector;
template <class D> class CTmatrix;
*/

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define MAX_ITER 50

#define ROTATE(p1,p2,p3,p4,p5) { g = p1.at(p2,p3); h = p1.at(p4,p5); p1.at(p2,p3)=g-s*(h+g*tau); p1.at(p4,p5)=h+s*(g-h*tau); }

/*
Jakobi Routine:

Computes all eigenvalues and eigenvectors of a real SYMMETRIC matrix a[1..n][1..n].
On output, elements of a above the diagonal are destroed. d[1..n] returns the eigenvalues of a.
v[1..n][1..n] id a matrix whose columns contain, on output, the normalized eigenvectors of a.
nrot returns the number of Jacobi rotations that were required.
*/

void jacobi(CTmatrix<float> REF a, int n, CTvector<float> REF d, CTmatrix<float> REF v,int *nrot)
{
int j,iq,ip,i;
float tresh,theta,tau,t,sm,s,h,g,c;
CTvector<float> b (n,0);
CTvector<float> z (n,0);

mprintf("Running Jakobi routine...\n");
mprintf("(Computes all eigenvalues and eigenvectors of a real symmetric matrix (n x n).)\n"); 

// initialize to identity matrix

for (ip=0;ip<n;ip++)
 {
 for (iq=0;iq<n;iq++) v.at(ip,iq)=0.0;
 v.at(ip,ip)=1.0;
 }

// initialize b and d to the diagonal of a.

for (ip=0;ip<n;ip++)
 {
 b.at(ip)=d.at(ip)=a.at(ip,ip);
 z.at(ip)=0.0;
 }

*nrot=0;
for (i=0;i<=MAX_ITER;i++) 
 {
 sm=0.0;
 for (ip=0;ip<n;ip++)
  {
  for (iq=ip+1;iq<n;iq++) 
   sm += fabs(a.at(ip,iq));
  }
 if (sm == 0.0)			// check for normal return which relies 
  {						// on quadratic convergence to machine underflow.
  return;
  }

 if (i < 4)	
  tresh=0.2*sm/(n*n);	// first 3 sweeps.
 else
  tresh=0.0;			// thereafter.


for (ip=1;ip<=n-1;ip++)
 {
 for (iq=ip+1;iq<=n;iq++)
  {
  g=100.0*fabs(a.at(ip-1,iq-1));
  if (i > 4 && (float)(fabs(d.at(ip-1))+g) == (float)fabs(d.at(ip-1))		// after 4 sweeps, skip rotation if the off-diagonal element is small.
      && (float)(fabs(d.at(iq-1))+g) == (float)fabs(d.at(iq-1)))
   a.at(ip-1,iq-1)=0.0;
  else
   if (fabs(a.at(ip-1,iq-1)) > tresh)
    {
	h=d.at(iq-1)-d.at(ip-1);
	if ((float)(fabs(h)+g) == (float)fabs(h))
	 t=(a.at(ip-1,iq-1))/h;											// t = 1/(2è)
	else
     {
	 theta=0.5*h/(a.at(ip-1,iq-1));
	 t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
	 if (theta < 0.0) t = -t;
     }
	c=1.0/sqrt(1.0+t*t);
	s=t*c;
	tau=s/(1.0+c);
	h=t*a.at(ip-1,iq-1);
	z.at(ip-1) -= h;
	z.at(iq-1) += h;
	d.at(ip-1) -= h;
	d.at(iq-1) += h;
	a.at(ip-1,iq-1)=0.0;

	for (j=1;j<=ip-1;j++)
	 ROTATE(a,j-1,ip-1,j-1,iq-1)
   
    for (j=ip+1;j<=iq-1;j++)
	 ROTATE(a,ip-1,j-1,j-1,iq-1)

	for (j=iq+1;j<=n;j++)
	 ROTATE(a,ip-1,j-1,iq-1,j-1)

	for (j=1;j<=n;j++)
	 ROTATE(v,j-1,ip-1,j-1,iq-1)

	++(*nrot);
	}
   }
  }
 for (ip=1;ip<n;ip++)
  {
  b.at(ip-1) += z.at(ip-1);
  d.at(ip-1)=b.at(ip-1);
  z.at(ip-1)=0.0;
  }
 }

/*
for (ip=0;ip<n-1;ip++)
 {
 for (iq=ip+1;iq<n;iq++)
  {
  g=100.0*fabs(a.at(ip,iq));
  if ((i > 4) &&
      (float)(fabs(d.at(ip))+g) == (float)fabs(d.at(ip)) &&		// after 4 sweeps, skip rotation if the off-diagonal element is small.
      (float)(fabs(d.at(iq))+g) == (float)fabs(d.at(iq)))
   a.at(ip,iq)=0.0;
  else
   if (fabs(a.at(ip,iq)) > tresh)
    {
	h=d.at(iq)-d.at(ip);
	if ((float)(fabs(h)+g) == (float)fabs(h))
	 t=(a.at(ip,iq))/h;											// t = 1/(2è)
	else
     {
	 theta=0.5*h/(a.at(ip,iq));
	 t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
	 if (theta < 0.0) t = -t;
     }
	c=1.0/sqrt(1.0+t*t);
	s=t*c;
	tau=s/(1.0+c);
	h=t*a.at(ip,iq);
	z.at(ip) -= h;
	z.at(iq) += h;
	d.at(ip) -= h;
	d.at(iq) += h;
	a.at(ip,iq)=0.0;

mprintf("--- ip = %d , iq = %d --- \n",ip,iq);

	for (j=0;j<ip-1;j++)
	 ROTATE(a,j,ip,j,iq)
   
    for (j=ip+1;j<iq-1;j++)
	 ROTATE(a,ip,j,j,iq)

	for (j=iq+1;j<n;j++)
	 ROTATE(a,ip,j,iq,j)

	for (j=0;j<n;j++)
	 ROTATE(v,j,ip,j,iq)

	++(*nrot);
	}
   }
  }
 for (ip=0;ip<n;ip++)
  {
  b.at(ip) += z.at(ip);
  d.at(ip) =  b.at(ip);
  z.at(ip) =  0.0;
  }
 }
*/

runerror(ARITHMERR,"Too many iterations in routine JACOBI");
}

#undef ROTATE

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void eigsrt(CTvector<float> REF d, CTmatrix<float> REF v, int n)
{
int k,j,i;
float p;

mprintf("Sorting Eigenvalues - Eigenvectors...\n");

for (i=0;i<n;i++)
 {
 k=i;
 p=d.at(i);
 for (j=i+1;j<n;j++) 
  if (d.at(j) >= p)
   {
   k=j;
   p=d.at(k);
   }
 if (k != i)
  {
  d.at(k)=d.at(i);
  d.at(i)=p;
  for (j=0;j<n;j++)
   {
   p=v.at(j,i);
   v.at(j,i)=v.at(j,k);
   v.at(j,k)=p;
   }
  }
 }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void sorted_eigen(CTmatrix<float> REF matrix,
                  CTmatrix<float> REF e_vecs,
                  CTvector<float> REF e_vals,
                  unsigned int np)
{
int i,j,nrot;

mprintf("Determining and sorting Eigenvectors - Eigenvalues...\n");

jacobi(matrix,np,e_vals,e_vecs,&nrot);

#ifdef _DEBUG
 mprintf("\n");
 e_vals.show();
 mprintf("\n");
 e_vecs.show();
 mprintf("\n");
#endif

eigsrt(e_vals,e_vecs,np);

#ifdef _DEBUG
 mprintf("\n");
 e_vals.show();
 mprintf("\n");
 e_vecs.show();
 mprintf("\n");
#endif

if(mrequest_yn("Show eigenvectors - eigenvalues (sorted)"))
 {
 mprintf("- Sorted eigenvectors: -\n");
 for (i=0;i<np;i++)
  {
  mprintf("\n eigenvalue %3d = %12.6f\n",i,e_vals.at(i));
  mprintf(" eigenvector:\n[");
  for (j=0;j<np;j++) mprintf("%12.6f",e_vecs.at(j,i));
  mprintf("   ]\n");
  }
 }
}

/*---------------------------------------------------------------------------*/
