/*
   -------------------
   TTNANS:
   TTNOTHER.C ver.0.01
   -------------------
   V.N.Nikolaidis
   ------------------------
   Non-ANS clustering
   Graph Theoretic Algorithms.
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
// MST based clustering.

#define MST_RED		0	    /* reject */
#define MST_BLUE	1		/* accept */
#define MST_CUT		2		/* separate a cluster */
#define MST_BLUE_MD 3		/* in a main tree diameter */

#define MST_EDGE_COLOR(x)	at(0,(x))
#define MST_EDGE_V1(x)		at(1,(x))
#define MST_EDGE_V2(x)		at(2,(x))
#define MST_EDGE_WEIGHT(x)	at(3,(x))
#define MST_EDGE_DIST(x)	at(4,(x))

#define _AT_(x)				at(0,(x))

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void MSTBV_DepthFirstTraverse 
			   (unsigned current_point,
                unsigned points_so_far,
                CTmatrix<DATA> REF em,
                CTmatrix<bool> REF marked,
                unsigned REF max_points_traversed,
                int REF max_points_traversed_endpoint)
{
bool found_adjacent_unmarked_point = false;
int next_point = -1;

marked._AT_(current_point) = true;

for(unsigned i=0;i<em.cols();i++)
 {
 if(em.MST_EDGE_COLOR(i) == MST_BLUE)
  {
  next_point = -1;
  if( (em.MST_EDGE_V1(i)==current_point) AND (NOT marked._AT_((int)em.MST_EDGE_V2(i))) )
   {
   found_adjacent_unmarked_point = true;
   next_point=(int)em.MST_EDGE_V2(i);
   }
  else
  if( (em.MST_EDGE_V2(i)==current_point) AND (NOT marked._AT_((int)em.MST_EDGE_V1(i))) )
   {
   found_adjacent_unmarked_point = true;
   next_point=(int)em.MST_EDGE_V1(i);
   }

  if(next_point!=-1)
   {
   em.MST_EDGE_DIST(i)=points_so_far;
   MSTBV_DepthFirstTraverse(next_point,(points_so_far+1),em,marked,max_points_traversed,max_points_traversed_endpoint);
   }
  }
 }

if(found_adjacent_unmarked_point) return;
 
if(points_so_far>max_points_traversed)
 {
 max_points_traversed=points_so_far;
 max_points_traversed_endpoint=current_point;
 }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void MSTBV_Mark_A_Main_Diameter(unsigned n_points,CTmatrix<DATA> REF em)
{
CTmatrix<bool> marked(1,n_points,false,"Points Marker",true);

unsigned i,j;
unsigned now  = 0;
unsigned best = 0;
int best_start= -1;
int best_end  = -1;
int an_end  = -1;
unsigned p;

mstarttick("<Determining a main diameter (path through most points)>");

for(i=0;i<n_points;i++) 
 {

 marked.reset(false);

 MSTBV_DepthFirstTraverse (i,1,em,marked,now,an_end);

 if(now>best)
   {
   best=now;
   best_start=i;
   best_end=an_end;
   }

 mtick(i,n_points);
 }
// finalize;

marked.reset(false);
for(j=0;j<em.cols();j++) if(em.MST_EDGE_COLOR(j)==MST_BLUE_MD) em.MST_EDGE_DIST(j)=-1;
MSTBV_DepthFirstTraverse (best_start,1,em,marked,now,an_end);
i=best-1;
p=best_end;

while(i>0)
 {
 for(j=0;j<em.cols();j++)
  {
  if((em.MST_EDGE_COLOR(j)==MST_BLUE)AND(em.MST_EDGE_DIST(j) == i))
   {
   if(em.MST_EDGE_V1(j)==p)
    {
    p=em.MST_EDGE_V2(j);
	em.MST_EDGE_COLOR(j)=MST_BLUE_MD;
    i--;
	}
   else
   if(em.MST_EDGE_V2(j)==p)
    {
    p=em.MST_EDGE_V1(j);
	em.MST_EDGE_COLOR(j)=MST_BLUE_MD;
	i--;
	}
   }
  }
 }
mendtick();
mprintf("Best path passes %d vertices.\n",best);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void MST_Recluster(CTmatrix<DATA> REF em,		// Edge matrix (as used below)
			 unsigned	n_rows,					// # of vectors (n_cols-dimentional points) in data set
			 DATA *		p_class,				// returned clustering index (n_rows x 1). -1 here indicates isolated point.
             bool		show_progress = true,
             DATA		marker = MST_BLUE)
{
unsigned ct = 0;
int i;
unsigned num_of_edges = em.cols() ;

if(show_progress) mstarttick("Reclustering...");

for(i=0;i<n_rows;i++) p_class[i]=(DATA)-1;				// Reset

for(i=0;i<num_of_edges;i++)								// recluster considering only BLUE (MST) edges.
 {	
 if(em.MST_EDGE_COLOR(i)==marker)
  {
  
  if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND
     (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge joins two unclustered points...
    {
    p_class[(int)em.MST_EDGE_V1(i)] = (DATA) ct;
    p_class[(int)em.MST_EDGE_V2(i)] = (DATA) ct;
    ct=ct+1;
    goto done_clustering_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
 	  (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge is added to an existing cluster at V2...
    {
    p_class[(int)em.MST_EDGE_V1(i)] = p_class[(int)em.MST_EDGE_V2(i)];
    goto done_clustering_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge is added to an existing cluster at V1...
    {
    p_class[(int)em.MST_EDGE_V2(i)] = p_class[(int)em.MST_EDGE_V1(i)];
    goto done_clustering_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge joins two existing clusters, we merge them...
    {
    DATA d1,d2;
    unsigned j;

    d1=min(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
    d2=max(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
    for(j=0;j<n_rows;j++) if(p_class[j]==d2) p_class[j]=d1;
    goto done_clustering_this_edge;
    }
   }
 done_clustering_this_edge:
 if(show_progress)mtick(i,num_of_edges);
 } 

if(show_progress)mendtick();
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// RS=Recursive Step for custom version, no reference.

void MSTBV_RS_My_Mark_Cut_Candidates
			(CTmatrix<DATA> REF em,				// (shorted) 5-row edge matrix as used below.
			 unsigned curedge,
             unsigned REF count)
{ 
unsigned i,ie=em.cols();
unsigned newmin1     = em.cols()+100;
unsigned newmin1edge = curedge;
unsigned newmin2     = em.cols()+100;
unsigned newmin2edge = curedge;

#ifdef _DEBUG
mprintf("*** (Marked %d (%d-%d length %f score %f).)\n",curedge,(int)em.MST_EDGE_V1(curedge),(int)em.MST_EDGE_V2(curedge),(float)em.MST_EDGE_WEIGHT(curedge),em.at(4,curedge));
#endif
 
em.MST_EDGE_COLOR(curedge)=MST_BLUE_MD;
count++;

mtick(count,ie);

for(i=0;i<ie;i++)											// find adjacent blue edge with smallest difference score.
 {
 if(em.MST_EDGE_COLOR(i)==MST_BLUE)							// if blue ...
  {
  if
   ((em.MST_EDGE_V1(i)==em.MST_EDGE_V1(curedge))OR			// ... and adjacent 'left' edge
    (em.MST_EDGE_V2(i)==em.MST_EDGE_V1(curedge)))
   if(em.at(4,i)<=newmin1)
    {
    newmin1=em.at(4,i);
    newmin1edge=i; 
    }

  if
   ((em.MST_EDGE_V1(i)==em.MST_EDGE_V2(curedge))OR			// ... and adjacent 'right' edge
    (em.MST_EDGE_V2(i)==em.MST_EDGE_V2(curedge)))
   if(em.at(4,i)<=newmin2)
    {
    newmin2=em.at(4,i);
    newmin2edge=i; 
    }
  }
 }

if(newmin1edge NEQL curedge)								// Follow 'left'
 {
 MSTBV_RS_My_Mark_Cut_Candidates(em,newmin1edge,count);
 }

if(newmin2edge NEQL curedge)								// Follow 'right'
 {
 MSTBV_RS_My_Mark_Cut_Candidates(em,newmin2edge,count);
 }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
// This is a custom version, no reference.

void MSTBV_My_Mark_Cut_Candidates
			(unsigned	n_rows,					// # of vectors (n_cols-dimentional points) in data set
             CTmatrix<DATA> REF em,				// (shorted) 5-row edge matrix as used below.
			 DATA *		p_class)				// returned clustering index (n_rows x 1)
{
unsigned i,j,ie=em.cols();
DATA id1,id2,test;
unsigned cnt1,cnt2;
unsigned mincnt = em.cols()+100;
unsigned mincntedge = em.cols()+100;

mhintclear();
mhintf(true,"Marking cut candidates (custom version):\n");
mhintf(true,"Instead of performing an exhaustive depth-first-search for a\n");
mhintf(true,"main diameter, edges are marked according to the effect of\n");
mhintf(true,"their removal. Edges are ranked using an additional score\n");
mhintf(true,"which equals the (absolute value of) the difference in\n");
mhintf(true,"sizes of the two classes that would have been created if\n");
mhintf(true,"just that one edge was removed.\n\n");
mhintf(true,"After the edge with lowest score is picked, a path of adjacent");
mhintf(true,"low-score MST edges is found and used as the 'main diameter'.\n");
mhintf(true,"\n");

mstarttick("Determining main-diameter candidate edges, stage 1");
for(i=0;i<ie;i++)
 {
 if(em.MST_EDGE_COLOR(i)==MST_BLUE)
  {
  em.at(4,i)=0;
  em.MST_EDGE_COLOR(i)=(DATA)MST_CUT;			// try cutting it.

  MST_Recluster(em, n_rows, p_class, false);

  id1=id2=p_class[0];
  cnt1=cnt2=0;

  for(j=0;j<n_rows;j++)
   {
   test=p_class[j];

   if(test==id1)
    {
    cnt1++;
    goto out;
    }

   if(id1==id2) id2=test;
   
   if(test==id2)
    {
    cnt2++;
    goto out;
    }

   mprintf("Warning: Maximum (2) cluster ids should exist at this point. Check algorithm.\n");
   mprintf("(id1=%f, id2=%f, testing id=%f).\n",(float)id1,(float)id2,(float)test);
   out:;
   }

  em.MST_EDGE_COLOR(i)=(DATA)MST_BLUE;			// change it back to BLUE when done.
  em.at(4,i)=abs((int)(cnt1-cnt2));				// 0 means removing it produces two equaly sized clusters, good main diameter candidate.
  if(em.at(4,i)<mincnt)
   {
   mincnt=em.at(4,i);
   mincntedge=i;
   }
  } 
 mtick(i,ie);
 }
mendtick();


unsigned count=0;
mstarttick("Determining main-diameter candidate edges, stage 2");
MSTBV_RS_My_Mark_Cut_Candidates(em,mincntedge,count);
//mtick(i,ie);
mendtick();
mprintf("Found path containing %d edges.\n",count);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#define MSTBV_DEPTHFIRST 1
#define MSTBV_CANDIDATE  2

bool MSTBV_Clustering
			(DATA **	p_set,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors (n_cols-dimentional points) in p_set
			 unsigned	n_cols,					// dimentionality of each p_set vector
			 DATA *		p_class,				// returned clustering index (n_rows x 1)
             unsigned   mark_diameter_method)
{
int cuts = (TGBL outputdim) - 1;

mprintf("\nInvoking Minimum Spanning Tree Clustering (BOOK VERSION) (on %u x % u set)\n\n",n_rows,n_cols);

mhintclear();
mhintf(true,"For more on Minimal Spanning Tree (MST) Clustering Method,\n");
mhintf(true,"see: Pattern Recognition,\n");
mhintf(true,"Applications to Large Data-Set Problems\n");
mhintf(true,"by Sing-Tze Bow (1984) p.136.\n");
mhintf(true,"\n");
mhintf(true,"This routine cuts blue (MST) edges only if\n");
mhintf(true,"they belong to a main diameter of the tree.\n");
mhintf(true,"Cuts take place according to length (longest are cut first).\n");
mhintf(true,"\n");
mhintf(true,"Kruskal's algorithm is used for determining\n");
mhintf(true,"the Minimal Spanning Tree. For more on MSTs,\n");
mhintf(true,"see: Data Structures and Network Algorithms,\n");
mhintf(true,"by Robert Endre Tarjan (1983) p.71.\n");
mhintf(true,"\n");

bool run_ok=true;
unsigned rr,rc;
int i,ct = 0;			

for(i=0;i<n_rows;i++) p_class[i]=-1;

// step 1.	Find Minimal Spanning Tree

// step 1.0 Short distances in nondecreasing order (fully connected has (n*(n-1))/2 edges).
//          (using columns to store edge info (5 x num_of_edges) since using rows (num_of_edges x 5)
//           would be much slower at runtime).

unsigned num_of_edges = (n_rows*(n_rows-1))/2;
unsigned edges_in_mst = 0;

CTmatrix<DATA> em (5,num_of_edges,"Edges matrix, columns = (color,v1,v2,weight,somedistance)");

i=0;
for(rr=0;rr<n_rows;rr++)
for(rc=rr+1;rc<n_rows;rc++)
 {
 em.MST_EDGE_COLOR(i)	=(DATA)MST_RED;
 em.MST_EDGE_V1(i)		=(DATA)rr;
 em.MST_EDGE_V2(i)		=(DATA)rc;
 em.MST_EDGE_WEIGHT(i)	=EuclideanDistance(p_set[rr],p_set[rc],(int)n_cols);
 i++;
 }

if(run_ok=(bool)(i==num_of_edges))mprintf("Ok initializing edges.\n");

em.quicksort_cols(3);

// step 1.1 "Color" the edges...

mstarttick("Colouring Edges...(get your red-blue crayons, boys!)");

ct = 0;

for(i=0;i<num_of_edges;i++)							// for each edge (in nondecreasing order of distance)...
 {
 if(
   (p_class[(int)em.MST_EDGE_V1(i)] != p_class[(int)em.MST_EDGE_V2(i)]) OR		// if it does not create a cycle on an existing tree...
   (p_class[(int)em.MST_EDGE_V1(i)] == -1) OR									// or one of the vertices are not in any existing tree..
   (p_class[(int)em.MST_EDGE_V2(i)] == -1)										// (same as above)
   )
   {
   em.MST_EDGE_COLOR(i) = MST_BLUE;
   edges_in_mst++;

   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge belongs to a new tree...
	{
	p_class[(int)em.MST_EDGE_V1(i)] = (DATA) ct;
    p_class[(int)em.MST_EDGE_V2(i)] = (DATA) ct;
    ct++;
    goto done_coloring_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND
	  (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge is added to an existing tree at V2...
	{
	p_class[(int)em.MST_EDGE_V1(i)] = p_class[(int)em.MST_EDGE_V2(i)];
    goto done_coloring_this_edge;
    }
  
   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
	  (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge is added to an existing tree at V1...
    {
    p_class[(int)em.MST_EDGE_V2(i)] = p_class[(int)em.MST_EDGE_V1(i)];
    goto done_coloring_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
	  (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge joins two existing trees...
	{
    DATA d1,d2;
	unsigned j;

    d1=min(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
    d2=max(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
	for(j=0;j<n_rows;j++) if(p_class[j]==d2) p_class[j]=d1;
	goto done_coloring_this_edge;
	}
   }

 done_coloring_this_edge:
 mtick(i,num_of_edges);
 } 

mendtick();

// Step 2.  At this point all vertices should be in one MST.

#ifdef _DEBUG
for(i=0;i<n_rows;i++) if(p_class[i]==-1)  mprintf("Warning: Not in MST, element %d.\n",i);

if(mrequest_yn("Show MST? (Debug option)"))
 {
 int j=0;
 for(i=0;i<num_of_edges;i++)
  {
  if(em.MST_EDGE_COLOR(i)==MST_BLUE)
   {
   j++;
   mprintf("in MST: Edge %d (%d-%d)\n",i,(int)em.MST_EDGE_V1(i),(int)em.MST_EDGE_V2(i));
   }
  }
 mprintf("Found MST with %d edges.\n",j);
 }
#endif

// Step 2.0 Find a main diameter (path containing largest number of points)

if(mark_diameter_method==MSTBV_DEPTHFIRST)
 {
 mprintf("There are %d edges in the minimum spanning tree (MST).\n",edges_in_mst);
 mprintf("Finding a main diameter (path containing most points) of the MST...\n");
 MSTBV_Mark_A_Main_Diameter (n_rows,em);
 }

if(mark_diameter_method==MSTBV_CANDIDATE)
 {
 MSTBV_My_Mark_Cut_Candidates(n_rows,em,p_class);
 }

#ifdef _DEBUG
if(mrequest_yn("Show MST diameter? (Debug option)"))
 {
 int j=0;
 for(i=0;i<num_of_edges;i++)
  {
  if(em.MST_EDGE_COLOR(i)==MST_BLUE_MD)
   {
   j++;
   mprintf("in MST MD : Edge %d (%d-%d)\n",i,(int)em.MST_EDGE_V1(i),(int)em.MST_EDGE_V2(i));
   }
  }
 mprintf("Found a main MST diameter with %d edges.\n",j);
 }
#endif

// Step 2.1 Cut a few blue edges and recluster...

mstarttick("Cutting some BLUE edges and reclustering...");

int j=cuts;

for(i=num_of_edges-1;((i>=0)AND(j>0));i--)				// for each edge (in decreasing -non increasing- order)
 {
 if(em.MST_EDGE_COLOR(i)==(DATA)MST_RED);				// if red do nada.
 else
 {
 if(em.MST_EDGE_COLOR(i)==(DATA)MST_BLUE_MD) 			// is BLUE in the (some) main diameter
   {
   em.MST_EDGE_COLOR(i)=(DATA)MST_CUT;					// cut it!
   j--;
   mprintf("(Cut # %d at blue main diameter edge %d (%d-%d length %f).)\n",j,i,(int)em.MST_EDGE_V1(i),(int)em.MST_EDGE_V2(i),(float)em.MST_EDGE_WEIGHT(i));
   }
  }
 }

if(j>0)
 {
 mprintf("Warning: Could not perform %d cuts (too few main diameter edges?).\n",cuts); 
 run_ok=false;
 }


// re-color the remaining main diameter edges to BLUE

for(i=0;i<num_of_edges;i++) if(em.MST_EDGE_COLOR(i)==(DATA)MST_BLUE_MD) em.MST_EDGE_COLOR(i)=(DATA)MST_BLUE;

// re-cluster

for(i=0;i<n_rows;i++) p_class[i]=-1;					// reset.

ct = 0;

for(i=0;i<num_of_edges;i++)								// recluster considering only BLUE (MST) edges.
 {	
 if(em.MST_EDGE_COLOR(i)==(DATA)MST_BLUE)
  {
   
  if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND
     (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge joins two unclustered points...
   {
   p_class[(int)em.MST_EDGE_V1(i)] = (DATA) ct;
   p_class[(int)em.MST_EDGE_V2(i)] = (DATA) ct;
   ct=ct+1;
   goto done_clustering_this_edge;
   }

  if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
     (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge is added to an existing cluster at V2...
   {
   p_class[(int)em.MST_EDGE_V1(i)] = p_class[(int)em.MST_EDGE_V2(i)];
   goto done_clustering_this_edge;
   }

  if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
     (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge is added to an existing cluster at V1...
   {
   p_class[(int)em.MST_EDGE_V2(i)] = p_class[(int)em.MST_EDGE_V1(i)];
   goto done_clustering_this_edge;
   }

  if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND
     (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge joins two existing clusters, we merge them...
   {
   DATA d1,d2;
   unsigned j;

   d1=min( (p_class[(int)em.MST_EDGE_V1(i)]), (p_class[(int)em.MST_EDGE_V2(i)]) );
   d2=max( (p_class[(int)em.MST_EDGE_V1(i)]), (p_class[(int)em.MST_EDGE_V2(i)]) );
   for(j=0;j<n_rows;j++) if(p_class[j]==d2) p_class[j]=d1;
   goto done_clustering_this_edge;
   }
  }

 done_clustering_this_edge:

 mtick(i,num_of_edges);
 }

mendtick();

#ifdef _DEBUG
mprintf("Cleaning Up...\n");
for(i=0;i<n_rows;i++) if(p_class[i]==-1)  mprintf("Warning: Not clustered (isolated) element %d.\n",i);
#endif


// Step 2.2  Isolated points become clusters by themselves.

j=0;
for(i=0;i<n_rows;i++) if(p_class[i]==-1) j++;

if(j>0)
 {
 if(mrequest_yn("Put all isolated points in one (the last) cluster?"))
  {
  j=0;
  for(i=0;i<n_rows;i++)
   if(p_class[i]==-1)
    {
    p_class[i] = (DATA) ct;
	j++;
	}
  mprintf("Found %d isolated points, now all located in the last cluster.\n",j);
  if(j>0)
   mprintf("Sujestion: Re-run the algorithm for at least %d classes.\n",cuts+j+1);
  }
 else
  {
  for(i=0;i<n_rows;i++)
  if(p_class[i]==-1)
   {
   p_class[i] = (DATA) ct;
   ct++;
   }
  }
 }

// Step 2.3  Correct the "holes" found in p_class ids. These are created when we are merging clusters.

 {
 ct=0;
 int iter_ct = 0;
 int max_ct  = 0; 
 bool found_one = false;
 CTmatrix <int> ta (1,n_rows,-1,"Temporary Storage",true);

 for(i=0;i<n_rows;i++)  if(p_class[i]>max_ct) max_ct = (int) p_class[i];

 while(iter_ct<=max_ct)
  {
  found_one = false;
  for(i=0;i<n_rows;i++)
   if(p_class[i]==iter_ct)
	{
    found_one=true;
    ta.at(0,i)=ct;
    }
  if(found_one) ct++;
  iter_ct++;
  }

 for(i=0;i<n_rows;i++) p_class[i]=(DATA)ta.at(0,i);
 }

// Done!

if(run_ok) {mprintf("MST Clustering returns OK, producing %d classes.\n",(int)ct);TGBL outputdim=ct;}
else       {mprintf("MST Clustering returns with Warning.\n");}
return run_ok;
}

/*-----------------------------------------------------------------------*/

bool MSTCnR_Clustering
			(DATA **	p_set,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
			 unsigned	n_cols,					// dimentionality of each p_set vector
			 DATA *		p_class)				// returned clustering index (n_rows x 1)

{
int cuts = (TGBL outputdim) - 1;

mprintf("\nInvoking Minimum Sp.Tree Modified ('Cut and Recluster') Clustering (on %u x % u set)\n\n",n_rows,n_cols);

mhintclear();
mhintf(true,"For more on Minimal Spanning Tree (MST) Clustering Method,\n");
mhintf(true,"see: Pattern Recognition,\n");
mhintf(true,"Applications to Large Data-Set Problems\n");
mhintf(true,"by Sing-Tze Bow (1984) p.136.\n");
mhintf(true,"\n");
mhintf(true,"Note: During clustering, this version removes\n");
mhintf(true,"edges from the actual minimal spanning tree,\n");
mhintf(true,"(not from one of it's main diameters).\n");
mhintf(true,"Cuts take place according to length (longest are cut first).\n");
mhintf(true,"This MODIFIED version, however, keeps removing edges until \n");
mhintf(true,"the requested number of non-single element classes is produced.\n");
mhintf(true,"\n");
mhintf(true,"We will use Kruskal's algorithm for determining\n");
mhintf(true,"the Minimal Spanning Tree. For more on MST,\n");
mhintf(true,"see: Data Structures and Network Algorithms,\n");
mhintf(true,"by Robert Endre Tarjan (1983) p.71.\n");
mhintf(true,"\n");

bool run_ok=true;
unsigned rr,rc;
int i,ct = 0;

for(i=0;i<n_rows;i++) p_class[i]=-1;

// step 1.	Find Minimal Spanning Tree

// step 1.0 Short distances in nondecreasing order (fully connected has (n*(n-1))/2 edges).
//          (using columns to store edge info (4 x num_of_edges) since using rows (num_of_edges x 4)
//           would be much slower at runtime).

unsigned cuts_done=0;
unsigned num_of_edges = (n_rows*(n_rows-1))/2;
CTmatrix<DATA> em (4,num_of_edges,"Edges matrix, columns = (color,v1,v2,weight)");

i=0;
for(rr=0;rr<n_rows;rr++)
for(rc=rr+1;rc<n_rows;rc++)
 {
 em.MST_EDGE_COLOR(i)	=(DATA)MST_RED;
 em.MST_EDGE_V1(i)		=(DATA)rr;
 em.MST_EDGE_V2(i)		=(DATA)rc;
 em.MST_EDGE_WEIGHT(i)	=EuclideanDistance(p_set[rr],p_set[rc],(int)n_cols);
 i++;
 }

if(run_ok=(bool)(i==num_of_edges))mprintf("Ok initializing edges.\n");

em.quicksort_cols(3);

// step 1.1 "Color" the edges...

mstarttick("Colouring Edges...(get your red-blue crayons, boys!)");

ct = 0;

for(i=0;i<num_of_edges;i++)							// for each edge (in nondecreasing order of distance)...
 {
 if(
   (p_class[(int)em.MST_EDGE_V1(i)] != p_class[(int)em.MST_EDGE_V2(i)]) OR		// if it does not create a cycle on an existing tree...
   (p_class[(int)em.MST_EDGE_V1(i)] == -1) OR									// or one of the vertices are not in any existing tree..
   (p_class[(int)em.MST_EDGE_V2(i)] == -1)										// (same as above)
   )
   {
   em.MST_EDGE_COLOR(i) = MST_BLUE;

   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
	  (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge belongs to a new tree...
    {
	p_class[(int)em.MST_EDGE_V1(i)] = (DATA) ct;
	p_class[(int)em.MST_EDGE_V2(i)] = (DATA) ct;
    ct++;
    goto done_coloring_this_edge;
    }
 
   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge is added to an existing tree at V2...
	{
    p_class[(int)em.MST_EDGE_V1(i)] = p_class[(int)em.MST_EDGE_V2(i)];
    goto done_coloring_this_edge;
    }
  
   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND
      (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge is added to an existing tree at V1...
	{
    p_class[(int)em.MST_EDGE_V2(i)] = p_class[(int)em.MST_EDGE_V1(i)];
    goto done_coloring_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge joins two existing trees...
    {
	DATA d1,d2;
    unsigned j;

    d1=min(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
    d2=max(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
	for(j=0;j<n_rows;j++) if(p_class[j]==d2) p_class[j]=d1;
	goto done_coloring_this_edge;
	}
   }

 done_coloring_this_edge:
 mtick(i,num_of_edges);
 } 

mendtick();

// Step 2.  At this point all vertices should be in one MST.
// Step 2.1 Cut a few blue edges and recluster...

bool done=false;
int j=cuts;

while ((NOT done)AND(run_ok))
 {
 for(i=num_of_edges-1;(i>=0)AND(j>0);i--)				// for each edge (in decreasing -non increasing- order)
  {
  if(em.MST_EDGE_COLOR(i)==(DATA)MST_BLUE)				// if blue cut it.
   {
   em.MST_EDGE_COLOR(i)=(DATA)MST_CUT;
   j--;
   cuts_done++;		
   mprintf("(Cut # %d at blue edge %d (%d-%d length %f).)\n",cuts_done,i,(int)em.MST_EDGE_V1(i),(int)em.MST_EDGE_V2(i),(float)em.MST_EDGE_WEIGHT(i));}
   }      

 for(i=0;i<n_rows;i++) p_class[i]=-1;					// reset.

 if(j>0) 
  {
  runerror(-1,"Could not perform all cuts (too few edges?). Exiting."); 
  return false;
  }

 mstarttick("Reclustering...");

 ct = 0;

 for(i=0;i<num_of_edges;i++)								// recluster considering only BLUE (MST) edges.
  {	
  if(em.MST_EDGE_COLOR(i)==(DATA)MST_BLUE)
   {
   
   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND
      (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge joins two unclustered points...
    {
    p_class[(int)em.MST_EDGE_V1(i)] = (DATA) ct;
    p_class[(int)em.MST_EDGE_V2(i)] = (DATA) ct;
    ct=ct+1;
    goto done_clustering_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
 	  (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge is added to an existing cluster at V2...
    {
    p_class[(int)em.MST_EDGE_V1(i)] = p_class[(int)em.MST_EDGE_V2(i)];
    goto done_clustering_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge is added to an existing cluster at V1...
    {
    p_class[(int)em.MST_EDGE_V2(i)] = p_class[(int)em.MST_EDGE_V1(i)];
    goto done_clustering_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge joins two existing clusters, we merge them...
    {
    DATA d1,d2;
    unsigned j;

    d1=min(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
    d2=max(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
    for(j=0;j<n_rows;j++) if(p_class[j]==d2) p_class[j]=d1;
    goto done_clustering_this_edge;
    }
   }

  done_clustering_this_edge:

  mtick(i,num_of_edges);
  }

 mendtick();

// Count isolated.

 j=0;
 for(i=0;i<n_rows;i++)
  if(p_class[i]==-1)
   {
   p_class[i] = (DATA) ct;
   j++;
   }
 mprintf("Found %d isolated points (now in last cluster (temp.id = %d)), ",j,ct);

// Correct the "holes" found in p_class ids. These are created when we are merging clusters.

 {
 ct=0;
 int iter_ct = 0;
 int max_ct  = 0; 
 bool found_one = false;
 CTmatrix <int> ta (1,n_rows,-1,"Temporary Storage",true);

 for(i=0;i<n_rows;i++)  if(p_class[i]>max_ct) max_ct = (int) p_class[i];

 while(iter_ct<=max_ct)
  {
  found_one = false;
  for(i=0;i<n_rows;i++) 
   if(p_class[i]==iter_ct)
    {
	found_one=true;
    ta.at(0,i)=ct;
    }
  if(found_one) ct++;
  iter_ct++;
  }

 for(i=0;i<n_rows;i++) p_class[i]=(DATA)ta.at(0,i);
 }

mprintf("%d classes so far.\n",ct);

// Done!

 if(ct<cuts+1)  j=1;
 else done=true;
}

// Done!

if(run_ok) {mprintf("MST Clustering returns OK, producing %d classes.\n",(int)ct);TGBL outputdim=ct;}
else       {mprintf("MST Clustering returns with Warning.\n");}
return run_ok;
}


/*-----------------------------------------------------------------------*/

bool MST_Clustering
			(DATA **	p_set,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
			 unsigned	n_cols,					// dimentionality of each p_set vector
			 DATA *		p_class)				// returned clustering index (n_rows x 1)

{
int cuts = (TGBL outputdim) - 1;

mprintf("\nInvoking Minimum Spanning Tree Clustering (on %u x % u set)\n\n",n_rows,n_cols);

mhintclear();
mhintf(true,"For more on Minimal Spanning Tree (MST) Clustering Method,\n");
mhintf(true,"see: Pattern Recognition,\n");
mhintf(true,"Applications to Large Data-Set Problems\n");
mhintf(true,"by Sing-Tze Bow (1984) p.136.\n");
mhintf(true,"\n");
mhintf(true,"Note: During clustering, this version removes\n");
mhintf(true,"edges from the actual minimal spanning tree,\n");
mhintf(true,"(not from one of it's main diameters).\n");
mhintf(true,"Cuts take place according to length (longest are cut first).\n");
mhintf(true,"\n");
mhintf(true,"We will use Kruskal's algorithm for determining\n");
mhintf(true,"the Minimal Spanning Tree. For more on MSTs,\n");
mhintf(true,"see: Data Structures and Network Algorithms,\n");
mhintf(true,"by Robert Endre Tarjan (1983) p.71.\n");
mhintf(true,"\n");

bool run_ok=true;
unsigned rr,rc;
int i,ct = 0;

for(i=0;i<n_rows;i++) p_class[i]=-1;

// step 1.	Find Minimal Spanning Tree

// step 1.0 Short distances in nondecreasing order (fully connected has (n*(n-1))/2 edges).
//          (using columns to store edge info (4 x num_of_edges) since using rows (num_of_edges x 4)
//           would be much slower at runtime).

unsigned num_of_edges = (n_rows*(n_rows-1))/2;
CTmatrix<DATA> em (4,num_of_edges,"Edges matrix, columns = (color,v1,v2,weight)");

i=0;
for(rr=0;rr<n_rows;rr++)
for(rc=rr+1;rc<n_rows;rc++)
 {
 em.MST_EDGE_COLOR(i)	=(DATA)MST_RED;
 em.MST_EDGE_V1(i)		=(DATA)rr;
 em.MST_EDGE_V2(i)		=(DATA)rc;
 em.MST_EDGE_WEIGHT(i)	=EuclideanDistance(p_set[rr],p_set[rc],(int)n_cols);
 i++;
 }

if(run_ok=(bool)(i==num_of_edges))mprintf("Ok initializing edges.\n");

em.quicksort_cols(3);

// step 1.1 "Color" the edges...

mstarttick("Colouring Edges...(get your red-blue crayons, boys!)");

ct = 0;

for(i=0;i<num_of_edges;i++)							// for each edge (in nondecreasing order of distance)...
 {
 if(
   (p_class[(int)em.MST_EDGE_V1(i)] != p_class[(int)em.MST_EDGE_V2(i)]) OR		// if it does not create a cycle on an existing tree...
   (p_class[(int)em.MST_EDGE_V1(i)] == -1) OR									// or one of the vertices are not in any existing tree..
   (p_class[(int)em.MST_EDGE_V2(i)] == -1)										// (same as above)
   )
   {
   em.MST_EDGE_COLOR(i) = MST_BLUE;

   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
	  (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge belongs to a new tree...
    {
	p_class[(int)em.MST_EDGE_V1(i)] = (DATA) ct;
	p_class[(int)em.MST_EDGE_V2(i)] = (DATA) ct;
    ct++;
    goto done_coloring_this_edge;
    }
 
   if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge is added to an existing tree at V2...
	{
    p_class[(int)em.MST_EDGE_V1(i)] = p_class[(int)em.MST_EDGE_V2(i)];
    goto done_coloring_this_edge;
    }
  
   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND
      (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge is added to an existing tree at V1...
	{
    p_class[(int)em.MST_EDGE_V2(i)] = p_class[(int)em.MST_EDGE_V1(i)];
    goto done_coloring_this_edge;
    }

   if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
      (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge joins two existing trees...
    {
	DATA d1,d2;
    unsigned j;

    d1=min(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
    d2=max(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
	for(j=0;j<n_rows;j++) if(p_class[j]==d2) p_class[j]=d1;
	goto done_coloring_this_edge;
	}
   }

 done_coloring_this_edge:
 mtick(i,num_of_edges);
 } 

mendtick();

// Step 2.  At this point all vertices should be in one MST.
// Step 2.1 Cut a few blue edges and recluster...

#ifdef _DEBUG
if(mrequest_yn("List MST (blue) edges (debug option)?"))
 {
 mprintf("\n");
 for(i=0;i<num_of_edges;i++)							// for each edge
  {
  if(em.MST_EDGE_COLOR(i)==MST_BLUE) mprintf("MST: Edge %d \t(%d-%d)\tlength:%f.\n",i,(int)em.MST_EDGE_V1(i),(int)em.MST_EDGE_V2(i),(float)em.MST_EDGE_WEIGHT(i));
  }
 mprintf("\n");
 }
#endif

int j=cuts;

for(i=num_of_edges-1;(i>=0)AND(j>0);i--)				// for each edge (in decreasing -non increasing- order)
 {
 if(em.MST_EDGE_COLOR(i)==(DATA)MST_RED);				// if red do nada.
 else { em.MST_EDGE_COLOR(i)=(DATA)MST_CUT; j--;		// if blue cut it.
        mprintf("(Cut # %d at blue edge %d (%d-%d length %f).)\n",j,i,(int)em.MST_EDGE_V1(i),(int)em.MST_EDGE_V2(i),(float)em.MST_EDGE_WEIGHT(i));}
 }      

if(j>0) 
 {
 mprintf("Warning: Could not perform %d cuts (too few edges?).\n",cuts); 
 run_ok=false;
 }

if(mrequest_yn("Cut any more edges manualy?"))
 {
 j=1;
 if(mrequest_yn("List MST (blue) edges before you cut?"))
  {
  for(i=0;i<em.cols();i++)
  if(em.MST_EDGE_COLOR(i)==MST_BLUE) mprintf("MST: Edge %d \t(%d-%d)\tlength:%f.\n",i,(int)em.MST_EDGE_V1(i),(int)em.MST_EDGE_V2(i),(float)em.MST_EDGE_WEIGHT(i));
  }
 while(j>=0)
  {
  j=mrequest_int("Select edge to cut...(negative to exit)");
  if((j>=0)AND(em.MST_EDGE_COLOR(j)==(DATA)MST_BLUE))
   {
   em.MST_EDGE_COLOR(j)=(DATA)MST_CUT;
   mprintf("(Manualy cut blue edge %d (%d-%d length %f).)\n",j,(int)em.MST_EDGE_V1(j),(int)em.MST_EDGE_V2(j),(float)em.MST_EDGE_WEIGHT(j));
   }
  }
 }

mstarttick("Reclustering...");

for(i=0;i<n_rows;i++) p_class[i]=-1;					// reset.

ct = 0;

for(i=0;i<num_of_edges;i++)								// recluster considering only BLUE (MST) edges.
 {	
 if(em.MST_EDGE_COLOR(i)==(DATA)MST_BLUE)
  {
   
  if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND
     (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge joins two unclustered points...
   {
   p_class[(int)em.MST_EDGE_V1(i)] = (DATA) ct;
   p_class[(int)em.MST_EDGE_V2(i)] = (DATA) ct;
   ct=ct+1;
   goto done_clustering_this_edge;
   }

  if((p_class[(int)em.MST_EDGE_V1(i)] == -1) AND 
	 (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge is added to an existing cluster at V2...
   {
   p_class[(int)em.MST_EDGE_V1(i)] = p_class[(int)em.MST_EDGE_V2(i)];
   goto done_clustering_this_edge;
   }

  if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
     (p_class[(int)em.MST_EDGE_V2(i)] == -1))									// edge is added to an existing cluster at V1...
   {
   p_class[(int)em.MST_EDGE_V2(i)] = p_class[(int)em.MST_EDGE_V1(i)];
   goto done_clustering_this_edge;
   }

  if((p_class[(int)em.MST_EDGE_V1(i)] != -1) AND 
     (p_class[(int)em.MST_EDGE_V2(i)] != -1))									// edge joins two existing clusters, we merge them...
   {
   DATA d1,d2;
   unsigned j;

   d1=min(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
   d2=max(p_class[(int)em.MST_EDGE_V1(i)],p_class[(int)em.MST_EDGE_V2(i)]);
   for(j=0;j<n_rows;j++) if(p_class[j]==d2) p_class[j]=d1;
   goto done_clustering_this_edge;
   }
  }

 done_clustering_this_edge:

 mtick(i,num_of_edges);
 }

mendtick();

// Step 2.2  Isolated points become clusters by themselves.

if(mrequest_yn("Put all isolated points (if any) in one (the last) cluster?"))
 {
 j=0;
 for(i=0;i<n_rows;i++)
  if(p_class[i]==-1)
   {
   p_class[i] = (DATA) ct;
   j++;
   }
 mprintf("Found %d isolated points, now all located in the last cluster.\n",j);
 if(j>0)
  mprintf("Sujestion: Re-run the algorithm for at least %d classes.\n",cuts+j+1);
 }
else
 {
 for(i=0;i<n_rows;i++)
 if(p_class[i]==-1)
  {
  p_class[i] = (DATA) ct;
  ct++;
  }
 }

// Step 2.3  Correct the "holes" found in p_class ids. These are created when we are merging clusters.

 {
 ct=0;
 int iter_ct = 0;
 int max_ct  = 0; 
 bool found_one = false;
 CTmatrix <int> ta (1,n_rows,-1,"Temporary Storage",true);

 for(i=0;i<n_rows;i++)  if(p_class[i]>max_ct) max_ct = (int) p_class[i];

 while(iter_ct<=max_ct)
  {
  found_one = false;
  for(i=0;i<n_rows;i++) 
   if(p_class[i]==iter_ct)
    {
	found_one=true;
    ta.at(0,i)=ct;
    }
  if(found_one) ct++;
  iter_ct++;
  }

 for(i=0;i<n_rows;i++) p_class[i]=(DATA)ta.at(0,i);
 }

// Done!

if(run_ok) {mprintf("MST Clustering returns OK, producing %d classes.\n",(int)ct);TGBL outputdim=ct;}
else       {mprintf("MST Clustering returns with Warning.\n");}
return run_ok;
}

/*-----------------------------------------------------------------------*/
// this function adds the point to the cluster and repeats for any adjucent points.

unsigned Similarity_Matrix_RECURSIVE_STEP(unsigned item, CTmatrix<short> & s,
                                               DATA * p_class, unsigned cluster_id) 
 {
 unsigned ra,ret=0;

 if(p_class[item]==-1)			// item not clustered
  {
  ret=1;
  p_class[item]=(DATA)cluster_id;
  for(ra=0;ra<s.rows();ra++)
   if(s.at(item,ra)==1)
    ret=ret+Similarity_Matrix_RECURSIVE_STEP(ra, s, p_class, cluster_id);
  }
 else
  {
  if(p_class[item]!=cluster_id)
   mprintf("Warning: Item %u was in %d, now is in %d!\n", item,(int)p_class[item], (int)cluster_id);
  }
 return ret;
 }

/*-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
// this is the main Similarity_Matrix routine

bool Similarity_Matrix_Clustering
			(DATA **	p_set,					// data set (n_rows x n_cols)
			 unsigned	n_rows,					// # of vectors in p_set
             unsigned	n_cols,					// dimentionality of each p_set vector
             DATA *		p_class)				// returned clustering index (n_rows x 1) 

{
mprintf("\nInvoking Similarity-Matrix (on %u x % u set)\n\n",n_rows,n_cols);

mhintclear();
mhintf(true,"For more on Similarity Matrix Method,\n");
mhintf(true,"see: Pattern Recognition,\n");
mhintf(true,"Applications to Large Data-Set Problems\n");
mhintf(true,"by Sing-Tze Bow (1984) p.131.\n");
mhintf(true,"\n");

bool run_ok=true;

DATA theta;

unsigned ra,rb;
CTmatrix <short> s (n_rows,n_rows,0,"Similarity Matrix");	// similarity matrix

 {
 double ED;
 double sED = 0;
 double maxED = 0;
 unsigned d=0;
 
 mstarttick("Estimating è");

 for(ra=0;ra<n_rows;ra++)
  {
  for(rb=(ra+1);rb<n_rows;rb++)
   {
   ED = EuclideanDistance(p_set[ra], p_set[rb], (int) n_cols);
   sED = sED + ED;
   if(ED>maxED) maxED=ED;
   d++;
   }
  mtick(ra,n_rows);
  }
 mendtick();

 mprintf("The %u inter-point euclidian distances average at %f.\n",d,(sED/d));
 mprintf("The maximum inter-point euclidian distance found is %f.\n",maxED);
 mprintf("On evenly distributed data points a (very rough) estimate\n");
 mprintf("of the recommented è would be as follows:\n");
 for(ra=2;ra<5;ra++)
  mprintf("- for aprox. %d clusters,\t è = %f (using average),\t è = %f (using max).\n",ra,sED/(d*ra),maxED/ra);
 mprintf("- etc...\n");

 mhintclear();
 mhintf(true,"Parameter è (theta) is the distance threshold below which\n");
 mhintf(true,"two points are considered similar (adjacent).\n");
 mhintf(true,"Small è implies more classes.\n");
  
 mprintf("Recommended è for %d classes is %f (using average), %f (using max),\n",TGBL outputdim,sED/(d*(TGBL outputdim)),maxED/(TGBL outputdim));
 if(mrequest_yn("Use recommented è (average-based) value?"))
  theta = sED/(d*(TGBL outputdim));
 else
  theta = mrequest_DATA("Please enter distance threshold è (theta)");
 }

mprintf("\nSelected è = %f.\n",theta);

mstarttick("Calculating Similarity Matrix");

for(ra=0;ra<n_rows;ra++)
 {
 for(rb=ra;rb<n_rows;rb++)
  if(EuclideanDistance(p_set[ra], p_set[rb], (int) n_cols) < theta)
   {
   s.at(ra,rb)=1;
   s.at(rb,ra)=1;
   }
  else
   {
   s.at(ra,rb)=0;
   s.at(rb,ra)=0;
   }
 mtick(ra,n_rows);
 }

mendtick();

s.show();

// initialize clusters.

for(ra=0;ra<n_rows;ra++) p_class[ra]=-1;

// form clusters

unsigned current_cluster_id = 0;

mstarttick("Forming Clusters");
 {
 int local, max = 0;
 unsigned  max_loc = 0;
 unsigned currently_classified = 0;
 unsigned pass = 0;

 while (currently_classified < n_rows)
  {

  //  Step 1. Find row with most 1's

  max = 0; max_loc = 0;

  for(ra=0;ra<n_rows;ra++)
   {
   local = 0;
   for(rb=0;rb<n_rows;rb++)
    if((p_class[ra]==-1)AND(p_class[rb]==-1))   // dont check rows, cols already clustered.
     {
     if(s.at(ra,rb)==-1)
      run_ok=false;
     else
      local=local+(int)s.at(ra,rb);
     }
   if(local>max)
	{
    max=local;
    max_loc = ra;
    }
   }

  mprintf("Pass %u: similarity matrix has most 1's at row %u (%d ones).\n",pass,max_loc,max);

  // Step 2. Form cluster corresponding to 1's in the row found in step 1.

  currently_classified += Similarity_Matrix_RECURSIVE_STEP(max_loc, s, p_class, current_cluster_id);

  mtick(currently_classified,n_rows);
  pass++;
  current_cluster_id++;
  }
 }
mendtick();

for(ra=0;ra<n_rows;ra++) if(p_class[ra]==-1) run_ok=false;
if(NOT run_ok)
 {
 mprintf("Warning, something is wrong: Check Similarity Matrix Algorithm.\n");
 return false;
 }
  
if (TGBL outputdim != current_cluster_id)	// we need this to SaveClasses correctly (stupid huh?).
 {
 mprintf("Similarity Matrix, Warning: Output size changes from %d to %u.\n",(int)(TGBL outputdim),current_cluster_id);
 TGBL outputdim=current_cluster_id;
 }

mprintf("\nResult: %u Classes.\n",current_cluster_id);

return true;
}

/*-----------------------------------------------------------------------*/

int graph_theoretic_algorithm_menu (int preselect)      /* -1 = Show menu */

{

mhintclear();
mhintf(true,"Since Graph Theoretic Methods are independent \n");
mhintf(true,"of presentation ordering, no experimentation  \n");
mhintf(true,"options are provided here, just load the *.prb\n");
mhintf(true,"file and run the algorithm.                   \n");
mhintf(true,"\n");
mhintf(true,"All methods are clustering algorithms, only the     \n");
mhintf(true,"training set and classification output are accessed.\n");

int msel=preselect;

char mtitle[]="Graph Theoretic Algorithm Menu";
char *menu[]={"0...No more processing - Go to previous menu.",
              "1...Similarity Matrix  Clustering.",
			  "2...Minimum Spanning Tree Clustering, cuts on longest MST edges.",
			  "3...Minimum Spanning Tree Modified (Cut n' Recluster).",
			  "4...Minimum Spanning Tree Clustering, cuts on a main MST diameter (DFS).",
			  "5...Minimum Spanning Tree Clustering, cuts on main MST diameter (no DFS)."
              };

TGBL ANS_run_success=false;
if(TGBL no_error)
 {
 if(preselect<0) msel=mmenu(mtitle,menu,6,5);

 switch(msel)
  {
  case 0: break;

  case 1: TGBL ANS_run_success = Similarity_Matrix_Clustering
                                                   (TGBL trainset,
                                                    TGBL trainsetsize,
								    			    TGBL inputdim,
												    TGBL classif);
		  break;

  case 2: TGBL ANS_run_success = MST_Clustering
												   (TGBL trainset,
													TGBL trainsetsize,
													TGBL inputdim,
													TGBL classif);
		  break;


  case 3: TGBL ANS_run_success = MSTCnR_Clustering
												   (TGBL trainset,
													TGBL trainsetsize,
													TGBL inputdim,
													TGBL classif);
		  break;


  case 4: TGBL ANS_run_success = MSTBV_Clustering
                                                   (TGBL trainset,
                                                    TGBL trainsetsize,
								    			    TGBL inputdim,
												    TGBL classif,
                                                    MSTBV_DEPTHFIRST);

          break;

  case 5: TGBL ANS_run_success = MSTBV_Clustering
                                                   (TGBL trainset,
                                                    TGBL trainsetsize,
								    			    TGBL inputdim,
												    TGBL classif,
                                                    MSTBV_CANDIDATE);
          break;

  default:break;
  }
 }

mbeep();
return(msel);
}


/*-----------------------------------------------------------------------*/

void graph_theoretic_menu(int preselect)
{
char mtitle[]="  Graph Theoretic Problem Menu ";
char *menu[]={"0...No more processing - Go to previous menu.",
              "1...Load Problem Description File.",
              "2...Preprocess/Scale Sets.",
              "3...Show Available Data Sets.",
			  "4...Select and run Graph Theoretic method."
             };
int msel;

msel=preselect;                          /* -1 means no preset selection */

while((TGBL no_error)&&(msel!=0))
 {
 if(preselect<0)
  {
  if(TGBL prb_loaded)
   msel=mmenu(mtitle,menu,5,4);     /* Show Algorithm option only if problem loaded */
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
  case 4: graph_theoretic_algorithm_menu(-1);  
          if(TGBL ANS_run_success)
           {
           ShowClassif();
		   SaveClassif("","TTNANS Graph Theoretic Method - based Classification Results",true);
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
