// Filter utilities, 
// Upon return, if true : (* ndata) = new (2-d DATA) set (malloced here).
//				if false : (* ndata) ???.

bool filter_set(DATA ** data,int rows,int cols,DATA *** ndata,int * nrows,int * ncols);
