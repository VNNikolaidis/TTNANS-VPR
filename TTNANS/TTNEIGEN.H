
/* --------------------
   TTNANS: Eigen-routines
   --------------------
   Vasilis.N.Nikolaidis
   ---------------------

*/

#ifndef TTNEIGEN
#define TTNEIGEN

template <class D> class CTmatrix;
template <class D> class CTvector;

void sorted_eigen(CTmatrix <float> REF matrix,			// matrix will be modified here!.
				  CTmatrix <float> REF e_vecs,
				  CTvector <float> REF e_vals,
				  unsigned int np); 

#endif
