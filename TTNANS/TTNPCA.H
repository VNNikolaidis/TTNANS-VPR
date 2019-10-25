/*
   --------------------
   TTNANS:
   TTNPCA.CPP  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------------------------
   PCA - Principal Components Analysis.
   ------------------------------------------
*/

void PCA		  (char * indataname, DATA ** indata, unsigned rows, unsigned cols, int preselect);
void PCALowMemory (char * indataname, DATA ** indata, unsigned rows, unsigned cols, int preselect);
