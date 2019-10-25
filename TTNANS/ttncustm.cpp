/*
   -------------------
   TTNANS:
   TTNCUSTM.C ver.0.01
   -------------------
   V.N.Nikolaidis
   ------------------------
   Custom Experimental
   Algorithms.
   ------------------------
*/

#include "ttndef.h"
#include "ttndef_o.h"
#include "ttnsets.h"

#include "ttnmain.h"
#include "ttndata1.h"
#include "ttndata2.h"
#include "ttnprb.h"
#include "ttnfname.h"
#include "ttnui.h"
#include "ttnmath.h"
#include "ttnprepr.h"

#include "tmatrix.h"

/*-----------------------------------------------------------------------*/

extern bool Custom_Agglo_Clustering_Weighted_Average
			(DATA **	p_data,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
             unsigned	n_cols,					// dimentionality of each p_set vector
             DATA *		p_class,				// returned clustering index (n_rows x 1) 
             unsigned   method = 0);


/*-----------------------------------------------------------------------*/
#ifdef _OLD_AGGLOCUMULATIVE_VERSIONS_
/*-----------------------------------------------------------------------*/

bool Custom_Agglo_Clustering
			(DATA **	p_data,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
             unsigned	n_cols,					// dimentionality of each p_set vector
             DATA *		p_class,				// returned clustering index (n_rows x 1) 
             unsigned   method = 0)
{
bool run_ok=true;

mprintf("\nInvoking Custom_Agglomerative_Clustering (on %u x % u set)\n\n",n_rows,n_cols);

mhintclear();
mhintf(true,"This is an experimental algorithm in BETA stage.\n");
mhintf(true,"\n");
mhintf(true,"The threshold t is used on the equality check.\n");
mhintf(true,"Elements with distance <= t are considered equal.\n");
mhintf(true,"\n");

switch(method)
 {
 case 1:														// if they are both NN of each other, merge them... 
	  mhintf(true,"The selected merging method merges (averages) two elements \n");
	  mhintf(true,"if they are both nearest neighbors of each other.\n");
      mhintf(true,"\n");
 break;
  
 case 2:														// if they are both NN of each other, merge them...
	  mhintf(true,"The selected merging method merges (averages) an element with\n");
	  mhintf(true,"all its nearest neighbors. Avoid this method if you want\n");
	  mhintf(true,"to have outliers classified by themselves.\n");
      mhintf(true,"\n");
 break;

 default:
	 mhintf(true,"Unknown merging method.\n"); 
 break;
 }


CTmatrix <DATA> data_1 (p_data,n_rows,n_cols, "Working copy #1 of training set");
CTmatrix <DATA> data_2 (p_data,n_rows,n_cols, "Working copy #2 of training set");

CTmatrix <DATA> * pd1 = & data_1;
CTmatrix <DATA> * pd2 = & data_2;
CTmatrix <DATA> * pdt;

CTvector <DATA> NN_distance  	(n_rows,LARGEDATA);
CTvector <int>  number_of_NNs	(n_rows,1);

CTvector <bool> is_classified	(n_rows,false);	// if value is false (0) then this is a 'cluster center'.
CTvector <int>  is_in_class		(n_rows,-1);

DATA d;
DATA threshold = mrequest_DATA("Enter threshold t (default=0)");
bool add_r2_to_r1;
bool add_r1_to_r2;

mprintf("Merging method : %d , Equality Threshold %f .\n",method,threshold);

bool found_a_NN = true;
bool not_converged = true;
unsigned r1,r2,c,i;
int num_classified = 0;
int num_classes = n_rows;

bool rerun = true;

// Step 1. Initially all items are at their own class.

for(r1=0 ;r1<n_rows; r1++)
 is_in_class.at(r1) = r1;

while(rerun)
 {
 mstarttick("Merging Classes...");

 while((TGBL no_error) AND (num_classes > TGBL outputdim) AND (not_converged))
  {
  for(r1=0 ;r1<n_rows; r1++) NN_distance.at(r1) = LARGEDATA;

// Step 2. Find distances to nearest neighbors(s) (NNs).

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   for(r2=r1+1; r2<n_rows; r2++) if(NOT is_classified.at(r2))
      {
      d = EuclideanDistance(pd1->row(r1),pd1->row(r2),n_cols); 
      if( d < NN_distance.at(r1) ) NN_distance.at(r1) = d;
      if( d < NN_distance.at(r2) ) NN_distance.at(r2) = d;
      }

// Step 3. Merge coordinates using average of this and nearest neigbour(s)'. 

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   {
   number_of_NNs.at(r1)=1;										// including this record (at r1)...
   for(c=0 ;c<n_cols; c++) 
    pd2->at(r1,c) = pd1->at(r1,c);								// copy this record to pd2.
   }

// Step 3.1 Main coordinate merging step.

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   {
   for(r2=r1+1; r2<n_rows; r2++) if(NOT is_classified.at(r2))
    {

// Step 3.2 Continue merging coordinates.

    found_a_NN = false;
    add_r2_to_r1 = add_r1_to_r2 = false;

    d = EuclideanDistance(pd1->row(r1),pd1->row(r2),n_cols); 

    switch(method)
     {
 
     case 1:													// if they are both NN of each other, merge them... 
    
     if( d == NN_distance.at(r1) )								// r2 is a NN of r1.
     if( d == NN_distance.at(r2) )								// r1 is a NN of r2. 
  	  {
      add_r2_to_r1 = true;
      add_r1_to_r2 = true;
      found_a_NN = true;
      }

     break;
  
     case 2:													// if they are both NN of each other, merge them...

     if( d == NN_distance.at(r1) )								// r2 is a NN of r1.
	  {
      add_r2_to_r1 = true;
      found_a_NN = true;
      }

     if( d == NN_distance.at(r2) )								// r1 is a NN of r2.
      {
	  add_r1_to_r2 = true;
      found_a_NN = true;
      }

     break;

     default: mprintf("Unknown merging method.\n"); not_converged = run_ok = false; 
     break;

     }

	if(add_r2_to_r1)											// add NN record to pd2 r1.
     {
     for(c=0 ;c<n_cols; c++)
      pd2->at(r1,c) = pd2->at(r1,c) + pd1->at(r2,c);
     number_of_NNs.at(r1)=number_of_NNs.at(r1)+1;
     }

	if(add_r1_to_r2)											// add NN record to pd2 r2.
     {
     for(c=0 ;c<n_cols; c++)
      pd2->at(r2,c) = pd2->at(r2,c) + pd1->at(r1,c);
     number_of_NNs.at(r2)=number_of_NNs.at(r2)+1;
     }

// Step 3.3 Merge classes.

//  if(found_a_NN)
     {
     if(d<=threshold)
      {
      int old_r1_class = is_in_class.at(r1);
      int old_r2_class = is_in_class.at(r2);

      c = min (old_r1_class,r2);
      c = min (old_r2_class,c);									// new class id for both will be the minimum...
      
      if(r1 != c)
       {
       is_classified.at(r1) = true;
       num_classified ++;
       num_classes --;        
       }

      if(r2 != c)
       {
       is_classified.at(r2) = true;
       num_classified ++;        
       num_classes --;        
       }

      for(i=0;i<n_rows;i++)
       {
       if(is_in_class.at(i) == old_r1_class) is_in_class.at(i)=c;
       if(is_in_class.at(i) == old_r2_class) is_in_class.at(i)=c;
       }
      }
     }

    }
   }

// Step 4. Average coordinates.
 
  d=0;

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   {
   for(c=0 ;c<n_cols; c++)
    pd2->at(r1,c) = pd2->at(r1,c) / number_of_NNs.at(r1);		// average sum of neighbors.

   d+=EuclideanDistance(pd1->row(r1),pd2->row(r1),n_cols);
   }
  if(d == 0) 
   {
   mprintf("Converged in %d classes, exiting.\n",num_classes);
   not_converged = false;
   }

  pdt = pd2;
  pd2 = pd1;
  pd1 = pdt;

  mtick(num_classified,n_rows); 
  }

 mendtick();

// Step 5. Done. Correct the "holes" found in p_class ids. These are created when we are merging clusters.

 if(run_ok) 
  {
  int cur_ct=0;
  int iter_ct = 0;
  int max_ct  = 0; 
  bool found_one = false;
 
  for(r1=0;r1<n_rows;r1++) p_class[r1]=-1;
  for(r1=0;r1<n_rows;r1++) if(is_in_class.at(r1)>max_ct) max_ct = is_in_class.at(r1);

  while(iter_ct<=max_ct)
   {
   found_one = false;
   for(r1=0;r1<n_rows;r1++) 
    if(is_in_class.at(r1)==iter_ct)
     {
 	 found_one=true;
     p_class[r1]=(DATA)cur_ct;
     }
   if(found_one) cur_ct++;
   iter_ct++;
   }

  mprintf("Done, producing %d classes.\n",(int)num_classes);
  }

// since most of the calculations for y classes are done for x>y classes, ask to continue.

 if((num_classes>1) AND (not_converged))
  {
  mprintf("Currently produced %d classes (requested %d classes).\n",num_classes,TGBL outputdim);
  mprintf("The method can continue to merge classes, producing classifications with less classes.\n");
  rerun=mrequest_yn("Continue merging to less classes? (Last classification will be saved first)");
  if(rerun)
   {
   c = mrequest_int("Please enter new number of desired classes.");
   if(c >= TGBL outputdim)
    {
    mprintf("New requested number of classes (%d) is not smaller than old (%d), exiting.\n",c,TGBL outputdim);
    rerun=false;
    }
   else
    {
    ShowClassif();
    SaveClassif("","TTNANS - Custom Method - Classification Results",true);
    SavePreprocessedClasses ("testclass",true);
    SaveClasses(TGBL prbfname,"ansclass",true);
    TGBL outputdim = c;
    }
   }
  }
 else
  {
  rerun = false;
  }

 }

if(run_ok)
 {
 mprintf("Returns OK, producing %d classes.\n",(int)num_classes);
 TGBL outputdim=num_classes;
 }

return run_ok;
}

/*-----------------------------------------------------------------------*/

bool Custom_Agglo_Clustering_Weighted_1_Average
			(DATA **	p_data,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
             unsigned	n_cols,					// dimentionality of each p_set vector
             DATA *		p_class,				// returned clustering index (n_rows x 1) 
             unsigned   method = 0)
{
bool run_ok=true;

mprintf("\nInvoking Custom_Agglomerative_Clustering (on %u x % u set)\n\n",n_rows,n_cols);

mhintclear();
mhintf(true,"This is an experimental algorithm in BETA stage.\n");
mhintf(true,"\n");
mhintf(true,"The threshold t is used on the equality check.\n");
mhintf(true,"Elements with distance <= t are considered equal.\n");
mhintf(true,"\n");
mhintf(true,"With this weighted average adjustment method enabled, the number of\n");
mhintf(true,"records a point represents (records classified with and merged at\n");
mhintf(true,"the point) are used to bias the coordinate adjustments.\n");
mhintf(true,"\n");

switch(method)
 {
 case 1:														// if they are both NN of each other, merge them... 
	  mhintf(true,"The selected merging method merges (averages) two elements \n");
	  mhintf(true,"if they are both nearest neighbors of each other.\n");
      mhintf(true,"\n");
 break;
  
 case 2:														// if they are both NN of each other, merge them...
	  mhintf(true,"The selected merging method merges (averages) an element with\n");
	  mhintf(true,"all its nearest neighbors. Avoid this method if you want\n");
	  mhintf(true,"to have outliers classified by themselves.\n");
      mhintf(true,"\n");
 break;

 default:
	 mhintf(true,"Unknown merging method.\n"); 
 break;
 }


CTmatrix <DATA> data_1 (p_data,n_rows,n_cols, "Working copy #1 of training set");
CTmatrix <DATA> data_2 (p_data,n_rows,n_cols, "Working copy #2 of training set");

CTmatrix <DATA> * pd1 = & data_1;
CTmatrix <DATA> * pd2 = & data_2;
CTmatrix <DATA> * pdt;

CTvector <DATA> NN_distance  	(n_rows,LARGEDATA);
CTvector <int>  number_of_NNs	(n_rows,1);

CTvector <bool> is_classified	(n_rows,false);	// if value is false (0) then this is a 'cluster center'.
CTvector <int>  is_in_class		(n_rows,-1);
CTvector <int>	items_in_class_1(n_rows,1);		
CTvector <int>	items_in_class_2(n_rows,1);		
CTvector <int>  * piic1 = & items_in_class_1;
CTvector <int>  * piic2 = & items_in_class_2;
CTvector <int>  * piict;

DATA d;
DATA threshold = mrequest_DATA("Enter threshold t (default=0)");
bool add_r2_to_r1;
bool add_r1_to_r2;

mprintf("Merging method : %d , Equality Threshold %f .\n",method,threshold);

bool found_a_NN = true;
bool not_converged = true;
unsigned r1,r2,c,i;
int num_classified = 0;
int num_classes = n_rows;

bool rerun = true;

// Step 1. Initially all items are at their own class.

for(r1=0 ;r1<n_rows; r1++)
 is_in_class.at(r1) = r1;

while(rerun)
 {
 mstarttick("Merging Classes...");

 while((TGBL no_error) AND (num_classes > TGBL outputdim) AND (not_converged))
  {

  for(r1=0 ;r1<n_rows; r1++) NN_distance.at(r1) = LARGEDATA;

// Step 2. Find distances to nearest neighbors(s) (NNs).

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   for(r2=r1+1; r2<n_rows; r2++) if(NOT is_classified.at(r2))
      {
      d = EuclideanDistance(pd1->row(r1),pd1->row(r2),n_cols); 
      if( d < NN_distance.at(r1) ) NN_distance.at(r1) = d;
      if( d < NN_distance.at(r2) ) NN_distance.at(r2) = d;
      }

// Step 3. Merge coordinates using average of this and nearest neigbour(s)'. 

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   {
   number_of_NNs.at(r1)=0;
   for(c=0 ;c<n_cols; c++) pd2->at(r1,c) = 0;
   }

// Step 3.1 Main coordinate merging step.

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   {
   for(r2=r1+1; r2<n_rows; r2++) if(NOT is_classified.at(r2))
    {

// Step 3.2 Continue merging coordinates

    found_a_NN = false;
    add_r2_to_r1 = add_r1_to_r2 = false;

    d = EuclideanDistance(pd1->row(r1),pd1->row(r2),n_cols); 

    switch(method)
     {
 
     case 1:													// if they are both NN of each other, merge them... 
    
     if( d == NN_distance.at(r1) )								// r2 is a NN of r1.
     if( d == NN_distance.at(r2) )								// r1 is a NN of r2. 
  	  {
      add_r2_to_r1 = true;
      add_r1_to_r2 = true;
      }

     break;
  
     case 2:													// if NN, merge ...

     if( d == NN_distance.at(r1) )								// r2 is a NN of r1.
	  {
      add_r2_to_r1 = true;
      }

     if( d == NN_distance.at(r2) )								// r1 is a NN of r2.
      {
	  add_r1_to_r2 = true;
      }

     break;

     default: mprintf("Unknown merging method.\n"); not_converged = run_ok = false; 
     break;

     }

	if(add_r2_to_r1)											// add NN record to pd2 r1.
     {
     for(c=0 ;c<n_cols; c++)
      {
      pd2->at(r1,c) = pd2->at(r1,c) + (pd1->at(r2,c) * piic1->at(r2));
      }
     number_of_NNs.at(r1)=number_of_NNs.at(r1) + piic1->at(r2);
     found_a_NN = true;
     }

	if(add_r1_to_r2)											// add NN record to pd2 r2.
     {
     for(c=0 ;c<n_cols; c++)
	  {
      pd2->at(r2,c) = pd2->at(r2,c) + (pd1->at(r1,c) * piic1->at(r1));
	  }
     number_of_NNs.at(r2)=number_of_NNs.at(r2) + piic1->at(r1);
     found_a_NN = true;
     }

// Step 3.2 Merge classes if coordinates overlap.

    if(found_a_NN)												// Some coordinate adjustent took place...
     {
     if(d<=threshold)
      {
      int old_r1_class = is_in_class.at(r1);
      int old_r2_class = is_in_class.at(r2);

      c = min (old_r1_class,r2);
      c = min (old_r2_class,c);									// new class id for both will be the minimum...
      
      if(r1 != c)
       {
       is_classified.at(r1) = true;
       num_classified ++;
       num_classes --;        
       }

      if(r2 != c)
       {
       is_classified.at(r2) = true;
       num_classified ++;        
       num_classes --;        
       }

      piic2->at(c) = 0;	

      for(i=0;i<n_rows;i++)
       {
       if(is_in_class.at(i) == old_r1_class) is_in_class.at(i)=c;
       if(is_in_class.at(i) == old_r2_class) is_in_class.at(i)=c;
       if(is_in_class.at(i) == c) piic2->at(c) = piic2->at(c) + 1;
       }
      }
     }

    }
   }

// Step 4. Average coordinates.

  d=0;

  for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified.at(r1))
   {
   for(c=0 ;c<n_cols; c++)
    pd2->at(r1,c) = pd2->at(r1,c) + (pd1->at(r1,c) * piic1->at(r1));
   
   for(c=0 ;c<n_cols; c++)
    pd2->at(r1,c) = pd2->at(r1,c) / (piic1->at(r1) + number_of_NNs.at(r1));		// average sum of neighbors.

   d+=EuclideanDistance(pd1->row(r1),pd2->row(r1),n_cols);
   }
  if(d == 0) 
   {
   mprintf("Converged in %d classes, exiting.\n",num_classes);
   not_converged = false;
   }

#ifdef  _DEBUG_THIS_METHOD__

//debug info:

pd2->show();
mprintf("\nis classified:\n");
is_classified.show();
mprintf("\npoints in class:\n");
piic2->show();
mprintf("\nis in class:\n");
is_in_class.show();
mprintf("\n");

//Shows movement of cluster representators:

for(r1=0;r1<n_rows;r1++)
if(is_classified.at(r1)==0) 
 {
 mprintf("2 \t%d \t",r1);
 for(c=0;c<n_cols;c++)
  mprintf("%f \t",pd2->at(r1,c));
 mprintf("\n");
 }

#endif // _DEBUG_THIS_METHOD__

  pdt = pd2;
  pd2 = pd1;
  pd1 = pdt;

  piict = piic2;
  piic2 = piic1;
  piic1 = piict;

  mtick(num_classified,n_rows); 
  }

 mendtick();

// Step 5. Done. Correct the "holes" found in p_class ids. These are created when we are merging clusters.

 if(run_ok) 
  {
  int cur_ct=0;
  int iter_ct = 0;
  int max_ct  = 0; 
  bool found_one = false;
 
  for(r1=0;r1<n_rows;r1++) p_class[r1]=-1;
  for(r1=0;r1<n_rows;r1++) if(is_in_class.at(r1)>max_ct) max_ct = is_in_class.at(r1);

  while(iter_ct<=max_ct)
   {
   found_one = false;
   for(r1=0;r1<n_rows;r1++) 
    if(is_in_class.at(r1)==iter_ct)
     {
 	 found_one=true;
     p_class[r1]=(DATA)cur_ct;
     }
   if(found_one) cur_ct++;
   iter_ct++;
   }

  mprintf("\nClusters are represented at :\n");
  for(r1=0;r1<n_rows;r1++)
  if(is_classified.at(r1)==0) 
   {
   mprintf("Row %d : \t ( ",r1);
   for(c=0;c<n_cols;c++)
    mprintf("%f \t",pd2->at(r1,c));
   mprintf(" ) \n");
   }
  mprintf("\n");

  mprintf("Done, producing %d classes.\n",(int)num_classes);
  }

// since most of the calculations for y classes are done for x>y classes, ask to continue.

 if((num_classes>1) AND (not_converged))
  {
  mprintf("Currently produced %d classes (requested %d classes).\n",num_classes,TGBL outputdim);
  mprintf("The method can continue to merge classes, producing classifications with less classes.\n");
  rerun=mrequest_yn("Continue merging to less classes? (Last classification will be saved first)");
  if(rerun)
   {
   c = mrequest_int("Please enter new number of desired classes.");
   if(c >= TGBL outputdim)
    {
    mprintf("New requested number of classes (%d) is not smaller than old (%d), exiting.\n",c,TGBL outputdim);
    rerun=false;
    }
   else
    {
    ShowClassif();
    SaveClassif("","TTNANS - Custom Method - Classification Results",true);
    SavePreprocessedClasses ("testclass",true);
    SaveClasses(TGBL prbfname,"ansclass",true);
    TGBL outputdim = c;
    }
   }
  }
 else
  {
  rerun = false;
  }

 }

if(run_ok)
 {
 mprintf("Returns OK, producing %d classes.\n",(int)num_classes);
 TGBL outputdim=num_classes;
 }

return run_ok;
}

/*-----------------------------------------------------------------------*/
#endif //  _OLD_AGGLOCUMULATIVE_VERSIONS_
/*-----------------------------------------------------------------------*/

#undef _DEBUG_THIS_METHOD_
//#define  _DEBUG_THIS_METHOD_

bool Custom_Agglo_Clustering
			(DATA **	p_data,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
             unsigned	n_cols,					// dimentionality of each p_set vector
             DATA *		p_class,				// returned clustering index (n_rows x 1) 
             unsigned   method = 0)
{
bool run_ok=true;
int old_converge_point = - 1;
 
mprintf("\nInvoking Custom_Agglomerative_Clustering (on %u x % u set)\n\n",n_rows,n_cols);

mhintclear();
mhintf(true,"This is an experimental algorithm.\n");
mhintf(true,"\n");
mhintf(true,"The threshold t is used on the equality check.\n");
mhintf(true,"Elements with distance <= t are considered equal.\n");
mhintf(true,"\n");

switch(method)
 {
 case 1:														// if they are both NN of each other, merge them... 
	  mhintf(true,"The selected merging method merges (averages) two elements \n");
	  mhintf(true,"if they are both nearest neighbors of each other.\n");
      mhintf(true,"\n");
 break;
  
 case 2:														// if they are both NN of each other, merge them...
	  mhintf(true,"The selected merging method merges (averages) an element with\n");
	  mhintf(true,"all its nearest neighbors. Avoid this method if you want\n");
	  mhintf(true,"to have outliers classified by themselves.\n");
      mhintf(true,"\n");
 break;

 default:
	 mhintf(true,"Unknown merging method.\n"); 
 break;
 }

CTvector <DATA> NN_distance  	(n_rows,LARGEDATA);
CTvector <int>  is_in_class		(n_rows,-1);

CTmatrix <DATA> data_1 (p_data,n_rows,n_cols, "Working copy #1 of training set");
CTmatrix <DATA> data_2 (p_data,n_rows,n_cols, "Working copy #2 of training set");
CTmatrix <DATA> * p_data_now  = & data_1;
CTmatrix <DATA> * p_data_next = & data_2;
CTmatrix <DATA> * p_dtemp;

CTvector <bool> is_classified_now 	(n_rows,false);	// if value is false (0) then this is a 'cluster center'.
CTvector <bool> is_classified_next	(n_rows,false);	

CTvector <int>	NNs (n_rows,1);		

DATA d;
DATA threshold = mrequest_DATA("Enter threshold t (default = 0.0001)");
bool add_r2_to_r1;
bool add_r1_to_r2;

mprintf("Merging method : %d , Equality Threshold %f .\n",method,threshold);

bool found_a_NN = true;
bool not_converged = true;
unsigned r1,r2,c,i,tcount;
int num_classified = 0;
int num_classes = n_rows;

bool rerun = true;
bool check_converge;

mhintf(true,"\n");
mhintf(true,"Convergence (no movement after a complete iteration) may be\n");
mhintf(true,"caused by identical record values. By selecting NO in the corresponding\n");
mhintf(true,"request you ensure that the number of classes created will be\n");
mhintf(true,"closer to the requested number of classes.\n");
mhintf(true,"The program will always stop if total change equals 0 and no\n");
mhintf(true,"nearest neighbour record is found for all records considered.\n");
mhintf(true,"\n");

check_converge = mrequest_yn("Stop on total change equal to 0?");

// Step 1. Initially all items are at their own class.

for(r1=0 ;r1<n_rows; r1++)
 is_in_class.at(r1) = r1;

while(rerun)
	{

   	mstarttick("Merging Classes...");

	while((TGBL no_error) AND (num_classes > TGBL outputdim) AND (not_converged))
		{

		for(r1=0 ;r1<n_rows; r1++) NN_distance.at(r1) = LARGEDATA;

// Step 2. Find distances to nearest neighbors(s) (NNs).

		for(r1=0 ;r1<n_rows; r1++)    if(NOT is_classified_now .at(r1))
		for(r2=r1+1; r2<n_rows; r2++) if(NOT is_classified_now .at(r2))
			{
			d = EuclideanDistance(p_data_now ->row(r1),p_data_now ->row(r2),n_cols); 
			if( d < NN_distance.at(r1) ) NN_distance.at(r1) = d;
			if( d < NN_distance.at(r2) ) NN_distance.at(r2) = d;
			}

// Step 3. Merge coordinates using average of this and nearest neigbour(s)': 

		for(r1=0 ;r1<n_rows; r1++) // if(NOT is_classified_now .at(r1))
			{
		    for(c=0 ;c<n_cols; c++)	p_data_next->at(r1,c) = p_data_now->at(r1,c);		// initialize new to old;
			NNs.at(r1) = 1;																// now 1 (itself).
			}

// Start main loop.

		found_a_NN = false;

		for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified_now .at(r1))
			for(r2=r1+1; r2<n_rows; r2++) if(NOT is_classified_now .at(r2))
				{

				add_r2_to_r1 = add_r1_to_r2 = false;

				d = EuclideanDistance(p_data_now ->row(r1),p_data_now ->row(r2),n_cols); 

				switch(method)
					{
 
					case 1:														// if they are both NN of each other, merge them... 
   					if( ( d == NN_distance.at(r1) ) AND 						// r2 is a NN of r1.
					    ( d == NN_distance.at(r2) )	)							// r1 is a NN of r2. 
  						{
						add_r2_to_r1 = true;
						add_r1_to_r2 = true;
						}
					break;
  
					case 2:													// if NN merge ...
					if( d == NN_distance.at(r1) )							// r2 is a NN of r1.
						add_r2_to_r1 = true;
					if( d == NN_distance.at(r2) )							// r1 is a NN of r2.
						add_r1_to_r2 = true;
					break;

					default:
					
					mprintf("Unknown merging method.\n");
					not_converged = run_ok = false; 

					break;

					}

				if(add_r2_to_r1)										// add NN record to p_data_next r1.
					{
					for(c=0 ;c<n_cols; c++)
						p_data_next->at(r1,c) += p_data_now ->at(r2,c);
					NNs.at(r1) ++;
					found_a_NN = true;
					}


				if(add_r1_to_r2)										// add NN record to p_data_next r2.
					{
					for(c=0 ;c<n_cols; c++)
						p_data_next->at(r2,c) += p_data_now ->at(r1,c);
					NNs.at(r2) ++;
					found_a_NN = true;
					}
				}

// End main loop.

		
// Step 4. Average coordinates.

		for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified_now .at(r1))
			for(c=0 ;c<n_cols; c++)
				p_data_next->at(r1,c) /= NNs.at(r1);									// ... creating new averaged sum of neighbors.
				

// Step 5. Merge classes if coordinates overlap.
// Start secondary loop.

		for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified_now .at(r1))
			for(r2=r1+1; r2<n_rows; r2++) if(NOT is_classified_now .at(r2))
				{

				d = EuclideanDistance(p_data_now ->row(r1),p_data_now ->row(r2),n_cols); 

				if(d<=threshold)
					{
					int old_r1_class = is_in_class.at(r1);
					int old_r2_class = is_in_class.at(r2);

					c = min (old_r1_class,r2);
					c = min (old_r2_class,c);						// new class id for both (c) will be the minimum of old ...

                    if(r1 != c)										// r1 is not the new cluster center.
						{
						if(NOT is_classified_next.at(r1))
							{
							num_classified ++;
							num_classes --;        
							is_classified_next.at(r1) = true;
							}
						}

					if(r2 != c)										// r2 is not the new cluster center.
						{
						if(NOT is_classified_next.at(r2))
							{
							num_classified ++;        
							num_classes --;        
							is_classified_next.at(r2) = true;
							}
						}
					
					tcount = 0;
					for(i=0;i<n_rows;i++)
						{
   						if(is_in_class.at(i) == old_r1_class) is_in_class.at(i)=c;
						if(is_in_class.at(i) == old_r2_class) is_in_class.at(i)=c;
						}
					}
			}

// end secondary loop


//  Step 6. Convergence checking.

		d=0;
		for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified_now .at(r1))
			{
			d+=EuclideanDistance(p_data_now ->row(r1),p_data_next->row(r1),n_cols);
		    }
		if( (d == 0) )
			{
			if(NOT found_a_NN) 
				{
				mprintf("\n - Converged in %d classes (last total movement was 0 and no NN found), exiting - \n",num_classes);
				not_converged = false;
				}
			else 
				{	
				if(old_converge_point != (int)num_classes)
					{
					mprintf("\n - ");
					mprintf("Total movement equals 0 in %d classes , ",num_classes);
					if(check_converge)
						{
						mprintf("exiting.");
						not_converged = false;
						}
					else mprintf("continuing.");
					mprintf(" - \n");
					old_converge_point = (int)num_classes;
					}
				}
			}


// switch sets (now <-> next).

		p_dtemp = p_data_next;
		p_data_next = p_data_now ;
		p_data_now  = p_dtemp;

		for(r1=0 ;r1<n_rows; r1++)
			{
			is_classified_now .at(r1) = is_classified_now .at(r1) OR is_classified_next.at(r1);
			is_classified_next.at(r1) = false;
			}


#ifdef  _DEBUG_THIS_METHOD_

//debug info:

mprintf("\n Start Debug info ----------------------------- \n");

mprintf("\nis classified:\n");
is_classified_now .show();
mprintf("\nold items_in_class:\n");
p_items_in_class_next->show();
mprintf("\nnew items_in_class:\n");
p_items_in_class_now ->show();
mprintf("\nis in class:\n");
is_in_class.show();
mprintf("\n");

//Shows movement of cluster representators:

mprintf("\n Clusters : \n");

for(r1=0;r1<n_rows;r1++)
if(is_classified_now .at(r1)==false) 
 {
 mprintf("@matrix 2,\t%d \t",r1);
 for(c=0;c<n_cols;c++)
  mprintf("%f \t",p_data_now->at(r1,c));
 mprintf("\n");
 }

mprintf("\nNew data set is :\n");
for(r1=0;r1<n_rows;r1++)
 {
 mprintf("@matrix 2,\t%d \t",r1);
 for(c=0;c<n_cols;c++)
  mprintf("%f \t",p_data_now->at(r1,c));
 mprintf("\n");
 }

mprintf("\n End Debug info -----------------------------\n\n");

#endif // _DEBUG_THIS_METHOD_

		mtick(num_classified,n_rows); 
		}
 
	mendtick();

// Step 5. Done. Correct the "holes" found in p_class ids. These are created when we are merging clusters.

 if(run_ok) 
  {
  int cur_ct=0;
  int iter_ct = 0;
  int max_ct  = 0; 
  bool found_one = false;
 
  for(r1=0;r1<n_rows;r1++) p_class[r1]=-1;
  for(r1=0;r1<n_rows;r1++) if(is_in_class.at(r1)>max_ct) max_ct = is_in_class.at(r1);

  while(iter_ct<=max_ct)
   {
   found_one = false;
   for(r1=0;r1<n_rows;r1++) 
    if(is_in_class.at(r1)==iter_ct)
     {
 	 found_one=true;
     p_class[r1]=(DATA)cur_ct;
     }
   if(found_one) cur_ct++;
   iter_ct++;
   }

   {
   int count = 0;
   mprintf("\nClusters are represented at :\n");
   for(r1=0;r1<n_rows;r1++)
   if(NOT is_classified_now .at(r1)) 
    {
    mprintf("Row %d : \t ( ",r1);
    for(c=0;c<n_cols;c++)
     mprintf("%f \t",p_data_next->at(r1,c));
    mprintf(" ) \n");
    count++;
    }
  
   mprintf("\n");   
   mprintf("Done, producing %d classes.\n",(int)num_classes);

   if(count!=num_classes) 
    {
    run_ok=false;
    mprintf("Check Algorithm: %d must be equal to %d !.\n",(int)num_classes,count);
    }

   if(count+num_classified != n_rows) 
    {
    run_ok=false;
    mprintf("Check Algorithm: %d + %d = %d must be equal to %d !.\n",count,num_classified,count+num_classified,n_rows);
    }
  
   }
  }
  
// since most of the calculations for y classes are done for x>y classes, ask to continue.

 if((run_ok) AND (num_classes>1) AND (not_converged))
  {
  mprintf("Currently produced %d classes (requested %d classes).\n",num_classes,TGBL outputdim);
  mprintf("The method can continue to merge classes, producing classifications with less classes.\n");
  rerun=mrequest_yn("Continue merging to less classes? (Last classification will be saved first)");
  if(rerun)
   {
   c = mrequest_int("Please enter new number of desired classes.");
   if(c >= TGBL outputdim)
    {
    mprintf("New requested number of classes (%d) is not smaller than old (%d), exiting.\n",c,TGBL outputdim);
    rerun=false;
    }
   else
    {
    ShowClassif();
    SaveClassif("","TTNANS - Custom Method - Classification Results",true);
    SavePreprocessedClasses ("testclass",true);
    SaveClasses(TGBL prbfname,"ansclass",true);
    TGBL outputdim = c;
    }
   }
  }
 else
  {
  rerun = false;
  }
 }

if(run_ok)
 {
 mprintf("Returns OK, producing %d classes.\n",(int)num_classes);
 TGBL outputdim=num_classes;
 }

return run_ok;
}

/*-----------------------------------------------------------------------*/

bool Custom_Gravity_Clustering
			(DATA **	p_dset,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
             unsigned	n_cols,					// dimentionality of each p_set vector
             DATA *		p_class)				// returned clustering index (n_rows x 1) 

{
mprintf("\nInvoking Gravity Clustering (on %u x % u set)\n\n",n_rows,n_cols);
mhintclear();
mhintf(true,"This is an experimental algorithm in GAMMA stage.\n");
mhintf(true,"\n");

bool run_ok=true;

mprintf("\nCode under construction.\nNot complete in this version,exiting.\n");
run_ok=false;

/*
CTmatrix <DATA> data_1 (p_dset,n_rows,n_cols, "Working copy #1 of training set");
CTmatrix <DATA> data_2 (p_dset,n_rows,n_cols, "Working copy #2 of training set");

CTvector <int>  placed_in_class  (n_rows,-1);
CTvector <int>  items_in_class   (n_rows,1);

DATA distance;

CTmatrix <DATA> * pd1 = data_1;
CTmatrix <DATA> * pd2 = data_2;
CTmatrix <DATA> * pdt;

unsigned r1,r2;

// Step 1. All items are at their own class.

for(r1=0; r1<n_rows; r1++)
 placed_in_class.at(r1) = r1;

// Step 2. Move them...

for(r1=0; r1<n_rows; r1++)
 for(r2=0; r2<n_rows; r2++)
  {
  distance = EuclideanDistance(pd1->[r1],pd1->[r2],n_cols); 
  if(distance == 0)
	  {
	  max_id = max(r1,r2);
	  min_id = min(r1,r2);
	  is_classified.at(max_id) = true;
	  placed_in_class.at(max_id) = placed_in_class.at(min_id);
	  items_in_class.at(max_id)--;
	  items_in_class.at(min_id)++;
	  num_classified ++;
	  }
   
  }
*/
return run_ok;
}

/*-----------------------------------------------------------------------*/

bool Split_Set(int splits,int rows,DATA * split_index)
{
 static bool showinfo=true;
 int size;
 int i,counter,clss;

 mprintf("Split (Testing) set into %d sets.\n",splits);
 mprintf(" \n");
 if(!IS_CLUSTERING_PROBLEM)
  {
  mprintf("Note: This uses the test set and ignores any reordering\n");
  mprintf("      or scaling performed on any other sets.          \n");
  mprintf(" \n");
  }

 mprintf(" \n");
 mprintf("Split Set:\n");
 mprintf(" \n");
 mhintclear();
 mhintf(showinfo,"This algorithm splits the given set into a requested number of classes\n");
 mhintf(showinfo,"(%d in this case) of (default) equal size (number of records). If the set cannot \n",splits);
 mhintf(showinfo,"be split evenly, the last class will contain the remaining events.\n");
 mhintf(showinfo,"If split number (output size) is one no spliting takes place.\n");
 mhintf(showinfo," \n");
 showinfo=false;
 
 if((TGBL no_error)&&
   (rows>0)&&
   (splits>0)&&
   (rows>=splits))
  {

  if(mrequest_yn("Split set into equally-sized classes (default)?"))
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
    }
   else
   {
   int splitpoint=10;
   int oldsplitpoint=-1;
   bool doit;

   i=0;
   counter=0;
   clss=0;

   mprintf("Spliting set of size %d into %d (user-defined split-points).\n",splits,rows);
   mprintf("All split-points s should be in 0 <= s < %d. The first record is 0.\n",rows);
   mprintf("Splits will take place after split-point.\n\n");
    
   while (clss < splits)
    {
    doit = false;
    if(clss < splits - 1)
     {
     splitpoint=mrequest_int("Please select split-point.");
     if((splitpoint >= 0) AND (splitpoint > oldsplitpoint) AND (splitpoint <= (rows-(splits-clss))))
      doit=true;
     else
      mprintf("Can not use s=%d as a split-point (%d < s <= %d). Retry.\n",splitpoint,oldsplitpoint,rows-(splits-clss));
      }
    else
     {
     mprintf("No split point needed for last class.\n");
     splitpoint=rows-1;
     doit = true;
     }

    if(doit)
     {
     counter = 0;
     i=oldsplitpoint+1;
     oldsplitpoint=splitpoint;
     while(i<=splitpoint)
      {
      split_index[i]=(DATA)clss;
      i++;
      counter++;
      }
     mprintf("Defined set %d of size %d.\n",clss,counter);
     clss++;
     }
    }
   }

  return true;
  }
 else
  {
  runerror(999,"Split Training Set: Can't split, set sizes are invalid.");
  }
return false;
}


/*-----------------------------------------------------------------------*/

int custom_algorithm_menu (int preselect)      /* -1 = Show menu */

{
mhintclear();
mhintf(true,"Custom Methods are experimental clustering algorithms (by V.N). Some are\n");
mhintf(true,"based on ideas in Batchelor's 'Practical Approach to Pattern Classification',\n");
mhintf(true,"and Anderburg's 'Cluster Analysis for Applications'.\n");
mhintf(true,"\n");
mhintf(true,"All methods are clustering algorithms, only the     \n");
mhintf(true,"training set and classification output are accessed.\n");
mhintf(true,"\n");

int msel=preselect;

char mtitle[]="Custom Algorithm Menu";
char *menu[]={"0...No more processing - Go to previous menu.",
              "1...CAM1,Custom Agglomerative Clustering-Merging Method #1.",
              "2...CAM2,Custom Agglomerative Clustering-Merging Method #2.",
              "3...CAM3,Custom Agglomerative Clustering-Weighted Averages-Merging Method #1.",
              "4...CAM4,Custom Agglomerative Clustering-Weighted Averages-Merging Method #2.",
			  "5...Gravity Clustering (Custom).",
			  "6...Split Test Set."
              };

TGBL ANS_run_success=false;

if(TGBL outputdim > TGBL trainsetsize)
 {
 mprintf("Cannot classify %d items into %d classes, too many classes.\n",TGBL trainsetsize,TGBL outputdim);
 return false;
 }

if(TGBL no_error)
 {
 if(preselect<0) msel=mmenu(mtitle,menu,7,6);

 switch(msel)
  {
  case 0: break;

  case 1:
  case 2: TGBL ANS_run_success = Custom_Agglo_Clustering
                                                   (TGBL trainset,
                                                    TGBL trainsetsize,
								    			    TGBL inputdim,
												    TGBL classif,
													msel);
		  break;

  case 3:
  case 4: TGBL ANS_run_success = Custom_Agglo_Clustering_Weighted_Average
                                                   (TGBL trainset,
                                                    TGBL trainsetsize,
								    			    TGBL inputdim,
												    TGBL classif,
													msel-2);
		  break;

  case 5: TGBL ANS_run_success = Custom_Gravity_Clustering
                                                   (TGBL trainset,
                                                    TGBL trainsetsize,
								    			    TGBL inputdim,
												    TGBL classif);

		  break;

  case 6: TGBL ANS_run_success = Split_Set (TGBL outputdim, TGBL testsetsize, TGBL classif);
		  break;

  default:break;
  }
 }

mbeep();
return(msel);
}


/*-----------------------------------------------------------------------*/

void custom_menu(int preselect)
{
char mtitle[]="  Custom Algorithms - Problem Menu ";
char *menu[]={"0...No more processing - Go to previous menu.",
              "1...Load Problem Description File.",
              "2...Preprocess/Scale Sets.",
              "3...Show Available Data Sets.",
              "4...Change requested number of classes (output size).",
			  "5...Select and run custom method."
             };
int msel;

msel=preselect;                          /* -1 means no preset selection */

while((TGBL no_error)&&(msel!=0))
 {
 if(preselect<0)
  {
  if(TGBL prb_loaded)
   msel=mmenu(mtitle,menu,6,5);     /* Show Algorithm option only if problem loaded */
  else
   msel=mmenu(mtitle,menu,2,1);
  }

 switch(msel)
  {
  case 0: FreeAllData();
          TGBL prb_loaded=false;
          break;
  case 1: FreeAllData();
          TGBL prb_loaded=false;
		  GetFilename("Please select problem filename.",TGBL prbfname,"*.PRB",true);
          LoadAllData(TGBL prbfname);
          CreateClassif();
		  if(TGBL no_error) TGBL prb_loaded=true;
          break;
  case 2: preprocess_all_data_sets();
          break;
  case 3: ShowTrainset();
          ShowDesired();
          if(TGBL testset!=TGBL trainset)ShowTestset();
          break;
  case 4: mprintf("Current output size is %d.\n",TGBL outputdim);
          TGBL outputdim = mrequest_int ("Please select new output size");
          break;

  case 5: custom_algorithm_menu(-1);  
          if(TGBL ANS_run_success)
           {
           ShowClassif();
		   SaveClassif("","TTNANS - Custom Method - Classification Results",true);
           SavePreprocessedClasses ("testclass",true);
		   SaveClasses(TGBL prbfname,"ansclass",true);
           }
          break;
  default:break;
  }
 if(!(preselect<0))msel=0;
 }
}

/*-----------------------------------------------------------------------*/
