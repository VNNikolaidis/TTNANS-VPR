/*
   -------------------
   TTNANS:
   TTNOTHER.C ver.0.01
   -------------------
   V.N.Nikolaidis
   ------------------------
   Non-ANS clustering/PR
   algorithms added for
   performance comparisons.
   ------------------------
*/

#include "ttndef.hpp"
#include "ttnpros.hpp"
#include "ttnsets.hpp"
#include "ttnui.hpp"

#include "TTNMEMOR.HPP"
#include "TTNMATH.HPP"
#include "TTNBANDX.HPP"
#include "TTNPREP3.HPP"

int select_initial_center_type(int rows,int cols)
{
int r;
int combs;

mcls();
mprintf("There are several options for selecting initial cluster centers.\n");
mprintf("You are about to define the ordering method used for initial    \n");
mprintf("cluster center selection out of the data set (training set).    \n");
mprintf("The set itself will NOT be reordered according to the selection.\n");
mprintf("entered now. You may be asked for a training set reordering     \n");
mprintf("method later.                                                 \n\n");

if(mrequest_yn("Select an ordering method for initial cluster centers?"))
 r=ordering_info(SRE_NOT_SET,&combs,rows,cols,TRUE);
else
 r=ordering_info(SRE_NO_CHANGE,&combs,rows,cols,TRUE);

mprintf("Note: Ordering type gives %d possible combinations of which\n",combs);
mprintf("      the first will be used to initialize cluster centers.\n");
mprintf("\n");
return r;
}

/*-----------------------------------------------------------------------*/

void NNC_call (DATA ** Dataset,         /* (Nearest Neighbor Classifier) */
               int rows,
               int cols,
               DATA ** Prototypes,      /* must be numprototypes x cols. */
               int numprototypes,
               DATA * Classification)   /* must have size == rows.       */
{
int i,j;
DATA dist,mindist;

mstarttick("Invoking NNC.");

for(i=0;i<rows;i++)
 {
 mtick(i,rows);
 mindist=LARGEDATA;
 Classification[i]=(DATA)-1;
 for(j=0;j<numprototypes;j++)
  {
  dist=EuclideanDistance(Dataset[i],Prototypes[j],cols);
  if(dist<mindist)
   {
   mindist=dist;
   Classification[i]=(DATA)j;
   }
  }
 if(Classification[i]==(DATA)-1)
  runerror(999,"NNC:Cannot classify,check algorithm");
 }

mendtick();
}

/*-----------------------------------------------------------------------*/
/* NNC classify Dataset with Prototypes, replace Prototypes with MEAN of */
/* each class.                                                           */

void move_prototypes_to_means
              (DATA ** Dataset,
			   int rows,
			   int cols,
               DATA ** Prototypes,      /* must be numprototypes x cols. */
               int numprototypes,       /* overwrites Prototypes.        */
               DATA * Classification)
{
int i,j,c;
int items_in_class;

NNC_call(Dataset,rows,cols,Prototypes,numprototypes,Classification);
for(i=0;i<numprototypes;i++)
 {
 for(c=0;c<cols;c++)
  Prototypes[i][c]=0;
 items_in_class=0;

 for(j=0;j<rows;j++)
  {
  if(Classification[j]==i)
   {
   for(c=0;c<cols;c++)
	Prototypes[i][c]=Prototypes[i][c]+Dataset[j][c];
   items_in_class++;
   }
  }
 if(items_in_class>0)
  {
  for(c=0;c<cols;c++)
   Prototypes[i][c]=Prototypes[i][c]/items_in_class;
  }
 }
}

/*-----------------------------------------------------------------------*/

int Split_Set(BOOL RunAlgorithm,int splits,int rows,DATA * split_index)
{
static BOOL showinfo=TRUE;
int size;
int i,counter,clss;

mprintf("Split (Testing) set into %d sets.\n",splits);
mprintf("\n");
if(!IS_CLUSTERING_PROBLEM)
 {
 mprintf("Note: This uses the test set and ignores any reordering\n");
 mprintf("      or scaling performed on any other sets.          \n");
 mprintf("\n");
 }

if(RunAlgorithm)
 {

 if(showinfo)
  {
  mprintf("\n");
  mprintf("Split Set:\n");
  mprintf("\n");
  mprintf("This algorithm splits the given set into a requested number of classes\n");
  mprintf("(%d in this case) of equal size (number of events). If the set cannot \n",splits);
  mprintf("be split evenly, the last class will contain the remaining events.\n");
  mprintf("If split number (output size) is one no spliting takes place.\n");
  mprintf("\n");
  showinfo=FALSE;
  }

 if(no_error&&
   (rows>0)&&
   (splits>0)&&
   (rows>=splits))
  {

  mprintf("Spliting Set of size %d into :\n",rows);

  size=rows/splits;
  counter=0;
  clss=0;

  for(i=0;i<rows;i++)
   {
   split_index[i]=(DATA)clss;
   counter++;
   if((counter>=size)||(i==rows-1))
    {
	mprintf(" - Set %d of size %d.\n",clss,counter);
	counter=0;
	clss++;
    }
   }
  return TRUE;
  }
 else
  {
  runerror(999,"Split Training Set: Can't split, set sizes are invalid.");
  }
 }
return FALSE;
}

/*-----------------------------------------------------------------------*/
/* K-Means algorithm, modified. Original code by A.Anastassopoulos.      */
/*-----------------------------------------------------------------------*/

BOOL K_Means(BOOL GetParameters,
			 BOOL RunAlgorithm,
			 int  ins,                          /* input size (dim).     */
			 int  outs,                         /* output size (classes).*/
			 DATA **Trainset,
			 int  Trainsetsize,
			 DATA **Testset,
			 int  Testsetsize,
			 DATA **Unused,                     /* (unused)              */
			 DATA *Classif)
{
int i, j, a;
int iter=0;
int start;
int clas;
int status;
BOOL run_success=FALSE;

static int max_iteration=-1;
static BOOL showinfo=TRUE;

DATA **cluster_center;
DATA **temp_cluster_center;
int  * number_of_prototypes_in_class;

static int initial_cluster_center_type;
int * initial_cluster_center_index;

DATA min_dist, dist;

if(outs>Trainsetsize)
 runerror(999,"Not enough records for requested number of clusters");

if(Trainsetsize!=Testsetsize)
 runerror(999,"Clustering algo. k-Means needs |train set| = |test set|.\n");

if(no_error)
 {
 mprintf("K-Means Algorithm.\n");

 if(showinfo)
  {
  mprintf("------------------\n");
  mprintf("A non-ANS clustering algorithm described in      \n");
  mprintf("Pattern Recognition Principles by Tou & Gonzalez (p.95).\n");
  mprintf("\n");
  showinfo=FALSE;
  }

 if(GetParameters)
  {
  while(outs<1)
   outs=mrequest_int("Enter the number of clusters desired");

  while(max_iteration<0)
  max_iteration=mrequest_int("Enter max iteration limit");

  initial_cluster_center_type=select_initial_center_type(Trainsetsize,ins);
  }

 mprintf("Requested number of clusters (classes):%d.\n",outs);

 if(RunAlgorithm)
  {
  cluster_center=MMalloc2dDATA(outs,ins);
  temp_cluster_center=MMalloc2dDATA(outs,ins);
  number_of_prototypes_in_class=(int *)MMalloc(outs*sizeof(int));
  initial_cluster_center_index=(int *)MMalloc(outs*sizeof(int));

  if(no_error)
   {
   mprintf("Initializing cluster centers to selected items in training set.\n");
   ordering(initial_cluster_center_type,0,Trainset,Trainsetsize,ins,
			initial_cluster_center_index,outs);

   mprintf("Cluster center data set indexes are [ ");
   for(j=0;j<outs;j++)                     /* initialize cluster centers */
	{
	mprintf("%d ",initial_cluster_center_index[j]);
	for(a=0;a<ins;a++)
	 {
	 cluster_center[j][a]=Trainset[initial_cluster_center_index[j]][a];
	 temp_cluster_center[j][a]=Trainset[initial_cluster_center_index[j]][a];
	 }
	Classif[j]=(DATA)j;
	number_of_prototypes_in_class[j]=1;
	}
   mprintf("].\n");

   start=outs;

   mstarttick("Running K-Means.");

   step:                                  /* classify to the nearest     */
										  /* cluster center.   Note:     */
										  /* Unlike LVQ, each record is  */
   iter+=1;                               /* compared with original      */
   for(i=start;i<Trainsetsize; i++)       /* (in 'cluster_center'), not  */
	{                                     /* modified (in 'temp_cl...'). */
	min_dist=LARGEDATA;                   /* Before update, temp_c... is */
	for(j=0;j<outs;j++)                   /* SUM of all records found to */
	 {                                    /* be in given class.          */
	 dist=
	  EuclideanDistance(Trainset[i],cluster_center[j],ins);
	 if(dist<min_dist)
	  {
	  min_dist=dist;
	  clas=j;
	  }
	 }
	Classif[i]=(DATA)clas;      /*'clas' contains winner for Trainset[i].*/
								/* write updates in 'temp_cluster_center.*/
	for(a=0;a<ins;a++)
	 temp_cluster_center[clas][a]=temp_cluster_center[clas][a]+Trainset[i][a] ;

	number_of_prototypes_in_class[clas]=number_of_prototypes_in_class[clas]+1 ;
	}

   /* Done classifing all input records. Update cluster centers to       */
   /* corresponding temp_cluster_center(s) divided by number of records  */
   /* found in class, effectively moving to the mean of the sample set   */
   /* in the given class. (They don't call this k-MEANs for nothing!!!). */

   for(j=0;j<outs;j++)                        /* find new cluster center */
	for(a=0;a<ins;a++)
	 {
	 if(number_of_prototypes_in_class[j]==0)
	  {
	  /*
	  mprintf("K-Means Warning: Empty cluster %d at iteration %d.\n",j,iter);
	  mprintf("---------------  Cluster center is not modified.\n");
	  runerror(ARITHMERR,"K-Means: Division by 0 (bypassed).");
	  */
	  }
	 else
	  temp_cluster_center[j][a]=(DATA)temp_cluster_center[j][a]/number_of_prototypes_in_class[j];
	 if(temp_cluster_center[j][a]!=cluster_center[j][a])
	  {
	  cluster_center[j][a]=temp_cluster_center[j][a];
	  status=1;
	  }
	 }

   mtick(iter,max_iteration);

   if (status==1)                                  /* no convergence yet */
	{
	if(iter<max_iteration)
	 {
	 start=status=0;
	 /*initial */
	 for(j=0;j<outs;j++)
	  {
	  number_of_prototypes_in_class[j]=0;
	  for (a=0; a<ins; a++)
	   temp_cluster_center[j][a]=0;
	  }
	 goto step;
	 }
	else
	 {
	 mendtick();
	 mprintf ("No convergence after %d iterations.\n",iter);
	 }
	}
   else
	{
	mendtick();
	mprintf  ("Converged  after %d iterations.\n",iter);
	}
   run_success=TRUE;

   /* Original algorithm ends here, but in this case we proceed to      */
   /* the test set (original order train set) and this is what we put   */
   /* to classif.                                                       */

   mstarttick("Classifing original-order trainset with current cluster centers");

   for(i=0;i<Testsetsize;i++)
	{
	clas=-1;
	min_dist=LARGEDATA;
	for(j=0;j<outs;j++)
	 if(number_of_prototypes_in_class[j]!=0)
	  {
	  dist=EuclideanDistance(Testset[i],cluster_center[j],ins);
	  if(dist<min_dist)
	   {
	   min_dist=dist;
	   clas=j;
	   }
	  }
	if(clas==-1)
	 {
	 runerror(999,"All classes empty,check algorithm.");
	 }
	else
	 {
	 Classif[i]=(DATA)clas;      /*'clas' contains winner for Testset[i].*/
	 mtick(i,Testsetsize);
	 }
	}
   mendtick();

   MFree2dDATA(cluster_center,outs);
   MFree2dDATA(temp_cluster_center,outs);
   MFree(number_of_prototypes_in_class);
   MFree(initial_cluster_center_index);
   }
  }
 }
return run_success;
}

/*-----------------------------------------------------------------------*/
/* K-Means algorithm, well modified.                                     */
/*-----------------------------------------------------------------------*/

BOOL Krazy_K_Means(BOOL GetParameters,
			 BOOL RunAlgorithm,
             int  inputdim,                     /* input size (dim).     */
             int  classes,                      /* output size (classes).*/
             DATA **Trainset,
             int  Trainsetsize,
             DATA **Testset,
             int  Testsetsize,
             DATA **Unused,                     /* (unused)              */
			 DATA *Classif)
{
int i, j, a;
int iter=0;
int clas;
int status;
int same;
BOOL run_success=FALSE;

int ins=inputdim;
int outs=classes;

static int max_iteration=-1;
static BOOL showinfo=TRUE;
static int look_back=0;

DATA **cluster_center;
DATA **temp_cluster_center;
DATA * max_distance;
int  * max_distance_item;                                 /* per cluster */
int  * number_of_prototypes_in_class;
int  **last_max_item;                     /* keep track of old maxs here */
BOOL * cluster_marked_out;                /* for eliminating clusters.   */

static int initial_cluster_center_type;
int * initial_cluster_center_index;

DATA min_dist, dist;

if(outs>Trainsetsize)
 runerror(999,"Not enough records for requested number of clusters");

if(Trainsetsize!=Testsetsize)
 runerror(999,"Clustering algo. k-Means needs |train set| = |test set|.\n");

if(no_error)
 {
 mprintf("Krazy K-Means V.01 Algorithm.\n");

 if(showinfo)
  {
  mprintf("------------------------------------\n");
  mprintf("A non-ANS clustering algorithm based on K-means, \n");
  mprintf("(K-means described in P.R.Pr. by Tou & Gonzalez.)\n");
  mprintf("After k-means temporary cluster center (mean) is \n");
  mprintf("calculated, it is replaced by one record (event) \n");
  mprintf("in the cluster most distant from all centers.    \n");
  mprintf("\n");
  showinfo=FALSE;
  }
                                          /*- Get parameters. - - - - - -*/
 if(GetParameters)
  {
  while(outs<1)
   outs=mrequest_int("Enter the number of clusters desired");

  while(max_iteration<0)
  max_iteration=mrequest_int("Enter max iteration limit");

  while(look_back<1)
  look_back=mrequest_int("Enter look back steps (convergence check)");

  initial_cluster_center_type=select_initial_center_type(Trainsetsize,ins);
  }

 mprintf("Requested number of clusters (classes):%d.\n",outs);

										  /*- Run algorithm as follows. -*/

 if(RunAlgorithm)
  {
  cluster_center=MMalloc2dDATA(outs,ins);
  temp_cluster_center=MMalloc2dDATA(outs,ins);
  number_of_prototypes_in_class=(int *)MMalloc(outs*sizeof(int));
  initial_cluster_center_index=(int *)MMalloc(outs*sizeof(int));
  max_distance=MMalloc1dDATA(outs);
  max_distance_item=(int *)MMalloc(outs*sizeof(int));
  last_max_item=MMalloc2dint(look_back,outs);
  cluster_marked_out=(BOOL *)MMalloc(outs*sizeof(BOOL));

  if(no_error)

   {                                      /*- Initialize cluster centers-*/

   mprintf("Initializing cluster centers to selected items in training set.\n");
   ordering(initial_cluster_center_type,0,Trainset,Trainsetsize,ins,
            initial_cluster_center_index,outs);

   mprintf("Cluster center data set indexes are [ ");
   for(j=0;j<outs;j++)
    {
    mprintf("%d ",initial_cluster_center_index[j]);
	for(a=0;a<ins;a++)
     {
	 cluster_center[j][a]=Trainset[initial_cluster_center_index[j]][a];
     temp_cluster_center[j][a]=Trainset[initial_cluster_center_index[j]][a];
     }
    cluster_marked_out[j]=FALSE;
    number_of_prototypes_in_class[j]=0;
	}
   mprintf("].\n");

										  /*- Init.list of centers used- */

   for(j=0;j<look_back;j++)
    for(i=0;i<outs;i++)
     last_max_item[j][i]=Trainsetsize+1;        /*(initialize to invalid)*/

   mstarttick("Running KK-Means.");

   step:                                  /*- Run this iteratively - - - */

   for(j=0;j<outs;j++)                    /* eliminate identical cluster */
    for(i=j+1;i<outs;i++)                 /* centers.                    */
     {
	 if(
       (EuclideanDistance(cluster_center[i],cluster_center[j],ins)==(DATA)0)
	   &&(!(cluster_marked_out[i]||cluster_marked_out[j]))
       )
      {
	  mprintf("Cluster Centers %d,%d identical.Eliminating %d.\n",j,i,i);
      cluster_marked_out[i]=TRUE;
	  number_of_prototypes_in_class[i]=0;
      }
	 }
                                          /* classify to nearest valid   */
										  /* cluster center.   Note:     */
                                          /* Unlike LVQ, each record is  */
   iter+=1;                               /* compared with original      */
   for(i=0;i<Trainsetsize; i++)           /* (in 'cluster_center'), not  */
    {                                     /* modified (in 'temp_cl...'). */
    min_dist=LARGEDATA;                   /* Before update, temp_c... is */
	for(j=0;j<outs;j++)                   /* SUM of all records found to */
	 if(!cluster_marked_out[j])           /* be in given class.          */
      {
      dist=EuclideanDistance(Trainset[i],cluster_center[j],ins);
      if(dist<min_dist)
       {
	   min_dist=dist;
       clas=j;
	   }
      }

    Classif[i]=(DATA)clas;      /*'clas' contains winner for Trainset[i].*/
                                /* write updates in 'temp_cluster_center.*/
	for(a=0;a<ins;a++)
	 temp_cluster_center[clas][a]=temp_cluster_center[clas][a]+Trainset[i][a] ;

    number_of_prototypes_in_class[clas]=number_of_prototypes_in_class[clas]+1 ;
	}

   /* Done classifing all input records. Update cluster centers to       */
   /* corresponding temp_cluster_center(s) divided by number of records  */
   /* found in class, effectively moving to the mean of the sample set   */
   /* in the given class. (They don't call this k-MEANs for nothing!!!). */

   for(j=0;j<outs;j++)                        /* find new cluster center */
    {
    if(!cluster_marked_out[j])
	 {
     if(number_of_prototypes_in_class[j]==0)
	  {
      mprintf("K-Means Warning: Empty cluster %d at iteration %d.\n",j,iter);
	  mprintf("---------------  Cluster center is not modified.\n");
      runerror(ARITHMERR,"K-Means: Division by 0 (bypassed).");
      }
     else
      for(a=0;a<ins;a++)
	   temp_cluster_center[j][a]=(DATA)temp_cluster_center[j][a]/number_of_prototypes_in_class[j];
     }
    }

   /* all records are classified and temp_cluster_centers are at the     */
   /* mean of each (valid) class. Now do the limbo, go crazy and...      */
   /* for each class find the most distant from all means training item  */
   /* and set this as the cluster center.                                */

   for(i=0;i<outs;i++)
    {
    max_distance[i]=(DATA)-1;  /* most-distance-to-all-centers for class */
    max_distance_item[i]=-1;   /* item with above most distance in class */
    }

   for(i=0;i<Trainsetsize;i++)          /* find item per class with most */
	{                                   /* distance to all cluster means.*/
	dist=0;
	clas=(int)Classif[i];
    for(j=0;j<outs;j++)
     if(!cluster_marked_out[j])
      dist=dist+EuclideanDistance(Trainset[i],temp_cluster_center[j],ins);

	if(dist>=max_distance[clas])
     {
     max_distance_item[clas]=i;
     max_distance[clas]=dist;
	 }
    }

   for(j=0;j<outs;j++)               /* Replace cluster center with item */
	{
    if(!cluster_marked_out[j])
     {
     if(max_distance_item[j]==-1)
      {
      mprintf("KKM problem: max distance item not found (Iteration %d).\n",iter);
      mprintf("             Check algorithm.\n");
	  mwait();
	  runerror(999,"KKM failed.");
      }
	 for(a=0;a<ins;a++)
      cluster_center[j][a]=Trainset[max_distance_item[j]][a];
	 }
	}

   status=1;

   for(j=0;j<look_back;j++)          /* Check if this set of items was   */
    {                                /* picked during passed iterations; */
	same=0;                          /* If yes stop.                     */
    for(i=0;i<outs;i++)
	 if(max_distance_item[i]==last_max_item[j][i]) same=same+1;
	if(same==outs) status=0;
    }

   mtick(iter,max_iteration);

   if (status==1)                                  /* no convergence yet */
    {
    if(iter<max_iteration)
	 {
	 for(j=look_back-1;j>0;j--)
      for(i=0;i<outs;i++)
	   last_max_item[j][i]=last_max_item[j-1][i];   /* update passed set */
     for(i=0;i<outs;i++)
	  last_max_item[0][i]=max_distance_item[i];

     /*
	 for(j=0;j<look_back;j++)
      {
      mprintf("Centers for t-%d: ",j);
      for(i=0;i<outs;i++)
	   mprintf("%d ",last_max_item[j][i]);
	  mprintf(".\n");
	  }
     mprintf("---------------------\n");
     */

     /*initial */

     for(j=0;j<outs;j++)
	  {
      number_of_prototypes_in_class[j]=0;
	  for (a=0; a<ins; a++)
	   temp_cluster_center[j][a]=0;
      }
	 goto step;
	 }
    else
     {
     mendtick();
	 mprintf ("No convergence after %d iterations.\n",iter);
     }
    }
   else
	{
	mendtick();
    mprintf  ("Converged  after %d iterations.\n",iter);
    }
   run_success=TRUE;

   /* Original algorithm ends here, but in this case we proceed to      */
   /* the test set (original order train set) and this is what we put   */
   /* to classif.                                                       */

   i=0;                          /* just a silly test to make sure....  */
   for(j=0;j<outs;j++)
	if(cluster_marked_out[j])i++;
   mprintf("Eliminated clusters : %d out of %d.\n",i,outs);
   if(i==outs)
    runerror(999,"KKM: All clusters were eliminated.");

   mstarttick("Classifing original-order trainset with current cluster centers");
   for(i=0;i<Testsetsize;i++)
	{
    min_dist=LARGEDATA;
    for(j=0;j<outs;j++)
	 if(!cluster_marked_out[j])
	  {
      dist=EuclideanDistance(Testset[i],cluster_center[j],ins);
	  if(dist<min_dist)
       {
       min_dist=dist;
       clas=j;
       }
      }
    Classif[i]=(DATA)clas;      /*'clas' contains winner for Testset[i].*/
    mtick(i,Testsetsize);
    }
   mendtick();

   MFree(cluster_marked_out);
   MFree(initial_cluster_center_index);
   MFree2dDATA(cluster_center,outs);
   MFree2dDATA(temp_cluster_center,outs);
   MFree(max_distance);
   MFree(max_distance_item);
   MFree(number_of_prototypes_in_class);
   MFree2dint(last_max_item,look_back);
   }
  }
 }
return run_success;
}

/*-----------------------------------------------------------------------*/

BOOL MaxMin_Distance
			(BOOL GetParameters,
			 BOOL RunAlgorithm,
			 int  inputdim,                     /* input size (dim).     */
			 int  maxnumclasses,                /* max output classes.   */
			 DATA **Trainset,
			 int  Trainsetsize,
			 DATA **Testset,
			 int  Testsetsize,
			 DATA **Unused,                     /* (unused)              */
			 DATA *Classif)
{
static int numinitialclasses;               /* number of initial classes.*/       /* (aint these comments helpful or what?) */
static DATA Tm;                             /* Distance threshold param. */
static BOOL classify_using_means;

static int initial_cluster_center_type;
int * initial_cluster_center_index;
DATA ** cluster_centers;

int i,j,c;
int max_class_defined;

int * clustercenterindex;                   /* Cluster center indexes to */
											/* training set items.       */
DATA dist;
DATA distz;                                 /* Average distance between  */
											/* cluster centers.          */

DATA * Dmin;                                /* Min distance from item to */
											/* cluster centers           */
int mmitem;                                 /* Maxmindist. training item.*/

BOOL new_class_created = TRUE;
BOOL maximum_classes_exceeded=FALSE;

if(Trainsetsize!=Testsetsize)
 {
 mprintf("MaxMin: Aborted. Training set size =/= Testing set size.\n");
 return FALSE;
 }

mprintf("MaxMin Distance.\n");
mprintf("----------------\n");
mprintf("A clustering technique described in \n");
mprintf("'Pattern Recognition Principles' by Tou & Gonzalez.\n");
mprintf("\n");

if(GetParameters)
 {
 numinitialclasses=-1;
 while((numinitialclasses<1)||(numinitialclasses>maxnumclasses))
  {
  mprintf("Requesting number of initial clusters to create (0<n<=%d).\n",maxnumclasses);
  numinitialclasses=mrequest_int("Enter number of initial clusters (default = 1).");
  }

 Tm=-1.0;
 mprintf("Requesting threshold parameter Tm used in creating new classes.\n");
 mprintf("(small Tm => more classes).\n");
 while((Tm<=0)||(Tm>=1))
  Tm=mrequest_DATA("Select threshold parameter (0<Tm<1).");

 initial_cluster_center_type=select_initial_center_type(Trainsetsize,inputdim);

 mprintf("Before classifing the testing set you have the option of using\n");
 mprintf("the mean of each class created by maxmin and using this as the\n");
 mprintf("final cluster center.\n");
 classify_using_means=mrequest_yn("Use means for final classification?");
 }

if(no_error&&RunAlgorithm)
 {
 initial_cluster_center_index=(int *)MMalloc(numinitialclasses*sizeof(int));
 clustercenterindex=(int *)MMalloc(maxnumclasses*sizeof(int));
 Dmin=MMalloc1dDATA(Trainsetsize);

 if(no_error)
  {
  mprintf("Initializing cluster centers to selected items in training set.\n");
  ordering(initial_cluster_center_type,0,Trainset,Trainsetsize,inputdim,
		   initial_cluster_center_index,numinitialclasses);

  mprintf("Initial cluster centers (data set indexes) are [ ");

  for(i=0;i<numinitialclasses;i++)
   {
   mprintf("%d ",initial_cluster_center_index[i]);
   clustercenterindex[i]=initial_cluster_center_index[i];
   }

  mprintf("]\n");

  max_class_defined=numinitialclasses-1;
  for(;i<maxnumclasses;i++)
   clustercenterindex[i]=-1;                   /* Reset rest to invalid.  */

  mstarttick("MaxMin Distance: Encoding");

  while(new_class_created)
   {
   mtick(max_class_defined,maxnumclasses);

   /*- Determine minimum distance from each item to each cluster center. -*/

   for(i=0;i<Trainsetsize;i++) Dmin[i]=LARGEDATA;  /* Reset min to large. */
   for(i=0;i<Trainsetsize;i++)
	for(j=0;j<=max_class_defined;j++)
	 {
	 dist=EuclideanDistance(Trainset[i],Trainset[clustercenterindex[j]],inputdim);
	 if(dist<Dmin[i])
	  Dmin[i]=dist;
	 }

   /*- Determine item with maximum Dmin. (they call it maxmin,remember?) -*/

   mmitem=-1;
   dist=(DATA)-1;
   for(i=0;i<Trainsetsize;i++)
	{
	if(Dmin[i]>dist)
	 {
	 mmitem=i;
	 dist=Dmin[i];                     /* we will keep max min dist here. */
	 }
	}

   /*- - - -  Determine average distance between cluster centers.  - - - -*/

   distz=(DATA)0;
   c=0;

   for(i=0;i<=max_class_defined-1;i++)
   for(j=i+1;j<=max_class_defined;j++)
	{
	distz=distz+EuclideanDistance(Trainset[clustercenterindex[i]],
								  Trainset[clustercenterindex[j]],
								  inputdim);
	c++;
	}

   if(c!=0)
	distz=distz/c;

   /* - - Check if new class needs to be created and create new class.- - */

   new_class_created=FALSE;
   if(dist>(distz*Tm))
	{
	if(max_class_defined<maxnumclasses-1)
	 {
	 max_class_defined++;
	 clustercenterindex[max_class_defined]=mmitem;
	 new_class_created=TRUE;
	 }
	else
	 maximum_classes_exceeded=TRUE;
	}
   }

  mendtick();

  if(maximum_classes_exceeded)
   mprintf("MaxMin exits due to maximum number of classes limit reached.\n");

  mprintf("Last cluster defined = %d (including 0), Max clusters allowed = %d.\n",
		  max_class_defined,maxnumclasses);
  mprintf("\n");

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  cluster_centers=MMalloc2dDATA(max_class_defined+1,inputdim);

  if(no_error)
   {
   for(i=0;i<max_class_defined+1;i++)
	for(j=0;j<inputdim;j++)
	 cluster_centers[i][j]=Trainset[clustercenterindex[i]][j];

   if(classify_using_means)
	move_prototypes_to_means(Trainset,Trainsetsize,inputdim,cluster_centers,max_class_defined+1,Classif);


   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

   mprintf("Classifing Testing Set.\n");
   NNC_call(Testset,Testsetsize,inputdim,cluster_centers,max_class_defined+1,Classif);
   MFree2dDATA(cluster_centers,max_class_defined+1);
   }

  MFree(Dmin);
  MFree(clustercenterindex);
  MFree(initial_cluster_center_index);
  }
 }
return TRUE;
}
/*-----------------------------------------------------------------------*/

BOOL MaxMin_Distance_with_Tm_Estimation
			(BOOL GetParameters,
			 BOOL RunAlgorithm,
			 int  inputdim,                     /* input size (dim).     */
			 int  classes,                      /* output classes.       */
			 DATA **Trainset,
			 int  Trainsetsize,
			 DATA **Testset,
			 int  Testsetsize,
			 DATA **Unused,                     /* (unused)              */
			 DATA *Classif)
{

static BOOL classify_using_means;

int i,j,c;

DATA Tm;                                    /* Distance threshold param. */
DATA OLD_Tm;
DATA HI_Tm=1;
DATA LOW_Tm=0;

int max_class_defined=-1;
int max_class_wanted=classes-1;

int * clustercenterindex;                   /* Cluster center indexes to */
											/* training set items.       */
DATA ** cluster_centers;

DATA dist;
DATA distz;                                 /* Average distance between  */
											/* cluster centers.          */

DATA * Dmin;                                /* Min distance from item to */
											/* cluster centers           */
int mmitem;                                 /* Maxmindist. training item.*/

BOOL new_class_created = TRUE;

static int numinitialclasses;
static int initial_cluster_center_type;
int * initial_cluster_center_index;

BOOL enough_classes;

/*
*/
if(Trainsetsize!=Testsetsize)
 {
 mprintf("MaxMin(B): Aborted. Training set size =/= Testing set size.\n");
 return FALSE;
 }

if(classes<2)
 {
 mprintf("MaxMin(B): Aborted. Output classes must be > 1.\n");
 return FALSE;
 }

mprintf("MaxMin Distance Bsearch.\n");
mprintf("------------------------\n");
mprintf("Modified MaxMin, Searches for Tm outputing requested number of classes.\n");
mprintf("\n");

if(GetParameters)
 {
 numinitialclasses=-1;
 while((numinitialclasses<1)||(numinitialclasses>classes))
  {
  mprintf("Requesting number of initial clusters to create (0<n<=%d).\n",classes);
  numinitialclasses=mrequest_int("Enter number of initial clusters (default = 1).");
  }
 initial_cluster_center_type=select_initial_center_type(Trainsetsize,inputdim);
 classify_using_means=mrequest_yn("Use means for final classification?");
 }

if(no_error&&RunAlgorithm)
 {
 clustercenterindex=(int *)MMalloc(classes*sizeof(int));
 Dmin=MMalloc1dDATA(Trainsetsize);
 initial_cluster_center_index=(int *)MMalloc(numinitialclasses*sizeof(int));

 if(no_error)
  {
  mprintf("Initializing cluster centers.\n");
  ordering(initial_cluster_center_type,0,Trainset,Trainsetsize,inputdim,
		   initial_cluster_center_index,numinitialclasses);

  Tm=(DATA)1;                                     /* Put all in one class */
  OLD_Tm=0;
  HI_Tm=1;
  LOW_Tm=0;

  while((max_class_defined!=max_class_wanted)&&(Tm!=OLD_Tm))
   {
   mprintf("Trying Tm = ");
   mprintf(DATAFORMAT,Tm);
   mprintf(" (Range [");
   mprintf(DATAFORMAT,LOW_Tm);
   mprintf(",");
   mprintf(DATAFORMAT,HI_Tm);
   mprintf("]).\n");
   mprintf("Initial cluster centers at  ");

   for(i=0;i<numinitialclasses;i++)
	{
	mprintf("%d ",initial_cluster_center_index[i]);
	clustercenterindex[i]=initial_cluster_center_index[i];
	}

   new_class_created=TRUE;
   max_class_defined=numinitialclasses-1;

   mprintf("]\n");

   for(;i<classes;i++)
	clustercenterindex[i]=-1;                   /* Reset rest to invalid.  */

   mstarttick("MaxMin (B) Distance: Encoding");

   while(new_class_created)
	{
	mtick(max_class_defined,max_class_wanted);

	/*- Determine minimum distance from each item to each cluster center.-*/

	for(i=0;i<Trainsetsize;i++) Dmin[i]=LARGEDATA; /* Reset min to large. */
	for(i=0;i<Trainsetsize;i++)
	 for(j=0;j<=max_class_defined;j++)
	  {
	  dist=EuclideanDistance(Trainset[i],Trainset[clustercenterindex[j]],inputdim);
	  if(dist<Dmin[i])
	   Dmin[i]=dist;
	  }

	/*- Determine item with maximum Dmin. (they call it maxmin,remember?)-*/

	mmitem=-1;
	dist=(DATA)-1;
	for(i=0;i<Trainsetsize;i++)
	 {
	 if(Dmin[i]>dist)
	  {
	  mmitem=i;
	  dist=Dmin[i];                    /* we will keep max min dist here. */
	  }
	 }

	/*- - - - Determine average distance between cluster centers.  - - - -*/

	distz=(DATA)0;
	c=0;

	for(i=0;i<=max_class_defined-1;i++)
	for(j=i+1;j<=max_class_defined;j++)
	 {
	 distz=distz+EuclideanDistance(Trainset[clustercenterindex[i]],
								   Trainset[clustercenterindex[j]],
								   inputdim);
	 c++;
	 }

	if(c!=0)
	 distz=distz/c;

	/* - - Check if new class needs to be created and create new class. - */

	new_class_created=FALSE;
	enough_classes=TRUE;
	if(dist>(distz*Tm))                      /* need to create new class. */
	 {
	 if(max_class_defined<max_class_wanted)
	  {
	  max_class_defined++;
	  clustercenterindex[max_class_defined]=mmitem;
	  new_class_created=TRUE;
	  enough_classes=TRUE;
	  }
	 else
	  enough_classes=FALSE;
	 }

	mendtick();
	}

   mprintf("Last cluster defined = %d (including 0), clusters requested = %d.\n",
		   max_class_defined,classes);

   mprintf("\n");

   if(!enough_classes)                     /* Too many classes, higher Tm */
	{
	mprintf("Too MANY classes, making Tm larger.\n");

	OLD_Tm=Tm;
	LOW_Tm=Tm;
	Tm=HI_Tm-((HI_Tm-Tm)/2);
	max_class_defined=max_class_wanted+1;                  /* invalidate. */
	}

   if(max_class_defined<max_class_wanted)
	{
	mprintf("Too FEW classes, making Tm smaller.\n");

	OLD_Tm=Tm;
	HI_Tm=Tm;
	Tm=LOW_Tm+((Tm-LOW_Tm)/2);
	}
   }

  if(Tm==OLD_Tm)
   {
   mprintf("Could not estimate Tm for %d+1 classes,\n",max_class_wanted);
   mprintf("exiting with %d+1 classes, (Tm = ",max_class_defined);
   mprintf(DATAFORMAT,Tm);
   mprintf(").\n");
   if(max_class_defined>max_class_wanted)
	{
	mbeep();
	mprintf("WARNING:Ended with too many classes, trimmed to %d. Results unpredictable.\n",max_class_wanted+1);
	max_class_defined=max_class_wanted;
	mbeep();
	}
   }

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  cluster_centers=MMalloc2dDATA(max_class_defined+1,inputdim);

  if(no_error)
   {
   for(i=0;i<max_class_defined+1;i++)
	for(j=0;j<inputdim;j++)
	 cluster_centers[i][j]=Trainset[clustercenterindex[i]][j];

   if(classify_using_means)
	move_prototypes_to_means(Trainset,Trainsetsize,inputdim,cluster_centers,max_class_defined+1,Classif);


   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

   mprintf("Classifing Testing Set.\n");
   NNC_call(Testset,Testsetsize,inputdim,cluster_centers,max_class_defined+1,Classif);
   MFree2dDATA(cluster_centers,max_class_defined+1);
   }

  MFree(Dmin);
  MFree(clustercenterindex);
  MFree(initial_cluster_center_index);
  }
 }
return TRUE;
}

/*-----------------------------------------------------------------------*/

BOOL Nearest_Neighbor_Classifier
			(BOOL GetParameters,
			 BOOL RunAlgorithm,
			 int  inputdim,                     /* input size (dim).     */
			 int  classes,                      /* output classes.       */
			 DATA **Trainset,
			 int  Trainsetsize,
			 DATA **Testset,
			 int  Testsetsize,
			 DATA **Unused,                     /* (unused)              */
			 DATA *Classif)
{
static int initial_cluster_center_type;
int * initial_cluster_center_index;
DATA ** cluster_centers;

int i,j;

if(GetParameters)
 {
 initial_cluster_center_type=select_initial_center_type(Trainsetsize,inputdim);
 }

if(RunAlgorithm&&no_error)
 {
 initial_cluster_center_index=(int *)MMalloc(classes*sizeof(int));
 cluster_centers=MMalloc2dDATA(classes,inputdim);

 if(no_error)
  {
  mprintf("Initializing cluster centers to selected items in training set.\n");
  ordering(initial_cluster_center_type,0,Trainset,Trainsetsize,inputdim,
		   initial_cluster_center_index,classes);

  mprintf("Initial cluster centers (data set indexes) are [ ");

  for(i=0;i<classes;i++)
   {
   mprintf("%d ",initial_cluster_center_index[i]);
   for(j=0;j<inputdim;j++)
	cluster_centers[i][j]=Trainset[initial_cluster_center_index[i]][j];
   }

  NNC_call(Testset,Testsetsize,inputdim,cluster_centers,classes,Classif);

  MFree(initial_cluster_center_index);
  MFree2dDATA(cluster_centers,classes);
  return TRUE;
  }
 }
return FALSE;
}

/*-----------------------------------------------------------------------*/

int non_ans_menu(int preselect,           /* -1 = Show menu              */
			 BOOL take_action,            /* Don't just select an algo.  */
			 BOOL get_algo_parameters,    /* Ask for algo parameters too.*/
			 BOOL run_it,                 /* and run it.                 */
			 int Unused)                  /* currently unused.           */
{
int msel=preselect;


char *menu[]={"---------------------",
			  "    Non-ANS Menu     ",
			  "---------------------",
			  "Select:              ",
			  "0...No more processing - Go to previous menu.",
			  "1...Split Test Set.",
			  "2...K-Means.",
			  "3...Krazy K-Means.",
			  "4...Max-Min Distance.",
			  "5...Max-Min Distance, Estimate Tm.",
			  "6...Nearest Neighbor Classifier."
			  };

ANS_run_success=FALSE;

if(no_error)
 {
 if(preselect<0) msel=mmenu(menu,11,4,0,6);

 if(take_action)
 switch(msel)
  {
  case 0: break;

  case 1: ANS_run_success=Split_Set(run_it,outputdim,testsetsize,classif);
		  break;

  case 2: ANS_run_success=K_Means(get_algo_parameters,
								  run_it,
								  inputdim,
								  outputdim,
								  trainset,
								  trainsetsize,
								  testset,
								  testsetsize,
								  output,
								  classif);
		  break;

  case 3: ANS_run_success=Krazy_K_Means(get_algo_parameters,
								  run_it,
								  inputdim,
								  outputdim,
								  trainset,
								  trainsetsize,
								  testset,
								  testsetsize,
								  output,
								  classif);
		  break;

  case 4: ANS_run_success=MaxMin_Distance(get_algo_parameters,
								  run_it,
								  inputdim,
								  outputdim,
								  trainset,
								  trainsetsize,
								  testset,
								  testsetsize,
								  output,
								  classif);
		  break;

  case 5: ANS_run_success=MaxMin_Distance_with_Tm_Estimation
								 (get_algo_parameters,
								  run_it,
								  inputdim,
								  outputdim,
								  trainset,
								  trainsetsize,
								  testset,
								  testsetsize,
								  output,
								  classif);
		  break;

  case 6: ANS_run_success=Nearest_Neighbor_Classifier
								 (get_algo_parameters,
								  run_it,
								  inputdim,
								  outputdim,
								  trainset,
								  trainsetsize,
								  testset,
								  testsetsize,
								  output,
								  classif);
		  break;

  default:break;
  }
 }
mbeep();
return(msel);
}


/*-----------------------------------------------------------------------*/

void non_ans_module(void)
{
mprintf("\n\n");
mprintf("Conventional (Non-ANS) Algorithms.\n");
mprintf("Batch and experimentation mode.\n");
mprintf("(added for comparison purposes.)\n");

one_ans_one_problem_menu(4,non_ans_menu);
}

/*- Note ----------------------------------------------------------------*/
/*     ENTIRE MODULE SHOULD BE RE-WRITTEN IF FURTHER USE OF NON-ANS      */
/*                   ALGORITHMS IS EXPECTED,                             */
/*-----------------------------------------------------------------------*/


