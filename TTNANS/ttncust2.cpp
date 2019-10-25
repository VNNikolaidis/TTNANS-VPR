/*
   -------------------
   TTNANS:
   TTNCUSTM.C ver.0.01
   -------------------
   V.N.Nikolaidis
   ------------------------
   Custom Experimental
   Algorithms, part 2
   ------------------------
*/

#include "ttndef.h"
#include "ttndef_o.h"

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

#undef _DEBUG_THIS_METHOD_
//#define  _DEBUG_THIS_METHOD_

bool Custom_Agglo_Clustering_Weighted_Average
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
mhintf(true,"With this weighted average adjustment method enabled, the number of\n");
mhintf(true,"records both points represent (records classified with and merged at\n");
mhintf(true,"the points) are used to bias the coordinate adjustments.\n");
mhintf(true,"\n");
mhintf(true,"The method is sensitive to multiple identical-valued records.\n");
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

CTvector <int>	items_in_class_1(n_rows,1);		
CTvector <int>	items_in_class_2(n_rows,0);		
CTvector <int>  * p_items_in_class_now  = & items_in_class_1;
CTvector <int>  * p_items_in_class_next = & items_in_class_2;
CTvector <int>  * p_iictemp;

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

// Step 3. Merge coordinates using average of this and nearest neighbors(s)': 

		for(r1=0 ;r1<n_rows; r1++) // if(NOT is_classified_now .at(r1))
			{
		    for(c=0 ;c<n_cols; c++)	p_data_next->at(r1,c) = 0;							// initialize new to 0;
			p_items_in_class_next->at(r1) = 0;											// now 0, later new inherits old points + merged.
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
						p_data_next->at(r1,c) += ( (p_data_now ->at(r2,c)) * (p_items_in_class_now ->at(r2)) );
					p_items_in_class_next->at(r1) += p_items_in_class_now ->at(r2);
					found_a_NN = true;
					}


				if(add_r1_to_r2)										// add NN record to p_data_next r2.
					{
					for(c=0 ;c<n_cols; c++)
						p_data_next->at(r2,c) += ( (p_data_now ->at(r1,c)) * (p_items_in_class_now ->at(r1)) );
					p_items_in_class_next->at(r2) += p_items_in_class_now ->at(r1);
					found_a_NN = true;
					}

				}

// End main loop.

		
// Step 4. Average coordinates.

		for(r1=0 ;r1<n_rows; r1++) if(NOT is_classified_now .at(r1))
			{
			p_items_in_class_next->at(r1) += p_items_in_class_now ->at(r1);				// inherit old points to calculate average...
			for(c=0 ;c<n_cols; c++)
				{
				p_data_next->at(r1,c) += ( (p_data_now ->at(r1,c)) * (p_items_in_class_now->at(r1)) );		// ... and old coordinates...
				p_data_next->at(r1,c) /= p_items_in_class_next->at(r1);										// ... creating new averaged sum of neigbours.
				}
            p_items_in_class_next->at(r1) = p_items_in_class_now ->at(r1);				// inherit only old points until we merge classes...
			}
            

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
						p_items_in_class_next->at(r1)=0;
						}

					if(r2 != c)										// r2 is not the new cluster center.
						{
						if(NOT is_classified_next.at(r2))
							{
							num_classified ++;        
							num_classes --;        
							is_classified_next.at(r2) = true;
							}
						p_items_in_class_next->at(r2)=0;
						}
					
					tcount = 0;
					for(i=0;i<n_rows;i++)
						{
   						if(is_in_class.at(i) == old_r1_class) is_in_class.at(i)=c;
						if(is_in_class.at(i) == old_r2_class) is_in_class.at(i)=c;
                        if(is_in_class.at(i) == c) tcount++;		
						}
                    p_items_in_class_next->at(c)=tcount;

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

		p_iictemp = p_items_in_class_next;
		p_items_in_class_next = p_items_in_class_now ;
		p_items_in_class_now  = p_iictemp;
 
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

