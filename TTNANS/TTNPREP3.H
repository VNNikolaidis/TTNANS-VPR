/*
  ---------------------
  TTNANS:
  TTNPREP2.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Data Preprocessing 3
  (ReOrdering)
  ---------------------

*/

#ifndef TTNPREP3
#define TTNPREP3

extern int ordering_info
		    (int preset,int * numofcombinations,
		     int reordersetsize,
		     int reordersetcols,
		     bool flag);

extern void ordering
	     (int reorder_type_in,  /* preselected (SRE_NOT_SET for menu).*/
	      int selection,        /* combination selector (if >1 combs).*/
	      DATA ** dataset,
	      int rows,             /* in dataset.                        */
	      int cols,             /* in dataset.                        */
	      int * ordering,       /* ordering indexes put here. Must    */
	      int nfirst);          /* be at least 'nfirst' size big.     */

extern void reorder_set
		(int reorder_type,
		 int selection,
		 DATA ** dataset,
		 int rows,
		 int cols);

#endif
