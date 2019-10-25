// Filter utilities, ndata stores new set and can be initialy NULL (is allocated here);

#include "ttndef.h"
#include "ttndef_s.h"
#include "ttndef_o.h"

#include "ttnmain.h"
#include "ttnui.h"
#include "ttnmemor.h"
#include "ttnmath.h"

#include "tmatrix.h"

/*-----------------------------------------------------------------------------*/

bool filter_on_threshold (bool keep_above, DATA ** d, int r, int c, bool *keep)
{
mhintclear();
mhintf(true,"Given a column x, this filter eliminates all records\n");
mhintf(true,"for which the value at x is largest (below) or smaller (above)\n");
mhintf(true,"the threshold.\n");

bool cropped_some = false;
int  cropped = 0;
bool keep_this = false;
int i;
int basecol    = mrequest_int("Enter column to base filter on");
DATA threshold = mrequest_DATA("Enter threshold value");

if((basecol<c)AND(basecol>-1))
 {
 for(i=0;i<r;i++)   
  {
  keep_this = false;
  switch(keep_above)
   {
   case true:	if(d[i][basecol]>threshold) keep_this=true; break;
   case false:	if(d[i][basecol]<threshold) keep_this=true; break;
   }
  if(keep_this)
   keep[i]=true;
  else
   {
   keep[i]=false;
   if(!cropped_some)
    {mprintf("Threshold Filter (");
    if(keep_above) mprintf(">");
    else  mprintf("<");
    mprintf(DATAFORMAT,threshold);
    mprintf(") cropped row(s): %d",i);
    }
   else	
    mprintf(",%d",i);
   cropped_some=true;
   cropped ++;
   }
  }
 mprintf(".\n");
 }
mprintf("Filter cropped a total of %d rows.\n",cropped);		  
return cropped_some;
}

/*-----------------------------------------------------------------------------*/

#define DROPLESS			3
#define DROPLESSOREQUAL		4
#define DROPGRTR			5
#define DROPGRTROREQUAL		6

bool filter_on_rise_fall (int on_what, DATA ** d, int r, int c, bool *keep)
{
mhintclear();
mhintf(true,"Given a column x, this 'filter' eliminates all subsequent records\n");
mhintf(true,"for which the value at x is larger (for decreasing) or smaller \n");
mhintf(true,"(for increasing) than the current value at x.\n");
mhintf(true,"\n");
mhintf(true,"In other words there is a moving threshold, which is adjusted towards\n");
mhintf(true,"only one direction.\n");
mhintf(true,"\n");
mhintf(true,"Note: The first record is never cropped.\n");

bool cropped_some = false;
int cropped = 0;
bool keep_this = false;
int i;
DATA cur_threshold;

int basecol = mrequest_int("Enter column to base filter on");
if((basecol<c)AND(basecol>-1))
 {

 cur_threshold=d[0][basecol];
 keep[0]=true;

 for(i=1;i<r;i++)					// Note: starts at 1
  {
  keep_this = false;
  switch(on_what)
   {
   case DROPLESSOREQUAL:
				if(d[i][basecol]>cur_threshold)  keep_this=true;
				break;

   case DROPLESS:
				if(d[i][basecol]>=cur_threshold) keep_this=true;
				break;

   case DROPGRTROREQUAL:
				if(d[i][basecol]<cur_threshold)  keep_this=true;
				break;

   case DROPGRTR:
				if(d[i][basecol]<=cur_threshold) keep_this=true;
				break;

   default:	mprintf("Invalid selection \n"); break;
   }

  if(keep_this)
   {
   cur_threshold=d[i][basecol];
   keep[i]=true;
   }
  else
   {
   keep[i]=false;
   if(!cropped_some)  mprintf("Filter cropped row(s): %d",i);		  
   else mprintf(", %d",i);
   cropped_some=true;
   cropped++;
   }

  }
 mprintf(".\n");
 }
mprintf("Filter cropped a total of %d rows (%d percent).\n",cropped,(int)((100.0*cropped)/r));		  
return cropped_some;
}

/*-----------------------------------------------------------------------------*/

bool filter_empirical (DATA ** d, int r, int c, bool *keep)
{
DATA threshold;
bool cropped_some = false;
unsigned cropped = 0;
int i;

for(i=0;i<r;i++) keep[i]=true;

mhintclear();
mhintf(true,"This filter eliminates all records for which\n");
mhintf(true,"            _                               \n");
mhintf(true,"      | x - x |                             \n");
mhintf(true,"      | _____ |  > threshold                \n");
mhintf(true,"      |   s   |                             \n");
mhintf(true,"                                       _    \n");
mhintf(true,"where x the distance from mean-vector, x the\n");
mhintf(true,"mean of such distances, s the standard deviation\n");
mhintf(true,"of such distances.\n");
mhintf(true,"Suggested thresholds for Empirical Rule are : \n");
mhintf(true,"\n");
mhintf(true,"  1 : (x - s ... x + s contains 60 to 80 %% of data.)               \n");
mhintf(true,"\n");
mhintf(true,"  2 : (x - 2s ... x + 2s contains 95 %% of data (symmetric distr.)).\n");
mhintf(true,"\n");
mhintf(true,"  3 : (x - 3s ... x + 3s contains near 100 %% of data.              \n");
mhintf(true,"\n");
mhintf(true,"For more info see: \n");
mhintf(true,"Statistics by example, Terry Sincich. 5th Edition pp.115-136.\n");
mhintf(true,"\n");

CTvector <bool> include_col(c,true);
unsigned included_cols=(unsigned)c;

if(NOT mrequest_yn("Include all columns in data set?"))
 {
 while((i=mrequest_int("Select column to exclude (0=first,negative=exit)"))>=0)
  {
  if(i<c)
   {
   include_col.at((unsigned)i)=false;
   mprintf("Excluded column %d from filter.\n",i);
   included_cols--;
   }
  else
   mprintf("Note:Columns range from 0 to %d.\n",c);
  }
 mprintf("Note: Column numbers will now refer to REMAINING columns.\n");
 }

CTmatrix <DATA> data_buffer (r,included_cols,"data buffer",true);
unsigned rr,cc,cn;

for(rr=0;rr<r;rr++)
 {
 cn=0;
 for(cc=0;cc<c;cc++)
 if(include_col.at(cc))
  {
  data_buffer.at(rr,cn)=d[rr][cc];
  cn++;
  }
 }

data_buffer.show();

CTvector <DATA> mean_vector (included_cols,0);
DATA dd;

for(cc=0;cc<data_buffer.cols();cc++)
 {
 dd=0;
 for(rr=0;rr<data_buffer.rows();rr++) dd=dd+data_buffer.at(rr,cc);
 mean_vector.at(cc)=dd/data_buffer.rows();
 }

CTvector <DATA> distances_from_mean_vector(data_buffer.rows(),0);

for(rr=0;rr<data_buffer.rows();rr++)
 {
 distances_from_mean_vector.at(rr)=dd=0;
 for(cc=0;cc<data_buffer.cols();cc++)
  dd = dd + squared(data_buffer.at(rr,cc) - mean_vector.at(cc));
 dd = square_root(dd);
 distances_from_mean_vector.at(rr)=dd;
 }

DATA mean_of_distances = 0;
for(rr=0;rr<data_buffer.rows();rr++)
 mean_of_distances += distances_from_mean_vector.at(rr);
mean_of_distances = mean_of_distances / data_buffer.rows();


if(data_buffer.rows()==1)
 {
 mprintf("Warning, cannot proceed without causing division by zero, exiting (1).\n");
 return false;
 }

DATA s_of_distances = 0;
dd=0;
for(rr=0;rr<data_buffer.rows();rr++)
 dd = dd + squared( (distances_from_mean_vector.at(rr) - mean_of_distances) );
dd = dd / (data_buffer.rows() - 1);
s_of_distances = square_root(dd);

if(s_of_distances==0)
 {
 mprintf("Warning, cannot proceed without causing division by zero, exiting (2).\n");
 return false;
 }

DATA display [20];
DATA range = 10;
DATA lo_limit = -5;
DATA step = range / 20;
DATA now = lo_limit;

mstarttick("Preparing distances-to-mean / s-of-distances distribution plot");
for(cc=0;cc<20;cc++)
 {
 display[cc]=0;
 for(rr=0;rr<data_buffer.rows();rr++) 
  {
  dd = (distances_from_mean_vector.at(rr) - mean_of_distances) / s_of_distances; 
  if((dd>now)AND(dd<=(now+step))) display[cc]++;
  }
 now=now+step;
 mtick(cc,20);
 }
mendtick();

mprintf("\n(Plot starts at %f, step %f)\n\n",lo_limit,step);
mplot_bar(display,20,data_buffer.rows());

threshold = -1;
while(threshold<0) threshold = mrequest_DATA ("Please enter (positive) threshold");

for(rr=0;rr<data_buffer.rows();rr++) 
 {
 dd = (distances_from_mean_vector.at(rr) - mean_of_distances) / s_of_distances; 
 if((dd>threshold)OR(dd<-threshold))
   {
   keep[rr]=false;
   mprintf("Filtered: %d (z-score : %f)\n",rr,(float)dd);
   cropped_some=true;
   cropped++;
   }
 } 

mprintf("Filter cropped a total of %d rows (%d percent).\n",cropped,(int)((100.0*cropped)/r));		  
return cropped_some;
}

/*-----------------------------------------------------------------------------*/

bool filter_empirical_per_column (DATA ** d, int r, int c, bool *keep)
{
DATA threshold;
bool cropped_some = false;
unsigned cropped = 0;
int i;

for(i=0;i<r;i++) keep[i]=true;

mhintclear();
mhintf(true,"This filter eliminates all records for which\n");
mhintf(true,"            _                               \n");
mhintf(true,"      | x - x |                             \n");
mhintf(true,"      | _____ |  > threshold                \n");
mhintf(true,"      |   s   |                             \n");
mhintf(true,"      _                                     \n");
mhintf(true,"where x the column's mean,\n");
mhintf(true,"s the column's standard deviation.\n");
mhintf(true,"\n");
mhintf(true,"Suggested thresholds for Empirical Rule are : \n");
mhintf(true,"\n");
mhintf(true,"  1 : (x - 1s ... x + 1s contains 60 to 80 %% of data.)             \n");
mhintf(true,"\n");
mhintf(true,"  2 : (x - 2s ... x + 2s contains 95 %% of data (symmetric distr.)).\n");
mhintf(true,"\n");
mhintf(true,"  3 : (x - 3s ... x + 3s contains near 100 %% of data.              \n");
mhintf(true,"\n");
mhintf(true,"For more info see: \n");
mhintf(true,"Statistics by example, Terry Sincich. 5th Edition pp.115-136.\n");
mhintf(true,"\n");

CTvector <bool> include_col(c,true);
unsigned included_cols=(unsigned)c;

if(NOT mrequest_yn("Include all columns in data set?"))
 {
 while((i=mrequest_int("Select column to exclude (0=first,negative=exit)"))>=0)
  {
  if(i<c)
   {
   include_col.at((unsigned)i)=false;
   mprintf("Excluded column %d from filter.\n",i);
   included_cols--;
   }
  else
   mprintf("Note:Columns range from 0 to %d.\n",c);
  }
 mprintf("Note: Column numbers will now refer to REMAINING columns.\n");
 } 

CTmatrix <DATA> data_buffer (r,included_cols,"data buffer",true);
unsigned rr,cc,cn;

for(rr=0;rr<r;rr++)
 {
 cn=0;
 for(cc=0;cc<c;cc++)
 if(include_col.at(cc))
  {
  data_buffer.at(rr,cn)=d[rr][cc];
  cn++;
  }
 }

data_buffer.show();

CTvector <DATA> mean (included_cols,0);
DATA dd;

for(cc=0;cc<data_buffer.cols();cc++)
 {
 dd=0;
 for(rr=0;rr<data_buffer.rows();rr++) dd=dd+data_buffer.at(rr,cc);
 mean.at(cc)=dd/data_buffer.rows();
 }

CTvector <DATA> s (included_cols,0);

for(cc=0;cc<data_buffer.cols();cc++)
 {
 dd=0;
 for(rr=0;rr<data_buffer.rows();rr++) dd=dd+squared(data_buffer.at(rr,cc)-mean.at(cc));
 dd=dd/(data_buffer.rows()-1);
 s.at(cc)=square_root(dd);
 if(s.at(cc)==0)
  {
  mprintf("Warning, s at col. %d is 0. Cannot proceed (division by zero).\n",cc);
  return false; 
  }
 }

threshold = -1;
while(threshold<0) threshold = mrequest_DATA ("Please enter (positive) threshold");

for(cc=0;cc<data_buffer.cols();cc++)
 {
 mprintf("Checking column %d...\n",cc);
 for(rr=0;rr<data_buffer.rows();rr++) 
  {
  dd = (data_buffer.at(rr,cc) - mean.at(cc)) / s.at(cc);
  if((dd>threshold)OR(dd<-threshold))
   {
   if(keep[rr])
    mprintf("Filtered   :");
   else
    mprintf("Re-Filtered:");
   mprintf("%d (z-score : %f)\n",rr,(float)dd);
   keep[rr]=false;
   cropped_some=true;
   cropped++;
   }
  }
 } 

mprintf("Filter cropped a total of %d rows (%d percent).\n",cropped,(int)((100.0*cropped)/r));		  
return cropped_some;
}

/*-----------------------------------------------------------------------------*/

bool filter_after_extreme (DATA ** d, int r, int c, bool *keep)
{
mhintclear();
mhintf(true,"Given a column x, this 'filter' eliminates all records after\n");
mhintf(true,"the extreme value record (max,min) in x occurance.\n");
mhintf(true,"\n");

bool cropped_some = false;
int  cropped = 0;
bool keep_this = false;
int  i;

DATA extreme;
int  extreme_loc;

bool find_max;
bool first_extreme;
bool found_new_extreme;

int basecol = mrequest_int("Enter column to base filter on");

if((basecol<c)AND(basecol>-1))
 {
 find_max = mrequest_yn("Filter after max value? (no = min value)");
 first_extreme = mrequest_yn("Filter after first occurance of extreme? (no = last)");

 extreme=d[0][basecol];
 extreme_loc = -1;

 mprintf("Finding ");

 if(first_extreme) 
  mprintf("first ");
 else 
  mprintf ("last ");

 if(find_max)
  { mprintf("max "); extreme --; }
 else 
  { mprintf("min "); extreme ++; }
 
 mprintf("value of column %d.\n",basecol);
 
 for(i=0;i<r;i++)	
  {
  found_new_extreme = false;
  if(( find_max) AND ( first_extreme) AND (d[i][basecol] >  extreme)) found_new_extreme = true;
  if((!find_max) AND ( first_extreme) AND (d[i][basecol] <  extreme)) found_new_extreme = true;
  if(( find_max) AND (!first_extreme) AND (d[i][basecol] >= extreme)) found_new_extreme = true;
  if((!find_max) AND (!first_extreme) AND (d[i][basecol] <= extreme)) found_new_extreme = true;

  if(found_new_extreme)
   {
   extreme = d[i][basecol];
   extreme_loc = i;
   }
  }
 
  mprintf("Extreme value is %f located at row %d.\n",(float)extreme,extreme_loc);
  
  for(i=0;i<r;i++)	
   {  
   if(i<=extreme_loc)
    keep[i] = true;
   else
    {
    keep[i] = false;
    cropped_some = true;
    cropped++;
    }
   }

  mprintf(".\n");
  mprintf("Filter cropped a total of %d rows (%d percent).\n",cropped,(int)((100.0*cropped)/r));		  
  }
 return cropped_some;
}

/*-----------------------------------------------------------------------------*/

bool filter_at_related_columns (DATA ** d, int r, int c, bool *keep)
{
int msel;
char mtitle[]="      Relation Menu      ";
char * menu[]={"0...Equal ( == , Default)",
               "1...Not equal ( != )",
               "2...Less ( < )",
               "3...Less or equal ( <= )",
               "4...Greater ( > )",
               "5...Greater or equal ( >= )",
			  };

mhintclear();
mhintf(true,"Given matrix M, columns c1, c2, and row r this 'filter' eliminates\n");
mhintf(true,"all records (rows) r for which ( M(r,c1) RELATION M(r,c2) ) is true. \n");
mhintf(true,"\n");

bool cropped_some = false;
int cropped = 0;
int i;
DATA x1,x2;

int basecol_1 = mrequest_int("Enter 1st column to base filter on");
int basecol_2 = mrequest_int("Enter 2nd column to base filter on");

msel=mmenu(mtitle,menu,6,5);

if((basecol_1<c)AND(basecol_2>-1)AND
   (basecol_2<c)AND(basecol_2>-1))
 {
 mprintf("Filtered : ");
 for(i=0;i<r;i++)	
  {
  keep[i] = true;
 
  x1=d[i][basecol_1];
  x2=d[i][basecol_2];
  
  switch(msel)
   {
   case 0: if(x1 == x2) keep[i] = false; break;
   case 1: if(x1 != x2) keep[i] = false; break;
   case 2: if(x1 <  x2) keep[i] = false; break;
   case 3: if(x1 <= x2) keep[i] = false; break;
   case 4: if(x1 >  x2) keep[i] = false; break;
   case 5: if(x1 >= x2) keep[i] = false; break;
   default : break;
   }
  if(keep[i]==false) 
   {
   mprintf("%d ",i);
   cropped_some=true;
   cropped++;
   }
  }
 if(cropped==0)mprintf("none");
 mprintf(".\n");
 mprintf("Filter cropped a total of %d rows (%d percent).\n",cropped,(int)((100.0*cropped)/r));		  
 }
return cropped_some;
}

/*-----------------------------------------------------------------------------*/

bool filter_duplicate (DATA ** d, int r, int c, bool *keep)
{
bool cropped_some = false;
bool same;
int cropped = 0;
int i,j,k;

for(i=0;i<r;i++) keep[i]=true;
	
CTvector <bool> include_col(c,true);

mhintclear();
mhintf(true,"Given columns c1,c2,...,cm this 'filter' eliminates all\n");
mhintf(true,"records for which all values at c1,c2..cm are identical.\n");
mhintf(true,"\n");

if(NOT mrequest_yn("Include all columns in comparison?"))
 {
 while((i=mrequest_int("Select column to exclude (0=first,negative=exit)"))>=0)
  {
  if(i<c)
   {
   include_col.at((unsigned)i)=false;
   mprintf("Excluded column %d from filter.\n",i);
   }
  else
   mprintf("Note:Columns range from 0 to %d.\n",c);
  }
 } 

mstarttick("Filtering duplicates...");
mprintf("Filtered : \n");

for(i=0;i<r;i++)	
 if(keep[i]) 
  {
  for(j=i+1;j<r;j++)
   if(keep[i])
    {
    same = true;
    for(k=0;k<c;k++)
     if(include_col.at(k))
      same = same AND (d[i][k]==d[j][k]);
  
    if(same AND keep[j])
     {
     keep[j] = false;
     mprintf(" %d ",j);
     cropped_some=true;
     cropped++;
     }
    }
  mtick(i,r);
  }
  
mendtick();
if(NOT cropped_some) mprintf("None filtered.");
mprintf("\n");
mprintf("Filter cropped a total of %d rows (%d percent).\n",cropped,(int)((100.0*cropped)/r));		  
return cropped_some;
}

/*-----------------------------------------------------------------------------*/

int filter_menu()
{
int msel=-1;
char mtitle[]="      Filter Menu      ";
char * menu[]={"00...Go Back.  ",
               "01...Threshold, keep records above a value (Hipass)",
               "02...Threshold, keep records below a value (Lowpass)",
               "03...Filter decreasing column values",
               "04...Filter equal-or-decreasing column values",
			   "05...Filter increasing column values",
               "06...Filter equal-or-increasing column values",
			   "07...Empirical Rule Filter on distance from mean-vector",
			   "08...Empirical Rule Filter on each of the columns",
			   "09...Filter after max (min) value",
			   "10...Filter records on relation of values at two columns",
			   "11...Filter duplicate records.",
			  };

if(TGBL no_error) msel=mmenu(mtitle,menu,12,11);
return msel;
}  

//

bool filter_set(DATA ** data,int rows,int cols,DATA *** ndata,int * nrows,int * ncols)
{
bool * keep;
int i;
int msel;

keep = (bool *) MMalloc (rows * sizeof(bool));
bool cropped_some = false;

if (TGBL no_error) 
 {
 
 for(i=0;i<rows;i++) keep[i]=false;  
 msel=filter_menu();
 
 mprintf("Original data set is %d rows x %d cols.\n",rows,cols);

 switch(msel)
  {
  case  0: return false;
  case  1: cropped_some = (filter_on_threshold(true, data,rows,cols,keep)); break;
  case  2: cropped_some = (filter_on_threshold(false,data,rows,cols,keep)); break;
  case  3: cropped_some = (filter_on_rise_fall(DROPLESS		 ,data,rows,cols,keep)); break;
  case  4: cropped_some = (filter_on_rise_fall(DROPLESSOREQUAL,data,rows,cols,keep)); break;
  case  5: cropped_some = (filter_on_rise_fall(DROPGRTR		 ,data,rows,cols,keep)); break;
  case  6: cropped_some = (filter_on_rise_fall(DROPGRTROREQUAL,data,rows,cols,keep)); break;
  case  7: cropped_some = (filter_empirical(data,rows,cols,keep)); break;
  case  8: cropped_some = (filter_empirical_per_column(data,rows,cols,keep)); break;
  case  9: cropped_some = (filter_after_extreme(data,rows,cols,keep)); break;
  case 10: cropped_some = (filter_at_related_columns(data,rows,cols,keep)); break;
  case 11: cropped_some = (filter_duplicate(data,rows,cols,keep)); break;
  default: return false;
  }

 *nrows = 0;
 *ncols = 0;
 for(i=0;i<rows;i++) if(keep[i]) (*nrows)++;

 if(!cropped_some)
  {
  // check
  if((*nrows)!=rows) mprintf("Filter:SOMETHING IS WRONG!!\n");  
  return false;
  }
 
 // at this point we know cropped_some == true;

 *ncols = cols;
 *ndata = MMalloc2dDATA(*nrows,*ncols);

  if(TGBL no_error)
   {
   int j=0;
   for(i=0;i<rows;i++)
    if(keep[i])
     {
     for(int k=0;k<cols;k++) (*ndata)[j][k]=data[i][k];
     j++;
     }
   }
 mprintf("Filtered data set is %d rows x %d cols.\n",*nrows,*ncols);
 return true; 
 }
return false; 
}

//