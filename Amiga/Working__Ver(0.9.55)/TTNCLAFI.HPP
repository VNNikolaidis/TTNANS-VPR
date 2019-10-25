
/* --------------------
   TTNANS:
   TTNCLAFI.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ---------------------
   Class (Cluster) Files
   (.x*,.f*) additionals
   ---------------------

*/

#ifndef TTNCLAFI
#define TTNCLAFI
extern BOOL is_class_file(char * fname);
extern void do_classification_filename(char * original, char * target);
/* Avoid calling next, call class_n_filename (below) instead.                                 */
extern void do_class_n_filename(char * original,int n, char * nthfname);
extern void class_n_filename(char * original, int n, char * nthfname);
extern int  class_number_of_class_filename(char * fname);
extern int  number_of_nonempty_class_files(char * fname);
extern int  index_nonempty_class_files(char * fname,int index[],int indexsize);
extern BOOL is_full_descriptor_class_filename(char *fname);
extern void reconstruct_testset_sizes_from_class_files(char *fname,int *r,int *c);
extern int  reconstruct_classification_and_testset_from_class_files
			 (char * fname,int * rclass,DATA ** rtestset,int r,int c);
extern void scaled_class_n_filename(char * original, int n, char *scaled);
extern void create_scaled_classification_files(char * fname,int get_scale_type);
extern void remove_scaled_classification_files(char * fname);
extern int  load_all_nonempty_class_files(char * fname,DATA **** data,
					  int **r,int *c,int ** index);
extern void unload_class_files(int N,DATA **** data,int **r,int ** index);
extern DATA make_alternative_descriptor_class_files(char * fname,int runnum);
extern DATA make_class_files_from_classification_file(char * prbfname,
						      char * clafname,int runnum);

#endif
