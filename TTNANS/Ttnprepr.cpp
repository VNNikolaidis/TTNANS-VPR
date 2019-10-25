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

#include "ttndef.h"
#include "ttnpros.h"

#include <string.h>

#include "ttnmath.h"
#include "ttnmemor.h"
#include "ttnpca.h"
#include "ttnpca_2.h"
#include "ttndata1.h"

#include "ttnui.h"

#include <math.h>

/*-----------------------------------------------------------------------*/

void ScaleOnDesMaxValue(char * targetname,
                        DATA ** target,
                        int r,
                        int c,
                        DATA xin)
{
DATA x=xin;
DATA curMaxvalue;
int cc,rr;

if(x<=0.0)x=mrequest_DATA("Enter x.");

mprintf(" \n");
mprintf("Scale: Each item (in %s set) will be divided by the \n",targetname);
mprintf("       maximum value of the column it belongs to,\n");
mprintf("       and then multiplied by x (=");
mprintf(DATAFORMAT,x);
mprintf(").\n");
mprintf("       Result will be in -oo...x range.\n");
mprintf(" \n");

for(cc=0;cc<c;cc++)
 {
 curMaxvalue=ColMaxValue(target,r,c,cc);
 mprintf("Column (descriptor) %d, max value ",cc);
 mprintf(DATAFORMAT,curMaxvalue);
 mprintf(".\n");

 if(curMaxvalue==0)
  {
  mprintf("Warning:Desciptor (column) %d has zero maximum value.\n",cc);
  mprintf("Can not divide, returning large data.\n");
  for(rr=0;rr<r;rr++)
   target[rr][cc]=LARGEDATA;
  }
 else
  {
  for(rr=0;rr<r;rr++)
   target[rr][cc]=target[rr][cc]*x/curMaxvalue;
  }
 }
}

/*-----------------------------------------------------------------------*/

void ScaleOnDesAverage(char * targetname,
                       DATA ** target,
                       int r,
                       int c)
{
DATA curAverage;
int cc,rr;

mprintf(" \n");
mprintf("Scale: Each item (in %s set) will be divided by the \n",targetname);
mprintf("       mean (average) value of the collumn it belongs to.\n");
mprintf("       Note: Not a good scaling method.\n");
mprintf(" \n");

for(cc=0;cc<c;cc++)
 {
 curAverage=0;
 for(rr=0;rr<r;rr++) curAverage=curAverage+target[rr][cc];
 curAverage=curAverage/r;

 mprintf("Column (descriptor) %d, average alue ",cc);
 mprintf(DATAFORMAT,curAverage);
 mprintf(".\n");

 if(curAverage==0)
  {
  mprintf("Warning:Desciptor (column) %d has zero average value.\n",cc);
  mprintf("Can not divide, returning large data.\n");
  for(rr=0;rr<r;rr++)
   target[rr][cc]=LARGEDATA;
  }
 else
  {
  for(rr=0;rr<r;rr++)
   target[rr][cc]=target[rr][cc]/curAverage;
  }
 }
}


/*-----------------------------------------------------------------------*/

void ScaleWithMeanAndSD (char * targetname,
						 DATA ** target,
						 int r,
						 int c)
{
int ir,ic;
DATA * means;
DATA * sds;
DATA * transposedcol;
DATA replaceval;

static bool showinfo = true;

mprintf("Scaling (subtracting Mean and dividing by Standard Deviation)...\n"); 

mhintclear();
mhintf(showinfo,"Scale: Each item x in %s is replaced by :                   \n",targetname);
mhintf(showinfo,"                                                            \n");
mhintf(showinfo,"                                                            \n");
mhintf(showinfo,"                  x - x                                     \n");
mhintf(showinfo,"                       m                                    \n");
mhintf(showinfo,"           x    = _____                                     \n");
mhintf(showinfo,"            new                                             \n");
mhintf(showinfo,"                    s                                       \n");
mhintf(showinfo,"                                                            \n");
mhintf(showinfo,"(x  is the mean, s the standard deviation at x's column.)   \n");
mhintf(showinfo,"  m                                                         \n");
mhintf(showinfo,"                                                            \n");
mhintf(showinfo,"The mean of scaled data is 0 while standard deviation is 1. \n");
mhintf(showinfo,"                                                            \n");
showinfo=false;

if(c!=0)
{
means=(DATA *)MMalloc(c*sizeof(DATA));
sds  =(DATA *)MMalloc(c*sizeof(DATA));
transposedcol=(DATA *)MMalloc(r*sizeof(DATA));

for(ic=0;ic<c;ic++)
 {
 for(ir=0;ir<r;ir++)
  transposedcol[ir]=target[ir][ic];

 means[ic]=Mean(transposedcol,r);
 sds[ic]=StandardDeviation(transposedcol,r,means[ic]);

 mprintf("Scaling column %d   :   \t mean =  %f ,\t standard deviation =  %f .\n",ic,means[ic],sds[ic]);

 if(sds[ic]==(DATA)0)
  {
  mprintf("Note:Standard Deviation (s) at col. %d is 0, cannot divide.\n",ic);
  if(mrequest_yn("Division by 0. Replace result by large number?"))
   {
   mprintf("Result will be replaced by large %s number.\n",DATADESCRI);
   replaceval=LARGEDATA;
   }
  else
   {
   if(mrequest_yn("Replace result by a user defined value?"))
    {
    replaceval=mrequest_DATA("Enter value to replace division by 0 col.");
    mprintf("Result will be replaced by %f.\n",(float)replaceval);
    }
   else
    runerror(ARITHMERR,"Can not divide by zero");
   }
  }
 }

if(TGBL no_error)
 {
 for(ir=0;ir<r;ir++)
  for(ic=0;ic<c;ic++)
   if(sds[ic]!=(DATA)0)
    target[ir][ic]=(target[ir][ic]-means[ic])/sds[ic];
   else
	target[ir][ic]=replaceval;

 /* verify scaling */

 /*
 for(ic=0;ic<c;ic++)
  {
  for(ir=0;ir<r;ir++) transposedcol[ir]=target[ir][ic];
  mprintf("Column %d \n",ic);
  mprintf("mean %f (should be 0).\n",Mean(transposedcol,r));
  mprintf("variance %f (should be 1).\n",Variance(transposedcol,r,Mean(transposedcol,r)));
  }
 */

 /* end of verify */
 }

MFree(transposedcol);
MFree(sds);
MFree(means);
}

mprintf("Scaling Done.\n"); 
}

/*-----------------------------------------------------------------------*/
void MultiplyByNumber(DATA ** target,int rows,int cols,
					  bool asknum, DATA numin)
{
int r;
DATA num=numin;
bool entireset;
int col=-1;
if(asknum)
 {
 num=mrequest_DATA("Number to multiply set with.");
 entireset=mrequest_yn("Multiply entire set by factor?");
 if(!entireset)
  while((col<0)||(col>=cols))
   col=mrequest_int("Column (descriptor) to multiply.");
 }

if(entireset)
 {
 mprintf("Multiplying entire (%d x %d) set contents with ",rows,cols);
 mprintf(DATAFORMAT,num);
 mprintf(".\n");
 for (r=0;r<rows;r++) VectorTimesNumber(target[r],cols,num);
 }
else
 for(r=0;r<rows;r++)
  target[r][col]=target[r][col]*num;
}

/*-----------------------------------------------------------------------*/

void FunctionalExpansionPlacebo()
 {
 mprintf("\nNote:\n");
 mprintf("Since Functional Expansion (FX) expands the dimentionality of a data set, it can not be performed here.  \n");
 mprintf("TTNANS allows to create a new data file with functionaly expanded data via the Data File Utilities option\n");
 mprintf("of the Run/Misc Utilities menu selection.\n");
 mprintf("\n");
 }

/*-----------------------------------------------------------------------*/

void FilterDataPlacebo()
 {
 mprintf("\nNote:\n");
 mprintf("Since Filtering reduces the number of items of a data set, it can not be performed here.  \n");
 mprintf("TTNANS allows to create a new data file with filtered data via the Data File Utilities option\n");
 mprintf("of the Run/Misc Utilities menu selection.\n");
 mprintf("\n");
 }

/*-----------------------------------------------------------------------*/

int FunctionalExpansion(char * targetname, DATA ** target, int r, int c)
 {
 int old_c=c;
 int new_c=6*c;
 DATA * pd;
 int i,j;
 DATA d;

 if(TGBL no_error)
  {
  mprintf("Performing Functional Expansion on %s set (# of columns change from %d to %d)...\n",targetname,old_c,new_c);

  mhintclear();
  mhintf(true,"Pao (Adaptive Pattern Recognition and Neural Networks) discusses.  \n");
  mhintf(true,"this method for enhancing data without adding information to each data vector:\n");
  mhintf(true,"In this case, a subset of a complete set of orthonormal basis functions \n");
  mhintf(true,"is used: for each vector coordinate x: \n");
  mhintf(true,"\n");
  mhintf(true,"sin(x),cos(x),sin(2x),cos(2x),sin(4x) is added. \n");
  mhintf(true,"(expanding the dimentionality by a factor of 6) \n");
  mhintf(true,"\n");
 
  for(i=0;i<r;i++)
  if(TGBL no_error)
   {
   pd=MMalloc1dDATA(new_c);
   if(TGBL no_error)
    {
    for(j=0;j<new_c;j=j+6)
     {
     d=target[i][j/6];
     pd[j  ]=d;
     pd[j+1]=sin(d);
     pd[j+2]=cos(d);
     pd[j+3]=sin(2*d);
     pd[j+4]=cos(2*d);
     pd[j+5]=sin(4*d);
     }
    MFree(target[i]);
    target[i]=pd;
    }
   }
  }
 c=new_c;
 mprintf("Done, size of %s set is %d rows, %d columns.\n",targetname,r,c);
 return c;   /* return new_c */
 }

/*-----------------------------------------------------------------------*/

int ReduceColumns(	char * targetname, DATA ** target, int r, int REF c, int newcolsin)
 {
 char message [100];
 int old_c=c;
 int new_c=newcolsin;
 DATA * pd;
 bool doit = false;
 int i,j;

 if(TGBL no_error)
  {
  strcpy(message,"Reduce the number of columns for ");
  strcat(message,targetname);
  strcat(message," set ?");

  mprintf("Reduce Columns:\n");
  mprintf("(Currently processing %s set, %d rows, %d columns.)\n",targetname,r,c);
 
  if((new_c<1)OR(new_c>old_c))
   {if(mrequest_yn(message)) doit=true;}
  else
   doit=true;

  if(doit)
   {
   while((new_c<1)OR(new_c>old_c)) new_c=mrequest_int("Please enter new column size.");
   if(new_c NEQL old_c)
	{

	mhintclear();
	mhintf(false,"You are attempting to change the column size of a data set.\n");
	mhintf(false,"If the same column size variable is used by other sets, you must\n");
	mhintf(false,"make sure the same column reduction steps are applied to them as well,\n");
	mhintf(false,"or their columns will be in disagreement to the column size.\n");
	mhintf(false,"(In most cases this is done automatically, but this routine does not guarantee it).\n");
	mhintf(false,"Such is the case when a separate training and testing set exists and\n");
	mhintf(false,"the column size of one or the other is reduced (these two sets share the\n");
	mhintf(false,"same column size (input dimention) variable).");

	mprintf("Reducing %s set columns from %d to %d...\n",targetname,old_c,new_c);
	for(i=0;i<r;i++)
	 {
	 if(TGBL no_error)
	  {
	  pd=MMalloc1dDATA(new_c);
	  if(TGBL no_error)
	   {
	   for(j=0;j<new_c;j++) pd[j]=target[i][j];
	   MFree(target[i]);
	   target[i]=pd;
	   }
	  }
	 }
	c=new_c;
	}
   }
  }
 mprintf("Done, size of %s set is %d rows, %d columns.\n",targetname,r,c);
 return c;   /* on success, new_c */
 }

/*-----------------------------------------------------------------------*/

#define SC_ADD 0
#define SC_SUB 1
#define SC_MLT 2
#define SC_DIV 3

void SingleColumnSimpleOperation(char * targetname, DATA ** target,
								 int rows, int cols, int col, unsigned op)
 {
 DATA factor;
 int r;

 if((col<0)OR(col>=cols)) return;
 
 factor = mrequest_DATA ("Please enter constant factor");

 mprintf("For all items of column %d in %s , ",col,targetname);

 switch(op)
  {
  case SC_ADD :	mprintf("adding %f.\n",(float)factor);
				for(r=0;r<rows;r++)
				target[r][col] = target[r][col] + factor;
				break;
  case SC_SUB :	mprintf("subtracting %f.\n",(float)factor);
				for(r=0;r<rows;r++)
				target[r][col] = target[r][col] - factor;
				break;
  case SC_MLT :	mprintf("multipling by %f.\n",(float)factor);
				for(r=0;r<rows;r++)
				target[r][col] = target[r][col] * factor;
				break;
  case SC_DIV :	mprintf("dividing by %f.\n",(float)factor);
				if(factor!=0)
                 {
                 for(r=0;r<rows;r++)
				 target[r][col] = target[r][col] / factor;
                 }
                else
                 mprintf("Cannot divide by 0.\n");
				break;
  default:		break;
  }
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

void SingleColumnScale0to1(char * targetname, DATA ** target,
						   int rows, int cols, int col)
 {
 DATA min,max;
 int r;

 if( (col<0) OR (col>=cols) )
  {
  mprintf("Valid column numbers for %s are 0 to %d, aborted.",targetname,cols-1);
  return;
  }
 
 
 min = LARGEDATA;
 max = -LARGEDATA;
 
 for(r=0;r<rows;r++)
  {
  if(min>target[r][col]) min=target[r][col];
  if(max<target[r][col]) max=target[r][col];
  }
 
 mprintf("For %s, column %d, found min = %f , max = %f.\n",targetname,col,(float)min,(float)max);
 mprintf("Scaling column %d to 0..1 range...\n",col);
 mprintf("x = ((x-(%f))/%f) .\n",(float)min,(float)max-min);

 for(r=0;r<rows;r++)
  target[r][col] = target[r][col] - min;

 max = max - min;

 if(max == 0)
  {
  mprintf("Cannot complete the operation, new max = 0, cannot divide.\n");
  return;
  }

 for(r=0;r<rows;r++)
  target[r][col] = target[r][col] / max;

 mprintf("Done.\n");
 }
 
/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */

void SingleColumnOperationMenu(char * targetname,DATA ** target, int rows, int cols)
 {
 char mtitle[]="Single Column Operation";
 char *menu[]={"0...Go Back - exit this menu",
  			   "1...Add (+) a constant.",
  			   "2...Subtract (-) a constant.",
  			   "3...Multiply (*) a constant.",
  			   "4...Divide by (/) a constant.",
  			   "5...Scale to 0..1 range."
			   };

 int s=-1;
 int col = mrequest_int("Please select column to process (first=0)");
 
 if( (col<0) OR (col>=cols) )
  {
  mprintf("Valid column numbers for %s are 0 to %d, aborted.\n",targetname,cols-1);
  return;
  }

 while(s!=0)
  {
  s=mmenu(mtitle,menu,6,5);
  
  switch(s)
   {
   case 1: SingleColumnSimpleOperation(targetname, target, rows, cols, col, SC_ADD); break;
   case 2: SingleColumnSimpleOperation(targetname, target, rows, cols, col, SC_SUB); break;
   case 3: SingleColumnSimpleOperation(targetname, target, rows, cols, col, SC_MLT); break;
   case 4: SingleColumnSimpleOperation(targetname, target, rows, cols, col, SC_DIV); break;
   case 5: SingleColumnScale0to1(targetname, target, rows, cols, col); break;
   default : break;
   }

  if(s!=0) if(mrequest_yn("Perform another operation on selected column?")==false) s=0; 

  }
 }


/*-----------------------------------------------------------------------*/

void PCA_3(char * indataname, DATA ** indata, unsigned rows, unsigned cols, int preselect)
 {
 mhintclear();
 mhintf(true,"This method first normalizes the data (Scale 05) then calls PCA (07).   \n");
 mhintf(true,"Doing so, it effectively performs a correlation matrix analysis on the  \n");
 mhintf(true,"data set. Note : The eigenvectors are equal to the new variances of the \n");
 mhintf(true,"data when projected to the principal components.                        \n");

 ScaleWithMeanAndSD(indataname,indata,rows,cols);
 PCA(indataname,indata,rows,cols,-1);
 }

void PCA_3LowMemory(char * indataname, DATA ** indata, unsigned rows, unsigned cols, int preselect)
 {
 mhintclear();
 mhintf(true,"This method first normalizes the data (Scale 05) then calls PCA (07).   \n");
 mhintf(true,"Doing so, it effectively performs a correlation matrix analysis on the  \n");
 mhintf(true,"data set. Note : The eigenvectors are equal to the new variances of the \n");
 mhintf(true,"data when projected to the principal components.                        \n");

 ScaleWithMeanAndSD(indataname,indata,rows,cols);
 PCALowMemory(indataname,indata,rows,cols,-1);
 }

/*-----------------------------------------------------------------------*/
/* preselection  < 0 : Show preprocesing menu.                           */
/*               = 0 : No Preprocessing (exit).                          */
/* function returns last processing method selected.                     */

int preprocess(int preselection,
				char * targetname,
				DATA ** target,
				int rows,
				int cols)
{
char message[100]="";

char mtitle[]="Preprocess - Scale";
char *menu[]={"00...No Selection - Exit scale",
			  "01...No Scaling.",
			  "02...Multiply all items by a factor.",
			  "03...Scale on maximum value of each column (descriptor).",
			  "04...Scale on maximum value of each column, then multiply by x.",
			  "05...Scale using mean and standard deviation of each column.",
			  "06...Scale on mean value of each column (descriptor).",
			  "07...PCA Variances-Covariances.",
			  "08...PCA Variances-Covariances, (Lower Memory).",
			  "09...PCA Correlation (Scale(05)+PCA(07), eigenvalues=new variances).",
			  "10...PCA Correlation (Scale(05)+PCA(08), eigenvalues=new variances, Lower Memory).",
			  "11...PCA (Display-only version with more options).",
			  "12...Functional Expansion (Note).",
			  "13...Filter Data (Note).",
			  "14...Single column (descriptor) operations."
			 };

int p,r,s;

p=0;
r=s=preselection;

strcat(message,"Preprocess ");
strcat(message,targetname);
strcat(message," set?");

mprintf("Preprocess-Scale...(%d)\n",s);

while((TGBL no_error)&&(s!=0))
 {
 if(s<0)
  {
  if(mrequest_yn(message))
   s=mmenu(mtitle,menu,15,14);
  else
   s=0;
  }

 switch(s)
   {
   case 0 :break;
   case 1 :break;
   case 2 :MultiplyByNumber(target,rows,cols,true,(DATA)0);
		   break;
   case 3 :ScaleOnDesMaxValue(targetname,target,rows,cols,(DATA)1.0);
		   break;
   case 4 :ScaleOnDesMaxValue(targetname,target,rows,cols,(DATA)0.0);
		   break;
   case 5 :ScaleWithMeanAndSD(targetname,target,rows,cols);
		   break;
   case 6 :ScaleOnDesAverage(targetname,target,rows,cols);
		   break;
   case 7 :PCA(targetname,target,rows,cols,-1);
           TGBL data_set_column_sizes_late_change = true;
		   break;
   case 8 :PCALowMemory(targetname,target,rows,cols,-1);
           TGBL data_set_column_sizes_late_change = true;
		   break;
   case 9 :PCA_3(targetname,target,rows,cols,-1);
           TGBL data_set_column_sizes_late_change = true;
		   break;
   case 10:PCA_3LowMemory(targetname,target,rows,cols,-1);
           TGBL data_set_column_sizes_late_change = true;
		   break;
   case 11 :PCA_2(target,rows,cols,-1);
		   break;
   case 12:FunctionalExpansionPlacebo();
		   break;
   case 13:FilterDataPlacebo();
		   break;
   case 14:SingleColumnOperationMenu(targetname,target,rows,cols);
		   break;
   default:break;
   }

 if(s!=0)
  {
  mprintf("\nPreprocessing/Scaling Done.\n");
  if((s!=0)&&(preselection<1))
   {
   if(p==0)
	{
	message[strlen(message)-1]='\0';
	strcat(message," again?");
	p=1;
	}
   r=s;
   s=-1;
   }
  else
   s=0;
  }
 }
return r;
}

/*-----------------------------------------------------------------------*/

void preprocess_all_data_sets()
{
if(TGBL trainset!=NULL)
 preprocess(-1,"training",TGBL trainset,TGBL trainsetsize,TGBL inputdim);

if(TGBL desired!=NULL)
 preprocess(-1,"desired output",TGBL desired,TGBL trainsetsize,TGBL outputdim);

if((TGBL testset!=NULL)&&(TGBL testset!= TGBL trainset))
 preprocess(-1,"testing",TGBL testset,TGBL testsetsize,TGBL inputdim);

adjust_columns_all_data_sets();
}

/*-----------------------------------------------------------------------*/
