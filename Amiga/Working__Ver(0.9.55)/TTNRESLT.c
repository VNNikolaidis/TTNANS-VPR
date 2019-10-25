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

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include <string.h>

#include "TTNCLAFI.HPP"
#include "TTNMEMOR.HPP"
#include "TTNFNAME.HPP"
#include "TTNMATH.HPP"
#include "TTNBANDX.HPP"
#include "TTNAXUM.HPP"
#include "TTNFILE.HPP"     /* added for Quick Report File generation. - */

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

if(no_error)
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

static BOOL showinfo=TRUE;

mprintf("Calculating Sum of Squared errors. (run # %d)\n",runnum);

if(!is_class_file(fname))
 {
 mprintf("Bad Filename. Returning large number.\n");
 return LARGEDATA;
 }

if(showinfo)
 {
 mprintf("Sum of Squared Errors (J): A performance index \n");
 mprintf("for clustering algorithms calculated as follows\n");
 mprintf("                                               \n");
 mprintf("                                               \n");
 mprintf("             N                                 \n");
 mprintf("              c                                \n");
 mprintf("           _____  _____                        \n");
 mprintf("           \\      \\                          \n");
 mprintf("            \\      \\     ||        ||        \n");
 mprintf("      J =    >      >    || X - M  ||          \n");
 mprintf("            /      /     ||      j ||          \n");
 mprintf("           /____  /____                        \n");
 mprintf("                                               \n");
 mprintf("            j=1   X in S                       \n");
 mprintf("                        j                      \n");
 mprintf("                                               \n");
 mprintf("where N  the number of clusters,               \n");
 mprintf("       c                                       \n");
 mprintf("                                               \n");
 mprintf("      S  the set of vectors in cluster j,      \n");
 mprintf("       j                                       \n");
 mprintf("                                               \n");
 mprintf("     ||A-B|| the Euclidian Distance of A,B and,\n");
 mprintf("                                               \n");
 mprintf("      M  the mean vector for cluster j defined:\n");
 mprintf("       j                                       \n");
 mprintf("          _____                                \n");
 mprintf("          \\                                   \n");
 mprintf("       1   \\                                  \n");
 mprintf(" M  =  -    >  X    with N = num. of S vectors.\n");
 mprintf("  j    N   /              j           j        \n");
 mprintf("        j /____                                \n");
 mprintf("                                               \n");
 mprintf("          X in S                               \n");
 mprintf("                j                              \n");
 showinfo=FALSE;
 }

mprintf(" \n");
mprintf("Opening class (cluster) file set (*.F0,*.F1... or *.X0,*.X1...).\n");

if(no_error)
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
 mprintf("----------------------------------\n");
 mprintf("SSE = ");
 mprintf(DATAFORMAT,sumofsquarederrors);
 mprintf(".\n");
 mprintf("----------------------------------\n");
 return sumofsquarederrors;
 }
return LARGEDATA;
}

/*-------------------------------------------------------------------------*/

DATA sum_of_squared_errors_on_set_scaled(char *fname,int runnum)
{
char tempf[FILENAMELENGTH];
DATA r=-1;
static BOOL ask_to_keep_scaled_files=TRUE;
static BOOL keep_scaled_files;

if(is_class_file(fname))
 {
 mprintf("Processing Sum_of_Squared_Errors (SSE) criteria.\n");

 if(runnum==0)
  create_scaled_classification_files(fname,TRUE);
 else
  create_scaled_classification_files(fname,FALSE);

 scaled_class_n_filename(fname,0,tempf);

 r=sum_of_squared_errors_on_set(tempf,runnum);
 if(ask_to_keep_scaled_files)
  {
  keep_scaled_files=mrequest_yn("SSE: Keep scaled Class files (_*.*)?");
  ask_to_keep_scaled_files=FALSE;
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

static BOOL showinfo=TRUE;

mprintf(" \n");
mprintf("Calculating Rij Cluster Separation Measure.\n");

if(!is_class_file(fname))
 {
 mprintf("Bad Filename. Returning large number.\n");
 return LARGEDATA;
 }

if(showinfo)
 {
 mprintf(" \n");
 mprintf("            S + S          \n");
 mprintf("             i   j         \n");
 mprintf("     R   = --------        \n");
 mprintf("      ij      M            \n");
 mprintf("               ij          \n");
 mprintf(" \n");
 mprintf("S = dispersion measure for cluster. (q=2 => standard deviation)\n");
 mprintf("M = Minkowski inter-cluster metric. (r=1 => City-block distance of means)\n");
 mprintf("                                    (r=2 => Euclidean distance of means)\n");
 mprintf(" \n");
 mprintf("For information on Rij see:\n");
 mprintf("A Cluster Separation Measure, D.L.Davies, D.W.Bouldin. \n");
 mprintf("IEEE Transactions on Pattern Analysis and Machine Inteligence,\n");
 mprintf("Vol.PAM1-No2.1979.\n");
 mprintf(" \n");
 showinfo=FALSE;
 }

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

if(no_error)
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
mprintf("----------------------------------\n");
mprintf("R = ");
mprintf(DATAFORMAT,Rbuf);
mprintf(".\n");
mprintf("----------------------------------\n\n");
return Rbuf;
}

/*-------------------------------------------------------------------------*/

DATA Rij_on_set_scaled(char *fname,int runnum)
{
char tempf[FILENAMELENGTH];
DATA r=-1;
static BOOL ask_to_keep_scaled_files=TRUE;
static BOOL keep_scaled_files;

if(is_class_file(fname))
 {
 mprintf("Processing Rij criteria.\n");

 if(runnum==0)
  create_scaled_classification_files(fname,TRUE);
 else
  create_scaled_classification_files(fname,FALSE);

 scaled_class_n_filename(fname,0,tempf);

 r=Rij_on_set(tempf,runnum);
 if(ask_to_keep_scaled_files)
  {
  keep_scaled_files=mrequest_yn("Rij: Keep scaled Class files (_*.*)?");
  ask_to_keep_scaled_files=FALSE;
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

DATA all_criteria_scaled_with_quick_report(char *fname,int runnum)
{
DATA cv;
if(FileOpenOK(QuickRepFile))
 {
 WriteString(QuickRepFile,"(File:");
 WriteString(QuickRepFile,fname);
 WriteString(QuickRepFile,",run #");
 WriteInt(QuickRepFile,runnum);
 WriteString(QuickRepFile,") Non_Empty : ");
 cv=(DATA)number_of_nonempty_class_files(fname);
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

void result_evaluation_menu(void)
{
char fname [FILENAMELENGTH];
char fname2[FILENAMELENGTH];

int msel=-1;
char *menu[]={"-----------------------",
              "Results Evaluation Menu",
	      "-----------------------",
              "0...Return to previous menu.",
	      "1...Reconstruct Class files from Classification.",
	      "2...Reconstruct Class files, on batch results.",
	      "3...Create modified Class files.",
	      "4...Create modified Class files, on batch results.",
	      "5...Sum of squared errors, one set.",
	      "6...Sum of squared errors, on batch results.",
	      "7...Sum of squared errors, one set,scaled.",
	      "8...Sum of squared errors, on batch results,scaled.",
	      "9...Rij, one set.",
	      "10..Rij, on batch results.",
	      "11..Rij, one set,scaled.",
	      "12..Rij, on batch results,scaled.",
	      "13..Quick batch report file, all criteria.",
	      "14..Call Axum graph program."
	     };

while(msel!=0)
 {
 msel=mmenu(menu,18,3,0,14);
 switch(msel)
  {
  case 0 : break;

  case 1 : make_class_files_from_classification_file(fname,fname2,-1);
	   break;

  case 2 : GetFilename("Select base filename to rebuild (or *.prb)",fname,"*.prb",TRUE);
	   batch_run_using_classification
	    (
	    fname,
	    make_class_files_from_classification_file
	    );
	   break;

  case 3 : GetFilename("Select first class file in set to convert.",fname,"*.f*",TRUE);
	   make_alternative_descriptor_class_files(fname,-1);
	   break;

  case 4 : GetFilename("Select base filename to convert (or problem).",fname,"*.prb",TRUE);
	   batch_run_using_classes
	    (
	    fname,
	    make_alternative_descriptor_class_files
	    );
	   break;

  case 5 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",TRUE);
	   sum_of_squared_errors_on_set(fname,0);
	   break;

  case 6 : GetFilename("Select base filename (or problem).",fname,"*.prb",TRUE);
	   batch_run_using_classes
	    (
	    fname,
	    sum_of_squared_errors_on_set
	    );
	   break;

  case 7 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",TRUE);
	   sum_of_squared_errors_on_set_scaled(fname,0);
	   break;

  case 8 : GetFilename("Select base filename (or problem).",fname,"*.prb",TRUE);
	   batch_run_using_classes
	    (
	    fname,
	    sum_of_squared_errors_on_set_scaled
	    );
	   break;

  case 9 : GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",TRUE);
	   Rij_on_set(fname,0);
	   break;

  case 10: GetFilename("Select Problem filename.",fname,"*.prb",TRUE);
	   batch_run_using_classes
	    (
	    fname,
	    Rij_on_set
	    );
	   break;

  case 11: GetFilename("Select first class file in set (*.f*,*.x*).",fname,"*.x0",TRUE);
	   Rij_on_set_scaled(fname,0);
	   break;

  case 12: GetFilename("Select Problem filename.",fname,"*.prb",TRUE);
	   batch_run_using_classes
	    (
	    fname,
	    Rij_on_set_scaled
	    );
	   break;

  case 13: GetFilename("Select Problem filename.",fname,"*.prb",TRUE);
	   GetFilename("Select Quick Report File.",QuickRepFname,"*.qck",TRUE);
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
	   break;

  case 14: CallAxum();
	   break;

  default: break;
  }
 if(msel!=0) mwait();
 }
}
