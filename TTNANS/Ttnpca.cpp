/*
   --------------------
   TTNANS:
   TTNPCA.CPP  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   PCA.
   Original code
   ------------------------
*/

#include "math.h"

#include "ttndef.h"
#include "ttnmain.h"
#include "ttnerror.h"

#include "tmatrix.h"
#include "tmatrixvirtual.h"

/*********************************/
/* Principal Components Analysis */
/*********************************/

/*********************************************************************/
/* Principal Components Analysis or the Karhunen-Loeve expansion is a
   classical method for dimensionality reduction or exploratory data
   analysis.  One reference among many is: F. Murtagh and A. Heck,
   Multivariate Data Analysis, Kluwer Academic, Dordrecht, 1987.     */
/*********************************************************************/

#define SIGN(a, b) ( (b) < 0 ? -fabs(a) : fabs(a) )

void PCA(char * indataname, DATA ** indata, unsigned rows, unsigned cols, int preselect)
{

mprintf("\n");
mprintf("Principal Components Analysis (PCA) or the Karhunen-Loeve expansion.\n");
mprintf("--------------------------------------------------------------------\n");

static bool showinfo = true;
mhintclear();
mhintf(showinfo,"PCA is a classical method for dimensionality reduction or exploratory data analysis.\n");
mhintf(showinfo,"PC coefficients define a set of orthogonal vectors. The first PC has the \n");
mhintf(showinfo,"largest variance of any linear combination of the descriptors (variables)\n");
mhintf(showinfo,"in the data set. The second PC has the largest variance of any linear combination\n");
mhintf(showinfo,"orthogonal to the first. The third has the largest variance of any linear combination\n");
mhintf(showinfo,"orthogonal to the first two, etc.\n");
mhintf(showinfo,"References: \n");
mhintf(showinfo,"- F. Murtagh and A. Heck, Multivariate Data Analysis, Kluwer Academic, Dordrecht, 1987.\n");
mhintf(showinfo,"- M.R.Anderberg, Cluster Analysis for Applications, p.109, 1973.\n");
mhintf(showinfo,"NOTE: This analysis is based on Anderberg, variance-covariance, and is scale-dependent.\n\n");
mhintf(showinfo,"\n");
showinfo = false;

unsigned i,j,k;
DATA buffer;

CTmatrix <DATA> X (indata,rows,cols,"Data matrix (local)"/*,true*/);
CTvector <DATA> mean (cols, 0);

//CTmatrix <DATA> S (cols,cols,0,"Variance-Covariance Matrix"/*,true*/);

CTmatrix <float> evec (cols,cols,0,"Eigenvectors (matrix)"/*,true*/);
CTvector <float> eval (cols,0);

mprintf("\nStep 1.  : Determine Variance-Covariance Matrix S.\n\n");
mprintf("\nStep 1.0 : Find mean of each variable (column).\n\n");

for(i=0;i<cols;i++)
 {
 buffer=0;
 for(j=0;j<rows;j++)
  buffer = buffer + X.at(j,i);
 mean.at(i) = buffer / (rows);
 }

mprintf("Means for each column (descriptor):\n");mean.show();mprintf("\n");

//
//   S = (X*X_transposed)/m , where m is X's number of rows.
//

mprintf("\nStep 1.1 : Compute Variance-Covariance Matrix S (%d x %d symmetric and positive semidefinite (eigenvalues >= 0)).\n\n",cols,cols);

/*

// Computing S via the Andeberg formula follows... 
 
for(i=0;i<cols;i++)
for(k=0;k<cols;k++)
 {
 buffer=0.0;
 for(j=0;j<rows;j++)
  {
  buffer = buffer + ( (X[j][i]-mean.at(i)) * (X[j][k]-mean.at(k)) );
  }
 S.at(k,i)=buffer/rows;
 }

*/

// Computing S via the Andeberg description of steps taken follows...

mprintf("Subtracting means (per column)...\n");

for(i=0;i<X.rows();i++)
for(k=0;k<X.cols();k++)
 {
 X.at(i,k) = X.at(i,k) - mean.at(k);
 }

CTmatrix <DATA> XT = X;
XT.transpose();
CTmatrix <DATA> S = (XT*X)/rows;

// Patch Start : eliminates precision problems when checking for matrix symmetry.

for(i=0;i<S.rows();i++)
for(j=i;j<S.cols();j++)
 {
 if (fabs(S.at(i,j)-S.at(j,i))>0.000001)
  mprintf("\nS not symmetric! (difference of elements (%d,%d) and (%d,%d) > 0.000001. \n",i,j,j,i);
 S.at(j,i)=S.at(i,j);
 }

strcpy(S.title(),"Variance-Covariance Matrix");

// Patch End.

S.show();

mprintf("\nStep 2.  : Find vector(s) of coefficients.\n\n");

S.eigen(eval,evec);

k=0;

mprintf("\nStep 3.  : Project data (row,per record) to eigenvectors.\n\n");
mprintf("There are %d eigenvalues (eigenvectors)\n",S.rows());
mprintf("(the %d eigenvalues are : ",S.rows());

float evals_tot=0;
float cur_evals_tot=0;
for(i=0;i<eval.cols();i++)
 {
 mprintf("%.4f ",(float)eval.at(i));
 evals_tot=evals_tot+(float)eval.at(i);
 if(eval.at(i)>0) k++;
 }
mprintf(").\n\n");
mprintf("The ratios of sums for using the n largest eigenvalues (a degree-of-fit measure (Anderberg p.109)) are:\n");
for(i=0;i<eval.cols();i++)
 {
 cur_evals_tot+=(float)eval.at(i);
 mprintf("for n = %d (%d principal components), fit = %.4f .\n",i+1,i+1,cur_evals_tot/evals_tot);
 }
mprintf("The number of non-zero (positive) eigenvalues is %d.\n\n",k);

unsigned p=S.rows()+1;
while(p>S.rows()) p=mrequest_int("Create how many principal components? (0=exit)");

if(p==0) return;

mprintf("Creating %d principal components (using %d largest eigenvalues)...\n",p,p);

CTmatrix <DATA> pcamatrix (rows,p,0,"Result (temp PCA Matrix)",true);

for(j=0;j<p;j++)
 for(i=0;i<rows;i++)
  for(k=0;k<cols;k++)
   pcamatrix.at(i,j) = pcamatrix.at(i,j) + (X.at(i,k) * evec.at(k,j));

mprintf("\nStep 4.  : Replacing original data set (%s)...\n\n",indataname);
if(mrequest_yn("Continue? - Replace data set entries?"))
 {
 mprintf("Reseting original set (%s) to zeros...\n",indataname);

 for(i=0;i<rows;i++)
 for(k=0;k<cols;k++)
   indata[i][k]=(DATA)0.0;

 mprintf("Copying %d columns (remaining columns are set to zeros)...\n",p);

 for(i=0;i<rows;i++)
 for(k=0;k<p;k++)
   indata[i][k]=(DATA)pcamatrix.at(i,k);
 }
else
 mprintf("Original set (%s) was not modified.\n",indataname); 
}


/*********************************************************************/
/* Principal Components Analysis or the Karhunen-Loeve expansion is a
   classical method for dimensionality reduction or exploratory data
   analysis.  One reference among many is: F. Murtagh and A. Heck,
   Multivariate Data Analysis, Kluwer Academic, Dordrecht, 1987.     */
/*********************************************************************/


DATA function_add_x_y(unsigned x,unsigned y)
 {
 return((DATA)x+y);
 }

void PCALowMemory (char * indataname, DATA ** indata, unsigned rows, unsigned cols, int preselect)
{
warning("NOT FINISHED!!!");

mprintf("\n");
mprintf("Principal Components Analysis (PCA) or the Karhunen-Loeve expansion.\n");
mprintf("--------------------------------------------------------------------\n");
mprintf("(Less memory consuming version)\n");

static bool showinfo = true;
mhintclear();
mhintf(showinfo,"PCA is a classical method for dimensionality reduction or exploratory data analysis.\n");
mhintf(showinfo,"PC coefficients define a set of orthogonal vectors. The first PC has the \n");
mhintf(showinfo,"largest variance of any linear combination of the descriptors (variables)\n");
mhintf(showinfo,"in the data set. The second PC has the largest variance of any linear combination\n");
mhintf(showinfo,"orthogonal to the first. The third has the largest variance of any linear combination\n");
mhintf(showinfo,"orthogonal to the first two, etc.\n");
mhintf(showinfo,"References: \n");
mhintf(showinfo,"- F. Murtagh and A. Heck, Multivariate Data Analysis, Kluwer Academic, Dordrecht, 1987.\n");
mhintf(showinfo,"- M.R.Anderberg, Cluster Analysis for Applications, p.109, 1973.\n");
mhintf(showinfo,"NOTE: This analysis is based on Anderberg, variance-covariance, and is scale-dependent.\n\n");
mhintf(showinfo,"\n");
showinfo = false;

unsigned i,j,k;
DATA buffer;

CTmatrix <DATA> X (indata,rows,cols,"Data matrix (local)"/*,true*/);
CTvector <DATA> mean (cols, 0);

//CTmatrix <DATA> S (cols,cols,0,"Variance-Covariance Matrix"/*,true*/);

CTmatrix <float> evec (cols,cols,0,"Eigenvectors (matrix)"/*,true*/);
CTvector <float> eval (cols,0);

mprintf("\nStep 1.  : Determine Variance-Covariance Matrix S.\n\n");
mprintf("\nStep 1.0 : Find mean of each variable (column).\n\n");

for(i=0;i<cols;i++)
 {
 buffer=0;
 for(j=0;j<rows;j++)
  buffer = buffer + X.at(j,i);
 mean.at(i) = buffer / (rows);
 }

//
//   S = (X*X_transposed)/m , where m is X's number of rows.
//

mprintf("\nStep 1.1 (skipped): Compute Variance-Covariance Matrix S (%d x %d symmetric and positive semidefinite (eigenvalues >= 0)).\n\n",cols,cols);

// Computing S via the Andeberg formula follows... 

CTmatrixVirtual<DATA,&function_add_x_y> S (cols,cols,"Variance-Covariance Matrix (virtual matrix)");

/* 
for(i=0;i<cols;i++)
for(k=0;k<cols;k++)
 {
 buffer=0.0;
 for(j=0;j<rows;j++)
  {
  buffer = buffer + ( (X.at(j,i)-mean.at(i)) * (X.at(j,k)-mean.at(k)) );
  }
 S.at(k,i)=buffer/rows;
 }
*/

mprintf("\nStep 2.  : Find vector(s) of coefficients.\n\n");

S.eigen(eval,evec);

k=0;

mprintf("\nStep 3.  : Project data (row,per record) to eigenvectors.\n\n");
mprintf("There are %d eigenvalues (eigenvectors)\n",S.rows());
mprintf("(the %d eigenvalues are : ",S.rows());

float evals_tot=0;
float cur_evals_tot=0;
for(i=0;i<eval.cols();i++)
 {
 mprintf("%.4f ",(float)eval.at(i));
 evals_tot=evals_tot+(float)eval.at(i);
 if(eval.at(i)>0) k++;
 }
mprintf(").\n\n");
mprintf("The ratios of sums for using the n largest eigenvalues (a degree-of-fit measure (Anderberg p.109)) are:\n");
for(i=0;i<eval.cols();i++)
 {
 cur_evals_tot+=(float)eval.at(i);
 mprintf("for n = %d (%d principal components), fit = %.4f .\n",i+1,i+1,cur_evals_tot/evals_tot);
 }
mprintf("The number of non-zero (positive) eigenvalues is %d.\n\n",k);

unsigned p=S.rows()+1;
while(p>S.rows()) p=mrequest_int("Create how many principal components? (0=exit)");

if(p==0) return;

mprintf("Creating %d principal components (using %d largest eigenvalues)...\n",p,p);

CTmatrix <DATA> pcamatrix (rows,p,0,"Result (temp PCA Matrix)",true);

for(j=0;j<p;j++)
 for(i=0;i<rows;i++)
  for(k=0;k<cols;k++)
   pcamatrix.at(i,j) = pcamatrix.at(i,j) + (X.at(i,k) * evec.at(k,j));

mprintf("\nStep 4.  : Replacing original data set (%s)...\n\n",indataname);
if(mrequest_yn("Continue? - Replace data set entries?"))
 {
 mprintf("Reseting original set (%s) to zeros...\n",indataname);

 for(i=0;i<rows;i++)
 for(k=0;k<cols;k++)
   indata[i][k]=(DATA)0.0;

 mprintf("Copying %d columns (remaining columns are set to zeros)...\n",p);

 for(i=0;i<rows;i++)
 for(k=0;k<p;k++)
   indata[i][k]=(DATA)pcamatrix.at(i,k);
 }
else
 mprintf("Original set (%s) was not modified.\n",indataname); 
}



