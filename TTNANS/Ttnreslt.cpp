/*
   --------------------
   TTNANS:
   TTNRESLT.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------
   Result Evaluation Module
   ------------------------
*/

#include "ttndef.h"
#include "ttnpros.h"

#include <string.h>

#include "ttnclafi.h"
#include "ttnmemor.h"
#include "ttnfname.h"
#include "ttnmath.h"
#include "ttnbandx.h"
#include "ttnaxum.h"
#include "ttnfile.h"     /* added for Quick Report File generation. - */

#include "ttnui.h"
#include "tmatrix.h"

char    QuickRepFname[FILENAMELENGTH];
FHANDLE QuickRepFile;

/*-------------------------------------------------------------------------*/

DATA number_of_empty_cluster_files(char * fname,int runnum)
{
char fnamebuffer[FILENAMELENGTH];
int found=0;
int empty=0;
int nonempty;
int id=0;

mprintf("Classes (run %d): ",runnum);

if(!is_class_file(fname))
 {
 mprintf("Bad Filename. Returning no empty classes.\n");
 return 0;
 }

if(TGBL no_error)
 {
 class_n_filename(fname,id,fnamebuffer);

 while(FileExists(fnamebuffer))
  {
  found++;
  id++;
  class_n_filename(fname,id,fnamebuffer);
  }

 mprintf("found %d, ",found);

 nonempty=number_of_nonempty_class_files(fname);

 empty=found-nonempty;

 mprintf("empty %d.\n",empty);
 }
return (DATA)empty;
}
/*-------------------------------------------------------------------------*/

DATA sum_of_squared_errors_on_set(char * fname,int runnum)
{
FHANDLE f;
char fnamebuffer[FILENAMELENGTH];

int setsnum   =0;
int vectornum =0;
int vectorsize=0;
int processed =0;
int oldvectorsize=0;
int i;

DATA * mean;
DATA ** data;
DATA temp;

DATA sumofsquarederrors=0;

static bool showinfo=true;

mprintf("\nCalculating Sum of Squared errors. (run # %d)\n",runnum);

if(!is_class_file(fname))
 {
 mprintf("Bad Filename. Returning large number.\n");
 return LARGEDATA;
 }

 mhintclear();
 mhintf(showinfo,"Sum of Squared Errors (J): A performance index \n");
 mhintf(showinfo,"for clustering algorithms calculated as follows\n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"             N                                 \n");
 mhintf(showinfo,"              c                                \n");
 mhintf(showinfo,"           _____  _____                        \n");
 mhintf(showinfo,"           \\      \\                          \n");
 mhintf(showinfo,"            \\      \\     ||        || 2       \n");
 mhintf(showinfo,"      J =    >      >    || X - M  ||          \n");
 mhintf(showinfo,"            /      /     ||      j ||          \n");
 mhintf(showinfo,"           /____  /____                        \n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"            j=1   X in S                       \n");
 mhintf(showinfo,"                        j                      \n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"where N  the number of clusters,               \n");
 mhintf(showinfo,"       c                                       \n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"      S  the set of vectors in cluster j,      \n");
 mhintf(showinfo,"       j                                       \n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"     ||A-B|| the Euclidian Distance of A,B and,\n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"      M  the mean vector for cluster j defined:\n");
 mhintf(showinfo,"       j                                       \n");
 mhintf(showinfo,"          _____                                \n");
 mhintf(showinfo,"          \\                                   \n");
 mhintf(showinfo,"       1   \\                                  \n");
 mhintf(showinfo," M  =  -    >  X    with N = num. of S vectors.\n");
 mhintf(showinfo,"  j    N   /              j           j        \n");
 mhintf(showinfo,"        j /____                                \n");
 mhintf(showinfo,"                                               \n");
 mhintf(showinfo,"          X in S                               \n");
 mhintf(showinfo,"                j                              \n");
 mhintf(showinfo,"\n");
 mhintf(showinfo,"See: Tou&Gonzalez,Pat.Rec.Principles (K-Means).\n");
 mhintf(showinfo,"\n");
 showinfo=false;


mprintf(" \n");
mprintf("Opening class (cluster) file set (*.F0,*.F1... or *.X0,*.X1...).\n");

if(TGBL no_error)
 {
 class_n_filename(fname,setsnum,fnamebuffer);

 while(FileExists(fnamebuffer))
  {
  GetDataFileDims(fnamebuffer,&vectornum,&vectorsize);

  if((vectornum>0)&&(vectorsize>0))
   {
   if((vectorsize!=oldvectorsize)&&(processed>0))
	mprintf("Warning: Vector Size Changed!\n");

   data=MMalloc2dDATA(vectornum,vectorsize);
   mean=(DATA *)MMalloc(vectorsize*sizeof(DATA));

   f=OpenInFile(fnamebuffer);

   if(Read2dDATA(f,data,vectornum,vectorsize))
    {
    CloseFile(f);

    /* Put mean vector of data in mean */
    MeanVector(data,vectornum,vectorsize,mean);

    /* distance of points in cluster from mean. */

    for(i=0;i<vectornum;i++)
     {
     temp=EuclideanDistance(mean,data[i],vectorsize);
     temp=temp*temp;
	 sumofsquarederrors=sumofsquarederrors+temp;
     }

    MFree(mean);
    MFree2dDATA(data,vectornum);
    oldvectorsize=vectorsize;
	processed++;
    }
   }
  setsnum++;
  mprintf("Processed Set %s.\n",fnamebuffer);
  class_n_filename(fname,setsnum,fnamebuffer);
  }
 mprintf("Files (clusters):");
 mprintf("found %d, processed %d, empty %d.\n",setsnum,processed,setsnum-processed);
 mprintf("--------------------------------------------------------------------------------\n\n");
 mprintf("SSE = ");
 mprintf(DATAFORMAT,sumofsquarederrors);
 mprintf(".\n");
 mprintf("--------------------------------------------------------------------------------\n\n");
 return sumofsquarederrors;
 }
return LARGEDATA;
}

/*-------------------------------------------------------------------------*/

DATA sum_of_squared_errors_on_set_scaled(char *fname,int runnum)
{
char tempf[FILENAMELENGTH];
DATA r=-1;
static bool ask_to_keep_scaled_files=true;
static bool keep_scaled_files;

if(is_class_file(fname))
 {
 mprintf("\nProcessing Sum_of_Squared_Errors (SSE) criteria.\n");

 if(runnum==0)
  create_scaled_classification_files(fname,true);
 else
  create_scaled_classification_files(fname,false);

 scaled_class_n_filename(fname,0,tempf);

 r=sum_of_squared_errors_on_set(tempf,runnum);
 if(ask_to_keep_scaled_files)
  {
  keep_scaled_files=mrequest_yn("SSE: Keep scaled Class files (_*.*)?");
  ask_to_keep_scaled_files=false;
  }
 if(!keep_scaled_files)
  remove_scaled_classification_files(fname);
 }
else
 {
 mprintf("Selected filename is not in valid class format.\n");
 mprintf("(Returning Sum of squared errors =");
 mprintf(DATAFORMAT,r);
 mprintf(").\n");
 }
return r;
}

/*-------------------------------------------------------------------------*/

DATA Rij_on_set(char * fname, int runnum)
{
int N;                     /* number of (non-empty) clusters (class files) */
int i,j;

static DATA q=-1;
static DATA r=-1;

DATA ***Cluster;                            /* Each class file stored here */
int  *  vectornum;                          /* vectors in each class file. */
int     vectorsize;                         /* vector dimention (unique)   */


DATA *  S;                              /* Dispersion Measure (per class). */
DATA ** M;                              /* Minkowski Metric (class pair)   */
DATA ** R;                              /* Rij values.                     */
int  *  index;                          /* loaded class vs class-file-name.*/

DATA Rbuf=-1;

static bool showinfo=true;

mprintf("\nCalculating Rij Cluster Separation Measure.\n");

if(!is_class_file(fname))
 {
 mprintf("Bad Filename. Returning large number.\n");
 return LARGEDATA;
 }

 mhintclear();
 mhintf(showinfo," \n");
 mhintf(showinfo,"            S + S          \n");
 mhintf(showinfo,"             i   j         \n");
 mhintf(showinfo,"     R   = ________        \n");
 mhintf(showinfo,"      ij      M            \n");
 mhintf(showinfo,"               ij          \n");
 mhintf(showinfo," \n");
 mhintf(showinfo,"S = dispersion measure for cluster. (q=2 => standard deviation)\n");
 mhintf(showinfo,"M = Minkowski inter-cluster metric. (r=1 => City-block distance of means)\n");
 mhintf(showinfo,"                                    (r=2 => Euclidean distance of means)\n");
 mhintf(showinfo," \n");
 mhintf(showinfo,"For information on Rij see:\n");
 mhintf(showinfo,"A Cluster Separation Measure, D.L.Davies, D.W.Bouldin. \n");
 mhintf(showinfo,"IEEE Transactions on Pattern Analysis and Machine Inteligence,\n");
 mhintf(showinfo,"Vol.PAM1-No2.1979.\n");
 mhintf(showinfo," \n");
 showinfo=false;

if ((runnum==0)||(q<0))
 while(q<0) q=mrequest_DATA("Select q (for dispersion):");

if ((runnum==0)||(r<0))
 while(r<0) r=mrequest_DATA("Select r (for Minkowski metric):");

mprintf("(q=");
mprintf(DATAFORMAT,q);
mprintf(",r=");
mprintf(DATAFORMAT,r);
mprintf(").\n");

N=number_of_nonempty_class_files(fname);

if(N<1)
 {
 mprintf("Warning: No valid class files. Returning large value.\n");
 return LARGEDATA;
 }

if(N==1)
 {
 mprintf("Warning: One class file found, Rij Undefined, Returning large value.\n");
 return LARGEDATA;
 }

/* at this point N>=2 */

S=(DATA *)MMalloc(N*sizeof(DATA));
M=MMalloc2dDATA(N,N);
R=MMalloc2dDATA(N,N);

for(i=0;i<N;i++)
 for(j=0;j<N;j++)
  {
  M[i][j]=0;
  R[i][j]=-1;
  }

if((TGBL no_error))
 {
 if(N==load_all_nonempty_class_files(fname,&Cluster,&vectornum,&vectorsize,&index))
  {

  /* Calculate Dispersion Measures */

  mprintf("Calculating Dispersions...\n");

  for(i=0;i<N;i++)
   S[i]=dispersion_metric_Rij(Cluster[i],vectornum[i],vectorsize,q);

  mprintf("Calculating Minkowski Metrics...\n");

  for(i=0;i<N;i++)
   for(j=i+1;j<N;j++)
    M[i][j]=M[j][i]=Minkowski_Metric(Cluster[i],vectornum[i],Cluster[j],vectornum[j],vectorsize,r);

  mprintf("Calculating Rij Table...\n");

  for(i=0;i<N;i++)
   for(j=i+1;j<N;j++)
    if(M[i][j]==0)
     {
     mprintf("Warning M[%d][%d] is zero. R[&d][&d]=R[%d][%d] set to a large value\n",i,j,i,j,j,i);
	 R[i][j]=R[j][i]=LARGEDATA;
     }
    else
     R[i][j]=R[j][i]=(S[i]+S[j])/M[i][j];

  mprintf(" \n");
  mprintf("        Rij Matrix :\n");
  mprintf("        ------------\n");
  for(i=0;i<N;i++)
   {
   mprintf("[ ");
   for(j=0;j<N;j++)
    {
    mprintf(DATAFORMAT,R[i][j]);
    mprintf(" ");
    }
   mprintf("]\n");
   }
  mprintf(" \n");

  for(i=0;i<N;i++)                       /* to save space we will re-use S */
   S[i]=-1;

  for(i=0;i<N;i++)
   {
   Rbuf=-1;
   for(j=0;j<N;j++)
    if(R[i][j]>Rbuf)Rbuf=R[i][j];
   S[i]=Rbuf;
   }

  Rbuf=0;
  for(i=0;i<N;i++)
   Rbuf=Rbuf+S[i];
  Rbuf=Rbuf/N;

  unload_class_files(N,&Cluster,&vectornum,&index);
  }
 MFree2dDATA(R,N);
 MFree2dDATA(M,N);
 MFree(S);
 }

mprintf("(Rij run number %d).\n\n",runnum);
 mprintf("--------------------------------------------------------------------------------\n\n");
mprintf("R = ");
mprintf(DATAFORMAT,Rbuf);
mprintf(".\n");
 mprintf("--------------------------------------------------------------------------------\n\n");
return Rbuf;
}

/*-------------------------------------------------------------------------*/

DATA Rij_on_set_scaled(char *fname,int runnum)
{
char tempf[FILENAMELENGTH];
DATA r=-1;
static bool ask_to_keep_scaled_files=true;
static bool keep_scaled_files;

if(is_class_file(fname))
 {
 mprintf("\nProcessing Rij criteria.\n");

 if(runnum==0)
  create_scaled_classification_files(fname,true);
 else
  create_scaled_classification_files(fname,false);

 scaled_class_n_filename(fname,0,tempf);

 r=Rij_on_set(tempf,runnum);
 if(ask_to_keep_scaled_files)
  {
  keep_scaled_files=mrequest_yn("Rij: Keep scaled Class files (_*.*)?");
  ask_to_keep_scaled_files=false;
  }
 if(!keep_scaled_files)
  remove_scaled_classification_files(fname);
 }
else
 {
 mprintf("Selected filename is not in valid class format.\n");
 mprintf("(Returning Rij =");
 mprintf(DATAFORMAT,r);
 mprintf(").\n");
 }
return r;
}

/*-------------------------------------------------------------------------*/
// returns number of non-empty class files

DATA sizes_of_class_files(char *classfname_in, int unused = 0)
 {
 char classfname [FILENAMELENGTH];
 int  i=0;
 int  r,c;
 DATA n=0;

 mprintf("\nReporting Class Sizes (%s) : \n",classfname_in);

 class_n_filename(classfname_in,i,classfname);

 while(FileExists(classfname))
	{
    if(IsEmptyFile(classfname))
     {
     mprintf("File %s:\t 0 X 0 (contains no records.)\n",classfname);
	 }
    else
     {
     GetDataFileDims(classfname,&r,&c);
	 mprintf("File %s:\t %d X %d (rows X cols).\n",classfname,r,c);
     n++;
     }
	i++;
	class_n_filename(classfname,i,classfname);
    }
 mprintf("\n");
 return n;
 }

/*-------------------------------------------------------------------------*/

DATA stats_on_set(char * fname,int runnum)
{
FHANDLE f;
char fnamebuffer[FILENAMELENGTH];

int setsnum   =0;
int vectornum =0;
int vectorsize=0;
int processed =0;
int oldvectorsize=0;
int r,c;
bool first_time_in=true;

DATA * min;
DATA * max;
DATA * mean;
DATA * stdev;
DATA * transposed_column;
DATA ** data;

DATA temp;

DATA * gmean;
DATA * gmin;
DATA * gmax;
int gitems=0;

mprintf("\nCalculating Simple Statistics. (run # %d)\n",runnum);

if(!is_class_file(fname))
 {
 mprintf("Bad Filename, aborting.\n");
 return 0;
 }

mprintf(" \n");
mprintf("Opening class (cluster) file set (*.F0,*.F1... or *.X0,*.X1...).\n");

if(TGBL no_error)
 {
 class_n_filename(fname,setsnum,fnamebuffer);

 while(FileExists(fnamebuffer))
  {
  GetDataFileDims(fnamebuffer,&vectornum,&vectorsize);

  if((vectornum>0)&&(vectorsize>0))
   {
   if((vectorsize!=oldvectorsize)&&(processed>0))
    mprintf("Warning: Vector Size Changed!\n");

   data =MMalloc2dDATA(vectornum,vectorsize);
   min  =(DATA *)MMalloc(vectorsize*sizeof(DATA));
   max  =(DATA *)MMalloc(vectorsize*sizeof(DATA));
   mean =(DATA *)MMalloc(vectorsize*sizeof(DATA));
   stdev=(DATA *)MMalloc(vectorsize*sizeof(DATA));	// Standard Deviation per column
   transposed_column=MMalloc1dDATA(vectornum);

   for(c=0;c<vectorsize;c++)
    {
	mean[c]=0;
    min[c]=LARGEDATA;
    max[c]=-LARGEDATA;
    }

   if(first_time_in)
	{
    gmean=(DATA *)MMalloc(vectorsize*sizeof(DATA));
    gmin =(DATA *)MMalloc(vectorsize*sizeof(DATA));
    gmax =(DATA *)MMalloc(vectorsize*sizeof(DATA));
    gitems = 0;
    for(c=0;c<vectorsize;c++)
     {
     gmean[c]=0;
     gmin[c]=LARGEDATA;
     gmax[c]=-LARGEDATA;
     }
    first_time_in=false;
    }

   f=OpenInFile(fnamebuffer);

   if(Read2dDATA(f,data,vectornum,vectorsize))
    {
    CloseFile(f);

	/* Put mean vector of data in mean */
    MeanVector(data,vectornum,vectorsize,mean);

    for(c=0;c<vectorsize;c++)
     {
     for(r=0;r<vectornum;r++)
      {
	  temp=data[r][c];
      transposed_column[r]=temp;
      if(temp>max[c]) max[c]=temp;
      if(temp<min[c]) min[c]=temp;
      if(temp>gmax[c]) gmax[c]=temp;
      if(temp<gmin[c]) gmin[c]=temp;
      gmean[c]=gmean[c]+temp;
      }
     stdev[c]=StandardDeviation(transposed_column, vectornum, mean[c]);
     }

    gitems+=vectornum;

    mprintf("\nStats for %s (%d rows, %d columns) : \n",fnamebuffer,vectornum,vectorsize);

	mprintf("\nMin :\t");
    for(c=0;c<vectorsize;c++)
     {
     mprintf("(%d) ",c);
     mprintf(DATAFORMAT,min[c]);
     mprintf(" \t");
	 }
    mprintf(" (Minimum Value)");

    mprintf("\nMax :\t");
    for(c=0;c<vectorsize;c++)
     {
     mprintf("(%d) ",c);
     mprintf(DATAFORMAT,max[c]);
     mprintf(" \t");
     }
    mprintf(" (Maximum Value)");

    mprintf("\nMean:\t");
    for(c=0;c<vectorsize;c++)
     {
     mprintf("(%d) ",c);
     mprintf(DATAFORMAT,mean[c]);
     mprintf(" \t");
     }
    mprintf(" (Average)");

    mprintf("\nStDev:\t");
    for(c=0;c<vectorsize;c++)
     {
     mprintf("(%d) ",c);
     if(stdev[c]==LARGEDATA) mprintf("DIV0");
     else mprintf(DATAFORMAT,stdev[c]);
     mprintf(" \t");
     }
    mprintf(" (Standard Deviation)");

    mprintf("\nCoefV:\t");
    for(c=0;c<vectorsize;c++)
     {
     mprintf("(%d) ",c);
     if(mean[c]==0) mprintf("DIV0");
     else mprintf("%.2f%%",(stdev[c]/mean[c])*100);
     mprintf("\t");
     }
    mprintf(" (Coefficient of Variation)");

    mprintf("\n");

    MFree(transposed_column);
    MFree(stdev);
    MFree(mean);
    MFree(max);
    MFree(min);
    MFree2dDATA(data,vectornum);
    oldvectorsize=vectorsize;
    processed++;
    }
   }
  setsnum++;
  class_n_filename(fname,setsnum,fnamebuffer);
  }

 if(gitems NEQL 0)
  {
  mprintf("\n--------------------------------------------------------------------------------\n");

  mprintf("Stats for Entire Set (%d vectors (records,items,events)) : \n",gitems);

  mprintf("\nGlobal Min :\t");
  for(c=0;c<vectorsize;c++)
   {
   mprintf("(%d) ",c);
   mprintf(DATAFORMAT,gmin[c]);
   mprintf(" \t");
   }

  mprintf("\nGlobal Max :\t");
  for(c=0;c<vectorsize;c++)
   {
   mprintf("(%d) ",c);
   mprintf(DATAFORMAT,gmax[c]);
   mprintf(" \t");
   }

  mprintf("\nGlobal Mean:\t");
  for(c=0;c<vectorsize;c++)
   {
   mprintf("(%d) ",c);
   mprintf(DATAFORMAT,(gmean[c]/gitems));
   mprintf(" \t");
   }

  }

 MFree(gmax);
 MFree(gmin);
 MFree(gmean);

 mprintf("\n");
 mprintf("--------------------------------------------------------------------------------\n");
 mprintf("Files (clusters):");
 mprintf("found %d, processed %d, empty %d.\n",setsnum,processed,setsnum-processed);
 mprintf("--------------------------------------------------------------------------------\n\n");
 return (DATA) setsnum;
 }

return 0;
}

/*-------------------------------------------------------------------------*/

DATA bin_counts_on_set(char * fname,int runnum)
{
char fnamebuffer[FILENAMELENGTH];

int setsnum   =0;
int processed =0;
int ucol,unumbins;
DATA umin, umax; 
DATA binsize,d;
CTmatrix <DATA> data (1,1,"Temporary data storage",true);
unsigned r,bin;
bool done;
int countitems = 0;

mprintf("\nCalculating Bin Counts. (run # %d)\n",runnum);

if(!is_class_file(fname))
 {
 mprintf("Bad Filename, aborting.\n");
 return 0;
 }

strcpy(fnamebuffer,fname);

ucol = mrequest_int("Please select column (first = 0, negative = exit)");

if(ucol < 0)
 {
 mprintf("Aborted.\n");
 return 0;
 }

umin = mrequest_DATA("Select minimum value for all bins");
umax = mrequest_DATA("Select maximum value for all bins");

if(umin >= umax)
 {
 mprintf("%f >= %f , aborting.\n",(float)umin,(float)umax);
 return 0;
 }

unumbins = mrequest_int("Select number of bins");

if(unumbins <= 0)
 {
 mprintf("Must be greater than 0, aborting.\n");
 return 0;
 }

CTvector <DATA> lobinlimit (unumbins+2,0);
CTvector <DATA> hibinlimit (unumbins+2,0);
CTvector <int>  lbins    (unumbins+2,0);
CTvector <int>  gbins    (unumbins+2,0);

binsize = (umax - umin)/unumbins;

d=umin;
lobinlimit.at(0)=-LARGEDATA;
for(bin=1;bin<unumbins+2;bin++)
 {
 lobinlimit.at(bin)=d;
 d=d+binsize;
 }

d=umin;
for(bin=0;bin<unumbins+1;bin++)
 {
 hibinlimit.at(bin)=d;
 d=d+binsize;
 }
hibinlimit.at(bin)=LARGEDATA;

mprintf("Number of bins = %d, bin size = %f.\n",unumbins,(float)binsize);
mprintf(" \n");
mprintf("Opening class (cluster) file set (based on %s):\n",fnamebuffer);

if(TGBL no_error)
 {
 mprintf("\nLimits:\n");
 mprintf("L_>=: ");
 lobinlimit.show("\t");
 mprintf("\n");
 mprintf("H__<: ");
 hibinlimit.show("\t");
 mprintf("\n\n");
  
 while((FileExists(fnamebuffer)) AND (TGBL no_error))
  {
  if(NOT IsEmptyFile(fnamebuffer))
   {
   data.load(fnamebuffer,true);
   lbins.reset(0);
   
   for(r=0;r<data.rows();r++)
    {
    done = false; 
    d = data.at(r,ucol);

    for(bin=0;(bin<unumbins+1)AND(NOT done);bin++)
     if(d < lobinlimit.at(bin+1))
      {
      lbins.at(bin) = lbins.at(bin) + 1;
      gbins.at(bin) = gbins.at(bin) + 1;
      done = true;
      }
    if(NOT done)
      {
      lbins.at(bin) = lbins.at(bin) + 1;
      gbins.at(bin) = gbins.at(bin) + 1;
      done = true;
      }
     countitems++;
     }
    
   mprintf("@#%d: ",setsnum);
   lbins.show("\t");
   mprintf("\n"); 
   processed ++;
   }

  setsnum++;
  class_n_filename(fname,setsnum,fnamebuffer);
  }


 mprintf("\n@All: ",setsnum);
 gbins.show("\t");
 mprintf("\n\nProcessed %d rows (records).\n",countitems); 

 mprintf("--------------------------------------------------------------------------------\n");
 mprintf("Files (clusters):");
 mprintf("found %d, processed %d, empty %d.\n",setsnum,processed,setsnum-processed);
 mprintf("--------------------------------------------------------------------------------\n\n");
 return (DATA) setsnum;
 }
 
return 0;
}

/*-------------------------------------------------------------------------*/

DATA all_criteria_scaled_with_quick_report(char *fname,int runnum)
{
DATA cv;
int nnempty;

if(FileOpenOK(QuickRepFile))
 {
 WriteString(QuickRepFile,"(File:");
 WriteString(QuickRepFile,fname);
 WriteString(QuickRepFile,",run #");
 WriteInt(QuickRepFile,runnum);
 WriteString(QuickRepFile,") Non_Empty : ");
 nnempty=number_of_nonempty_class_files(fname);
 cv=(DATA)nnempty;
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile," Empty : ");
 cv=number_of_empty_cluster_files(fname,runnum);
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile," SSE : ");
 cv=sum_of_squared_errors_on_set_scaled(fname,runnum);
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile,"  Rij : ");
 cv=Rij_on_set_scaled(fname,runnum);
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile," .\n");
 return (DATA)runnum;
 }
return (DATA)-1;
}


/*-------------------------------------------------------------------------*/

DATA all_criteria_with_quick_report(char *fname,int runnum)
{
DATA cv;
int nnempty;

if(FileOpenOK(QuickRepFile))
 {
 WriteString(QuickRepFile,"(File:");
 WriteString(QuickRepFile,fname);
 WriteString(QuickRepFile,",run #");
 WriteInt(QuickRepFile,runnum);
 WriteString(QuickRepFile,") Non_Empty : ");
 nnempty=number_of_nonempty_class_files(fname);
 cv=(DATA)nnempty;
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile," Empty : ");
 cv=number_of_empty_cluster_files(fname,runnum);
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile," SSE : ");
 cv=sum_of_squared_errors_on_set(fname,runnum);
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile,"  Rij : ");
 cv=Rij_on_set(fname,runnum);
 WriteDATA(QuickRepFile,cv);
 WriteString(QuickRepFile," .\n");
 return (DATA)runnum;
 }
return (DATA)-1;
}

/*-------------------------------------------------------------------------*/
// this was written in a hurry!

void Compare_Classifs(void)
{

int * c1;
char c1_fname [FILENAMELENGTH];
int c1_rows,c1_cols;
int c1_max_class=-1;
FHANDLE c1_fh;

int * c2;
char c2_fname [FILENAMELENGTH];
int c2_rows,c2_cols;
int c2_max_class=-1;
FHANDLE c2_fh;

int ** xc;

int i,j;

mhintclear();
mhintf(true,"Warning: Take this as a suggestion only!       \n");
mhintf(true,"-----------------------------------------------\n");
mhintf(true,"Two classifications performed on the same data \n");
mhintf(true,"may have created clusters that are similar.    \n");
mhintf(true,"This compares them, finding items in both.     \n");
mhintf(true," \n");
mhintf(true,"Note: Displayed results are biased towards the \n");
mhintf(true,"      first file (how it compares to the 2nd). \n");

if(mrequest_yn("Proceed with the comparison?"))
 {
 GetFilename("Select 1st classification file to compare.",c1_fname,"*.cla",false);
 GetFilename("Select 2nd classification file to compare.",c2_fname,"*.cla",false);

 c1_rows=c1_cols=c2_rows=c2_cols=0;

 if(TGBL no_error)
  {
  GetDataFileDims(c1_fname, &c1_rows, &c1_cols);
  GetDataFileDims(c2_fname, &c2_rows, &c2_cols);

  if(c1_rows!=c2_rows)
   {
   mprintf("Compare Classifs Warning: Classification files are of different sizes.\n");
   mprintf("(Are you sure they both come from classification of the same data?.)\n");
   mprintf("Only the first %d items of both files will be compared.\n",min(c1_rows,c2_rows));
   }

  if((c1_cols!=1)OR(c2_cols!=1))
   mprintf("Compare Classifs Error: Classification files should have only one column!\n");
  else
   {
   // Malloc and Read .cla files

   c1=(int *)MMalloc(c1_rows*sizeof(int));
   c2=(int *)MMalloc(c2_rows*sizeof(int));

   if(TGBL no_error)
	{

	c1_fh=OpenInFile(c1_fname);
	SeekFirstDATAinFile(c1_fh,false);
	for(i=0;i<c1_rows;i++)
	 {
	 c1[i]=(int)ReadDATA(c1_fh);
	 if(c1[i]>c1_max_class) c1_max_class=c1[i];
	 }
	CloseFile(c1_fh);
	mprintf("Read %d class tags from %s, maximum class is %d.\n",c1_rows,c1_fname,c1_max_class);

	c2_fh=OpenInFile(c2_fname);
	SeekFirstDATAinFile(c2_fh,false);
	for(i=0;i<c2_rows;i++)
	 {
	 c2[i]=(int)ReadDATA(c2_fh);
	 if(c2[i]>c2_max_class) c2_max_class=c2[i];
	 }
	CloseFile(c2_fh);
	mprintf("Read %d class tags from %s, maximum class is %d.\n",c2_rows,c2_fname,c2_max_class);

	// Now see how the classifications of first file fall into the second

	int c1_classes = c1_max_class+1;
	int c2_classes = c2_max_class+1;

	xc=(int **)MMalloc(c1_classes*sizeof(int *));
	for(i=0;i<c1_classes;i++)
	 {
	 xc[i]=(int *)MMalloc(c2_classes*sizeof(int));
	 for(j=0;j<c2_classes;j++)
	  xc[i][j]=0;
	 }

	for(i=0;i<(min(c1_rows,c2_rows));i++)
	 {
	 (xc [c1[i]] [c2[i]]) +=  1;
	 }

	mprintf(" \n");
	mprintf(" Results : \n");
	mprintf(" \n");

	int locmax,locmaxpos,cl_size;
	for(i=0;i<c1_classes;i++)
	 {
	 cl_size=0;
	 locmax=-1;
	 locmaxpos=-1;
	 for(j=0;j<c2_classes;j++)
	  {
	  mprintf("%d\t",xc[i][j]);
	  if(xc[i][j]>locmax)
	   {
	   locmax=xc[i][j];
	   locmaxpos=j;
	   }
	  }
	 if(locmax==0)
	  mprintf(" => cl.%d of %s is NOT like any %s class ",i,c1_fname,c2_fname);
	 else
	  mprintf(" => cl.%d of %s is most like cl.%d of %s ",i,c1_fname,locmaxpos,c2_fname);

	 // now calculate size of class i to find the percentage of the most-like class.
	 cl_size=0;
	 for(j=0;j<c1_rows;j++)
	  if(c1[j]==i) cl_size++;
	 if(cl_size==0)
	  mprintf("(empty).\n");
	 else
	  mprintf("( %d items out of %d, or %f percent ).\n",locmax,cl_size,((float)locmax/cl_size)*100);
	 }

	for(i=0;i<c1_classes;i++)
	 MFree(xc[i]);
	MFree(xc);
   }

   MFree(c2);
   MFree(c1);
   }
  }
 }
}

/*-------------------------------------------------------------------------*/

void result_evaluation_menu(void)
{
char fname [FILENAMELENGTH];
char fname2[FILENAMELENGTH];

int msel=-1;
char mtitle[]="Results Evaluation Menu";
char *menu[]={
		  "00...Go Back.",
		  "01...Reconstruct class files from classification indexes (*.cla).",
		  "02...Reconstruct class files, on batch results.",
		  "03...Create modified class files.",
		  "04...Create modified class files, on batch results.",
		  "05...Sum of squared errors, one set.",
		  "06...Sum of squared errors, on batch results.",
		  "07...Sum of squared errors, one set, scale first.",
		  "08...Sum of squared errors, on batch results, scale first.",
		  "09...R - clustering criteria, one set.",
		  "10...R - clustering criteria, on batch results.",
		  "11...R - clustering criteria, one set,scale first.",
		  "12...R - clustering criteria, on batch results, scale first.",
		  "13...Quick batch report file (most criteria), scale first.",
		  "14...Quick batch report file (most criteria), no scale.",
		  "15...Class sizes, one set.",
		  "16...Class sizes, on batch results.",
		  "17...Simple statistics, one set.",
		  "18...Simple bin counts, one set.",
		  "19...Item per item comparison of two classifications.",
		  "20...Call Axum graph program."
		 };

while(msel!=0)
 {
 msel=mmenu(mtitle,menu,21,20);
 switch(msel)
  {
  case 0 : break;

  case 1 : make_class_files_from_classification_file(fname,fname2,-1);
	   break;

  case 2 : GetFilename("Select base filename to rebuild (or *.prb)",fname,"*.prb",true);
	   batch_run_using_classification
		(
		fname,
		make_class_files_from_classification_file
		);
	   break;

  case 3 : GetFilename("Select first class file in set to convert.",fname,"*.f*",true);
	   make_alternative_descriptor_class_files(fname,-1);
	   break;

  case 4 : GetFilename("Select base filename to convert (or problem).",fname,"*.prb",true);
	   batch_run_using_classes
	    (
	    fname,
	    make_alternative_descriptor_class_files
	    );
	   break;

  case 5 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",true);
	   sum_of_squared_errors_on_set(fname,0);
	   break;

  case 6 : GetFilename("Select base filename (or problem).",fname,"*.prb",true);
	   batch_run_using_classes
		(
	    fname,
	    sum_of_squared_errors_on_set
	    );
	   break;

  case 7 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",true);
	   sum_of_squared_errors_on_set_scaled(fname,0);
	   break;

  case 8 : GetFilename("Select base filename (or problem).",fname,"*.prb",true);
	   batch_run_using_classes
		(
	    fname,
	    sum_of_squared_errors_on_set_scaled
	    );
	   break;

  case 9 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",true);
	   Rij_on_set(fname,0);
	   break;

  case 10: GetFilename("Select Problem filename.",fname,"*.prb",true);
	   batch_run_using_classes
	    (
		fname,
	    Rij_on_set
	    );
	   break;

  case 11: GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",true);
	   Rij_on_set_scaled(fname,0);
	   break;

  case 12: GetFilename("Select Problem filename.",fname,"*.prb",true);
	   batch_run_using_classes
		(
		fname,
	    Rij_on_set_scaled
	    );
	   break;

  case 13:
	   GetFilename("Select Problem filename.",fname,"*.prb",true);
	   GetFilename("Select Quick Report File.",QuickRepFname,"*.qck",true);
	   if(TGBL no_error)
        {
 	    QuickRepFile=OpenOutFile(QuickRepFname);
	    if(FileOpenOK(QuickRepFile))
		 {
	 	 batch_run_using_classes
		  (
		  fname,
		  all_criteria_scaled_with_quick_report
		  );
		 CloseFile(QuickRepFile);
		 }
        }
	   break;

  case 14:
	   GetFilename("Select Problem filename.",fname,"*.prb",true);
	   GetFilename("Select Quick Report File.",QuickRepFname,"*.qck",true);
	   if(TGBL no_error)
        {
	    QuickRepFile=OpenOutFile(QuickRepFname);
        if(FileOpenOK(QuickRepFile))
	 	 {
		 batch_run_using_classes
		  (
		  fname,
		  all_criteria_with_quick_report
		  );
		 CloseFile(QuickRepFile);
		 }
        }
	   break;

  case 15 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",true);
	   sizes_of_class_files(fname);
	   break;

  case 16 : GetFilename("Select base filename (or problem).",fname,"*.prb",true);
	   batch_run_using_classes
		(
		fname,
		sizes_of_class_files
		);
	   break;

  case 17 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",true);
	   stats_on_set(fname,0);
	   break;

  case 18 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",true);
	   bin_counts_on_set(fname,0);
	   break;

  case 19: Compare_Classifs();
	   break;

  case 20: CallAxum();
	   break;

  default: break;
  }
 if(msel!=0) mwait();
 }
}

