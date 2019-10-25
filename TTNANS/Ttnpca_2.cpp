/*
   --------------------
   TTNANS:
   TTNPCA.CPP  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   PCA.
   Modified code.
   (Original code author
    information follows)
   ------------------------
*/

#include "ttndef.h"
#include "ttnmain.h"
#include "ttnerror.h"

#include "ttnui.h"

/*********************************/
/* Principal Components Analysis */
/*********************************/

/*********************************************************************/
/* Principal Components Analysis or the Karhunen-Loeve expansion is a
   classical method for dimensionality reduction or exploratory data
   analysis.  One reference among many is: F. Murtagh and A. Heck,
   Multivariate Data Analysis, Kluwer Academic, Dordrecht, 1987.

   Author:
   F. Murtagh
   Phone:        + 49 89 32006298 (work)
                 + 49 89 965307 (home)
   Earn/Bitnet:  fionn@dgaeso51,  fim@dgaipp1s,  murtagh@stsci
   Span:         esomc1::fionn
   Internet:     murtagh@scivax.stsci.edu
   
   F. Murtagh, Munich, 6 June 1989                                   */   
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIGN(a, b) ( (b) < 0 ? -fabs(a) : fabs(a) )

DATA **matrix(int,int);
DATA * vector(int);
void free_matrix(DATA **,int, int);
void free_vector(DATA *, int);
void corcol(DATA **, int, int, DATA **);
void covcol(DATA **, int, int, DATA **);
void scpcol(DATA **, int, int, DATA **);
void tred2(DATA **, int, DATA *, DATA *);
void tqli(DATA [], DATA [], int, DATA**);

void PCA_2(DATA ** indata, int rows, int cols, int preselect)
{
int  n, m, i, j, k, k2;
DATA **data, **symmat, **symmat2, *evals, *interm;
// DATA in_value;
int option=preselect;

char mtitle[]="   P.C.A.   M e n u  ";
char *menu[]={"0...No more processing - Go to previous menu.",
			  "1...for correlation analysis (recommented).",
			  "2...for variance/covariance analysis.",
			  "3...for SSCP analysis."
			 };


mhintclear();
mhintf(true,"Principal Components Analysis or the Karhunen-Loeve expansion is a\n");
mhintf(true,"classical method for dimensionality reduction or exploratory data\n");
mhintf(true,"analysis.  One reference among many is: F. Murtagh and A. Heck,\n");
mhintf(true,"Multivariate Data Analysis, Kluwer Academic, Dordrecht, 1987.\n");
mhintf(true,"Author:\n");
mhintf(true,"   Phone:        + 49 89 32006298 (work)\n");
mhintf(true,"                 + 49 89 965307 (home)\n");
mhintf(true,"   Earn/Bitnet:  fionn@dgaeso51,  fim@dgaipp1s,  murtagh@stsci\n");
mhintf(true,"   Span:         esomc1::fionn\n");
mhintf(true,"   Internet:     murtagh@scivax.stsci.edu\n");
mhintf(true,"   \n");
mhintf(true,"   F. Murtagh, Munich, 6 June 1989\n");

mprintf("********* Display only, does NOT modify data sets. ******\n");
mprintf("(Adapted code written by F.Murtagh (see hint). Added for comparison purposes.)\n");

 if((preselect<0)OR(preselect>3))
   {   
   option=mmenu(mtitle,menu,4,3);
   if(option==0) return;
   }
  
   n = rows;                       /* # rows */
   m = cols;                       /* # columns */

   mprintf("No. of rows: %d, no. of columns: %d.\n",n,m);

   data = matrix(n, m);  /* Storage allocation for input data */

	for (i = 0; i < n; i++)
	 for (j = 0; j < m; j++)
	   data[i+1][j+1] = indata[i][j];

	/* Check on (part of) input data.*/

    if(mrequest_yn("Show data?"))
     {
	 mprintf(" \n");
	 for (i = 1; i <= n; i++)
	  {
	  for (j = 1; j <= m; j++) mprintf("%7.1f", data[i][j]);
	  mprintf(" \n");
	  }
     }
	mprintf(" \n");

	symmat = matrix(m, m);  /* Allocation of correlation (etc.) matrix */

   /* Look at analysis option; branch in accordance with this. */

	 switch(option)
			 {
		  case 1:
			  mprintf("Analysis of correlations chosen.\n");
			  corcol(data, n, m, symmat);

						  /* Output correlation matrix.
						  for (i = 1; i <= m; i++) {
						   for (j = 1; j <= 8; j++)  {
							mprintf("%7.4f", symmat[i][j]);  }
							mprintf(" \n");  }
						  */
			  break;

		  case 2:
			  mprintf("Analysis of variances-covariances chosen.\n");
			  covcol(data, n, m, symmat);

						  /* Output variance-covariance matrix.
						  for (i = 1; i <= m; i++) {
						  for (j = 1; j <= 8; j++)  {
							mprintf("%7.1f", symmat[i][j]);  }
							mprintf(" \n");  }
						  */
			  break;

		  case 3:
			  mprintf("Analysis of sums-of-squares-cross-products");
			  mprintf(" matrix chosen.\n");
			  scpcol(data, n, m, symmat);

						 /* Output SSCP matrix.
						 for (i = 1; i <= m; i++) {
						  for (j = 1; j <= 8; j++)  {
							mprintf("%7.1f", symmat[i][j]);  }
							mprintf(" \n");  }
						 */
			  break;
		  default:
			  mprintf("Option: %s is invalid.\n",option);
			  mprintf("Returning...\n");
			  break;
		  }

/*********************************************************************
	Eigen-reduction
**********************************************************************/

	/* Allocate storage for dummy and new vectors. */
	evals = vector(m);     /* Storage alloc. for vector of eigenvalues */
	interm = vector(m);    /* Storage alloc. for 'intermediate' vector */
	symmat2 = matrix(m, m);  /* Duplicate of correlation (etc.) matrix */
	for (i = 1; i <= m; i++) {
	 for (j = 1; j <= m; j++) {
	  symmat2[i][j] = symmat[i][j]; /* Needed below for col. projections */
							  }
							 }
	tred2(symmat, m, evals, interm);  /* Triangular decomposition */
	tqli(evals, interm, m, symmat);   /* Reduction of sym. trid. matrix */
	/* evals now contains the eigenvalues,
	   columns of symmat now contain the associated eigenvectors. */

	 mprintf(" \nEigenvalues:\n");
	 for (j = m; j >= 1; j--) {
	   mprintf("%18.5f\n", evals[j]); }
	 mprintf(" \n(Eigenvalues should be strictly positive; limited\n");
	 mprintf("precision machine arithmetic may affect this.\n");
	 mprintf("Eigenvalues are often expressed as cumulative\n");
	 mprintf("percentages, representing the 'percentage variance\n");
	 mprintf("explained' by the associated axis or principal component.)\n");

	 mprintf(" \nEigenvectors:\n");
	 mprintf("(First three; their definition in terms of original vbes.)\n");
	 for (j = 1; j <= m; j++) {
	   for (i = 1; i <= 3; i++)  {
		  mprintf("%12.4f", symmat[j][m-i+1]);  }
		  mprintf(" \n");  }

	 /* Form projections of row-points on first three prin. components. */
	 /* Store in 'data', overwriting original data. */
	 for (i = 1; i <= n; i++) {
	  for (j = 1; j <= m; j++) {
		interm[j] = data[i][j]; }   /* data[i][j] will be overwritten */
		for (k = 1; k <= 3; k++) {
		  data[i][k] = 0.0;
		  for (k2 = 1; k2 <= m; k2++) {
			data[i][k] += interm[k2] * symmat[k2][m-k+1]; }
		}
	 }

	 mprintf(" \nProjections of row-points on first 3 prin. comps.:\n");
	 for (i = 1; i <= n; i++) {
	   for (j = 1; j <= 3; j++)  {
		  mprintf("%12.4f", data[i][j]);  }
		  mprintf(" \n");  }

	 /* Form projections of col.-points on first three prin. components. */
	 /* Store in 'symmat2', overwriting what was stored in this. */
	 for (j = 1; j <= m; j++) {
	  for (k = 1; k <= m; k++) {
		interm[k] = symmat2[j][k]; }  /*symmat2[j][k] will be overwritten*/
		for (i = 1; i <= 3; i++) {
		  symmat2[j][i] = 0.0;
		  for (k2 = 1; k2 <= m; k2++) {
			symmat2[j][i] += interm[k2] * symmat[k2][m-i+1]; }
		  if (evals[m-i+1] > 0.0005)   /* Guard against zero eigenvalue */
			 symmat2[j][i] /= sqrt(evals[m-i+1]);   /* Rescale */
		  else
			 symmat2[j][i] = 0.0;    /* Standard kludge */
		}
	 }

	 mprintf(" \nProjections of column-points on first 3 prin. comps.:\n");
	 for (j = 1; j <= m; j++) {
	   for (k = 1; k <= 3; k++)  {
		  mprintf("%12.4f", symmat2[j][k]);  }
		  mprintf(" \n");  }

/*  free_matrix(data, n, m); */
	free_matrix(symmat, m, m);
	free_matrix(symmat2, m, m);
	free_vector(evals, m);
	free_vector(interm, m);
 }

/**  Correlation matrix: creation  ***********************************/

void corcol(DATA ** data,int n, int m, DATA ** symmat)
/* Create m * m correlation matrix from given n * m data matrix. */
{
DATA eps = 0.005;
DATA x, *mean, *stddev;
int i, j, j1, j2;

/* Allocate storage for mean and std. dev. vectors */

mean = vector(m);
stddev = vector(m);

/* Determine mean of column vectors of input data matrix */

for (j = 1; j <= m; j++)
    {
    mean[j] = 0.0;
    for (i = 1; i <= n; i++)
        {
        mean[j] += data[i][j];
        }
    mean[j] /= (DATA)n;
    }

mprintf(" \nMeans of column vectors:\n");
for (j = 1; j <= m; j++)  {
    mprintf("%7.1f",mean[j]);  }   mprintf(" \n");

/* Determine standard deviations of column vectors of data matrix. */

for (j = 1; j <= m; j++)
    {
    stddev[j] = 0.0;
    for (i = 1; i <= n; i++)
        {
        stddev[j] += (   ( data[i][j] - mean[j] ) *
                         ( data[i][j] - mean[j] )  );
        }
        stddev[j] /= (DATA)n;
        stddev[j] = sqrt(stddev[j]);
        /* The following in an inelegant but usual way to handle
        near-zero std. dev. values, which below would cause a zero-
        divide. */
        if (stddev[j] <= eps) stddev[j] = 1.0;
    }

mprintf(" \nStandard deviations of columns:\n");
for (j = 1; j <= m; j++) { mprintf("%7.1f", stddev[j]); }
mprintf(" \n");

/* Center and reduce the column vectors. */

for (i = 1; i <= n; i++)
    {
    for (j = 1; j <= m; j++)
        {
        data[i][j] -= mean[j];
        x = sqrt((DATA)n);
        x *= stddev[j];
        data[i][j] /= x;
        }
    }

/* Calculate the m * m correlation matrix. */
for (j1 = 1; j1 <= m-1; j1++)
    {
    symmat[j1][j1] = 1.0;
    for (j2 = j1+1; j2 <= m; j2++)
        {
        symmat[j1][j2] = 0.0;
        for (i = 1; i <= n; i++)
            {
            symmat[j1][j2] += ( data[i][j1] * data[i][j2]);
			}
        symmat[j2][j1] = symmat[j1][j2];
        }
    }
    symmat[m][m] = 1.0;

return;

}

/**  Variance-covariance matrix: creation  *****************************/

void covcol(DATA ** data, int n, int m, DATA ** symmat)
/* Create m * m covariance matrix from given n * m data matrix. */
{
DATA *mean;
int i, j, j1, j2;

/* Allocate storage for mean vector */

mean = vector(m);

/* Determine mean of column vectors of input data matrix */

for (j = 1; j <= m; j++)
    {
    mean[j] = 0.0;
    for (i = 1; i <= n; i++)
        {
        mean[j] += data[i][j];
        }
    mean[j] /= (DATA)n;
    }

mprintf(" \nMeans of column vectors:\n");
for (j = 1; j <= m; j++)  {
    mprintf("%7.1f",mean[j]);  }   mprintf(" \n");

/* Center the column vectors. */

for (i = 1; i <= n; i++)
    {
    for (j = 1; j <= m; j++)
        {
        data[i][j] -= mean[j];
        }
    }

/* Calculate the m * m covariance matrix. */
for (j1 = 1; j1 <= m; j1++)
    {
    for (j2 = j1; j2 <= m; j2++)
        {
        symmat[j1][j2] = 0.0;
        for (i = 1; i <= n; i++)
            {
            symmat[j1][j2] += data[i][j1] * data[i][j2];
            }
        symmat[j2][j1] = symmat[j1][j2];
        }
    }

return;

}

/**  Sums-of-squares-and-cross-products matrix: creation  **************/

void scpcol(DATA ** data, int n, int m, DATA ** symmat)
/* Create m * m sums-of-cross-products matrix from n * m data matrix. */
{
int i, j1, j2;

/* Calculate the m * m sums-of-squares-and-cross-products matrix. */

for (j1 = 1; j1 <= m; j1++)
    {
    for (j2 = j1; j2 <= m; j2++)
        {
        symmat[j1][j2] = 0.0;
        for (i = 1; i <= n; i++)
            {
            symmat[j1][j2] += data[i][j1] * data[i][j2];
            }
        symmat[j2][j1] = symmat[j1][j2];
        }
    }

return;

}

/**  Error handler  **************************************************/

void erhand(char err_msg[])
/* Error handler */
{
runerror(999, err_msg);
}

/**  Allocation of vector storage  ***********************************/

DATA *vector(int n)
/* Allocates a DATA vector with range [1..n]. */
{

    DATA *v;

    v = (DATA *) malloc ((unsigned) n*sizeof(DATA));
    if (!v) erhand("Allocation failure in vector().");
    return v-1;

}

/**  Allocation of DATA matrix storage  *****************************/

DATA **matrix(int n, int m)
/* Allocate a DATA matrix with range [1..n][1..m]. */
{
    int i;
	DATA **mat;

    /* Allocate pointers to rows. */
    mat = (DATA **) malloc((unsigned) (n)*sizeof(DATA*));
    if (!mat) erhand("Allocation failure 1 in matrix().");
    mat -= 1;

    /* Allocate rows and set pointers to them. */
    for (i = 1; i <= n; i++)
        {
        mat[i] = (DATA *) malloc((unsigned) (m)*sizeof(DATA));
        if (!mat[i]) erhand("Allocation failure 2 in matrix().");
        mat[i] -= 1;
        }

     /* Return pointer to array of pointers to rows. */
     return mat;

}

/**  Deallocate vector storage  *********************************/

void free_vector(DATA *v, int n)
/* Free a DATA vector allocated by vector(). */
{
   free((char*) (v+1));
}

/**  Deallocate DATA matrix storage  ***************************/

void free_matrix(DATA ** mat, int n, int m)
/* Free a DATA matrix allocated by matrix(). */
{
   int i;

   for (i = n; i >= 1; i--)
	   {
	   free ((char*) (mat[i]+1));
	   }
   free ((char*) (mat+1));
}

/**  Reduce a real, symmetric matrix to a symmetric, tridiag. matrix. */

void tred2(DATA **a, int n, DATA *d, DATA *e)
/* DATA **a, d[], e[]; */
/* Householder reduction of matrix a to tridiagonal form.
   Algorithm: Martin et al., Num. Math. 11, 181-195, 1968.
   Ref: Smith et al., Matrix Eigensystem Routines -- EISPACK Guide
		Springer-Verlag, 1976, pp. 489-494.
		W H Press et al., Numerical Recipes in C, Cambridge U P,
		1988, pp. 373-374.  */
{
int l, k, j, i;
DATA scale, hh, h, g, f;

for (i = n; i >= 2; i--)
	{
	l = i - 1;
	h = scale = 0.0;
	if (l > 1)
	   {
	   for (k = 1; k <= l; k++)
		   scale += fabs(a[i][k]);
	   if (scale == 0.0)
		  e[i] = a[i][l];
	   else
		  {
		  for (k = 1; k <= l; k++)
			  {
			  a[i][k] /= scale;
			  h += a[i][k] * a[i][k];
			  }
		  f = a[i][l];
		  g = f>0 ? -sqrt(h) : sqrt(h);
		  e[i] = scale * g;
		  h -= f * g;
		  a[i][l] = f - g;
		  f = 0.0;
		  for (j = 1; j <= l; j++)
			  {
			  a[j][i] = a[i][j]/h;
			  g = 0.0;
			  for (k = 1; k <= j; k++)
				  g += a[j][k] * a[i][k];
			  for (k = j+1; k <= l; k++)
				  g += a[k][j] * a[i][k];
			  e[j] = g / h;
			  f += e[j] * a[i][j];
			  }
		  hh = f / (h + h);
		  for (j = 1; j <= l; j++)
			  {
			  f = a[i][j];
			  e[j] = g = e[j] - hh * f;
			  for (k = 1; k <= j; k++)
				  a[j][k] -= (f * e[k] + g * a[i][k]);
			  }
		 }
	}
	else
		e[i] = a[i][l];
	d[i] = h;
	}
d[1] = 0.0;
e[1] = 0.0;
for (i = 1; i <= n; i++)
	{
	l = i - 1;
	if (d[i])
	   {
	   for (j = 1; j <= l; j++)
		   {
		   g = 0.0;
		   for (k = 1; k <= l; k++)
			   g += a[i][k] * a[k][j];
		   for (k = 1; k <= l; k++)
			   a[k][j] -= g * a[k][i];
		   }
	   }
	   d[i] = a[i][i];
	   a[i][i] = 1.0;
	   for (j = 1; j <= l; j++)
		   a[j][i] = a[i][j] = 0.0;
	}
}

/**  Tridiagonal QL algorithm -- Implicit  **********************/

void tqli(DATA d[],DATA e[], int n, DATA **z)
{
int m, l, iter, i, k;
DATA s, r, p, g, f, dd, c, b;

for (i = 2; i <= n; i++)
	e[i-1] = e[i];
e[n] = 0.0;
for (l = 1; l <= n; l++)
    {
    iter = 0;
    do
      {
      for (m = l; m <= n-1; m++)
          {
		  dd = fabs(d[m]) + fabs(d[m+1]);
          if (fabs(e[m]) + dd == dd) break;
          }
          if (m != l)
             {
             if (iter++ == 30) erhand("No convergence in TLQI.");
             g = (d[l+1] - d[l]) / (2.0 * e[l]);
             r = sqrt((g * g) + 1.0);
             g = d[m] - d[l] + e[l] / (g + SIGN(r, g));
             s = c = 1.0;
             p = 0.0;
             for (i = m-1; i >= l; i--)
                 {
                 f = s * e[i];
                 b = c * e[i];
                 if (fabs(f) >= fabs(g))
					{
                    c = g / f;
                    r = sqrt((c * c) + 1.0);
                    e[i+1] = f * r;
                    c *= (s = 1.0/r);
                    }
                 else
                    {
					s = f / g;
                    r = sqrt((s * s) + 1.0);
                    e[i+1] = g * r;
                    s *= (c = 1.0/r);
                    }
                 g = d[i+1] - p;
                 r = (d[i] - g) * s + 2.0 * c * b;
                 p = s * r;
                 d[i+1] = g + p;
                 g = c * r - b;
                 for (k = 1; k <= n; k++)
                     {
                     f = z[k][i+1];
                     z[k][i+1] = s * z[k][i] + c * f;
                     z[k][i] = c * z[k][i] - s * f;
                     }
				 }
                 d[l] = d[l] - p;
                 e[l] = g;
                 e[m] = 0.0;
             }
          }  while (m != l);
      }
 }

