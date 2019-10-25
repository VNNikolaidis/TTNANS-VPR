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

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include <string.h>

#include "TTNMATH.HPP"
#include "TTNMEMOR.HPP"

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

mprintf("\n");
mprintf("Scale: Each item (in %s set) will be divided by the \n",targetname);
mprintf("       maximum value of the column it belongs to,\n");
mprintf("       and then multiplied by x (=");
mprintf(DATAFORMAT,x);
mprintf(").\n");
mprintf("       Result will be in -oo...x range.\n");
mprintf("\n");

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

mprintf("\n");
mprintf("Scale: Each item (in %s set) will be divided by the \n",targetname);
mprintf("       average value of the collumn it belongs to.\n");
mprintf("       Note: Not a good scaling method.\n");
mprintf("\n");

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

static BOOL show_info_smsd = TRUE;

if(show_info_smsd)
 {
 mprintf("\n");
 mprintf("Scale: Each item x in %s is replaced by :       \n",targetname);
 mprintf("                                                           \n");
 mprintf("                                                           \n");
 mprintf("                  x - x                                    \n");
 mprintf("                       m                                   \n");
 mprintf("           x    = _____                                    \n");
 mprintf("            new                                            \n");
 mprintf("                    s                                      \n");
 mprintf("                                                           \n");
 mprintf("(x  is the mean, s the standard deviation at x's column.)  \n");
 mprintf("  m                                                        \n");
 mprintf("\n");
 mprintf("The mean of scaled data is 0 while standard deviation is 1.\n");
 mprintf("\n");
 show_info_smsd=FALSE;
 }

if(c!=0)
{
means=(DATA *)MMalloc(c*sizeof(DATA));
sds=(DATA *)MMalloc(c*sizeof(DATA));
transposedcol=(DATA *)MMalloc(r*sizeof(DATA));

for(ic=0;ic<c;ic++)
 {
 for(ir=0;ir<r;ir++)
  transposedcol[ir]=target[ir][ic];

 means[ic]=Mean(transposedcol,r);
 sds[ic]=StandardDeviation(transposedcol,r,means[ic]);


 if(sds[ic]==(DATA)0)
  {
  mprintf("Note:Standard Deviation (s) at col. %d is 0, cannot divide.\n",ic);
  if(mrequest_yn("Division by 0. Replace result by large number?"))
   mprintf("Result will be replaced by large %s number.\n",DATADESCRI);
  else
   runerror(ARITHMERR,"Can not divide by zero");
  }
 }

if(no_error)
 {
 for(ir=0;ir<r;ir++)
  for(ic=0;ic<c;ic++)
   if(sds[ic]!=(DATA)0)
    target[ir][ic]=(target[ir][ic]-means[ic])/sds[ic];
   else
    target[ir][ic]=LARGEDATA;

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
}

/*-----------------------------------------------------------------------*/
void MultiplyByNumber(DATA ** target,int rows,int cols,
		      BOOL asknum, DATA numin)
{
int r;
DATA num=numin;
BOOL entireset;
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

char *menu[]={"------------------",
              "Preprocess - Scale",
              "------------------",
              "Please Select:",
              "0...No Selection - Exit scale",
              "1...No Scaling.",
              "2...Multiply all items by a number.",
              "3...Scale on largest value of each descriptor.",
              "4...As above (2), then multiply by x.",
              "5...Scale using mean and standard deviation.",
              "6...As above (4), then multiply by x.",
              "7...Scale on average value of each descriptor.",
              "8...As above (6), then multiply by x."
             };

int p,r,s;

p=0;
r=s=preselection;

strcat(message,"Preprocess ");
strcat(message,targetname);
strcat(message," set?");

mprintf("Preprocess-Scale...(%d)\n",s);

while((no_error)&&(s!=0))
 {
 if(s<0)
  {
  if(mrequest_yn(message))
   s=mmenu(menu,13,4,0,8);
  else
   s=0;
  }

 switch(s)
   {
   case 0 :break;
   case 1 :break;
   case 2 :MultiplyByNumber(target,rows,cols,TRUE,(DATA)0);
	   break;
   case 3 :ScaleOnDesMaxValue(targetname,target,rows,cols,(DATA)1.0);
	   break;
   case 4 :ScaleOnDesMaxValue(targetname,target,rows,cols,(DATA)0.0);
	   break;
   case 5 :ScaleWithMeanAndSD(targetname,target,rows,cols);
	   break;
   case 6 :ScaleWithMeanAndSD(targetname,target,rows,cols);
	   MultiplyByNumber(target,rows,cols,TRUE,(DATA)0);
	   break;
   case 7 :ScaleOnDesAverage(targetname,target,rows,cols);
	   break;
   case 8 :ScaleOnDesAverage(targetname,target,rows,cols);
	   MultiplyByNumber(target,rows,cols,TRUE,(DATA)0);
	   break;
   default:break;
   }

 if(s!=0)
  {
  mprintf("Preprocessing/Scaling Done.\n");
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
